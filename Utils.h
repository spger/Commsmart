#pragma once

#include <mutex>
#include <iostream>
#include <string>

class Utils {
public:

	static std::mutex printMessageSyncMutex; 

	Utils();
	~Utils();

	static float BytesToFloat2(const void *data, int offset);

	static float BytesToFloat3(const void *data, int offset);

	static void PrintMessageSync(std::string message);

	
};

