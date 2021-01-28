#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <vector>
#include "sharedfunctions.h"



using namespace std;


int socket_descpt = -1, socket_rec = -1;
int socket_descpt_c = -1;

int valid_arg(char** ar){
    return 0;
}




void signal_handler(int sig){
    if (socket_descpt!=-1)
        close(socket_descpt);
    if (socket_descpt_c!=-1)
        close(socket_descpt_c);
    if (socket_rec!=-1)
        close(socket_rec);
    exit(-1);
}



string readFileBytes(const char *name)
{
    ifstream fl(name, ios::in | ios::binary);
    fl.seekg( 0, ios::end );
    size_t len = fl.tellg();
    char *ret = new char[len];
    fl.seekg(0, ios::beg);
    fl.read(ret, len);
    ret[len] = 0;
    fl.close();
    string r(ret);
    return r;
}

size_t getFileLength(const char *name)
{
    ifstream fl(name, ios::binary);
    fl.seekg( 0, ios::end );
    size_t len = fl.tellg();
    return len;
}


bool chain_list_is_empty(char* chainlist){
    /*int i=0, s = 0;
    while (*(chainlist+i)!=','){
        s = s*10 + *(chainlist+i) - '0';
        i++;
    }
    if (s == 0)
        return true;
    else
        return false;
        */
    bool f = false;
    for (unsigned int i = 0; i<strlen(chainlist); i++){
	if (chainlist[i]=='.')
	{
		f = true;
		break;
	}
    }
    return (!f);
}




string onePieceDocument(string& fileString){
    string onePiece = fileString.substr(0, MAX_SIZE_OF_DOWNSTREAM_DATA);
    fileString = fileString.substr(MAX_SIZE_OF_DOWNSTREAM_DATA);
    return onePiece;
}
string lastPieceDocument(size_t pieceLength, string& fileString){
    string lastPiece = fileString.substr(0, pieceLength);
    fileString = fileString.substr(pieceLength);
    return lastPiece;
}

char* packDocumentPacket(string oneDocumentPiece){
    char* pack = new char[SIZE_OF_DOWNSTREAM_PACKET];
    uint16_t dataLen = MAX_SIZE_OF_DOWNSTREAM_DATA;
    uint8_t flag = 1;
    memcpy(pack, &dataLen, 2);
    memcpy(pack+2, &flag, 1);
    for (unsigned int i = 0; i < oneDocumentPiece.length(); i++)
        pack[4+i] = oneDocumentPiece[i];
    pack[SIZE_OF_DOWNSTREAM_PACKET] = 0;
    return pack;
}

char* packLastDocumentPacket(string oneDocumentPiece){
    char* pack = new char[SIZE_OF_DOWNSTREAM_PACKET];
    memset(pack, 0, SIZE_OF_DOWNSTREAM_PACKET);
    uint16_t dataLen = (uint16_t)oneDocumentPiece.length();
    uint8_t flag = 0;
    memcpy(pack, &dataLen, 2);
    memcpy(pack+2, &flag, 1);
    for (int i = 0; i < dataLen; i++)
        pack[4+i] = oneDocumentPiece[i];
    pack[4 + dataLen] = 0;
    return pack;
}


void handle_client(int socket_fd) {
    char recBuff[SIZE_OF_UPSTREAM_BUFFER];
    //according to the given URL and use wget to get the file
    if (recv(socket_fd, recBuff, SIZE_OF_UPSTREAM_BUFFER ,0)== -1){
	cout << "SS: Receive Error from the last SS(awget)" <<endl;
        exit(-1);
    }
    chainPacket pack = unpackRequest(recBuff);
    //Jenny__Jenny__Jenny
	string s(pack.chainList);
	cout << "chainList's length   " << strlen(pack.chainList) <<endl << s <<endl;
    //Jenny__Jenny__Jenny
 
    if (chain_list_is_empty(pack.chainList))
    {
        string url(pack.url);
        string wget_command = "wget " + url;
	system(wget_command.c_str());
        //put the file we downloaded into the array file_array in binary format
        string filename = getFileName(url);

	cout <<"Here is file name" << filename <<endl;

        string fileString;
        fileString= readFileBytes(filename.c_str());


        //pack it into the downstream packet with the structure "header + document stream". (flag = 1, which means it is not the last packet)
        //then send it to another stepping stone
        while (fileString.length() > MAX_SIZE_OF_DOWNSTREAM_DATA ){
            char* toSend = packDocumentPacket(onePieceDocument(fileString));
            if (send(socket_fd, toSend, SIZE_OF_DOWNSTREAM_PACKET, 0)==-1){
		cout << "SS: Send common packet Error(empty)" <<endl;
                exit(-1);
	    }
            delete toSend;
        }


        //Send the last Packet. (flag = 0)
        char* toSend = packLastDocumentPacket(lastPieceDocument(fileString.length(), fileString));
        if (send(socket_fd, toSend, SIZE_OF_DOWNSTREAM_PACKET, 0)==-1){
	    cout << "SS: Send last packet Error(empty)" <<endl;
            exit(-1);
	}
	//release the memory space we malloc
	if (toSend!=NULL)
        	delete toSend;
	//delete the file we download from localhost

	string delete_call("rm ./");
	delete_call.append(filename);
	system(delete_call.c_str());

    }
    else{
        //do the deletion things and send it to the next stepping stone
        SteppingStone nextSS = chooseNextStone(pack.chainList);
        int socket_nextSS = connectToServer(nextSS.IPAddr, nextSS.portNum);
        if (socket_nextSS == -1){
	    cout << "SS: next stepping stone Socket error" <<endl;
            exit(-1);
	}
        if (sendToChain(pack.url, nextSS.chainList, socket_nextSS) == -1){
	    cout << "SS: Send to Chain Error(not empty)" <<endl;
            exit(-1);
	}

        //block and wait to rec eive the document, once a packet has received, just forward it back, until all packets have been send back
        char recBuffDoc[SIZE_OF_DOWNSTREAM_PACKET];
        do{
            //receive document packets from "the next SteppingStone"
            if (recv(socket_nextSS, recBuffDoc, SIZE_OF_DOWNSTREAM_PACKET,0)!=-1){
		cout << "SS: Receive Error (not empty)" <<endl;
                exit(-1);
	    }
            //send the document packets back to "the last SteppingStone"
            char* toSend = recBuffDoc;
            if (send(socket_fd, toSend, strlen(toSend), 0) == -1){
		cout << "SS: Send Error(not empty)" <<endl;
                exit(-1);
	    }
        }
        while (getFlag(recBuffDoc));
        close(socket_fd);
	cout << "Forward the file successfully. The connection has been closed" <<endl;
    }
}

void stepping_stone(int portOfSS) {
	vector<thread*> thread_list;
    sockaddr_in localAddre, client_addrinfo;
    socklen_t client_addlen;
    localAddre.sin_family = AF_INET;
    localAddre.sin_port = htons(portOfSS);
    localAddre.sin_addr.s_addr = INADDR_ANY;
    memset(localAddre.sin_zero, 0, 8);
    socket_descpt = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(socket_descpt, (sockaddr *) &localAddre, sizeof(localAddre)) == 0) {
        listen(socket_descpt, 30);
        while (true) {
            socket_rec = accept(socket_descpt, (sockaddr *) &client_addrinfo, &client_addlen);
            if (socket_rec != -1) {
                //thread t(handle_client, socket_rec);
                //thread_list.push_back(&t);
                handle_client(socket_rec);
            }
            else{
                exit(-1);
            }
        }
    }
    else {
        exit(-1);
    }
    
	for (unsigned int i = 0; i < thread_list.size(); i++)
		(*(thread_list[i])).join();
}


int main(int argc,char* argv[]) {
    signal(SIGINT, signal_handler);
    if (argc == 2 || argc == 1)
    {
        int portAssigned = 0;

        if (argc == 2) {
            string temp(argv[1]);
            for (unsigned int i = 0; i < temp.length() ; i++)
                portAssigned = portAssigned*10 + (temp[i]-'0');

        }
        else{
            portAssigned = PORT_OF_SS;
        }
        char hostname[1000];
        gethostname(hostname, 1000);
        hostent* he;
        he = gethostbyname(hostname);
        cout << "Welcome to Chat!\nwaiting for a connection on " << endl;
        in_addr ** addr_list = (struct in_addr **)he->h_addr_list;
        char ip_notation[16];
        inet_ntop(AF_INET,addr_list[0],ip_notation, 16);
        cout << ip_notation << " port " << portAssigned << endl;
        stepping_stone(portAssigned);

    }
    else {
            cerr << "Error: wrong argument" << endl;
            return -1;
    }

    return 0;
}
