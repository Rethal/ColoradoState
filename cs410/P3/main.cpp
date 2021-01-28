#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "Camera.h"
#include "PlyReader.h"
#include "Raycast.h"
#include "PPMPrint.h"
using namespace std;
int main(int argc, char *argv[]) {
	int desiredArgs = 4;
	if (argc != desiredArgs) {
		cerr << "error: Please input " << desiredArgs - 1 << " parameters" << endl;
		return -1;
	}
	ifstream CameraFile(argv[1]);
	ifstream ModelFile(argv[2]);
	string outFile = argv[3];
	Camera cam(CameraFile);
	cam.CameraSetup(CameraFile);
	//cout << "camera good" << endl;
	PlyModel model(ModelFile);
	//cout << model.XYZvertex.size() << endl;
	//cout << "model good" << endl;
	raytracer impacts(cam, model);
	//cout << "tracer good" << endl;
	impacts.pixelMap();
	//cout << "map good" << endl;
	impacts.rayCaster();
	//cout << "cast good" << endl;
	ppmPrint printer(impacts, outFile);
}