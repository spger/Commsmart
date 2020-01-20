#pragma once

#include <math.h>  
#include <iostream>
#include <armadillo>
#include "Antenna.h"


#define LIGHT_SPEED 3e8;
class AOATradicional
{
public:
	
	int antennas;
	float distance_antennas = 10;
	float AOA;
	float *phase_difference;
	float *distance_array;


	int get_valid_setup(float *phase, float dmax, int sourceNumber);
	float calculate_traditional_AOA(float freq, float *phase);

	AOATradicional(Antenna * array_antenna_setup);
	~AOATradicional();
};



