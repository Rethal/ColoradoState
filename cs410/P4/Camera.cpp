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
				else if (word.compare("light") == 0) {
					double x, y, z, w, r, b, g;
					iss >> x; iss >> y; iss >> z; iss >> w; iss >> r; iss >> g; iss >> b;
					Light light(x, y, z, w, r, g, b);
					lights.push_back(light);
				}
				else if (word.compare("sphere") == 0) {
					double x, y, z, rad, r, b, g;
					iss >> x; iss >> y; iss >> z; iss >> rad; iss >> r; iss >> g; iss >> b;
					Sphere circle(x, y, z, rad, r, g, b);
					spheres.push_back(circle);
				}
				else if (word.compare("ambient") == 0) {
					//cout << "ambient" << endl;
					double r, b, g;
					iss >> r; iss >> g; iss >> b;
					ambient.clear();
					ambient.push_back(r); ambient.push_back(g); ambient.push_back(b);
					AmbientSet = true;
				}
				else if (word.compare("model") == 0) {
					double x, y, z, a, b, c, d;
					string Name;
					iss >> x; iss >> y; iss >> z; iss >> a; iss >> b; iss >> c; iss >> d; iss >> Name;
					cout << Name << endl;
					ObjModel model(x, y, z, Name);
					models.push_back(model);
				}
			}
		}
		if (!AmbientSet) {
			ambient.push_back(0); ambient.push_back(0); ambient.push_back(0);
		}
		//cout << "Ambient R: " << ambient[0] << " Ambient B: " << ambient[1] << " Ambient G: " << ambient[2] << endl;
	}
	return 0;
}