#pragma once

#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include "data_structures.h"
#include <thread> 
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class server_data_IHM
{
private:
	static const int DEFAULT_BUFLEN = 32;
	WSADATA wsaData;
	SOCKET listenSocket;
	SOCKET clientSocket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	unsigned int data_IHM_port = 5000;

public:

	bool halt;
	bool connected;
	char outStream[74];
	int iResult;

	void Init();
	void Send(char *sendbuff, int BufferSize);
	void Start();

	server_data_IHM();
	~server_data_IHM();
};

