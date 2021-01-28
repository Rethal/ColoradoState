#include <stick.h>
using namespace std;

vector<vector<Point3D>> timeVector;

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
		double numCount = 0;
		vector<Point3D> poseVector;
		while (iss.good() && !iss.eof()) {
			//for (int i = 0; i < 25; i++) {
			double x;
			double y;
			double z;
			string finish;
			if (iss >> x) {
				//cout << x << " ";
				numCount++;
				if (iss >> y) {
					//cout << y << " ";
					numCount++;
					if (iss >> z) {
						//cout << z << endl;
						numCount++;
						poseVector.push_back(Point3D(x, y, z));
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
				}
			}
		}
		if (numCount == 75) {
			//	if (pose.Pose(poseVector, 33)) {
			timeVector.push_back(poseVector);
			lineCount++;
			//}
			
		}
		else {
			cerr << "error: incorrect amount of numbers on line " << lineCount << endl;
			return -1;
		}
	}
	return 0;
}