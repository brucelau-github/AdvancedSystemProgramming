#!/bin/bash
# write a bash-shell script to calculate the Fibonacci numbers given by 
# if(n<2) f=n; else f= f(n-1)+f(n-2);
# author: bruce lau
# email : brucelau.email@gmail.com
# At university of windsor in Canada.
if [ $# -ne 1 ]
then
	echo "useage: fibonacci.sh <numbers>"
	exit 0
fi
if [ $1 -lt 2 ]
then 
	if [ $1 -eq 0 ]; then 
		echo "0"
	else 
		echo "0 1"
	fi

	echo "the fibonacci of $1 is $1"
	exit 0
fi

n=2
fib1=0
fib2=1
fib3=0
printf "0 1"
# calculate the fibonacci
while [ $n -le $1 ]
do
	fib3=$(( $fib1 + $fib2 ))
	fib1=$fib2
	fib2=$fib3
	let "n = $(( $n + 1 ))"
	printf " $fib3"
done
echo ""
echo "the fibonacci of $1 is $fib3"
