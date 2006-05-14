.phony: clean html

VIM2HTML = vim2html.pl
VIMDOCDIR = ../../../doc

html:
	${VIM2HTML} ${VIMDOCDIR}/tags ${VIMDOCDIR}/*.txt

%.html:${VIMDOCDIR}/%.txt
	${VIM2HTML} ${VIMDOCDIR}/tags $<
	

clean:
	rm -f *.html *~ *.css
