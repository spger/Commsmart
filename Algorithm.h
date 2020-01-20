#pragma once
#include <iostream>
#include <armadillo>
#include <stdlib.h>
#include <random>
#include <vector>
#include <complex.h>
#include <map>

#include "Antenna.h"

#include "mkl.h"

//define i complex number
const arma::cx_double i = arma::cx_double(0, 1);

class Algorithm
{

private:



	Algorithm(Antenna * array_antenna_setup);
	static Algorithm* Singleton_instance; // singleton
	
	static int get_valid_setup(float *phase, float frequency, int sourceNumber);

	static arma::cx_mat getSteeringMat_DOA(float *DOA, float lamda, int AntNumber, int NumSources, float distance);
	static arma::cx_mat getSteeringMat_Phase(float* APhase, int NumSources, int numDetec);

	static arma::cx_mat simulateSignal(arma::cx_mat &steeringMatrix, float frequency, int shots, int NumSources);

	static arma::cx_mat noise(arma::cx_mat &steering);

	static  arma::mat music(arma::cx_mat &signal, int NumSources, int AntNumber, double *scan, float lamda, float distance);
	static arma::mat music_Phase(arma::cx_mat &signal, float *ADistance, int NumSources, float frequency, double *intervalSearch, int numDetection);
	static arma::mat  Improve_Algorithm_Music(arma::cx_mat &signal, float *ADistance, int NumSources, float frequency, double *intervalSearch, int numDetection);

	static double AOA_one_source(arma::mat &music, int NumSources, double *intervalSearch);
	static std::vector<float> AOA(arma::mat &music, int NumSources, double *scan);

public:

	static Algorithm* getInstance();
	~Algorithm();

	static float startMusic_real_signal(float *phase, float frequency);
	static float startMusic_simulate_signal(float frequency);
	static float calculate_traditional_AOA(float *phase, float frequency);
	
};

