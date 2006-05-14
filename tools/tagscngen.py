#!/usr/bin/env python
# Python script for adapting a original tags file into vimcdoc 0.7.0+
# compatible.
# Usage: run inside 'tools' directory directly and will generate a
# tags-cn file

import os
import sys
import glob
from testtags import parse_tag_line
import logging

doc_dir = '../doc'
tags_file = '%s/tags' % doc_dir


class Vimcdoc:
    """Class for vimcdoc, including a dictionary for the translated
    documents. This is core. Information such as who's the author,
    etc, can be retrieved from this dictionary."""

    documents = []
    def __init__(self):
        for i in glob.glob1( doc_dir, '*.txt' ):
            #shamelessly take over all docs b4 we standardize the
            #author line
            self.documents.append( i )
        return

    def __repr__(self):
        return self.documents

    def __iter__(self):
        return self.iterator()

    def iterator(self):
        for i in self.documents:
            yield i


def txt2cnx(fn):
    """Transfer a *.txt filename to a *.cnx filename"""
    return os.path.splitext(fn)[0] + '.cnx'

def generate_tagscn_file():
    """ Generate a tags-cn file which can be used for release. The
    output file will be written to the current directory."""

    docs = Vimcdoc()
    try:
        fp = open( tags_file, 'r' )
        fp_out = open ('tags-cn', 'w')
        for i in fp:
            i = i.strip()
            taginfo = parse_tag_line( i )
            if taginfo["file"] in docs:
                fp_out.write( '%s\t%s\t%s\n' % \
                              ( taginfo["name"],\
                               txt2cnx(taginfo["file"]), \
                               '/'+taginfo["jump"] ) )
            else:
                print 'Deleted: %s' % i
    except IOError:
        print 'Error opening files.'
    except KeyError:
        pass
    else:
        fp.close()
        fp_out.close()


if __name__ == '__main__':
    logging.getLogger().setLevel( logging.DEBUG )
    generate_tagscn_file()
