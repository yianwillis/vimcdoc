#!/bin/bash

version=VIMCDOC_`cat ../VERSION | sed -e 's/\./_/g'`
last_rev=`svn info ../../tags/$version | grep 'Last Changed Rev:' | cut -d ' ' -f 4`

# decect added new files since last tagged release
list=/tmp/vimcdoc-list.$$
added=/tmp/vimcdoc-added.$$
cd ../doc
ls > $list
ls ../../tags/$version/doc | comm -3 - $list > $added
if [ -s $added ]; then
	echo '>>>> NEW FILES SINCE LAST RELEASE <<<<'
	cat $added
	echo -e '\n'
fi
rm $list $added

# output updating info of various files
change=/tmp/vimcdoc-change.$$
echo '>>>> UPDATED FILES SINCE LAST RELEASE <<<'
for i in *.txt
do
    svn log -r $last_rev:HEAD  $i > $change
    len=`cat $change | wc -l`
    if [ $len -gt 1 ]; then
	    echo -e "~~~~\t$i\t~~~~"
	    cat $change
	    echo -e '\n'
    fi
done
rm $change
