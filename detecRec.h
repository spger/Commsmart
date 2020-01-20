#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <ctime>
#include <fstream>
#include <vector>

#include "client_data_SDR.h"
#include "client_control_SDR.h"
#include "data_structures.h"


#define MAX_SIZE_FILE 1E4

const int HEADERLENGTH = sizeof(data_header);
typedef unsigned char BYTE;


class detecRec
{
private:
	static const int SIZE_TIMESTAMP = 18;
	char fileName[SIZE_TIMESTAMP];
	
public:

	static void write(char &headerBuffer, char &dataBuffer, int numberOfFrames, char fileName[SIZE_TIMESTAMP]);
	static long getSize(char fileName[SIZE_TIMESTAMP]);
	static void maxSize(char fileName[SIZE_TIMESTAMP], char* newName);
	static std::vector < BYTE> read(char fileName[SIZE_TIMESTAMP]);
	detecRec();
	~detecRec();
};

