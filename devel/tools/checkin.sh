#!/bin/bash

ROOT="$(git rev-parse --show-toplevel)"
[[ $# == 1 ]] || exit 1
git commit -a -m "$1"
git push
cd "$ROOT"/devel/doc
aap -f main.aap allhtml
git checkout gh-pages
cp *.html *.css ../../doc
git commit -a -m "$1"
git push
git checkout master
