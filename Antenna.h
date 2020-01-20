#pragma once
#include <iostream>
#include <stdlib.h>
#include <random>
#include <vector>
#include <map>
#include <string> 
class Antenna
{
public:
	
	std::map<float, std::string > antennas_map;
	std::vector<std::pair<float, std::string>> pair_antennas;
	Antenna(int num_antennas, float *distance,  double *intervalSearch);
	int numberAntennas;
	float *distance;
	double *intervalSearch;

private:
	
	float *pair_antennas_array_distance;
	std::vector<int>::iterator it;
	void setUp_antennas_array();

	~Antenna();





};

