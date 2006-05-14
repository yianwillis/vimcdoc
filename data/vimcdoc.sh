#!/bin/sh
#
# vimcdoc.sh:	vimcdoc Linux install/uninstall script
#
# Usage: 		(run it as root)
#				'./vimcdoc.sh -i' to install vimcdoc
#				'./vimcdoc.sh -u' to uninstall vimcdoc
#
# Author:		wandys	(wandys@users.sf.net)
#				lang2	(lang2@users.sf.net)

if [ $# -ne 1 ]; then
	echo "Usage: $0 {-i|-u}"
	exit 1
fi

vim --cmd ":exec 'normal i' . \$VIM | wq! /tmp/vimrt.$$" > /dev/null 2>&1 
if [ -e /tmp/vimrt.$$ ]; then
	VIM_PATH=`cat /tmp/vimrt.$$`/vimfiles
	rm /tmp/vimrt.$$
else
	echo 'Error: No vim found on this system.'
	exit 1
fi

VIMCDOC_PATH_LINK=`echo $VIM_PATH|sed 's:vim.*$:doc/vimcdoc:'`
VIMCDOC_PATH=$VIMCDOC_PATH_LINK-`cat VERSION`
CNTAGS=tags-cn
DIST_FILES="README
guides.txt
LICENSE
TODO
VERSION
INSTALL
AUTHORS
dict.txt"
VIMCDOC_INST='vimcdoc.sh'
install_dist_files=0

if [ `whoami` = 'root' ]; then
	install_dist_files=1
else
	VIM_PATH=$HOME/.vim
fi

case $1 in
	-i)
	if [ $install_dist_files -eq 1 ]; then
		for i in $DIST_FILES; do
			if [ ! -d $VIMCDOC_PATH ]; then
				rm -f $VIMCDOC_PATH
				mkdir $VIMCDOC_PATH
			fi
			echo "install -m 644 $i $VIMCDOC_PATH/$i"
			install -m 644 $i $VIMCDOC_PATH/$i
		done
		echo "install -m 755 $VIMCDOC_INST $VIMCDOC_PATH/$VIMCDOC_INST"
		install -m 755 $VIMCDOC_INST $VIMCDOC_PATH/$VIMCDOC_INST
		ln -sf $VIMCDOC_PATH $VIMCDOC_PATH_LINK
	fi
	cd doc
	for i in *.cnx; do
		if [ ! -d $VIM_PATH/doc ]; then
			rm -f $VIM_PATH/doc
			mkdir -p $VIM_PATH/doc
		fi
		echo "install -m 644 $i $VIM_PATH/doc/$i"
		install -m 644 $i $VIM_PATH/doc/$i
	done
	echo "install -m 644 $CNTAGS $VIM_PATH/doc/$CNTAGS"
	install -m 644 $CNTAGS $VIM_PATH/doc/$CNTAGS
    cd ..
    if [ ! -d $VIM_PATH/syntax ]; then
		rm -f $VIM_PATH/syntax
		mkdir -p $VIM_PATH/syntax
    fi
    install -m 644 help_cn.vim $VIM_PATH/syntax/help_cn.vim
	echo 'Done.'
	;;

	-u)
	if [ $install_dist_files -eq 1 ]; then
		rm -rf $VIMCDOC_PATH $VIMCDOC_PATH_LINK
	fi
	if [ -d $VIM_PATH/doc ]; then
		cd $VIM_PATH/doc
		rm -f *.cnx $CNTAGS
	fi
	rm -f $VIM_PATH/syntax/help_cn.vim
	echo 'Done.'
	;;

    *)
	echo "Usage: $0 {-i|-u}"
	exit 1
	;;
esac

# vim:ts=4:sw=4:
# EOF
