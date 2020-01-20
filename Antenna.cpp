#include "Antenna.h"



Antenna::Antenna(int num_antennas, float *distance, double *intervalSearch)
{
	this->numberAntennas = num_antennas;
	this->distance = distance;
	this->intervalSearch = intervalSearch;

	setUp_antennas_array();
}


Antenna::~Antenna()
{
}

void Antenna::setUp_antennas_array() {

	/*
	EXAMPLE SETUP ANTENNAS
	DATAS IN METERS
	A1 ---- A2 ---- A3 ----- A4 ---- A5


	A1 ---- d1 ---- A2
	A1 ---- d2 ---- A3
	A1 ---- d3 ---- A4
	|
	|
	A1 ---- dn ---- An

	MAXIMUN ANTENNAS PAIRS
	3 antennas -- > 3 Pairs
	4 antennas -- > 6 Pairs
	5 antennas -- > 10 Pairs
	*/

	std::cout << "Getting Antennas Pairs Distance Differences:  " << std::endl<< std::endl;

	if (numberAntennas == 3) {
		pair_antennas_array_distance = new float[3];
		pair_antennas_array_distance[0] = distance[0]; // A1 ---- d1 ---- A2
		pair_antennas_array_distance[1] = distance[1]; // A1 ---- d2 ---- A3
		pair_antennas_array_distance[2] = distance[1] - distance[0];  // A2 ---- d3 ---- A3

		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[0], std::string("A1 ---- d1 ---- A2")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[1], std::string("A1 ---- d2 ---- A3")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[2], std::string("A1 ---- d3 ---- A4")));
		
		for (int k = 0; k < pair_antennas.size(); ++k) {
			std::cout << std::to_string(pair_antennas[k].first) << "  " << pair_antennas[k].second << std::endl;
		}
	}

	if (numberAntennas == 4) {

		pair_antennas_array_distance = new float[6];
		pair_antennas_array_distance[0] = distance[0]; // A1 ---- d1 ---- A2
		pair_antennas_array_distance[1] = distance[1]; // A1 ---- d2 ---- A3
		pair_antennas_array_distance[2] = distance[2]; // A1 ---- d3 ---- A4
		pair_antennas_array_distance[3] = distance[1] - distance[0];  // A2 ---- d4 ---- A3
		pair_antennas_array_distance[4] = distance[2] - distance[1];  // A3 ---- d5 ---- A4
		pair_antennas_array_distance[5] = distance[2] - distance[0];  // A2 ---- d6 ---- A4

		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[0], std::string("A1 ---- d1 ---- A2")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[1], std::string("A1 ---- d2 ---- A3")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[2], std::string("A1 ---- d3 ---- A4")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[3], std::string("A2 ---- d4 ---- A3")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[4], std::string("A3 ---- d5 ---- A4")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[5], std::string("A2 ---- d6 ---- A4")));

		for (int k = 0; k < pair_antennas.size(); ++k) {
			std::cout << std::to_string(pair_antennas[k].first)<< "  " << pair_antennas[k].second << std::endl;
		}
	}

	if (numberAntennas == 5) {
		pair_antennas_array_distance = new float[10];
		pair_antennas_array_distance[0] = distance[0]; // A1 ---- d1 ---- A2
		pair_antennas_array_distance[1] = distance[1]; // A1 ---- d2 ---- A3
		pair_antennas_array_distance[2] = distance[2]; // A1 ---- d3 ---- A4
		pair_antennas_array_distance[3] = distance[3]; // A1 ---- d4 ---- A5
		pair_antennas_array_distance[4] = distance[3] - distance[0];  // A2 ---- d5 ---- A3 
		pair_antennas_array_distance[5] = distance[3] - distance[1];  // A3 ---- d6 ---- A4
		pair_antennas_array_distance[6] = distance[3] - distance[2];  // A4 ---- d7 ---- A5
		pair_antennas_array_distance[7] = distance[3] - distance[0];  // A2 ---- d8 ---- A4
		pair_antennas_array_distance[8] = distance[3] - distance[1];  // A3 ---- d9 ---- A5
		pair_antennas_array_distance[9] = distance[3] - distance[0];  // A2 ---- d10 ---- A5

		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[0], std::string("A1 ---- d1 ---- A2")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[1], std::string("A1 ---- d2 ---- A3")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[2], std::string("A1 ---- d3 ---- A4")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[3], std::string("A1 ---- d4 ---- A5")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[4], std::string("A2 ---- d5 ---- A3")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[5], std::string("A3 ---- d6 ---- A4")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[6], std::string("A4 ---- d7 ---- A5")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[7], std::string("A2 ---- d8 ---- A4")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[8], std::string("A3 ---- d9 ---- A5")));
		pair_antennas.push_back(std::make_pair(pair_antennas_array_distance[9], std::string("A2 ----d10 ---- A5")));

		for (int k = 0; k < pair_antennas.size(); ++k) {
			std::cout << std::to_string(pair_antennas[k].first) << "  " << pair_antennas[k].second << std::endl;
		}
	}

	std::cout << std::endl << std::endl;

}