#!/bin/bash

for i in 10000 15000 30000 50000 75000 100000 1000000 2000000 10000000
do
	FILENAME=./data/${i}_buildings.dat
	echo "Processing " $FILENAME
	time ./bin/skyline $FILENAME >> /dev/null 
done
