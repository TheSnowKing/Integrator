#!/bin/bash

tmp=$(mktemp)

if [ "$#" -eq 4 ]; then
	prog=$1
	if [ ! -f "$prog" ]; then
		echo -e "Error: Program '$prog' does not exist."
		exit 1
	fi

else
	echo -e "Error: Invalid number of arguments."
	exit 1
fi


if [ "$4" -eq 0 ]; then
	./position.sh $prog $2 $3 $4
elif [ "$4" -eq 1 ]; then
	./energy.sh $prog $2 $3 $4
fi
