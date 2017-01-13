#!/bin/bash
# Write a bash-shell script to list the names of directories and files separately, and display the total number of directories and files.
# Synopsis: listfd <directory_name>
#handle input parameter error
#echo help message
isDigit=$(echo "$1" | grep "[^0-9]") 
if [ -z $isDigit ]
then
	echo "$1 is a digit"
fi
echo ""
