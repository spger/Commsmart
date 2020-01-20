#pragma once

#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <cstring>

#include "client_control_SDR.h"
#include "client_data_SDR.h"
#include "data_structures.h"
#include "ControlCommand.h"
#include "Utils.h"


#include <thread> 
#include <string>

//#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")
class client_control_SDR;
class client_data_SDR;

#define DEFAULT_BUFLEN 33
#define DEFAULT_BUF_TIMESTAMP 22
#define DEFAULT_RESPONSE 4

class server_control_IHM
{
public:
	WSADATA wsaData;
	SOCKET listenSocket;
	SOCKET clientSocket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	unsigned int control_IHM_port = 4000;
	std::string lastError;

	bool halt;
	bool connected;
	bool state_socket_sdr;

	char recvbuf[DEFAULT_BUFLEN];
	char *sendBuf;
	
	char outStream[74];
	int iResult;

	bool fail_NACK;
	int error_message_control;
	int error_message_data;

	//IHM SERVER
	void Init();
	void Start(client_control_SDR* pass, client_data_SDR* control);
	void Send(char *recbuff, int size);//eliminar??

	float BytesToFloat(unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0);

	server_control_IHM();
	~server_control_IHM();
};

