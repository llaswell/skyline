 #!/bin/bash

if [ ! -d "./bin" ]; then
	mkdir ./bin
fi

#g++ -std=gnu++11 -ocreateBuildings createBuildings.cpp
g++ -std=c++0x -o bin/createBuildings createBuildings.cpp
g++ -o bin/skyline skyline.cpp
