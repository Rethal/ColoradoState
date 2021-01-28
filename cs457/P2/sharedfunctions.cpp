#include "sharedfunctions.h"

using namespace std;

char* packRequest(const char* url, const char* chainList){
	//build the packet from the given information
	chainPacket pkt;

	pkt.length = 6 + strlen(url) + strlen(chainList);
	pkt.urlLength = strlen(url);
	pkt.chainListLength = strlen(chainList);

	pkt.url = (char*)malloc((pkt.urlLength) * sizeof(char));
	memcpy(pkt.url, url, pkt.urlLength);

	pkt.chainList = (char*)malloc((pkt.chainListLength) * sizeof(char));
	memcpy(pkt.chainList, chainList, pkt.chainListLength);

	//copy the packet into a buffer
	char* retBuff = (char*)malloc((pkt.length) * sizeof(char));
	memcpy(retBuff, &pkt.length, 2);
	memcpy(retBuff+2, &pkt.urlLength, 2);
	memcpy(retBuff+4, &pkt.chainListLength, 2);
	memcpy(retBuff+6, pkt.url, pkt.urlLength);
	memcpy(retBuff+6+pkt.urlLength, pkt.chainList, pkt.chainListLength);
	
	//cout << "retBuff size: " << sizeof retBuff << endl;

	return retBuff;
}

chainPacket unpackRequest(char* buff){
	chainPacket pkt;
	memcpy(&pkt.length, buff, 2);
	memcpy(&pkt.urlLength, buff+2, 2);
	memcpy(&pkt.chainListLength, buff+4, 2);
	pkt.url = (char*)malloc(pkt.urlLength * sizeof(char));
	memcpy(pkt.url, buff+6, pkt.urlLength);
	pkt.chainList = (char*)malloc(pkt.chainListLength * sizeof(char));
	memcpy(pkt.chainList, buff+6+pkt.urlLength, pkt.chainListLength);
	
	return pkt;
}

int connectToServer(const char* ipaddr, const char* portNum){
	int sockfd;
	struct addrinfo hints, *serverInfo, *p;
	int retVal;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((retVal = getaddrinfo(ipaddr, portNum, &hints, &serverInfo)) != 0){
		cerr << "getaddrinfo: " << gai_strerror(retVal) << endl;
		return -1;
	}

	for(p=serverInfo; p!=NULL; p=p->ai_next){
		if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
			cerr << "client: socket" << endl;
			continue;
		}

		if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1){
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if(p == NULL){
		cerr << "client: failed to connect" << endl;
		return -1;
	}

	cout << "Connected!" << endl;

	freeaddrinfo(serverInfo);

	return sockfd;
}

int sendToChain(const char* url, const char* chainList, int sockfd){
	while(1){
		char* toSend = packRequest(url, chainList);
		if(send(sockfd, toSend, (strlen(url) + strlen(chainList) + 6), 0) == -1){
			cerr << "send error" << endl;
			exit(1);
		}
		break;
	}
	return 0;
}
const char* chainVectorToChar(vector<string> chainFile, int numSteppingStones){
	string SSPassString = to_string(numSteppingStones);

	string chainFilePass = SSPassString;
	for (unsigned int i = 0; i < chainFile.size(); i++) {
		chainFilePass.append(",");
		chainFilePass.append(chainFile.at(i));
	}
	char* chainFileBuf = (char*)malloc(chainFilePass.size());
	strcpy(chainFileBuf, chainFilePass.c_str());

	return chainFileBuf;
}

int getIpPort(string ipString, char* &ipaddr, char* &portNum){
	//cout << "check 1" << endl;

	istringstream iss;
	iss.str(ipString);
	cout << "ipString  " << ipString <<endl;

	string tempIpaddr;
	string tempPortNum;

	iss >> tempIpaddr;
	iss >> tempPortNum;
	
	cout << "IP String: " << tempIpaddr << " port string: " << tempPortNum << endl;

	//cout << "check 2: " << tempIpaddr << endl;

	//tempIpaddr.erase(tempIpaddr.end()-1);
	//cout << "check 3: " << tempIpaddr << endl;
	ipaddr = (char*)malloc((tempIpaddr.length()+1) * sizeof(char));
	portNum = (char*)malloc((tempPortNum.length()+1) * sizeof(char));
	//ipaddr = tempIpaddr.c_str();
	//portNum = tempPortNum.c_str();

	strcpy(ipaddr, tempIpaddr.c_str());
	strcpy(portNum, tempPortNum.c_str());

	//Consider changing this due to terminating 0

	return 0;
}

SteppingStone chooseNextStone(const char* chain){
	
	string chainString(chain);
	vector<string> chainFile;
	stringstream stream(chainString);
	string item;
	int numSteppingStones;
	
	string firstLine;
	getline(stream, firstLine, ',');
	numSteppingStones = atoi(firstLine.c_str());
	
	while(getline(stream, item, ',')){
		chainFile.push_back(item);
	}
	
	int nextSteppingStone = 0;
	string nextStoneString = "";
	
	if (numSteppingStones != 0) {
		srand(time(NULL));
		nextSteppingStone = rand() % numSteppingStones;		//determines which in the vector is the next stepping stone
		nextStoneString = chainFile.at(nextSteppingStone);	//puts this in a string to be used for socket connection
		chainFile.erase(chainFile.begin() + nextSteppingStone);
		chainFile.shrink_to_fit();							//removes used string from vector list
		numSteppingStones--;								//decrements number of stepping stones
	}
	
	cout << nextStoneString << endl;
	const char* tempList = chainVectorToChar(chainFile, numSteppingStones);
	char* newList = (char*)malloc((strlen(tempList)+1) * sizeof(char));
	memcpy(newList, tempList, strlen(tempList));
	
	SteppingStone step;
	//Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_

	cout << "Jenny test:" << endl;
	cout << "nextStoneString   " << nextStoneString << "step.IPAddr   " << step.IPAddr << " step.portNum  "<<step.portNum<<endl;
//Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_Jenny!_
	getIpPort(nextStoneString, step.IPAddr, step.portNum);
	cout << step.IPAddr << " " << step.portNum << endl;
	step.chainList = (char*)malloc(strlen(newList)+1);
	memcpy(step.chainList, newList, strlen(newList) * sizeof(char));
	//cout << step.chainList << endl;
	
	return step;
}
bool getFlag(char* packReceived){
	uint8_t flag;
	memcpy(&flag, packReceived+2, 1);
	if (flag == (uint8_t)1)
		return false;
	else
		return  true;
}
DocumentPacket DocumentUnpackRequest(char* packReceived){
	DocumentPacket pack;
	pack.doc = new char[MAX_SIZE_OF_DOWNSTREAM_DATA];
	memcpy(&pack.dataLength, packReceived, 2);
	memcpy(&pack.flag, packReceived+2, 1);
	return pack;
}
void join(string &fileReceived, char* docData){
	string DocumentPiece(docData);
	fileReceived.append(DocumentPiece);
}
string getFileName(string url){
	int p = url.find("http://");
	if ( p != -1)
		url.erase(p, strlen("http://"));
	p = url.find_last_of("/");
	if (p != -1){
		if ((unsigned int)p==url.length()-1){
			string r("index.html");
			return r;
		}
		else{
			string r = url.substr(p+1);
			return r;
		}


	}
	else{
		string r("index.html");
		return r;
	}

}
void writeDocumentToFile(string filename, string WholeFile){
	ofstream file(filename, ios::out|ios::binary);
	file << WholeFile;
	file.close();
}
