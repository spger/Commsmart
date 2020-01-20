#pragma once

const int SIZE_ACK = 4;
const int SIZE_NACK = 5;
const int SIZE_TIMESTAMP = 18;
const int SIZE_START_SETUP = 33;
const int SIZE_STOP = 4;

const int BYTE_START_MESSAGE = 0x02;
const int BYTE_END_MESSAGE = 0x03;


enum ControlCommandType {
	START = 1,
	STOP = 2,
	ACK = 3,
	NACK = 4,
	START_REC = 5,
	STOP_REC = 6,
	START_REC_IQ = 7,
	STOP_REC_IQ = 8,
	PLAY_IQ = 9,
	STOP_IQ = 10,
	PLAY_DETEC = 13,//0D
	STOP_DETEC = 14,
	CONNECT = 16,
	DISCONNECT = 17

};

struct ControlCommandArgs {
	float frecuency;
	float threshold;
	float umbral_dinamico;
	float margen_dinamico;
	float bandwidth;
	float bit_rate;
	unsigned short int maxFFTDetections;
	unsigned short int cellsFFT;
	unsigned char overlap;
	std::string sdrIp;
	int sdrControlPort;
	int sdrDataPort;
};

struct ControlCommand {
	ControlCommandType type;
	ControlCommandArgs args;

	char* GetStartBytes() {

		char* bytes = new char[SIZE_START_SETUP];
		bytes[0] = BYTE_START_MESSAGE;
		bytes[1] = ControlCommandType::START;
		bytes[2] = SIZE_START_SETUP;

		memcpy(bytes + 3, &args.frecuency, 4);
		memcpy(bytes + 7, &args.threshold, 4);
		memcpy(bytes + 11, &args.umbral_dinamico, 4);
		memcpy(bytes + 15, &args.margen_dinamico, 4);
		memcpy(bytes + 19, &args.bandwidth, 4);
		memcpy(bytes + 23, &args.bit_rate, 4);
		memcpy(bytes + 27, &args.maxFFTDetections, 2);
		memcpy(bytes + 29, &args.cellsFFT, 2);
		memcpy(bytes + 31, &args.overlap, 1);

		bytes[32] = BYTE_END_MESSAGE;
		return bytes;
	}

	char* GetStopBytes() {

		char* bytes = new char[SIZE_STOP];
		bytes[0] = BYTE_START_MESSAGE;
		bytes[1] = ControlCommandType::STOP;
		bytes[2] = SIZE_STOP;
		bytes[3] = BYTE_END_MESSAGE;
		return bytes;
	}

	char* ACK_response(){

		char* Buf = new char[SIZE_ACK];
		Buf[0] = BYTE_START_MESSAGE;
		Buf[1] = ControlCommandType::ACK;
		Buf[2] = SIZE_ACK;
		Buf[3] = BYTE_END_MESSAGE;

		return Buf;
	}
	char* NACK_response(int error) {

		char* Buf = new char[SIZE_NACK];
		Buf[0] = BYTE_START_MESSAGE;
		Buf[1] = ControlCommandType::NACK;
		Buf[2] = SIZE_NACK;
		Buf[3] = error;
		Buf[4] = BYTE_END_MESSAGE;

		return Buf;
	}

};

struct RecCommand {
	ControlCommandType type;
	char timestamp[SIZE_TIMESTAMP];
};

struct PlayCommand {
	ControlCommandType type;
	char timestamp[SIZE_TIMESTAMP];
};