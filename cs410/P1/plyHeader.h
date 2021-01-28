#ifndef PLY_HEADER
#define PLY_HEADER
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
class HEADER {
public:

	HEADER(ifstream& inFile) {
		getVertices(inFile);
	}
	int getHeader(ifstream& inFile);
	int getVertices(ifstream& inFile);
	int vecAvg(vector<double>& meanFind);
	int meanVertexFind();
	int vectorNorm();
	int stdDeviations();
	int vectorWhite();
	int setMinMax();
	int resetMinMax();
	int meanVertexCorrect();
	int whiteVertexCorrect();
	int projOneRun(string Title);
	int printToConsole();
	int printNorm(string Title);
	int printWhite(string Title);


	double xMax, yMax, zMax, xMin, yMin, zMin = 0;
	int xMaxSet, yMaxSet, zMaxSet, xMinSet, yMinSet, zMinSet = 0;

	vector<string> format;
	vector<string> vertex;
	vector<string> face;
	vector<string> FLOAT32;
	vector<vector<string> > property_list;
	vector<double> XYZvertex;
	vector<double> Xall;
	vector<double> Yall;
	vector<double> Zall;
	vector<vector<double>> allXYZvertices;
	vector<string> headerLine;
	vector<vector<string>> totalHeader;

	vector<double> meanVertex;
	vector<vector<double>> allXYZnormal;
	vector<vector<double>> allXYZwhite;


	vector<double> currentDev;

	vector<int> faceLine;
	vector<vector<int>> totalFace;

	int FACES;
	int VERTICES;
	int curVert;

	ofstream normOut;
	ofstream whiteOut;

};
#endif