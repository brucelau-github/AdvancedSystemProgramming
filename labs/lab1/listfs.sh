#!/bin/bash
# Write a bash-shell script to list all regular files in the current directory that are smaller than n bytes (n is an integer argument).
# Synopsis: listfs <directory_name> <n bytes>
#echo help message
if [ "$#" -ne "2" ]
then
  echo "Error: Please supply the directory name to use and the size n in bytes"
  echo "usage:listfs <directory_name> <size_n>"
  echo "list the files in a given <directory_name> that are smaller than n bytes"
  exit $?
fi
isDigit=$(echo "$2" | grep "[^0-9]")
if [ -n "$isDigit" ]
then
	echo "parameter error <size_n>: $2 is not a digit!"
	exit $?
fi
echo ""
dirname=$1
echo "the file list with size smaller than $2 bytes in $1 directory"
echo "-----------------------"

#find all files with limited size in this directory
filelist=$(find $1 -type f -size -$2c)

echo "$filelist"
echo ""
