#include "plyHeader.h"

using namespace std;
int HEADER::getHeader(ifstream& infile) {
	//string headerLine = "";
	//while (getline(infile, headerLine)) {
	//	istringstream iss;
	//	iss.str(headerLine);
	//	string word;
	//	iss >> word;
	//	while (iss.good() && !iss.eof()) {
	//		string nextWord;
	//		string VALUE;
	//		if (strcmp(word, "format") == 0) {
	//			if (format.size() == 0) {
	//				format.push_back(word);
	//			}
	//			iss >> nextWord;
	//			format.push_back(nextWord);
	//		}
	//		else if (strcmp(word, "element") == 0)
	//			if (nextWord.size() == 0) {
	//				iss >> nextWord;
	//			}
	//			else {
	//				iss >> value;
	//			}
	//			if (strcmp(nextWord, "vertex") == 0) {
	//				if (vertex.size() == 0) {
	//					vertex.push_back(word);
	//				}
	//				else if (vertex.size() == 1) {
	//					vertex.push_back(nextWord);
	//				}
	//				else
	//					vertex.push_back(value);
	//			}
	//			else if (strcmp(nextWord, "face")) {
	//				if (face.size() == 0) {
	//					face.push_back(word);
	//				}
	//				else if (face.size() == 1) {
	//					face.push_back(nextWord);
	//				}
	//				else
	//					face.push_back(value);
	//			}
	//			else if (strcmp(word, "property")) {

	//			}
	//			else if (strcmp(word, "end_header")) {
	//				break;
	//			}
	//	}

	//}
	return 0;
}
int HEADER::getVertices(ifstream& infile) {
	string headerLineString = "";
	int startVertex = 0;
	while (getline(infile, headerLineString)) {
		headerLine.clear();
		istringstream iss;
		iss.str(headerLineString);
		string word;
		double x, y, z;
		int facePoints;
		if (startVertex == 0) {
			while (iss.good() && !iss.eof()) {
				if (iss >> word) {
					if (word.compare("element") == 0) {
						headerLine.push_back(word);
						string ELEMENT;
						int VALUE;
						iss >> ELEMENT;
						iss >> VALUE;
						headerLine.push_back(ELEMENT);
						headerLine.push_back(to_string(VALUE));
						if (ELEMENT.compare("vertex") == 0) {
							VERTICES = VALUE;
							curVert = VERTICES;
						}
						else if (ELEMENT.compare("face") == 0) {
							FACES = VALUE;
						}
					}
					else {
						headerLine.push_back(word);
					}
				}
			}
			totalHeader.push_back(headerLine);
			headerLine.clear();
		}
		if (startVertex == 1 && curVert != 0) {
			iss >> x;
			iss >> y;
			iss >> z;
			if (x > xMax || xMaxSet == 0) { xMax = x; }
			if (y > yMax || yMaxSet == 0) { yMax = y; }
			if (z > zMax || zMaxSet == 0) { zMax = z; }
			if (x < xMin || xMinSet == 0) { xMin = x; }
			if (y < yMin || yMinSet == 0) { yMin = y; }
			if (z < zMin || zMinSet == 0) { zMin = z; }
			setMinMax();
			XYZvertex.push_back(x);
			Xall.push_back(x);
			XYZvertex.push_back(y);
			Yall.push_back(y);
			XYZvertex.push_back(z);
			Zall.push_back(z);
			allXYZvertices.push_back(XYZvertex);
			XYZvertex.clear();
			curVert--;
		}
		if (startVertex == 1 && curVert == 0) {
			while (iss.good() && !iss.eof()) {
				if(iss >> facePoints)
					faceLine.push_back(facePoints);
			}
			if (faceLine.size() > 0) {
				totalFace.push_back(faceLine);
			}
			faceLine.clear();
		}
		if (word.compare("end_header") == 0) {
			startVertex = 1;
		}
	}
	return 0;
}
int HEADER::vecAvg(vector<double>& meanFind) {
	double mean;
	for (unsigned int i = 0; i < meanFind.size(); i++) {
		mean = mean + meanFind[i];
	}
	mean = mean / meanFind.size();
	return mean;
}
int HEADER::meanVertexFind() {
	meanVertex.clear();
	double x = vecAvg(Xall);
	double y = vecAvg(Yall);
	double z = vecAvg(Zall);
	meanVertex.push_back(x);
	meanVertex.push_back(y);
	meanVertex.push_back(z);
	return 0;
}
int HEADER::vectorNorm() {
	double xmean = meanVertex[0];
	double ymean = meanVertex[1];
	double zmean = meanVertex[2];
	resetMinMax();

	for (unsigned int i = 0; i < allXYZvertices.size(); i++) {
		double x = allXYZvertices[i][0];
		double y = allXYZvertices[i][1];
		double z = allXYZvertices[i][2];
		x = x - xmean;
		y = y - ymean;
		z = z - zmean;
		if (x > xMax || xMaxSet == 0) { xMax = x; }
		if (y > yMax || yMaxSet == 0) { yMax = y; }
		if (z > zMax || zMaxSet == 0) { zMax = z; }
		if (x < xMin || xMinSet == 0) { xMin = x; }
		if (y < yMin || yMinSet == 0) { yMin = y; }
		if (z < zMin || zMinSet == 0) { zMin = z; }
		setMinMax();
		XYZvertex.push_back(x);
		XYZvertex.push_back(y);
		XYZvertex.push_back(z);
		allXYZnormal.push_back(XYZvertex);
		XYZvertex.clear();
	}
	return 0;
}
int HEADER::stdDeviations() {
	double xStd, yStd, zStd;
	double x = xMax;
	double y = yMax;
	double z = zMax;
	if (abs(xMin) > xMax)
		x = abs(xMin);
	if (abs(yMin) > yMax)
		y = abs(yMin);
	if (abs(zMin) > zMax)
		z = abs(zMin);
	xStd = x - meanVertex[0];
	yStd = y - meanVertex[1];
	zStd = z - meanVertex[2];
	vector<double> standardDev;
	standardDev.push_back(xStd);
	standardDev.push_back(yStd);
	standardDev.push_back(zStd);
	currentDev = standardDev;
	return 0;
}
int HEADER::vectorWhite() {
	double xDev = currentDev[0];
	double yDev = currentDev[1];
	double zDev = currentDev[2];
	resetMinMax();

	for (unsigned int i = 0; i < allXYZnormal.size(); i++) {
		double x = allXYZnormal[i][0];
		double y = allXYZnormal[i][1];
		double z = allXYZnormal[i][2];
		x = x / xDev;
		y = y / yDev;
		z = z / zDev;
		if (x > xMax || xMaxSet == 0) { xMax = x; }
		if (y > yMax || yMaxSet == 0) { yMax = y; }
		if (z > zMax || zMaxSet == 0) { zMax = z; }
		if (x < xMin || xMinSet == 0) { xMin = x; }
		if (y < yMin || yMinSet == 0) { yMin = y; }
		if (z < zMin || zMinSet == 0) { zMin = z; }
		setMinMax();

		XYZvertex.push_back(x);
		XYZvertex.push_back(y);
		XYZvertex.push_back(z);
		allXYZwhite.push_back(XYZvertex);
		XYZvertex.clear();
	}
	return 0;
}
int HEADER::setMinMax() {
	xMaxSet = 1;
	yMaxSet = 1;
	zMaxSet = 1;
	xMinSet = 1;
	yMinSet = 1;
	zMinSet = 1;
	return 1;
}
int HEADER::resetMinMax() {
	xMaxSet = 0;
	yMaxSet = 0;
	zMaxSet = 0;
	xMinSet = 0;
	yMinSet = 0;
	zMinSet = 0;
	return 0;
}
int HEADER::meanVertexCorrect() {
	vector<double> newX;
	vector<double> newY;
	vector<double> newZ;
	double xMean = meanVertex[0];
	double yMean = meanVertex[1];
	double zMean = meanVertex[2];
	for (unsigned int i = 0; i < Xall.size(); i++) {
		double x = Xall[i] - xMean;
		newX.push_back(x);
	}
	for (unsigned int i = 0; i < Yall.size(); i++) {
		double y = Yall[i] - yMean;
		newY.push_back(y);
	}
	for (unsigned int i = 0; i < Xall.size(); i++) {
		double z = Zall[i] - zMean;
		newZ.push_back(z);
	}
	Xall = newX;
	Yall = newY;
	Zall = newZ;
	return 0;
}
int HEADER::whiteVertexCorrect() {
	vector<double> newX;
	vector<double> newY;
	vector<double> newZ;
	double xDev = currentDev[0];
	double yDev = currentDev[1];
	double zDev = currentDev[2];
	for (unsigned int i = 0; i < Xall.size(); i++) {
		double x = Xall[i] / xDev;
		newX.push_back(x);
	}
	for (unsigned int i = 0; i < Yall.size(); i++) {
		double y = Yall[i] / yDev;
		newY.push_back(y);
	}
	for (unsigned int i = 0; i < Xall.size(); i++) {
		double z = Zall[i] / zDev;
		newZ.push_back(z);
	}
	Xall = newX;
	Yall = newY;
	Zall = newZ;
	return 0;
}
int HEADER::projOneRun(string Title) {
	meanVertexFind();
	stdDeviations();
	cout << "=== Before centering" << endl;
	cout << VERTICES << " vertices, " << FACES << " polygons" << endl;
	cout << "Mean Vertex = (" << meanVertex[0] << ", " << meanVertex[1] << ", " << meanVertex[2] << ")" << endl;
	cout << "Bounding Box: " << xMin << " <= x <= " << xMax << ", " << yMin << " <= y <= " << yMax << ", " << zMin << " <= z <= " << zMax << endl;
	cout << "Standard Deviations: x = " << currentDev[0] << ", y = " << currentDev[1] << ", z = " << currentDev[2] << endl;
	vectorNorm();
	meanVertexCorrect();
	meanVertexFind();
	stdDeviations();
	cout << "=== After Centering" << endl;
	cout << VERTICES << " vertices, " << FACES << " polygons" << endl;
	cout << "Mean Vertex = (" << meanVertex[0] << ", " << meanVertex[1] << ", " << meanVertex[2] << ")" << endl;
	cout << "Bounding Box: " << xMin << " <= x <= " << xMax << ", " << yMin << " <= y <= " << yMax << ", " << zMin << " <= z <= " << zMax << endl;
	cout << "Standard Deviations: x = " << currentDev[0] << ", y = " << currentDev[1] << ", z = " << currentDev[2] << endl;
	printNorm(Title);
	vectorWhite();
	whiteVertexCorrect();
	stdDeviations();
	cout << "=== After Whitening" << endl;
	cout << VERTICES << " vertices, " << FACES << " polygons" << endl;
	cout << "Mean Vertex = (" << meanVertex[0] << ", " << meanVertex[1] << ", " << meanVertex[2] << ")" << endl;
	cout << "Bounding Box: " << xMin << " <= x <= " << xMax << ", " << yMin << " <= y <= " << yMax << ", " << zMin << " <= z <= " << zMax << endl;
	cout << "Standard Deviations: x = " << currentDev[0] << ", y = " << currentDev[1] << ", z = " << currentDev[2] << endl;
	printWhite(Title);
	//print, print
	return 0;
}
int HEADER::printToConsole() {
	return 0;
}
int HEADER::printNorm(string Title) {
	string rawname = Title.substr(0, Title.find_last_of("."));
	string newname = rawname + "_centered.ply";
	normOut.open(newname.c_str());
	for (unsigned int i = 0; i < totalHeader.size(); i++) {
		vector<string> HEADLINE = totalHeader[i];
		for (unsigned int j = 0; j < HEADLINE.size(); j++) {
			normOut << HEADLINE[j] << " ";
		}
		normOut << endl;
	}
	for (unsigned int i = 0; i < allXYZnormal.size(); i++) {
		vector<double> HEADLINE = allXYZnormal[i];
		for (unsigned int j = 0; j < HEADLINE.size(); j++) {
			normOut << HEADLINE[j] << " ";
		}
		normOut << endl;
	}
	for (unsigned int i = 0; i < totalFace.size(); i++) {
		vector<int> HEADLINE = totalFace[i];
		for (unsigned int j = 0; j < HEADLINE.size(); j++) {
			normOut << HEADLINE[j] << " ";
		}
		normOut << endl;
	}
	return 0;
}
int HEADER::printWhite(string Title) {
	string rawname = Title.substr(0, Title.find_last_of("."));
	string newname = rawname + "_rounded.ply";
	whiteOut.open(newname.c_str());
	for (unsigned int i = 0; i < totalHeader.size(); i++) {
		vector<string> HEADLINE = totalHeader[i];
		for (unsigned int j = 0; j < HEADLINE.size(); j++) {
			whiteOut << HEADLINE[j] << " ";
		}
		whiteOut << endl;
	}
	for (unsigned int i = 0; i < allXYZwhite.size(); i++) {
		vector<double> HEADLINE = allXYZwhite[i];
		for (unsigned int j = 0; j < HEADLINE.size(); j++) {
			whiteOut << HEADLINE[j] << " ";
		}
		whiteOut << endl;
	}
	for (unsigned int i = 0; i < totalFace.size(); i++) {
		vector<int> HEADLINE = totalFace[i];
		for (unsigned int j = 0; j < HEADLINE.size(); j++) {
			whiteOut << HEADLINE[j] << " ";
		}
		whiteOut << endl;
	}
	return 0;
}
