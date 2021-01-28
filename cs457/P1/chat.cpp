#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <signal.h>

using namespace std;
void sig_handler(int signal) {
	exit(0);
}
struct abc {

}; 
//typedef struct
//{
//	short num;
//	char *some_array;
//};
int main(int argc, char *argv[]) {
	signal((SIGINT || SIGTERM || SIGKILL), sig_handler);
	if (argc == 1) {
		int port = 55055;
		//string ip;
		char host[1024];
		struct addrinfo *hints, **res;
		int hostname = gethostname(host, 1023);
		int addrinfo = getaddrinfo(host, "http", hints, res);
		int file = socket(AF_INET, SOCK_STREAM, 0);

		hostent* hoser = gethostbyname(host);
		in_addr* address = (in_addr*)hoser->h_addr;
		string ip_address = inet_ntoa(*address);

		//char ip[1024] = hoser->h_addr;
		char ip[1024] = "129.82.46.226";
		//ip = ip_address.c_str();
		cout << "Welcome to Chat!" << endl;
		/*Server
		Set up a TCP port and listen for connections (print out IP and PORT listening on).
		Accept connection from client'
		Block to receive a message from the client.
		Receive message and print to screen.
		Prompt the user for a message to send.
		Send the message to the client.
		GOTO step 3.*/

		struct sockaddr_in localAddress;
		int bound = bind(file, (struct sockaddr*)&localAddress, sizeof(localAddress));
		//listen
		int listening = listen(file, 1);
		ntohs(port);
		localAddress.sin_port = port;
		localAddress.sin_family = AF_INET;
		inet_pton(AF_INET, ip_address.c_str(), &(localAddress.sin_addr));
		inet_ntop(AF_INET, &(localAddress.sin_addr), ip, sizeof(ip));

		cout << "Waiting for a connection on " << ip << " port " << port << endl;
		socklen_t addrLen = sizeof(localAddress);
		int accepting = accept(file, (struct sockaddr*)&localAddress, &addrLen);
		cout << "Found a friend! You receive first." << endl;
		if (accepting == -1) {
			cerr << "Failed to accept connection." << endl;
		}
		while (true) {
			char buf[141];
			int received = recv(file, buf, 140, 0);
			if (received != 0) {
				//print
				cout << "Friend: " << buf << endl;
				//prompt
				cout << "You: ";
				string message;
				cin >> message;
				int sent = 0;
				if (message.length() < 140) {
					sent = send(file, message.c_str(), message.size(), 0);
				}
				else {
					cerr << "Error: Input too long." << endl;
				}
			}
		}
		close(file);
		return 0;
	}
	else if (argc == 2) {
		if (strcmp(argv[1],"-h") == 0) {
			cout << "help message" << endl;
			//cout <<
		}
		return 0;
	}
	else if (argc == 5) {
		/*
		Client
		Set up a TCP connection to the server on the IP and port specified.
		Prompt the user for a message to send.
		Send the message to the server.
		Block to receive a message from the server.
		Receive message and print to screen.
		GOTO step 2.*/
		int file = socket(AF_INET, SOCK_STREAM, 0);
		//bind
		struct sockaddr_in localAddress;
		int bound = bind(file, (struct sockaddr*)&localAddress, sizeof(localAddress));
		//connect
		localAddress.sin_family = AF_INET;
		int port = 55055;
		//unsigned char buf[sizeof(struct in6_addr)];
		if (strcmp(argv[1], "-p") == 0 && strcmp(argv[3], "-s") == 0) {
			port = atoi(argv[2]);
			if (inet_pton(AF_INET, argv[4], &(localAddress.sin_addr.s_addr)) <= 0) {
				cerr << "Please input actual IP address." << endl;
				exit(-1);
			}
		}
		else if (strcmp(argv[1], "-s") == 0 && strcmp(argv[3], "-p") == 0) {
			port = atoi(argv[4]);
			if (inet_pton(AF_INET, argv[2], &(localAddress.sin_addr.s_addr)) <= 0) {
				cerr << "Please input actual IP address." << endl;
				exit(-1);
			}
			//*localAddress.sin_addr is server_address?
		}
		else {
			return -1;
		}
		htons(port);
		localAddress.sin_port = port;
		//localAddress.sin_addr = "129.82.46.212";
		cout << "Connecting to server... ";
		//cout << localAddress.sin_addr;
		//cout << localAddress;
		int connected = connect(file, (struct sockaddr *)&localAddress, sizeof(localAddress));
		if (connected == 0) {
			cout << "Connected!" << endl;
			cout << "Connected to a friend! You send first." << endl;
		}
		else {
			cerr << "Failed to connect." << endl;
			return -1;
		}
		while (true) {
			//prompt
			cout << "You: ";
			string message;
			cin >> message;
			int sent = 0;
			if (message.length() < 140) {
				sent = send(file, message.c_str(), message.size(), 0);
			}
			else {
				cerr << "Error: Input too long." << endl;
			}
			while (sent != 0) {
				char buf[141];
				int received = recv(file, buf, 140, 0);
				if (received != 0) {
					//print
					cout << "Friend: " << buf << endl;
					sent = 0;
				}
			}
		}
		close(file);
		return 0;
	}
	else {
		return -1;
	}
}
//file_descriptor = socket();
//recv(file_descriptor, into_buffer);
//send(file_descriptor, from_buffer);
//close(file_descriptor);
//
//int send(int descriptor, const void *msg, int len, int flags);
//int recv(int descriptor, void *recv_buf, int len, int flags);
//int bind(int descriptor, struct sockaddr *localAddress, unsigned int addressLength);
//int inet_ntop(int family, void *addeptr, const char *strptr, size_t len);
//int inet_pton(int family, const char *strptr, void *addeptr);
//int listen(int descriptor, int max_conn);
//int accept(int descriptor, struct sockaddr *client_addrinfo, int *addr_len);
//int connect(int descriptor, struct sockaddr *server_address, unsigned int addressLength);
//int close(int descriptor);



