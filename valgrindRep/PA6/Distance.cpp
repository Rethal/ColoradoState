#include <Distance.h>
double Distance::poseVectorCompare(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong) {

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

double Distance::poseVectorMed(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong) {
	double x1, x2, y1, y2, z1, z2, xdist, ydist, zdist, underRoot, pointCompare;
	vector<double> distVector;
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
		distVector.push_back(pointCompare);
	}
	sort(distVector.begin(), distVector.end());
	return distVector[12];
}
double Distance::poseVectorLinf(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong) {
	double x1, x2, y1, y2, z1, z2, xdist, ydist, zdist, underRoot, pointCompare;
	vector<double> distVector;
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
		distVector.push_back(pointCompare);
	}
	sort(distVector.begin(), distVector.end());
	return distVector[24];
}
double Distance::poseVectorL2(const vector<Point3D>& poseVectorShort, const vector<Point3D>& poseVectorLong) {
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
		pointCompare += abs(underRoot);
	}
	poseCompare = sqrt(pointCompare);
	return poseCompare;
}