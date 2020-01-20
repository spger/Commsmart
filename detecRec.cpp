#include "detecRec.h"

std::string path = "../RecordFiles/";
//std::string path = "";

detecRec::detecRec()
{
}


detecRec::~detecRec()
{
}

void detecRec::write(char &headerBuffer, char &dataBuffer, int numberOfFrames, char fileName[SIZE_TIMESTAMP]) {
	

	
	std::string filename = fileName;
	std::string file = path + filename + ".bin";

	std::ofstream fs(file, std::ios::out | std::ios::app	| std::ios::binary);

	if (!fs) {
		std::cout << "Cannot write file!" << std::endl;
		printf("\n Cannot write file! %c", filename);
		return;
	}
	fs.write((char*)&headerBuffer, HEADERLENGTH);
	fs.write((char*)&dataBuffer, numberOfFrames * sizeof(data_frame));

}

long detecRec::getSize(char fileName[SIZE_TIMESTAMP]) {

	char *memblock;

	std::string filename = fileName;
	std::string file = path + filename + ".bin";

	
	std::ifstream fs(file, std::ios::in | std::ios::binary);
	
	if (!fs) {
		std::cout << "Cannot open file!" << std::endl;
		printf("\n Cannot open file! %c", filename);
		

	}
	if (fs.is_open()) {
		
		fs.seekg(0, std::ios::end);
		long fileSize = fs.tellg();

		return fileSize;

	}

}

std::vector<BYTE> detecRec::read(char fileName[SIZE_TIMESTAMP]) {
	char *memblock;
	
	std::string filename = fileName;
	std::string file = path + filename + ".bin";

	std::ifstream fs(file, std::ios::in | std::ios::binary |std::ios::ate);


	if (!fs) {
		std::cout << "Cannot open file!" << std::endl;
		printf("\n Cannot open file! %c", filename);


	}
	if (fs.is_open()) {

		
		//fs.seekg(0, std::ios::end);
		long fileSize = fs.tellg();
		memblock = new char[fileSize];

		fs.seekg(0, std::ios::beg);
		//fs.read(memblock, fileSize);
		std::vector <BYTE> fileData(fileSize);
		fs.read((char*) &fileData[0], fileSize);
		fs.close();

		/*size = fs.tellg();
		memblock = new char[size];
		fs.seekg(0, std:: ios::beg);
		fs.read(memblock, size);
		fs.close();*/

		std::cout << "the entire file content is in memory" << std::endl;

		return fileData;
		
	}

}



void detecRec::maxSize(char fileName[SIZE_TIMESTAMP], char* newName) {

	char *memblock;
	//std::ofstream fs;
	//newName = new char[18];



	//std::string filename = ("%c.", &name);
	std::string filename = fileName;
	std::string file = path + filename + ".bin";


	std::ifstream fs(file, std::ios::in | std::ios::binary);

	if (!fs) {
		std::cout << "Cannot open file!" << std::endl;
		printf("\n Cannot open file! %c", filename);


	}
	if (fs.is_open()) {

		fs.seekg(0, std::ios::end);
		long fileSize = fs.tellg();

		if (fileSize > MAX_SIZE_FILE) {
			time_t timer = time(0);
			char * dt;
			dt = ctime(&timer);
			std::string sl;
			sl.push_back(*dt);
			strcpy(newName, sl.c_str());
		}

	}

}


