#pragma once

#include <iostream>
#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include "server_data_IHM.h"
#include "server_control_IHM.h"
#include <fstream>
#include "data_structures.h"
#include "detecRec.h"
#include <mutex>
#include <queue> 
#include "Queue.h"


#include <ctime> 
#include <chrono>

#include "AntennaArray.h"

#pragma comment(lib, "Ws2_32.lib")

#define MAX_CONTROL_BYTES 18

//int MAX_CONTROL_BYTES = 24;

const int HEADER_LENGTH = sizeof(data_header);
const int MAX_PACKET_DETECTIONS = 100;
const int MAX_DATA_BYTES_TO_READ = sizeof(data_frame) * MAX_PACKET_DETECTIONS;
//static const char *ipSDR;
//const char ipSDR[] = { "127.0.0.1" };
class server_control_IHM;

//"10.228.120.137 



class client_data_SDR
{
public:
	
	WSADATA			wsaData;
	SOCKET			conn_socket;
	unsigned int	Tcp_port_data_sdr; 
	const char *ipSDR;

	SOCKADDR_IN server;
	int  RetCode;

	bool halt;
	bool connected;
	bool control;
	bool begin;

	bool detecRec;
	bool playDetec;
	bool endPlay;

	int val_control;
	int error_client_data_sdr;
	int bytesRead;

	char headerBuffer[HEADER_LENGTH];
	char dataBuffer[MAX_DATA_BYTES_TO_READ];


	//CODE NEW ////
	char *buffer;
	CQueue<std::unique_ptr<fullData>> buff_queue;
	/////////////


	std::string fileRecName;
	char fileNa[18];
	char newfileNa[18];
	bool newName = false; 
	bool stopRec = false;	
	char *filePlayName;

	int lastReceivedPacketId;
	int lastProcessedpacketId = 0;

	int Init(bool state);
	int Start();

	bool p1WantsData = false;
	bool p2WantsData = false;

	std::mutex m;
	std::mutex m1;

	std::condition_variable cv, cv2, cv3;
	//std::condition_variable cv2;
	//std::condition_variable cv3;


	int Process(server_data_IHM* sender, AntennaArray* antennaObject);
	int ProcessRec(server_data_IHM* sender, server_control_IHM* stop_rec);
	//int read_binary();

	fullDataFixed fixedDataP1;
	fullDataFixed fixedDataP2;

	client_data_SDR();
	~client_data_SDR();
};

