#!/bin/bash

tmp=$(mktemp)

if [ "$#" -eq 3 ]; then
	prog=$1
	if [ ! -f "$prog" ]; then
		echo -e "Error: Program '$prog' does not exist."
		exit 1
	fi

else
	echo -e "Error: Invalid number of arguments."
	exit 1
fi

./$prog $2 $3 > $tmp
#cat $tmp

#set xrange[0:];\
#set yrange[0:];\

echo -e "Generating plot..."
echo -e "set terminal png;\
	 set size square;\
	 set key off;\
	 \
	 set xlabel 'Time (seconds)';\
	 set ylabel 'f(x)';\
	 \
	 set output 'img.png';\
	 \
	 set title 'Plot';\
	 plot\
	 '$tmp' using 1:2 with points pt 7 lc rgb 'blue';\
	 \
	 set terminal x11;\
	 replot" | gnuplot --persist

echo -e "Plot generated."
rm $tmp
