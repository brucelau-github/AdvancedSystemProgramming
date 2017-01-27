#!/bin/bash
# Dr. Ziad Kobti (c)2017
# Lab 3c - sample sum

# load the library functions
source ./lab3lib.cgi
outputs=`exec $cmd 2>&1 | sed 'a\<br/>' | sed 's/\s/\&nbsp/g'`
echo "$outputs"