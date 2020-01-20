#include <stdio.h>
#include <string>
#include <iostream>

#include "Utils.h"


std::mutex Utils::printMessageSyncMutex;


Utils::Utils() {
}


Utils::~Utils() {
}


float Utils::BytesToFloat2(const void *data, int offset) {
	float f;
	try {
		unsigned char *b = (unsigned char*)data;
		unsigned char bb[] = { b[offset], b[offset + 1], b[offset + 2], b[offset + 3] };
		memcpy(&f, &bb, sizeof(f));
	} catch(std::exception ex) {
		f = NULL;
	}
	return f;
}

float Utils::BytesToFloat3(const void *data, int offset) {
	float f;
	try {
		unsigned char *b = (unsigned char*)data;
		unsigned char bb[] = { b[offset + 3], b[offset + 2], b[offset + 1], b[offset + 0] };
		memcpy(&f, &bb, sizeof(f));
	} catch(std::exception ex) {
		f = NULL;
	}
	return f;
}

void Utils::PrintMessageSync(std::string message) {
	std::lock_guard<std::mutex> lock(printMessageSyncMutex);
	std::cout << message << std::endl;
}

//
//
//
//
//complex<double>* ReadDummy() {
//	// reading a text file
//#include <iostream>
//#include <fstream>
//#include <string>
//	using namespace std;
//
//	complex<double> *result = new complex<double>[1024];
//
//	int index = 0;
//
//	string line;
//	ifstream myfile("C:\\workspace\\sandbox\\COMMSMART\\iq.csv");
//	if(myfile.is_open()) {
//		while(getline(myfile, line)) {
//
//			char* pEnd;
//			float f1, f2;
//			f1 = strtof(line.c_str(), &pEnd);
//			f2 = strtof(pEnd, NULL);
//
//			result[index].real((double)f1);
//			result[index].imag((double)f2);
//
//			index++;
//		}
//		myfile.close();
//	}
//	return result;
//}