#pragma once

#include <iostream>
#include <string>

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

#include "server_control_IHM.h"
#include "client_data_SDR.h"

const int BYTES_CONTROL = 21;

class client_control_SDR
{
private:
	WSADATA			wsaData;
	SOCKET			conn_socket;
	SOCKADDR_IN server;
	bool halt;
	bool connected;
public:
	unsigned int	SDR_control_port;
	char recv_control[4];
	int error_client_control_sdr;

	int Init(const char *ipSDR_control, bool state);
	void Start(const char *ipSDR_control, bool state);
	void Send(char *recbuff, int size);

	client_control_SDR();
	~client_control_SDR();
};

