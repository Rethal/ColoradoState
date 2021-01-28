#include "PPMPrint.h"
#include <algorithm>
int ppmPrint::print(const vector<vector<Ray>>& rayColors, string OutFile) {
	ofstream printStream;
	printStream.open(OutFile);
	printStream << "P3" << endl;
	int pixelStrength = 255;
	printStream << column << " " << row << " " << pixelStrength << endl;
	for (int i = row - 1; i >= 0; i--) {
		for (int j = 0; j < column; j++) {
			vector<double> color = rayColors[i][j].Color;
			double R = color[0]; double G = color[1]; double B = color[2];
			R = pixelStrength * R;
			B = pixelStrength * B;
			G = pixelStrength * G;
			int r = R; int b = B; int g = G;
			if (r > pixelStrength)
				r = pixelStrength;
			if (b > pixelStrength)
				b = pixelStrength;
			if (g > pixelStrength)
				g = pixelStrength;
			if (r < 0)
				r = 0;
			if (b < 0)
				b = 0;
			if (g < 0)
				g = 0;
			printStream << r << " " << g << " " << b << " ";
		}
		printStream << endl;
	}
	printStream.close();
	return 0;
}

//int ppmPrint::print(const vector<vector<double>>& tdists, string OutFile) {
//	double t;
//	double ZERO = 0;
//	ofstream printStream;
//	printStream.open(OutFile);
//	printStream << "P3" << endl;
//	printStream << column << " " << row << " 255" << endl;
//	//cout << tmin << " " << tmax << endl;
//	for (int i = row-1; i >= 0; i--) {
//		for (int j = 0; j < column; j++) {
//			t = tdists[i][j];
//			//cout << t << " ";
//			double ratio = 2 * (t - tmin) / (tmax - tmin);
//			int r = 239;
//			int b = 239;
//			int g = 239;
//			/*if ((tmax - tmin) == 0) {
//				ratio = 0;
//			}*/
//			if (t <= 0) {
//				r = 239;
//				b = 239;
//				g = 239;
//			}
//			else {
//				r = max(ZERO, 255 * (1 - ratio));
//				b = max(ZERO, 255 * (ratio - 1));
//				g = 255 - b - r;
//			}
//			printStream << r << " " << g << " " << b << " ";
//			//cout << i << " " << j << endl;
//
//		}
//		printStream << endl;
//		//cout << endl;
//	}
//	printStream.close();
//	return 0;
//}