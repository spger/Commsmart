#include "client_data_SDR.h"

client_data_SDR::client_data_SDR()
{
	halt = false;
	connected = false;
	
}


client_data_SDR::~client_data_SDR()
{
}

int client_data_SDR::Init(bool state) {
	
	if (state == true) {
		//Inicializamos la DLL de sockets
		int resp = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (resp) {
			//printf("Error al inicializar socket data SDR\n");
			
			return 23;
		}

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(ipSDR);
		server.sin_port = htons(Tcp_port_data_sdr);

		// Creamos el socket...
		conn_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (conn_socket == INVALID_SOCKET) {
			//printf("Error al crear socket data SDR\n");
			WSACleanup();
			return 24;
		}

		// Nos conectamos con el servidor...
		if (connect(conn_socket, (SOCKADDR *)&server, sizeof(server)) == SOCKET_ERROR) {
			//printf("Fallo al conectarse con el servidor data SDR\n");
			closesocket(conn_socket);
			WSACleanup();
			
			return 25;


		}
		printf("Conexion establecida con: data SDR %s\n\n", inet_ntoa(server.sin_addr));
		connected = true;

	}

	if (state == false) {
		printf("CLOSE SOCKET SDR DATA\n\n");
		closesocket(conn_socket);
		WSACleanup();
		//getchar();

		return 0;
	}
	

	return 0;
}

int client_data_SDR::Start() {
	
	
	
	int totalBytesRead = 0;
	int offset = 0;
	bool gotFrame = false;
	
	while (!halt) {

		//// LECTURA DE BUFFER 
		if (connected && control) {
			try {
				bytesRead = recv(conn_socket, headerBuffer, HEADER_LENGTH, 0);

				if (bytesRead > 0) {
					if (headerBuffer[4] == 0x4E && headerBuffer[5] == 0x4F && headerBuffer[6] == 0x47 && headerBuffer[7] == 0x00) {
						//control = true;
						// Leemos datos
						unsigned int numberOfFrames = unsigned int((unsigned char)headerBuffer[11] << 24 | (unsigned char)headerBuffer[10] << 16 | (unsigned char)headerBuffer[9] << 8 | (unsigned char)headerBuffer[8]);
						unsigned int packetId = unsigned int((unsigned char)headerBuffer[15] << 24 | (unsigned char)headerBuffer[14] << 16 | (unsigned char)headerBuffer[13] << 8 | (unsigned char)headerBuffer[12]);
						
						if (numberOfFrames > 100) {
							std::cout << "ERROR: SUPERADO TAMAÑO MAXIMO DE FRAMES ENVIADOS POR EL SDR " << std::endl << std::endl;
							return 0;
						}
						while (!gotFrame) {
							bytesRead = recv(conn_socket, dataBuffer + offset, (numberOfFrames * sizeof(data_frame)) - offset, 0);
							if (bytesRead > 0) {
								totalBytesRead += bytesRead;
								if (totalBytesRead == numberOfFrames * sizeof(data_frame)) {
									gotFrame = true;
								}
								else {
									offset += bytesRead;
								}
							}
						}

						//pasamos frame a queue
						std::unique_ptr<fullData> buff_pointer(new fullData);
						//hay que pasar lo recibido a una estructura para luego almacenarlo en col

						memcpy(&(buff_pointer)->header, headerBuffer, HEADER_LENGTH);
						memcpy(&(buff_pointer)->data, dataBuffer, numberOfFrames * sizeof(data_frame));
				
						if (buff_queue.Size() < 20) {
							
							buff_queue.Push(std::move(buff_pointer));
						}
						
						////GRABACION DATOS LEIDOS BUFFER
						if (detecRec) {
							detecRec::write(*headerBuffer, *dataBuffer, numberOfFrames, fileNa);

						}

						lastReceivedPacketId = packetId;
						offset = 0;
						totalBytesRead = 0;

						gotFrame = false;

						if (headerBuffer[0] == 0x02 && headerBuffer[1] == ACK) {
							std::cout << "ACK from SDR -> Data Port" << std::endl << std::endl;

						}
						if (headerBuffer[0] == 0x02 && headerBuffer[1] == NACK) {
							std::cout << "NACK from SDR -> Data Port" << std::endl << std::endl;
						}

					}
					else {
						int pepe = 0;
					}

				}
				else if (bytesRead == 0) {
					closesocket(conn_socket);
					connected = false;
					std::cout << std::string("Cliente desconectado.") << std::endl;
				}
				else {
					closesocket(conn_socket);
					connected = false;
					std::cout << std::string("Error - Cliente desconectado.") << std::endl;
				}

			}
			catch (std::exception) {
				int pepe = 0;
			}
		}

		if (!control) {
			Sleep(100);
		}
	}

	return 0;
}

int client_data_SDR::Process(server_data_IHM* sender, AntennaArray* antennaObject) {

	full_data_frame fullFrame;
	fullData procBuffer;
	//Algorithm_music music;
	double intervalSearch[3] = { -90, 90, 0.1 };
	
	
	while (!halt) {
		if (control) {
			
			try {

				std::unique_ptr<fullData> processBuffer(new fullData);

				if (buff_queue.Pop(processBuffer)) {
					procBuffer = *processBuffer;

					if (procBuffer.header.msg_id > lastProcessedpacketId) {
						char *bb = procBuffer.header.ToBytes();
						sender->Send(bb, sizeof(procBuffer.header));
						delete bb;

						lastProcessedpacketId = procBuffer.header.msg_id;

						std::cout << std::dec << "TRAMA CON ID: " << std::to_string(procBuffer.header.msg_id) << std::endl;

						for (int x = 0; x < procBuffer.header.n_detections; x++) {

							memcpy(&fullFrame.det_module, procBuffer.data[x].det_module, sizeof(procBuffer.data[x].det_module));
							memcpy(&fullFrame.det_phase, procBuffer.data[x].det_phase, sizeof(procBuffer.data[x].det_phase));
							fullFrame.det_freq = procBuffer.data[x].det_freq;
							std::cout << std::dec << "FRECUENCIA: " << std::to_string(fullFrame.det_freq) << std::endl << std::endl;

							//check HACK RF
							if (fullFrame.det_phase[1] == 0 && fullFrame.det_phase[2] == 0 && fullFrame.det_phase[3] == 0) {
								fullFrame.angle = 0;
							}

							else {
								antennaObject->getAngleTraditionalMethod(intervalSearch, fullFrame.det_phase, fullFrame.det_freq);
								antennaObject->getAngleMusicMethod(intervalSearch, fullFrame.det_phase, fullFrame.det_freq);
								//antennaObject.getAngleMusicMethod(intervalSearch, fullFrame.det_phase, fullFrame.det_freq);
								/*auto begin_music = std::chrono::system_clock::now();
								fullFrame.angle = antennaObject->getAngleTraditionalMethod(intervalSearch, fullFrame.det_phase, fullFrame.det_freq);
								auto end_music = std::chrono::system_clock::now() - begin_music;
								std::cout << "execution time MUSIC: " << std::chrono::duration<double>(end_music).count()*1000 << " ms" << std::endl << std::endl << std::endl;
								
								*/
								/*auto begin_traditional = std::chrono::system_clock::now();
								
								auto end_traditional = std::chrono::system_clock::now() - begin_traditional;
								std::cout << "execution time: " << std::chrono::duration<double>(end_traditional).count() * 1000 << " ms" << std::endl << std::endl << std::endl;*/
								//Algorithm::getInstance()->calculate_traditional_AOA(fullFrame.det_phase, fullFrame.det_freq);
								//float angle = Algorithm::getInstance()->startMusic_simulate_signal(fullFrame.det_freq);
								//std::cout << "simulate signal angle: " << angle << std::endl << std::endl;
								//auto begin_music = std::chrono::system_clock::now();
								//fullFrame.angle = Algorithm::getInstance()->startMusic(fullFrame.det_phase, fullFrame.det_freq);
								//auto end_music = std::chrono::system_clock::now() - begin_music;
								//std::cout << "execution time MUSIC: " << std::chrono::duration<double>(end_music).count() * 1000 << " ms" << std::endl << std::endl << std::endl;
								
								//fullFrame.angle = 73;
							}

							fullFrame.detection_ID = procBuffer.data[x].detection_ID;
							fullFrame.det_timestamp = procBuffer.data[x].det_timestamp;
							fullFrame.ReservedFlags = procBuffer.data[x].ReservedFlags;
							fullFrame.ReservedMemory = procBuffer.data[x].ReservedMemory;
							
							
							char* bytes = fullFrame.ToBytes();
							sender->Send(bytes, sizeof(fullFrame));

							delete[] bytes;

						}
					}


				}


				std::cout << std::endl << std::endl;

			}
			catch (std::exception ex) {
				int x = 0;
			}
		}
		if (!control){
		Sleep(100);
		}
	}

	return 0;
}

int client_data_SDR::ProcessRec(server_data_IHM* sender, server_control_IHM* stop_rec) {

	char sendBuffHeader[HEADER_LENGTH];
	char sendBuffFrame[sizeof(full_data_frame)];

	
	fullDataFixed* fullRec;
	data_frame currentFrame;

	full_data_frame fullFrame;
	data_header dh;

	int totalBytesRead = 0;
	int offset = 0;
	lastProcessedpacketId = 0;
	bool gotFrame = false;

	char *loadDataBuffer;
	char loadDataHeader[HEADERLENGTH];

	while (!halt) {
		if (playDetec) {

			try {

				long fileSize = detecRec::getSize(fileNa);

				std::cout << std::endl << std::endl;
				std::cout << std::endl << " Loading file:   " << std::string(fileNa)
					<< "  Size:   " << std::to_string(fileSize) << std::endl << std::endl;

				std::vector <BYTE> loadBuffer = detecRec::read(fileNa);
				

				while (fileSize > offset && playDetec ==true) {
					totalBytesRead = 0;

					for (int x = 0; x < HEADERLENGTH; x++) {
						loadDataHeader[x] = loadBuffer[x + offset];

					}

					if (loadDataHeader[4] == 0x4E && loadDataHeader[5] == 0x4F && loadDataHeader[6] == 0x47 && loadDataHeader[7] == 0x00) {

						//PROCESS HEAD
						unsigned int numberOfFrames = unsigned int((unsigned char)loadDataHeader[11] << 24 | (unsigned char)loadDataHeader[10] << 16 | (unsigned char)loadDataHeader[9] << 8 | (unsigned char)loadDataHeader[8]);
						unsigned int packetId = unsigned int((unsigned char)loadDataHeader[15] << 24 | (unsigned char)loadDataHeader[14] << 16 | (unsigned char)loadDataHeader[13] << 8 | (unsigned char)loadDataHeader[12]);

						p2WantsData == true;
						
						loadDataBuffer = (char *)malloc((numberOfFrames * sizeof(data_frame)));

						while (!gotFrame) {
							
							for (int x = 0; x < numberOfFrames * sizeof(data_frame); x++) {
								loadDataBuffer[x] = loadBuffer[16 + x + offset];
							}

							bytesRead = HEADERLENGTH + (numberOfFrames * sizeof(data_frame));

							if (bytesRead > 0) {
								totalBytesRead += bytesRead;
								if (totalBytesRead == 16 + numberOfFrames * sizeof(data_frame)) {
									gotFrame = true;
									offset += totalBytesRead;
									if (fileSize <= offset) {
										endPlay = true;

									}
								}
								else {
									offset += bytesRead;

								}
							}

						}
						
						//PROCESS FRAME
						memcpy(&(fixedDataP2).header, loadDataHeader, HEADER_LENGTH);
						memcpy(&(fixedDataP2).data, loadDataBuffer, numberOfFrames * sizeof(data_frame));

						free(loadDataBuffer);
						Sleep(1);
					}

					gotFrame = false;


					if (fileSize <= offset) {
						playDetec = false;
						
					}

					fullRec = &fixedDataP2;

					if (fullRec->header.msg_id > lastProcessedpacketId) {

						sender->Send(fullRec->header.ToBytes(), sizeof(fullRec->header));

						lastProcessedpacketId = fullRec->header.msg_id;

						for (int x = 0; x < fullRec->header.n_detections; x++) {
							memcpy(&currentFrame, fullRec->data + x, sizeof(data_frame));

							//if (x == 0) {
								std::cout << std::dec << "Trama: " << std::to_string(fullRec->header.msg_id)
									//<< std::dec << "  Frame: " << std::to_string(currentFrame.detection_ID)
									<< std::dec << "  Frecuencia: " << std::to_string(currentFrame.det_freq)
									//<< std::dec << "  Phase[0]: " << std::to_string(currentFrame.det_phase[0])
									<< std::endl;
							//}

							//fullFrame.angle = MusicLib::startMusic(currentFrame.det_phase, &currentFrame.det_freq)
							fullFrame.angle = 73;
							//std::cout << " ANGLE: " << std::to_string(fullFrame.angle) << std::endl;

							memcpy(&fullFrame.det_module, fullRec->data->det_module, sizeof(fullRec->data->det_module));
							memcpy(&fullFrame.det_phase, fullRec->data->det_phase, sizeof(fullRec->data->det_phase));

							fullFrame.det_freq = fullRec->data->det_freq;
							fullFrame.detection_ID = fullRec->data->detection_ID;
							fullFrame.det_timestamp = fullRec->data->det_timestamp;
							fullFrame.ReservedFlags = fullRec->data->ReservedFlags;
							fullFrame.ReservedMemory = fullRec->data->ReservedMemory;


							sender->Send(fullFrame.ToBytes(), sizeof(fullFrame));
							
						}
						Sleep(1);
						
						std::cout << std::endl << std::endl;
						if (endPlay) {
							endPlay = false;
							playDetec = false;

						}

					}

				}
			}

			catch (std::exception ex) {
			}


			Sleep(1);
		}
		offset = 0;
		totalBytesRead = 0;
		lastProcessedpacketId = 0;
		gotFrame = false;

		if (!playDetec) {
			Sleep(100);
		}
	}
	return 0;
}
