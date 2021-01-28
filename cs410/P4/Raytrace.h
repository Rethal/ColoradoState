#ifndef RAYTRACER
#define RAYTRACER
#include "Camera.h"
#include "Ray.h"

//at this point, camera is a scene, not just a camera
class Raytracer {
public:
	Raytracer(const Camera& cam) {
		EV = cam.eye;
		LV = cam.look;
		UP = cam.up;
		WV = subtractBfromA(EV, LV);
		left = cam.bounds[0];
		bottom = cam.bounds[1];
		right = cam.bounds[2];
		top = cam.bounds[3];
		width = cam.res[0];
		height = cam.res[1];
		distance = cam.d;
		ambient = cam.ambient;
		lights = cam.lights;
		models = cam.models;
		spheres = cam.spheres;
		WV = normalize(WV);
		UV = cross_product(UP, WV);
		UV = normalize(UV);
		VV = cross_product(WV, UV);
	}

	//vector math
	vector<double> normalize(const vector<double>& inVector);
	vector<double> cross_product(const vector<double>& u, const vector<double>& v);
	double dot_product(const vector<double>& u, const vector<double>& v);
	vector<double> pairwise_product(const vector<double>& u, const vector<double>& v);
	int pixelMap();
	vector<double> subtractBfromA(const vector<double>& A, const vector<double>& B);
	vector<double> scalarMultiply(double scalar, const vector<double>& Vec);
	vector<double> vectorAdd(const vector<double>& A, const vector<double>& B);

	int rayCaster();
	vector<double> rayTrace(Ray& ray, vector<double> accumulation = { 0,0,0 }, vector<double> attenuation = { 1, 1, 1 }, int level = 7);
	int modelRun(Ray& ray);
	int sphereRun(Ray& ray);
	vector<double> rayColor(const vector<double>& Ka, const vector<double>& Ks, const vector<double>& Kd, const vector<double>& snrm, Ray& ray);

	//important vectors
	vector<vector<vector<double>>> pixpt;
	vector<double> EV;
	vector<double> LV;
	vector<double> UP;
	vector<double> WV;
	vector<double> UV;
	vector<double> VV;

	//impacts for t table
	/*vector<double> impactsForARow;
	vector<vector<double>> impactsForAllPoints;*/
	//impacts for ray table
	vector<Ray> raysInARow;
	vector<vector<Ray>> allRayImpacts;
	double left;
	double bottom;
	double right;
	double top;
	int width;
	int height;
	double distance;

	//new variables
	vector<double> ambient;
	vector<Light> lights;
	vector<Sphere> spheres;
	vector<ObjModel> models;

	double Alltmax = -1;
	double Alltmin = -1;
};

#endif