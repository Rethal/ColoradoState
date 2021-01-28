#include "Raycast.h"

vector<double> raytracer::normalize(const vector<double>& inVector) {
	/*The magnitude (length) of the vector is,
	length = sqrt((ax * ax) + (ay * ay) + (az * az))
	length = sqrt(9 + 1 + 4) = 3.742*/
	double x = inVector[0];
	double y = inVector[1];
	double z = inVector[2];
	vector<double> outVector;
	double magnitude = sqrt((x * x) + (y*y) + (z*z));
	double newX = x / magnitude;
	double newY = y / magnitude;
	double newZ = z / magnitude;
	outVector.push_back(newX);
	outVector.push_back(newY);
	outVector.push_back(newZ);

	return outVector;
}

vector<double> raytracer::cross_product(const vector<double>& u, const vector<double>& v) {
	/*The cross product a × b is defined as a vector c that is perpendicular to both a and b, with a direction given by the right-hand rule and a magnitude equal to the area of the parallelogram that the vectors span.
	abs(a)abs(b)sin(theta)n*/
	//(u2v3-u3v2)i+(u3v1-u1v3)j+(u1v2-u2v1)k
	/*cout << "got here" << endl;
	cout << u[0] << " " << u[1] << " " << u[2] << " " << v[0] << " " << v[1] << " " << v[2] << endl;*/
	double I = (u[1] * v[2]) - (u[2] * v[1]);
	double J = (u[2] * v[0]) - (u[0] * v[2]);
	double K = (u[0] * v[1]) - (u[1] * v[0]);
	vector<double> newVector;
	newVector.push_back(I);
	newVector.push_back(J);
	newVector.push_back(K);
	return newVector;
}

int raytracer::pixelMap() {
	pixpt.resize(width);
	for (int i = 0; i < width; i++) {
		pixpt[i].resize(height);
		double px = ((double)i / (width - 1))*(right - left) + left;
		for (int j = 0; j < height; j++) {
			pixpt[i][j].resize(3);
			double py = ((double)j / (height - 1))*(top - bottom) + bottom;
			vector<double> pixelPoint = vectorAdd(EV, vectorAdd(scalarMultiply(-distance, WV), vectorAdd(scalarMultiply(px, UV), scalarMultiply(py, VV))));
			//cout << pixelPoint[0] << endl;
			//cout << pixelPoint[1] << endl;
			//cout << pixelPoint[2] << endl;
			//pixpt[i][j].push_back
			pixpt[i][j][0] = pixelPoint[0];
			//cout << "check 8" << endl;
			pixpt[i][j][1] = pixelPoint[1];
			pixpt[i][j][2] = pixelPoint[2];
			//cout << px << " " << py << "|";
			//cout << "i: " << i << " j: " << j << " " << pixpt[i][j][0] << "," << pixpt[i][j][1] << "," << pixpt[i][j][2] << " ";
		}
		//cout << endl;
	}
	return 0;
}

vector<double> raytracer::subtractBfromA(const vector<double>& A, const vector<double>& B) {
	vector<double> returnVec;
	double X = A[0] - B[0];
	double Y = A[1] - B[1];
	double Z = A[2] - B[2];
	returnVec.push_back(X);
	returnVec.push_back(Y);
	returnVec.push_back(Z);
	return returnVec;
}

vector<double> raytracer::vectorAdd(const vector<double>& A, const vector<double>& B) {
	vector<double> returnVec;
	double X = A[0] + B[0];
	double Y = A[1] + B[1];
	double Z = A[2] + B[2];
	returnVec.push_back(X);
	returnVec.push_back(Y);
	returnVec.push_back(Z);
	return returnVec;
}

vector<double> raytracer::scalarMultiply(double scalar, const vector<double>& Vec) {
	vector<double> returnVec;
	for (unsigned int i = 0; i < Vec.size(); i++) {
		double point = scalar*Vec[i];
		returnVec.push_back(point);
	}
	return returnVec;
}

int raytracer::rayCaster() {
	for (int i = 0; i < height; i++) {
		//a, b, c are points
		double ax, ay, az, bx, by, bz, cx, cy, cz, dx, dy, dz, lx, ly, lz;
		double beta;
		double gamma;
		for (int j = 0; j < width; j++) {
			//l is point of origination
			//d is direction of ray
			double t = -1;
			double tmin = -1;
			lx = pixpt[j][i][0];
			ly = pixpt[j][i][1];
			lz = pixpt[j][i][2];
			dx = lx - EV[0];
			dy = ly - EV[1];
			dz = lz - EV[2];
			double magnitude = sqrt((dx * dx) + (dy * dy) + (dz * dz));
			dx = dx / magnitude;
			dy = dy / magnitude;
			dz = dz / magnitude;
			dx = dx*abs(distance);
			dy = dy*abs(distance);
			dz = dz*abs(distance);
			//cout << dx << " " << dy << " " << dz << endl;
			for (unsigned int face = 0; face < Connections.size(); face++) {
				int vertex1, vertex2, vertex3;
				vertex1 = Connections[face][1];
				vertex2 = Connections[face][2];
				vertex3 = Connections[face][3];
				ax = Points[vertex1][0];
				ay = Points[vertex1][1];
				az = Points[vertex1][2];
				bx = Points[vertex2][0];
				by = Points[vertex2][1];
				bz = Points[vertex2][2];
				cx = Points[vertex3][0];
				cy = Points[vertex3][1];
				cz = Points[vertex3][2];
				//cout << vertex1 << " " << vertex2 << " " << vertex3 << endl;
				//cout << ax << " " << ay << " " << az << endl;
				//cout << bx << " " << by << " " << bz << endl;
				//cout << cx << " " << cy << " " << cz << endl;
				double M1 = (((az - cz)*dy - (ay - cy)*dz)*(ax - lx)) - (((az - cz)*dx - (ax - cx)*dz)*(ay - ly)) + (((ay - cy)*dx - (ax - cx)*dy)*(az - lz));
				double M = (((az - cz)*dy - (ay - cy)*dz)*(ax - bx)) - (((az - cz)*dx - (ax - cx)*dz)*(ay - by)) + (((ay - cy)*dx - (ax - cx)*dy)*(az - bz));
				beta = M1 / M;
				//cout << beta << endl;
				if (beta >= 0 && beta <= 1) {
					double M2 = (((az - lz)*dy - (ay - ly)*dz)*(ax - bx)) - (((az - lz)*dx - (ax - lx)*dz)*(ay - by)) + (((ay - ly)*dx - (ax - lx)*dy)*(az - bz));
					gamma = M2 / M;
					//cout << "check 1" << endl;
					if (gamma >= 0 && (beta + gamma) <= 1) {
						//cout << "check 2" << endl;
						double M3 = (((ay - ly)*(az - cz)) - ((ay - cy)*(az - lz)))*(ax - bx) - (((ax - lx)*(az - cz)) - ((ax - cx)*(az - lz)))*(ay - by) + (((ax - lx)*(ay - cy)) - ((ax - cx)*(ay - ly)))*(az - bz);
						t = M3 / M;
					}
				}
				else {
					t = -1;
				}
				if ((tmin == -1 || t < tmin) && t > 0) {
					tmin = t;
				}
			}
			t = tmin;
			if ((Alltmin == -1 || t < Alltmin) && t != -1) {
				Alltmin = t;
			}
			if (Alltmax == -1 || t > Alltmax) {
				Alltmax = t;
			}
			impactsForARow.push_back(t);
			//cout << "ray: " << i << " " << j << endl;
		}
		impactsForAllPoints.push_back(impactsForARow);
		impactsForARow.clear();
	}
	return 0;
}

//px in UV and py in VV to each pixpt
//pixpt = EV + [-d* (WV)] + [px * UV] + [py * VV]
//px = i/(width-1)*(right-left)+left
//py = j/(height-1)*(top-bottom)+bottom
//column row
//width height
//for(i(for(j))))

