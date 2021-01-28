#ifndef AWGET_H_INCLUDE
#define AWGET_H_INCLUDE
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
#include "sharedfunctions.h"

using namespace std;

/*struct chainPacket{
	uint16_t length;
	uint16_t urlLength;
	uint16_t chainListLength;
	char* url;
	char* chainList;
};

struct SteppingStone{
	char* IPAddr;
	char* portNum;
	char* chainList;
};*/

void *get_in_addr(struct sockaddr* sa);
const char* readStoneFile(string fileName);

#endif // AWGET_H_INCLUDE
