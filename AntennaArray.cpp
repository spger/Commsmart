#include "AntennaArray.h"



AntennaArray::AntennaArray(int num_antennas, float *distance)
{
	this->numberAntennas = num_antennas;
	this->distance = distance;

	setUp_antennas_array();
}

void AntennaArray::setUp_antennas_array()
{
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

	std::cout << "Getting Antennas Pairs Distance Differences:  " << std::endl << std::endl;

	if (numberAntennas == 3) {
		pair_antennas_array_distance = new float[3];
		pair_antennas_array_distance[0] = distance[0]; // A1 ---- d1 ---- A2
		pair_antennas_array_distance[1] = distance[1]; // A1 ---- d2 ---- A3
		pair_antennas_array_distance[2] = distance[1] - distance[0];  // A2 ---- d3 ---- A3

		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[0], std::string("A1 ---- d1 ---- A2")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[1], std::string("A1 ---- d2 ---- A3")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[2], std::string("A1 ---- d3 ---- A4")));

		for (int k = 0; k < antennas_distance.size(); ++k) {
			std::cout << std::to_string(antennas_distance[k].first) << "  " << antennas_distance[k].second << std::endl;
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

		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[0], std::string("A1 ---- d1 ---- A2")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[1], std::string("A1 ---- d2 ---- A3")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[2], std::string("A1 ---- d3 ---- A4")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[3], std::string("A2 ---- d4 ---- A3")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[4], std::string("A3 ---- d5 ---- A4")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[5], std::string("A2 ---- d6 ---- A4")));

		for (int k = 0; k < antennas_distance.size(); ++k) {
			std::cout << std::to_string(antennas_distance[k].first) << "  " << antennas_distance[k].second << std::endl;
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

		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[0], std::string("A1 ---- d1 ---- A2")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[1], std::string("A1 ---- d2 ---- A3")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[2], std::string("A1 ---- d3 ---- A4")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[3], std::string("A1 ---- d4 ---- A5")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[4], std::string("A2 ---- d5 ---- A3")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[5], std::string("A3 ---- d6 ---- A4")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[6], std::string("A4 ---- d7 ---- A5")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[7], std::string("A2 ---- d8 ---- A4")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[8], std::string("A3 ---- d9 ---- A5")));
		antennas_distance.push_back(std::make_pair(pair_antennas_array_distance[9], std::string("A2 ----d10 ---- A5")));

		for (int k = 0; k < antennas_distance.size(); ++k) {
			std::cout << std::to_string(antennas_distance[k].first) << "  " << antennas_distance[k].second << std::endl;
		}
	}

	std::cout << std::endl << std::endl;
}

int AntennaArray::getValidSetup_ArrayAntennas(float *phase, float frequency)
{
	int antennasWithoutAmbiguity = 0;
	distanceMaxAntennas = c0 / (2 * frequency);
	lambda = c0 / frequency;
	std::vector<std::pair<float, std::string>> pair_Aphases;
	
	float *full_APhase = NULL;
	try {
		//CHECK IF DISTANCE BETWEEN ANTENNAS ARE NOT BIGGER THAN DMAX
		//TAKE ONLY PAIR ANTENNAS WITH VALID DISTANCE
		//AND PAIR DISTANCE PAIR WITH APHASE PAIR

		if (numberAntennas == 3) {

			full_APhase = new float[3];
			full_APhase[0] = phase[1] - phase[0];// A1 ---- APhase ---- A2
			full_APhase[1] = phase[2] - phase[0];// A1 ---- APhase ---- A3
			full_APhase[2] = phase[2] - phase[1];// A2 ---- APhase ---- A3

			pair_Aphases.push_back(std::make_pair(full_APhase[0], std::string("A1 ---- AP1 ---- A2")));
			pair_Aphases.push_back(std::make_pair(full_APhase[1], std::string("A1 ---- AP2 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[2], std::string("A1 ---- AP3 ---- A4")));

		}

		if (numberAntennas == 4) {

			full_APhase = new float[6];
			full_APhase[0] = phase[1] - phase[0];// A1 ---- APhase ---- A2
			full_APhase[1] = phase[2] - phase[0];// A1 ---- APhase ---- A3
			full_APhase[2] = phase[3] - phase[0];// A1 ---- APhase ---- A4
			full_APhase[3] = phase[2] - phase[1];// A2 ---- APhase ---- A3
			full_APhase[4] = phase[3] - phase[2];// A3 ---- APhase ---- A4
			full_APhase[5] = phase[3] - phase[1];// A2 ---- APhase ---- A4

			pair_Aphases.push_back(std::make_pair(full_APhase[0], std::string("A1 ---- AP1 ---- A2")));
			pair_Aphases.push_back(std::make_pair(full_APhase[1], std::string("A1 ---- AP2 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[2], std::string("A1 ---- AP3 ---- A4")));
			pair_Aphases.push_back(std::make_pair(full_APhase[3], std::string("A2 ---- AP4 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[4], std::string("A3 ---- AP5 ---- A4")));
			pair_Aphases.push_back(std::make_pair(full_APhase[5], std::string("A2 ---- AP6 ---- A4")));

		}

		if (numberAntennas == 5) {

			full_APhase = new float[10];
			full_APhase[0] = phase[1] - phase[0];// A1 ---- APhase ---- A2
			full_APhase[1] = phase[2] - phase[0];// A1 ---- APhase ---- A3
			full_APhase[2] = phase[3] - phase[0];// A1 ---- APhase ---- A4
			full_APhase[3] = phase[4] - phase[0];// A1 ---- APhase ---- A5
			full_APhase[4] = phase[2] - phase[1];// A2 ---- APhase ---- A3
			full_APhase[5] = phase[3] - phase[2];// A3 ---- APhase ---- A4
			full_APhase[6] = phase[4] - phase[3];// A4 ---- APhase ---- A5
			full_APhase[7] = phase[3] - phase[1];// A2 ---- APhase ---- A4
			full_APhase[8] = phase[4] - phase[2];// A3 ---- APhase ---- A5
			full_APhase[9] = phase[4] - phase[1];// A2 ---- APhase ---- A5


			pair_Aphases.push_back(std::make_pair(full_APhase[0], std::string("A1 ---- AP1 ---- A2")));
			pair_Aphases.push_back(std::make_pair(full_APhase[1], std::string("A1 ---- AP2 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[2], std::string("A1 ---- AP3 ---- A4")));
			pair_Aphases.push_back(std::make_pair(full_APhase[3], std::string("A1 ---- AP4 ---- A5")));
			pair_Aphases.push_back(std::make_pair(full_APhase[4], std::string("A2 ---- AP5 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[5], std::string("A3 ---- AP6 ---- A4")));
			pair_Aphases.push_back(std::make_pair(full_APhase[6], std::string("A4 ---- AP6 ---- A5")));
			pair_Aphases.push_back(std::make_pair(full_APhase[7], std::string("A2 ---- AP6 ---- A4")));
			pair_Aphases.push_back(std::make_pair(full_APhase[8], std::string("A3 ---- AP6 ---- A5")));
			pair_Aphases.push_back(std::make_pair(full_APhase[9], std::string("A2 ---- AP6 ---- A5")));

		}


		for (int k = 0; k < pair_Aphases.size(); ++k) {
			validArrayAntennas.push_back(std::make_pair(antennas_distance[k].first, pair_Aphases[k].first));
			antennas_map.insert(std::make_pair(antennas_distance[k].first, pair_Aphases[k].first));

			if (antennas_distance[k].first < distanceMaxAntennas) {
				antennasWithoutAmbiguity++;

				//IMPORTANTE//
				/*CUANDO SE CREA EL MAPA SI HAY ALGUN VALOR REPETIO ENTRE LAS DISTANCIAS ENTRE ANTENAS, SE ELEMINA UNA PAREJA DE ANTENAS
				CON LA DISTANCIA REPETIDA, POR LO QUE TAMBIEN SE ELIMINA SU PAREJA DE FASE*/

			}

		}

		/*if (antennasWithoutAmbiguity > 0) {
			for (int k = 0; k < pair_Aphases.size(); ++k) {
				if (antennas_distance[k].first < distanceMaxAntennas) {
					antennas_map_no_ambiguity.insert(std::make_pair(antennas_distance[k].first, pair_Aphases[k].first));
				}
			}

			std::cout << "Getting Valid Pair PHASE / ANTENNAS DISTANCE no ambiguity:  " << std::endl;
			std::cout << "   DISTANCE --> APHASE" << std::endl;
			for (itr = antennas_map_no_ambiguity.begin(); itr != antennas_map_no_ambiguity.end(); ++itr) {
				std::cout << '\t' << itr->first
					<< '\t' << itr->second << '\n';
			}

			return antennas_map_no_ambiguity;

		}*/

		if (validArrayAntennas.empty()) {
			std::cout << "ERROR CALCULO ANGULO. Relacion frecuencia y distancia entre el array de antenas incompatible" << std::endl;
			return -1;
		}

		// PRINT VALID PHASE DIFFERENCE
		/*std::cout << "Getting Valid Pair PHASE / ANTENNAS DISTANCE:  " << std::endl;
		std::cout << "   DISTANCE --> APHASE" << std::endl;
		for (std::vector<std::pair<float, float>>::iterator itr = validArrayAntennas.begin(); itr != validArrayAntennas.end(); ++itr) {
			std::cout << '\t' << itr->first
				<< '\t' << itr->second << '\n';
		}*/



		//free memory
		std::vector< std::pair<float, std::string>>().swap(pair_Aphases);

		delete full_APhase;


	}
	catch (std::exception) {
		int pepe = 0;
	}
	return 0;
}

std::vector<double> AntennaArray::getIntervalToSearchAngles(double * intervalSearch)
{
	//default 1 degree precision
	int degreesPrecision = intervalSearch[1] - intervalSearch[0];
	std::vector<double> anglesArray;
	double min = (intervalSearch[0] * pi) / 180;
	double max = (intervalSearch[1] * pi) / 180;

	anglesArray = linspace(min, max, degreesPrecision);

	return  anglesArray;
}

std::vector<double> AntennaArray::getAPhase()
{
	std::vector<double> APhases;
	for (std::vector<std::pair<float, float>>::iterator itr = validArrayAntennas.begin(); itr != validArrayAntennas.end(); ++itr)
		APhases.push_back(itr->second);

	//PRINT
	/*std::cout << "APHASE:  ";
	for (std::vector<double>::iterator it = APhases.begin(); it != APhases.end(); ++it)
		std::cout << *it << "   ";
	std::cout << std::endl << std::endl;*/

	return APhases;
}

std::vector<double> AntennaArray::getADistance()
{
	std::vector<double> ADistance;
	for (std::vector<std::pair<float, float>>::iterator itr = validArrayAntennas.begin(); itr != validArrayAntennas.end(); ++itr)
		ADistance.push_back(itr->first);

	//PRINT
	/*std::cout << "ADISTANCE:  ";
	for (std::vector<double>::iterator it = ADistance.begin(); it != ADistance.end(); ++it)
		std::cout << *it << "   ";
	std::cout << std::endl << std::endl;*/
	return ADistance;
}

std::vector<std::string> AntennaArray::getArrayDistribution_description()
{
	std::vector<std::string> arrayDistribution;
	for (std::vector<std::pair<float, std::string>>::iterator it = antennas_distance.begin(); it != antennas_distance.end(); ++it) {
		arrayDistribution.push_back(it->second);
	}
	return arrayDistribution;
}

double AntennaArray::getNormalizeAPhase(double Aphase)
{
	return fmod(Aphase, 2 * pi) - pi;
}

std::vector<double> AntennaArray::getNormalizeAPhasesVector(std::vector<double> Aphases)
{
	std::vector<double> normalizeVector;
	for (std::vector<double>::iterator it = Aphases.begin(); it != Aphases.end(); ++it) {
		if (*it > 0) {
			normalizeVector.push_back(fmod(*it, 2 * pi) - pi);
		}
		else normalizeVector.push_back(fmod(*it, 2 * pi) + pi);
	}

	//PRINT
	/*std::cout << "Aphases Normalizadas a +-PI:  ";
	for (std::vector<double>::iterator it = normalizeVector.begin(); it != normalizeVector.end(); ++it) {
		std::cout << *it << "  ";
	}
	std::cout << std::endl << std::endl;
*/
	return normalizeVector;
}

std::vector<int> AntennaArray::getNumberAmbiguities(float frequency, double *intervalSearch)
{
	//lambda = c0 / frequency;
	std::vector<std::pair<int, std::string>> NumberAmbiguity;
	std::vector<int> arrayAmbiguity;
	float distanceMaxAntennas = c0 / (2 * frequency);
	int antennasWithoutAmbiguity = 0;
	double coefficient = sin(pi*(intervalSearch[1]) / 180) - sin(pi * (intervalSearch[0]) / 180);
	double numAmbiguity;
	int roundedNumberAmbiguity;
	for (std::vector<std::pair<float, std::string>>::iterator it = antennas_distance.begin(); it != antennas_distance.end(); ++it) {
		numAmbiguity = (coefficient * it->first) / lambda;

		if (numAmbiguity > 0.95 && numAmbiguity < 1) {//factor de correccion para numero de ambiguedades
			numAmbiguity = 1;
		}
		int number = numAmbiguity;
		if (numAmbiguity - number < 0.5) {
			roundedNumberAmbiguity = round(numAmbiguity);
			if (roundedNumberAmbiguity % 2 == 0) {
				++roundedNumberAmbiguity;
			}
			else if (roundedNumberAmbiguity % 2 == 1) {
				roundedNumberAmbiguity = roundedNumberAmbiguity + 2;
			}

		}

		else {
			roundedNumberAmbiguity = round(numAmbiguity);
			if (roundedNumberAmbiguity % 2 == 0) {
				++roundedNumberAmbiguity;
			}

		}

		NumberAmbiguity.push_back(std::make_pair(roundedNumberAmbiguity, it->second));

		arrayAmbiguity.push_back(roundedNumberAmbiguity);
		if (it->first < distanceMaxAntennas) {
			antennasWithoutAmbiguity++;
			arrayAmbiguity.pop_back();
			arrayAmbiguity.push_back(0);
			NumberAmbiguity.pop_back();
			NumberAmbiguity.push_back(std::make_pair(0, it->second));

		}
	}
	/*std::cout << "Distancia maxima sin ambiguedad:  " << distanceMaxAntennas << std::endl;
	for (int k = 0; k < NumberAmbiguity.size(); ++k) {
		std::cout << std::to_string(NumberAmbiguity[k].first) << "  " << NumberAmbiguity[k].second << std::endl;
	}*/
	return arrayAmbiguity;
}

std::vector<double> AntennaArray::getAmbiguityStraight(int numberAmbiguity, double Adistance, double *intervalSearch, std::vector<double> intervalSearchAngles)
{
	std::vector<double> straight;
	double aux;
	double coefficient = sin(pi*(intervalSearch[1]) / 180) - sin(pi * (intervalSearch[0]) / 180);

	if (numberAmbiguity == 0) {
		straight.push_back(0);
		return straight;
	}
	else {
		int k = numberAmbiguity;
		for (std::vector<double>::iterator it = intervalSearchAngles.begin(); it != intervalSearchAngles.end(); ++it) {
			double noNormalize = coefficient * Adistance / lambda * pi * (*it);
			aux = (coefficient*Adistance / lambda * pi * *it) + (k - 2) * pi;

			if (aux > pi) {
				k = k - 2;
				aux = (*it * numberAmbiguity * pi) + (k - 1) * pi;
			}

			straight.push_back(aux);
		}
		return straight;
	}

}

auto AntennaArray::getMapAmbiguityStraight(std::vector<int> MapAmbiguities, std::vector<double> ADistance, double *intervalSearch, std::vector<double> intervalSearchAngles)
{
	std::vector<std::vector<double>> map;

	std::vector<double> ::iterator itx = ADistance.begin();
	for (std::vector<int> ::iterator it = MapAmbiguities.begin(); it != MapAmbiguities.end(); it++) {
		map.push_back(getAmbiguityStraight(*it, *itx,intervalSearch,intervalSearchAngles));
		itx++;
	}

	return map;
}

auto AntennaArray::getAnglesOneAntennasPair(std::vector<double> ambiguityStraight, std::vector<double> intervalSearchAngles, double APhase, double ADistance)
{
	double highValue, lowValue;
	float AOATraditional;
	double resultInterpolationAngleRad , angle; 
	std::vector<double> mapAngle;

	std::vector<double>::iterator iteratorAngle = intervalSearchAngles.begin();
	if (ambiguityStraight.size() == 1) {
		//calculate angle
		double AphaseNoNormalization;
		if (APhase > 0) {
			AphaseNoNormalization = APhase - pi;
		}
		else if (APhase < 0) {
			AphaseNoNormalization = APhase + pi;
		}
		AOATraditional = asin((AphaseNoNormalization * lambda) / (2 * pi *  ADistance));
		//Degrees
		AOATraditional = AOATraditional * (180 / pi);
		//std::cout << "POSSIBLE ANGLES NO AMBIGUITY:  " << AOATraditional  << std::endl;

		mapAngle.push_back(AOATraditional);
		return mapAngle;
	}

	for (std::vector<double>::iterator it = ambiguityStraight.begin(); it != ambiguityStraight.end(); ++it) {
		//std::cout << *it << std::endl;
		lowValue = *it;
		if (std::next(it) != ambiguityStraight.end()) {
			highValue = *std::next(it);
		}

		if (APhase >= lowValue && APhase <= highValue) {
			std::vector<double> xData;
			xData.push_back(highValue);
			xData.push_back(lowValue);

			std::vector<double> yData;
			yData.push_back(*iteratorAngle);
			yData.push_back(*std::next(iteratorAngle));

			resultInterpolationAngleRad = interpolate(xData, yData, APhase, true);

			angle = asin(resultInterpolationAngleRad);
			angle = (angle * 180) / pi;
			mapAngle.push_back(angle);
		}
		if (lowValue > highValue && lowValue > APhase && APhase < highValue) {
			std::vector<double> xData;
			xData.push_back(highValue);
			xData.push_back(-pi);

			std::vector<double> yData;
			yData.push_back(*iteratorAngle);
			yData.push_back(*std::next(iteratorAngle));

			resultInterpolationAngleRad = interpolate(xData, yData, APhase, true);

			angle = asin(resultInterpolationAngleRad);
			angle = (angle * 180) / pi;
			mapAngle.push_back(angle);

		}
		if (lowValue > highValue && lowValue < APhase && APhase > highValue) {
			std::vector<double> xData;
			xData.push_back(pi);
			xData.push_back(lowValue);

			std::vector<double> yData;
			yData.push_back(*iteratorAngle);
			yData.push_back(*std::next(iteratorAngle));

			resultInterpolationAngleRad = interpolate(xData, yData, APhase, true);

			angle = asin(resultInterpolationAngleRad);
			angle = (angle * 180) / pi;
			mapAngle.push_back(angle);

		}

		iteratorAngle++;

	}
	if (mapAngle.size() == 0) {
		//ERROR CODE ADD yo NEXT STEPS
		mapAngle.push_back(INFINITY);
	}
	//PRINT
	//std::cout << "POSSIBLE ANGLES:  ";

	//for (std::vector<double> ::iterator it = mapAngle.begin(); it != mapAngle.end(); it++) {
	//	std::cout << *it << "  ";
	//}
	//std::cout << std::endl;
	return mapAngle;
}

auto AntennaArray::getMapAnglesAntennasArray(std::vector<std::vector<double>> MapAmbiguityStraight, std::vector<double> intervalSearchAngles, std::vector<double> Aphases, std::vector<double> Adistances)
{
	std::vector<std::vector<double>> map;

	std::vector<double> ::iterator itAdistance = Adistances.begin();
	std::vector<double> ::iterator itAphases = Aphases.begin();
	for (std::vector<std::vector<double>> ::iterator it = MapAmbiguityStraight.begin(); it != MapAmbiguityStraight.end(); it++) {

		map.push_back(getAnglesOneAntennasPair(*it, intervalSearchAngles, *itAphases, *itAdistance));

		++itAdistance;
		++itAphases;
	}

	return map;
}

auto AntennaArray::getAnglesAmbiguityUnion(antenna_array AntennasArrayStruct)
{
	std::vector< std::pair<int, std::vector<double>>> angles_ambiguity;;
	std::vector<int> ::iterator itx = AntennasArrayStruct.MapAmbiguities.begin();
	for (std::vector<std::vector<double>> ::iterator it = AntennasArrayStruct.MapAngles.begin(); it != AntennasArrayStruct.MapAngles.end(); ++it) {
		angles_ambiguity.push_back(std::make_pair(*itx, *it));
		++itx;
	}

	return angles_ambiguity;
}

auto AntennaArray::findBigestBaseLine(std::vector<double> ADistanceLineBase)
{
	int itr = 0;
	auto max = std::max_element(std::begin(ADistanceLineBase), std::end(ADistanceLineBase));
	for (std::vector<double> ::iterator it = ADistanceLineBase.begin(); it != ADistanceLineBase.end(); ++it) {
		if (*it == *max) {
			break;
		}
		else itr++;
	}

	return itr;
}

auto AntennaArray::getAnglesAmbiguityBigestLine(antenna_array AntennasArrayStruct)
{
	std::vector<int> MapAmbiguities = AntennasArrayStruct.MapAmbiguities;
	std::vector<double> anglesBiggestLine;
	std::vector<double> ADistanceWithAmbiguity;
	std::vector<std::vector<double>> angleWithAmbiguity;
	int itrAdistance = 0;
	std::vector<std::vector<double>> ::iterator itr = AntennasArrayStruct.MapAngles.begin();
	for (std::vector<int> ::iterator it = MapAmbiguities.begin(); it != MapAmbiguities.end(); ++it) {
		if (*it >= 1) {
			ADistanceWithAmbiguity.push_back(AntennasArrayStruct.ADistance.at(itrAdistance));
			++itrAdistance;
			angleWithAmbiguity.push_back(*itr);
			itr++;


		}
		else {
			++itrAdistance;
			itr++;
		}
	}
	
	std::vector<std::vector<double>> ::iterator it = angleWithAmbiguity.begin();
	it = it + (findBigestBaseLine(ADistanceWithAmbiguity));
	for (std::vector<double> ::iterator itr = it->begin(); itr != it->end(); ++itr) {
		anglesBiggestLine.push_back(*itr);
	}

	return anglesBiggestLine;
}

auto AntennaArray::getAngleFilter(std::vector<std::vector<double>> AnglesCompared)
{
	std::vector<double> angles;
	std::vector<double> differences;
	double angle;
	double mn = std::numeric_limits<double>::infinity();
	for (std::vector<std::vector<double>> ::iterator it = AnglesCompared.begin(); it != AnglesCompared.end(); ++it) {
		std::vector<double> ::iterator itx = it->begin();
		angles.push_back(*itx);

	}
	if (angles.size() == 1) {
		angle = angles[0];
		return angle;
	}
	std::sort(angles.begin(), angles.end());
	float difference;

	for (int n = 0; n < angles.size(); ++n) {
		for (int i = 1 + n; i < angles.size(); i++) {
			double first = angles[n];
			double second = angles[i];
			difference = std::abs(first - second);
			if (difference < mn) {
				mn = difference;
				angle = first;

			}
		}
	}
	/*std::cout << "OBTAINED ANGLES with filter: ";
	for (std::vector<double> ::iterator it = angles.begin(); it != angles.end(); ++it) {
		std::cout << *it << "  ";
	}
	std::cout << std::endl;
	std::cout << "ANGLE TRADITIONAL with filter: " << angle << std::endl;*/
	return angle;

}

auto AntennaArray::getAnglesNoAmbiguity(antenna_array AntennasArrayStruct)
{
	std::vector<double> AnglesZeroAmbiguities;
	std::vector<int> iteratorLineBase;
	double angle;
	int iteratorLB = 0;
	for (std::vector< std::pair<int, std::vector<double>>> ::iterator it = AntennasArrayStruct.angles_ambiguity.begin(); it != AntennasArrayStruct.angles_ambiguity.end(); ++it) {
		if (it->first == 0) {
			AnglesZeroAmbiguities.push_back((it->second.at(0)) * 180 / pi);
			iteratorLineBase.push_back(iteratorLB);
			++iteratorLB;
		}
		else ++iteratorLB;
	}

	//if threre are more than one angles without ambiguity and they are different
	//check wich one belong to biggest base line
	if (AnglesZeroAmbiguities.size() > 1) {
		std::vector <double > aux;
		for (std::vector<int> ::iterator it = iteratorLineBase.begin(); it != iteratorLineBase.end(); ++it) {
			aux.push_back(AntennasArrayStruct.ADistance.at(*it));
		}

		angle = AnglesZeroAmbiguities.at(findBigestBaseLine(aux));

	}
	else if (AnglesZeroAmbiguities.size() == 1) {
		angle = AnglesZeroAmbiguities.at(0);
	}

	else if (AnglesZeroAmbiguities.size() < 1) {
		double x = NULL;
		return x;
	}
	return angle;
}

auto AntennaArray::compareAngles_betweenToLines(std::vector<double> LineToCompare1, std::vector<double> LineToCompare2)
{
	double absDifference = std::numeric_limits<double>::infinity();
	std::vector<double> lineToCompare1 = LineToCompare1;
	std::vector<double> lineToCompare2 = LineToCompare2;
	std::vector<double> angleDiference;
	float difference;
	int indexLine1 = 0, indexLine2 = 0;
	for (int i = 0; i < lineToCompare1.size(); i++) {
		for (int j = 0; j < lineToCompare2.size(); j++) {
			difference = std::abs(lineToCompare1[i] - lineToCompare2[j]);
			if (difference < absDifference) {
				absDifference = difference;
				indexLine2 = j;
				indexLine1 = i;
			}
		}
	}

	if (absDifference != INFINITY) {
		angleDiference.push_back(lineToCompare1[indexLine1]);
		angleDiference.push_back(absDifference);
	}

	return angleDiference;
}

double AntennaArray::angleEstimation(antenna_array AntennasArrayStruct)
{
	std::vector<double> APhases = AntennasArrayStruct.APhases;
	std::vector<double> ADistance = AntennasArrayStruct.ADistance;
	std::vector<int> MapAmbiguities = AntennasArrayStruct.MapAmbiguities;
	std::vector<std::vector<double>> MapAmbiguityStraight = AntennasArrayStruct.MapAmbiguityStraight;
	std::vector<std::vector<double>> MapAngles = AntennasArrayStruct.MapAngles;
	std::vector<double> biggestAnglesLineBase;
	std::vector<std::vector<double>> AnglesCompared;
	double angleSolution;

	angles_struct anglesStruct;

	anglesStruct.AngleNoAmbiguity = getAnglesNoAmbiguity(AntennasArrayStruct);

	/*choose the bigest line base to get AOA because this line has more precision to get angle estimation*/
	biggestAnglesLineBase = getAnglesAmbiguityBigestLine(AntennasArrayStruct);

	int index = 0;
	for (std::vector<std::vector<double>> ::iterator it = MapAngles.begin(); it != MapAngles.end(); ++it) {
		std::vector<double> aux;
		for (std::vector<double> ::iterator itx = it->begin(); itx != it->end(); ++itx) {
			aux.push_back(*itx);
		}
		if (biggestAnglesLineBase != aux && MapAmbiguities[index] != 0) {
			//remove biggestLine to compare and remove line without ambiguity
			AnglesCompared.push_back(compareAngles_betweenToLines(biggestAnglesLineBase, aux));

		}
		++index;
	}

	/************************************/
	angleSolution = getAngleFilter(AnglesCompared);

	return angleSolution;
}

double  AntennaArray::getAngleTraditionalMethod(double * intervalSearch, float *phase, float frequency)
{
	
	std::vector<double> intervalSearchAngles;
	std::vector<double> Aphases;
	std::vector<double> Adistance;
	std::vector<int> ambiguities;
	std::vector<std::vector<double>> mapAmbiguityStraight;
	float angleResult = 0;

	antenna_array AntennasArrayStruct;

	getValidSetup_ArrayAntennas(phase, frequency);
	intervalSearchAngles = getIntervalToSearchAngles(intervalSearch);
	
	Aphases = getAPhase();
	Aphases = getNormalizeAPhasesVector(Aphases);
	AntennasArrayStruct.APhases = Aphases;

	Adistance = getADistance();
	AntennasArrayStruct.ADistance = Adistance;
	AntennasArrayStruct.ArrayDistribution = getArrayDistribution_description();

	ambiguities = getNumberAmbiguities(frequency, intervalSearch);
	AntennasArrayStruct.MapAmbiguities = ambiguities;

	mapAmbiguityStraight = getMapAmbiguityStraight(ambiguities,Adistance,intervalSearch,intervalSearchAngles);
	AntennasArrayStruct.MapAmbiguityStraight = mapAmbiguityStraight;

	AntennasArrayStruct.MapAngles = getMapAnglesAntennasArray(mapAmbiguityStraight, intervalSearchAngles, Aphases, Adistance);
	AntennasArrayStruct.angles_ambiguity = getAnglesAmbiguityUnion(AntennasArrayStruct);

	angleResult = angleEstimation(AntennasArrayStruct);

	return angleResult;
}



arma::cx_mat AntennaArray::getSteeringMat_DOA(float * DOA, float lambda, int antennasNumber, int numberSources, float distance)
{
	arma::cx_mat steeringMatrix;
	float *Doa_rad = new float[numberSources];

	//[rows x cols]
	steeringMatrix.ones(numberSources, antennasNumber);
	for (int k = 0; k < numberSources; k++) {
		Doa_rad[k] = DOA[k] / 180 * arma::datum::pi;
	}

	for (int m = 0; m < numberSources; m++) {
		for (int k = 0; k < antennasNumber; k++) {

			double aux = k * ((2 * arma::datum::pi * distance * sin(Doa_rad[m])) / lambda);
			arma::cx_double aux2 = arma::cx_double(aux, 0); //get complex number
			steeringMatrix.row(m).col(k) = exp(-i * aux2);
		}
	}
	return steeringMatrix.t();
}

arma::cx_mat AntennaArray::getSteeringMat_Phase(float APhase, int numberSources)
{
	arma::cx_mat steeringMatrix;

	steeringMatrix.ones(numberSources, PAIR_ANTENNAS);//[rows x cols]

	for (int m = 0; m < numberSources; m++) {
		for (int k = 0; k < PAIR_ANTENNAS; k++) {

			steeringMatrix.row(m).col(k) = exp(-i * (arma::cx_double((k * APhase), 0)));
		}
	}

	return steeringMatrix.t();
}

arma::cx_mat AntennaArray::simulateSignal(arma::cx_mat & steeringMatrix, float frequency, int snapShots, int numberSources)
{
	//arma::rowvec create row vector
	//arma::vec create column vector
	arma::cx_mat signal;
	signal.zeros(numberSources, snapShots);


	arma::rowvec cadena(snapShots);
	for (int k = 0; k < snapShots; k++) {
		cadena.col(k) = k + 1;

		for (int m = 0; m < numberSources; m++) {
			arma::cx_double aux2 = arma::cx_double((frequency * cadena[k]), 0);
			signal.col(k).row(m) = arma::cx_double(2, 0) * exp(i*aux2);
		}
	}
	signal = steeringMatrix * signal;

	return signal;
}

arma::cx_mat AntennaArray::noise(double noiseMean, double standartDeviation)
{
	//const double mean = 0.0;
	//const double stddev = 0.1;
	arma::cx_mat signalWithNoise;
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(noiseMean, standartDeviation);

	// Add Gaussian noise
	for (auto& signalWithNoise : signalWithNoise) {
		signalWithNoise = signalWithNoise + distribution(generator);
	}

	return signalWithNoise;
}

arma::cx_mat AntennaArray::getNoiseSubspace(arma::cx_mat & signal, int numberSources, float frequency, double * intervalSearch)
{
	arma::cx_mat R;
	arma::cx_vec eigval;
	arma::cx_mat eigvec;
	arma::cx_mat sorteigvec;
	arma::cx_mat En;
	

	float lambda = arma::datum::c_0 / frequency;
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);

	R = signal * trans(signal);

	En.ones(PAIR_ANTENNAS, PAIR_ANTENNAS - numberSources);
	sorteigvec.ones(PAIR_ANTENNAS, PAIR_ANTENNAS);

	arma::eig_gen(eigval, eigvec, R);

	arma::uvec indexval = sort_index(eigval, "descend");

	int index;
	for (int k = 0; k < PAIR_ANTENNAS; k++) {
		for (int m = 0; m < PAIR_ANTENNAS; m++) {
			index = int(indexval[m]);
			sorteigvec.row(k).col(m) = eigvec.row(k).col(index);
		}

	}

	//estimate noise subspace
	for (int k = 0; k < (PAIR_ANTENNAS - numberSources); k++) {
		En.col(k) = sorteigvec.col(PAIR_ANTENNAS - (PAIR_ANTENNAS - numberSources) + k);
	}

	return En;
}

arma::mat AntennaArray::musicRealSignal(arma::cx_mat & noiseSubspace, float ADistance,  double * intervalSearch)
{
	arma::mat Pmusic;
	arma::cx_mat PP;
	arma::cx_mat SS;
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);
	
	Pmusic.zeros(1, precision);

	for (int k = 0; k < precision - 1; k++) {
		
		SS.zeros(1, PAIR_ANTENNAS);
		for (int m = 0; m < PAIR_ANTENNAS; m++) {
			SS.col(m) = exp(i*(arma::cx_double((m
				* (2 * arma::datum::pi* ADistance * sin(search[k]
					/ 180 * arma::datum::pi)
					/ lambda)), 0)));
		}

		PP = SS * noiseSubspace*arma::trans(noiseSubspace)*arma::trans(SS);
		Pmusic.col(k) = abs(1 / PP);

	}

	return Pmusic;
}

arma::cx_mat AntennaArray::improveAlgorithmMusic(arma::cx_mat & signal, int numberSources, float frequency, double * intervalSearch)
{
	arma::cx_mat R;
	arma::cx_vec eigval;
	arma::cx_mat eigvec;
	arma::cx_mat sorteigvec;
	arma::cx_mat En;


	float lambda = arma::datum::c_0 / frequency;
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);

	R = signal * trans(signal);

	arma::mat J = arma::eye<arma::mat>(PAIR_ANTENNAS, PAIR_ANTENNAS);
	J = arma::fliplr(J);
	R = R + J * arma::conj(R)*J;

	En.ones(PAIR_ANTENNAS, PAIR_ANTENNAS - numberSources);
	sorteigvec.ones(PAIR_ANTENNAS, PAIR_ANTENNAS);

	arma::eig_gen(eigval, eigvec, R);

	arma::uvec indexval = sort_index(eigval, "descend");

	int index;
	for (int k = 0; k < PAIR_ANTENNAS; k++) {
		for (int m = 0; m < PAIR_ANTENNAS; m++) {
			index = int(indexval[m]);
			sorteigvec.row(k).col(m) = eigvec.row(k).col(index);
		}

	}

	//estimate noise subspace
	for (int k = 0; k < (PAIR_ANTENNAS - numberSources); k++) {
		En.col(k) = sorteigvec.col(PAIR_ANTENNAS - (PAIR_ANTENNAS - numberSources) + k);
	}

	return En;
}

double AntennaArray::AOA_maximunMethod(arma::mat & music, double * intervalSearch)
{
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);//generate vector with angles intervals
	//std::cout << music << std::endl;
	//its possible delete this code is using to graphic representation but maybe is not neccesary and is possible get similar results without plot 
	/****************************/
	//int index;
	//arma::mat plot;
	//plot.zeros(1, precision);
	//for (int k = 0; k < precision; k++) {
	//	plot.col(k) = 10 * arma::log10(music.col(k) / music.max());

	//}
	////std::cout << plot << std::endl;
	//arma::uword i = plot.index_max();
	//double AOA = (-1)*search(i);
	/****************************/

	arma::uword j = music.index_max();
	double AOA = (-1)*search(j);

	return AOA;
}

std::vector<float> AntennaArray::AOA_analyseAllPosibilities(arma::mat & music, double * intervalSearch)
{
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);//generate vector with angles intervals
	std::vector<float> aoaArray;
	float angle = 0;
	for (int k = 1; k < (music.size() - 1); k++) {

		if (music(k) > music(k - 1) && music(k) > music(k + 1)) {
			double angle = (-1)*search(k);
			if (angle > intervalSearch[0] + 2 && angle < intervalSearch[1] - 2) {
				aoaArray.push_back((-1)*search(k));
				std::sort(aoaArray.begin(), aoaArray.end());
			}
		}
	}
	std::cout << "POSSIBLE ANGLE MUSIC :  ";
	for (auto i = aoaArray.begin(); i != aoaArray.end(); ++i) {
		std::cout << *i << ' ';
		angle = *i + angle;
	}
	std::cout << std::endl;
	return aoaArray;
}

auto AntennaArray::getAngle_maximunMethod(std::vector<float> AOArray)
{
	std::vector<float> angles = AOArray;
	double difference;
	double angle;
	double maginAngle = 2;
	double mn = std::numeric_limits<double>::infinity();
	for (int n = 0; n < angles.size(); ++n) {
		for (int i = 1 + n; i < angles.size(); i++) {
			double first = angles[n];
			double second = angles[i];
			difference = std::abs(first - second);
			if (difference < mn) {
				mn = difference;
				angle = first;

			}
		}
	}
	if (difference > maginAngle) {
		angle = AOArray[0];
	}
	/*std::cout << std::endl;
	std::cout << "MUSIC ANGLE ONE SOURCE with filter: " << angle << std::endl;*/
	return angle;
}

auto AntennaArray::getAngle_analyseAllPosibilities(std::vector<std::vector<float>> AOAMatrix)
{
	std::vector< std::vector<float>> AOA = AOAMatrix;
	std::vector<double> line1;
	std::vector<double> line2;
	std::vector<double> angleDiference;
	std::vector<std::vector<double>> arrayDifference;
	double angle = 0;
	double mn = std::numeric_limits<double>::infinity();
	float difference;
	int indexLine1 = 0, indexLine2 = 0;

	auto it = AOA.begin();
	for (auto itx = it->begin(); itx != it->end(); ++itx) {
		line1.push_back(*itx);
	}
	for (auto itr = AOA.begin() + 1; itr != AOA.end(); ++itr) {
		for (auto itx = itr->begin(); itx != itr->end(); ++itx) {
			line2.push_back(*itx);
		}


		for (int i = 0; i < line1.size(); i++) {
			for (int j = 0; j < line2.size(); j++) {
				difference = std::abs(line1[i] - line2[j]);
				if (difference < mn) {
					mn = difference;
					indexLine2 = j;
					indexLine1 = i;
				}

			}
		}

		//eliminar informacion de diferencia
		if (mn != INFINITY) {
			angleDiference.push_back(line1[indexLine1]);
			angleDiference.push_back(mn);
			arrayDifference.push_back(angleDiference);
			while (angleDiference.size() != 0) {
				angleDiference.pop_back();
			}

		}
	}
	double mm = std::numeric_limits<double>::infinity();

	for (std::vector<std::vector<double>> ::iterator it = arrayDifference.begin(); it != arrayDifference.end(); ++it) {
		std::vector<double> ::iterator itx = it->begin();
		if (mm > *std::next(itx)) {
			angle = *itx;
		}
	}

	return angle;

}

double AntennaArray::getAngleMusicMethod(double * intervalSearch, float* phase, float frequency)
{
	int numberSources = 1;//could change 
	double angleResult;
	std::vector< std::vector<float>> matrix;
	std::vector<float> AOA_MUSIC;
	int numberValidPhases;
	float *APhase;
	float *ADistance;
	int snapShots = 50;//sacer fuera como paramatero configuracion
	arma::cx_mat steeringMatrix;
	arma::cx_mat signal;
	arma::cx_mat noiseSubspace;
	arma::mat music;
	arma::mat AngleOfArrival;
	std::vector<float> arrayAOA;
	std::vector<float> arrayAOA_oneSource;

	getValidSetup_ArrayAntennas(phase, frequency);


	APhase = new float[antennas_map.size()];
	ADistance = new float[antennas_map.size()];
	int j = 0;
	for (auto itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
		APhase[j] = itr->second;
		ADistance[j] = itr->first;
		j++;
	}

	for (numberValidPhases = 0; numberValidPhases < antennas_map.size(); numberValidPhases++) {

		steeringMatrix = getSteeringMat_Phase(APhase[numberValidPhases], numberSources);
		signal = simulateSignal(steeringMatrix, frequency, snapShots, numberSources);
		//noise();
		noiseSubspace = getNoiseSubspace(signal, numberSources, frequency, intervalSearch);
		//noiseSubspace = improveAlgorithmMusic(signal, numberSources, frequency, intervalSearch);

		music = musicRealSignal(noiseSubspace, ADistance[numberValidPhases], intervalSearch);

		//estimation maximun method
		arrayAOA_oneSource.push_back(AOA_maximunMethod(music, intervalSearch));

		//estimation multiple maximuns 
		matrix.push_back(AOA_analyseAllPosibilities(music, intervalSearch));

	}


	angleResult = getAngle_maximunMethod(arrayAOA_oneSource);
	//angleResult = getAngle_analyseAllPosibilities(matrix);


	std::cout << std::endl << std::endl;
	delete APhase;
	delete ADistance;

	return angleResult;
}

AntennaArray::~AntennaArray()
{
}

