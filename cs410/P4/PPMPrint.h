#ifndef PPMPRINT
#define PPMPRINT
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
//#include "Raycast.h"
#include "Raytrace.h"
//P3
//column row pixel
using namespace std;
class ppmPrint {
public:
	ppmPrint(const Raytracer& inRays, string OutFile) {
		//tmax = inRays.Alltmax;
		//tmin = inRays.Alltmin;
		row = inRays.height;
		column = inRays.width;
		print(inRays.allRayImpacts, OutFile);
	}
	//int print(const vector<vector<double>>& tdists, string OutFile);
	//double tmax;
	//double tmin;
	int print(const vector<vector<Ray>>& rayColors, string OutFile);
	int row;
	int column;
	int pixel;
	//vector<vector<vector<int>>> RGB;
};
#endif