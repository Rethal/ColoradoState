#ifndef RAYCASTER
#define RAYCASTER
#include "PlyReader.h"
#include "Camera.h"
//look - eye = look direction vector
//unit length look direction vector times d + eye = image(0,0)
class raytracer {
public:
	raytracer(const Camera& cam, const PlyModel& model){
		EV = cam.eye;
		//cout << "EV: " << EV[0] << "," << EV[1] << "," << EV[2] << endl;
		LV = cam.look;
		//cout << "LV: " << LV[0] << "," << LV[1] << "," << LV[2] << endl;
		UP = cam.up;
		//cout << "UP: " << UP[0] << "," << UP[1] << "," << UP[2] << endl;
		WV = subtractBfromA(EV,LV);
		//cout << "WV: " << WV[0] << "," << WV[1] << "," << WV[2] << endl;
		left = cam.bounds[0];
		//cout << "left: " << left << endl;
		bottom = cam.bounds[1];
		//cout << "bottom: " << bottom << endl;
		right = cam.bounds[2];
		//cout << "right: " << right << endl;
		top = cam.bounds[3];
		//cout << "top: " << top << endl;
		width = cam.res[0];
		//cout << "width: " << width << endl;
		height = cam.res[1];
		//cout << "height: " << height << endl;
		distance = cam.d;
		//cout << "distance: " << distance << endl;
		WV = normalize(WV);
		//cout << "WV: " << WV[0] << "," << WV[1] << "," << WV[2] << endl;
		UV = cross_product(UP, WV);
		//cout << "UV: " << UV[0] << "," << UV[1] << "," << UV[2] << endl;
		UV = normalize(UV);
		//cout << "UV: " << UV[0] << "," << UV[1] << "," << UV[2] << endl;
		VV = cross_product(WV, UV);
		//cout << "VV: " << VV[0] << "," << VV[1] << "," << VV[2] << endl;
		Points = model.allXYZvertices;
		Connections = model.totalFace;
	}
	vector<double> normalize(const vector<double>& inVector);
	vector<double> cross_product(const vector<double>& u, const vector<double>& v);
	int pixelMap();
	vector<double> subtractBfromA(const vector<double>& A, const vector<double>& B);
	vector<double> scalarMultiply(double scalar, const vector<double>& Vec);
	vector<double> vectorAdd(const vector<double>& A, const vector<double>& B);
	int rayCaster();

	vector<vector<vector<double>>> pixpt;
	//vector<vector<double>> tDists;
	vector<double> EV;
	vector<double> LV;
	vector<double> UP;
	vector<double> WV;
	vector<double> UV;
	vector<double> VV;
	//vector<double> tdists;
	vector<double> impactsForARow;
	vector<vector<double>> impactsForAllPoints;
	double left;
	double bottom;
	double right;
	double top;
	int width;
	int height;
	double distance;
	vector<vector<double>> Points;
	vector<vector<int>> Connections;
	double Alltmax = -1;
	double Alltmin = -1;
};
#endif