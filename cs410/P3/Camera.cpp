#include "Camera.h"
int Camera::CameraSetup(ifstream& CameraFile) {
	string CameraAspect = "";
	//int startVertex = 0;
	while (getline(CameraFile, CameraAspect)) {
		istringstream iss;
		iss.str(CameraAspect);
		string word;
		double dpoint;
		double point;
		int resolution;
		while (iss.good() && !iss.eof()) {
			//cout << "camera check" << endl;
			if (iss >> word) {
				if (word.compare("eye") == 0) {
					//up d bounds res
					for (int i = 0; i < 3; i++) {
						iss >> dpoint;
						eye.push_back(dpoint);
					}
				}
				else if (word.compare("look") == 0) {
					for (int i = 0; i < 3; i++) {
						iss >> dpoint;
						look.push_back(dpoint);
					}
				}
				else if (word.compare("up") == 0) {
					for (int i = 0; i < 3; i++) {
						iss >> dpoint;
						up.push_back(dpoint);
					}
				}
				else if (word.compare("d") == 0) {
					iss >> d;
				}
				else if (word.compare("bounds") == 0) {
					for (int i = 0; i < 4; i++) {
						iss >> point;
						bounds.push_back(point);
					}
				}
				else if (word.compare("res") == 0) {
					iss >> resolution;
					res.push_back(resolution);
					iss >> resolution;
					res.push_back(resolution);
				}
			}
		}
	}
	return 0;
}