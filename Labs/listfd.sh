#!/bin/bash
# Write a bash-shell script to list the names of directories and files separately, and display the total number of directories and files.
# Synopsis: listfd <directory_name>
#handle input parameter error
#echo help message
dirname=$1
echo "the directories is $1"
dirlist=`ls -l $1`
echo $dirlist
