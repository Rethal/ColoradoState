#ifndef DISTANCE_CLASS
#define DISTANCE_CLASS
#include <iostream>
#include <fstream>
#include <sstream>
#include <PoseDisplay.h>
#include <Point3D.h>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
class Distance {
public:
	Distance(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong, string type = "euclid") {
		if (type == "avg") { Comparison = poseVectorCompare(poseVectorShort, poseVectorLong)/25; }
		else if (type == "med") { Comparison = poseVectorMed(poseVectorShort, poseVectorLong); }
		else if (type == "Linf") { Comparison = poseVectorLinf(poseVectorShort, poseVectorLong); }
		else if (type == "L2") { Comparison = poseVectorL2(poseVectorShort, poseVectorLong); }
		else { Comparison = poseVectorCompare(poseVectorShort, poseVectorLong); }
	};
	double poseVectorCompare(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong);
	double poseVectorMed(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong);
	double poseVectorLinf(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong);
	double poseVectorL2(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong);
	double Comparison;
};
#endif