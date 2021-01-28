#ifndef FIGURE_COMPARE
#define FIGURE_COMPARE
#include <iostream>
#include <fstream>
#include <sstream>
#include <PoseDisplay.h>
#include <Point3D.h>
#include <cmath>
#include <stick.h>
#include <Distance.h>

using namespace std;

class multistick {
public:
	multistick(int argc, char *argv[]) { 
		FailOrFile = compareIterator(argc, argv);
	};
	/*int comparePosesMulti(const stick& StickShort, const stick& StickLong);
	bool openOutFileMulti(string outFile);
	bool writeDistanceMulti();
	int fileDistPrintMulti(const stick& firstIn, const stick& secondIn, string outFile);*/
	int compareIterator(int argc, char *argv[]);
	double singleDistCompare(stick& firstIn, stick& secondIn, string DistanceType = "");
	/*int argc;
	char* argv[];*/
	int FailOrFile = 0;
};


#endif