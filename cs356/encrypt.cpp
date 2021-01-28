#include "encrypt.h"

int Crypt::StreamEncrypt(ifstream& inFile, string outFile, ifstream& keyFile) {
	char character;
	string key = "";
	stringstream fileread;	
	ofstream Output;
	Output.open(outFile);
	getline(keyFile, key);
	int i = 0;
	while (inFile.get(character)) {
		character = character ^ key.at((i%key.length()));
		fileread << character;
		i++;
	}
	Output << fileread.str();
	return 0;
}

int Crypt::BlockEncrypt(ifstream& inFile, string outFile, ifstream& keyFile) {
	char character;
	string key = "";
	stringstream fileread;
	ofstream Output;
	Output.open(outFile);
	getline(keyFile, key);
	while (inFile.get(character)) {
		fileread << character;
	}
	//pad
	string line = fileread.str();
	int pad = key.length()-(line.length() % key.length());
	for (int i = 0; i < pad; i++) {
		fileread << (char)0X80;
	}
	line = fileread.str();
	//cipher
	for (unsigned int i = 0; i < line.length(); i++) {
		line.at(i) = line.at(i) ^ key.at((i%key.length()));
	}
	//swap
	string::iterator startChar = line.begin();
	string::iterator endChar = line.end()-1;
	int keychar = 0;
	while (startChar < endChar) {
		if ((key.at((keychar % key.length())) % 2) == 0) {
			startChar++;
		}
		else {
			swap(*startChar, *endChar);
			startChar++;
			endChar--;
		}
		keychar++;
	}
	Output << line;//fileread.str();
	return 0;
}
int Crypt::BlockDecrypt(ifstream& inFile, string outFile, ifstream& keyFile) {
	char character;
	string key = "";
	stringstream fileread;
	ofstream Output;
	Output.open(outFile);
	getline(keyFile, key);
	while (inFile.get(character)) {
		fileread << character;
	}
	string line = fileread.str();
	//swap
	string::iterator startChar = line.begin();
	string::iterator endChar = line.end()-1;
	int keychar = 0;
	while (startChar < endChar) {
		if ((key.at((keychar % key.length())) % 2) == 0) {
			startChar++;
		}
		else {
			swap(*startChar, *endChar);
			startChar++;
			endChar--;
		}
		keychar++;
	}
	//cipher
	for (unsigned int i = 0; i < line.length(); i++) {
		line.at(i) = line.at(i) ^ key.at((i%key.length()));
	}
	//unpad
	for (unsigned int i = 0; i < line.length(); i++) {
		if (line.at(i) == (char)0X80) {
			line.erase(line.begin() + i, line.end());
			//line.at(i) = NULL;
		}
	}
	Output << line;

	return 0;
}

