#include <multistick.h>

double multistick::singleDistCompare(stick& firstIn, stick& secondIn, string DistanceType) {
	//vector<vector<double>> Distances;
	if (comparePosesMulti(firstIn, secondIn, DistanceType) == -1) {
		cerr << "error: comparison failed";
		return -1;
	}
	double Returned = recursiveMatch(fileDistances);
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
		//cout << comparison << endl;
		//cout << argv[savedArg] << endl;
	}
	return savedArg;
}
int multistick::selfCompare(const stick& firstIn) {
	int endFrame = firstIn.timeVector.size();
	double comparison;
	//double prevcompare = 0;
	double truecomp;
	double minValue = -1;
	int savedArg = -1;
	if (endFrame < 60) {
		cerr << "error: too few distances to compare" << endl;
		return -1;
	}
	for (unsigned int i = 30; i < (endFrame-i); i++) {
		stick Selfiestick(firstIn, i, 0);
		//cout << Selfiestick.timeVector.size() << endl;
		stick LongSelfie(firstIn, endFrame, i);
		//cout << LongSelfie.timeVector.size() << endl;
		truecomp = singleDistCompare(Selfiestick, LongSelfie, "L2");
		/*comparison = truecomp - prevcompare;
		prevcompare = truecomp;*/
		comparison = truecomp/i;
		//cout << minValue << endl;
		//cout << comparison << endl;
		if (comparison == -1) {
			return -1;
		}
		else if (minValue == -1 || comparison < minValue) {
			minValue = comparison;
			savedArg = i;
		}
		//cout << "length: " << i << " distance: " << comparison << endl;
		//cout << "prev: " << prevcompare << endl;
	}
	//cout << "0" << endl;
	cout << savedArg << endl;
	//cout << minValue << endl;
	return savedArg;
}

int multistick::dynamicMatch(const stick& firstIn, const stick& secondIn, string distanceType) {
	//passes short in first
	if (firstIn.timeVector.size() > secondIn.timeVector.size()) {
		if (comparePosesMulti(secondIn, firstIn, distanceType) == -1) {
			return -1;
		}
	}
	else {
		if (comparePosesMulti(firstIn, secondIn, distanceType) == -1) {
			return -1;
		}
	}
	double Returned = recursiveMatch(fileDistances);
	cout << Returned << endl;
	return 0;
	/*for (unsigned int i = fileDistances.size()-1; i > 0; i--) {
	vector<double> poseDistances = fileDistances[i];
	unsigned int j = poseDistances.size();
	for (vector<double>::const_iterator iter2 = poseDistances.begin(); iter2 != poseDistances.end(); iter2++) {
	}
	}*/
}

int multistick::comparePosesMulti(const stick& StickShort, const stick& StickLong, string distanceType) {
	vector<Point3D> poseVectorShort;
	poseVectorShort.reserve(25);
	vector<Point3D> poseVectorLong;
	poseVectorLong.reserve(25);
	vector<double> poseDistances;
	int allDistances = StickShort.timeVector.size()*StickLong.timeVector.size();
	poseDistances.reserve(allDistances);
	fileDistances.clear();
	if (StickShort.timeVector.size() < 1 || StickLong.timeVector.size() < 1) {
		cerr << "error: not enough poses" << endl;
		return -1;
	}
	unsigned int i = 0;
	while (i < StickShort.timeVector.size()) {
		poseVectorShort = StickShort.timeVector[i];
		unsigned int k = 0;
		while (k < StickLong.timeVector.size()) {
			poseVectorLong = StickLong.timeVector[k];
			Distance d(poseVectorShort, poseVectorLong, distanceType);
			double poseCompare = d.Comparison;//distance::poseVectorCompare(poseVectorShort, poseVectorLong);
											  //cout << poseCompare << endl;
			poseDistances.push_back(poseCompare);
			k++;
		}
		fileDistances.push_back(poseDistances);
		poseDistances.clear();
		i++;
	}
	return 0;
}

double multistick::recursiveMatch(const vector<vector<double>>& distMatrix, int i, int base) {
	int col = distMatrix[0].size();
	int row = distMatrix.size();

	double minValue = 0;
	vector<vector<double>> w_array;
	w_array.resize(row);
	for (int i = 0; i < row; i++) {
		w_array[i].resize(col);
	}

	for (int j = 0; j < col; j++) {
		w_array[0][j] = distMatrix[0][j];
	}

	for (int i = 1; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (j == 0) {
				minValue = w_array[i - 1][0];
			}
			minValue = min(minValue, w_array[i - 1][j]);
			w_array[i][j] = distMatrix[i][j] + minValue;
		}
	}

	minValue = DBL_MAX;
	for (int i = 0; i < col; i++) {
		if (w_array[row - 1][i] < minValue) {
			minValue = w_array[row - 1][i];
		}
	}

	return minValue;
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