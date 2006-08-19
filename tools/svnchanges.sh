#!/bin/bash
version=VIMCDOC_`cat ../VERSION | sed -e 's/\./_/g'`
last_rev=`svnversion ../../tags/$version`

cd ../doc
for i in *.txt;
do
    echo ~~~~ $i ~~~~
    svn log -r $last_rev:HEAD  $i | sed -e '/^-----/d' -e '/^r[0-9]\+/d'
done
