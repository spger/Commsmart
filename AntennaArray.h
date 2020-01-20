#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <armadillo>
#include <map>
#include <string> 
#include <algorithm> 
#include <cmath>
#include <numeric>


#include "MathUtils.h"
#include "antennas_struct.h"

class AntennaArray
{
private:
	std::vector<std::pair<float, float>> validArrayAntennas;
	int getValidSetup_ArrayAntennas(float *phase, float frequency);
	std::map< float, float > antennas_map;
	/**********TRADITIONAL METHOD**********/
	std::vector<double> getIntervalToSearchAngles(double *intervalSearch);
	std::vector<double> getAPhase();
	std::vector<double> getADistance();
	std::vector<std::string> getArrayDistribution_description();
	double getNormalizeAPhase(double Aphase);
	std::vector<double> getNormalizeAPhasesVector(std::vector<double> Aphases);
	std::vector<int> getNumberAmbiguities(float frequency, double *intervalSearch);
	std::vector<double> getAmbiguityStraight(int numberAmbiguity, double Adistance, double *intervalSearch, std::vector<double> intervalSearchAngles);
	auto getMapAmbiguityStraight(std::vector<int> MapAmbiguities, std::vector<double> ADistance, double *intervalSearch, std::vector<double> intervalSearchAngles);
	auto getAnglesOneAntennasPair(std::vector<double> ambiguityStraight, std::vector<double> intervalSearchAngles, double APhase, double ADistance);
	auto getMapAnglesAntennasArray(std::vector<std::vector<double>>MapAmbiguityStraight, std::vector<double> intervalSearchAngles, std::vector<double> Aphases, std::vector<double> Adistances);
	auto getAnglesAmbiguityUnion(antenna_array AntennasArrayStruct);
	
	auto findBigestBaseLine(std::vector<double> ADistanceLineBase);
	auto getAnglesAmbiguityBigestLine(antenna_array AntennasArrayStruct);
	auto getAngleFilter(std::vector<std::vector<double>> AnglesCompared);
	/******************************************************/

	/***********MUSIC METHOD*****************/
	arma::cx_mat getSteeringMat_DOA(float *DOA, float lambda, int antennasNumber, int numberSources, float distance);
	arma::cx_mat getSteeringMat_Phase(float APhase, int numberSources);

	arma::cx_mat simulateSignal(arma::cx_mat &steeringMatrix, float frequency, int snapShots, int numberSources);
	arma::cx_mat noise(double noiseMean, double standartDeviation);
	arma::cx_mat getNoiseSubspace(arma::cx_mat & signal,  int numberSources, float frequency, double * intervalSearch);
	arma::cx_mat improveAlgorithmMusic(arma::cx_mat & signal, int numberSources, float frequency, double * intervalSearch);
	arma::mat musicRealSignal(arma::cx_mat & noiseSubspace, float ADistance, double * intervalSearch);
	
	
	/****************************************/
	
public:

	std::vector<std::pair<float, std::string>> antennas_distance;

	/**********TRADITIONAL METHOD**********/
	AntennaArray(int num_antennas, float *distance);
	double angleEstimation(antenna_array AntennasArrayStruct);
	auto getAnglesNoAmbiguity(antenna_array AntennasArrayStruct);
	auto compareAngles_betweenToLines(std::vector<double> LineToCompare1, std::vector<double> LineToCompare2);

	double getAngleTraditionalMethod(double * intervalSearch, float *phase, float frequency);
	/******************************************************/

	/***********MUSIC METHOD*****************/
	double AOA_maximunMethod(arma::mat &music, double *intervalSearch);
	std::vector<float> AOA_analyseAllPosibilities(arma::mat &music, double *intervalSearch);
	auto getAngle_maximunMethod(std::vector<float> AOArray);
	auto getAngle_analyseAllPosibilities(std::vector< std::vector<float>> AOAMatrix);

	double getAngleMusicMethod(double * intervalSearch, float *phase, float frequency);
	/****************************************/
	~AntennaArray();
protected:
	const arma::cx_double i = arma::cx_double(0, 1);
	const int  PAIR_ANTENNAS = 2;
	const double pi = 3.1415926535897;
	const double c0 = 3E8;
	float lambda;
	int numberAntennas;
	float *distance;
	float distanceMaxAntennas;
	
	/*setUp_antennas_array*/
	void setUp_antennas_array();
	float *pair_antennas_array_distance;
	
};

