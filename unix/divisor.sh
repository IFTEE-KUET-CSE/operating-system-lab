#!/bin/bash
read x
case $((x%2)) in
	0) echo "by 2"
	*) case $((x%3)) in
		0) echo "by 3"
		*) i=$((x-1))
		while (($i>0))
		do
			if [ $(($x%$i)) -eq 0 ]
			then
				echo $i
			fi
			i=$((i-1))
		done
	esac
esac
