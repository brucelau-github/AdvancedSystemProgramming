#!/bin/bash
# create a diectory with following structure.
#|-labtest1
#|- -foder1
#|- ---file11 0 byte
#|- ---file12 100 byte
#|- -folder2
#|- -folder3
#|- ---file31 50 byte

mkdir labtest1
mkdir labtest1/foder1
touch labtest1/foder1/file11
touch labtest1/foder1/file12
echo "The Linux Find Command is one of the most important and much used \
command in Linux sytems. Find command used to search and locate list of \
files and directories based on conditions you specify for files that match \
the arguments." > labtest1/foder1/file12
mkdir labtest1/foder2
mkdir labtest1/foder3
echo "The Linux Find Command is one of the most important and much used \
command in Linux sytems. " > labtest1/foder1/file31
