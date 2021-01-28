//#include <multistick.h>
//
//
//ofstream audi;
//vector<vector<double>> fileDistances;
//
//
//int multistick::comparePosesMulti(const stick& StickShort, const stick& StickLong) {
//	vector<Point3D> poseVectorShort;
//	vector<Point3D> poseVectorLong;
//	vector<double> poseDistances;
//	
//	double x1, x2, y1, y2, z1, z2, xdist, ydist, zdist, underRoot, pointCompare;
//	for (unsigned int i = 0; i < StickShort.timeVector.size(); i++) {
//		double poseCompare = 0;
//		poseVectorShort = StickShort.timeVector[i];
//		for (unsigned int k = 0; k < StickLong.timeVector.size(); k++) {
//			poseVectorLong = StickLong.timeVector[k];
//			for (unsigned int j = 0; j < poseVectorShort.size(); j++) {
//				x1 = poseVectorShort[j].X();
//				x2 = poseVectorLong[j].X();
//				y1 = poseVectorShort[j].Y();
//				y2 = poseVectorLong[j].Y();
//				z1 = poseVectorShort[j].Z();
//				z2 = poseVectorLong[j].Z();
//				xdist = x1 - x2;
//				ydist = y1 - y2;
//				zdist = z1 - z2;
//				underRoot = (xdist*xdist) + (ydist*ydist) + (zdist*zdist);
//				pointCompare = sqrt(underRoot);
//				poseCompare += abs(pointCompare);
//			}
//			poseDistances.push_back(poseCompare);
//		}
//		fileDistances.push_back(poseDistances);
//		poseDistances.clear();
//	}
//	return 0;
//}
//
//int multistick::fileDistPrintMulti(const stick& firstIn, const stick& secondIn, string outFile) {
//	
//	//passes short in first
//	if (firstIn.timeVector.size() > secondIn.timeVector.size()) {
//		comparePosesMulti(secondIn, firstIn);
//	}
//	else {
//		comparePosesMulti(firstIn, secondIn);
//	}
//	if (!multistick::openOutFileMulti(outFile)) return -1;
//	if (!multistick::writeDistanceMulti()) return -1;
//	return 0;
//}
//
//bool multistick::openOutFileMulti(string outFile) {
//	audi.open(outFile.c_str());
//	if (!audi) {
//		cerr << "error: could not open output file " << outFile << endl;
//		return false;
//	}
//	return true;
//}
//
//bool multistick::writeDistanceMulti()
//{
//	for (unsigned int i = 0; i < fileDistances.size();i++) {
//		vector<double> poseDistances = fileDistances[i];
//		for (vector<double>::const_iterator iter2 = poseDistances.begin(); iter2 != poseDistances.end(); iter2++) {
//			audi << *iter2 << " ";
//		}
//		audi << endl;
//	}
//	return !(audi.fail());
//}