#ifndef RAY_OBJECT
#define RAY_OBJECT
#include <vector>
#include <cmath>

using namespace std;
class Ray {
public:
	Ray(const vector<double>& locationVector, const vector<double>& startVector, double distance = 0) {
		//location vector
		LV = locationVector;
		LX = locationVector[0];
		LY = locationVector[1];
		LZ = locationVector[2];
		//direction is location minus start point, then normalized
		DX = LX - startVector[0];
		DY = LY - startVector[1];
		DZ = LZ - startVector[2];
		double magnitude = sqrt((DX * DX) + (DY * DY) + (DZ * DZ));
		DX = DX / magnitude;
		DY = DY / magnitude;
		DZ = DZ / magnitude;
		/*DX = DX*abs(distance);
		DY = DY*abs(distance);
		DZ = DZ*abs(distance);*/
		DV.clear();
		DV.push_back(DX);
		DV.push_back(DY);
		DV.push_back(DZ);
		//set default color to 0
		bestImpactKD.reserve(3); bestImpactKS.reserve(3); bestImpactKA.reserve(3); bestImpactSNRM.reserve(3); bestImpact.reserve(3);
		//Color.push_back(0); Color.push_back(0); Color.push_back(0);
	}
	double closestImpact = -1;
	//double r, b, g = -1;
	double LX, LY, LZ;
	double DX, DY, DZ;
	vector<double> DV;
	vector<double> LV;
	vector<double> Color = { 0,0,0 };
	vector<double> bestImpactKD, bestImpactKS, bestImpactKA, bestImpactSNRM, bestImpact;
	bool isSphere = false;
	bool isModel = false;
	bool isLight = false;

	/*px = RR(i / (width - 1)*(right - left) + left)
		py = RR(j / (height - 1)*(top - bottom) + bottom)
		# Naming is base point L and direction U
		//this is pixelpt:
		Lv = CEv + (near * CWv) + (px * CUv) + (py * CVv)
		//this is D:
		Uv = Lv - CEv; Uv = Uv / Uv.norm()
		return{ 'L' : Lv, 'U' : Uv }*/
};

#endif