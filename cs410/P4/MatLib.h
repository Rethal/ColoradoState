#ifndef MATERIAL_LIBRARY
#define MATERIAL_LIBRARY
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "Material.h"

using namespace std;
class MatLib {
public:
	MatLib(string libFile = "") {
		//char*[] fileChars;
		//fileChars[0] = libFile.c_str();
		//ifstream filename = fileChars[0];
		ifstream filename(libFile.c_str());
		makeMaterials(filename);
	}
	vector<Material> Materials;
	int makeMaterials(ifstream& infile);
	vector<string> names;
	vector<Vertex> KAs;
	vector<Vertex> KDs;
	vector<Vertex> KSs;
	/*vector<vector<double>> KAs;
	vector<vector<double>> KDs;
	vector<vector<double>> KSs;*/
	vector<string> maps;
};

#endif