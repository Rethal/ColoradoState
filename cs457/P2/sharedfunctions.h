//
// Created by Jialing Zheng on 16/10/30.
//

#ifndef CLIONPROJECTS_PJ2_457
#define CLIONPROJECTS_PJ2_457

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <cstdio>

using namespace std;

struct chainPacket{
    uint16_t length;
    uint16_t urlLength;
    uint16_t chainListLength;
    char* url;
    char* chainList;
};


struct DocumentPacket{
    uint16_t dataLength;
    uint8_t flag;
    char* doc;
};

struct SteppingStone{
    char* IPAddr;
    char* portNum;
    char* chainList;
};


//default port number for stepping Stone
#define PORT_OF_SS 55555

#define  SIZE_OF_UPSTREAM_BUFFER 10000
#define MAX_SIZE_OF_DOWNSTREAM_DATA 10000
//Size of downstream packet equals to max size of downstream data plus 4.
//4 bytes = 1 + 2 + 1   [ sizeof('/0') + sizeof(uint16_t) + sizeof(uint8_t) ]
#define SIZE_OF_DOWNSTREAM_PACKET 10000 + 4


char* packRequest(const char* url, const char* chainList);
chainPacket unpackRequest(char* buff);
int connectToServer(const char* ipaddr, const char* portNum);
int sendToChain(const char* url, const char* chainList, int sockfd);
SteppingStone chooseNextStone(const char* chain);
const char* chainVectorToChar(vector<string> chainFile, int numSteppingStones);
int getIpPort(string ipString, char* &ipaddr, char* &portNum);
DocumentPacket DocumentUnpackRequest(char* packReceived);

bool getFlag(char* packReceived);
void join(string &fileReceived, char*);
void writeDocumentToFile(string filename, string WholeFile);
string getFileName(string url);
#endif //CLIONPROJECTS_PJ2_457
