#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread> 

#include "data_structures.h"
#include "client_data_SDR.h"
#include "client_control_SDR.h"
#include "server_data_IHM.h"
#include "server_control_IHM.h"
#include "AntennaArray.h"

#define MKL_Complex16 std::complex<double>


int main() {
	int antennasNumber = 4;
	float antennas_dist[3] = { 0.01, 0.5, 1.8 };
	//double intervalSearch[3] = { -90, 90, 0.1 };

	AntennaArray* array4_antennas = new AntennaArray(antennasNumber, antennas_dist);

	//INICIO CONTROL Y ENVIO DATOS IHM
	server_control_IHM* receiverControl = new server_control_IHM();
	server_data_IHM* senderData = new server_data_IHM();

	//INICIO RECEPTOR TRAMA SDR
	client_data_SDR* receiver = new client_data_SDR();
	
	//INICIO ENVIO DATOS CONTROL SDR
	client_control_SDR* senderControl = new client_control_SDR();

	std::thread recvControlThread(&server_control_IHM::Start, receiverControl, senderControl, receiver);
	recvControlThread.detach();

	std::thread sendDataThread(&server_data_IHM::Start, senderData);
	sendDataThread.detach();

	std::thread receiverThread(&client_data_SDR::Start, receiver);
	receiverThread.detach();

	//INICIO PROCESAMIENTO DATOS SDR
	std::thread processThread(&client_data_SDR::Process, receiver, senderData, array4_antennas);
	processThread.detach();

	//INICIO PROCESAMIENTO DETECCIONES GRABADAS
	std::thread processRecThread(&client_data_SDR::ProcessRec, receiver, senderData, receiverControl);
	processRecThread.detach();

	
	while(true) std::this_thread::sleep_for(std::chrono::minutes(10));

}

