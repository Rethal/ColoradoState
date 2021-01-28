#include <multistick.h>

double multistick::singleDistCompare(stick& firstIn, stick& secondIn, string DistanceType) {
	//vector<vector<double>> Distances;
	cout << "got here" << endl;

	if (firstIn.comparePosesMulti(firstIn, secondIn, DistanceType) == -1) {
		cerr << "error: comparison failed";
		return -1;
	}
	cout << "got here" << endl;
	double Returned = firstIn.recursiveMatch(firstIn.fileDistances);
	return Returned;
//cout << Returned << endl;
}
int multistick::compareIterator(int argc, char* argv[]) {
	ifstream inFile(argv[1]);
	if (!inFile.good()) {
		cerr << "error: Filename not recognized" << endl;
		return -1;
	}
	string distanceType(argv[argc - 1]);
	if (distanceType != "avg" && distanceType != "med" && distanceType != "Linf" && distanceType != "L2") {
		cerr << "error: must select a valid distance type" << endl;
		return -1;
	}
	stick Stickman(inFile);
	int savedArg = -1;
	double comparison;
	double minValue = -1;
	for (int i = 2; i < (argc - 1); i++) {
		ifstream inFile2(argv[i]);
		if (!inFile2.good()) {
			cerr << "error: Filename not recognized" << endl;
			return -1;
		}
		stick Secondman(inFile2);
		if (Secondman.timeVector.size() > Stickman.timeVector.size()) {
			cerr << "error: " << argv[i] << "is longer than " << argv[1] << endl;
			return -1;
		}
		comparison = singleDistCompare(Secondman, Stickman, distanceType);
		if (comparison == -1) {
			return -1;
		}
		else if (minValue == -1 || comparison < minValue) {
			minValue = comparison;
			savedArg = i;
		}
		cout << comparison << endl;
		cout << argv[savedArg] << endl;
	}
	return savedArg;
}



//ofstream audi;
//vector<vector<double>> filedistances;
//
//
//int multistick::compareposesmulti(const stick& stickshort, const stick& sticklong) {
//	vector<point3d> posevectorshort;
//	vector<point3d> posevectorlong;
//	vector<double> posedistances;
//	
//	double x1, x2, y1, y2, z1, z2, xdist, ydist, zdist, underroot, pointcompare;
//	for (unsigned int i = 0; i < stickshort.timevector.size(); i++) {
//		double posecompare = 0;
//		posevectorshort = stickshort.timevector[i];
//		for (unsigned int k = 0; k < sticklong.timevector.size(); k++) {
//			posevectorlong = sticklong.timevector[k];
//			for (unsigned int j = 0; j < posevectorshort.size(); j++) {
//				x1 = posevectorshort[j].x();
//				x2 = posevectorlong[j].x();
//				y1 = posevectorshort[j].y();
//				y2 = posevectorlong[j].y();
//				z1 = posevectorshort[j].z();
//				z2 = posevectorlong[j].z();
//				xdist = x1 - x2;
//				ydist = y1 - y2;
//				zdist = z1 - z2;
//				underroot = (xdist*xdist) + (ydist*ydist) + (zdist*zdist);
//				pointcompare = sqrt(underroot);
//				posecompare += abs(pointcompare);
//			}
//			posedistances.push_back(posecompare);
//		}
//		filedistances.push_back(posedistances);
//		posedistances.clear();
//	}
//	return 0;
//}
//
//int multistick::filedistprintmulti(const stick& firstin, const stick& secondin, string outfile) {
//	
//	//passes short in first
//	if (firstin.timevector.size() > secondin.timevector.size()) {
//		compareposesmulti(secondin, firstin);
//	}
//	else {
//		compareposesmulti(firstin, secondin);
//	}
//	if (!multistick::openoutfilemulti(outfile)) return -1;
//	if (!multistick::writedistancemulti()) return -1;
//	return 0;
//}
//
//bool multistick::openoutfilemulti(string outfile) {
//	audi.open(outfile.c_str());
//	if (!audi) {
//		cerr << "error: could not open output file " << outfile << endl;
//		return false;
//	}
//	return true;
//}
//
//bool multistick::writedistancemulti()
//{
//	for (unsigned int i = 0; i < filedistances.size();i++) {
//		vector<double> posedistances = filedistances[i];
//		for (vector<double>::const_iterator iter2 = posedistances.begin(); iter2 != posedistances.end(); iter2++) {
//			audi << *iter2 << " ";
//		}
//		audi << endl;
//	}
//	return !(audi.fail());
//}