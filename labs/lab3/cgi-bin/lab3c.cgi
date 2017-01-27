#!/bin/bash
# Dr. Ziad Kobti (c)2017
# Lab 3c - sample sum

# load the library functions
source ./lab3lib.cgi

if [ "x$alertvalue" != "x" ]; then
  
  # This script does a very simple test for checking disk space.
  space=`df -h | awk '{print $5}' | grep % | grep -v Use | sort -n | tail -1 | cut -d "%" -f1 -`
  let gap=" 100 - $space "
  if [ "$space" -ge "$alertvalue" ]; then
    message2="At least one of my disks is nearly full!"
  else
    message2="Disk space normal at ${space}%"
  fi

cat <<EOFA
<html>
<body>
${message2}
<img src="http://kobti.myweb.cs.uwindsor.ca/lab3/1by1red.gif" height="20" width="${space}">
<img src="http://kobti.myweb.cs.uwindsor.ca/lab3/1by1green.gif" height="20" width="${gap}">
</body>
</html>
EOFA


else

cat <<EOFB
<html>
<body>
Enter the alert value for the disk space:<br/><br/>
<form action="?version=${version:=1}" method="POST" enctype="application/x-www-form-urlencoded">
Alert value: <input type="text" name="alertvalue" value="$alertvalue"><br/><br/>
<input type="submit">
</form>
</body>
</html>
EOFB

fi
