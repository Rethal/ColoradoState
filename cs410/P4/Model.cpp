#include "Model.h"

int ObjModel::readFile(ifstream& filename) {
	string LineString = "";
	while (getline(filename, LineString)) {
		//headerLine.clear();
		istringstream iss;
		iss.str(LineString);
		while (iss.good() && !iss.eof()) {
			string word;
			iss >> word;
			//v, vt, vn, usemtl, g, mtllib, f
			//create each vertex
			if (word.compare("v") == 0) {
				double x, y, z;
				iss >> x; iss >> y; iss >> z;
				x = x + xTrans; y = y + yTrans; z = z + zTrans;
				Vertex point(x, y, z);
				vertices.push_back(point);
			}
			//create each texture
			else if (word.compare("vt") == 0) {
				double u, v, w;
				iss >> u; iss >> v;
				if (iss >> w) {
					Vertexture text(u, v, w);
					textures.push_back(text);
				}
				else {
					Vertexture text(u, v);
					textures.push_back(text);
				}
			}
			//create all normals
			else if (word.compare("vn") == 0) {
				double x, y, z;
				iss >> x; iss >> y; iss >> z;
				x = x + xTrans; y = y + yTrans; z = z + zTrans;
				Vertexnorm normal(x, y, z);
				normals.push_back(normal);
			}
			//create material library (which creates all materials for itself)
			else if (word.compare("mtllib") == 0) {
				string title;
				iss >> title;
				MatLib library(title);
				Library = library;
				//materialLibraries.push_back(library);
			}
			//switch used material
			else if (word.compare("usemtl") == 0) {
				string title;
				iss >> title;
				for (unsigned int i = 0; i < Library.names.size(); i++) {
					if (title.compare(Library.names[i]) == 0) {
						curMat = i;
						break;
					}
				}
			}
			//create all faces
			else if (word.compare("f") == 0) {
				string delimiter = "/";
				string pointVals;
				vector<int> allVals;
				//parse all three points into a vector of ints
				for (int i = 0; i < 3; i++) {
					iss >> pointVals;
					size_t pos = 0;
					string token;
					//cout << pointVals << endl;
					while ((pos = pointVals.find(delimiter)) != string::npos) {
						token = pointVals.substr(0, pos);
						//cout << token << endl;
						int A = atoi(token.c_str());
						allVals.push_back(A);
						pointVals.erase(0, pos + delimiter.length());
						//cout << pointVals << endl;
					}
					int finalVal = atoi(pointVals.c_str());
					allVals.push_back(finalVal);
				}
				int a, at, an, b, bt, bn, c, ct, cn;
				//change ints into individual values
				a = allVals[0]; at = allVals[1]; an = allVals[2]; b = allVals[3]; bt = allVals[4]; bn = allVals[5]; c = allVals[6];
				ct = allVals[7]; cn = allVals[8];
				Vertex A, B, C;
				Vertexture At, Bt, Ct;
				Vertexnorm An, Bn, Cn;
				Material mat;
				//use individual values to find the vertices, textures, and normals used for each face
				A = vertices[a - 1]; B = vertices[b - 1]; C = vertices[c - 1];
				At = textures[at - 1]; Bt = textures[bt - 1]; Ct = textures[ct - 1];
				An = normals[an - 1]; Bn = normals[bn - 1]; Cn = normals[cn - 1];
				//use current material's Ka, Kd, Ks values
				mat = Library.Materials[curMat];
				//create the face
				Face face(A, B, C, At, Bt, Ct, An, Bn, Cn, mat);
				//push it back
				faces.push_back(face);
			}
			//create groups?
		}
	}
	return 0;
}