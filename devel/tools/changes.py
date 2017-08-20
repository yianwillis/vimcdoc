#!/usr/bin/python
# vim:tw=78:ts=4:shiftwidth=4:noexpandtab:
# This is a python script to detect changes since the last release
# of vimcdoc. It makes an assumption that all releases are 'cvs tag'ed
# as 'VIMCDOC.*' (so that cvs branches will not confused as a release)
# and every argument is indeed a CVS file, i.e. 'cvs log' output is not
# garbage.
# Usage: ./changes.py <txt_file_name(s)>
# Author: lang2
# Note: You have to run this b4 you tag the release, otherwise it
# won't detect anything!
# Todo:
#	1. some of the nameing are very bad.
#	2. draw a state diagram maybe, since this is a state machine.


import re
import sys
import os
from string import upper

# global vars
log_file     = 'vimcdoc-trans.log'
FILE         = ''
head         = None
author       = None
fh           = None
last_log     = ''
last_tag     = None

new_files    = []
update_files = {}

#############
# StateMachine class definition
#############
class StateMachine:
	def __init__(self):
		self.handlers = {}
		self.startState = None
		self.endStates = []

	def add_state(self, name, handler, end_state=0):
		name = upper(name)
		self.handlers[name] = handler
		if end_state:
			self.endStates.append(name)

	def set_start(self, name):
		self.startState = upper(name)

	def run(self, cargo):
		try:
			handler = self.handlers[self.startState]
		except:
			raise "InitializationError", "must call .set_start() before .run()"
		if not self.endStates:
			raise "InitializationError", "at least one state must be an end_state"

		while 1:
			(newState, cargo) = handler(cargo)
			if upper(newState) in self.endStates:
				break
			else:
				handler = self.handlers[upper(newState)]


# function definitions
def prepare_log():
	global FILE

	if os.path.exists( log_file ):
		os.remove( log_file )

	cmd = 'cvs log'
	for f in sys.argv[1:]:
		cmd += ' ' + f
	cmd += ' > ' + log_file

	os.system( cmd )

##################
# individule state handlers
##################

# detect what file we are on
def detect_file(line):
	# Detec head head:1.3
	global fh
	global head
	global FILE

	#print 'State: detect_file'
	#print 'line= ' + line

	pat = re.compile( r'^Working file: (.*)$' )
	matobj = pat.match( line )
	if matobj != None:
		state = 'detect_head'
		FILE = matobj.group(1)
#		print FILE
	else:
		state = 'DETECT_FILE'

	line = fh.readline().rstrip()
	return ( state, line )

# detect cvs-head of the file
def detect_head(line):
	# Detec head head:1.3
	global fh
	global head

	#print 'State: detect_head'
	#print 'line= ' + line

	pat = re.compile( r'^head: (.*)$' )
	matobj = pat.match( line )
	if matobj != None:
		state = 'LAST_TAG'
		head = matobj.group(1)
	else:
		state = 'DETECT_HEAD'

	line = fh.readline().rstrip()
	return ( state, line )

def detect_last_tag( line ):
	global fh
	global head
	global last_tag

	#print 'State: detect_last_tag'
	#print 'line= ' + line

	if ( line ):
		pat = re.compile( r'^\tVIMCDOC.*: (.*)$' )
		matobj = pat.match( line )

		if matobj != None:
			last_tag = matobj.group(1)
			#print 'last_tag: %s' % last_tag

			if last_tag == head:
				state = 'END'
			else:
				state = 'LAST_ENTRY'
		else:
			state = 'LAST_TAG'

		line = fh.readline().rstrip()
	else:
		new_files.append( FILE )
		state = 'end'
	return ( state, line )

	#no line contains a <TAB> new file
	#print FILE[:-4]
	#print 'New file.'
	#state = -1

def detect_last_entry_start(line):
	global fh
	global head

	#print 'State: detect_last_entry_start'
	#print 'line= ' + line

	regex = '^revision ' + head + '$'
	pat = re.compile( regex )
	matobj = pat.match( line )
	if matobj != None:
		state = 'DETECT_AUTHOR'
	else:
		state = 'LAST_ENTRY'

	line = fh.readline().rstrip()
	return (state, line)


def detect_author(line):
	global fh
	global head
	global last_log

	#print 'State: detect_author'
	#print 'line= ' + line

	current_revision = None

	pat = re.compile( r'^revision (.*)$'  )
	matobj = pat.match( line )
	if matobj != None:
		if matobj.group(1) == last_tag:
			#print "\r"
			update_files[ FILE ] = last_log
			state = 'end'
		else:
			state = 'detect_author'
	else:
		#print line
		last_log += line + "\n"
		state = 'detect_author'

	line = fh.readline().rstrip()

	return (state,line)

# wrapper for the state machine
def analyse_single_file(file):
    global FILE
    global fh

    #print 'Process ' + FILE
    line = fh.readline().rstrip()

    #print "~~~~~\t" + FILE[:-4] + "\t~~~~~"
    m = StateMachine()
    m.add_state("detect_file", detect_file)
    m.add_state("detect_head", detect_head)
    m.add_state("last_tag", detect_last_tag)
    m.add_state("last_entry", detect_last_entry_start)
    m.add_state("detect_author", detect_author)
    m.add_state("end", None, end_state=1)
    m.set_start("detect_file")
    m.run(line)


##############################
# main
##############################
if __name__ == '__main__':
	if len (sys.argv) <= 1:
		print 'I need at least one filename to work.'
		sys.exit(1)

	prepare_log()

	fh = open( log_file )
	for f in sys.argv[1:]:
		last_log = ''
		FILE = ''
		analyse_single_file( f )
	fh.close()
	os.remove( log_file )

	print '>>>> NEW FILES SINCE LAST RELEASE <<<<'
	for x in new_files:
		print x

	print "\r"
	print '>>>> UPDATED FILES SINCE LAST RELEASE <<<<'
	for x in update_files:
		print "~~~~~\t" + x + "\t~~~~~"  
		print update_files[x]
