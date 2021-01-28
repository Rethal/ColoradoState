#include <string>
#include <iostream>
#include <fstream>



using namespace std;
string fileName = "router";


int routerPrint(string message) {
	ofstream routerFile;
	routerFile.open(fileName);
	routerFile << message << endl;
	return 0;
}

int routerOpen(){
	int routerID = 0;
	string ID = to_string(routerID);
	fileName.append(ID.c_str());
	fileName.append(".out");
}


int main(int argc, char *argv[]){
	string Message = "sup dude";
	routerOpen();
	routerPrint(Message);
	routerPrint("oh shit");
	routerPrint("wtf");
}

