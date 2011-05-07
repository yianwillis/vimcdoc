/* HTML2LaTeX -- Converting HTML files to LaTeX
   Copyright (C) 1995-2009 Frans Faase

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

GNU General Public License:
   http://www.iwriteiam.nl/GNU.txt
*/

#define VERSION "2.7 of January 25, 2011."
#define WRITTEN_BY "F.J. Faase.  http://www.iwriteiam.nl/"
/*

Status: Has been tested on my documents

To do:

Known bugs:
    - accept \t as space inside tag scanning
    - empty_item sometimes false when should be true
    - deal with "\end{verbatim}" inside verbatim??

Revision history:
    110125
    - Added support for STYLE and NOSCRIPT tags
    - SCRIPT and STYLE are now standard LATEX_KIND_OFF
    - Enhancements contributed by John Pezaris http://www.johnpezaris.com
        - Added option -stdout for sending output to stdout
        - DEBUG_P macro's now output to stderr
    110123
    - Allow nested FONT tags
    100803
    - Now quotes can be used in the skeleton for file names containing spaces (as suggested by Stephan Clemenz)
    - Added t modifier (for text) to all fopen function calls
    - improved special character translation table (ch_table) based on: http://www.w3.org/TR/html4/sgml/entities.html
    080305
    - Small enhancements contributed by Lion Vollnhals
      - Added decoding for &deg;, &acute;, &brvbar;, &euro;, &trade;, &sup1;, &sup2; and &sup3;
      - Changed translation of Â¦ and ` to match the corresponding html renderings better.
    080223
    - Fixed decoding for &nbsp; (As suggested by Lion Vollnhals)
    080206
    - Fixed the default LaTeX encoding for some bold face, emphasize, italics, slanted and such
      (As suggested by Lion Vollnhals)
    070923
    - Small fixes contributed by Kenji Arisawa
      - changed &emdash; and &endash; to &mdash; and &ndash;.
      - added support for &ldquo; and &rdquo;.
      - unrecognized tags and attributes are converted to comments for
          post-processing with, for example, sed.
    060125
    - Small fixes contributed by Dr. Nigel Brown
    031114
    - Made some corrections with respect to the LaTeX output
      generated for some of the special characters. Thanks to
      Ott Toomet for pointing out the problem.
    030819
    - Added define ASCII8 for preventing translation of characters 160 to 255
    991029
    - fixed some small bugs
    990506
    - Added minimal support for SCRIPT, FORM, INPUT and TEXTAREA tags.
    - Dynamically allocate memory for comments.
    990427
    - Added minimal support for FONT tag.
    990317
    - On popular demand, changed the command line processing, such that
      a LaTeX file can be generated without having to create a template
      file. If a HTML is given as input file, a LaTeX file is generated
      from it. To check a HTML file, use the option '-c' or rename/link
      the program to chkhtml.
    990224
    - (in norm_URL remove everything after question mark.) [DISABLED]
    981229
    - added error reporting for non-existing local files
      other than HTML files, which were already reported.
    980124
    - allow latex-commands after latex-on
    - add option latex-fmt, which overrides format string. 
      Only works for internal references now.
    970314
    - replaced all \hbox by \mbox
    970301
    - fix bug with generating footnotes in headers
    - added %p before \cite in f_cite(_n)
    970224
    - use \( and \) for math inside alltt
    970223
    - fixed `empty_line is sometimes false when it should be true' bug
    - added support for many more specials
    - added more tags
    - fixed usage of SUB and SUP tags outside math mode. Can be nested.
    970221
    - Experimental: generate `{\"u}' for `&uuml;' in alltt mode.
    970216
    - remove tolower for processing options. Did not recognize f_URL
    970115
    - for opt_no_header print_sp was called with fout == NULL (twice)
    970103
    - the meta-tags l1 to l2 could not be redefined.
    961221
    - "not included" turned into info (instead of warning)
    - suppress "empty item" when inside no-copy part.
    960903
    - fixed problem with <A NAME=".."> inside <HEAD>.
    960828
    - fixed bug with <p> <!--latex-off--> combination.
    - added (some) support for <sup> and <sub>. Does not work for
      nested tags.
    - added -o<FN> option for specifying output file.
    - fixed bug with <a name=".."> inside <head> (not completely)
    (These four were reported/fixed by: Victor Volle 
     <vrvolle@cip.informatik.uni-erlangen.de>)
    - allow META tag inside HEAD, and ignore attributes of META tag.
    - fixed bug with <ul> </ul>, which caused an \item[] to be
      generated afterwards. Added: no_item = FALSE.
    960827
    - -cr option was not recognized on the command line.
    - added error message for unknown document style.
    960710
    - bug-fix in alltt \ should be mapped to \(\backslash\) instead of \\
      (reported by: Daniel Drotos <drotos@cpc.wmin.ac.uk>) 
    960708
    - added error reporting about non-existing non-HTML files.
    960703
    - added code for parsing `\nl', must have been deleted accidentialy
    - fixed bug (skipping spaces) in process_option
      (Thanks to Chris Ritson <C.R.Ritson@ncl.ac.uk> for theses fixes)
    - added support for `report' style (= `book' style)
    960626
    - added empty_line = FALSE after echoing comment (bug-fix)
    - fixed wrong default value for latex open for H4.
    - changed default value for code into \tt.
    - chenged default value for quote into \em
    - added \nl after close quotation
    960623
    - removed recalculation of H1-H6 tagnr values. (a bug)
    960614
    - add options no_title, no_header and at_start
    - removed bug in -o processing
    - removed bug in process-definition (looked only at first option)
    - removed bug with wrong use of realloc
    960530
    - map character '\t' on 8 spaces.
    960520
    - add option at start.
    960519
    - rewrote print_str_ to deal with &special and >127. Does not report
      warnings.
    - rewrote level system, as -l<nr> options of latex-def.
    960517
    - rewrote &special; and added support for >127 characters.
    - recognize .htm as html extension
    - small bug-fixes from Michael Ritzert <mjr@geo.uni-bonn.de>
    960515
    - bug-fix: no latex commands for special characters were generated.
    - missing file are only reported once.
    - bug-fix: unknown <..> gave last attribte name, instead of tag.
    - add checking of empty name and href tags.
    - give warnings for ignored attributes.
    960514 
    - improved reference checking and reporting.
    960512
    - added -on option for switching copying on
    - added -igh option for ignoring headers. (Added to blockquote/bq; bug-fix)
    960508
    - changed "cf. " into "cf.\ ".
    960506
    - improved error messages for references.
    960504
    - bug-fix for -s (I accidenlty removed a call to find_file).
    - improved treatment of alternating <A> and <P>, which caused stack 
      overflows.
    960503
    - bug-fix generation of incorrect HREF's is suppressed.
    960428
    - add "\n" after "\quote"
    - fix generation for < and > in normal text
    960422
    - added more options.
    - prevent redefinitions of HTML tags in first pass.
    960413
    - Ignore external references if they are included in the anchor text
    960410
    - add code for filling atext with text inside anchors
    - error message for ignored href moved from close-latex to open-latex
    960409
    - add function for splitting a URL
    960407
    - in alltt mode \, {, and } are now backslashed.
    - newlines are printed directly in alltt and verb mode, instead
      of being delayed through gen-newline.
    960401
    - warnings on not included but ignored file are suppressed.
    960331
    - made some modifications because of lclint.
    960312
    - Added some "empty_line = TRUE" statement, and some additional
      checking for tweede "gen_newline = TRUE".
    960311
    - Improved comment processing. Can process comments in any tag
      now. Give warning for non-standard comments, and comments that
      exceed maximum length of 10000 characters.
    960309
    - T_DIR markers also go through latex-open/close now
    - improved generation of newlines. (a <BR> on an empty line is
      printed after the last non-empty line.)
    960305:
    - added %html -i <file> for ignoring files.
    - did something on math-mode and iim (ignore inside math)
    - Fixed LaTeX generation for latex-off/latex-on (has not been tested!)
    - bug-repear: <P> was being ignored.
    960304:
    - Added some more special characters. (Many still missing.)
    960301:
    - added link mapping (use: %html -l "from" "to")
    960229:
    - Supress generation of LaTeX for HTML tags inside Tags with -off.
      (The latex_open part of tags with -off is ouyputted, the
      latex_close part not.)
    - '[' and ']' are now generated as '$[$' and '$]$' (was $\[$ and $\]$).
    (Thanks: Rejnold Byzio and Arno Schielke <m11h1@ifra.ing.tu-bs.de>)

    960205:
    - adding switches for changing latex output.

    960201: warwick@cs.uq.oz.au
    - fixed off-by-one error.
    - add 1mm space above hrules.
    - use abort() rather than div0 hack. (FF: slightly modified)
    - ignore HTML3 tables and meta (for now).
    - support Netscapism centering.
    - add -p (pendantic) option, without which <HTML></HTML> is not insisted.
    - added "<!latex ...>" which causes "..." to carry through to latex.
      - can add latex-only text
      - can mark text as html-only by using:
        <!latex \begin{xcomment}>
                ...
        <!latex \end{xcomment}>
        (xcomment.sty is written by Timothy Van Zandt, tvz@Princeton.EDU)
    - IMG tags carried through as \\framebox{IMAGE: imagefilename}
      - note that filename does not have "_" escaped, in order to aid
        automated conversion (eg. via sed) of these tags to such
        constructs as \epsfbox{filename.eps}.
    - increased limits DRASTICALLY (especially comments, for the
        purpose of including large amounts of text via <!latex ... >)

   960113:
   - extending error reporting in scan-a-file.
   - changed meaning of -i option. -w used to include -i, now -i includes -w
   - removed bug in "-r .." option processing.
   960112:
   - adding `index.html' support.
   960110:
   - improved the tag checking.
   951111:
   - did some more hacking, to make it working again.
   950811:
   - added corrections from Wolfgang Wander <wwc@lars.desy.de>:
     - for br: \\\\\n -> \\newline\n
     - for hr: -> \n\n  (not yet)
     - add processing for ^
   - added some ideas found in htmllatex.pl from 
     Jacob C. Kesinger <n9146070@cc.wwu.edu>:
   950803:
   - added more syntax checking
   950728:
   - added missing markings and comment processing
   - accept both NAME and HREF in anchor
   - \label generated after end of /H*
   950706:
   - allow a single reference between <dt> and <dd>
   950608:
   - resolved bug in printing name part (starting with #) in footnote
   950601:
   - removed useless call to find_file in print_label that caused core dump
   950530:
   - replaced names in labels with numbers
   950502: 
   - solved bug: took first argument as output file name.
   - references in <ADDRESS> are omitted during output generation
   950303: 
   - solved bug in -s option. It now does a complete recursive
     search.
   - some extra parsing added. Still alot is missing. No compliance
     with the any standard.
   - the program can now also except a single html file as input.
     It does not generate any LaTeX output.
*/

#include <stdio.h>
#include <string.h>
#ifdef _MSC_VER
#include <io.h>
const R_OK = 4;
#define access _access
#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <ctype.h>

/*********** Basic definitions **************/

typedef int bool;
#define TRUE (bool)1
#define FALSE (bool)0

typedef unsigned char byte;

#define ALLOC(type) (type *)malloc(sizeof(type))
#define SALLOC(s)   (char *)malloc(strlen(s)+1)
#define NALLOC(type,n) (type *)malloc((n)*sizeof(type))
#define SREALLOC(d,s) (char *)realloc(d,strlen(s)+1)
#define NREALLOC(d,type,n) (type *)realloc(d,(n)*sizeof(type))

/************ lclint macros ************/

#define streq(A,B) (strcmp(A,B) == 0)
#define strneq(A,B,C) (strncmp(A,B,C) == 0)
#define memeq(A,B,C) (memcmp(A,B,C) == 0)

/*********** debug macros *********/

#define DYN_DEBUG
#ifdef DEBUG
#define DEBUG_P(F)  fprintf(stderr,F)
#define DEBUG_P1(F,A1)  fprintf(stderr,F,A1)
#define DEBUG_P2(F,A1,A2)  fprintf(stderr,F,A1,A2)
#define DEBUG_P3(F,A1,A2,A3)  fprintf(stderr,F,A1,A2,A3)
#define DEBUG_P4(F,A1,A2,A3,A4)  fprintf(stderr,F,A1,A2,A3,A4)
#define DEBUG_P5(F,A1,A2,A3,A4,A5)  fprintf(stderr,F,A1,A2,A3,A4,A5)
#define BREAK { int i = i/0; } /* sneaky trick to remain in debugger */
#else
#ifdef DYN_DEBUG
bool option_debug = FALSE;
#define DEBUG_P(F)  if (option_debug) fprintf(stderr,F)
#define DEBUG_P1(F,A1)  if (option_debug) fprintf(stderr,F,A1)
#define DEBUG_P2(F,A1,A2)  if (option_debug) fprintf(stderr,F,A1,A2)
#define DEBUG_P3(F,A1,A2,A3)  if (option_debug) fprintf(stderr,F,A1,A2,A3)
#define DEBUG_P4(F,A1,A2,A3,A4)  if (option_debug) fprintf(stderr,F,A1,A2,A3,A4)
#define DEBUG_P5(F,A1,A2,A3,A4,A5)  if (option_debug) fprintf(stderr,F,A1,A2,A3,A4,A5)
#define BREAK { int i = i/0; } /* sneaky trick to remain in debugger */
#else
#define DEBUG_P(F)  
#define DEBUG_P1(F,A1)  
#define DEBUG_P2(F,A1,A2)  
#define DEBUG_P3(F,A1,A2,A3)  
#define DEBUG_P4(F,A1,A2,A3,A4) 
#define DEBUG_P5(F,A1,A2,A3,A4,A5) 
#define BREAK { fprintf(stderr, "\nInternal error, please report\n"); abort(); }
#endif
#endif

#define DEBUG_GN(X) /* fputc(X, fout) */

#define DO_DEBUG_P(F)  fprintf(stderr,F)
#define DO_DEBUG_P1(F,A1)  fprintf(stderr,F,A1)
#define DO_DEBUG_P2(F,A1,A2)  fprintf(stderr,F,A1,A2)
#define DO_DEBUG_P3(F,A1,A2,A3)  fprintf(stderr,F,A1,A2,A3)
#define DO_DEBUG_P4(F,A1,A2,A3,A4)  fprintf(stderr,F,A1,A2,A3,A4)

/************** ASCII-8 *****************/

#ifdef ASCII8
#define HIGHASCII 255
#else
#define HIGHASCII 126
#endif

/************** prototypes ***************/

char *rel_URL(char *from, char *to);

/************** Program options stored in global variables *******/

bool option_info = FALSE,
     option_warn = FALSE,
     option_pedantic = FALSE,
     option_bibliography = FALSE,
     option_stdout = FALSE,
     is_html_fn = FALSE;

/************** Generation options *************/



#define OPT_NONE   0
#define OPT_FN     1
#define OPT_CFFN   2
#define OPT_NORMAL 3

#define OPT_KIND_STR  0
#define OPT_KIND_IN   1
#define OPT_KIND_BOOL 2

#define NR_OPTS  44
struct
{   char *name;
    char *str;
    int  v;
    int  kind;
} allopt[NR_OPTS] =
{   { "citenr",         NULL, 0, OPT_KIND_STR},
    { "cite",           NULL, 0, OPT_KIND_STR},
    { "cite_n",         NULL, 0, OPT_KIND_STR},
    { "f_cite",         NULL, 0, OPT_KIND_STR},
    { "f_cite_n",       NULL, 0, OPT_KIND_STR},
    { "filenr",         NULL, 0, OPT_KIND_STR},
    { "label",          NULL, 0, OPT_KIND_STR},
    { "label_n",        NULL, 0, OPT_KIND_STR},
    { "cf",             NULL, 0, OPT_KIND_STR},
    { "cf_n",           NULL, 0, OPT_KIND_STR},
    { "f_cf",           NULL, 0, OPT_KIND_STR},
    { "f_cf_n",         NULL, 0, OPT_KIND_STR},
    { "f_news",         NULL, 0, OPT_KIND_STR},
    { "f_mailto",       NULL, 0, OPT_KIND_STR},
    { "f_ftp",          NULL, 0, OPT_KIND_STR},
    { "f_ftp_d",        NULL, 0, OPT_KIND_STR},
    { "f_ftp_f",        NULL, 0, OPT_KIND_STR},
    { "f_ftp_df",       NULL, 0, OPT_KIND_STR},
    { "f_URL",          NULL, 0, OPT_KIND_STR},
    { "f_URL_n",        NULL, 0, OPT_KIND_STR},
    { "b_news",         NULL, 0, OPT_KIND_STR},
    { "b_mailto",       NULL, 0, OPT_KIND_STR},
    { "b_ftp",          NULL, 0, OPT_KIND_STR},
    { "b_ftp_d",        NULL, 0, OPT_KIND_STR},
    { "b_ftp_f",        NULL, 0, OPT_KIND_STR},
    { "b_ftp_df",       NULL, 0, OPT_KIND_STR},
    { "b_URL",          NULL, 0, OPT_KIND_STR},
    { "b_URL_n",        NULL, 0, OPT_KIND_STR},
    { "t_img",          NULL, 0, OPT_KIND_STR},
    { "t_img_r",        NULL, 0, OPT_KIND_STR},
    { "t_href",         NULL, 0, OPT_KIND_STR},
    { "s_math_open",    NULL, 0, OPT_KIND_STR},
    { "s_math_close",   NULL, 0, OPT_KIND_STR},
    { "empty_item",     NULL, 0, OPT_KIND_STR},
    { "href",           NULL, 0, OPT_KIND_IN},
    { "href_in_alltt",  NULL, 0, OPT_KIND_IN},
    { "href_in_header", NULL, 0, OPT_KIND_IN},
    { "dni_email",      NULL, 0, OPT_KIND_BOOL},
    { "dni_ftp",        NULL, 0, OPT_KIND_BOOL},
    { "dni_news",       NULL, 0, OPT_KIND_BOOL},
    { "dni_other",      NULL, 0, OPT_KIND_BOOL},
    { "no_header",      NULL, 0, OPT_KIND_STR},
    { "no_title",       NULL, 0, OPT_KIND_STR},
    { "at_start",       NULL, 0, OPT_KIND_STR},
};

#define opt_citenr         allopt[ 0].str
#define opt_cite           allopt[ 1].str
#define opt_cite_n         allopt[ 2].str
#define opt_f_cite         allopt[ 3].str
#define opt_f_cite_n       allopt[ 4].str
#define opt_filenr         allopt[ 5].str
#define opt_label          allopt[ 6].str
#define opt_label_n        allopt[ 7].str
#define opt_cf             allopt[ 8].str
#define opt_cf_n           allopt[ 9].str
#define opt_f_cf           allopt[10].str
#define opt_f_cf_n         allopt[11].str
#define opt_f_news         allopt[12].str
#define opt_f_mailto       allopt[13].str
#define opt_f_ftp          allopt[14].str
#define opt_f_ftp_d        allopt[15].str
#define opt_f_ftp_f        allopt[16].str
#define opt_f_ftp_df       allopt[17].str
#define opt_f_URL          allopt[18].str
#define opt_f_URL_n        allopt[19].str
#define opt_b_news         allopt[20].str
#define opt_b_mailto       allopt[21].str
#define opt_b_ftp          allopt[22].str
#define opt_b_ftp_d        allopt[23].str
#define opt_b_ftp_f        allopt[24].str
#define opt_b_ftp_df       allopt[25].str
#define opt_b_URL          allopt[26].str
#define opt_b_URL_n        allopt[27].str
#define opt_t_img          allopt[28].str
#define opt_t_img_r        allopt[29].str
#define opt_t_href         allopt[30].str
#define opt_s_math_open    allopt[31].str
#define opt_s_math_close   allopt[32].str
#define opt_empty_item     allopt[33].str
#define opt_href           allopt[34].v
#define opt_href_in_alltt  allopt[35].v
#define opt_href_in_header allopt[36].v
#define opt_dni_email      allopt[37].v
#define opt_dni_ftp        allopt[38].v
#define opt_dni_news       allopt[39].v
#define opt_dni_other      allopt[40].v
#define opt_no_header      allopt[41].str
#define opt_no_title       allopt[42].str
#define opt_at_start       allopt[43].str

void assign_str(char **dest, char *src)
{  
    if (*dest == NULL) 
        *dest = SALLOC(src);
    else
        *dest = SREALLOC(*dest, src);
    strcpy(*dest, src);
}

void init_opts()
{
    assign_str(&opt_citenr   , "b%d");
    assign_str(&opt_cite     , "%p\\cite{%c}");
    assign_str(&opt_cite_n   , "%p\\cite[%n]{%c}");
    assign_str(&opt_f_cite   , "%p%F{See %p\\cite{%c}}");
    assign_str(&opt_f_cite_n , "%p%F{See %p\\cite[%n]{%c}}");

    assign_str(&opt_filenr   , "f%d");
    assign_str(&opt_label    , "%p\\label{%f}");
    assign_str(&opt_label_n  , "%p\\label{%f:%n}");
    assign_str(&opt_cf       , " (cf.\\ Section~%p\\ref{%f})");
    assign_str(&opt_cf_n     , " (cf.\\ Section~%p\\ref{%f:%n})");
    assign_str(&opt_f_cf     , "%p%F{See also Section~%p\\ref{%f}.}");
    assign_str(&opt_f_cf_n   , "%p%F{See also Section~%p\\ref{%f:%n}.}");

    assign_str(&opt_f_news   , "%p%F{See URL news:%n}");
    assign_str(&opt_f_mailto , "%p%F{See URL mailto:%m}");
    assign_str(&opt_f_ftp    , "%p%F{See URL ftp://%s}");
    assign_str(&opt_f_ftp_d  , "%p%F{See URL ftp://%s/%d}");
    assign_str(&opt_f_ftp_f  , "%p%F{See URL ftp://%s/%f}");
    assign_str(&opt_f_ftp_df , "%p%F{See URL ftp://%s/%d/%f}");
    assign_str(&opt_f_URL    , "%p%F{See URL %U}");
    assign_str(&opt_f_URL_n  , "%p%F{See URL %U\\#%n}");

    assign_str(&opt_b_news   , "news:%n");
    assign_str(&opt_b_mailto , "mailto:%m");
    assign_str(&opt_b_ftp    , "ftp://%s");
    assign_str(&opt_b_ftp_d  , "ftp://%s/%d");
    assign_str(&opt_b_ftp_f  , "ftp://%s/%f");
    assign_str(&opt_b_ftp_df , "ftp://%s/%d/%f");
    assign_str(&opt_b_URL    , "%U");
    assign_str(&opt_b_URL_n  , "%U\\#%n");

    assign_str(&opt_t_img    , "\\fbox{\\texttt{%n %mR}}%tR");
    assign_str(&opt_t_img_r  , "%r");
    assign_str(&opt_t_href   , "%R");

    assign_str(&opt_s_math_open  , "\\(");
    assign_str(&opt_s_math_close , "\\)");
    assign_str(&opt_empty_item   , "\\item[] ");

    opt_href           = OPT_NORMAL;
    opt_href_in_alltt  = OPT_NONE;
    opt_href_in_header = OPT_NORMAL;

    opt_dni_email = TRUE;
    opt_dni_ftp   = TRUE;
    opt_dni_news  = TRUE;
    opt_dni_other = TRUE;

    assign_str(&opt_no_header , "");
    assign_str(&opt_no_title  , "");
    assign_str(&opt_at_start  , "");
}

/********** HTML files and there references **********/

/* list of HREF's that reference a NAME: */
typedef struct ref_by_T
{   struct ref_by_T *next;
    char *file;       /* HTML file that references this name */
    int  ln;          /* ln number */
    char *name;       /* NAME after which the reference appears */
    struct link_T *href;  /* HREF following this name, which refers
                             to this file/name */
} ref_by_t;


/* struct for NAME: */
typedef struct
{   char *name;
    bool exists;
    bool repeated;
    bool referenced;  /* set if referenced by HREF which is outputted to
                         LaTeX. */
    ref_by_t *ref_by;
} name_t;


/* struct for HREF: */
typedef struct 
{   struct file_T *file;
    char *name;
    char *re_name;
    int status;
    int ln;
} ref_t;

/* coding for ref_t.status: */
#define S_CORRECT  0    
#define S_E_FILE   1    /* HTML file does not exist */
#define S_U_FILE   2    /* HTML file name is an URL */
#define S_E_NAME   3    /* NAME in HTML file does not exist */


/* List of HREF and NAME in a HTML file */
typedef struct link_T
{   struct link_T *next;
    int kind;
    union
    {   name_t name;
        ref_t ref;
    } info;
    bool copied;    /* set if outputted in LaTeX */
} link_t;

/* Coding for link_t.info */
#define A_NAME 0
#define A_HREF 1


/* Information of a file: */
typedef struct file_T
{   struct file_T *next;
    char *name;
    int nr;
    link_t *link;
    bool exists;      /* exists == TRUE implies !is_URL(name) */
    int read;
    bool ignore;      /* do not generate reference to it */
    int nr_refs;      /* number of references to this file */
    ref_by_t *ref_by;
} file_t;

/* Coding for file_t.read: */
#define R_UNREAD   0
#define R_READ     1    /* HTML file read, to check for consistency */
#define R_INCLUDED 2    /* HTML file included in LaTeX output */


/* List of all files: */
file_t *the_files = NULL;
int nr_files = 0;

/************ Procedures for storing reference information *******/ 

char *c_top = ":TOP";

char *norm_name(char *name)
{    return name == NULL ? c_top : name;
}

bool eq_name(char *a, char *b)
{    if (a == NULL || a == c_top || *a == '\0')
         return b == NULL || b == c_top || *b == '\0';
     if (b == NULL || b == c_top || *b == '\0')
         return FALSE;
     return !strcmp(a, b);
}

bool is_URL(name) char *name;
/* returns TRUE if name is an URL. */
{   return    memeq(name, "news:", 5)
           || memeq(name, "http:", 5)
           || memeq(name, "file:", 5)
           || memeq(name, "ftp:", 4)
           || memeq(name, "wais:", 5)
           || memeq(name, "gopher:", 7)
           || memeq(name, "mailto:", 7)
           || memeq(name, "telnet:", 7);
}

bool is_html(name) char *name;
/* returns TRUE if name has .html extension */
{   return    streq(name + strlen(name) - 5, ".html") 
           || streq(name + strlen(name) - 4, ".htm");
}

file_t *find_file(file) char *file;
/* Returns pointer to HTML file record with the name `file'.
   If such a record did not exist in the list, it is added
   alphabetically on the file name.
*/
{   file_t **p_file = &the_files;

    while (*p_file != NULL && strcmp((*p_file)->name, file) < 0)
        p_file = &(*p_file)->next;

    if (*p_file == NULL || strcmp((*p_file)->name, file))
    {   file_t *n = ALLOC(file_t);
        DEBUG_P("FILEADDED\n");
        n->next = *p_file;
        n->name = SALLOC(file);
        strcpy(n->name, file);
        n->nr = nr_files++;
        n->link = NULL;
        n->exists = access(file, R_OK) == 0;
        n->read = R_UNREAD;
        n->ref_by = NULL;
        n->ignore = FALSE;
        n->nr_refs = 0;
        *p_file = n;
    }

    return *p_file;
}

void add_name(file, name, copied) char *file; char *name; bool copied;
/* Adds a NAME record for `name' at the end of the list of the HTML file 
   `file'. Checks of the name is repeated.
*/
{   file_t *tfile = find_file(file);
    link_t **p_link = &tfile->link;
    bool repeated = FALSE;

    DEBUG_P2("add_name(%s,%s)\n", file, name);

    for(;*p_link != NULL; p_link = &(*p_link)->next)
        if (   (*p_link)->kind == A_NAME
            && streq((*p_link)->info.name.name, name))
             repeated = TRUE;

    {  link_t *n = ALLOC(link_t);
       n->next = NULL;
       n->kind = A_NAME;
       n->info.name.name = SALLOC(name);
       strcpy(n->info.name.name, name);
       n->info.name.exists = TRUE;
       n->info.name.repeated = repeated;
       n->info.name.referenced = FALSE;
       n->info.name.ref_by = NULL;
       n->copied = copied;
       *p_link = n;
    }
}

link_t *last_ref = NULL;

void add_ref(file, ln, to_file, name)
char *file; int ln; char *to_file; char *name;
/* Adds a HREF record at the end of the list of the HTML file `file' to
   HTML file `to_file' and (optional) NAME `name'.
*/
{   file_t *tfile = find_file(file);
    link_t **p_link = &tfile->link;

    DEBUG_P4("add_ref(%s,%d,%s,%s)\n", file, ln, to_file, name);
    for(;*p_link != NULL; p_link = &(*p_link)->next);

    {  link_t *n = ALLOC(link_t);
       n->next = NULL;
       n->kind = A_HREF;
       n->info.ref.ln = ln;
       n->info.ref.file = find_file(to_file);
       if (name == NULL)
            n->info.ref.name = NULL;
       else
       {   n->info.ref.name = SALLOC(name);
           strcpy(n->info.ref.name, name);
       }
       n->info.ref.re_name = NULL;
       n->info.ref.status = S_CORRECT; /* temporary */
       n->copied = TRUE;
       *p_link = n;
    }
    last_ref = *p_link;
}

/* Return values for find_ref */
#define REF_OKAY            0
#define REF_FILE_NOT_FOUND  1  /* HTML file does not exist */
#define REF_FILE_NOT_INC    2  /* HTML file not included in LaTeX */
#define REF_FILE_IGNORED    3  /* HTML file is ignored in output */
#define REF_NAME_NOT_FOUND  4  /* NAME not found in HTML file */
#define REF_NAME_NOT_INC    5  /* NAME not included in LaTeX, but referenced */
#define REF_ILL             6  /* Illegal (or too long) formed URL */

int find_ref(file, name) char *file, *name;
/* Checks reference to HTML file `file' with (optional) NAME `name' and 
   returns appropriate return value. */
{   file_t *tfile = the_files;
    link_t *link;    

    DEBUG_P2("find_ref(%s, %s)\n", file, name);

    if (is_URL(file)/* || !is_html(file)*/)
        return REF_OKAY;

    while (tfile != NULL && strcmp(tfile->name, file) < 0)
        tfile = tfile->next;

    if (tfile == NULL || strcmp(tfile->name, file))
        return REF_FILE_NOT_FOUND;
    if (!tfile->exists)
        return REF_FILE_NOT_FOUND;
    if (tfile->ignore)
        return REF_FILE_IGNORED;
    if (!(tfile->read & R_INCLUDED))
        return REF_FILE_NOT_INC;
    if (name[0] == '\0')
        return REF_OKAY;

    if (!is_html(file))
        return name[0] == '\0' ? REF_NAME_NOT_FOUND : REF_OKAY;

    for (link = tfile->link; link != NULL; link = link->next)
        if (link->kind == A_NAME && streq(link->info.name.name, name))
            return   link->info.name.exists
                   ? (link->copied ? REF_OKAY : REF_NAME_NOT_INC)
                   : REF_NAME_NOT_FOUND;

    return REF_NAME_NOT_FOUND;
}

int name_repeated(file, name) char *file, *name;
/* Checks reference to HTML file `file' with (optional) NAME `name' and 
   returns appropriate return value. */
{   file_t *tfile = the_files;
    link_t *link;    

    DEBUG_P2("name_repeated(%s, %s)\n", file, name);

    while (tfile != NULL && strcmp(tfile->name, file) < 0)
        tfile = tfile->next;

    for (link = tfile->link; link != NULL; link = link->next)
        if (link->kind == A_NAME && streq(link->info.name.name, name))
            return link->info.name.repeated;
    return FALSE;
}

int name_referenced(file, name) char *file, *name;
/* Returns TRUE if NAME `name' in HTML file `file' is referenced,
   otherwise FALSE.
*/
{   file_t *tfile = the_files;
    link_t *link;    

    DEBUG_P2("name_referenced(%s, %s)\n", file, name);

    if (is_URL(file))
        return FALSE;

    while (tfile != NULL && strcmp(tfile->name, file) < 0)
        tfile = tfile->next;

    if (tfile == NULL || strcmp(tfile->name, file))
        return FALSE;

    if (!(tfile->read & R_INCLUDED))
        return FALSE;

    if (name == NULL)
        return FALSE;

    link = tfile->link;

    while(link != NULL)
        if (link->kind == A_NAME && streq(link->info.name.name, name))
            return link->info.name.referenced;
        else
            link = link->next;

    return FALSE;
}

/********** Procedures for making/checking cross references ***********/   

int nstrcmp(str1, str2) char *str1, *str2;
/* This procedure compares two strings, like strcmp, where the string 
   pointers can be NULL. A NULL pointer comes before all other strings.
*/
{   return   (str1 == NULL)
           ? (str2 == NULL ? 0 : -1)
           :   (str2 == NULL)
             ? 1
             : strcmp(str1, str2);
}

void add_ref_by(p_ref_by, file, ln, name, href)
ref_by_t **p_ref_by; char *file; int ln; char *name; link_t *href;
/* This procedures adds HTML file `file' with (optional) name `name' to
   the list `p_ref_by' in alphabetic order. The value of `href' is
   assign to the field `href'.
*/
{   int c;

    DEBUG_P2("add_ref_by(,%s,%s)\n", file, name);

    while(   *p_ref_by != NULL
          && (   (c = strcmp((*p_ref_by)->file, file)) < 0
              || (   c == 0
                  && (c = nstrcmp((*p_ref_by)->name, name)) < 0)))
           p_ref_by = &(*p_ref_by)->next;

    if (*p_ref_by == NULL || c != 0)
    {   ref_by_t *n = ALLOC(ref_by_t);
        DEBUG_P("ADDED\n");
        n->next = *p_ref_by;
        n->file = file;
        n->name = name;
        n->href = href;
        n->ln = ln;
        *p_ref_by = n;
    }
}

link_t *find_re_href(l, file, name)
link_t *l; file_t *file; char *name;
/* Returns name used in HREF to HTML file `file' in link list `l' either
   equal to `name' or the first, where a not NULL name is prefered
   above a NULL name (e.g. reference to the file).
*/
{   link_t *first = NULL;

    for(;l != NULL; l = l->next)
        if (l->kind == A_HREF && l->info.ref.file == file)
        {   if (eq_name(name, l->info.ref.name))
                return l;
            if (first == NULL)
                first = l;
        }

    return first;
}

int check_ref(file_t *file, int ln, char *name, file_t *file_to, char *name_to,
              bool copied);
int check_ref(file, ln, name, file_to, name_to, copied)
file_t *file; int ln; char *name; file_t *file_to; char *name_to; bool copied;
/* Returns the (error) status of a the reference to the HTML file `file'
   (occuring after name `name') to the HTML file `file_to' with the
   (optional) name `name'. 
*/
{
    file_to->nr_refs++;

    DEBUG_P5("check_ref(%s,%s,%s,%s) %d\n", 
                 file->name, name, file_to->name, name_to, file_to->nr_refs);

    if (name_to == NULL)
    {    add_ref_by(&file_to->ref_by, file->name, ln, name,
                    find_re_href(file_to->link, file, name));
         return   file_to->exists
                ? S_CORRECT 
                : is_URL(file_to->name) ? S_U_FILE :  S_E_FILE;
    }
    else
    {   link_t **p_link = &file_to->link;
        bool found = FALSE;

        /* Find NAME record with name `name_to' in list `file_to->link': */
        while(*p_link != NULL && !found)
            if (   (*p_link)->kind == A_NAME
                && streq((*p_link)->info.name.name, name_to))
                found = TRUE;
            else
                p_link = &(*p_link)->next;

        /* Add if not found: */
        if (!found)
        {  link_t *n = ALLOC(link_t);
           DEBUG_P1("ADD `%s'\n", name_to);
           n->next = NULL;
           n->kind = A_NAME;
           n->info.name.name = SALLOC(name_to);
           strcpy(n->info.name.name, name_to);
           n->info.name.exists = FALSE;
           n->info.name.repeated = FALSE;         
           n->info.name.ref_by = NULL;
           *p_link = n;
        }

        /* Add `file' and `name' to reference list of NAME record where
           return name is looked in the remaining of the list of records.
        */
        {   ref_by_t **p_ref_by = &(*p_link)->info.name.ref_by;
            add_ref_by(p_ref_by, file->name, ln, name,
                       find_re_href(*p_link, file, name));
            if (copied)
                (*p_link)->info.name.referenced = TRUE;
        }

        return   !file_to->exists 
               ? (is_URL(file_to->name) ? S_U_FILE : S_E_FILE)
               : found ? S_CORRECT : S_E_NAME;
     }
}


void make_by_refs()
/* This procedure fills all referenced-by fields of the NAME records
   in the links of the HTML files: 
*/
{   file_t *file;

    DEBUG_P("make_by_refs\n");

    /* Scan all the files that exist: */
    for (file = the_files; file != NULL; file = file->next)
        if (file->exists)
        {   link_t *link;
            char *name = NULL; /* pointer to last found name in the link */

            DEBUG_P1("make_by_refs for `%s'\n", file->name);

            /* Scan all the records: */
            for (link = file->link; link != NULL; link = link->next) 
                if (link->kind == A_NAME)
                    name = link->info.name.name;
                else
                    link->info.ref.status 
                    = check_ref(file,
                                link->info.ref.ln,
                                name,
                                link->info.ref.file,
                                link->info.ref.name,
                                link->copied);
        }
}

void fill_re_names_ref_by(ref_by_t *ref_by)
/* scan all ref-by records */
{
    for(; ref_by != NULL; ref_by = ref_by->next)
    {   DEBUG_P3(" %s#%s %d\n", ref_by->file,
                    ref_by->name, ref_by->href != NULL);
        if (ref_by->href != NULL)
        {   link_t *l = ref_by->href;
            if (   l->info.ref.re_name == NULL
                || !eq_name(l->info.ref.name, l->info.ref.re_name))
                l->info.ref.re_name = norm_name(ref_by->name);
        }
    }
}

void fill_re_names()
/* This procedure fills all re_name fields of the HREF records
   in the links of the HTML files: 
*/
{   file_t *file;

    DEBUG_P("file_re_name\n");

    /* Scan all the files that exist: */
    for (file = the_files; file != NULL; file = file->next)
        if (file->exists)
        {   link_t *link;

            DEBUG_P1("file_re_name for `%s'\n", file->name);

            /* Scan all the records: */
            fill_re_names_ref_by(file->ref_by);
            for (link = file->link; link != NULL; link = link->next) 
                if (link->kind == A_NAME)
                    fill_re_names_ref_by(link->info.name.ref_by);
        }
}

/********** Printing cross-reference information *****************/

void print_ref_bys(fout, ref_by) FILE *fout; ref_by_t *ref_by;
/* Prints contents of `ref_by'. */
{
    for(;ref_by != NULL; ref_by = ref_by->next)
    {   fprintf(fout, "    referenced by: `%s'", ref_by->file);
        if (ref_by->name != NULL)
            fprintf(fout, " (after name: `%s')", ref_by->name);
        if (ref_by->href != NULL && ref_by->href->info.ref.name != NULL)
            fprintf(fout, " (re name: `%s')", ref_by->href->info.ref.name);

        fprintf(fout, "\n");
    }
}

void print_links(fout, link) FILE *fout; link_t *link;
/* Prints information of list of records `link' */
{
    for(;link != NULL; link = link->next)
        if (link->kind == A_NAME)
        {   fprintf(fout, "  name: `%s'",
                    link->info.name.name);
            if (!link->info.name.exists)
                fprintf(fout, "  NAME DOES NOT EXIST");
            if (link->info.name.repeated)
                fprintf(fout, "  IS REPEATED");
            fprintf(fout, "\n");
            print_ref_bys(fout, link->info.name.ref_by);
        }
        else
        {   fprintf(fout, "  ref to file: `%s'", 
                    link->info.ref.file->name);
            if (link->info.ref.name != NULL)
                fprintf(fout, " name: `%s'",
                        link->info.ref.name);
            if (link->info.ref.status == S_E_FILE)
                fprintf(fout, "  FILE DOES NOT EXIST");  
            if (link->info.ref.status == S_U_FILE)
                fprintf(fout, "  FILE IS URL");  
            if (link->info.ref.status == S_E_NAME)
                fprintf(fout, "  NAME DOES NOT EXIST");  
            fprintf(fout, "\n"); 
       }
}

void print_files(fout) FILE *fout;
/* Print all the cross-reference information: */
{
    file_t *file;

    for (file = the_files; file != NULL; file = file->next)
    {   fprintf(fout, "\nFile: %s", file->name);
        if (!file->exists)
           fprintf(fout, "   DOES NOT EXIST");
        fprintf(fout, "\n");   
        print_ref_bys(fout, file->ref_by); 
        print_links(fout, file->link);
    }
}

/********** Printing errors ***********/

void errors_info_ref_bys(FILE *fout, ref_by_t *ref_by, char *file_name)
/* Prints information about `ref_by'. */
{
    for(;ref_by != NULL; ref_by = ref_by->next)
    {   fprintf(fout, "%s (0) : referenced at %s (%d)",
                file_name, ref_by->file, ref_by->ln);
        fprintf(fout, ".\n");
    }
}

void errors_ref_bys(fout, ref_by, file_name, ln, file_exists)
FILE *fout; ref_by_t *ref_by; char *file_name; int ln; bool file_exists;
{   char *mess = file_exists ? "could add" : "should contain";

    for(;ref_by != NULL; ref_by = ref_by->next)
    {   DEBUG_P2("ref_by: %s#%s", ref_by->file, ref_by->name);
        if (ref_by->href == NULL)
                DEBUG_P("--href == NULL\n");
        else
                DEBUG_P2("-- %s %s\n", ref_by->name, 
                                   ref_by->href->info.ref.re_name); 
        if (strcmp(file_name, ref_by->file))
            if (   ref_by->href == NULL
                || !eq_name(ref_by->name, ref_by->href->info.ref.re_name))
                if (ref_by->name == NULL)
                    fprintf(fout, "%s (%d) : %s: <a href=\"%s\">.\n",
                            file_name, ln, mess,
                            rel_URL(file_name, ref_by->file));
                else
                    fprintf(fout, "%s (%d) : %s: <a href=\"%s#%s\">.\n",
                            file_name, ln, mess,
                            rel_URL(file_name, ref_by->file), ref_by->name);
     }
}

#ifdef COMMENT
            else
            {   if (ref_by->re_name == NULL)
                {   if (is_html(file_name) && option_info) 
                        fprintf(fout, 
                                "%s (0) : could add: <a href=\"%s#%s\">.\n",
                                file_name, ref_by->file, ref_by->name);
                }
                else if (!eq_name(ref_by->re_name, ref_by->name))
                {   bool warn =   ref_by->re_name == c_top
                               || memeq(ref_by->name, ref_by->re_name,
                                          strlen(ref_by->re_name));
                    if ((warn && option_warn) || option_info)
                    {   fprintf(fout, "%s (0) : %s replace <a href=\"%s",
                                file_name, warn ? "could" : "should",
                                ref_by->file);
                        if (ref_by->re_name != c_top)
                            fprintf(fout, "#%s", ref_by->re_name);
                        fprintf(fout, "\"> with <a href=\"%s#%s\">.\n",
                                ref_by->file, ref_by->name);
                    }
                }
            } 
}
#endif

void errors_links(FILE *fout, link_t *link, char *file_name, bool file_exists);
void errors_links(FILE *fout, link_t *link, char *file_name, bool file_exists)
{
    for(;link != NULL; link = link->next)
        if (link->kind == A_NAME)
        {   if (!link->info.name.exists && option_warn)
            {   fprintf(fout, "%s (0) : should contain: <a name=\"%s\">.\n",
                              file_name, link->info.name.name);
                if (option_info)
                    errors_info_ref_bys(fout, link->info.name.ref_by,
                                        file_name);
            }
            else if (link->info.name.repeated)
            {   fprintf(fout,
                        "%s (0) : repeated <a name=\"%s\">.\n",
                        file_name, link->info.name.name);
            }
            else
                errors_ref_bys(fout, link->info.name.ref_by, file_name, 0,
                               file_exists);
        }
        else if (link->info.ref.status == S_E_FILE)
        {   if (link->info.ref.file->nr_refs > 1 || option_warn)
                fprintf(fout, "%s (0) : file `%s' does not exist.\n", 
                        file_name, link->info.ref.file->name);
        }
        else if (link->info.ref.status == S_E_NAME)
        {   if (option_warn)
                fprintf(fout, "%s (0) : file `%s' requires <a name=\"%s\">.\n",
                        file_name, link->info.ref.file->name, 
                        link->info.ref.name);
        }
}

void errors_links_names(FILE *fout, link_t *link, char *file_name);
void errors_links_names(FILE *fout, link_t *link, char *file_name)
{
    for(;link != NULL; link = link->next)
        if (link->kind == A_NAME && !link->info.name.exists)
        {   fprintf(fout, "%s (0) : should contain: <a name=\"%s\">.\n",
                    file_name, link->info.name.name);
            if (option_info)
                errors_info_ref_bys(fout, link->info.name.ref_by, file_name);
        }
}


void errors_files(fout) FILE *fout;
{
    file_t *file;

    for (file = the_files; file != NULL; file = file->next)
    {   if (!file->exists && !is_URL(file->name))
            fprintf(fout, "%s (0) : does not exits.\n", file->name);

        if (is_html(file->name))
            errors_ref_bys(fout, file->ref_by, file->name, 0, file->exists);

        errors_links(fout, file->link, file->name, file->exists);
    }
}

/************ Scanning buffers **************/

/* sizes of buffers used during reading of HTML files: */
#define MAX_SF     80  /* max size of name of source HTML file name */
#define MAX_DF    600  /* max size of name of reference HTML file name */
#define MAX_N     100  /* max size of NAME's */
#define MAX_HC    100  /* max size of HTML commands */
#define MAX_AT   1000  /* max size of text inside an anchor */
#define MAX_AV    600  /* max size of attribute value */

/* Text buffer, used for big comment fragments inside comments */
char *comment = NULL;
int comment_len = 0;

void add_to_comment(char ch, int *p_i)
{
   if ((*p_i) >= comment_len)
   {   if (comment == NULL)
       {   comment = NALLOC(char,1024);
           comment_len = 1024;
       }
       else
       {   comment_len *= 2;
           comment = NREALLOC(comment, char, comment_len);
       }
       if (comment == NULL)
       {
           fprintf(stderr, "Fatal error: memory allocation failed\n");
           exit(1);
       }
   }
   comment[(*p_i)++] = ch;
}

/* buffer used for text inside anchors: */
char atext[MAX_AT + 1];
int atext_len;

/* Temporary buffer used during file name manipulations: */
char df_buffer[MAX_DF+1];

/*********** Manipulating URL's *************/

/* URL of document */
char *document_URL = NULL,
     *server_URL = NULL, /* server part of document_URL (without last '/'). */
     *file_URL = NULL;   /* file part of document_URL (starting with '/'). */

/* List of link and final mappings of referenced files to URL's */
typedef struct mapping_T
{   struct mapping_T *next;
    char *prefix;           
    char *replace;
} mapping_t;

/* List of all the mappings: */
mapping_t *link_mappings = NULL;

/* List of all the link mappings: */
mapping_t *final_mappings = NULL;

/* List of bibliographic entries: */
typedef struct biblio_T
{   struct biblio_T *next;
    int nr;                /* internal number */
    char *name;
} biblio_t;

/* List of all the bibliographic entries: */
biblio_t *biblios = NULL;
int biblio_nr = 0;         /* Number of bibliographic entries */


bool norm_URL(origin, file) char *origin, *file;
/* Normalizes the file name `file' appearing in HTML file `origin', with
   the following steps:
   1.  If `file' is empty, use assign `origin' to `file'.
       Else if `file' is not an URL and does not start with '/'
       then glue it together with directories in `origin'.
   2.  If `file' is not an URL glue it together with document URL.
   3.  If `file' starts with document URL, remove it.
   4.  If not URL and not html, add index.html, when the file exists.
   5.  Do any link mappings.
*/
{   /* assume that origin: ['/'](<dn> '/')* <fn> */

   DEBUG_P4("norm_URL(%s, %s) %s %s\n", 
                origin, file, server_URL, file_URL);
/* Step 1: */

    /* if file is empty, use origin: */
    if (file[0] == '\0')
    {   if (strlen(origin) < MAX_DF)
            strcpy(file, origin);
        else
            return FALSE;
    }
    /* if file is not an URL and does not start with '/'
       then glue it together with directories in origin:  */
    else if (file[0] != '/' && !is_URL(file))
    {   int i = strlen(origin);
        char *s = file;

        DEBUG_P2("glue %s with %s", origin, file);

        /* remove ./ from the start of file name: */
        if (s[0] == '.' && s[1] == '/')
            s += 2;
                    
        /* remove file-name from origin: */
        while (i > 0 && origin[i - 1] != '/')
            i--;
        DEBUG_P2(" : %s + %s\n", origin, file);
        /* cancel last directory in origin with '../': */
        while (   i > 1 && origin[i - 1] == '/'
               && s[0] == '.'
               && (   (s[1] == '.' && (s[2] == '/' || s[2] == '\0'))
                   || s[1] == '/' || s[1] == '\0'))
            if (s[1] == '/')
                s += 2;
            else if (s[1] == '\0')
                s++;
            else 
            {   s += s[2] == '/' ? 3 : 2;  
                do
                    i--;
                while (i > 0 && origin[i - 1] != '/');
            }

        if (   i == 1 && origin[0] == '/'
            && s[0] == '.' && s[1] == '.' /* && s[2] == '/'*/)
            return FALSE;
        else if (i == 0)
            strcpy(file, s);
        else if(i + strlen(s) < MAX_DF)
        {   memcpy(df_buffer, origin, i); 
            strcpy(df_buffer + i, s);
            strcpy(file, df_buffer);
        }
        else
            return FALSE;
    }

    DEBUG_P1("After step 1: %s\n", file);

/* Step 2. */

    if (   document_URL != NULL
        && file[0] == '.' && file[1] == '.' && file[2] == '/') 
    {   int i = strlen(file_URL) - 1;
        char *s = file;

        DEBUG_P2("glue %s + %s\n", file_URL, file);
        /* assume that file_URL is of the form: '/' (<dn> '/')*  */
        while (i > 0 && s[0] == '.' && s[1] == '.' && s[2] == '/')
        {   s += 3;  
            i--;
            while (i > 0 && file_URL[i] != '/') 
               i--;
            DEBUG_P2("replace %s with %s\n", s, file_URL + i);
        }
        i += strlen(server_URL);
        if (i + 1 + strlen(s) < MAX_DF)
        {   memcpy(df_buffer, document_URL, i + 1); 
            strcpy(df_buffer + i + 1, s);
            strcpy(file, df_buffer);
        }
        else
            return FALSE;
    }
    /* if file starts with '/' add server_URL: */
    else if (document_URL != NULL && file[0] == '/') 
        if (strlen(file) + strlen(server_URL) < MAX_DF)
        {   strcpy(df_buffer, server_URL);
            strcat(df_buffer, file);
            strcpy(file, df_buffer);
        }
        else 
            return FALSE;

    DEBUG_P1("After step 2: %s\n", file);

/* Step 3: */

    /* if URL starts with document URL, remove it: */
    if (   document_URL != NULL
        && memeq(file, document_URL, strlen(document_URL)))
        strcpy(file, file + strlen(document_URL));

    DEBUG_P1("After step 3: %s\n", file);

/* Step 4: */

    if (streq(file, "."))
        file[0] = '\0';

    /* if not URL and not .html, add index.html, when file exists */
    if (!is_URL(file) && !is_html(file) && strlen(file) + 12 < MAX_DF)
    {   strcpy(df_buffer, file);
        if (df_buffer[0] != '\0' && df_buffer[strlen(df_buffer)-1] != '/')
            strcat(df_buffer, "/");
        strcat(df_buffer, "index.html");
        DEBUG_P1("Try: %s\n", df_buffer);
        if (access(df_buffer, R_OK) == 0)
            strcpy(file, df_buffer);
    }

    if (!is_URL(file) && strstr(file, ".html?") != 0)
        strstr(file, ".html?")[5] = '\0';

    DEBUG_P1("After step 4: %s\n", file);

/* Step 5: */

    {   mapping_t *map = link_mappings;

        /* check if there is a mapping for this file: */
        while (   map != NULL 
               && memcmp(map->prefix, file, strlen(map->prefix)))
            map = map->next;

        /* if there is a mapping: */
        if (map != NULL && memeq(map->prefix, file, strlen(map->prefix))
            &&   strlen(file) - strlen(map->prefix) + strlen(map->replace)
               < MAX_DF)
        {   strcpy(df_buffer, map->replace);
            strcat(df_buffer, file + strlen(map->prefix));
            strcpy(file, df_buffer);
        }
    }

    DEBUG_P1("After step 5: %s\n", file);

    return TRUE;
}

char *rel_URL(char *from, char *to)
/* This function returns the shortest string to go file "to" inside
   file "from" */
{  char *to2 = to;
   bool go;
   int d;

   DEBUG_P2("rel_URL(%s, %s)\n", from, to);

   go = TRUE;
   while (go)
   {   char *f = from,
            *t = to;

       for (; *f != '\0' && *f != '/' && *f == *t; f++, t++);
       if (*f == '/' && *t == '/')
       {   from = f + 1;
           to = t + 1;
       }
       else
           go = FALSE;
   }

   d = 0;
   for (; *from != '\0'; from++)
       if (*from == '/')
           d++;

   df_buffer[0] = '\0';
   for (; d > 0; d--)
       if (strlen(df_buffer) + 3 >= MAX_DF)
           return to;
       else
           strcat(df_buffer, "../");
   if (strlen(df_buffer) + strlen(to) >= MAX_DF)
       return to;
   else
       strcat(df_buffer, to);

   DEBUG_P1("relative: %s\n", df_buffer);
   if (file_URL != NULL && strlen(file_URL) + strlen(to2) < strlen(df_buffer))
   {    strcpy(df_buffer, file_URL);
        strcat(df_buffer, to2);
   }
   if (streq(df_buffer, "index.html"))
       return ".";
   {   int l = strlen(df_buffer);

       if (l > 11 && streq(df_buffer + l - 11, "/index.html"))
           df_buffer[l - 11] = '\0';
   }
   DEBUG_P1("return:   %s\n", df_buffer);
   return df_buffer;
}

/******* Translating special characters to LaTeX characters ******/

#define NR_CH_TABLE 173
#define NR_CH_M     159

struct {
  int nr;
  char *html_ch;
  char *tex_ch;
  char ch;
} ch_table[NR_CH_TABLE] =
{ // code assumes that table start with 160 to 255
  {  160, "nbsp",   "\\* ",     0   },
  {  161, "iexcl",  "!`",       0   },
  {  162, "cent",   NULL,       0   },  /* "$\\cents" */
  {  163, "pound",  "\\pounds", 0   },
  {  164, "curren", NULL,       0   },  
  {  165, "yen",    NULL,       0   },  /* Yen */
  {  166, "brvbar", "{\\fontencoding{U}\\fontfamily{wasy}\\selectfont\\char124}", 0   },
  {  167, "sect",   "{\\S}",    0   },
  {  168, "uml",    "\\texttt{{}\"{}}", 0   },
  {  169, "copy",   "\\copyright{}", 'c' },
  {  170, "ordf",   NULL,       0   },
  {  171, "laquo",  "$\\ll",    0   },
  {  172, "not",    "$\\neg",   0   },
  {  173, "shy",    "\\-",      0   },
  {  174, "reg",    "{{\\ooalign{\\hfil\\raise.07ex\\hbox{R}\\hfil\\crcr\\mathhexbox20D}}}", 0   },
  {  175, "macr",   NULL,       0   },  /* "\\B " */
  {  176, "deg",    "${}^\\circ", 0   },
  {  177, "plusmn", "$\\pm",    0   },
  {  178, "sup2",   "${}^2",    0   },
  {  179, "sup3",   "${}^3",    0   },
  {  180, "acute",  "\\'{}",    0   },
  {  181, "micro",  "$\\mu",    0   },
  {  182, "para",   "{\\P}",    0   }, 
  {  183, "middot", NULL,       0   },    /* "\\D " */
  {  184, "cedil",  "\\c{}",    0   },
  {  185, "sup1",   "${}^1",    0   },
  {  186, "ordm",   NULL,       0   },      /* ^\underbar{o} */
  {  187, "raquo",  "$\\gg",    0   },
  {  188, "frac14", "$\\frac14", 0  },
  {  189, "frac12", "$\\frac12", 0  },
  {  190, "frac34", "$\\frac34", 0  },
  {  191, "iquest", "?`",       0   },
  {  192, "Agrave", "\\`A",     'A' },
  {  193, "Aacute", "\\'A",     'A' },
  {  194, "Acirc",  "\\^A" ,    'A' },
  {  195, "Atilde", "\\~A",     'A' },
  {  196, "Auml",   "\\\"A",    'A' },
  {  197, "Aring",  "{\\AA}",   'A' },
  {  198, "AElig",  "{\\AE}",   'A' },
  {  199, "Ccedil", "\\c C",    'C' },
  {  200, "Egrave", "\\`E",     'E' },
  {  201, "Eacute", "\\'E",     'E' },
  {  202, "Ecirc",  "\\^E",     'E' },
  {  203, "Euml",   "\\\"E",    'E' },
  {  204, "Igrave", "\\`I",     'I' },
  {  205, "Iacute", "\\'I",     'I' },
  {  206, "Icirc",  "\\^I",     'I' },
  {  207, "Iuml",   "\\\"I",    'I' },
  {  208, "ETH",    NULL,       'D' },   /* -D */
  {  209, "Ntilde", "\\~N",     'N' },
  {  210, "Ograve", "\\`O",     'O' },
  {  211, "Oacute", "\\'O",     'O' },
  {  212, "Ocirc",  "\\^O",     'O' },
  {  213, "Otilde", "\\~O",     'O' },
  {  214, "Ouml",   "\\\"O",    'O' },
  {  215, "times",  "$\\times", 'x' },
  {  216, "Oslash", "{\\O}",    'O' },
  {  217, "Ugrave", "\\`U",     'U' },
  {  218, "Uacute", "\\'U",     'U' },
  {  219, "Ucirc",  "\\^U",     'U' },
  {  220, "Uuml",   "\\\"U",    'U' },
  {  221, "Yacute", "\\'Y",     'Y' },
  {  222, "THORN",  "P",        'P' },   /* P thorn */
  {  223, "szlig",  "{\\ss}",   's' },
  {  224, "agrave", "\\`a",     'a' },
  {  225, "aacute", "\\'a",     'a' },
  {  226, "acirc",  "\\^a",     'a' },
  {  227, "atilde", "\\~a",     'a' },
  {  228, "auml",   "\\\"a",    'a' },
  {  229, "aring",  "{\\aa}",   'a' },
  {  230, "aelig",  "{\\ae}",   'a' },
  {  231, "ccedil", "\\c c",    'c' },
  {  232, "egrave", "\\`e",     'e' },
  {  233, "eacute", "\\'e",     'e' },
  {  234, "ecirc",  "\\^e",     'e' },
  {  235, "euml",   "\\\"e",    'e' },
  {  236, "igrave", "\\`{\\i}", 'i' },
  {  237, "iacute", "\\'{\\i}", 'i' },
  {  238, "icirc",  "\\^{\\i}", 'i' },
  {  239, "iuml",   "\\\"{\\i}", 'i' },
  {  240, "eth",    "\\v o",    'e' },
  {  241, "ntilde", "\\~n",     'n' },
  {  242, "ograve", "\\`o",     'o' },
  {  243, "oacute", "\\'o",     'o' },
  {  244, "ocirc",  "\\^o",     'o' },
  {  245, "otilde", "\\~o",     'o' },
  {  246, "ouml",   "\\\"o",    'o' },
  {  247, "divide", "$\\div",   0   },
  {  248, "oslash", "{\\o}",    'o' },
  {  249, "ugrave", "\\`u",     'u' },
  {  250, "uacute", "\\'u",     'u' },
  {  251, "ucirc",  "\\^u",     'u' },
  {  252, "uuml",   "\\\"u",    'u' },
  {  253, "yacute", "\\'y",     'y' },
  {  254, "thorn",  "p",        'p' },  /* p thorn */
  {  255, "yuml", "\\'y",       'y' },

  {   34, "quot",   "\\\"{}",   '"' },
  {   38, "amp",    "\\&",      '&' },
  {   60, "lt",     "$<",       '<' },
  {   62, "gt",     "$>",       '>' },

  {  338, "OElig",  NULL,       0   },
  {  339, "oelig",  NULL,       0   },
  {  352, "Scaron", NULL,       0   },
  {  353, "scaron", NULL,       0   },
  {  376, "Yuml",   "\\\"Y",    'Y' },

  {  710, "circ",   "\\^{}",    '^' },
  {  732, "tilde",  "\\~{}",    '~' },

  {  913, "Alpha",  "A",        'A' },
  {  914, "Beta",   "B",        'B' },
  {  915, "Gamma",  "$\\Gamma", 0   },
  {  916, "Delta",  "$\\Delta", 0   },
  {  917, "Epsilon","E",        'E' },
  {  918, "Zeta",   "Z",        'Z' },
  {  919, "Eta",    "H",        'H' },
  {  920, "Theta",  "$\\Theta", 0   },
  {  921, "Iota",   "I",        'I' },
  {  922, "Kappa",  "K",        'K' },
  {  923, "Lambda", "$\\Lambda",0   },
  {  924, "Mu",     "M",        'M' },
  {  925, "Nu",     "N",        'N' },
  {  926, "Xi",     "$\\Xi",    0   },
  {  927, "Omicron", "$\\Omicron",'O' },
  {  928, "Pi",     "$\\Pi",    0   },
  {  929, "Rho",    "R",        'R' },
  {  931, "Sigma",  "$\\Sigma", 0   },
  {  932, "Tau",    "T",        'T' },
  {  933, "Upsilon", "$\\Upsilon",0   },
  {  934, "Phi",    "$\\Phi",   0   },
  {  935, "Chi",    "X",        'X' },
  {  936, "Psi",    "$\\Psi",   0   },
  {  937, "Omega",  "$\\Omega", 'O'   },

  {  945, "alpha",  "$\\alpha", 0   },
  {  946, "beta",   "$\\beta",  0   },
  {  947, "gamma",  "$\\gamma", 0   },
  {  948, "delta",  "$\\delta", 0   },
  {  949, "epsilon","$\\epsilon",0   },
  {  950, "zeta",   "$\\zeta",  0   },
  {  951, "eta",    "$\\eta",   0   },
  {  952, "theta",  "$\\theta", 0   },
  {   -1, "thetav", "$\\vartheta",0   },
  {  953, "iota",   "$\\iota",  0   },
  {  954, "kappa",  "$\\kappa", 0   },
  {  955, "lambda", "$\\lambda",0   },
  {  956, "mu",     "$\\mu",    0   },
  {  957, "nu",     "$\\nu",    0   },
  {  958, "xi",     "$\\xi",    0   },
  {  959, "omicron","o",        0   },
  {  960, "pi",     "$\\pi",    0   },
  {  961, "rho",    "$\\rho",   0   },
  {  962, "sigmaf", "$\\sigma", 0   },
  {  963, "sigma",  "$\\sigma", 0   },
  {  964, "tau",    "$\\tau",   0   },
  {  965, "upsi",   "$\\upsilon",0   },
  {  966, "phi",    "$\\phi",   0   },
  {  967, "chi",    "$\\chi",   0   },
  {  968, "psi",    "$\\psi",   0   },
  {  969, "omega",  "$\\omega", 0   },

  { 8194, "ensp",   "\\enskip{}",' ' },
  { 8195, "emsp",   "\\quad{}", ' ' },
  { 8201, "thinsp", "",         ' ' },
  { 8204, "zwnj",   "",         0 },
  { 8205, "zwj",    "",         0 },
  { 8211, "ndash",  "--",       '-' },
  { 8212, "mdash",  "---",      '-' },
  { 8220, "ldquo",  "``",       '"' },
  { 8221, "rdquo",  "''",       '"' },
  { 8364, "euro",   "{\\fontencoding{U}\\fontfamily{mvs}\\selectfont\\char164}",  0 },
  { 8482, "trade",  "\\texttrademark{}", 0   },
  { 8730, "radic",  "",         0 },
  { 8800, "ne",     "",         0 },
  { 8801, "equiv",  "",         '=' },
  { 8804, "le",     "",         0 },
  { 8805, "ge",     "",         0 },
};



/********* Generating TeX output procedures **********/

void print_str(FILE *fout, char *str, FILE *freport, char *html_fn, int ln,
               bool in_math, bool in_verb, bool in_alltt);
void print_str(FILE *fout, char *str, FILE *freport, char *html_fn, int ln,
               bool in_math, bool in_verb, bool in_alltt)
{  
    DEBUG_P1("print_str(, %s)\n", str);

    for(; *str; str++)
    {   bool special = FALSE;
        int v = 0;
        char ch = '\0';
        char html_ch[10];
        html_ch[0] = '\0';

#ifndef ASCII8
        if ((unsigned char)*str >= 160 && (unsigned char)*str <= 255)
        {   special = TRUE;
            v = (unsigned char)*str - 160;
            ch = ch_table[v].ch;
        }
        else
#endif 
        if (*str == '&')
        {   int i = 0;
            bool correct = FALSE;

            if (isalpha(str[1]))
            {   for (i = 0; i < 9; i++)
                    if (isalnum(str[i+1]))
                        html_ch[i] = str[i+1];
                    else
                        break;
                html_ch[i] = '\0';
                for (v = 0; v < NR_CH_TABLE; v++)
                    if (   ch_table[v].html_ch != NULL
                        && !strcmp(html_ch, ch_table[v].html_ch))
                    {   special = TRUE;
                        correct = TRUE;
                        ch = ch_table[v].ch;
                        break;
                    }
            }
            else if (str[1] == '#')
            {   int code = 0;
                html_ch[0] = '#';
                for (i = 1; i < 9; i++)
                    if (isdigit(str[i+1]))
                    {   html_ch[i] = str[i+1];
                        code = code * 10 + str[i+1] - '0';
                    }
                    else
                        break;
                if ((code >= ' ' && code < 127) || code == 8)
                {   correct = TRUE;
                    ch = code;
                }
                else if (code >= 160)
                {
                    for (v = 0; v < NR_CH_TABLE; v++)
                        if (ch_table[v].html_ch != NULL && ch_table[v].nr == code)
                        {   special = TRUE;
                            correct = TRUE;
                            ch = ch_table[v].ch;
                            break;
                        }
                }
            }
            html_ch[i] = '\0';

            if (correct)
            {   str += i;
                if (str[1] == ';')
                    str++;
            }
            else 
            {   if (freport != NULL && option_warn)
                    if (html_ch[0] == '\0')
                        fprintf(freport,
                                "%s (%d) : Replace `&' by `&amp;'.\n",
                                html_fn, ln);
                    else
                        fprintf(freport,
                                "%s (%d) : Unknown sequence `&%s;'.\n",
                                html_fn, ln, html_ch);
                ch = *str;
            }
        }
        else if (((unsigned char)*str >= ' ' && (unsigned char)*str <= HIGHASCII) || *str == '\t')
            ch = *str;
        else if (option_warn && freport != NULL)
            fprintf(freport,
                    "%s (%d) : Unknown character %d (decimal)\n",
                    html_fn, ln, (unsigned char)*str);
        if (fout)
        {   if (in_verb)
            {   fputc(ch != '\0' ? ch : ' ', fout);
                if (   special && freport != NULL && option_warn
                    && v < NR_CH_M)
                {   fprintf(freport, "%s (%d) : ", html_fn, ln);
                    if (html_ch[0] == '\0')
                        fprintf(freport, "character %d (decimal)", 
                                (unsigned char) *str);
                    else
                        fprintf(freport, "sequence `&%s;'", html_ch);
                    fprintf(freport, " rendered as `%c' in verbatim\n",
                            ch != '\0' ? ch : ' ');
                }
            }
            else if (in_alltt)
            {   if (special)
                {   char *o = ch_table[v].tex_ch;
                    if (o != NULL)
                        if (*o == '$')
                            fprintf(fout, "\\(%s\\)", o + 1);
                        else
                            fprintf(fout, "%s", o);
                }
                else if (ch == '{' || ch == '}')
                    fprintf(fout, "\\%c", ch);
                else if (ch == '\\')
                    fprintf(fout, "\\(\\backslash\\)");
                else if (ch != '\0')
                    fputc(ch, fout);
            }
            else if (special)
            {   char *o = ch_table[v].tex_ch;
                if (o == NULL)
                {   if (freport != NULL && option_warn)
                    {   fprintf(freport,
                                "%s (%d) : no LaTeX representation for ",
                                html_fn, ln);
                        if (html_ch[0] == '\0')
                            fprintf(freport, "character %d (decimal)\n", 
                                    (unsigned char) *str);
                        else
                            fprintf(freport, "sequence `&%s;'\n", html_ch);
                    }
                }
                else if (*o == '$')
                    if (in_math)
                        fprintf(fout, "%s", o+1);
                    else
                        fprintf(fout, "\\mbox{%s$}", o);
                else
                    fputs(o, fout);
            }
            else if (in_math)
            {   if (ch == '#' || ch == '%')
                    fprintf(fout, "\\%c", ch);
                else
                    fputc(ch, fout);
            }
            else
            {   switch(ch)
                {   case '\0' : break;
                    case '\t': fputs("        ", fout); break;
                    case '_': case '{': case '}':
                    case '#': case '$': case '%':
                               fprintf(fout, "\\%c", ch); break;
                    case '@' : fputs("{\\char64}", fout); break;
                    case '[' :
                    case ']' : fprintf(fout, "\\mbox{$%c$}", ch); break;
                    case '"' : fputs("\\texttt{{}\"{}}", fout); break;
                    case '~' : fputs("\\~{}", fout); break;
                    case '^' : fputs("\\^{}", fout); break;
                    case '|' : fputs("\\mbox{$|$}", fout); break;
                    case '\\': fputs("\\mbox{$\\backslash$}", fout); break;
                    case '&' : fputs("\\&", fout); break;
                    case '`' : fputs("\\char18", fout); break;
                    default: fputc(ch, fout); break;
                }
            }
        }
    }
}

bool in_header;
int  in_math;
int  in_verb;
int  in_alltt;


void print_str_(FILE *fout, char *str);
void print_str_(FILE *fout, char *str)
{

    for(; *str; str++)
    {   int v;
        char ch = '\0';
        char html_ch[10];
        html_ch[0] = '\0';

#if !defined(ASCII8)
        if ((unsigned char)*str >= 160 && (unsigned char)*str <= 255)
            ch = ch_table[(unsigned char)*str - 160].ch;
        else
#endif
        if (*str == '&')
        {   int i = 0;
            bool correct = FALSE;

            if (isalpha(str[1]))
            {   for (i = 0; i < 9; i++)
                    if (isalpha(str[i+1]))
                        html_ch[i] = str[i+1];
                    else
                        break;
                html_ch[i] = '\0';
                for (v = 0; v < NR_CH_TABLE; v++)
                    if (   ch_table[v].html_ch != NULL
                        && !strcmp(html_ch, ch_table[v].html_ch))
                    {   correct = TRUE;
                        ch = ch_table[v].ch;
                        break;
                    }
            }
            else if (str[1] == '#')
            {   int code = 0;
                html_ch[0] = '#';
                for (i = 1; i < 9; i++)
                    if (isdigit(str[i+1]))
                    {   html_ch[i] = str[i+1];
                        code = code * 10 + str[i+1] - '0';
                    }
                    else
                        break;
                if (code >= ' ' && code < 127)
                {   correct = TRUE;
                    ch = code;
                }
                else if (code >= 160 && code <= 255)
                {   correct = TRUE;
                    v = code - 160;
                    ch = ch_table[v].ch;
                }
            }
            html_ch[i] = '\0';

            if (correct)
            {   str += i;
                if (str[1] == ';')
                    str++;
            }
            else 
                ch = *str;
        }
        else if ((unsigned char)*str >= ' ' && (unsigned char)*str <= HIGHASCII)
            ch = *str;
        if (fout)
            if (   ch == '#' || ch == '[' || ch == ']'
                || ch == '-' || ch == '\\' || ch == '\'' || ch == ','
                || ch == '`' || ch == '<' || ch == '='
                || ch == '{' || ch == '}' || ch == '%' || ch == '&'
                || ch == '~' || ch == '\0') {
                fprintf(fout, "_%2d", (int)ch);
            }
            else
                fputc(ch, fout);
    }
}

void print_f(FILE *fout, char *str, char codes[], char *strs[]);
void print_f(FILE *fout, char *str, char codes[], char *strs[])
{
    DEBUG_P2("print_f(, %s, %s, );\n", str, codes);
    {   int i;
        for (i = 0; codes[i] != '\0'; i++)
             DEBUG_P2(" %c : %s\n", codes[i], strs[i]);
    }
    for(; *str; str++)
        if (*str != '%')
            fputc(*str, fout);
        else if (*(str+1) == '%')
        {   fputc('%', fout);
            str++;
        }
        else
        {   int i;
            DEBUG_P1("   found %c\n", *(str+1));
            for (i = 0; codes[i] != '\0'; i++)
                if (*(str+1) == codes[i])
                    break;
            if (codes[i] == '\0')
                fputc('%', fout);
            else if (codes[i] == 'a')
            {
              print_str(fout, strs[i], NULL, "", 0,in_math, in_verb, in_alltt); 
              str++;
            }
            else
            {   print_str_(fout, strs[i]);
                str++;
            }
        }
}

/* Generation state values */

#define URL_not     0
#define URL_ftp     1
#define URL_mailto  2
#define URL_news    3
#define URL_other   4

int kind_of_URL;
char *email,
     *newsgroup,
     *ftp_site,
     *ftp_dir,
     *ftp_file;

char *c_protect   = "\\protect",
     *c_footnote  = "\\footnote",
     *c_footmark  = "\\footnotemark",
     *c_foottext  = "\\footnotetext";

#define MAX_LATEX_FMT  100
char latex_fmt[MAX_LATEX_FMT+1];

void deter_kind_of_URL(char *URL);
void deter_kind_of_URL(char *URL)
{  
    DEBUG_P1("deter_kind_of_URL(%s)\n", URL);

    kind_of_URL = URL_not;
    if (strneq(URL, "mailto:", 7))
    {   email = URL + 7;
        kind_of_URL = URL_mailto;
        DEBUG_P1("mailto: %s\n", email);
    }
    else if (strneq(URL, "news:", 5))
    {   newsgroup = URL + 5;
        kind_of_URL = URL_news;
        DEBUG_P1("news: %s\n", newsgroup);
    }
    else if(strneq(URL, "ftp://", 6) && strlen(URL) <= MAX_DF)
    {   char *s, *l;
        strcpy(df_buffer, URL);
        s = df_buffer + 6;
        ftp_site = s;
        while (*s != '/' && *s != '\0')
            s++;
        if (*s == '\0' || s == ftp_site)
            kind_of_URL = URL_other; /* found no slash or no site */
        /* terminate ftp_site: */
        *s = '\0';
        DEBUG_P1("|%s|\n", ftp_site);
        s++;
        ftp_dir = s;
        l = ftp_dir;
        for (; *s != '\0'; s++)
            if (*s == '/')
                l = s;
        if (l == ftp_dir)
        {   /* found no other slash; no directory: */
            ftp_dir = "";
            ftp_file = l;
        }
        else 
        {   ftp_file = l + 1;
            /* terminate ftp_dir */
            *l = '\0';
        }
        kind_of_URL = URL_ftp;
        DEBUG_P3("ftp: %s|%s|%s|\n", ftp_site, ftp_dir, ftp_file);
    }
    else if (is_URL(URL))
        kind_of_URL = URL_other;
}

void print_label(FILE *fout, int file_nr, char *name, bool fragil_env);
void print_label(FILE *fout, int file_nr, char *name, bool fragil_env)
{   char *strs[3];
    char filenr[10];

    DEBUG_P3("print_label(, %d, %s, %d)\n", 
                file_nr, name, fragil_env);
    sprintf(filenr, opt_filenr, file_nr);
    strs[0] = filenr;
    strs[1] = fragil_env ? c_protect : "";
    if (name[0] == '\0')
        print_f(fout, opt_label, "fp", strs);
    else
    {   strs[2] = name;
        print_f(fout, opt_label_n, "fpn", strs);
    }
}

#define FOOTNOTE_KIND_NORMAL  0
#define FOOTNOTE_KIND_MARK    1
#define FOOTNOTE_KIND_TEXT    2


void print_ex_ref(FILE *fout, char *file, char *name, bool fragil_env,
                  int f_kind);
void print_ex_ref(FILE *fout, char *file, char *name, bool fragil_env,
                  int f_kind)
{   
    if (option_bibliography)
    {   biblio_t **ref = &biblios;
        char *strs[4],
             citenr[10];

        if (f_kind == FOOTNOTE_KIND_TEXT)
            return;

        /* find entry in bibliography: */
        while (*ref != NULL && strcmp((*ref)->name, file) < 0)
            ref = &(*ref)->next;

        /* entry does not exist yet: */
        if (*ref == NULL || strcmp((*ref)->name, file))
        {   biblio_t *new = ALLOC(biblio_t);
            new->next = *ref;
            *ref = new;
            new->nr = biblio_nr++;
            new->name = SALLOC(file);
            strcpy(new->name, file);
        }

        sprintf(citenr, opt_citenr, (*ref)->nr);
        strs[0] = citenr;
        strs[1] = fragil_env ? c_protect : "";
        if (  in_header
            ? opt_href_in_header != OPT_FN
            : in_alltt
            ? opt_href_in_alltt != OPT_FN
            : opt_href != OPT_FN)
        {   if (f_kind == FOOTNOTE_KIND_TEXT)
                /* ignore */;
            else if (name[0] == '\0')
                print_f(fout, opt_cite, "cp", strs);
            else
            {   strs[2] = name;
                print_f(fout, opt_cite_n, "cpn", strs);
            }
        }
        else if (f_kind == FOOTNOTE_KIND_MARK)
            fputs(c_footmark, fout);
        else
        {   strs[2] =   f_kind == FOOTNOTE_KIND_TEXT
                      ? c_foottext : c_footnote;
            if (name[0] == '\0')
                print_f(fout, opt_f_cite, "cpF", strs);
            else
            {   strs[3] = name;
                print_f(fout, opt_f_cite_n, "cpFn", strs);
            }
        }
    }
    else if (f_kind == FOOTNOTE_KIND_MARK)
        fputs(c_footmark, fout);
    else
    {   char *strs[5];
        strs[0] = fragil_env ? c_protect : "";
        strs[1] = f_kind == FOOTNOTE_KIND_TEXT ? c_foottext : c_footnote;
        if (name[0] == '\0')
            deter_kind_of_URL(file);
        else
            kind_of_URL = URL_other;
        switch (kind_of_URL)
        {   case URL_mailto:
                strs[2] = email;
                print_f(fout, opt_f_mailto, "pFm", strs);
                break;
            case URL_news:
                strs[2] = newsgroup;
                print_f(fout, opt_f_news, "pFn", strs);
                break;
            case URL_ftp:
                strs[2] = ftp_site;
                if (ftp_dir[0] == '\0')
                    if (ftp_file[0] == '\0')
                        print_f(fout, opt_f_ftp, "pFs", strs);
                    else
                    {   strs[3] = ftp_file;
                        print_f(fout, opt_f_ftp_f, "pFsf", strs);
                    }
                else
                {   strs[3] = ftp_dir;
                    if (ftp_file[0] == '\0')
                        print_f(fout, opt_f_ftp, "pFsd", strs);
                    else
                    {   strs[4] = ftp_file;
                        print_f(fout, opt_f_ftp_f, "pFsdf", strs);
                    }
                }
                break;
            case URL_other:
                strs[2] = file;
                if (name[0] == '\0')
                    print_f(fout, opt_f_URL, "pFU", strs);
                else
                {   strs[3] = name;
                    print_f(fout, opt_f_URL_n, "pFUn", strs);
                }
                break;
        }

    }
}

void print_reference(FILE *fout, char *file, char *name, int href_status, 
                     bool fragil_envr, int f_kind);
void print_reference(FILE *fout, char *file, char *name, int href_status, 
                     bool fragil_env, int f_kind)
{   file_t *tfile = find_file(file);

    /* said to be ignored: */
    if (tfile->ignore)
        /* ignore */;

    /* URL: */
    else if (is_URL(file))
        print_ex_ref(fout, file, name, fragil_env, f_kind);

    /* reference to a name that is not included: */
    else if (href_status == REF_NAME_NOT_INC)
        /* ignore */;

    /* no .html or not included .html file: */
    else if (!is_html(file) || href_status == REF_FILE_NOT_INC)
    {   mapping_t *map = final_mappings;

        /* check if there is a mapping for this file: */
        while (   map != NULL 
               && memcmp(map->prefix, file, strlen(map->prefix)))
            map = map->next;

        /* if there is a mapping: */
        if (map != NULL && memeq(map->prefix, file, strlen(map->prefix))
            &&   strlen(file) - strlen(map->prefix) + strlen(map->replace)
               < MAX_DF)
        {   strcpy(df_buffer, map->replace);
            strcat(df_buffer, file + strlen(map->prefix));
            print_ex_ref(fout, df_buffer, name, fragil_env, f_kind);
        }
        /* otherwise add document_URL, if given and possible: */
        else if (   document_URL != NULL
                 && strlen(document_URL) + strlen(file) < MAX_DF) 
        {   strcpy(df_buffer, document_URL);
            strcat(df_buffer, file);
            print_ex_ref(fout, df_buffer, name, fragil_env, f_kind);
        }
        else
            print_ex_ref(fout, file, name, fragil_env, f_kind);
    }

    /* correct .html file: */
    else if (href_status == 0)
    {   char *strs[5];
        char filenr[10];
        sprintf(filenr, opt_filenr, find_file(file)->nr);
        strs[0] = filenr;
        strs[1] = atext;
        strs[2] = fragil_env ? c_protect : "";

        if (  in_header
            ? opt_href_in_header == OPT_NORMAL
            : in_alltt
            ? opt_href_in_alltt == OPT_NORMAL
            : opt_href == OPT_NORMAL)
        {   if (f_kind == FOOTNOTE_KIND_TEXT)
                /* ignore */;
            else if (name[0] == '\0')
                print_f(fout, latex_fmt[0] != '\0' ? latex_fmt : opt_cf, 
                        "fap", strs);
            else
            {   strs[3] = name;
                print_f(fout, latex_fmt[0] != '\0' ? latex_fmt : opt_cf_n, 
                        "fapn", strs);
            }
        }
        else if (f_kind == FOOTNOTE_KIND_MARK)
            fputs(c_footmark, fout);
        else
        {   strs[3] =   f_kind == FOOTNOTE_KIND_NORMAL
                      ? c_footnote : c_foottext;
            if (name[0] == '\0')
                print_f(fout, latex_fmt[0] != '\0' ? latex_fmt : opt_f_cf, 
                        "fapF", strs);
            else
            {   strs[4] = name;
                print_f(fout, latex_fmt[0] != '\0' ? latex_fmt : opt_f_cf_n, 
                        "fapFn", strs);
            }
        }
    }
}

void print_f_href(FILE *fout, char *file, char *name, int href_status,
                  bool fragil_env);
void print_f_href(FILE *fout, char *file, char *name, int href_status,
                  bool fragil_env)
{   char *str = opt_t_href;

    for(; *str; str++)
        if (*str != '%')
            fputc(*str, fout);
        else if (*(str+1) == '%')
        {   fputc('%', fout);
            str++;
        }
        else if (*(str+1) == 'p')
        {   if (fragil_env)
                fputs(c_protect, fout);
            str++;
        }
        else
        {   int kind = FOOTNOTE_KIND_NORMAL;
            bool fe = fragil_env;
            char *s;
            for (s = str + 1; *s == 'f' || *s == 'm' || *s == 't'; s++)
                 if (*s == 'f')
                     fe = TRUE;
                 else if (*s == 'm')
                     kind = FOOTNOTE_KIND_MARK;
                 else if (*s == 't')
                     kind = FOOTNOTE_KIND_TEXT;
            if (*s == 'R')
            {   print_reference(fout, file, name, href_status, fe, kind);
                str = s;
            }
        }
    /* forget latex-fmt here */
    latex_fmt[0] = '\0';
}

void print_f_img(FILE *fout, char *file, char *filename, char *txt,
                 int href_status, bool fragil_env, 
                 FILE *freport, char *html_fn, int ln);
void print_f_img(FILE *fout, char *file, char *filename, char *txt,
                 int href_status, bool fragil_env, 
                 FILE *freport, char *html_fn, int ln)
{   char *str = txt[0] == '\0' ? opt_t_img : opt_t_img_r;

    DEBUG_P1("print_f_img(  %s  );\n", file);
    for(; *str; str++)
        if (*str != '%')
            fputc(*str, fout);
        else if (*(str+1) == '%')
        {   fputc('%', fout);
            str++;
        }
        else if (*(str+1) == 'p')
        {   if (fragil_env)
                fputs(c_protect, fout);
            str++;
        }
        else if (*(str+1) == 'r')
        {   print_str(fout, txt, freport, html_fn, ln, FALSE, FALSE, FALSE);
            str++;
        }
        else if (*(str+1) == 'n')
        {   print_str_(fout, filename);
            str++;
        }
        else
        {   int kind = FOOTNOTE_KIND_NORMAL;
            char *s;
            for (s = str + 1; *s == 'f' || *s == 'm' || *s == 't'; s++)
                 if (*s == 'f')
                     fragil_env = TRUE;
                 else if (*s == 'm')
                     kind = FOOTNOTE_KIND_MARK;
                 else if (*s == 't')
                     kind = FOOTNOTE_KIND_TEXT;
            if (*s == 'R')
            {   print_reference(fout, file, "", href_status, fragil_env,
                                kind);
                str = s;
            }
        }
    /* forget latex-fmt here */
    latex_fmt[0] = '\0';
}

void print_bibliography(fout) FILE *fout;
{  biblio_t *bib;

   fprintf(fout, "%%html (bibliography)\n");

   for (bib = biblios; bib != NULL; bib = bib->next)
   {    char *strs[4];
        fprintf(fout, "\\bibitem{b%d} ", bib->nr);
        deter_kind_of_URL(bib->name);
        switch (kind_of_URL)
        {   case URL_mailto:
                strs[0] = email;
                print_f(fout, opt_b_mailto, "m", strs);
                break;
            case URL_news:
                strs[0] = newsgroup;
                print_f(fout, opt_b_news, "n", strs);
                break;
            case URL_ftp:
                strs[0] = ftp_site;
                if (ftp_dir[0] == '\0')
                    if (ftp_file[0] == '\0')
                        print_f(fout, opt_b_ftp, "s", strs);
                    else
                    {   strs[1] = ftp_file;
                        print_f(fout, opt_b_ftp_f, "sf", strs);
                    }
                else
                {   strs[1] = ftp_dir;
                    if (ftp_file[0] == '\0')
                        print_f(fout, opt_b_ftp, "sd", strs);
                    else
                    {   strs[2] = ftp_file;
                        print_f(fout, opt_b_ftp_f, "sdf", strs);
                    }
                }
                break;
            case URL_other:
                strs[0] = bib->name;
                print_f(fout, opt_b_URL, "U", strs);
                break;
        }
        fprintf(fout, ".\n");
   }
}


/************* Scanning a HTML file ******************/

#define T_ILL    0
#define T_HTML   1
#define T_HEAD   2
#define T_TITLE  3
#define T_BODY   4
#define T_ADDR   5
#define T_LINK   6
#define T_H     10
#define T_VERB  11
#define T_DIR   12
#define T_LIST  13
#define T_DESC  14
#define T_ITEM  15
#define T_DT    16
#define T_DD    17
#define T_P     18
#define T_A     19
#define T_IMG   20
#define T_CHAR  21
#define T_BR    22
#define T_META  23
#define T_SCRIPT 24
#define T_STYLE 25
#define NR_TAGS   74
#define NR_M_TAGS 10

#define TN_H1   5

#define C_NO    0
#define C_YES   1
#define C_OPT   2

#define LATEX_KIND_OFF         (1<<0)
#define LATEX_KIND_ON          (1<<1)
#define LATEX_KIND_IGH         (1<<2)
#define LATEX_KIND_MATH        (1<<3)
#define LATEX_KIND_VERB        (1<<4)
#define LATEX_KIND_ALLTT       (1<<5)
#define LATEX_KIND_IIM         (1<<6)   /* ignore inside math */
#define LATEX_KIND_BR          (1<<7)
#define LATEX_KIND_OEL         (1<<8)
#define LATEX_KIND_CEL         (1<<9)
#define LATEX_KIND_IN_MATH     (1<<10)  /* enclose with math, if needed */
#define GET_LATEX_KIND_LEVEL(X) (((X)>>11) & 15)
#define SET_LATEX_KIND_LEVEL(X) (((X) & 15)<<11)

struct Codes
  { char *name;
    int  closing;
    byte kind;
    int latex_kind;
    char *latex_open,
         *latex_close;
  } tags[NR_TAGS + NR_M_TAGS] =
{
#define H_HTML     0
   { "html",    C_YES, T_HTML, 0, "", "" },
#define H_HEAD     1
   { "head",    C_YES, T_HEAD, 0, "", "" },
#define H_TITLE    2
   { "title",   C_YES, T_TITLE, 0, "", "" },
#define H_BODY     3
   { "body",    C_YES, T_BODY, LATEX_KIND_ON, "", "" },
#define H_ADDRESS  4
   { "address", C_YES, T_ADDR, 0, "", "" },
#define H_H1       5
   { "h1",      C_YES, T_H, SET_LATEX_KIND_LEVEL(1),"{\\LARGE \\textbf{", "}}" },
#define H_H2       6
   { "h2",      C_YES, T_H, SET_LATEX_KIND_LEVEL(2), "{\\Large \\textbf{", "}}" },
#define H_H3       7
   { "h3",      C_YES, T_H, SET_LATEX_KIND_LEVEL(3), "{\\large \\textbf{", "}}" },
#define H_H4       8
   { "h4",      C_YES, T_H, SET_LATEX_KIND_LEVEL(4), "\\textbf{ ", "}" },
#define H_H5       9
   { "h5",      C_YES, T_H, SET_LATEX_KIND_LEVEL(5), "{\\small \\textbf{", "}}" },
#define H_H6      10
   { "h6",      C_YES, T_H, SET_LATEX_KIND_LEVEL(6), "{\\footnotesize \\textbf{", "}}" },
#define H_P       11
   { "p",       C_OPT, T_P, 0, "\n\n", "" },
#define H_UL      12
   { "ul",      C_YES, T_LIST, LATEX_KIND_IGH,
                       "\n\\begin{itemize}", "\n\\end{itemize}\n" },
#define H_MENU    13
   { "menu",    C_YES, T_LIST, LATEX_KIND_IGH,
                       "\n\\begin{itemize}", "\n\\end{itemize}\n" },
#define H_DIR     14
   { "dir",     C_YES, T_LIST, LATEX_KIND_IGH,
                       "\n\\begin{itemize}", "\n\\end{itemize}\n" },
#define H_OL      15
   { "ol",      C_YES, T_LIST, LATEX_KIND_IGH,
                       "\n\\begin{enumerate}", "\n\\end{enumerate}\n" },
#define H_LI      16
   { "li",      C_OPT, T_ITEM, 0, "\n\\item ", "" },
#define H_LH      17
   { "lh",      C_OPT, T_ITEM, 0, "\n\\item ", "" },
#define H_DL      18
   { "dl",      C_YES, T_DESC, LATEX_KIND_IGH,
                       "\n\\begin{description}", "\n\\end{description}\n" },
#define H_DT      19
   { "dt",      C_OPT, T_DT, 0, "\n\\item[", "]" },
#define H_DD      20
   { "dd",      C_OPT, T_DD, 0, "", "" },
#define H_A       21
   { "a",       C_OPT, T_A, 0, "", "" },
#define H_Q       22
   { "q",       C_YES, T_CHAR, 0, "``", "''" },
#define H_I       23
   { "i",       C_YES, T_CHAR, LATEX_KIND_IIM, "\\textit{", "}" },
#define H_EM      24
   { "em",      C_YES, T_CHAR, 0, "\\emph{", "}" },
#define H_B       25
   { "b",       C_YES, T_CHAR, 0, "\\textbf{", "}" },
#define H_STRONG  26
   { "strong",  C_YES, T_CHAR, 0, "\\textbf{", "}" },
#define H_TT      27
   { "tt",      C_YES, T_CHAR, 0, "\\texttt{", "}" },
#define H_SAMP    28
   { "samp",    C_YES, T_CHAR, 0, "\\texttt{", "}" },
#define H_KDB     29
   { "kbd",     C_YES, T_CHAR, 0, "\\texttt{", "}" },
#define H_VAR     30
   { "var",     C_YES, T_CHAR, 0, "\\textsl{", "}" },
#define H_DFN     31
   { "dfn",     C_YES, T_CHAR, 0, "\\textsc{", "}" },
#define H_CODE    32
   { "code",    C_YES, T_CHAR, 0, "\\texttt{", "}" },
#define H_BLINK   33
   { "blink",   C_YES, T_CHAR, 0, "", "" },
#define H_CITE    34
   { "cite",    C_YES, T_CHAR, 0, "\\emph{", "}" },
#define H_BLOCKQUOTE 35
   { "blockquote", C_YES, T_CHAR, LATEX_KIND_IGH,
                       "\\begin{quotation} ", "\\end{quotation}" },
#define H_BQ      36
   { "bq",      C_YES, T_CHAR, LATEX_KIND_IGH,
                       "\\begin{quotation} ", "\\end{quotation}" },
#define H_U       37
   { "u",       C_YES, T_CHAR, 0, "\\underbar{", "}" },
#define H_S       38
   { "s",       C_YES, T_CHAR, 0, "", "" },
#define H_SMALL   39
   { "small",   C_YES, T_CHAR, 0, "{\\small ", "}" },
#define H_BIG     40
   { "big",     C_YES, T_CHAR, 0, "{\\large ", "}" },
#define H_NOTE    41
   { "note",    C_YES, T_CHAR, 0, "", "" },
#define H_AU      42
   { "au",      C_YES, T_CHAR, 0, "", "" },
#define H_PERSON  43
   { "person",  C_YES, T_CHAR, 0, "", "" },
#define H_ACRONYM 44
   { "acronym", C_YES, T_CHAR, 0, "", "" },
#define H_ABBREV  45
   { "abbrev",  C_YES, T_CHAR, 0, "", "" },
#define H_CREDIT  46
   { "credit",  C_YES, T_CHAR, 0, "", "" },
#define H_INS     47
   { "ins",     C_YES, T_CHAR, 0, "", "" },
#define H_DEL     48
   { "del",     C_YES, T_CHAR, 0, "", "" },
#define H_PRE     49
   { "pre",     C_YES, T_VERB, LATEX_KIND_ALLTT, "\\begin{alltt} ",
                                                 "\\end{alltt}\n" },
#define H_XMP     50
   { "xmp",     C_YES, T_VERB, LATEX_KIND_VERB, "\\begin{verbatim} ",
                                                "\\end{verbatim}\n" },
#define H_LISTING 51
   { "listing", C_YES, T_VERB, LATEX_KIND_VERB, "\\begin{verbatim} ",
                                                "\\end{verbatim}\n" },
#define H_BR      52
   { "br",      C_NO,  T_DIR, LATEX_KIND_BR, "\\newline\n", "" },
#define H_HR      53
   { "hr",      C_NO,  T_DIR, 0, "\\vspace{1mm}\\hrule ", "" },
#define H_IMG     54
   { "img",     C_NO,  T_IMG, 0, "", "" },
#define H_ISINDEX 55
   { "isindex", C_NO,  T_DIR, 0, "", "" },
#define H_SELECT  56
   { "select",  C_YES, T_DIR, 0, "", "" },
#define H_LINK    57
   { "link",    C_NO,  T_LINK, 0, "", "" },
#define H_CENTER  58
   { "center",  C_YES, T_CHAR, 0, "{\\centering ", "}" },
#define H_META    59
   { "meta",    C_NO,  T_META, 0, "", "" },
#define H_TABLE   60
   { "table",   C_YES, T_DIR, 0, "", "" },
#define H_TH      61
   { "th",      C_OPT, T_DIR, 0, "", "" },
#define H_TR      62
   { "tr",      C_OPT, T_DIR, 0, "", "" },
#define H_TD      63
   { "td",      C_OPT, T_DIR, 0, "", "" },
#define H_SUP     64
   { "sup",     C_YES, T_DIR, LATEX_KIND_IN_MATH, "^{", "}" },
#define H_SUB     65
   { "sub",     C_YES, T_DIR, LATEX_KIND_IN_MATH, "_{", "}" },
#define H_CAPTION 66
   { "caption", C_OPT, T_CHAR, 0, "", "" },
#define H_SCRIPT  67
   { "script",  C_OPT, T_SCRIPT, LATEX_KIND_OFF, "", "" },
#define H_NOSCRIPT 68
   { "noscript",  C_OPT, T_CHAR, 0, "", "" },
#define H_STYLE   69
   { "style",   C_OPT, T_SCRIPT, LATEX_KIND_OFF, "", "" },
#define H_FONT    70
   { "font",    C_OPT, T_CHAR, 0, "", "" },
#define H_FORM    71
   { "form",    C_OPT, T_CHAR, 0, "", "" },
#define H_INPUT   72
   { "input",   C_NO,  T_CHAR, 0, "", "" },
#define H_TEXTAREA 73
   { "textarea",C_OPT, T_CHAR, 0, "", "" },
#define H_M_OFF   74
   { "!--latex-off--", C_YES, T_DIR, LATEX_KIND_OFF, "", "" },
#define H_L1      75
   { "l1",      C_YES, T_ILL, 0, "\n\n\\chapter{", "}\n\n" },
#define H_L2      76
   { "l2",      C_YES, T_ILL, 0, "\n\n\\section{", "}\n\n" },
#define H_L3      77
   { "l3",      C_YES, T_ILL, 0, "\n\n\\subsection{", "}\n\n" },
#define H_L4      78
   { "l4",      C_YES, T_ILL, 0, "\n\n\\subsubsection{", "}\n\n" },
#define H_L5      79
   { "l5",      C_YES, T_ILL, 0, "\n\n\\paragraph{", "}\n" },
#define H_L6      80
   { "l6",      C_YES, T_ILL, 0, "\n\n\\subparagraph{", "}\n" },
#define H_L7      81
   { "l7",      C_YES, T_ILL, 0, "", "" },
#define H_L8      82
   { "l8",      C_YES, T_ILL, 0, "", "" },
#define H_L9      83
   { "l9",      C_YES, T_ILL, 0, "", "" },
};

/* Generation state values */

bool in_html,
     in_head,
     in_title,
     in_body,
     in_address;
bool in_desc_label;
int  no_copy;
int  ignore_header;
bool in_e_alltt;  /* = in_alltt && opt_href_in_alltt == OPT_NONE */
bool in_e_header; /* = in_header && opt_href_in_header == OPT_NONE */
char label_name[MAX_N + 1];
bool first_label,
     active_label,
     after_first,
     no_header,
     no_title,
     at_start,
     active_href,
     delayed_href,
     href_included;
int item_depth;
bool empty_line,
     gen_newline,
     empty_item,
     no_item,
     latex_repl;
char dest_file[MAX_DF + 1],
     href_name[MAX_N + 1];
int href_status;
int add_level_depth;

#define MAX_STACK 30
struct 
   { int  ln;
     byte tagnr;
     byte tagkind;
     byte p_tagnr;
     bool closing;
   } stack[MAX_STACK];
int stack_depth = 0;

bool scan_def_string(char *def, int *rp, int *rl, char *str)
{   int p = *rp,
        l = *rl; 
    l = 0;
    p++;
    for (;;)
    {   if (def[p] == '\0')
        {   *rp = p;
            *rl = l;
            return FALSE;
        }
        else if (def[p] == '"')
            if (def[p+1] == '"')
            {   if (str != NULL)
                    str[l] = '"';
                l++;
                p++;
            }
            else
            {   if (str != NULL)
                    str[l] = '\0';
                p++;
                *rp = p;
                *rl = l;
                return TRUE;
            }
        else if (strneq(def + p, "&amp;", 5))
        {   if (str != NULL)
                str[l] = '&';
            l++;
            p += 5;
        }
        else if (strneq(def + p, "&lt;", 4))
        {   if (str != NULL)
                str[l] = '<';
            l++;
            p += 4;
        }
        else if (strneq(def + p, "&gt;", 4))
        {   if (str != NULL)
                str[l] = '>';
            l++;
            p += 4;
        }
        else if (strneq(def + p, "&dash;", 6))
        {   if (str != NULL)
                str[l] = '-';
            l++;
            p += 6;
        }
        else if (strneq(def + p, "\\nl", 3))
        {   if (str != NULL)
                str[l] = '\n';
            l++;
            p += 3;
        }
        else
        {   if (str != NULL)
                str[l] = def[p];
            l++;
            p++;
        }
    }
}

void calculate_el_values(int tagnr)
{
    tags[tagnr].latex_kind &= ~(LATEX_KIND_OEL | LATEX_KIND_CEL);
    if (tags[tagnr].latex_open[strlen(tags[tagnr].latex_open)-1] == '\n')
    {   tags[tagnr].latex_kind |= LATEX_KIND_OEL;
        DEBUG_P1("newline in `%s'\n", tags[tagnr].latex_open);
    }
    if (tags[tagnr].latex_close[strlen(tags[tagnr].latex_close)-1] == '\n')
    {   tags[tagnr].latex_kind |= LATEX_KIND_CEL;
        DEBUG_P1("newline in `%s'\n", tags[tagnr].latex_close);
    }
}

void calculate_all_el()
{   int tagnr;

    for (tagnr = 0; tagnr < NR_TAGS + NR_M_TAGS; tagnr++)
        calculate_el_values(tagnr);
}

void process_definition(FILE *freport, char *def, char *fn, int ln,
                        bool in_html_file);
void process_definition(FILE *freport, char *def, char *fn, int ln,
                        bool in_html_file)
{   char html_com[MAX_HC + 1];
    int p = 0, i,
        tagnr;

    DEBUG_P1("process_definition(, `%s',,);\n", def);
    while (def[p] == ' ')
       p++;
    i = 0;
    while (def[p] != ' ' && def[p] != '\0')
    {   if (i < MAX_HC)
            html_com[i++] = tolower(def[p]);
        p++;
    }
    html_com[i] = '\0';

    for (tagnr = 0; tagnr < NR_TAGS + NR_M_TAGS; tagnr++)
        if (streq(html_com, tags[tagnr].name))
            break;
    if (tagnr == NR_TAGS || tagnr == NR_TAGS + NR_M_TAGS)
    {   if (freport)
            fprintf(freport,
                      in_html_file 
                    ? "%s (%d) : Unknown tag kind `%s' in <!htmldef %s>\n"
                    : "%s (%d) : Unknown tag kind `%s' in %%html -d %s\n", 
                    fn, ln, html_com, def);
        return;
    }
    DEBUG_P1("tag %s\n", tags[tagnr].name);

    for (i = 0; i < stack_depth; i++)
        if (stack[i].tagnr == tagnr)
        {   if (freport)
                fprintf(freport, 
                        "%s (%d) : Cannot redefine `%s' inside itself\n",
                        fn, ln, html_com);
            return;
        }
    tags[tagnr].latex_kind = 0;
    for(;;)
    {
        while (def[p] == ' ')
            p++;

        if (strneq(def + p, "-math ", 6))
        {   tags[tagnr].latex_kind |= LATEX_KIND_MATH;
            DEBUG_P("found -math\n");
            p += 6;
        }
        else if (strneq(def + p, "-inmath ", 8))
        {   tags[tagnr].latex_kind |= LATEX_KIND_IN_MATH;
            DEBUG_P("found -math\n");
            p += 8;
        }
        else if (   strneq(def + p, "-verb ", 6)
                 || streq(def + p, "-verb"))
        {   tags[tagnr].latex_kind |= LATEX_KIND_VERB;
            tags[tagnr].latex_open = "\\begin{verbatim}";
            tags[tagnr].latex_close = "\\end{verbatim}\n";
            DEBUG_P("found -verb\n");
            p += 5;
        }
        else if (   strneq(def + p, "-alltt ", 7)
                 || streq(def + p, "-alltt"))
        {   tags[tagnr].latex_kind |= LATEX_KIND_ALLTT;
            tags[tagnr].latex_open = "\\begin{alltt}";
            tags[tagnr].latex_close = "\\end{alltt}\n";
            DEBUG_P("found -alltt\n");
            p += 6;
        }
        else if (   strneq(def + p, "-off ", 5)
                 || streq(def + p, "-off"))
        {   tags[tagnr].latex_kind |= LATEX_KIND_OFF;
            DEBUG_P("found -off\n");
            p += 4;
        }
        else if (   strneq(def + p, "-on ", 4)
                 || streq(def + p, "-on"))
        {   tags[tagnr].latex_kind |= LATEX_KIND_ON;
            DEBUG_P("found -on\n");
            p += 3;
        }
        else if (   strneq(def + p, "-igh ", 5)
                 || streq(def + p, "-igh"))
        {   tags[tagnr].latex_kind |= LATEX_KIND_IGH;
            DEBUG_P("found -igh\n");
            p += 4;
        }
        else if (   strneq(def + p, "-iim ", 5)
                 || streq(def + p, "-iim"))
        {   tags[tagnr].latex_kind |= LATEX_KIND_IIM;
            DEBUG_P("found -iim\n");
            p += 4;
        }
        else if (   strneq(def + p, "-br ", 4)
                 || streq(def + p, "-br"))
        {   tags[tagnr].latex_kind |= LATEX_KIND_BR;
            DEBUG_P("found -br\n");
            p += 3;
        }
        else if (def[p] == '-' && def[p+1] == 'l' && def[p+2] >= '1'
                 && def[p+2] <= '9' && (def[p+3] == ' ' || def[p+3] == '\0'))
        {   tags[tagnr].latex_kind |= SET_LATEX_KIND_LEVEL(def[p+2] - '0');
            DEBUG_P1("found -h%c\n", def[p+2]);
            p += 3;
        }
        else
            break;
    }

    while (def[p] == ' ')
        p++;

    if (def[p] == '"')
    {   int kp = p,
            l;
        if (!scan_def_string(def, &p, &l, NULL))
        {   if (freport)
                fprintf(freport,
                        "%s (%d) : Incorrect quoted string `%s'\n",
                        fn, ln, def + kp);
        }
        else
        {   tags[tagnr].latex_open = NALLOC(char, l + 1);
            p = kp;
            scan_def_string(def, &p, &l, tags[tagnr].latex_open);
            DEBUG_P1("latex_open: `%s'\n", tags[tagnr].latex_open);
            while (def[p] == ' ')
                p++;
            if (def[p] == '"')
            {   kp = p;
                if (!scan_def_string(def, &p, &l, NULL))
                {   if (freport)
                        fprintf(freport,
                                "%s (%d) : Incorrect quoted string `%s'\n",
                                fn, ln, def + kp);
                }
                else
                {   tags[tagnr].latex_close = NALLOC(char, l + 1);
                    p = kp;
                    scan_def_string(def, &p, &l, tags[tagnr].latex_close);
                    DEBUG_P1("latex_close : `%s'\n", 
                                tags[tagnr].latex_close);
                }
            }
        }
    }
    calculate_el_values(tagnr);
}

void process_style(FILE *freport, char *style, char *fn, int ln);
void process_style(FILE *freport, char *style, char *fn, int ln)
{
    DEBUG_P1("Style: |%s|\n", style);

    if (streq(style, "book") || streq(style, "report"))
    {   tags[H_L1].latex_open = "\n\n\\chapter{";
        tags[H_L1].latex_close = "}\n\n";
        tags[H_L2].latex_open = "\n\n\\section{";
        tags[H_L2].latex_close = "}\n\n";
        tags[H_L3].latex_open = "\n\n\\subsection{";
        tags[H_L3].latex_close = "}\n\n";
        tags[H_L4].latex_open = "\n\n\\subsubsection{";
        tags[H_L4].latex_close = "}\n\n";
        tags[H_L5].latex_open = "\n\n\\paragraph{";
        tags[H_L5].latex_close = "}\n";
        tags[H_L6].latex_open = "\n\n\\subparagraph{";
        tags[H_L6].latex_close = "}\n";
        tags[H_L7].latex_open = "";
        tags[H_L7].latex_close = "";
    }
    else if (streq(style, "plain"))
    {   tags[H_L1].latex_open = "\n\n\\section*{";
        tags[H_L1].latex_close = "}\n\n";
        tags[H_L2].latex_open = "\n\n\\subsection*{";
        tags[H_L2].latex_close = "}\n\n";
        tags[H_L3].latex_open = "\n\n\\subsubsection*{";
        tags[H_L3].latex_close = "}\n\n";
        tags[H_L4].latex_open = "\n\n\\paragraph*{";
        tags[H_L4].latex_close = "}\n";
        tags[H_L5].latex_open = "\n\n\\subparagraph*{";
        tags[H_L5].latex_close = "}\n";
        tags[H_L6].latex_open = "";
        tags[H_L6].latex_close = "";
        tags[H_L7].latex_open = "";
        tags[H_L7].latex_close = "";
    }
    else if (streq(style, "article"))
    {   tags[H_L1].latex_open = "\n\n\\section{";
        tags[H_L1].latex_close = "}\n\n";
        tags[H_L2].latex_open = "\n\n\\subsection{";
        tags[H_L2].latex_close = "}\n\n";
        tags[H_L3].latex_open = "\n\n\\subsubsection{";
        tags[H_L3].latex_close = "}\n\n";
        tags[H_L4].latex_open = "\n\n\\paragraph{";
        tags[H_L4].latex_close = "}\n";
        tags[H_L5].latex_open = "\n\n\\subparagraph{";
        tags[H_L5].latex_close = "}\n";
        tags[H_L6].latex_open = "";
        tags[H_L6].latex_close = "";
        tags[H_L7].latex_open = "";
        tags[H_L7].latex_close = "";
    }
    else
    {   if (freport)
            fprintf(freport, "%s (%d) : Unknown style `%s'\n",
                    fn, ln, style);
    }
    calculate_all_el();
}

void process_option(FILE *freport, char *opt, char *fn, int ln,
                    bool in_html_file);
void process_option(FILE *freport, char *opt, char *fn, int ln,
                    bool in_html_file)
{   char html_com[MAX_HC + 1];
    int p = 0, i,
        optnr;

    DEBUG_P1("process_option(, `%s',,);\n", opt);
    while (opt[p] == ' ')
       p++;
    i = 0;
    while (opt[p] != ' ' && opt[p] != '\0')
    {   if (i < MAX_HC)
            html_com[i++] = opt[p];
        p++;
    }
    html_com[i] = '\0';

    for (optnr = 0; optnr < NR_OPTS; optnr++)
        if (streq(html_com, allopt[optnr].name))
            break;
    if (optnr == NR_OPTS)
    {   if (freport)
            fprintf(freport,
                      in_html_file
                    ? "%s (%d) : Unknown option `%s' in <!html-opt %s>\n"
                    : "%s (%d) : Unknown option `%s' in %%html -o %s\n",
                    fn, ln, html_com, opt);
        return;
    }
    DEBUG_P1("option %s\n", allopt[optnr].name);

    while (opt[p] == ' ')
        p++;

    if (allopt[optnr].kind == OPT_KIND_STR)
    {
        if (opt[p] == '"')
        {   int kp = p,
                l;
            if (!scan_def_string(opt, &p, &l, NULL))
            {   if (freport)
                    fprintf(freport,
                            "%s (%d) : Incorrect quoted string `%s'\n",
                            fn, ln, opt + kp);
            }
            else
            {   DEBUG_P1("old: `%s'\n", allopt[optnr].str);
                allopt[optnr].str = NREALLOC(allopt[optnr].str, char, l + 1);
                scan_def_string(opt, &kp, &l, allopt[optnr].str);
                DEBUG_P1("Found: |%s|\n", allopt[optnr].str);
            }
        }
        else if (freport)
            fprintf(freport,
                    "%s (%d) : Expected string in `%s'\n",
                    fn, ln, opt + p);
    }
    else
    {

        if (allopt[optnr].kind == OPT_KIND_IN)
        {   if (strneq(opt + p, "normal", 6))
                allopt[optnr].v = OPT_NORMAL;
            else if (strneq(opt + p, "cffn", 4))
                allopt[optnr].v = OPT_CFFN;
            else if (strneq(opt + p, "fn", 2))
                allopt[optnr].v = OPT_FN;
            else if (strneq(opt + p, "none", 4))
                allopt[optnr].v = OPT_NONE;
            else if (freport != NULL)
                fprintf(freport,
                      "%s (%d) : Expected: normal, cffn, fn, or none in `%s'\n",
                        fn, ln, opt + p);
        }
        else
        {   if (strneq(opt + p, "on", 2))
                allopt[optnr].v = TRUE;
            else if (strneq(opt + p, "off", 3))
                allopt[optnr].v = FALSE;
            else if (freport != NULL)
                fprintf(freport,
                        "%s (%d) : Expected: on or off in `%s'\n",
                        fn, ln, opt + p);
        }
    }
    DEBUG_P("ready\n");
}

void close_header(FILE *fout, char *html_fn)
{   after_first = TRUE;
    if (first_label)
    {   if (fout != NULL)
            print_label(fout, find_file(html_fn)->nr, "", FALSE);
        first_label = FALSE;
    }
    if (active_label)
    {   if (fout != NULL)
            print_label(fout, find_file(html_fn)->nr, label_name, FALSE);
        active_label = FALSE;
    }
}

void print_sp(FILE *fout, char *str, char *html_fn);
void print_sp(FILE *fout, char *str, char *html_fn)
{   bool has_header = strstr(str, "%l") != NULL;
    int level = add_level_depth;
    if (level > 9)
        level = 9;

    for(; *str; str++)
        if (*str != '%')
            fputc(*str, fout);
        else if (*(str+1) == '%')
        {   fputc('%', fout);
            str++;
        }
        else if (*(str+1) == 'f')
        {   fputs(html_fn, fout);
            str++;
        }
        else if (*(str+1) == 'l')
        {   fputs(tags[level + H_L1 - 1].latex_open, fout);
            str++;
        }
        else if (*(str+1) == 'c')
        {   fputs(tags[level + H_L1 - 1].latex_close, fout);
            str++;
        }

    if (has_header)
        close_header(fout, html_fn);
    no_header = FALSE; 
}

void latex_open(FILE *fout, FILE *freport, int tagnr, int ln, char *html_fn,
                bool closing)
{   int tagkind = tags[tagnr].kind,
        latex_kind = tags[tagnr].latex_kind;
    int level = GET_LATEX_KIND_LEVEL(latex_kind);
    int p_tagnr;
    char *latex_open;

    if (tagnr == H_BODY && fout != NULL)
    {   if (no_title && opt_no_title[0] != '\0')
            print_sp(fout, opt_no_title, html_fn);
        if (at_start && opt_at_start[0] != '\0')
            print_sp(fout, opt_at_start, html_fn);
        at_start = FALSE;
    }

    if (level > 0 && !ignore_header)
    {   level += add_level_depth - 1;
        if (level > 9)
            level = 9;
        p_tagnr = H_L1 + level - 1;
        no_header = FALSE;
    }
    else
    {   p_tagnr = tagnr;

        if (no_header && !no_copy && tagnr < NR_TAGS && fout != NULL)
            print_sp(fout, opt_no_header, html_fn);
    }

    latex_open = latex_repl ? "" : tags[p_tagnr].latex_open;

    if (latex_kind & LATEX_KIND_ON)
    {   DEBUG_P("no_copy--\n");
        no_copy--;
    }

    DEBUG_P5("latex_open(,tagnr=%d, %s, ln=%d, p_tagnr=%d:%s)\n",
             tagnr, tags[tagnr].name, ln, p_tagnr, tags[p_tagnr].name);
    if (fout == NULL || no_copy || latex_open[0] == '\0')
        /* nothing to generate */;
    else if (   (empty_line && (latex_kind & LATEX_KIND_BR))
             || (in_header && tagkind == T_P)
             || (item_depth >= 4 && tagkind == T_LIST)
             || in_verb
             || (in_alltt && !(latex_kind & LATEX_KIND_ALLTT) &&
                 tagkind != T_CHAR))
    {   if (freport && option_warn)
        fprintf(freport,
                "%s (%d) : <%s> ignored in LaTeX.\n",
                html_fn, ln, tags[tagnr].name);
    }
    else if (in_math && (latex_kind & (LATEX_KIND_IIM | LATEX_KIND_MATH)))
    {   if ((latex_kind & LATEX_KIND_MATH) && freport)
        fprintf(freport,
                "%s (%d) : <%s> ignored in LaTeX; nested math.\n",
                html_fn, ln, tags[tagnr].name);
    }
    else
    {   if (in_alltt && (latex_kind & LATEX_KIND_MATH))
            latex_open = opt_s_math_open;
        if (latex_open[0] == '\n')
        {   gen_newline = FALSE;
            if (no_item && tagkind != T_ITEM)
            {   fputs(opt_empty_item, fout);
                no_item = FALSE;
            }
            if (latex_kind & LATEX_KIND_IN_MATH)
            {   if (in_math == 0)
                    fputs(opt_s_math_open, fout);
                in_math++;
            }
            fputs(latex_open + empty_line, fout);
        }
        else
        {
            if (gen_newline)
            {   if (!(latex_kind & LATEX_KIND_BR))
                {   DEBUG_GN('1');
                    fputc('\n', fout);
                }
                gen_newline = FALSE;
            }
            if (no_item && tagkind != T_ITEM)
            {   if (fout != NULL && !no_copy)
                    fputs(opt_empty_item, fout);
                no_item = FALSE;
            }
            if (latex_kind & LATEX_KIND_IN_MATH)
            {   if (in_math == 0)
                    fputs(opt_s_math_open, fout);
                in_math++;
            }
            fputs(latex_open, fout);
        }
        if (latex_kind & LATEX_KIND_OEL)
            empty_line = TRUE;
    }
    if (tags[tagnr].closing == C_NO)
        return;
    if (stack_depth < MAX_STACK)
    {   DEBUG_P3("push(%d,%d,) : %d\n", ln, tagnr, stack_depth);
        stack[stack_depth].ln = ln;
        stack[stack_depth].tagnr = tagnr; 
        stack[stack_depth].tagkind = tagkind;
        stack[stack_depth].p_tagnr = p_tagnr; 
        stack[stack_depth].closing = closing;
        stack_depth++; 
    }
    else if (freport != NULL)
        fprintf(freport, 
                "%s (%d) : remove <%s>, more than %d nested tags.\n",
                html_fn, ln, tags[tagnr].name, MAX_STACK);


    DEBUG_P3("latex_open(,tagnr=%d, ln=%d, p_tagnr=%d)\n",
             tagnr, ln, p_tagnr);
    switch (tagnr)
    {   case H_HTML    : in_html = TRUE; break;
        case H_HEAD    : in_head = TRUE; break;
        case H_BODY    : in_body = TRUE; no_title = FALSE; break;
        case H_TITLE   : in_title = TRUE; no_title = FALSE; break;
        case H_ADDRESS : in_address = TRUE; break;
    }
    if (latex_kind & LATEX_KIND_OFF)
    {   DEBUG_P("no_copy++\n");
        no_copy++;
    }
    if (latex_kind & LATEX_KIND_IGH)
        ignore_header++;
    if (latex_kind & LATEX_KIND_MATH)
        in_math++;
    if (latex_kind & LATEX_KIND_VERB)
        in_verb++;
    if (latex_kind & LATEX_KIND_ALLTT)
    {   in_alltt++;
        in_e_alltt = opt_href_in_alltt == OPT_NONE;
    }
    switch (tagkind)
    {   case T_H     : in_header = TRUE;
                       in_e_header = opt_href_in_header == OPT_NONE;
                       break;
        case T_LIST  : item_depth++;
                       no_item = TRUE; break;
        case T_ITEM  : empty_item = TRUE;
                       no_item = FALSE; break;
        case T_DESC  : item_depth++; break;
        case T_DT    : in_desc_label = TRUE; break;
        case T_DD    : empty_item = TRUE; break;
        case T_A     :
            if (   freport && option_warn
                && (   in_verb || in_e_alltt || in_e_header))
                fprintf(freport, "%s (%d) : <a href> ignored in LaTeX.\n",
                        html_fn, ln);
            break;
    }
}

void latex_close(FILE *fout, FILE *freport, int ln, char *html_fn)
{   int tagnr,
        tagkind,
        p_tagnr;
    char *latex_close;
    int latex_kind;
    bool latex_kind_cel;
    if (stack_depth <= 0)
        return;

    stack_depth--;
    tagnr = stack[stack_depth].tagnr;
    tagkind = stack[stack_depth].tagkind;
    latex_kind = tags[tagnr].latex_kind;

    if ((tagkind == T_ITEM || tagkind == T_DD) && empty_item)
    {   if (fout != NULL && !no_copy)
            fprintf(fout, "??");
        if (freport != NULL && !no_copy)
            fprintf(freport, "%s (%d) : empty item.\n", html_fn, ln);
        empty_item = FALSE;
    }

    p_tagnr = stack[stack_depth].p_tagnr;
    if (latex_repl)
    {   latex_close = "";
        latex_kind_cel = FALSE;
    }
    else
    {   latex_close = tags[p_tagnr].latex_close;
        latex_kind_cel = (tags[p_tagnr].latex_kind & LATEX_KIND_CEL);
    }

    DEBUG_P2("latex_close: %s,%s\n", tags[tagnr].name, tags[p_tagnr].name);

    if (latex_kind & LATEX_KIND_OFF)
    {   DEBUG_P("no_copy--\n");
        no_copy--;
    }

    if (fout == NULL || no_copy || latex_close[0] == '\0')
        /* nothing to generate */;
    else if (   (in_header && tagkind == T_P)
             || (item_depth > 4 && tagkind == T_LIST)
             || (in_verb && !(latex_kind & LATEX_KIND_VERB))
             || (   in_alltt && !(latex_kind & LATEX_KIND_ALLTT)
                 && tagkind != T_CHAR))
    {   if (freport && option_warn)
        fprintf(freport,
                "%s (%d) : </%s> ignored in LaTeX.\n",
                html_fn, ln, tags[tagnr].name);
    }
    else if (   in_math
             && (   (latex_kind & LATEX_KIND_IIM)
                 || ((latex_kind & LATEX_KIND_MATH) && in_math > 1)))
    {   if ((latex_kind & LATEX_KIND_MATH) && in_math > 1 && freport)
        fprintf(freport,
                "%s (%d) : </%s> ignored in LaTeX; nested math.\n",
                html_fn, ln, tags[tagnr].name);
    }
    else
    {   if (in_alltt && (latex_kind & LATEX_KIND_MATH))
            latex_close = opt_s_math_close;
        if (latex_close[0] == '\n')
        {   gen_newline = FALSE;
            fprintf(fout, "%s", latex_close + empty_line);
        }
        else
        {   /* if not delay:
              if (gen_newline)
              {   fputc('\n', fout);
                  gen_newline = FALSE;
              }
            */
            fprintf(fout, "%s", latex_close);
        }
        if (latex_kind & LATEX_KIND_IN_MATH)
        {   if (in_math == 1)
                fputs(opt_s_math_close, fout);
            in_math--;
        }
        if (latex_kind_cel)
        {   empty_line = TRUE;
            gen_newline = FALSE; /* remove if no delay */
        }
    }
    switch (tagnr)
    {   case H_HTML    : in_html = FALSE; break;
        case H_HEAD    : in_head = FALSE; break;
        case H_BODY    : in_body = FALSE; break;
        case H_TITLE   : in_title = FALSE; break;
        case H_ADDRESS : in_address = FALSE; break;
    }

    if (GET_LATEX_KIND_LEVEL(latex_kind) && !ignore_header)
        close_header(fout, html_fn);

    if (latex_kind & LATEX_KIND_ON)
    {   DEBUG_P("no_copy++\n");
        no_copy++;
    }
    if (latex_kind & LATEX_KIND_IGH)
        ignore_header--;
    if (latex_kind & LATEX_KIND_MATH)
        in_math--;
    if (latex_kind & LATEX_KIND_VERB)
        in_verb--;
    if (latex_kind & LATEX_KIND_ALLTT)
    {   in_alltt--;
        if (in_alltt == 0)
            in_e_alltt = FALSE;
    }
    switch (tagkind)
    {   case T_H     : in_header = FALSE;
                       in_e_header = FALSE; break;
        case T_LIST  : no_item = FALSE; /* in case of empty list */
        case T_DESC  : item_depth--; break;
        case T_DT    : if (delayed_href && fout != NULL)
                       {   print_f_href(fout, dest_file, href_name, href_status,
                                           in_header > 0);
                           delayed_href = FALSE;
                       }
                       if (fout != NULL)
                           fprintf(fout, " ");
                       in_desc_label = FALSE;
                       break;
        case T_A     :
            {   if (!href_included)
                    /* ignore */;
                else if (active_href && fout != NULL)
                {   if (option_bibliography || !in_desc_label)  
                        print_f_href(fout, dest_file, href_name,
                                     href_status, in_header > 0);
                    else 
                    {   if (delayed_href && freport != NULL)
                            fprintf(freport,
                                "%s (%d) : more than one href in description\n",
                                html_fn, ln);
                        delayed_href = TRUE;
                    }
                }
                active_href = FALSE;
            } 
            break;
     } 
}

char tmp_tagname[30];

char *tagname(int tagnr, bool closing_tag)
{    if (closing_tag)
         if (tagnr == H_M_OFF)
             return "!--latex-on--";
         else
         {   tmp_tagname[0] = '/';
             strcpy(tmp_tagname + 1, tags[tagnr].name);
             return tmp_tagname;
         }
     else
         return tags[tagnr].name;
}

#define REMOVE_TAG(R) remove_tag(freport, tagnr, closing_tag, R, html_fn, ln)
void remove_tag(FILE *freport, int tagnr, bool closing_tag, char *r, 
                char *html_fn, int ln)
{   if (freport != NULL)
        fprintf(freport, "%s (%d) : remove <%s>%s.\n", html_fn, ln,
                tagname(tagnr, closing_tag), r);
}

#define ADD_TAG(T,C,R) add_tag(freport, T, C, R, html_fn, ln)
void add_tag(FILE *freport, int tagnr, bool closing_tag, char *r,
             char *html_fn, int ln)
{   if (freport != NULL)
    {   fprintf(freport, "%s (%d) : add <%s>", html_fn, ln,
                tagname(tagnr, closing_tag));
        if (closing_tag)
            fprintf(freport, " (with <%s> in line %d)", tags[tagnr].name,
                             stack[stack_depth-1].ln);
        fprintf(freport, "%s.\n", r ? r : "");
    }
}

#define REPLACE_TAG() replace_tag(freport, tagnr, closing_tag, html_fn, ln)
void replace_tag(FILE *freport, int tagnr, bool closing_tag,
             char *html_fn, int ln)
{   if (freport != NULL)
        fprintf(freport, "%s (%d) : replace <%s> by </%s>.\n",
                html_fn, ln, tagname(tagnr, closing_tag),
                tags[stack[stack_depth-1].tagnr].name);
}

void latex_closes(FILE *fout, FILE *freport, int tagnr, int tagkind, 
                  bool closing_tag, bool till, int ln, char *html_fn)
{   int j;
    bool found = FALSE;

    for (j = stack_depth - 1; j >= 0; j--)
        if (  tagkind != T_ILL 
            ? stack[j].tagkind == tagkind
            : stack[j].tagnr == tagnr) 
        {   found = TRUE; 
            break; 
        }

    if (found && tags[tagnr].kind == T_CHAR && tagnr != H_FONT) 
        found = j > stack_depth - 5;

    if (found)
    {   while (stack_depth > j + 1)
        {   char mess[60];
            sprintf(mess, ", before <%s>", tagname(tagnr, closing_tag));
            if (stack[stack_depth-1].closing == C_YES)
                ADD_TAG(stack[stack_depth-1].tagnr, TRUE, mess);
            latex_close(fout, freport, ln, html_fn);
        } 
    }
    if (till)
        return;
    if (found)
    {   if (stack[stack_depth-1].tagnr != tagnr)
            REPLACE_TAG();
        latex_close(fout, freport, ln, html_fn);
    }
    else if (stack_depth == 0)
        REMOVE_TAG(", no open tag");
    else 
    {   char mess[60];
        sprintf(mess, ", does not match <%s>", 
                      tags[stack[stack_depth-1].tagnr].name);
        REMOVE_TAG(mess);
    }
}

bool inside_tag(int tagkind)
{   int j;
    for (j = stack_depth - 1; j >= 0; j--)
        if (stack[j].tagkind == tagkind) 
            return TRUE;
        else if (   stack[j].tagkind == T_LIST
                 || stack[j].tagkind == T_DESC)
            return FALSE;
   return FALSE;
}

#define OPEN_TAG(K) (tagkind == K && !closing_tag)
#define CLOSE_TAG(K) (tagkind == K && closing_tag)


#define LATEX_OPEN(T) \
{   latex_open(fout, freport, T, ln, html_fn, tags[T].closing); }
#define LATEX_OPEN_C(T,C) \
{   latex_open(fout, freport, T, ln, html_fn, C); }
#define LATEX_CLOSES(T) \
{   latex_closes(fout, freport, T, T_ILL, TRUE, FALSE, ln, html_fn); }
#define LATEX_CLOSES_K() \
{   latex_closes(fout, freport, tagnr, tagkind, closing_tag, FALSE, ln, \
                 html_fn); }
#define LATEX_CLOSES_T(K) \
{   latex_closes(fout, freport, tagnr, K, FALSE, TRUE, ln, html_fn); }

void process_comment(html_fn, ln, fout, freport, comment, first)
char *html_fn;
int ln;
FILE *fout, *freport;
char *comment;
bool first;
{
    if (   strneq(comment, "latex ", 6)
        || strneq(comment, "latex\n", 6)
        || strneq(comment, "latex-rep ", 10)
        || strneq(comment, "latex-on ", 9)
        || strneq(comment, "latex-on\n", 9))
    {   if (fout != NULL)
        {   char *s;
            if (strneq(comment, "latex ", 6)||strneq(comment, "latex\n", 6))
                s = comment + 6;
            else if (strneq(comment, "latex-rep ", 10))
            {   s = comment + 10;
                latex_repl = TRUE;
            }
            else 
                s = comment + 9;
            while (*s != '\0')
                if (strneq(s, "&amp;", 5))
                {   fputc('&', fout);
                    s += 5;
                }
                else if (strneq(s, "&lt;", 4))
                {   fputc('<', fout);
                    s += 4;
                }
                else if (strneq(s, "&gt;", 4))
                {   fputc('>', fout);
                    s += 4;
                }
                else if (strneq(s, "&dash;", 6))
                {   fputc('-', fout);
                    s += 6;
                }
                else
                {   fputc(*s, fout);
                    s++;
                }
        }
        if (strneq(comment, "latex-on ", 9)||
            strneq(comment, "latex-on\n", 9))
        {   int tagnr = H_M_OFF;
            bool closing_tag = TRUE;
            if (!in_html)
                REMOVE_TAG(", only allowed inside <html>");
            else
                LATEX_CLOSES(tagnr);
        }
    }
    else if (strneq(comment, "latex-off", 9))
    {   int tagnr = H_M_OFF;
        bool closing_tag = FALSE;
        if (!in_html)
            REMOVE_TAG(", only allowed inside <html>");
        else
            LATEX_OPEN(tagnr);
    }
    else if (strneq(comment, "latex-on", 8))
    {   int tagnr = H_M_OFF;
        bool closing_tag = TRUE;
        if (!in_html)
            REMOVE_TAG(", only allowed inside <html>");
        else
            LATEX_CLOSES(tagnr);
    }
    else if (strneq(comment, "latex-def", 9))
    {   if (!first)
            process_definition(freport, comment+9, html_fn, ln, TRUE);
    }
    else if (strneq(comment, "latex-opt", 9))
        process_option(freport, comment+9, html_fn, ln, TRUE);
    else if (strneq(comment, "latex-fmt ", 10))
    {   if (fout != NULL)
        {   char *s = comment + 10;
            int i = 0;
            while (*s != '\0' && i < MAX_LATEX_FMT)
                if (strneq(s, "&amp;", 5))
                {   latex_fmt[i++] = '&';
                    s += 5;
                }
                else if (strneq(s, "&lt;", 4))
                {   latex_fmt[i++] = '<';
                    s += 4;
                }
                else if (strneq(s, "&gt;", 4))
                {   latex_fmt[i++] = '>';
                    s += 4;
                }
                else if (strneq(s, "&dash;", 6))
                {   latex_fmt[i++] = '-';
                    s += 6;
                }
                else
                {   latex_fmt[i++] = *s;
                    s++;
                }
            latex_fmt[i] = '\0';
        }
    }
    else if (strneq(comment, "latex-style ", 12))
    {   int i = 0;
        char *s = comment + 12 ;
        char style[21];

        while (*s == ' ')
            s++;
        for (; *s != '\0' && *s != ' '; s++)
            if (i < 20) 
                style[i++] = *s;
        style[i] = '\0';
        if (!first)
            process_style(freport, style, html_fn, ln);
    }
    else if (streq(comment, "latex-biblio"))
    {   option_bibliography = TRUE; 
        if (fout != NULL)
            print_bibliography(fout);
    }
    else if (fout != NULL)
    {   char *s = comment;
        fprintf(fout, "%% ");
        while (*s != '\0')
        {   if (*s == '\n')
                fprintf(fout, "\n%% ");
            else
                fputc(*s, fout);
            s++;
        }
        fputc('\n', fout);
        empty_line = TRUE;
    }
}

void skip_spaces(FILE *fin, char *html_fn, FILE *fout, FILE *freport,
                 char *r_ch, int *r_lni, bool first);
void skip_spaces(FILE *fin, char *html_fn, FILE *fout, FILE *freport,
         char *r_ch, int *r_ln, bool first)
{   char ch = *r_ch;
    int ln = *r_ln;

    /* skip spaces */
    while (!feof(fin) && (ch == ' ' || ch == '\n'))
        if ((ch = (char)fgetc(fin)) == '\n') ln++;

    /* process comments */
    while (!feof(fin) && ch == '-')
    {   int i = 0;

        if ((ch = (char)fgetc(fin)) == '\n') ln++;
        if (ch != '-')
        {   if (freport)
                fprintf(freport,
                        "%s (%d) : ill comment start\n",
                        html_fn, ln);
            break;
        }
        while(!feof(fin))
        {   if ((ch = (char)fgetc(fin)) == '\n') ln++;
            if (ch == '-' && i > 0 && comment[i-1] == '-')
            {   comment[i-1] = '\0';
                if ((ch = (char)fgetc(fin)) == '\n') ln++;
                break;
            }
            add_to_comment(ch, &i);
        }
        process_comment(html_fn, ln, fout, freport, comment, first);

        /* skip spaces */
        while (!feof(fin) && (ch == ' ' || ch == '\n'))
            if ((ch = (char)fgetc(fin)) == '\n') ln++;
    }
    *r_ch = ch;
    *r_ln = ln;
}

void scan_a_file(html_fn, fout, freport, depth, first, included)
char *html_fn;    /* file name of HTML file */
FILE *fout,       /* LaTeX output file */
     *freport;    /* Error report file */
int depth;        /* Depth for headings */
bool first;       /* First scanning */
bool included;    /* Included in output (or only checking) */    
{   
    file_t *in_file = find_file(html_fn);
    FILE *fin;
    char html_com[MAX_HC + 1],
         attr_name[MAX_HC + 1],
         attr_val[MAX_AV + 1],
         name[MAX_N + 1],
         src[MAX_DF + 1],
         alt[MAX_DF + 1];
    char ch;
    int ln = 1;
    link_t *link = in_file->link;
    label_name[0] = '\0';

    DEBUG_P3("Scan %s %d %d\n", html_fn, first, in_file->nr_refs);

    in_html = FALSE;
    in_head = FALSE;
    in_title = FALSE;
    in_body = FALSE;
    in_address = FALSE;
    in_header = FALSE;
    in_desc_label = FALSE;
    no_copy = 1;
    ignore_header = 0;
    in_math = 0;
    in_verb = 0;
    in_alltt = 0;
    first_label = TRUE;
    active_label = FALSE;
    after_first = FALSE;
    no_header = TRUE;
    no_title = TRUE;
    at_start = TRUE;
    active_href = FALSE;
    delayed_href = FALSE;
    href_included = TRUE;
    latex_fmt[0] = '\0';
    item_depth = 0;
    empty_line = TRUE;
    gen_newline = FALSE;
    empty_item = FALSE;
    no_item = FALSE;
    last_ref = NULL;
    add_level_depth = depth;

    if (in_file->exists)
    {   fin = fopen(html_fn, "rt");
        if (fin == NULL)    
            in_file->exists = FALSE;
    }
    if (!in_file->exists)
    {    if (freport != NULL)
         {  
             if (in_file->nr_refs > 1 || option_warn) 
                 fprintf(freport, "%s (0) : does not exist\n", html_fn);

             if (option_info)
             {   errors_ref_bys(freport, in_file->ref_by, html_fn, 0, FALSE);
                 errors_links_names(freport, in_file->link, html_fn);
             }
         }
         if (fout != NULL)
             fprintf(freport, "%% html: Cannot include file `%s'\n", html_fn);
         return;
    }
    if (!first && freport != NULL && option_warn)
    {   errors_ref_bys(freport, in_file->ref_by, html_fn, 0, TRUE);
        if (option_warn)
            errors_links_names(freport, in_file->link, html_fn);
    }

    in_file->read |= R_READ;
    if (included)
        in_file->read |= R_INCLUDED;

    if (fout)
        fprintf(fout, "%% html: Beginning of file: `%s'\n", html_fn);

    if ((ch = (char)fgetc(fin)) == '\n') ln++;

    while(!feof(fin))
    {   
        if (ch == '<')
        {   bool is_comment = FALSE,
                 a_name = FALSE,
                 a_href = FALSE,
                 a_src = FALSE;
            byte tagnr,
                 tagkind = T_ILL;
            bool closing_tag = FALSE;
            latex_repl = FALSE;
            alt[0] = '\0';

            /* SCAN <...> */ 

            /* skip < and following spaces: */
            if ((ch = (char)fgetc(fin)) == '\n') ln++;
            while (!feof(fin) && (ch == ' ' || ch == '\n'))
                if ((ch = (char)fgetc(fin)) == '\n') ln++;

            html_com[0] = '\0';

            if (ch != '!')
            {   int i;
                bool too_long;

                /* scan first word in html_com: */
                i = 0;
                too_long = FALSE;
                while (   !feof(fin) && ch != '>' 
                       && ch != ' ' && ch != '\n' && ch != '\t')
                {   if (i < MAX_HC)
                        html_com[i++] = tolower(ch);
                    else 
                        too_long = TRUE;
                    if ((ch = (char)fgetc(fin)) == '\n') ln++;
                }
                html_com[i] = '\0';
                if (too_long && freport != NULL)
                    fprintf(freport, 
                            "%s (%d) : HTML tag name too long --- `%s'\n",
                            html_fn, ln, html_com);

                for (tagnr = 0; tagnr < NR_TAGS; tagnr++)
                    if (streq(html_com, tags[tagnr].name))
                    {   tagkind = tags[tagnr].kind;
                        DEBUG_P2("found `%s' = %d\n", 
                                 tags[tagnr].name, tagkind);
                        break; 
                    }
                    else if (   html_com[0] == '/' 
                             && tags[tagnr].closing != C_NO
                             && streq(html_com + 1, tags[tagnr].name))
                    {   tagkind = tags[tagnr].kind;
                        closing_tag = TRUE;
                        DEBUG_P2("found `/%s' = %d\n", 
                                 tags[tagnr].name, tagkind);
                        break;
                    }

                while (!feof(fin) && ch != '>')
                {   bool found_is = FALSE;

                    skip_spaces(fin, html_fn, fout, freport, &ch, &ln, first);

                    if (feof(fin) || ch == '>')
                        break;

                    /* scan attribute in attr_name */
                    i = 0;
                    too_long = FALSE;
                    while (!feof(fin) && ch != '>' && ch != '=' && ch != ' '
                           && ch != '\n' && ch != '\t')
                    {   if (i < MAX_HC)
                            attr_name[i++] = tolower(ch);
                        else
                            too_long = TRUE;
                        if ((ch = (char)fgetc(fin)) == '\n') ln++;
                    }
                    attr_name[i] = '\0';

                    DEBUG_P1("found attribute: `%s'\n", attr_name);

                    if (too_long && freport != NULL)
                        fprintf(freport,
                                "%s (%d) : HTML attribute '%s' too long.\n",
                                html_fn, ln, attr_name);

                    /* skip = and spaces */
                    while (   !feof(fin) 
                           && (   ch == ' ' || ch == '\n' || ch == '='
                               || ch == '\t'))
                    {   if (ch == '=')
                            found_is = TRUE;
                        if ((ch = (char)fgetc(fin)) == '\n') ln++;
                    }

                    /* scan string into name */
                    i = 0;

                    if (found_is)
                    {   bool is_quoted = ch == '"';

                        too_long = FALSE;
                        if (is_quoted)
                            if ((ch = (char)fgetc(fin)) == '\n') ln++;
                        while(   !feof(fin) && ch != '>' && ch != '"'
                              && (is_quoted || ch != ' '))
                        {   if (i < MAX_AV)
                                attr_val[i++] = ch;
                            else
                                too_long = TRUE;
                            if ((ch = (char)fgetc(fin)) == '\n') ln++;
                        }
                        if (is_quoted != (ch == '\"') && freport != NULL)
                            fprintf(freport,
                                    "%s (%d) : incorrectly quoted string\n",
                                    html_fn, ln);
                        if (ch == '\"')
                            if ((ch = (char)fgetc(fin)) == '\n') ln++;
                        if (too_long && freport != NULL)
                            fprintf(freport, 
                                    "%s (%d) : attr value too long name `%s'\n",
                                    html_fn, ln, attr_val);
                    }
                    attr_val[i] = '\0';

                    DEBUG_P1("found attribute value: `%s'\n", attr_val);

                    if (OPEN_TAG(T_A) && streq(attr_name, "name"))
                    {   if (attr_val[0] == '\0')
                        {   if (freport != NULL)
                                 fprintf(freport,
                                         "%s (%d) : found <a name=\"\">\n",
                                         html_fn, ln);
                        }
                        else if (strlen(attr_val) > MAX_N)
                        {   if (freport != NULL)
                                 fprintf(freport,
                                         "%s (%d) : name too long `%s'\n",
                                         html_fn, ln, attr_val);
                        }
                        else 
                        {   strcpy(name, attr_val);
                            a_name = TRUE;
                        }
                    }
                    else if (OPEN_TAG(T_A) && streq(attr_name, "href")
                             && attr_val[0] != '\0')
                    {   char *av = attr_val;
                        i = 0;
                        too_long = FALSE;

                        for (; *av != '\0' && *av != '#'; av++)
                            if (i < MAX_DF)
                                dest_file[i++] = *av;
                            else
                                too_long = TRUE;
                        dest_file[i] = '\0';
                        DEBUG_P1("found dest file `%s'\n", dest_file);
                        href_name[0] = '\0';
                        if (attr_val[0] == '\0')
                        {   if (freport != NULL)
                                fprintf(freport,
                                        "%s (%d) : found <a href=\"\">\n",
                                        html_fn, ln);
                        }
                        else if (too_long)
                        {   if (freport != NULL)
                                fprintf(freport,
                                        "%s (%d) : URL too long `%s'\n",
                                        html_fn, ln, dest_file);
                        }
                        else if (*av == '\0')
                            a_href = TRUE;
                        else
                        {   i = 0;
                            too_long = FALSE; 
                            av++;
                            for (; *av != '\0'; av++)
                                if (i < MAX_N)
                                    href_name[i++] = *av;
                                else
                                    too_long = TRUE;
                            href_name[i] = '\0';
                            DEBUG_P1("found href name `%s'\n", href_name);
                            if (too_long)
                            {   if (freport != NULL)
                                    fprintf(freport,
                                            "%s (%d) : name too long `%s'\n",
                                            html_fn, ln, href_name);
                            }
                            else 
                                a_href = TRUE;
                        }
                    }
                    else if (   OPEN_TAG(T_IMG) && streq(attr_name, "src")
                             && attr_val[0] != '\0')
                    {   if (strlen(attr_val) > MAX_DF)
                        {   if (freport != NULL)
                                 fprintf(freport,
                                         "%s (%d) : src too long `%s'\n",
                                         html_fn, ln, attr_val);
                        }
                        else 
                        {   strcpy(src, attr_val);
                            a_src = TRUE;
                        }
                    }
                    else if (   OPEN_TAG(T_IMG) && streq(attr_name, "alt")
                             && attr_val[0] != '\0')
                    {   if (strlen(attr_val) > MAX_DF)
                        {   if (freport != NULL)
                                 fprintf(freport,
                                         "%s (%d) : alt too long `%s'\n",
                                         html_fn, ln, attr_val);
                        }
                        else 
                            strcpy(alt, attr_val);
                    }
                    else if (OPEN_TAG(T_META))
                        /* ignore */;
                    else if (   option_warn && freport != NULL 
                             && tagkind != T_ILL)
                        fprintf(freport, 
                                "%s (%d) : ignored <%s .. %s=\"%s\">\n" ,
                                html_fn, ln, html_com, attr_name, attr_val);

                }
            }
            else /* ch == '!' */
            {   int i = 0;

                is_comment = TRUE;
                if ((ch = (char)fgetc(fin)) == '\n') ln++;

                skip_spaces(fin, html_fn, fout, freport, &ch, &ln, first);

                if (ch != '>')
                {   if (freport != NULL && option_warn)
                        fprintf(freport,
                                "%s (%d) : using non-standard comments.\n",
                                html_fn, ln);

                    while (!feof(fin) && ch != '>')
                    {   add_to_comment(ch, &i);
                        if ((ch = (char)fgetc(fin)) == '\n') ln++;
                    }
                    add_to_comment('\0', &i);
                    while (i > 0 && comment[i - 1] == '-')
                        comment[--i] = '\0';

                    process_comment(html_fn, ln, fout, freport, comment, first);
                }
            } 

            /* skip till > */
            while (!feof(fin) && ch != '>')
                if ((ch = (char)fgetc(fin)) == '\n') ln++;

            /* PROCESS references */
            if (first)
            {   if (a_name)
                    add_name(html_fn, name,
                             is_html_fn || (!no_copy && !in_verb) || in_head);
                if (a_href)
                {   href_status = REF_OKAY;
                    if (!norm_URL(html_fn, dest_file))
                    {   if (freport != NULL)
                            fprintf(freport, 
                                   "%s (%d) : URL `%s' illegal or too long\n",
                                    html_fn, ln, dest_file);
                    }   
                    else
                    {   add_ref(html_fn, ln, dest_file,
                                href_name[0] == '\0' ? NULL : href_name);
                        /* to add dest_file to list of files: */
                        find_file(dest_file);
                    }
                }
            }
            else 
            {   if (a_name)
                {   DEBUG_P("<a name>\n");
                    if (freport != NULL && link->info.name.repeated)
                        fprintf(freport, 
                                "%s (%d) : <a name=\"%s\"> repeated.\n",
                                html_fn, ln, name);
                    if (   option_info && freport != NULL
                        && link->info.name.ref_by == NULL)
                        fprintf(freport,
                         "%s (%d) : <a name=\"%s\"> might not be referenced.\n",
                                html_fn, ln, name);
                    if (   freport != NULL && !is_html_fn && !link->copied
                        && link->info.name.referenced)
                        fprintf(freport,
                   "%s (%d) : <a name=\"%s\"> referenced, but not outputted.\n",
                                html_fn, ln, name);
                    if (freport != NULL)
                    {   DEBUG_P3( "%s (%d) : found <A NAME=\"%s\">\n",
                                    html_fn, ln, name);
                        {   ref_by_t *rb = link->info.name.ref_by;
                            for (; rb != NULL; rb = rb->next)
                                DEBUG_P2(" %s %s\n",
                                        rb->file, rb->name ? rb->name : "NULL");
                        }
                        if (option_warn)
                            errors_ref_bys(freport, link->info.name.ref_by,
                                           html_fn, ln, TRUE);
                    }
                    DEBUG_P2("name: |%s|%s|\n", name, link->info.name.name);
                    link = link->next;
                }
                if (a_href)
                {   DEBUG_P2("<a href %s %s>\n", html_fn, dest_file);
                    if (!norm_URL(html_fn, dest_file))
                    {   href_status = REF_ILL;
                        if (freport != NULL)
                            fprintf(freport, 
                                    "%s (%d) : URL `%s' illegal or too long.\n",
                                    html_fn, ln, dest_file);
                    }
                    else
                    {   href_status = find_ref(dest_file, href_name);
                        if (   href_status == REF_FILE_NOT_FOUND
                            && freport != NULL
                            && (   option_warn 
                                || link->info.ref.file->nr_refs < 2))
                            fprintf(freport, 
                                    "%s (%d) : file `%s' does not exist.\n",
                                    html_fn, ln, dest_file);
                        else if (   href_status == REF_FILE_NOT_INC
                                 && dest_file[0] != '\0' && freport != NULL
                                 && option_info && link->copied)
                            fprintf(freport, 
                                    "%s (%d) : file `%s' not included.\n",
                                    html_fn, ln, dest_file);
                        else if (   href_status == REF_NAME_NOT_FOUND
                                 && freport != NULL)
                        {   fprintf(freport,
                                "%s (%d) : no <a name=\"%s\"> in file `%s'.\n",
                                    html_fn, ln, href_name, dest_file);
                            if (   link->info.ref.re_name != NULL
                                && link->info.ref.re_name != c_top)
                                fprintf(freport,
                           "%s (%d) : could change into: <a href=\"%s#%s\">.\n",
                                        html_fn, ln,
                                        rel_URL(html_fn, dest_file),
                                        link->info.ref.re_name);
                        }
                        else if (   href_status == REF_NAME_NOT_INC
                                 && freport != NULL && link->copied)
                            fprintf(freport, 
                      "%s (%d) : <a name=\"%s\"> in file `%s' not outputted.\n",
                                    html_fn, ln, href_name, dest_file);
                        else if (   option_warn
                                 && href_status == REF_OKAY
                                 && link->info.ref.re_name != NULL
                                 && !eq_name(link->info.ref.re_name, href_name))
                             if (link->info.ref.re_name != c_top)
                                 fprintf(freport,
                           "%s (%d) : could change into: <a href=\"%s#%s\">.\n",
                                         html_fn, ln,
                                         rel_URL(html_fn, dest_file),
                                         link->info.ref.re_name);
                             else
                                 fprintf(freport,
                              "%s (%d) : could change into: <a href=\"%s\">.\n",
                                         html_fn, ln,
                                         rel_URL(html_fn, dest_file));
                    }
                    DEBUG_P2("href: |%s|%s|\n", dest_file, 
                                 link->info.ref.name);
                    link = link->next;
                }
            }

            /* PROCESS <...> */ 
            DEBUG_P4("found %s at %d: in_head %d: %d\n",
                     tags[tagnr].name, ln, in_head, tagkind);
            if (is_comment)
                /* skip */;
            else if (tagkind == T_ILL)
            {   if (freport != NULL)
                    fprintf(freport, "%s (%d) : unknown <%s>.\n",
                            html_fn, ln, html_com);
                    if(fout)
                    {    if(attr_name)
                            fprintf(fout, "\n%% <%s %s=\"%s\">\n", html_com, attr_name, attr_val); 
                        else
                            fprintf(fout, "\n%%>\n", html_com); 
                    }
            }
            else if (OPEN_TAG(T_HTML))
                if (in_html) 
                    REMOVE_TAG(", tag only inside <html>");
                else
                    LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_HTML))
                if (!in_html)
                    REMOVE_TAG(", not inside <html>");
                else
                    LATEX_CLOSES(tagnr)
            else 
            {   if (!in_html)
                {   if (option_pedantic) 
                        ADD_TAG(H_HTML, FALSE, ", tag requires <html>");
                    LATEX_OPEN(H_HTML)
                }
       /*** indention -4 ***/
            if (OPEN_TAG(T_HEAD))
                if (in_head)
                    REMOVE_TAG(", tag only outside <head>");
                else
                    LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_HEAD))
                if (!in_head)
                    REMOVE_TAG(", not inside <head>");
                else
                    LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_TITLE))
                if (in_body)
                    REMOVE_TAG(", tag not inside <body>");
                else if (in_title)
                    REMOVE_TAG(", nested <title>");
                else
                    LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_TITLE))
                if (in_body)
                    REMOVE_TAG(", tag not inside <body>");
                else if (!in_title)    
                    REMOVE_TAG(", not inside <title>");
                else
                    LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_BODY))
                if (in_body)
                    REMOVE_TAG(", nested <body>");
                else if (in_head)
                    REMOVE_TAG(", still inside <head>");
                else
                    LATEX_OPEN(tagnr)
                    /* print file name here ??? */
                    /* \n\\par{\\footnotesize$(File:\\   )$}\\par\n */
            else if (CLOSE_TAG(T_BODY))
                if (!in_body)
                    REMOVE_TAG(", not inside <body>");
                else if (in_head)
                    REMOVE_TAG(", still inside <head>");
                else
                    LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_LINK) || OPEN_TAG(T_META))
            {   /* ignore */
            }
            else if (OPEN_TAG(T_SCRIPT))
                LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_SCRIPT))
                LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_STYLE))
                LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_STYLE))
                LATEX_CLOSES(tagnr)
            else
            {   
                if (in_head && !a_name)
                {   char mess[60];
                    sprintf(mess, ", required by <%s>", tags[tagnr].name);
                    ADD_TAG(H_HEAD, TRUE, mess);
                    LATEX_CLOSES(H_HEAD)
                }
                if (!in_body && !a_name)
                {   char mess[60];
                    sprintf(mess, ", required by <%s>", tags[tagnr].name);
                    ADD_TAG(H_BODY, FALSE, mess);
                    LATEX_OPEN(H_BODY)
                }

       /*** indention -4 ***/
            if (OPEN_TAG(T_DIR))
                LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_DIR))
                LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_ADDR))
                if (in_address)    
                    REMOVE_TAG(", nested <address>");
                else
                    LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_ADDR))
                if (!in_address)    
                    REMOVE_TAG(", not inside <address>");
                else
                    LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_H))
                if (in_header)
                {   REPLACE_TAG();
                    LATEX_CLOSES_K()
                }
                else
                    LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_H))
                if (!in_header)
                    REMOVE_TAG(", not inside <h?>");
                else 
                {   LATEX_CLOSES_K()
                }
            else if (OPEN_TAG(T_LIST))
                LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_LIST))
                LATEX_CLOSES_K()
            else if (OPEN_TAG(T_ITEM))
                if (!inside_tag(T_LIST))
                    REMOVE_TAG(", not inside listing tag");
                else
                {   LATEX_CLOSES_T(T_LIST)
                    LATEX_OPEN(tagnr)
                }
            else if (CLOSE_TAG(T_ITEM))
                LATEX_CLOSES_K()
            else if (OPEN_TAG(T_DESC))
                LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_DESC))
                LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_DT))
                if (!inside_tag(T_DESC))
                    REMOVE_TAG(", not inside <dl>");
                else
                {   LATEX_CLOSES_T(T_DESC)
                    LATEX_OPEN(tagnr) 
                }
            else if (CLOSE_TAG(T_DT))
                LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_DD))
                if (!inside_tag(T_DESC))
                    REMOVE_TAG(", not inside <dl>");
                else
                {   LATEX_CLOSES_T(T_DESC)
                    LATEX_OPEN(tagnr)
                }
            else if (CLOSE_TAG(T_DD))
                LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_A))
            {   int j;

                for (j = stack_depth - 1;
                     j >= 0 && stack[j].closing == C_OPT; j--)
                    if (stack[j].tagkind == T_A) 
                    {   LATEX_CLOSES(H_A);
                        break; 
                    }

                if (   a_name && (!no_copy || in_head)
                    && name_referenced(html_fn, name))
                {   if (active_label && fout != NULL)
                        if (in_verb)
                        {   if (freport)
                                fprintf(freport,
                               "%s (%d) : <A NAME=\"%s\"> ignored in LaTeX.\n",
                                        html_fn, ln, label_name);
                        }
                        else
                            print_label(fout, in_file->nr, label_name, 
                                        FALSE);
                    active_label = TRUE;
                    strcpy(label_name, name);
                }
                if (a_href && !no_copy && href_status == REF_OKAY)
                {   if (active_href && freport != NULL)
                        fprintf(freport,
                                "%s (%d) : nested href\n", html_fn, ln);
                    active_href = TRUE;
                    atext_len = 0;
                }
                LATEX_OPEN_C(tagnr, a_href ? C_YES : C_OPT);
            }
            else if (CLOSE_TAG(T_A))
            {   if (active_href)
                {   atext[atext_len] = '\0';
                    deter_kind_of_URL(dest_file);
                    if (is_html_fn)
                        href_included = TRUE;
                    else if (no_copy || in_verb || in_e_alltt || in_e_header)
                        href_included = FALSE;
                    else
                    {   href_included = TRUE;
                        switch(kind_of_URL)
                        {   case URL_mailto:
                                DEBUG_P2("mailto:%s %s\n", email, atext);
                                if (strstr(atext, email))
                                    href_included = !opt_dni_email;
                                break;
                            case URL_news:
                                DEBUG_P2("news:%s %s\n", newsgroup, atext);
                                if (strstr(atext, newsgroup))
                                    href_included = !opt_dni_news;
                                break;
                            case URL_ftp:
                                if (   strstr(atext, ftp_site)
                                    && (   ftp_dir[0] == '\0'
                                        || strstr(atext, ftp_dir))
                                    && (   ftp_file[0] == '\0'
                                        || strstr(atext, ftp_file)))
                                    href_included = !opt_dni_ftp;
                                break;
                            case URL_other:
                                if (strstr(atext, dest_file))
                                    href_included = !opt_dni_other;
                                break;
                        }
                    }
                    if (last_ref != NULL)
                        last_ref->copied = href_included;
                }
                LATEX_CLOSES(tagnr)
            }
            else if (OPEN_TAG(T_VERB))
                LATEX_OPEN(tagnr)
            else if (CLOSE_TAG(T_VERB))
                LATEX_CLOSES_K()
            else if (OPEN_TAG(T_IMG))
            {   if (a_src)
                    if (!norm_URL(html_fn, src)) 
                    {   if (freport != NULL)
                            fprintf(freport, 
                                    "%s (%d) : URL `%s' illegal or too long.\n",
                                    html_fn, ln, src);
                    }
                    else
                    {
                        file_t *src_file = find_file(src) ;
                        if (first)
                            src_file->nr_refs++;
                        else if (!is_URL(src) && !src_file->exists)
                        {
                            if ( freport != NULL
                                 && (   option_warn
                                     || src_file->nr_refs < 2))
                                 fprintf(freport,
                                        "%s (%d) : file `%s' does not exist.\n",
                                         html_fn, ln, src);
                        }
                        else if (fout && !no_copy)
                        {
                            if (tags[H_IMG].latex_open[0] != '\0')
                                fprintf(fout,"%s%s%s",
                                        tags[H_IMG].latex_open, src,
                                        tags[H_IMG].latex_close);
                            else
                            {   char *s = src + strlen(src);
                                while (s > src && *(s - 1) != '/')
                                    s--;
                                print_f_img(fout, src, s, alt, REF_FILE_NOT_INC,
                                            in_header > 0, 
                                            freport, html_fn, ln);
                                /* maybe not always fragil environment */
                            }
                        }
                    }
            }
            else if (OPEN_TAG(T_P))
            {   if (stack[stack_depth-1].tagkind == T_P)
                    LATEX_CLOSES(H_P);
                if (in_header && freport != NULL && option_info)
                    fprintf(freport, "%s (%d) : <p> ignored in header\n",
                            html_fn, ln);
                LATEX_OPEN(tagnr)
            }
            else if (CLOSE_TAG(T_P))
                LATEX_CLOSES(tagnr)
            else if (OPEN_TAG(T_CHAR))
            {
                if (tagnr == H_FONT || tagnr == H_CODE)
                {
                    LATEX_OPEN(tagnr) // FONT may be nested
                }
                else
                {   int j;
                    bool found = FALSE;
    
                    for (j = stack_depth - 1; j >= 0; j--)
                        if (stack[j].tagnr == tagnr)
                        {   found = TRUE;
                            break;
                        }
    
                    if (found && j == stack_depth - 1)
                    {   REPLACE_TAG();
                        LATEX_CLOSES(tagnr)
                    }
                    else
                    {   if (found && freport != NULL)
                           fprintf(freport, "%s (%d) : nested <%s>\n",
                                   html_fn, ln, html_com);
                        LATEX_OPEN(tagnr)
                    }
                }
            }
            else if (CLOSE_TAG(T_CHAR))
                LATEX_CLOSES(tagnr)
            else
            {   if (freport != NULL)
                    fprintf(freport, "%s (%d) : tag %s not processed\n",
                            html_fn, ln, tags[tagnr].name);
            }
       /*** indention +4 ***/
            }
       /*** indention +4 ***/
            }

            /* read > and skip till first non-space */
            if (!feof(fin) && ch == '>')
            {   if ((ch = (char)fgetc(fin)) == '\n') ln++;

                if (   active_href && (ch == ' ' || ch == '\n' || ch == '\t')
                    && atext_len < MAX_AT)
                     atext[atext_len++] = ' ';

                while (!feof(fin) && (ch == ' ' || ch == '\n' || ch == '\t'))
                {   if (fout != NULL && !no_copy)
                        if (ch == '\n')
                        {   if (in_verb || in_alltt)
                            {   DEBUG_GN('V');
                                fputc('\n', fout);
                            }
                            else if (!empty_line && !in_desc_label)
                            {   DEBUG_GN('T');
                                gen_newline = TRUE;
                            }
                        }
                        else
                        {   if (gen_newline)
                            {   DEBUG_GN('2');
                                fputc('\n', fout);
                                gen_newline = FALSE;
                                empty_line = TRUE;
                            }
                            fputc(ch, fout);
                        }
                    if ((ch = (char)fgetc(fin)) == '\n') ln++;   
                }
            }
        }
        else 
        {   if (active_label && !in_header && after_first)
            {   if (fout != NULL)
                    print_label(fout, in_file->nr, label_name, FALSE);
                active_label = FALSE;
            }
            if  (ch == '\n')
            {   if (in_verb || in_alltt)
                {   DEBUG_GN('V');
                    if (fout != NULL && !no_copy)
                        fputc('\n', fout);
                }
                else if (!empty_line && !in_desc_label)
                {   DEBUG_GN('T');
                    gen_newline = TRUE;
                }
                if ((ch = (char)fgetc(fin)) == '\n') ln++;
            }
            else 
            {   int i = 0;
                if (no_item)
                {   if (fout != NULL && !no_copy)
                        fputs(opt_empty_item, fout);
                    no_item = FALSE;
                }
                if (   gen_newline && fout != NULL
                    && (   (!empty_line && !in_desc_label)
                        || in_verb || in_alltt))
                {   fputc('\n', fout);
                    gen_newline = FALSE;
                    empty_line = TRUE;
                }
                while (!feof(fin) && ch != '<' && ch != '\n')
                {   if (ch != ' ' && ch != '\t' && !no_copy)
                    {   empty_line = FALSE;
                        empty_item = FALSE;
                    }
                    if (active_href && atext_len < MAX_AT)
                        atext[atext_len++] = ch;
                    else
                      add_to_comment(ch, &i);
                    ch = (char)fgetc(fin);
                }
                add_to_comment('\0', &i);
                if (no_header && !no_copy && !empty_line && fout != NULL)
                    print_sp(fout, opt_no_header, html_fn);
                print_str(no_copy ? NULL : fout, comment, freport, html_fn,
                          ln, in_math, in_verb, in_alltt);
                if (ch == '\n') ln++;
            }
        }
    }
    /* In case no header occured, dump label */
    close_header(fout, html_fn);
    while (stack_depth > 0)
    {   if (   freport != NULL
            && (!option_pedantic || stack[stack_depth-1].tagnr != T_HTML))
            fprintf(freport, "%s (%d) : add </%s>.\n", 
                             html_fn, ln, 
                             tags[stack[stack_depth-1].tagnr].name);
        latex_close(fout, freport, ln, html_fn);
    }
    fclose(fin);
    if (fout != NULL)
        fprintf(fout, "\n%% html: End of file: `%s'\n", html_fn);
}

void check_exists_file(char *html_fn, FILE *freport)
{
    file_t *in_file = find_file(html_fn);

    if (in_file->exists)
    {   FILE *fin = fopen(html_fn, "rt");
        if (fin == NULL)
            in_file->exists = FALSE;
        else
            fclose(fin);
    }
    if (!in_file->exists)
    {    if (freport != NULL)
         {
             if (in_file->nr_refs > 1 || option_warn)
                 fprintf(freport, "%s (0) : does not exist\n", html_fn);
         }
    }

    in_file->read |= R_READ;
}


void accept_root_URL(URL, fout, freport) char *URL; FILE *fout, *freport;
{   int strlen_URL = strlen(URL);                 

    document_URL = NALLOC(char, strlen_URL + 2);
    strcpy(document_URL, URL);
    if (document_URL[strlen_URL - 1] != '/')
    {   document_URL[strlen_URL] = '/';
        document_URL[strlen_URL + 1] = '\0';
    }
    server_URL = NULL;
    {   int i;
        for (i = 0; URL[i] != '\0' && URL[i] != ':'; i++);
        if (URL[i] != '\0' && URL[i+1] == '/' && URL[i+2] == '/')
        {   i += 3;
            while (URL[i] != '\0' && URL[i] != '/')
                i++;
            if (URL[i] == '/')    
                file_URL = document_URL + i;
            else
                file_URL = "/";
            URL[i] = '\0';
            server_URL = SALLOC(URL);
            strcpy(server_URL, URL);
        }
    }
    if (server_URL == NULL)
    {   if (fout != NULL)
            fprintf(fout, "%%html: illegal URL `%s'\n", document_URL);
        if (freport != NULL)
            fprintf(freport, " : illegal URL `%s'\n", document_URL);
        document_URL = NULL;
    }
}

void parse_URL(fin, refch, buffer)
FILE *fin;
char *refch;
char *buffer;
{
    int i = 0;
    char ch = *refch;
    while (!feof(fin) && ch == ' ')
        ch = (char)fgetc(fin);
    if (ch=='\'')
    {
        ch = (char)fgetc(fin);
        while (!feof(fin) && ch != '\'' && ch != '\n')
        {   if (i < MAX_SF)
                buffer[i++] = ch;
            ch = (char)fgetc(fin);
        }
        if (ch == '\'')
            ch = (char)fgetc(fin);
    }
    else
    {
        while (!feof(fin) && ch != ' ' && ch != '\n')
        {   if (i < MAX_SF)
                buffer[i++] = ch;
            ch = (char)fgetc(fin);
        }
    }
    buffer[i] = '\0';
    
    *refch = ch;
}

void scan_input_file(FILE *fin, FILE *fout, FILE *freport, bool first, 
                     char *fn); 
void scan_input_file(fin, fout, freport, first, fn) 
FILE *fin, *fout, *freport;
bool first;
char *fn;
{   char ch,
         buffer[7];
    int ln = 1;

    DEBUG_P1("scan_input_file(,,,,%s)\n", fn);
    ch = (char)fgetc(fin);
    while(!feof(fin))
    {   int i;
        for (i = 0; i < 6 && !feof(fin) && ch != '\n' && ch != ' '; i++ )
        {   buffer[i] = ch;
            ch = (char)fgetc(fin);
        }
        buffer[i] = '\0';
        if (streq(buffer, "%html"))
        {   char html_file[MAX_SF + 1];   
            int  depth;

            while (!feof(fin) && ch == ' ')
                ch = (char)fgetc(fin);

            if (ch == '-')
            {   char buffer[MAX_SF + 1];

                ch = (char)fgetc(fin);
                if (ch == 'r')
                {   ch = (char)fgetc(fin);
                    parse_URL(fin, &ch, buffer);

                    accept_root_URL(buffer, fout, freport);
                }
                else if (ch == 'm' || ch == 'l')
                {   mapping_t *new = ALLOC(mapping_t);
                    bool is_link_mapping = ch == 'l';

                    ch = (char)fgetc(fin);
                    parse_URL(fin, &ch, buffer, MAX_SF);
                    
                    new->prefix = SALLOC(buffer);
                    strcpy(new->prefix, buffer);

                    parse_URL(fin, &ch, buffer, MAX_SF);

                    new->replace = SALLOC(buffer);
                    strcpy(new->replace, buffer);

                    if (new->prefix[0] != '\0')
                        if (is_link_mapping)
                        {   new->next = final_mappings;
                            final_mappings = new;
                        }
                        else
                        {   new->next = link_mappings;
                            link_mappings = new;
                        }
                }
                else if (ch == 'b')
                {   option_bibliography = TRUE; 
                    if (fout != NULL)
                        print_bibliography(fout);
                }
                else if (ch == 'd')
                {   int i = 0;
                    ch = (char)fgetc(fin);
                    while (ch != '\n')
                    {   add_to_comment(ch, &i);
                        ch = (char)fgetc(fin);
                    }
                    add_to_comment('\0', &i);
                    if (!first)
                        process_definition(freport, comment, fn, ln, FALSE);
                }
                else if (ch == 'o')
                {   int i = 0;
                    ch = (char)fgetc(fin);
                    while (ch != '\n')
                    {   add_to_comment(ch, &i);
                        ch = (char)fgetc(fin);
                    }
                    add_to_comment('\0', &i);
                    process_option(freport, comment, fn, ln, FALSE);
                }
                else if (ch == 's')
                {   int i = 0;
                    char style[21];

                    ch = (char)fgetc(fin);
                    while (ch == ' ')
                       ch = (char)fgetc(fin);
                    while (ch != '\n' && ch != ' ')
                    {   if (i < 20) 
                            style[i++] = tolower(ch);
                        ch = (char)fgetc(fin);
                    }
                    style[i] = '\0';
                    if (!first)
                        process_style(freport, style, fn, ln);
                }
                else if (ch == 'i')
                {   file_t *tfile;

                    ch = (char)fgetc(fin);
                    parse_URL(fin, &ch, html_file, MAX_SF);

                    tfile = find_file(html_file);
                    tfile->ignore = TRUE;
                }
                else
                {    if (fout != NULL)
                         fprintf(fout, "%%html: unknown option -%c\n", ch);
                     if (freport != NULL)
                         fprintf(freport, " : unknown option -%c\n", ch);
                }
            }
            else
            {
                parse_URL(fin, &ch, html_file, MAX_SF);

                while (!feof(fin) && ch == ' ')
                    ch = (char)fgetc(fin);
                depth = 1;
                if (isdigit(ch))
                    depth = ch - '0';

                scan_a_file(html_file, fout, freport, depth, first, TRUE);
            }
            while (!feof(fin) && ch != '\n')
                ch = (char)fgetc(fin);
            if (!feof(fin) && ch == '\n')
                ch = (char)fgetc(fin);
        }
        else
        {   if (fout != NULL)
                fprintf(fout, "%s", buffer);

            while (!feof(fin) && ch != '\n')
            {   if (fout != NULL)
                    fputc(ch, fout);
                ch = (char)fgetc(fin);
            }
            if (!feof(fin) && ch == '\n')
            {   if (fout != NULL)
                    fputc(ch, fout);
                ch = (char)fgetc(fin);
            }
        }
        ln++;
    }
}

void scan_not_included_files(freport, first, included) 
FILE *freport; bool first, included;
{
    if (first)
    {   bool found = TRUE;

        while (found)
        {   file_t *file = the_files;
            found = FALSE;

            while (file != NULL && !found)
            {   DEBUG_P4("%s %d %d %d ",
                            file->name, file->exists, !(file->read & R_READ),
                            !is_URL(file->name));
                DEBUG_P3("%d %d %d\n",
                            is_html(file->name),
                            file->name[0] != '.', file->name[1] != '.');
                if (   file->exists && !(file->read & R_READ)
                    && !is_URL(file->name)
                    && (file->name[0] != '.' || file->name[1] != '.'))
                    found = TRUE;
                else
                    file = file->next;
            }

            if (found)
            {
                if (is_html(file->name))
                    scan_a_file(file->name, NULL, freport, 1, first, included);
                else
                    check_exists_file(file->name, freport);
            }
        }
    }
    else
    {   file_t *file = the_files;

        for (file = the_files; file != NULL; file = file->next)
            if (   /* !(file->read & R_INCLUDED)
                &&*/ !is_URL(file->name)
                && is_html(file->name)
                && (file->name[0] != '.' || file->name[1] != '.'))
                scan_a_file(file->name, NULL, freport, 1, first, FALSE);
    }
}

int main(argc, argv)
int argc;
char **argv;
{   FILE *fin,
         *fout,
         *fref = NULL;
    char *fn = NULL,
         *html_fn,
         *outfn = NULL,
         *reffn;
    bool option_chk = streq( argv[0], "chkhtml" ),
         option_scan_not_inc = FALSE,
         option_cross_ref = FALSE;

    /* global options */
    option_info = FALSE;
    option_warn = FALSE;
    option_pedantic = FALSE;
    option_bibliography = FALSE;
    option_stdout = FALSE;

    calculate_all_el();

    /* Parse the command line options for -stdout */
    {   int i;

        for (i = 1; i < argc; i++)
            if (streq(argv[i], "-stdout"))
                option_stdout = TRUE;
    }

    if (!option_stdout)
        printf("%s: Version %s\nWritten by %s\n\n", 
               option_chk ? "chkhtml" : "html2tex", VERSION, WRITTEN_BY);

    /* Parse the command line options */
    {   int i;
        bool error = FALSE;

        for (i = 1; i < argc; i++)
        {   if (argv[i][0] == '-')
            {   if (argv[i][1] == 'o')
                {   if (argv[i][2] != '\0')
                        outfn = argv[i] + 2;
                    else if (i + 1 < argc)
                        outfn = argv[++i];
                    else
                        fprintf(stderr, "Argument of -o option missing\n");
                    if (option_stdout && outfn != 0)
                        fprintf(stderr, "Option -o is overruled by -stdout\n");
                }
                else if (argv[i][1] == 'i' && argv[i][2] == '\0') 
                {   option_warn = TRUE;
                    option_info = TRUE;
                }
                else if (argv[i][1] == 'w' && argv[i][2] == '\0')
                    option_warn = TRUE;
                else if (argv[i][1] == 'p' && argv[i][2] == '\0')
                    option_pedantic = TRUE;
                else if (argv[i][1] == 's' && argv[i][2] == '\0')
                    option_scan_not_inc = TRUE;
                else if (argv[i][1] == 'c' && argv[i][2] == '\0')
                    option_chk = TRUE;
                else if (argv[i][1] == 'r')
                {   if (argv[i][2] != '\0')
                        accept_root_URL(argv[i] + 2, stdout, NULL);
                    else if (i + 1 < argc)
                        accept_root_URL(argv[++i], stdout, NULL);
                    else
                        fprintf(stderr, "Argument of -r option missing\n");
                }
                else if (argv[i][1] == 'b' && argv[i][2] == '\0')
                    option_bibliography = TRUE;
#ifdef DYN_DEBUG
                else if (argv[i][1] == 'd')
                    option_debug = TRUE;
#endif
                else if (streq(argv[i], "-cr"))
                    option_cross_ref = TRUE;
                else if (streq(argv[i], "-stdout"))
                    ; // -- already processed
                else 
                {   fprintf(stderr, "Unknown option %s\n", argv[i]);
                    error = TRUE;
                }
            }
            else if (fn == NULL)
                fn = argv[i];
            else
            {   fprintf(stderr, "Too many input filenames\n");
                error = TRUE;
            }
        }
        if (fn == NULL)
        {   fprintf(stderr, "No input filename given\n");    
            error = TRUE;
        }
        else 
        {   fin = fopen(fn, "rt");

            if (fin == NULL)
            {   fprintf(stderr, "Error: Cannot open file: `%s'.\n", fn);
                error = TRUE;
            }
        }
        if (error)
        {   fprintf(stderr, "Usages: html2tex [options] <file>\n");
            fprintf(stderr, "\nOptions:\n");
            fprintf(stderr, " -o<FN> : specify output file\n");
            fprintf(stderr, " -i : print info\n");
            fprintf(stderr, " -w : print warnings (and info)\n");
            fprintf(stderr, " -r<URL> : root URL of document\n");
            fprintf(stderr, " -b : make bibliography\n");
            fprintf(stderr, " -cr : generate cross-reference\n");
            fprintf(stderr, " -c : check html file\n");
            fprintf(stderr, " -s : scan not included files\n");
            fprintf(stderr, " -stdout : output to stdout\n");
#ifdef DYN_DEBUG
            fprintf(stderr, " -d : print (a lot of) debugging information\n");
#endif
            return 1;
        }

        if (streq(fn + strlen(fn) - 5, ".html"))
        {   is_html_fn = TRUE;
            html_fn = SALLOC(fn);
            strcpy(html_fn, fn);
            fn[strlen(fn) - 5] = '\0';
        }

    }

    reffn = NALLOC(char, strlen(fn) + 5);
    strcpy(reffn, fn);
    strcat(reffn, ".ref");

    if (option_cross_ref)
    {   fref = fopen(reffn, "wt");

        if (fref == NULL)
            fprintf(stderr, "Error: Cannot open file: %s.\n", reffn);
    }

    /* Perform the first pass, during which information about
       the input files are collected. */
    init_opts();

    if (!is_html_fn)
        scan_input_file(fin, (FILE *)NULL, (FILE *)NULL, TRUE, fn);
    else
        scan_a_file(html_fn, (FILE *)NULL, (FILE *)NULL, 0, TRUE, TRUE);

    if (option_scan_not_inc)
        scan_not_included_files(NULL, TRUE, is_html_fn);

    {   file_t *file;
        for (file = the_files; file != NULL; file = file->next)
            file->read &= ~R_READ;
    }

    /* Resolve all cross references */
    make_by_refs();
    fill_re_names();

    /* Perform the second pass, during which the LaTeX output file
       is produced while parsing the input files. */
    rewind(fin);

    init_opts();

    if (!option_chk)
    {   
        if (outfn == NULL)
        {   outfn = NALLOC(char, strlen(fn) + 5);
            strcpy(outfn, fn);
            strcat(outfn, ".tex");
        }

        if (option_stdout)
            fout = stdout;
        else
        {
            fout = fopen(outfn, "wt");

            if (fout == NULL)
            {   fprintf(stderr, "Error: Cannot open file: %s.", outfn);
                return 1;
            }
        }
        
        fprintf(fout, "%% Generated by html2tex: Version %s\n%% Written by %s\n\n", 
               VERSION, WRITTEN_BY);

        if (!is_html_fn)
            scan_input_file(fin, fout, stderr, FALSE, fn);
        else
            scan_a_file(html_fn, fout, stderr, 1, FALSE, TRUE);
    }
    else
        scan_a_file(html_fn, (FILE *)NULL, stdout, 0, TRUE, TRUE);

    if (option_scan_not_inc)
        scan_not_included_files(stdout, FALSE, is_html_fn);

    DEBUG_P("ready reading\n");
    /* print_files(stdout);*/
    DEBUG_P("\n\n\n");

    /* errors_files(stdout); */
    if (fref)
    {   errors_files(fref);
        fprintf(fref, "\n----------------\n\n");
        print_files(fref);
    }

    return 0;
} 
