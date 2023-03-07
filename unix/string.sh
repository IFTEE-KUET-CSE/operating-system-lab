#!/bin/bash
read x1
len=${#x1}
i=0
while(($i<len))
do
	echo "$i"
	if [ ${x1:$i:1} -ls 'd' ]
	then
		echo "letter"
	fi
	i=$((i+1))
done
