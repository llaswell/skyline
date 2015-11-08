#include <cstdio>
#include <iostream>
#include <list>
#include <cstdlib>
#include <random>

struct Building {
	double l;
	double r;
	double h;
};


int main(int argc,char** argv) {
	if( argc != 2) {
		std::cerr << "Usage: " << argv[0] << "<num_buildigns>" << std::endl;
		return -1;
	}

	long N = atoi(argv[1]);

	Building building;

	std::random_device rd;

	std::default_random_engine e1(rd());
	//std::mt19937 gen(rd())
	std::uniform_real_distribution<> dis(0.0,1.0);
	for(long i = 0; i < N; ++i) {
		building.l = dis(e1) * 10000.0;
		building.r = building.l + dis(e1) * 1000.0;
		building.h = dis(e1) * 10000.0;
		std::cout << building.l
			<< " "
			<< building.r
			<< " "
			<< building.h
			<< std::endl;
	}

	return 0;
}
