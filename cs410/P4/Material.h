#ifndef MATERIALFILE
#define MATERIALFILE
#include "Vertex.h"
#include <string>

using namespace std;
class Material {
public:
	Material() {
	}
	Material(string name, Vertex ka, Vertex kd, Vertex ks) {
		Name = name;
		KA = ka;
		KD = kd;
		KS = ks;
	}
	Material(string name, Vertex ka, Vertex kd, Vertex ks, string mapping) {
		Name = name;
		KA = ka;
		KD = kd;
		KS = ks;
		Mapping = mapping;
	}
	string Name;
	Vertex KA;
	Vertex KD;
	Vertex KS;
	string Mapping = "";
};
#endif