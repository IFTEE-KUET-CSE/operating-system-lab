#!/bin/bash
echo "enter string 1: "
read s1
echo "enter string 2: "
read s2
l1=${#s1}
l2=${#s2}
i=0
ans=0
while ((($i<$l1) && ($i<$l2)))
do
	if [ ${s1:$i:1} = ${s2:$i:1} ]
	then
		ans=$((ans+1))
	fi		
	i=$((i+1))
done
echo "$((ans*100/l1))"
