#pragma once

#include<vector>
#include<iostream>

#ifndef ANTENNAS_STRUCTURES
#define ANTENNAS_STRUCTURES


struct antenna_pair{
	std::string	pairId;
	double		APhase;
	double		ADistance;
	int ambiguity;
	std::vector<double> ambiguityStraight;
	std::vector<double> ambiguityAngles;
};

struct antenna_array {
	std::vector<std::string> ArrayDistribution;
	std::vector<double> APhases;
	std::vector<double> ADistance;
	std::vector<int> MapAmbiguities;
	std::vector<std::vector<double>> MapAmbiguityStraight;
	std::vector<std::vector<double>> MapAngles;
	std::vector< std::pair<int, std::vector<double>>> angles_ambiguity;
};

struct angles_struct {
	std::vector<double> AnglesZeroAmbiguities;
	double AngleNoAmbiguity;
	std::vector<double>AnglesBiggestLineBase;

	double angle;


};

#endif