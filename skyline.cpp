#include <cstdio>
#include <iostream>
#include <list>
#include <fstream>

//struct used to represent each building
struct Building {
	double l;
	double r;
	double h;
};

//b1 overlaps b2 on its right side
bool overlapRight(const Building& _b1,const Building& _b2) {
	return ( (_b1.r > _b2.l) && ( _b1.r <= _b2.r) );
}

//b1 overlaps b2 on its left side
bool overlapLeft(const Building& _b1,const Building& _b2) {
	return ( (_b1.l >= _b2.l) && (_b1.l < _b2.r));
}

//b1 overlaps b2
bool overlap(const Building& _b1,const Building& _b2) {
	return overlapRight(_b1,_b2) || overlapLeft(_b1,_b2) || ((_b1.l < _b2.l) && (_b1.r > _b2.r));
}
//b1 covers b2
bool covers(const Building& _b1,const Building& _b2) {
	return ( (_b1.l <= _b2.l) && (_b1.r >= _b2.r) && (_b1.h >= _b2.h) );
}

//helper function to insert buildings into our list
std::list< Building >::iterator insertBuilding(std::list< Building >& _buildingList,std::list< Building >::iterator _p,const Building& _building,bool debug = false) {

	if(debug) {
		std::cout << "Insert: "
				<< _building.l
				<< " "
				<< _building.h
				<< " "
				<< _building.r
				<< std::endl;
	}
	
	if( _building.l == _building.r ) {
		std::cout << "ERROR: 0 width building not inserted: " 
			<< _building.l
			<< " "
			<< _building.r
			<< std::endl;
	}

	return _buildingList.insert(_p,_building);

}

//this function determines any interactions with the existing list
//this function adds the building to the list and adjusts  or removes the existing buildings
//to maintain the list with only disjoint buildings
//the list is maintained in order by the left coordianate of the building
void addBuilding(std::list< Building >& _buildingList,const Building& _building,bool debug=false) {
	std::list<Building>::iterator p = _buildingList.begin();
	Building bld = _building;

	if(debug) std::cout << "Add: " << bld.l << " " << bld.h << " " << bld.r << std::endl;

	//if(debug) std::cout << "debug is enabled" << std::endl;

	if( p == _buildingList.end() ) {
		if(debug) std::cout << "Insert first" << std::endl;
		insertBuilding(_buildingList,p,bld,debug);
		return;
	}


	bool inserted(false);

	while(p!=_buildingList.end()) {

		if(debug) std::cout << "Consider: " << p->l << " " << p->h << " " << p->r << std::endl;
		//Will not intersect any buildings
		//because they are all to its right
		if( bld.r <= p->l) {
			if(debug) std::cout << "will not intersect" << std::endl;
			insertBuilding(_buildingList,p,bld,debug);
			return;
		}

		//no overlap so examine the next building
		if( !overlap(bld,*p) ) {
			if(debug) std::cout << "no overlap" << std::endl;
			++p;
			continue;	
		}

		if( covers(*p,bld) ) {
			if(debug) std::cout << "this building is covered" << std::endl;
			//since this building is covered, we don't need it
			return;
		}

		//this one is covered so not visible
		if( covers(bld,*p) ) {
			if(debug) std::cout << "this building covers considered" << std::endl;
			if(debug) std::cout << "remove considered" << std::endl;
			_buildingList.erase(p++);
			continue;
		}

		//new building is shorter
		if( bld.h < p->h ) {
			if(debug) std::cout << "new is shorter" << std::endl;
			if( bld.l < p->l ) {
				if(debug) std::cout << "new overlaps on left" << std::endl;
				if(debug) std::cout << "insert new on before old" << std::endl;
				Building leftBuilding = bld;
				leftBuilding.r = p->l;
				insertBuilding(_buildingList,p,leftBuilding,debug);
				return;
			}
			else {
				if(debug) std::cout << "New overlaps on right" << std::endl;
				if(debug) std::cout << "Adjust left side and check against next" << std::endl;
				//move left wall of new building to remove overlap
				bld.l = p->r;
			}
		}
		//the new building is taller
		else {
			if(debug) std::cout << "new is taller" << std::endl;
			Building saveOld = *p;
			if( p->l < bld.l ) {
				if(debug) std::cout << "old overlaps on left" << std::endl;
				if(debug) std::cout << "Shorten right side of old" << std::endl;
				p->r = bld.l;
				if( p->r <= p->l ) {
					if(debug) {
						std::cout << "Adjustment created invalid building: "
						<< p->l
						<< " "
						<< p->r
						<< std::endl;
					}

				}
				if( saveOld.r > bld.r ) {
					if(debug) std::cout << "old overlaps on right" << std::endl;
					++p;
					if(debug) std::cout << "insert new after old" << std::endl;
					p = insertBuilding(_buildingList,p,bld,debug);
					++p;
					saveOld.l = bld.r;
					insertBuilding(_buildingList,p,saveOld,debug);
					//since overlap on right, we are done
					return;
				}
			}
			else {
				if(debug) std::cout << "old does not overlap on left" << std::endl;
				if( p->r > bld.r ) {
					if(debug) std::cout << "old overlaps on right" << std::endl;
					if(debug) std::cout << "insert new before old" << std::endl;
					insertBuilding(_buildingList,p,bld,debug);
					if(debug) std::cout << "adjust left side of old so it does not overlap new" << std::endl;
					p->l = bld.r;
					//since overlap on right, we are done
					return;
				}

			}
		}

		++p;
		continue;
	}

	if(!inserted) {
		if(debug) std::cout << "insert at end" << std::endl;
		insertBuilding(_buildingList,_buildingList.end(),bld,debug);
	}

	return;
}




int main(int argc,char** argv) {

	if( argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <building_file> [debug]" << std::endl;
		return -1;
	}

	std::ifstream in(argv[1]);

	if( in.fail() ) {
		std::cerr << "Unable to open file " << argv[1] << ".  Exiting..." << std::endl;
		return -1;
	}

	bool debug(false);
	if( argc > 2 ) debug = true; 

	Building building;
	std::list<Building> buildings;


	while(in >> building.l >> building.h >> building.r) {

		addBuilding(buildings,building,debug);
	}

	in.close();

	std::list<Building>::iterator p = buildings.begin();

	std::cerr << "Effective number of buildings in skyline: " << buildings.size() << std::endl;	

	double x(0.0);
	double y(0.0);
	bool start(true);
	std::cout << std::endl << std::endl;

	for(;p!=buildings.end();++p) {
		//std::cout << std::endl << "BUILDING: " << p->l
		//	<< " "
		//	<< p->h
		//	<< " "
		//	<< p->r
		//	<< std::endl;

		if(start) {	
			std::cout << p->l << " " << p->h;
			x=p->r;
			y=p->h;
			start = false;
		}
		else {
			if( p->l > x ) std::cout << " " << x << " 0";
			std::cout << " " << p->l << " " << p->h;
			x=p->r;
			y=p->h;
		}
	}
	std::cout << " " << x << " 0" << std::endl << std::endl;

	return 0;
}
