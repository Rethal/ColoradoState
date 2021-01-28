#ifndef PPMPRINT
#define PPMPRINT
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "Raycast.h"
//P3
//column row pixel
class ppmPrint {
public:
	ppmPrint(const raytracer& inRays, string OutFile) {
		tmax = inRays.Alltmax;
		tmin = inRays.Alltmin;
		row = inRays.height;
		column = inRays.width;
		print(inRays.impactsForAllPoints, OutFile);
	}
	int print(const vector<vector<double>>& tdists, string OutFile);
	double tmax;
	double tmin;
	int row;
	int column;
	int pixel;
	//vector<vector<vector<int>>> RGB;
};
#endif