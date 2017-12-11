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

./$prog $2 $3 $4 > $tmp
#cat $tmp

#set xrange[0:];\
#set yrange[0:];\

echo -e "Generating plot..."
#echo -e "set object 1 rectangle from graph 0, graph 0 to graph 1, graph 1 behind fc rgbcolor 'gray' fs noborder;\
echo -e "set terminal png;\
	 set object 1 rectangle from screen 0,0 to screen 1,1 fc rgb 'white' behind;\
	 set grid;\
	 \
	 set key outside;\
	 set key right;\
	 set key spacing 1.2;\
	 set key font 'Helvetica, 12';\
	 set key box lt -1 lw 1;\
	 \
	 set terminal png size 1000,1000;\
	 set size square 1,1;\
	 \
	 set xlabel 'Time (years)' font 'Helvetica, 14';\
	 set ylabel 'Energy' font 'Helvetica, 14';\
	 \
	 set output 'img.png';\
	 \
	 set title 'Energy vs Time for N-body System' font 'Helvetica, 16';\
	 plot\
	 \
	 '$tmp' using 1:4 with points pt 7 ps 0.7 lc rgb 'black' title 'Total Energy',\
	 \
	 '$tmp' using 1:3 with points pt 7 ps 0.7 lc rgb 'dark-red' title 'Kinetic Energy',\
	 \
	 '$tmp' using 1:2 with points pt 7 ps 0.7 lc rgb 'blue' title 'Potential Energy';\
	 \
	 set terminal x11;\
	 replot" | gnuplot --persist

echo -e "Plot generated."
rm $tmp
