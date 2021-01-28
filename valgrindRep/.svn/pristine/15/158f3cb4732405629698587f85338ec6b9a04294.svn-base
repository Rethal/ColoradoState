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
#include <Distance.h>
using namespace std; 
class stick {
public:
	
	stick(ifstream& inFile, string outFile = "") {
		legalFile(inFile);
	};
	int filePose(PoseDisplay& pose, ifstream& inFile);
	int fileDistPrint(ifstream& inFile, string outFile);
	/*string getOut(){ return OUTFILE; };
	ifstream getIn(){ return INFILE; };*/
	ifstream INFILE;
	string OUTFILE;
	vector<vector<Point3D>> timeVector;

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
	double poseVectorCompare(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong);

	vector<double> SpineX;
	vector<double> SpineY;
	vector<double> SpineZ;
	vector<double> allX;
	vector<double> allY;
	vector<double> allZ;
	vector<double> poseDistances;

	int comparePosesMulti(const stick& StickShort, const stick& StickLong, string distanceType = "");
	bool openOutFileMulti(string outFile);
	bool writeDistanceMulti();
	int fileDistPrintMulti(const stick& firstIn, const stick& secondIn, string outFile);
	
	int dynamicMatch(const stick& firstIn, const stick& secondIn, string distanceType = "");
	double recursiveMatch(const vector<vector<double>>& distMatrix, int i = -1, int base = 0);

	vector<vector<double>> fileDistances;

//protected:
	
	
};
#endif