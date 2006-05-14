#!/usr/bin/python

##################################################################
# vim:ts=4:shiftwidth=4:noet:tw=78:
#
# This is a python script for testing the integraty of the tags.
# Run this in the 'doc' directory where all the translated files
# are together with the tags file.
#
# Author: lang2 (wzhliang@speedymail.org)
##################################################################


## I M P O R T S
import os
import os.path
import re
import string
import commands
import logging

## F U N C T I O N S
def print_tag_info(ti):
	"""Print informaiton about a tag."""
	print 'TAG: %s' % ti['name']
	print 'FILE: %s' % ti['file']
	print 'JUMP: %s' % ti['jump']

def adapt_pattern(pat):
	""" Adapt a vim search pattern to be used for grep."""
	str = string.replace(pat, '*', '\\*')
	str = string.replace(str, '[', '\\[')
	str = string.replace(str, ']', '\\]')
	str = string.replace(str, '^', '\\^')
	return str

def find_tag(ti):
	"""try to find the tag given the tag info."""
	if os.path.isfile( ti["file"] ):
		cmd = "grep '%s' %s" % ( adapt_pattern(ti["jump"]), ti["file"] )
		(err, msg) = commands.getstatusoutput( cmd )
		if 0 != err:
			print 'Tag\t%20s\tis not found in file <%s>.' \
				% (ti["name"], ti["file"])
			logging.info( 'COMMAND: %s' % cmd )
		#else:
			#logging.info ( msg )


def parse_tag_line(line):
	taginfo={}
	reobj = re.compile('(\S+)\s+(\S+)\s+/(\S+)')
	matobj = re.search( reobj, line )
	if not matobj is None:
		taginfo["name"] = matobj.group(1)
		taginfo["file"] = matobj.group(2)
		taginfo["jump"] = matobj.group(3)
		return taginfo
	else:
		print 'WARNING: tag %10s cannot be checked.' % taginfo["name"]
		return None

######################
## M A I N
######################
if __name__ == '__main__':
	#logging.getLogger().setLevel( logging.DEBUG )

	try:
		fp = open('tags', 'r')

		for line in fp:
			line = line.strip()
			taginfo = parse_tag_line(line)
			if not taginfo is None:
				find_tag(taginfo)
	except IOError:
		print 'Error reading tag file. You have to run this inside'
		print 'the doc directory.'
	except KeyError:
		print 'Something wrong with your tag file. Parsing error.'
	else:
		fp.close()

#EOF
