#ifndef MODELS
#define MODELS
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "Face.h"
#include "Vertex.h"
#include "Vertexture.h"
#include "Vertexnorm.h"
#include "Material.h"
#include "MatLib.h"
using namespace std;
//Specifically, the first three are the x, y, z translation from model to world coordinates.
//The next four specify an axis - angle rotation.In this assignment you may ignore these values if you wish 
//and assume an identity transformation between the model and the world.Keep in mind this may change in the last assignment.
//The last argument is a string indicating the name of the file containing the 3D polygonal model in OBJ format.
class ObjModel {
public:
	ObjModel(double x, double y, double z, ifstream& filename) {
		xTrans = x;
		yTrans = y;
		zTrans = z;
		readFile(filename);
	}
	ObjModel(double x, double y, double z, string filename) {
		xTrans = x;
		yTrans = y;
		zTrans = z;
		//char*[] fileChars;
		//fileChars[0] = filename.c_str();
		//ifstream inFile = fileChars[0];

		ifstream inFile(filename);
		readFile(inFile);
		cout << faces.size() << endl;
	}
	double xTrans, yTrans, zTrans;
	double AxAn1, AxAn2, AxAn3, AxAn4;
	string ObjFileName;
	vector<Face> faces;
	vector<Vertex> vertices;
	vector<Vertexture> textures;
	vector<Vertexnorm> normals;
	//vector<MatLib> materialLibraries;
	MatLib Library;
	int curMat = 0;
	int readFile(ifstream& filename);
		//create Vertex as Vertex(x, y, z)
};
#endif