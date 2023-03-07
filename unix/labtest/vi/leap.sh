#!/bin/bash
n=1
while(($n))
do
	read yr
	if [ $yr = 'E' ]
	then
		break
	fi
	var=$(( (yr%400==0) || (yr%4==0) && (yr%100!=0) ))
	if [ $var -eq 1 ]
	then
		echo "leap year"
	else
		echo "not leap year"
	fi
done
