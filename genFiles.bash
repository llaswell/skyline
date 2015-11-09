#!/bin/bash

echo "Files will be written to data/"

for i in 10000 15000 30000 50000 75000 100000 1000000 2000000 10000000
do
	FILENAME=${i}_buildings.dat
	echo "Writing file: " $FILENAME
	./bin/createBuildings $i > ./data/$FILENAME
done
