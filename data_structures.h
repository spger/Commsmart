#pragma once

#ifndef DATA_STRUCTURES

#define DATA_STRUCTURES

#pragma pack(4)
struct data_frame {
	float det_module[4];
	float det_phase[4];
	float det_freq;
	unsigned long detection_ID;
	double det_timestamp;
	double ReservedFlags;
	double ReservedMemory;
};

//#pragma pack(reset)

struct data_header {
	int reservedMemory = 0x00000000;
	int identifier = 0x00474f4e;
	int n_detections;
	unsigned long msg_id;

	char* ToBytes() {
		char* bytes = new char[sizeof(data_header)];
		memcpy(bytes, &reservedMemory, sizeof(reservedMemory));
		memcpy(bytes + sizeof(reservedMemory), &identifier, sizeof(identifier));
		memcpy(bytes + sizeof(reservedMemory) + sizeof(identifier), &n_detections, sizeof(n_detections));
		memcpy(bytes + sizeof(reservedMemory) + sizeof(identifier) + sizeof(n_detections), &msg_id, sizeof(msg_id));
		return bytes;
	}
};

struct full_data_frame {
	float det_module[4];
	float det_phase[4];
	float det_freq;
	float angle;
	unsigned long  detection_ID;
	double det_timestamp;
	double ReservedFlags;
	double ReservedMemory;

	char* ToBytes() {//IMPORTANTE take care with memory leak in case yo use Tobytes()
		char* bytes = new char[sizeof(full_data_frame)];
		
		memcpy(bytes, det_module, sizeof(det_module));
		memcpy(bytes + sizeof(det_module), det_phase, sizeof(det_phase));
		memcpy(bytes + sizeof(det_module) + sizeof(det_phase), &det_freq, sizeof(det_freq));
		memcpy(bytes + sizeof(det_module) + sizeof(det_phase) + sizeof(det_freq), &angle, sizeof(angle));
		memcpy(bytes + sizeof(det_module) + sizeof(det_phase) + sizeof(det_freq) + sizeof(angle), &detection_ID, sizeof(detection_ID));
		memcpy(bytes + sizeof(det_module) + sizeof(det_phase) + sizeof(det_freq) + sizeof(angle) + sizeof(detection_ID), &det_timestamp, sizeof(det_timestamp));
		memcpy(bytes + sizeof(det_module) + sizeof(det_phase) + sizeof(det_freq) + sizeof(angle) + sizeof(detection_ID) + sizeof(det_timestamp), &ReservedFlags, sizeof(ReservedFlags));
		memcpy(bytes + sizeof(det_module) + sizeof(det_phase) + sizeof(det_freq) + sizeof(angle) + sizeof(detection_ID) + sizeof(det_timestamp) + sizeof(ReservedFlags), &ReservedMemory, sizeof(ReservedMemory));

		
		return bytes;
	}
};


struct fullData {
	data_header header;
	data_frame data[100]; //memoria dinamica cambair
};


struct fullDataFixed {
	data_header header;
	data_frame data[sizeof(data_frame) * 100];
};

//crear un heder y un fulldata en la readbuffer y compartirla con el resto de funciones, ademas enviarla con server 



#endif