#!/bin/bash

for i in 1000 5000 10000 15000 30000 50000 75000 100000 1000000
do
	echo $i
	time ./skyline < $i > /dev/null 
done
