#ifndef SPHERES
#define SPHERES
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
class Sphere {
public:
	Sphere(double x, double y, double z, double rad, double r, double g, double b) {
		X = x;
		Y = y;
		Z = z;
		radius = rad;
		R = r;
		B = b;
		G = g;
		Center.clear();
		Center.push_back(X);
		Center.push_back(Y);
		Center.push_back(Z);
		simpKaKsKd.clear();
		simpKaKsKd.push_back(R);
		simpKaKsKd.push_back(G);
		simpKaKsKd.push_back(B);
		Ka.reserve(3); Ks.reserve(3); Kd.reserve(3);
		Ka = simpKaKsKd;
		Ks = simpKaKsKd;
		Kd = simpKaKsKd;
		//cout << "Sphere R: " << R << " Sphere B: " << B << " Sphere G: " << G << endl;
	}
	double X, Y, Z, radius, R, B, G;
	vector<double> Center;
	//Ka, Kd, and Ks are all RBG
	vector<double> simpKaKsKd;
	vector<double> Ka, Ks, Kd;
};

//simplified material properties indicating "color" of sphere in rbg
//d^2 = r^2 - (c^2 - v^2)
//c = sphere origin minus eye
//r = radius
//v = 
//if d^2 < 0, no intersection
//otherwise Q = E + (v-d)R
#endif