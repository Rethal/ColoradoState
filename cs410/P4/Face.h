#ifndef FACE
#define FACE
#include "Vertex.h"
#include "Vertexture.h"
#include "Vertexnorm.h"
#include "Material.h"
class Face {
public:
	Face(Vertex a, Vertex b, Vertex c, Vertexture at, Vertexture bt, Vertexture ct, Vertexnorm an, Vertexnorm bn, Vertexnorm cn, Material mat) {
		A = a;
		B = b;
		C = c;
		At = at;
		Bt = bt;
		Ct = ct;
		An = an;
		Bn = bn;
		Cn = cn;
		MT = mat;
	}
	//have x, y, z
	Vertex A;
	Vertex B;
	Vertex C;
	//have u, v, [w]
	Vertexture At;
	Vertexture Bt;
	Vertexture Ct;
	//have x, y, z
	Vertexnorm An;
	Vertexnorm Bn;
	Vertexnorm Cn;
	//has KA, KD, KS
	Material MT;
};

#endif