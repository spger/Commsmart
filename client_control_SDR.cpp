#include "client_control_SDR.h"

client_control_SDR::client_control_SDR()
{
	halt = false;
	connected = false;
}


client_control_SDR::~client_control_SDR()
{
}

int client_control_SDR::Init(const char *ipSDR_control, bool state) {

	
	if (state == true) {
		int resp = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (resp) {
			//printf("Error al inicializar socket control SDR \n");
			//getchar();

			return 20;

		}

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(ipSDR_control);
		server.sin_port = htons(SDR_control_port);

		conn_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (conn_socket == INVALID_SOCKET) {
			//printf("Error al crear socket control SDR\n");
			//getchar();
			WSACleanup();
			return 21;
		}

		if (connect(conn_socket, (SOCKADDR *)&server, sizeof(server)) == SOCKET_ERROR) {
			//printf("Fallo al conectarse con el servidor control SDR \n");
			closesocket(conn_socket);
			WSACleanup();
			//getchar();
			//std::cout << WSAGetLastError();
			return 22;


		}
		printf("Conexion establecida con: SDR %s\n", inet_ntoa(server.sin_addr));
		connected = true;

	}
	if (state == false) {
		printf("CLOSE SOCKET SDR CONTROL \n");
		closesocket(conn_socket);
		WSACleanup();
	}
	return 0;
}

void client_control_SDR::Start(const char *ipSDR_control, bool state) {
	error_client_control_sdr = Init(ipSDR_control,state);
	 
}

void client_control_SDR::Send(char *recbuff, int size) {
	
	if (connected) {
			try {
				if (size > 0) {
					send(conn_socket, recbuff, size, 0);
				}

				int bytesRead = recv(conn_socket, recv_control, 4, 0);
				if (bytesRead > 0) {
					if(recv_control[0]==0x02 && recv_control[1]==ACK){
						std::cout << "ACK from SDR -> Control Port" << std::endl;
					}
					if (recv_control[0] == 0x02 && recv_control[1] == NACK) {
						std::cout << "NACK from SDR -> Control Port" << std::endl;
					}
				}

			}
			catch (std::exception) {}
		}
	

}


