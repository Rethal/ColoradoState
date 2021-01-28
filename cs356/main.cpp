#include "encrypt.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int UsagePrint(int error) {
	switch (error) {
	case 0: cerr << "Error: There should be five arguments." << endl;
		break;
	case 1: cerr << "Error: The first argument must be 'B' or 'S'." << endl;
		break;
	case 2: cerr << "Error: Input file for second argument not found." << endl;
		break;
	case 3: cerr << "Error: Keyfile for fourth argument not found." << endl;
		break;
	case 4: cerr << "Error: Fifth argument must be 'D' for decryption or 'E' for encryption." << endl;
	}
	return 0;
}

int Usage(int argc, char *argv[]) {
	if (argc != 6) {
		UsagePrint(0);
	}
	else if (strcmp(argv[1], "B") != 0 && strcmp(argv[1], "S") != 0) {
		UsagePrint(1);
	}
	else if (strcmp(argv[5], "D") != 0 && strcmp(argv[5], "E") != 0) {
		UsagePrint(4);
	}
	else {
		return 0;
	}
	return -1;
}

int main(int argc, char *argv[]) {
	if (Usage(argc, argv) == -1)
		return -1;
	ifstream InFile(argv[2]);
	ifstream KeyFile(argv[4]);
	string OutFile = argv[3];
	Crypt(argv[1], InFile, OutFile, KeyFile, argv[5]);
	return 0;
}