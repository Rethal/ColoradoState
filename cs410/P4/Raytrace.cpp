#include "Raytrace.h"

vector<double> Raytracer::normalize(const vector<double>& inVector) {
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
	if (magnitude == 0) {
		newX = 0;
		newY = 0;
		newZ = 0;
	}
	outVector.push_back(newX);
	outVector.push_back(newY);
	outVector.push_back(newZ);

	return outVector;
}

vector<double> Raytracer::cross_product(const vector<double>& u, const vector<double>& v) {
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

double Raytracer::dot_product(const vector<double>& u, const vector<double>& v) {
	if (u.size() != v.size()) {
		return -1;
	}
	else {
		double scalar = 0;
		for (unsigned int i = 0; i < u.size(); i++) {
			scalar = scalar + (u[i] * v[i]);
		}
		return scalar;
	}
}

vector<double> Raytracer::pairwise_product(const vector<double>& u, const vector<double>& v) {
	vector<double> returnVec;
	//if (u.size() != v.size()) {
	//	returnVec.push_back(-1);
	//	return returnVec;
	//}
	//else {
	for (unsigned int i = 0; i < u.size(); i++) {
		double prod = u[i] * v[i];
		returnVec.push_back(prod);
	}
	return returnVec;
}

int Raytracer::pixelMap() {
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

vector<double> Raytracer::subtractBfromA(const vector<double>& A, const vector<double>& B) {
	vector<double> returnVec;
	double X = A[0] - B[0];
	double Y = A[1] - B[1];
	double Z = A[2] - B[2];
	returnVec.push_back(X);
	returnVec.push_back(Y);
	returnVec.push_back(Z);
	return returnVec;
}

vector<double> Raytracer::vectorAdd(const vector<double>& A, const vector<double>& B) {
	vector<double> returnVec;
	double X = A[0] + B[0];
	double Y = A[1] + B[1];
	double Z = A[2] + B[2];
	returnVec.push_back(X);
	returnVec.push_back(Y);
	returnVec.push_back(Z);
	return returnVec;
}

vector<double> Raytracer::scalarMultiply(double scalar, const vector<double>& Vec) {
	vector<double> returnVec;
	for (unsigned int i = 0; i < Vec.size(); i++) {
		double point = scalar*Vec[i];
		returnVec.push_back(point);
	}
	return returnVec;
}

int Raytracer::rayCaster() {
	for (int i = 0; i < height; i++) {
		//a, b, c are points

		for (int j = 0; j < width; j++) {
			//l is point of origination
			//d is direction of ray
			Ray ray(pixpt[j][i], EV, distance);
			//sphereRun(ray);
			//modelRun(ray);
			ray.Color = rayTrace(ray);
			
			//cout << dx << " " << dy << " " << dz << endl;
			raysInARow.push_back(ray);
			//cout << "ray: " << i << " " << j << endl;
		}
		//impactsForAllPoints.push_back(impactsForARow);
		allRayImpacts.push_back(raysInARow);
		raysInARow.clear();
		//impactsForARow.clear();
	}
	return 0;
}

int Raytracer::modelRun(Ray& ray) {
	double ax, ay, az, bx, by, bz, cx, cy, cz, dx, dy, dz, lx, ly, lz = 0;
	double beta;
	double gamma;
	double t = -1;
	//lookvector
	//Lv = ray['L']
	//L is base point of ray, U/D is direction
	vector<double> cLV = ray.LV;
	//lookvector - eyevetor
	//Uv = ray['U']
	vector<double> Dv = ray.DV;
	for (unsigned int model = 0; model < models.size(); model++) {
		//check for impact - if impact is true, check for color
		for (unsigned int face = 0; face < models[model].faces.size(); face++) {
			//get KA of a face: models[model].faces[face].MT.KA;
			ax = models[model].faces[face].A.X;
			ay = models[model].faces[face].A.Y;
			az = models[model].faces[face].A.Z;
			bx = models[model].faces[face].B.X;
			by = models[model].faces[face].B.Y;
			bz = models[model].faces[face].B.Z;
			cx = models[model].faces[face].C.X;
			cy = models[model].faces[face].C.Y;
			cz = models[model].faces[face].C.Z;
			lx = ray.LX;
			ly = ray.LY;
			lz = ray.LZ;
			dx = ray.DX;
			dy = ray.DY;
			dz = ray.DZ;
			//cout << ax << " " << ay << " " << az << " " << bx << " " << by << " " << bz << " " << cx << " " << cy << " " << cz << endl;
			double M1 = (((az - cz)*dy - (ay - cy)*dz)*(ax - lx)) - (((az - cz)*dx - (ax - cx)*dz)*(ay - ly)) + (((ay - cy)*dx - (ax - cx)*dy)*(az - lz));
			double M = (((az - cz)*dy - (ay - cy)*dz)*(ax - bx)) - (((az - cz)*dx - (ax - cx)*dz)*(ay - by)) + (((ay - cy)*dx - (ax - cx)*dy)*(az - bz));
			beta = M1 / M;
			//cout << beta << endl;
			if (beta >= 0 && beta <= 1) {
				double M2 = (((az - lz)*dy - (ay - ly)*dz)*(ax - bx)) - (((az - lz)*dx - (ax - lx)*dz)*(ay - by)) + (((ay - ly)*dx - (ax - lx)*dy)*(az - bz));
				gamma = M2 / M;
				//cout << gamma << endl;
				//cout << "check 1" << endl;
				if (gamma >= 0 && (beta + gamma) <= 1) {
					//cout << "check 2" << endl;
					double M3 = (((ay - ly)*(az - cz)) - ((ay - cy)*(az - lz)))*(ax - bx) - (((ax - lx)*(az - cz)) - ((ax - cx)*(az - lz)))*(ay - by) + (((ax - lx)*(ay - cy)) - ((ax - cx)*(ay - ly)))*(az - bz);
					t = M3 / M;
					//do color
					if ((t > 0.00001) && (ray.closestImpact == -1 || t < ray.closestImpact)) {
						ray.closestImpact = t;
						/*if (ray.isLight) {
							cout << "Light impact" << endl;
						}*/
						if(!ray.isLight) {
							ray.bestImpactKD = models[model].faces[face].MT.KD.vertexVec;
							ray.bestImpactKS = models[model].faces[face].MT.KS.vertexVec;
							ray.bestImpactKA = models[model].faces[face].MT.KA.vertexVec;
							//pt = Lv + t * Uv
							vector<double> pt = vectorAdd(cLV, scalarMultiply(t, Dv));
							//now for the color
							//snrm = ptos - sph['c']; snrm = snrm / snrm.norm()
							vector<double> snrm = models[model].faces[face].An.vertexVec;// snrm = normalize(snrm);
							ray.bestImpactSNRM = snrm;
							ray.bestImpact = vectorAdd(ray.LV, scalarMultiply(ray.closestImpact, ray.DV));
							ray.isModel = true;
							ray.isSphere = false;

							//ray.Color.clear();
							//ray.Color = rayColor(models[model].faces[face].MT.KA.vertexVec, models[model].faces[face].MT.KS.vertexVec, models
							//	[model].faces[face].MT.KD.vertexVec, snrm, ray);
						}
					}
				}
			}

		}
	}
	return 0;
}

int Raytracer::sphereRun(Ray& ray) {
	//lookvector
	//Lv = ray['L']
	//L is base point of ray, U/D is direction
	vector<double> cLV = ray.LV;
	//lookvector - eyevetor
	//Uv = ray['U']
	vector<double> Dv = ray.DV;
	for (unsigned int sphere = 0; sphere < spheres.size(); sphere++) {
		/*if (ray.isLight) {
			cout << "got here" << endl;
		}*/
		//check for impact - if impact is true, check for color
		//r = sph['r']
		double r = spheres[sphere].radius;
		//Cv = sph['c']
		vector<double> center = spheres[sphere].Center;
		//Tv = vector(RR, 3, (Cv - Lv))
		vector<double> cTV = subtractBfromA(center, cLV);
		//v = Tv.dot_product(Uv)
		double v = dot_product(cTV, Dv);
		//csq = Tv.dot_product(Tv)
		double csq = dot_product(cTV, cTV);
		//disc = r ^ 2 - (csq - v ^ 2)
		double rsq = r*r;
		double vsq = v*v;
		double disc = rsq - (csq - vsq);
		if (disc >= 0) {
			//cout << "r: " << r << " v: " << v << " csq: " << csq << " disc: " << disc << endl;
			//distance between point of impact and dot-product spot (closest point on ray to center of sphere)
			//d = sqrt(disc)
			double D = sqrt(disc);
			//distance from beginning of ray to point of impact
			//t = v - d
			double T = v - D;
			//check to see if it's the closest impact of this ray so far; if so, calculate color, then set ray color to new color
			if ((T > 0.00001) && (ray.closestImpact == -1 || T < ray.closestImpact)) {
				ray.closestImpact = T;
				/*if (ray.isLight) {
					cout << "Light impact" << endl;
				}*/
				if (!ray.isLight) {
					ray.bestImpactKD = spheres[sphere].Kd;
					ray.bestImpactKS = spheres[sphere].Ks;
					ray.bestImpactKA = spheres[sphere].Kd;
					//pt = Lv + t * Uv
					vector<double> pt = vectorAdd(cLV, scalarMultiply(T, Dv));
					//now for the color
					//snrm = ptos - sph['c']; snrm = snrm / snrm.norm()
					vector<double> snrm = subtractBfromA(pt, center); snrm = normalize(snrm);
					ray.bestImpactSNRM = snrm;
					ray.bestImpact = vectorAdd(ray.LV, scalarMultiply(ray.closestImpact, ray.DV));
					ray.isModel = false;
					ray.isSphere = true;
					//ray.Color.clear();
					//ray.Color = rayColor(spheres[sphere].Ka, spheres[sphere].Ks, spheres[sphere].Kd, snrm, ray);
				}
			}
			//cout << endl;
		}
	}
	return 0;
}

vector<double> Raytracer::rayTrace(Ray& ray, vector<double> accumulation, vector<double> attenuation, int level) {
	sphereRun(ray);
	modelRun(ray);
	ray.Color = rayColor(ray.bestImpactKA, ray.bestImpactKS, ray.bestImpactKD, ray.bestImpactSNRM, ray);
	if (ray.closestImpact > 0) {
		//cout << ray.closestImpact << endl;
		//cout << level << endl;

		//all code goes in here
		//need to find Ray best impact point: 	self.best_pt = self.L + (tval * self.D)
		vector<double> N = ray.bestImpactSNRM;
		ray.bestImpact = vectorAdd(ray.LV, scalarMultiply(ray.closestImpact, ray.DV));

		vector<double> color = ray.Color;//rayColor(ray.bestImpactKA, ray.bestImpactKS, ray.bestImpactKD, ray.bestImpactSNRM, ray);

		for (int i = 0; i < 3; i++) {
			accumulation[i] = accumulation[i] + (attenuation[i] * color[i]);
		}
		if (level > 0) {
			vector<double> UInv = scalarMultiply(-1, ray.DV);
			vector<double> refR = normalize(subtractBfromA(scalarMultiply(2 * dot_product(N, UInv), N), UInv));
			refR = vectorAdd(refR, ray.bestImpact);
			Ray nextRay(refR, ray.bestImpact);
			//nextRay.DV = refR;
			//cout << nextRay.closestImpact << endl;
			if (ray.isSphere) {
				attenuation = { .9, .9, .9 };
			}
			else {
				attenuation = { .2, .2, .2 };
			}
			accumulation = rayTrace(nextRay, accumulation, attenuation, level - 1);
		}

		//Ray nextRay()
		//refR = make_unit((2 * np.dot(N, Uinv) * N) - Uinv) //NEXT RAY POINT FOR DIRECTION
			//ray_trace(Ray(ray.best_pt, refR), accum, mat.kr * refatt, (level - 1))
			//return accum* /
	}
	return accumulation;
}

vector<double> Raytracer::rayColor(const vector<double>& Ka, const vector<double>& Ks, const vector<double>& Kd, const vector<double>& snrm, Ray& ray) {
	vector<double> cLV = ray.LV;
	vector<double> Dv = ray.DV;
	double T = ray.closestImpact;
	vector<double> pt = vectorAdd(cLV, scalarMultiply(T, Dv));
	//now for the color
	//color = ambient.pairwise_product(mat1['ka'])
	vector<double> color = pairwise_product(ambient, Ka);
	//cout << "R: " << color[0] << " G: " << color[1] << " B: " << color[2] << endl;
	//cout << "Ambient: " << ambient[0] << " " << ambient[1] << " " << ambient[2] << endl;
	//cout << "KASD" << spheres[sphere].simpKaKsKd[0] << " " << spheres[sphere].simpKaKsKd[1] << " " << spheres[sphere].simpKaKsKd[2] << endl;
	//for lt in lights :
	for (unsigned int lightIndex = 0; lightIndex < lights.size(); lightIndex++) {
		//ptL = lt['p']
		vector<double> lightpoint = lights[lightIndex].pos;
		//emL = lt['e']
		vector<double> lightcolor = lights[lightIndex].color;
		//toL = ptL - ptos; toL = toL / toL.norm()
		vector<double> toL = subtractBfromA(lightpoint, pt); 
		//cout << "got here" << T << endl;

		//cout << pt[0] << " " << pt[1] << " " << pt[2] << endl;
		//cout << lightIndex << endl;

		//shadows (not working)
		//Ray LightRay(pt, lightpoint);
		//LightRay.isLight = true;
		//	sphereRun(LightRay);
		//	//cout << "got here" << endl;
		//	modelRun(LightRay);
		//	//cout << "light done" << endl;


		//to calculate shadow, if impact is closer than light then don't add light
		double LightDist = sqrt((toL[0] * toL[0]) + (toL[1]*toL[1]) + (toL[2]*toL[2]));
		//unfortunately only works if the ray knows it's impacted something else at this point

		toL = normalize(toL);
		//if (snrm.dot_product(toL) > 0.0) :
		//cout << toL[0] << " " << toL[1] << " " << toL[2] << endl;
		//cout << Light.closestImpact << endl;
		//cout << LightDist << endl;
		if ((dot_product(snrm, toL) > 0)){// && (LightRay.closestImpact > 0 && LightRay.closestImpact <= LightDist)) {
			//color += mat1['kd'].pairwise_product(emL) * snrm.dot_product(toL)
			color = vectorAdd(color, scalarMultiply(dot_product(snrm, toL), pairwise_product(Kd, lightcolor)));
			//toC = ray['L'] - ptos; toC = toC / toC.norm()
			vector<double> toC = subtractBfromA(ray.LV, pt); toC = normalize(toC);
			//spR = (2 * snrm.dot_product(toL) * snrm) - toL
			vector<double> spR = subtractBfromA(scalarMultiply((2 * dot_product(snrm, toL)), snrm), toL);
			//color += mat1['ks'].pairwise_product(emL) * toC.dot_product(spR)**16
			color = vectorAdd(color, scalarMultiply((pow(dot_product(toC, spR), 16)), pairwise_product(Ks, lightcolor)));
		}
	}
	//set color of ray to calculated color
	//ray.Color.clear();
	//ray.Color.push_back(color[0]); ray.Color.push_back(color[1]); ray.Color.push_back(color[2]);
	//cout << "R: " << ray.Color[0] << " G: " << ray.Color[1] << " B: " << ray.Color[2];
	return color;
}