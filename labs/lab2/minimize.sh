#!/bin/bash
# write a bash-shell script to compress files, in the current directory 
# with some extensions
# Synopsis: minimize.sh <extension list>
# Example minimize.sh doc jpa text
# author: bruce lau
# email : brucelau.email@gmail.com
# At university of windsor in Canada on Jan 20, 2017
if [ $# -lt 1 ]
then
	echo "useage: minimize.sh <extension list>"
	echo "example: minimize.sh doc jpg txt. to compress all these files"
	exit 0
fi

if [ -e compress.tar ]
then
	echo ""
	echo "remove old file compress.tar"
	rm -f compress.tar
fi

for ext in $* 
do
	echo "handling files with extension $ext"
	tar rvf compress.tar --wildcards *.$ext
	echo "done"
	echo ""
done
