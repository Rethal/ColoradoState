#include <stick.h>
using namespace std;

ofstream audi;

//int stick::filePose(PoseDisplay& pose, ifstream& inFile) {
//	if (legalFile(inFile)!=-1) {
//		for (unsigned int i = 0; i < timeVector.size(); i++) {
//			if (pose.Pose(timeVector[i], 33)) {
//			}
//			else {
//				cerr << "error: could not display pose " << endl;
//				return -1;
//			}
//		}
//	}
//	else
//		cerr << "error: illegal file " << endl;
//	return -1;
//}

//int stick::fileDistPrint(ifstream& inFile, string outFile) {
//	if (legalFile(inFile) != -1) {
//		if (!openOutFile(outFile)) return -1;
//		if (!writeDistance()) return -1;
//		return 0;
//	}
//	else
//		cerr << "error: could not write distance " << endl;
//	return -1;
//}

int stick::legalFile(ifstream& inFile) {
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
	/*if (comparePoses() == -1) {
		cerr << "error: failed to return poses" << endl;
		return -1;
	}*/
	return 0;
}

//bool stick::openOutFile(string outFile) {
//	audi.open(outFile.c_str());
//	if (!audi) {
//		cerr << "error: could not open output file " << outFile << endl;
//		return false;
//	}
//	return true;
//}

//bool stick::writeDistance()
//{
//	for (vector<double>::const_iterator iter = poseDistances.begin(); iter != poseDistances.end(); iter++) {
//		audi << *iter << endl;
//	}
//	return !(audi.fail());
//}

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
	poseVector.reserve(25);
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

//int stick::comparePoses() {
//	vector<Point3D> poseVector;
//	vector<Point3D> nextPose;
//	//double x1, x2, y1, y2, z1, z2, xdist, ydist, zdist, underRoot, pointCompare;
//	for (unsigned int i = 0; i < timeVector.size(); i++) {
//		double poseCompare = 0;
//		poseVector = timeVector[i];
//		if ((i + 1) < timeVector.size()) {
//			nextPose = timeVector[i + 1];
//		}
//		else {
//			if (i == 0) {
//				cerr << "error: fewer than two lines of input, cannot compare" << endl;
//				return -1;
//			}
//			else return 0;
//		}
//		/*for (unsigned int j = 0; j < poseVector.size(); j++) {
//			x1 = poseVector[j].X();
//			x2 = nextPose[j].X();
//			y1 = poseVector[j].Y();
//			y2 = nextPose[j].Y();
//			z1 = poseVector[j].Z();
//			z2 = nextPose[j].Z();
//			xdist = x1 - x2;
//			ydist = y1 - y2;
//			zdist = z1 - z2;
//			underRoot = (xdist*xdist) + (ydist*ydist) + (zdist*zdist);
//			pointCompare = sqrt(underRoot);
//			poseCompare += abs(pointCompare);
//		}*/
//		poseCompare = poseVectorCompare(poseVector, nextPose);
//		poseDistances.push_back(poseCompare);
//	}
//	return 0;
//}

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

//void stick::newBase() {
//	SpineX.clear();
//	SpineY.clear();
//	SpineZ.clear();
//	for (unsigned int i = 0; i < allX.size(); i++) {
//		SpineX.push_back(allX[i]);
//		i+=24;
//	}
//	for (unsigned int i = 0; i < allY.size(); i++) {
//		SpineY.push_back(allY[i]);
//		i+=24;
//	}
//	for (unsigned int i = 0; i < allZ.size(); i++) {
//		SpineZ.push_back(allZ[i]);
//		i += 24;
//	}
//}



double stick::poseVectorCompare(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong) {
	
	double x1, x2, y1, y2, z1, z2, xdist, ydist, zdist, underRoot, pointCompare;
	double poseCompare = 0;

	for (unsigned int j = 0; j < poseVectorShort.size(); j++) {
		x1 = poseVectorShort[j].X();
		x2 = poseVectorLong[j].X();
		y1 = poseVectorShort[j].Y();
		y2 = poseVectorLong[j].Y();
		z1 = poseVectorShort[j].Z();
		z2 = poseVectorLong[j].Z();
		xdist = x1 - x2;
		ydist = y1 - y2;
		zdist = z1 - z2;
		underRoot = (xdist*xdist) + (ydist*ydist) + (zdist*zdist);
		pointCompare = sqrt(underRoot);
		poseCompare += abs(pointCompare);
	}
	return poseCompare;
}

int stick::comparePosesMulti(const stick& StickShort, const stick& StickLong, string distanceType) {
	vector<Point3D> poseVectorShort;
	poseVectorShort.reserve(25);
	vector<Point3D> poseVectorLong;
	poseVectorLong.reserve(25);
	vector<double> poseDistances;
	int allDistances = StickShort.timeVector.size()*StickLong.timeVector.size();
	poseDistances.reserve(allDistances);
	//fileDistances.clear();
	if (StickShort.timeVector.size() < 1 || StickLong.timeVector.size() < 1) {
		cerr << "error: not enough poses" << endl;
		return -1;
	}
	unsigned int i = 0;
	while (i < StickShort.timeVector.size()) {
		poseVectorShort = StickShort.timeVector[i];
		unsigned int k = 0;
		while (k < StickLong.timeVector.size()) {
			poseVectorLong = StickLong.timeVector[k];
			Distance d(poseVectorShort,poseVectorLong,distanceType);
			double poseCompare = d.Comparison;//distance::poseVectorCompare(poseVectorShort, poseVectorLong);
			poseDistances.push_back(poseCompare);
			k++;
		}
		fileDistances.push_back(poseDistances);
		poseDistances.clear();
		i++;
	}
	return 0;
}

//int stick::fileDistPrintMulti(const stick& firstIn, const stick& secondIn, string outFile) {
//
//	//passes short in first
//	if (firstIn.timeVector.size() > secondIn.timeVector.size()) {
//		if (comparePosesMulti(secondIn, firstIn) == -1) {
//			return -1;
//		}
//	}
//	else {
//		if (comparePosesMulti(firstIn, secondIn) == -1) {
//			return -1;
//		}
//	}
//	if (!stick::openOutFileMulti(outFile)) return -1;
//	if (!stick::writeDistanceMulti()) return -1;
//	return 0;
//}

//bool stick::openOutFileMulti(string outFile) {
//	audi.open(outFile.c_str());
//	if (!audi) {
//		cerr << "error: could not open output file " << outFile << endl;
//		return false;
//	}
//	return true;
//}

//bool stick::writeDistanceMulti()
//{
//	for (unsigned int i = 0; i < fileDistances.size(); i++) {
//		vector<double> poseDistances = fileDistances[i];
//		for (vector<double>::const_iterator iter2 = poseDistances.begin(); iter2 != poseDistances.end(); iter2++) {
//			audi << *iter2 << " ";
//		}
//		audi << endl;
//	}
//	return !(audi.fail());
//}

int stick::dynamicMatch(const stick& firstIn, const stick& secondIn, string distanceType) {
	//passes short in first
	if (firstIn.timeVector.size() > secondIn.timeVector.size()) {
		if (comparePosesMulti(secondIn, firstIn, distanceType) == -1) {
			return -1;
		}
	}
	else {
		if (comparePosesMulti(firstIn, secondIn, distanceType) == -1) {
			return -1;
		}
	}
	double Returned = recursiveMatch(fileDistances);
	cout << Returned << endl;
	return 0;
	/*for (unsigned int i = fileDistances.size()-1; i > 0; i--) {
		vector<double> poseDistances = fileDistances[i];
		unsigned int j = poseDistances.size();
		for (vector<double>::const_iterator iter2 = poseDistances.begin(); iter2 != poseDistances.end(); iter2++) {
		}
	}*/
}

vector<vector<double>> mappedDistances;

double stick::recursiveMatch(const vector<vector<double>>& distMatrix, int i, int base) {
	double minValuePrev;
	if (i == -1) {
		i = distMatrix.size()-1;
	}
	//get to base case
	if (i > base) {
		minValuePrev = recursiveMatch(distMatrix, i - 1, base);
	}
	//create new vector
	if (i == base) {
		mappedDistances.clear();
		mappedDistances.reserve(distMatrix.size());
		mappedDistances.push_back(distMatrix[i]);
		vector<double> poseDistances = distMatrix[i];
		unsigned int lineLength = poseDistances.size();
		double minValue = poseDistances[0];
		for (unsigned int l = 0; l < lineLength; l++) {
			if (poseDistances[l] < minValue) {
				minValue = poseDistances[l];
			}
		}
		return minValue;
	}
	vector<double> poseDistances = distMatrix[i];
	vector<double> poseDistancesPrev = mappedDistances[i-1];
	unsigned int lineLength = poseDistances.size();
	//double minValuePrev;
	for (unsigned int j = 0; j < lineLength; j++) {
		//minValuePrev = poseDistancesPrev[0];
		//for (unsigned int k = 0; k <= j; k++) {
		//	if (poseDistancesPrev[k] < minValuePrev) {
		//		minValuePrev = poseDistancesPrev[k];
		//	}
	//	}
		poseDistances[j] = poseDistances[j] + minValuePrev;
	}
	mappedDistances.push_back(poseDistances);
	double minValue = poseDistances[0];
	for (unsigned int l = 0; l < lineLength; l++) {
		if (poseDistances[l] < minValue) {
			minValue = poseDistances[l];
		}
	}
	//cout << minValue << endl;
	return minValue;
}