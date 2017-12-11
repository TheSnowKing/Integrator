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

echo -e "Animating data..."
line=$(head -n 1 "$tmp")


for ((i = 0; i < line; i++)) do

	if [ $i -eq 0 ]; then
		echo -e "set key off; set xrange[-12:12]; set yrange[-12:12]; set zrange[-12:12]; splot '$tmp' every :::$i::$i using 1:2:3 pt 7 ps 1 lc rgb 'black'";
	else
		echo -e "set key off; set xrange[-12:12]; set yrange[-12:12]; set zrange[-12:12]; splot '$tmp' every :::$i::$i using 1:2:3 pt 7 ps 1 lc rgb 'black'";
	fi

#	echo -e "set size square;\
#		 set key off;\
#		 \
#		 set xlabel 'Time (seconds)';\
#		 set ylabel 'f(x)';\
#		 \
#		 set title 'Plot';\
#		 plot\
#		 '$tmp' using 1:2 with points pt 7 lc rgb 'blue'";
done | gnuplot --persist
echo -e "Animation complete."

rm $tmp

