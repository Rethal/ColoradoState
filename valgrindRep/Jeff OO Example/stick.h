//Main Header by Brent Grundman
//CS253
//829460164
#ifndef STICK_FIGURE
#define STICK_FIGURE
#include <iostream>
#include <fstream>
#include <sstream>
#include <PoseDisplay.h>
#include <Point3D.h>
#include <cmath>
using namespace std; 
class stick {
public:
	stick(ifstream& inFile, string outFile):  {
		INFILE = &inFile;
		OUTFILE = outFile;
	};
	int filePose(PoseDisplay& pose, ifstream& inFile);
	int fileDistPrint(ifstream& inFile, string outFile);
	
protected:
	int legalFile(ifstream& inFile);
	int checkLine(istringstream& iss, int lineCount);
	double findSpineX();
	double findSpineY();
	double findSpineZ();
	void shiftVector(double shift, vector<double>& values);
	int makePoses();
	double greatestAbs();
	bool sameLems();
	int scaleVector(double scale, vector<double>& values);
	void newBase();
	int comparePoses();
	bool openOutFile(string outFile);
	bool writeDistance();

	vector<vector<Point3D>> timeVector;
	vector<double> SpineX;
	vector<double> SpineY;
	vector<double> SpineZ;
	vector<double> allX;
	vector<double> allY;
	vector<double> allZ;
	vector<double> poseDistances;
	const ifstream INFILE;
	const string OUTFILE;
};
#endif