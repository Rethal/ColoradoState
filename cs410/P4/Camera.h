#ifndef CAMERAFILE
#define CAMERAFILE
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "Light.h"
#include "Sphere.h"
#include "Model.h"
using namespace std;
class Camera {
public:
	Camera(ifstream& CameraFile) {
	}
	int CameraSetup(ifstream& CameraFile);
	vector<double> eye;
	vector<double> look;
	vector<double> up;
	double d;
	//left bottom right top
	vector<double> bounds;
	//column row
	vector<int> res;
	vector<double> ambient;
	//Material sphereMat();
	vector<Light> lights;
	vector<Sphere> spheres;
	vector<ObjModel> models;
	bool AmbientSet;
	//vector<string> modelNames;
	//vector<vector<double>> 
};

#endif