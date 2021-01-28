#ifndef VERTEXTURE
#define VERTEXTURE

class Vertexture {
public:
	Vertexture() {
		U = 0; V = 0; W = 0;
	}
	Vertexture(double u, double v) {
		U = u;
		V = v;
	}
	Vertexture(double u, double v, double w) {
		U = u;
		V = v;
		W = w;
	}
	double U;
	double V;
	double W = 0;
};
#endif
