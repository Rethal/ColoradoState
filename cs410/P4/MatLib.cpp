#include "MatLib.h"

int MatLib::makeMaterials(ifstream& matfile) {
	string LineString = "";
	while (getline(matfile, LineString)) {
		//headerLine.clear();
		istringstream iss;
		iss.str(LineString);
		int line = 0;
		while (iss.good() && !iss.eof()) {
			string word;
			iss >> word;
			if (word.compare("newmtl") == 0) {
				string title;
				iss >> title;
				names.push_back(title);
			}
			else if (word.compare("Ka") == 0) {
				double r, b, g;
				//vector<double> Ka;
				iss >> r; iss >> g; iss >> b;
				//Ka.push_back(r); Ka.push_back(b); Ka.push_back(g);
				Vertex Ka(r, g, b);
				KAs.push_back(Ka);
			}
			else if (word.compare("Kd") == 0) {
				double r, g, b;
				//vector<double> Kd;
				iss >> r; iss >> g; iss >> b;
				//Kd.push_back(r); Kd.push_back(b); Kd.push_back(g);
				Vertex Kd(r, g, b);
				KDs.push_back(Kd);
			}
			else if (word.compare("Ks") == 0) {
				double r, g, b;
				//vector<double> Ks;
				iss >> r; iss >> g; iss >> b;
				Vertex Ks(r, g, b);
				//Ks.push_back(r); Ks.push_back(b); Ks.push_back(g);
				KSs.push_back(Ks);
			}
			else if (word.compare("map_Kd") == 0) {
				string map;
				iss >> map;
				maps.push_back(map);
			}
			if (maps.size() != line) {
				maps.push_back("");
			}
			line++;
		}
	}
	for (unsigned int i = 0; i < names.size(); i++) {
		if (maps[i].compare("") == 0) {
			Material mat(names[i], KAs[i], KDs[i], KSs[i]);
			Materials.push_back(mat);
		}
		else {
			Material mat(names[i], KAs[i], KDs[i], KSs[i]);
			Materials.push_back(mat);
		}
	}
	return 0;
}