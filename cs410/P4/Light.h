#ifndef LIGHTS
#define LIGHTS
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
class Light {
public:
	//if w is 0, light source at infinity in direction indicated by x, y, z
	Light(double x, double y, double z, double w, double r, double g, double b) {
		X = x;
		Y = y;
		Z = z;
		W = w;
		R = r;
		B = b;
		G = g;
		pos.clear();
		pos.push_back(X);
		pos.push_back(Y);
		pos.push_back(Z);
		color.clear();
		color.push_back(R);
		color.push_back(G);
		color.push_back(B);
		
	}
	double X, Y, Z, W, R, B, G;
	vector<double> pos;
	vector<double> color;
};

#endif