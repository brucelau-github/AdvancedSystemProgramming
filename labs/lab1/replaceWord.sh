#!/bin/bash
# Write a bash-shell script to replace all occurrences of a word by another word in a file.
# Synopsis: replaceWord <inFile> <word> <repWord> <outFile>
if [ "$#" -ne "4" ]
  then
    echo "Error: Please supply all parameters"
    echo "usage: replaceWord<inFile> <word> <repWord> <outFile>"
    echo "replace all occurences of a word by another word in a file"
    exit $?
fi
if [ ! -f "$1" ]
  then
    echo "$1: No such file"
    exit $?
fi
echo ""
echo "before replace:"
echo "---------$1--------"
cat $1
sed "s/\b$2\b/$3/g" <$1 >$4
echo ""
echo "after replace:"
echo "--------$4----------"
cat $4
echo "====finished!======="
echo ""
