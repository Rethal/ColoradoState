#include "awget.h"
#include "sharedfunctions.h"

using namespace std;


/*void sigHandler(int signum){
	cout << "Interrupt signal (" << signum << ") received.\n";

	close(sockfd);
	close(new_fd);
	exit(signum);  

}*/

void *get_in_addr(struct sockaddr* sa){
	if(sa -> sa_family == AF_INET){
		return &(((struct sockaddr_in*)sa) -> sin_addr);
	}
	
	return &(((struct sockaddr_in6*)sa) -> sin6_addr);
}


void recieveDocument(int the_fd){
	char buff[144];

	if((recv(the_fd, buff, sizeof buff, 0)) == -1){
			cerr << "recv error" << endl;
			exit(1);
		}

		//UNPACK THE RECIEVED DOCUMENT HERE
}





const char* readStoneFile(string fileName){
	ifstream chainRead(fileName);
	if(!chainRead){
		cerr << "Could not find " << fileName << endl;
		exit(-1);
	}
	string chainLine = "";
	int line = 0;
	int numSteppingStones = 0;
	vector<string> chainFile;
	string nextStoneString = "";

	while (getline(chainRead, chainLine)) {
		istringstream iss;
		iss.str(chainLine);
		if (line == 0) {
			iss >> numSteppingStones;							//determines number of stepping stones
		}
		else {
			chainFile.push_back(chainLine);						//creates a vector of strings which contain <IP,port>
		}
		line++;
	}
	
	const char* chainFileBuf = chainVectorToChar(chainFile, numSteppingStones);
	
	
	
	return chainFileBuf;
}

int main(int argc, char* argv[]){
	string URL = "http://www.google.com";
	string Chain = "chaingang.txt";
	//Store the filename of this url so that we can rename it when we get the whole document
	string nameOfFileGot = getFileName(URL);

	//We have a string to stone the file we have
	string FileReceived="";
	//argv[0] = awget
	
	//BEGIN argument check
	if (argc == 2) {
		URL = argv[1];
	}
	else if (argc == 4) {
		if (strcmp(argv[1], "-c") == 0) {
			Chain = argv[2];
			URL = argv[3];
		}
		else if (strcmp(argv[2], "-c") == 0) {
			Chain = argv[3];
			URL = argv[1];
		}
		else {
			cerr << "Must place a -c flag before a chainfile name." << endl;
			exit(-1);
		}
	}
	else {
		cerr << "Must input either a URL or a URL and a -c flag followed by a chainfile name." << endl;
		exit(-1);
	}
	
	const char* chainList = readStoneFile(Chain);
	

//Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_
	string testChain(chainList);
	cout << "Jenny test:" << testChain <<endl;
//Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_
	SteppingStone nextStep = chooseNextStone(chainList);
	
	
	cout << "IP: " << nextStep.IPAddr << " Port: " << nextStep.portNum << endl;

	//connect to socket using nextStoneString
	int sockfd = connectToServer((const char*)nextStep.IPAddr, (const char*)nextStep.portNum);
	if(sockfd == -1){
		cout << "Socket Error" <<endl;
		return -1;
	}

	//send packet(s)
	const char* URLbuf = (char*)malloc(URL.size());
	URLbuf = URL.c_str();
	sendToChain((const char*)URLbuf, (const char*)nextStep.chainList, sockfd);
	//wait for file
	cout << "Jenny just want to see whether it comes here" <<endl;
	DocumentPacket pack;
	pack.doc = NULL;
	char recBuffDoc[SIZE_OF_DOWNSTREAM_PACKET];
	do{
		//delete the space of char array of document piece when unpacking packet to avoid memory leak
		if (pack.doc != NULL)
		{
			delete pack.doc;
			pack.doc = NULL;
		}
		//receive document packets from "the next SteppingStone"
		if (recv(sockfd, recBuffDoc, SIZE_OF_DOWNSTREAM_PACKET,0)!=-1){
			cout << "Receive Error" <<endl;
			exit(0);
		}

		//assemble the packets received
		pack = DocumentUnpackRequest(recBuffDoc);
		join(FileReceived, pack.doc);
		cout << "it seems there is a dead loop here " << pack.flag <<endl;
	}
	while (pack.flag == (uint8_t)1);
	close(sockfd);
	cout << "The connection has closed" <<endl;
	//save file
	writeDocumentToFile(nameOfFileGot+"myFile", FileReceived);
}
