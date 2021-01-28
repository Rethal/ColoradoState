#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "Camera.h"
//#include "PlyReader.h"
#include "Raytrace.h"
#include "PPMPrint.h"
using namespace std;
int main(int argc, char *argv[]) {
	int desiredArgs = 3;
	if (argc != desiredArgs && argc != 1) {
		cerr << "error: Please input " << desiredArgs - 1 << " parameters" << endl;
		return -1;
	}
	if (argc == 1) {
		ifstream CameraFile("masterwork.txt");
		string outFile = "masterwork.ppm";
		Camera cam(CameraFile);
		cam.CameraSetup(CameraFile);
		Raytracer raytracer(cam);
		raytracer.pixelMap();
		raytracer.rayCaster();
		ppmPrint printer(raytracer, outFile);
	}
	else {
		ifstream CameraFile(argv[1]);
		//ifstream ModelFile(argv[2]);
		//string inFile = argv[2];
		string outFile = argv[2];
		Camera cam(CameraFile);
		cam.CameraSetup(CameraFile);
		//cout << "camera good" << endl;
		//old: PlyModel model(ModelFile);
		Raytracer raytracer(cam);
		//cout << model.XYZvertex.size() << endl;
		//cout << "model good" << endl;
		//old: raytracer impacts(cam, model);
		raytracer.pixelMap();
		raytracer.rayCaster();
		//cout << "tracer good" << endl;
		//old: impacts.pixelMap();
		//cout << "map good" << endl;
		//old: impacts.rayCaster();
		//cout << "cast good" << endl;
		ppmPrint printer(raytracer, outFile);
	}

}