#include <stick.h>
using namespace std;

vector<vector<Point3D>> timeVector;
vector<double> SpineX;
vector<double> SpineY;
vector<double> SpineZ;
vector<double> allX;
vector<double> allY;
vector<double> allZ;

int stick::filePose(ifstream& inFile, PoseDisplay& pose) {
	if (legalFile(inFile, pose)!=-1) {
		for (unsigned int i = 0; i < timeVector.size(); i++) {
			if (pose.Pose(timeVector[i], 33)) {
			}
			else {
				cerr << "error: could not display pose " << endl;
				return -1;
			}
		}
		return 0;
	}
	else
		cerr << "error: illegal file " << endl;
	return -1;
}

int stick::legalFile(ifstream& inFile, PoseDisplay& pose) {
	string lineOf75 = "";
	int lineCount = 0;
	while (getline(inFile, lineOf75)) {
		istringstream iss;
		iss.str(lineOf75);
		int numCount = 0;
		//vector<Point3D> poseVector;
		numCount = checkLine(iss, lineCount);
		if (numCount == -1) {
			return -1;
		}
		else if (numCount == 75) {
			//	if (pose.Pose(poseVector, 33)) {
			//timeVector.push_back(poseVector);
			lineCount++;
			//}
			
		}
		else {
			cerr << "error: incorrect amount of numbers on line " << lineCount << endl;
			return -1;
		}
	}
	if (!sameLems()) {
		return -1;
	}
	double xAvg = findSpineX();
	double yAvg = findSpineY();
	double zAvg = findSpineZ();
	//cout << xAvg << ", " << yAvg << ", " << zAvg << endl;
	shiftVector(xAvg, allX);
	shiftVector(yAvg, allY);
	shiftVector(zAvg, allZ);
	//newBase();
	//xAvg = findSpineX();
	//yAvg = findSpineY();
	//zAvg = findSpineZ();
	//cout << xAvg << ", " << yAvg << ", " << zAvg << endl;
	double Abs = greatestAbs();
	if (Abs == 0) {
		cerr << "error: scale is 0" << endl;
		return -1;
	}
	//cout << Abs << endl;
	scaleVector(Abs, allX);
	scaleVector(Abs, allY);
	scaleVector(Abs, allZ);
	//newBase();
	//xAvg = findSpineX();
	//yAvg = findSpineY();
	//zAvg = findSpineZ();
	//cout << xAvg << ", " << yAvg << ", " << zAvg << endl;
	//Abs = greatestAbs();
	//cout << Abs << endl;
	if (makePoses() == -1) {
		cerr << "error: failed to make poses" << endl;
		return -1;
	}
	return 0;
}

int stick::checkLine(istringstream& iss, int lineCount) {
	int numCount = 0;
	while (iss.good() && !iss.eof()) {
		//for (int i = 0; i < 25; i++) {
		double x;
		double y;
		double z;
		string finish;
		if (iss >> x) {
			//cout << x << " ";
			if (numCount == 0) {
				SpineX.push_back(x);
			}
			allX.push_back(x);
			numCount++;
			if (iss >> y) {
				//cout << y << " ";
				if (numCount == 1) {
					SpineY.push_back(y);
				}
				allY.push_back(y);
				numCount++;
				if (iss >> z) {
					//cout << z << endl;
					if (numCount == 2) {
						SpineZ.push_back(z);
					}
					allZ.push_back(z);
					numCount++;
					//poseVector.push_back(Point3D(x, y, z));
				}
				else {
					cerr << "error: z failed to write " << numCount;
					cerr << " line: " << lineCount << endl;
					return -1;
				}
			}
			else {
				cerr << "error: y failed to write " << numCount;
				cerr << " line: " << lineCount << endl;
				return -1;
			}
		}
		else {
			cerr << "error: x failed to write " << numCount;
			cerr << " line: " << lineCount << endl;
			return -1;
		}
		if (numCount == 75) {
			if (iss >> finish) {
				cerr << "error: too much on line: " << lineCount << endl;
				return -1;
			}
		}
	}
	return numCount;
}

double stick::findSpineX() {
	int count = 0;
	double xAvg = 0;
	for (unsigned int i = 0; i < SpineX.size(); i++) {
		xAvg += SpineX[i];
		count++;
	}
	xAvg = xAvg / count;
	return xAvg;
}

double stick::findSpineY() {
	int count = 0;
	double yAvg = 0;
	for (unsigned int i = 0; i < SpineY.size(); i++) {
		yAvg += SpineY[i];
		count++;
	}
	yAvg = yAvg / count;
	return yAvg;
}

double stick::findSpineZ() {
	int count = 0;
	double zAvg = 0;
	for (unsigned int i = 0; i < SpineZ.size(); i++) {
		zAvg += SpineZ[i];
		count++;
	}
	zAvg = zAvg / count;
	return zAvg;
}

void stick::shiftVector(double shift, vector<double>& values) {
	//shift = .5;
	for (unsigned int i = 0; i < values.size(); i++) {
		values[i] = values[i] - shift;
	}
}

int stick::makePoses() {
	vector<Point3D> poseVector;
	int poseCount = 0;
	for (unsigned int i = 0; i < allX.size(); i++) {
		//cout << allX[i] << " " << allY[i] << " " << allZ[i] << endl;
		poseVector.push_back(Point3D(allX[i], allY[i], allZ[i]));
		if (i != 0 && (i+1) % 25 == 0) {
			timeVector.push_back(poseVector);
			poseVector.clear();
			poseCount++;
		}
	}
	return 0;
}

bool stick::sameLems() {
	if (allX.size() != allY.size() || allY.size() != allZ.size() || allX.size() != allZ.size()) {
		cerr << "error: different number of elements" << endl;
		return false;
	}
	else return true;
}

double stick::greatestAbs() {
	double Absolute = 0;
	for (unsigned int i = 0; i < allX.size(); i++) {
		double absX = abs(allX[i]);
		double absY = abs(allY[i]);
		double absZ = abs(allZ[i]);
		if (absX > Absolute) {
			Absolute = absX;
		}
		if (absY > Absolute) {
			Absolute = absY;
		}
		if (absZ > Absolute) {
			Absolute = absZ;
		}
	}
	return Absolute;
}

int stick::scaleVector(double scale, vector<double>& values) {
	if (scale == 0) {
		cerr << "error: tried to scale by infinity " << endl;
		return -1;
	}
//	cout << scale << endl;
	scale = 1 / scale;
	//scale = 20;
//	cout << scale << endl;
	for (unsigned int i = 0; i < values.size(); i++) {
		values[i] = scale*values[i];
	}
	return scale;
}

void stick::newBase() {
	SpineX.clear();
	SpineY.clear();
	SpineZ.clear();
	for (unsigned int i = 0; i < allX.size(); i++) {
		SpineX.push_back(allX[i]);
		i+=24;
	}
	for (unsigned int i = 0; i < allY.size(); i++) {
		SpineY.push_back(allY[i]);
		i+=24;
	}
	for (unsigned int i = 0; i < allZ.size(); i++) {
		SpineZ.push_back(allZ[i]);
		i += 24;
	}
}