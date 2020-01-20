#include "server_data_IHM.h"

//#define DEFAULT_BUFLEN 32

server_data_IHM::server_data_IHM()
{
	halt = false;
	connected = false;

	Init(); 
}


server_data_IHM::~server_data_IHM()
{
}

void server_data_IHM::Init() {


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

		iResult = getaddrinfo(NULL, std::to_string(data_IHM_port).c_str(), &hints, &result);
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
	std::cout << std::string("Levantando servidor para data IHM en puerto: ") + std::to_string(data_IHM_port) << std::endl;
}

void server_data_IHM::Start() {
	

	char recvbuf[DEFAULT_BUFLEN];

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

					std::cout << std::string("Cliente data IHM conectado en el Server: ") + std::to_string(data_IHM_port) + std::string(" con ID: ") + std::to_string(clientSocket) << std::endl;

					if (clientSocket != INVALID_SOCKET) {
						connected = true;
						while (connected) {
							// Leemos comando y evaluamos
							iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
							if (iResult > 0) {

							}
							else if (iResult == 0) {
								closesocket(clientSocket);
								connected = false;
								std::cout << std::string("Cliente IHM data desconectado.") << std::endl;
							}
							else {
								closesocket(clientSocket);
								connected = false;
								std::cout << std::string("Error - Cliente IHM data desconectado.") << std::endl;
							}
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

	std::cout << std::string("Levantando servidor para datos IHM en puerto: ") + std::to_string(data_IHM_port) << std::endl;
}



void server_data_IHM::Send(char *sendbuff, int BufferSize) {

	if (connected) {
		try {

			iResult = send(clientSocket, sendbuff, BufferSize, 0);

			if (iResult < 0) {

				closesocket(clientSocket);
				connected = false;
				std::cout << std::string(" data IHM desconectado.") << std::endl;
			}
			
		}
		catch (std::exception ex) {}

	}
}