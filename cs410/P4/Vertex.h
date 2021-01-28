#ifndef VERTEX
#define VERTEX
#include <vector>
using namespace std;
class Vertex {
public:
	Vertex() {
		X = 0;
		Y = 0;
		Z = 0;
	}
	Vertex(double x, double y, double z) {
		X = x;
		Y = y;
		Z = z;
		vertexVec.push_back(X); vertexVec.push_back(Y); vertexVec.push_back(Z);
	}
	double X;
	double Y;
	double Z;
	vector<double> vertexVec;
};

#endif