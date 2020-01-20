#include "server_control_IHM.h"





server_control_IHM::server_control_IHM()
{
	halt = false;
	connected = false;
	Init();

}


server_control_IHM::~server_control_IHM()
{
}

void server_control_IHM::Init() {


	int stsize;
	try {

		//Inicializamos la DLL de sockets
		int resp = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (resp != 0) {
			std::cout << std::string("WSAStartup failed: ") + std::to_string(iResult) << std::endl;
			return;
		}

		struct addrinfo	*result = NULL, hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		iResult = getaddrinfo(NULL, std::to_string(control_IHM_port).c_str(), &hints, &result);
		if (iResult != 0) {
			std::cout << std::string("getaddrinfo failed: ") + std::to_string(iResult) << std::endl;
			WSACleanup();
			return;
		}

		listenSocket = INVALID_SOCKET;

		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (listenSocket == INVALID_SOCKET) {
			std::cout << std::string("Error at socket(): ") + std::to_string(WSAGetLastError()) << std::endl;
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			std::cout << std::string("bind failed: ") + std::to_string(WSAGetLastError()) << std::endl;
			freeaddrinfo(result);
			closesocket(listenSocket);
			WSACleanup();
			return;
		}

		freeaddrinfo(result);
		if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
			std::cout << std::string("listen failed: ") + std::to_string(WSAGetLastError()) << std::endl;
			closesocket(listenSocket);
			WSACleanup();
			return;
		}

	}
	catch (std::exception ex) {
		std::cout << std::string("Exception: ") + std::string(ex.what()) << std::endl;

	}
	std::cout << std::string("Levantando servidor para control IHM en puerto: ") + std::to_string(control_IHM_port) << std::endl;
}

void server_control_IHM::Start(client_control_SDR* pass, client_data_SDR* control) {

	

	
	char response[3] = { 0x02, 0x03, 0x03 };

	try {

		

		clientSocket = INVALID_SOCKET;

		while (!halt) {
			try {
				if (listenSocket != INVALID_SOCKET) {
					clientSocket = accept(listenSocket, NULL, NULL);
					if (clientSocket == INVALID_SOCKET) {
						std::cout << std::string("accept failed: ") + std::to_string(WSAGetLastError()) << std::endl;
						closesocket(listenSocket);
						WSACleanup();
						Init();
						Sleep(300);
						continue;
					}

					std::cout << std::string("Cliente control IHM conectado en el Server: ") + std::to_string(control_IHM_port) + std::string(" con ID: ") + std::to_string(clientSocket) << std::endl;

					if (clientSocket != INVALID_SOCKET) {

						connected = true;

						while (connected) {

							// Leemos comando y evaluamos
							iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);//DEFAULT_BUFLEN 24 
							
							if (iResult > 0) {
								// Comprobamos estructura
								if (recvbuf[0] == 0x02) {
									int type = recvbuf[1];
									int length = recvbuf[2];
									if (recvbuf[length - 1] = 0x03) {
										// Mensaje correcto

										if (type == DISCONNECT) {
											ControlCommand command;
											command.type = DISCONNECT;
											std::cout << "DISCONNECT SDR" << std::endl;
											control->begin = false;
											control->connected = false;
											state_socket_sdr = false;
											pass->Init(NULL, state_socket_sdr);
											//control->Init(state_socket_sdr);
											Sleep(1000);
											control->Init(state_socket_sdr);
											//pass->Init(NULL,state_socket_sdr);


										}

										if (type == CONNECT) {
											ControlCommand command;
											command.type = CONNECT;
											std::cout << "CONNECT SDR" << std::endl;
											ControlCommandArgs args;
											args.sdrIp = std::to_string((unsigned char)recvbuf[3]) + "." + std::to_string((unsigned char)recvbuf[4]) + "." + std::to_string((unsigned char)recvbuf[5]) + "." + std::to_string((unsigned char)recvbuf[6]);
											args.sdrControlPort = (unsigned char)recvbuf[10] << 24 | (unsigned char)recvbuf[9] << 16 | (unsigned char)recvbuf[8] << 8 | (unsigned char)recvbuf[7];
											args.sdrDataPort = (unsigned char)recvbuf[14] << 24 | (unsigned char)recvbuf[13] << 16 | (unsigned char)recvbuf[12] << 8 | (unsigned char)recvbuf[11];

											command.args = args;
											const char *ip = args.sdrIp.c_str();
											state_socket_sdr = true;
											control->Tcp_port_data_sdr = args.sdrDataPort;
											control->ipSDR = ip;
											error_message_data = control->Init(state_socket_sdr);
											pass->SDR_control_port = args.sdrControlPort;

											/*//DATOS INTRODUCIDOS EXPLICITAMENTE, ELIMINAR CUANDO LOS DATOS SEAB RECIBIDOS DESDE EL IHM
											control->Tcp_port_data_sdr = 3334;
											pass->SDR_control_port = 3333;
											pass->SDR_control_port = 7000;
											control->Tcp_port_data_sdr = 6000;

											ipSDR_control = ip;
											ipSDR = ip;

											/////////////////////////////////////////////////////////////////////////////////////////////*/

											if (control->begin == false) {
												pass->Start(ip, state_socket_sdr);//iniciamos el socket EJECUTAR SOLO UNA VEZ AL INICIO

												error_message_control = pass->error_client_control_sdr;

												if (error_message_control == 20) {
													std::cout << "Error al inicializar socket control SDR  " << std::endl;
													control->begin = false;
													fail_NACK = true;
													sendBuf = command.NACK_response(error_message_control);
													send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);


												}
												if (error_message_control == 21) {
													std::cout << "Error al crear socket control SDR " << std::endl;
													control->begin = false;
													fail_NACK = true;
													sendBuf = command.NACK_response(error_message_control);
													send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);


												}

												if (error_message_control == 22) {
													std::cout << "Fallo al conectarse con el servidor control SDR " << std::endl;
													control->begin = false;
													fail_NACK = true;
													sendBuf = command.NACK_response(error_message_control);
													send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);


												}
											}
											if (fail_NACK == false) {
												control->begin = true;
												sendBuf = command.ACK_response();
												send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);
											}

											//error_message_data = control->error_client_data_sdr;
											if (error_message_data == 23) {
												std::cout << "Error al inicializar socket datos SDR  " << std::endl;
												fail_NACK = true;
												sendBuf = command.NACK_response(error_message_data);
												send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);

												getchar();
											}
											if (error_message_data == 24) {
												std::cout << "Error al crear socket datos SDR " << std::endl;
												fail_NACK = true;
												sendBuf = command.NACK_response(error_message_data);
												send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);

												getchar();
											}
											if (error_message_data == 25) {
												std::cout << "Fallo al conectarse con el servidor datos SDR " << std::endl;
												fail_NACK = true;
												sendBuf = command.NACK_response(error_message_data);
												send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);


											}
										}

										if (type == START) {
											std::cout << "START SDR" << std::endl;
											control->control = true;
											ControlCommand command;
											command.type = START;
											ControlCommandArgs args;

											
											float frecuency = BytesToFloat((unsigned char)recvbuf[6], (unsigned char)recvbuf[5], (unsigned char)recvbuf[4], (unsigned char)recvbuf[3]);
											float threshold = BytesToFloat((unsigned char)recvbuf[10], (unsigned char)recvbuf[9], (unsigned char)recvbuf[8], (unsigned char)recvbuf[7]);
											float umbral_dinamico = BytesToFloat((unsigned char)recvbuf[14], (unsigned char)recvbuf[13], (unsigned char)recvbuf[12], (unsigned char)recvbuf[11]);
											float margen_dinamico = BytesToFloat((unsigned char)recvbuf[18], (unsigned char)recvbuf[17], (unsigned char)recvbuf[16], (unsigned char)recvbuf[15]);
											float bandwidth = BytesToFloat((unsigned char)recvbuf[22], (unsigned char)recvbuf[21], (unsigned char)recvbuf[20], (unsigned char)recvbuf[19]);
											float bit_rate = BytesToFloat((unsigned char)recvbuf[26], (unsigned char)recvbuf[25], (unsigned char)recvbuf[24], (unsigned char)recvbuf[23]);
											

											args.frecuency = frecuency;
											args.threshold = threshold;
											args.umbral_dinamico = umbral_dinamico;
											args.margen_dinamico = margen_dinamico;
											args.bandwidth = bandwidth;
											args.bit_rate = bit_rate;

											args.maxFFTDetections = (unsigned char)recvbuf[28] << 8 | (unsigned char)recvbuf[27];
											args.cellsFFT = (unsigned char)recvbuf[30] << 8 | (unsigned char)recvbuf[29];
											args.overlap = (unsigned char)recvbuf[31];
											
										
											command.args = args;

											char *buff = command.GetStartBytes();
											pass->Send(buff, 33);

											//ENVIO ACK IHM
											buff[1] = ACK;
											send(clientSocket, buff, 33, 0);


										}

										if (type == STOP) {
											ControlCommand command;
											control->control = false;
											command.type = STOP;
											std::cout << "STOP SDR" << std::endl;
											char *buff = command.GetStopBytes();
											pass->Send(buff, DEFAULT_RESPONSE);//modificar 

											sendBuf = command.ACK_response();

											send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);
											delete sendBuf;

										}

										if (type == START_REC){
											std::cout << "START REC DETEC" << std::endl;
											RecCommand  command;
											command.type = START_REC;
											control->detecRec = true;

										
											for (int x = 0; x < BYTES_CONTROL - 3; x++) {
												command.timestamp[x] = recvbuf[x + 3];
												control->fileNa[x] = recvbuf[x + 3];

											}

											sendBuf = new char[DEFAULT_BUF_TIMESTAMP];
											//char sendBuf[DEFAULT_BUF_TIMESTAMP];
											sendBuf[0] = 0x02;
											sendBuf[1] = ACK;
											sendBuf[2] = DEFAULT_BUF_TIMESTAMP;
											
											for (int k = 3; k < DEFAULT_BUF_TIMESTAMP; k++) {
												sendBuf[k] = control->fileNa[k-3];
											}
											sendBuf[21] = 0x03;
											

											send(clientSocket, sendBuf, DEFAULT_BUF_TIMESTAMP, 0);

											delete sendBuf;

										}

											/*if (control->newName) {

												sendNewName[0] = 0x02;
												sendNewName[1] = NEW_NAME;

												for (int k = 2; k < DEFAULT_BUFLEN; k++) {
													sendNewName[k] = control->fileNa[k];
												}

												send(clientSocket, sendNewName, DEFAULT_BUFLEN, 0);
		
											
											//control->fileRecName = std::string(aux);
											//control->fileRecName = aux;
											//char test[18] = "20190730085411999"
											//control->fileRecName = std::string(test);*/
											
														
										if (type == STOP_REC) {
											std::cout << "STOP REC DETEC" << std::endl;
											RecCommand  command;
											ControlCommand command2;
											command.type = STOP_REC;
											control->detecRec = false;
											/*recvbuf[1] = ACK;
											recvbuf[2] = DEFAULT_RESPONSE;
											recvbuf[3] = 0x03;*/

											sendBuf = command2.ACK_response();
											
											send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);

											delete sendBuf;
										}

										if (type == START_REC_IQ) {
											std::cout << "START REC IQ" << std::endl;

											ControlCommand  command;
											command.type = START_REC_IQ;
											
											pass->Send(recvbuf, DEFAULT_BUF_TIMESTAMP);

											sendBuf = new char[DEFAULT_BUF_TIMESTAMP];
											sendBuf[0] = 0x02;
											sendBuf[1] = ACK;
											sendBuf[2] = DEFAULT_BUF_TIMESTAMP;

											for (int k = 3; k < DEFAULT_BUF_TIMESTAMP; k++) {
												sendBuf[k] = recvbuf[k];
											}
											sendBuf[21] = 0x03;

											send(clientSocket, sendBuf, DEFAULT_BUF_TIMESTAMP, 0);

											delete sendBuf;



										}

										if (type == STOP_REC_IQ) {

											ControlCommand  command;
											command.type = STOP_REC_IQ; 

											std::cout << "STOP REC IQ" << std::endl;
											pass->Send(recvbuf, 4);

											


											sendBuf = command.ACK_response();
										
											send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);

											delete sendBuf;
										}

										if (type == PLAY_IQ) {
											control->control = true;
											std::cout << "PLAY IQ" << std::endl;
											Sleep(100);
											
											

											sendBuf = new char[DEFAULT_BUF_TIMESTAMP];
											sendBuf[0] = 0x02;
											sendBuf[1] = ACK;
											sendBuf[2] = DEFAULT_BUF_TIMESTAMP;

											for (int k = 3; k < DEFAULT_BUF_TIMESTAMP; k++) {
												sendBuf[k] = recvbuf[k];
											}
											sendBuf[21] = 0x03;


											send(clientSocket, sendBuf, DEFAULT_BUF_TIMESTAMP, 0);
											pass->Send(recvbuf, DEFAULT_BUF_TIMESTAMP);
											delete sendBuf;

										}

										if (type == STOP_IQ) {
											std::cout << "STOP PLAY IQ" << std::endl;
											pass->Send(recvbuf, 4);
											control->control = false;
											control->playDetec = false;

											sendBuf = new char[DEFAULT_RESPONSE];
											sendBuf[0] = 0x02;
											sendBuf[1] = ACK;
											sendBuf[2] = DEFAULT_RESPONSE;
											sendBuf[3] = 0x03;

											send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);

											delete sendBuf;
										}

										if (type == PLAY_DETEC) {
											std::cout << "PLAY DETEC" << std::endl;
											PlayCommand  command;
											command.type = PLAY_DETEC;
											control->playDetec = true;
											//control->control = false;
											for (int x = 0; x < BYTES_CONTROL - 3; x++) {
												command.timestamp[x] = recvbuf[x + 3];
												control->fileNa[x] = recvbuf[x + 3];
											}

											sendBuf = new char[DEFAULT_BUF_TIMESTAMP];
											sendBuf[0] = 0x02;
											sendBuf[1] = ACK;
											sendBuf[2] = DEFAULT_BUF_TIMESTAMP;

											for (int k = 3; k < DEFAULT_BUF_TIMESTAMP; k++) {
												sendBuf[k] = recvbuf[k];
											}
											sendBuf[21] = 0x03;


											send(clientSocket, sendBuf, DEFAULT_BUF_TIMESTAMP, 0);

											delete sendBuf;

										}

										if (type == STOP_DETEC) {
											std::cout << "STOP PLAY DETEC" << std::endl;
											PlayCommand  command;
											command.type = STOP_DETEC;
											control->playDetec = false;

											sendBuf = new char[DEFAULT_RESPONSE];
											sendBuf[0] = 0x02;
											sendBuf[1] = ACK;
											sendBuf[2] = DEFAULT_RESPONSE;
											sendBuf[3] = 0x03;

											send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);

											delete sendBuf;
										}

										if (fail_NACK) {
											ControlCommand command;
											command.type = NACK;
											control->begin = false;
											fail_NACK = false;

										}

										/*if (send(clientSocket, response, sizeof(response), 0) < 0) {
											closesocket(clientSocket);
											connected = false;
											control->control = false;
											Utils::PrintMessageSync(std::string("Cliente control IHM desconectado."));
										}
										else  {
											sendBuf = new char[DEFAULT_RESPONSE];
											sendBuf[0] = 0x02;
											sendBuf[1] = NACK;
											sendBuf[2] = DEFAULT_RESPONSE;
											sendBuf[3] = 0x03;

											send(clientSocket, sendBuf, DEFAULT_RESPONSE, 0);

											delete sendBuf;
										
										}*/
									}

									
								}

								
								

								else {

									// Tendríamos que recorrer el buffer en busca del 0x02
									Utils::PrintMessageSync(std::string("Mensaje desconocido."));

									response[1] = 0x04;
									if (send(clientSocket, response, sizeof(response), 0) < 0) {
										closesocket(clientSocket);
										connected = false;
										control->control = false;
										Utils::PrintMessageSync(std::string("Cliente control IHM desconectado."));
									}
								}


							}
							else if (iResult == 0) {
								closesocket(clientSocket);
								connected = false;
								control->control = false;
								std::cout << std::string("Cliente control IHM desconectado.") << std::endl;
							}
							else {
								closesocket(clientSocket);
								connected = false;
								control->control = false;
								pass->Send(recvbuf, BYTES_CONTROL);
								std::cout << std::string("Error - Cliente control IHM desconectado.") << std::endl;
							}

							Sleep(1);
						}
					}
				}

			}
			catch (std::exception ex) {
				std::cout << std::string("Exception: ") + std::string(ex.what()) << std::endl;
			}
		}
		closesocket(listenSocket);
		WSACleanup();

	}
	catch (std::exception ex) {
		std::cout << std::string("Exception: ") + std::string(ex.what()) << std::endl;
	}
}

void server_control_IHM::Send(char *recbuff, int size) {

	if(connected) {
		try {
			if (size > 0) {
				send(clientSocket, recbuff, size, 0);
			}

			

		}
		catch (std::exception) {}
	}
	//SOCKET client;
	//server_control_IHM::clientSocket
	//send(server_control_IHM::clientSocket, sendNewName, DEFAULT_BUFLEN, 0);
}

float server_control_IHM::BytesToFloat(unsigned char b3, unsigned char b2, unsigned char b1, unsigned char b0) {
	float f;
	try {
		unsigned char b[] = { b0, b1, b2, b3 };
		memcpy(&f, &b, sizeof(f));
	}
	catch (std::exception ex) {
		f = NULL;
	}
	return f;
}