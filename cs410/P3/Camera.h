#ifndef CAMERAFILE
#define CAMERAFILE
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
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
};

#endif