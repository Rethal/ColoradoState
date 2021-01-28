#ifndef STREAM_AND_BLOCK
#define STREAM_AND_BLOCK
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
class Crypt {
public:
	Crypt(string type, ifstream& inFile, string outFile, ifstream& keyFile, string direction){
		if (strcmp(type.c_str(), "B") == 0) {
			if (strcmp(direction.c_str(), "E") == 0) {
				BlockEncrypt(inFile, outFile, keyFile);
			}
			else BlockDecrypt(inFile, outFile, keyFile);
		}
		else 
			StreamEncrypt(inFile, outFile, keyFile);
	}
	int BlockEncrypt(ifstream& inFile, string outFile, ifstream& keyFile);
	int BlockDecrypt(ifstream& inFile, string outFile, ifstream& keyFile);
	int StreamEncrypt(ifstream& inFile, string outFile, ifstream& keyFile);
};

#endif