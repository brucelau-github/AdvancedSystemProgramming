#!/bin/bash
# Write a bash-shell script to list the names of directories and files separately, and display the total number of directories and files.
# Synopsis: listfd <directory_name>

#handle input parameter error
#echo help message
if [ $# -ne 1 ]
then
  echo -e "Error: Please supply the directory name to use\n\
usage: listfd <directory_name>\n\
list the files and directories in a given <directory_name> along with their counts"
  exit $?
fi

#find all folders in this directory
dirlist=$(find $1 -type d)
dirnum=$(find $1 -type d | wc -l)
#minus current directory.
let "dirnum--"
echo "Directories in $1:"
echo "$dirlist"
echo ""

#find all files in this directory
filelist=$(find $1 -type f)
filenum=$(find $1 -type f | wc -l)

echo "Files in $1:"
echo "$filelist"
echo ""

echo "There are $dirnum directories and $filenum files"
echo ""
