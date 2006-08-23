#!/usr/bin/env perl

# converts vim documentation to simple html
# Sirtaj Singh Kang (taj@kde.org)

# Sun Feb 24 14:49:17 CET 2002

# Updated by Willis (yianwillis@users.sourceforge.net)
# Sat Mar 24 12:11:02 EST 2006

use strict;
use utf8;
use Text::Tabs; # Willis: expand replaced by myexpand. So no longer necessary.
use Encode;
use vars qw/%url $date/;

%url = ();
$date = Encode::decode_utf8(`date --universal`);
chop $date;

sub maplink
{
	my $tag = shift;
	if( exists $url{ $tag } ){
		return $url{ $tag };
	} else {
		#warn "Unknown hyperlink target: $tag\n";
		$tag =~ s/</&lt;/g;
		$tag =~ s/>/&gt;/g;
		return "<code class=\"badlink\">$tag</code>";
	}
}

sub readTagFile
{
	my($tagfile) = @_;
	my( $tag, $file, $name );

	open(TAGS,"$tagfile") || die "can't read tags\n";

	while( <TAGS> ) {
		next unless /^(\S+)\s+(\S+)\s+/;

		$tag = $1;
		my $label = $tag;
		($file= $2) =~ s/.\w+$/.html/g; 

		$url{ $tag } = "<a href=\"$file#".escurl($tag)."\">".esctext($label)."</a>";
	}
	close( TAGS );
}

sub esctext
{
	my $text = shift;
	$text =~ s/&/&amp;/g;
	$text =~ s/</&lt;/g;
	$text =~ s/>/&gt;/g;
	return $text;
}

sub escurl
{
	my $url = shift;
	$url =~ s/"/%22/g;
	$url =~ s/~/%7E/g;
	$url =~ s/</%3C/g;
	$url =~ s/>/%3E/g;
	$url =~ s/=/%20/g;
	$url =~ s/#/%23/g;
	$url =~ s/\//%2F/g;

	return $url;
}

# expand() count bytes when computing tabstops. But each utf-8 character may
# take up to 3 bytes, we all know CJK characters use double width only.
$tabstop = 8;

sub mylength
{
    my ($str) = @_;
	my $length = length($str);
	my $i = 0;
	my @chars = unpack("U*", $str);
	foreach $i (@chars) {
		$length++ if $i > 255;
	}
	return $length;
}

sub myexpand
{   
    my (@l) = @_;
    for $_ (@l) {
        1 while s/(^|\n)([^\t\n]*)(\t+)/
            $1. $2 . (" " x 
                ($tabstop * length($3)
                - (mylength($2) % $tabstop)))
            /sex;
    }
    return @l if wantarray;
    return $l[0];
}

sub vim2html
{
	my( $infile ) = @_;
	my( $outfile );

	open(IN, "<:utf8", "$infile" ) || die "Couldn't read from $infile: $!.\n";

	($outfile = $infile) =~ s:.*/::g;

	my $tagfile =  ($outfile =~ /^tags(-..)?$/);
	if ($tagfile) {
		$outfile = "tags";
	} else {
		$outfile =~ s/\.\w+$//g;
	}

	open( OUT, ">:utf8", "$outfile.html" )
			|| die "Couldn't write to $outfile.html: $!.\n";
	binmode STDOUT, ":utf8";
	my $head = uc( $outfile );

	print OUT<<EOF;
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>VIM: $outfile</title>
<link rel="stylesheet" href="vim-stylesheet.css" type="text/css">
</head>
<body>
<h2>$head</h2>
<pre>
EOF

	my $inexample = 0;
	my $inheader = 0;
	if ($tagfile) {
		print OUT "<table>\n";
	}
	while( <IN> ) {
		chop;
		if ($tagfile) {
			print OUT "<tr>";
			my @fields = split(/\t/);
			if ($fields[0] eq "!_TAG_FILE_ENCODING") {
				print OUT "<td>" .  $fields[0] .  "</td><td>" .  $fields[1];
				print OUT "</td><td>" .  $fields[2] .  "</td></tr>\n";
			}
			else {
				$fields[1] =~ s/\.\w+/\.txt/;
				print OUT "<td>" .  maplink($fields[0]) .  "</td><td>";
				print OUT maplink($fields[1]) . "</td><td>". esctext($fields[2]);
				print OUT "</td></tr>\n";
			}
			next;
		}

		$_ = myexpand($_);
		if ( /^=+\s*$/ ) {
			print OUT "</pre><hr class=\"doubleline\" /><pre>\n";
			$inheader = 1;
			next;
		}
		elsif ( /^\s*-+\s*$/ ) {
			print OUT "</pre><hr class=\"singleline\" /><pre>\n";
			next;
		}

		# examples
		elsif( /^>$/ || /\s>$/ ) {
			if ( $inexample && /^(<)/ ) {
				$_ = $';
				$_ = " " . $_ if /^\s/;
			}	
			$inexample = 1;
			chop;
		}
		elsif ( $inexample && /^([<\S])/ ) {
			$inexample = 0;
			$_ = $' if $1 eq "<";
			$_ = " " . $_ if /^\s/;
		}

		s/\s+$//g;

		# Various vim highlights. note that < and > have already been escaped
		# so that HTML doesn't get screwed up.

		my @out = ();
		#		print "Text: $_\n";
		LOOP:
		foreach my $token ( split /((?:\|[^*"|[:space:]]+\|)|(?:\*[^*"|[:space:]]+\*))/ ) {
			if ( $token =~ /^\|([^*"|[:space:]]+)\|/ ) {
				# link
				push( @out, "|".maplink( $1 )."|" );
				next LOOP;
			}
			elsif ( $token =~ /^\*([^*"|[:space:]]+)\*/ ) {
				# target
				push( @out,
					"<b class=\"vimtag\">\*<a name=\"".escurl($1)."\">".esctext($1)."<\/a>\*<\/b>");
				next LOOP;
			}

			$_ = esctext($token);
			s/CTRL-(\w+|.)/<code class="keystroke">CTRL-$1<\/code>/g;
			# parameter <...>
			s/&lt;(.*?)&gt;/<code class="special">&lt;$1&gt;<\/code>/g;

			# parameter [...]
			s/\[(range|line|count|offset|cmd|[-+]?num)\]/<code class="special">\[$1\]<\/code>/g;
			# note
			s/(Note[:\s])/<code class="note">$1<\/code>/gi;

			s/(注意|备注)( (?=[^[:print:][:space:]]))?/<code class="note">$1<\/code>/g;
			s/VIM (?:参考手册|用户手册).*|译者[注]?/<code class="vim">$&<\/code>/g;

			# local heading
			s/^(.*)\~$/<code class="section">$1<\/code>/g;
			push( @out, $_ );
		}

		$_ = join( "", @out );

		# parameter {...}
		s/\{([^}]*)\}/<code class="special">{$1}<\/code>/g;

		if( $inexample == 2 ) {
			print OUT "<code class=\"example\">$_</code>\n";
		} elsif ($inheader == 1) {
			print OUT "<h4>$_</h4>";
		} else {
			print OUT $_,"\n";
		}

		$inexample = 2 if $inexample == 1;
		$inheader = 0;
	}
	if ($tagfile) {
		print OUT "</table>\n";
	}
	print OUT<<EOF;
</pre>
<p><i>Generated by vim2html on $date</i></p>
</body>
</html>
EOF
	close ( IN );
	close ( OUT );
}

sub usage
{
die<<EOF;
vim2html.pl: converts vim documentation to HTML.
usage:

	vim2html.pl <tag file> <text files>
EOF
}



sub writeCSS
{
	open( CSS, ">vim-stylesheet.css"  ) || die "Couldn't write stylesheet: $!\n";
	print CSS<<EOF;
body { background-color: white; color: black;}
:link { color: rgb(0,137,139); }
:visited { color: rgb(0,100,100);
           background-color: white; /* should be inherit */ }
:active { color: rgb(0,200,200);
          background-color: white; /* should be inherit */ }

B.vimtag { color : rgb(250,0,250); }

h1, h2 { color: rgb(82,80,82); text-align: center; }
h3, h4, h5, h6 { color: rgb(82,80,82); margin: 0px; }
.doubleline {
	border: none 0; border-top: 3px double #c00;
	width: 44em; height: 3px;
	margin: 10px auto 0 0; text-align: left;
}
.singleline {
	width: 40em; margin: 0px auto 0 0; text-align: left;
}
.headline { color: rgb(0,137,139); }
.header { color: rgb(164, 32, 246); }
.section { color: rgb(164, 32, 246); }
.keystroke { color: rgb(106, 89, 205); }
.vim { color: rgb(0, 136, 136); }
.example { color: rgb(0, 0, 255); }
.option { }
.notvi { }
.special { color: rgb(106, 89, 205); }
.note { color: blue; background-color: yellow; }
.sub {}
.badlink { color: rgb(0,37,39); }
EOF
	close ( CSS );
}

# main
#usage() if $#ARGV < 2;
usage() if !defined $ARGV[1];

print "Processing tags...\n";
readTagFile( $ARGV[ 0 ] );

vim2html( $ARGV[ 0 ] );
foreach my $file ( 1..$#ARGV ) {
	print "Processing ".$ARGV[ $file ]."...\n";
	vim2html( $ARGV[ $file ] );
}
print "Writing stylesheet...\n";
writeCSS();
print "done.\n"
