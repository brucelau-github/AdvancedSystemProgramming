#!/bin/bash
# Jianye Liu 104522497
# Generante json

# Header tells browser what to expect.
echo "Content-Type:  application/json; charset=utf-8"
echo ""


cat <<EOFB
[
	{
	"cpu" : `top -b -n 2 -d 0.1 | awk '/Cpu/ {print $2}' | awk 'NR==2 {print}'`,
	"timestamp" : "`date +"%m-%d-%Y %H:%M:%S"`"
	}
]

EOFB

exit 0