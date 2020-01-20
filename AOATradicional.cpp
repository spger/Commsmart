#include "AOATradicional.h"

////SETUP ARRAY ANTENNAS///////
int antennas_number = 4;
float antennas_distance[3] = { 0.2, 1, 2.5 };

//create new antennas object
Antenna* Antenna_array = new Antenna(antennas_distance, antennas_number);

/////////////////////////////

std::map< float, float > antennas_map;
std::map<float, float>::iterator itr;

int antNumber;
std::vector< std::pair<float, std::string>>distance;
int snapShots;
double *IntervalSearch;
float *APhase;

AOATradicional::AOATradicional(Antenna * array_antenna_setup)
{
	antNumber = array_antenna_setup->num_ant;
	distance = array_antenna_setup->pair_antennas;
	snapShots = array_antenna_setup->snapShots;
	IntervalSearch = array_antenna_setup->IntervalSearch;
}


AOATradicional::~AOATradicional()
{
}
int AOATradicional::get_valid_setup(float *phase, float dmax, int sourceNumber) {

	std::vector<std::pair<float, std::string>> pair_Aphases;

	float *full_APhase = NULL;

	if (antennas_distance != NULL) {
		try {
			//CHECK IF DISTANCE BETWEEN ANTENNAS ARE NOT BIGGER THAN DMAX
			//TAKE ONLY PAIR ANTENNAS WITH VALID DISTANCE
			//AND PAIR DISTANCE PAIR WITH APHASE PAIR

			if (antNumber == 3) {
				//get whole phase difference between antennas array
				full_APhase = new float[3];
				full_APhase[0] = phase[0] - phase[1];// A1 ---- APhase ---- A2
				full_APhase[1] = phase[0] - phase[2];// A1 ---- APhase ---- A3
				full_APhase[2] = phase[1] - phase[2];// A2 ---- APhase ---- A3

				std::cout << "Getting Phase Difference:  " << std::endl;
				pair_Aphases.push_back(std::make_pair(full_APhase[0], std::string("A1 ---- AP1 ---- A2")));
				pair_Aphases.push_back(std::make_pair(full_APhase[1], std::string("A1 ---- AP2 ---- A3")));
				pair_Aphases.push_back(std::make_pair(full_APhase[2], std::string("A1 ---- AP3 ---- A4")));


				for (int k = 0; k < pair_Aphases.size(); ++k) {
					std::cout << std::to_string(pair_Aphases[k].first) << "  " << pair_Aphases[k].second << std::endl;
				}


				for (int k = 0; k < pair_Aphases.size(); ++k) {

					if (distance[k].first < dmax) {

						antennas_map.insert(std::make_pair(distance[k].first, pair_Aphases[k].first));

					}

				}
				std::cout << "Getting Valid Pair PHASE / ANTENNAS DISTANCE:  " << std::endl;
				std::cout << "   DISTANCE --> APHASE" << std::endl;
				for (itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
					std::cout << '\t' << itr->first
						<< '\t' << itr->second << '\n';
				}


				//OLD CODE
				/*pair_antennas = new float[counter];
				antennas_position = new int[counter];

				for (int k = 0; k < counter; k++) {
					for (int m = 0; k < antNumber; m++) {
						if (antennas_distance[m] < dmax) {
							pair_antennas[k] = antennas_distance[m];
							antennas_position[k] = m;
							k++;



						}
					}
				}

				std::cout << "comprobada distancia entre antenas" << std::endl
					<< "numero de pares de antenas validos: " << counter << std::endl;




				////chose phase differende using pair antennas

				APhase = new float[counter];
				for (int k = 0; k < counter; k++) {
					APhase[k] = full_APhase[antennas_position[k]];

				}

				//mostrar en pantalla

				for (int k = 0; k < counter; k++) {
					std::cout << "Distances to apply MUSIC: " << std::to_string(pair_antennas[k]) << std::endl
						<< "APhase to apply MUSIC: " << std::to_string(APhase[k]) << std::endl;
				}
				*/
			}


			/////////////////////////////////////////////

			if (antNumber == 4) {

				full_APhase = new float[6];
				full_APhase[0] = phase[0] - phase[1];// A1 ---- APhase ---- A2
				full_APhase[1] = phase[0] - phase[2];// A1 ---- APhase ---- A3
				full_APhase[2] = phase[0] - phase[3];// A1 ---- APhase ---- A4
				full_APhase[3] = phase[1] - phase[2];// A2 ---- APhase ---- A3
				full_APhase[4] = phase[2] - phase[3];// A3 ---- APhase ---- A4
				full_APhase[5] = phase[1] - phase[3];// A2 ---- APhase ---- A4

				pair_Aphases.push_back(std::make_pair(full_APhase[0], std::string("A1 ---- AP1 ---- A2")));
				pair_Aphases.push_back(std::make_pair(full_APhase[1], std::string("A1 ---- AP2 ---- A3")));
				pair_Aphases.push_back(std::make_pair(full_APhase[2], std::string("A1 ---- AP3 ---- A4")));
				pair_Aphases.push_back(std::make_pair(full_APhase[3], std::string("A2 ---- AP4 ---- A3")));
				pair_Aphases.push_back(std::make_pair(full_APhase[4], std::string("A3 ---- AP5 ---- A4")));
				pair_Aphases.push_back(std::make_pair(full_APhase[5], std::string("A2 ---- AP6 ---- A4")));

				std::cout << "Getting Phase Difference:  " << std::endl;
				for (int k = 0; k < pair_Aphases.size(); ++k) {
					std::cout << std::to_string(pair_Aphases[k].first) << "  " << pair_Aphases[k].second << std::endl;
				}

				for (int k = 0; k < pair_Aphases.size(); ++k) {

					if (distance[k].first < dmax) {

						antennas_map.insert(std::make_pair(distance[k].first, pair_Aphases[k].first));
						//IMPORTANTE//
						/*CUANDO SE CREA EL MAPA SI HAY ALGUN VALOR REPETIO ENTRE LAS DISTANCIAS ENTRE ANTENAS, SE ELEMINA UNA PAREJA DE ANTENAS
						CON LA DISTANCIA REPETIDA, POR LO QUE TAMBIEN SE ELIMINA SU PAREJA DE FASE*/

					}

				}
				std::cout << "Getting Valid Pair PHASE / ANTENNAS DISTANCE:  " << std::endl << std::endl;

				std::cout << "   DISTANCE --> APHASE" << std::endl;
				for (itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
					std::cout << '\t' << itr->first
						<< '\t' << itr->second << '\n';
				}

			}

			/////////////////////////////////////////////


			if (antNumber == 5) {

				full_APhase = new float[10];
				full_APhase[0] = phase[0] - phase[1];// A1 ---- APhase ---- A2
				full_APhase[1] = phase[0] - phase[2];// A1 ---- APhase ---- A3
				full_APhase[2] = phase[0] - phase[3];// A1 ---- APhase ---- A4
				full_APhase[3] = phase[0] - phase[4];// A1 ---- APhase ---- A5
				full_APhase[4] = phase[1] - phase[2];// A2 ---- APhase ---- A3
				full_APhase[5] = phase[2] - phase[3];// A3 ---- APhase ---- A4
				full_APhase[6] = phase[3] - phase[4];// A4 ---- APhase ---- A5
				full_APhase[7] = phase[1] - phase[3];// A2 ---- APhase ---- A4
				full_APhase[8] = phase[2] - phase[4];// A3 ---- APhase ---- A5
				full_APhase[9] = phase[1] - phase[4];// A2 ---- APhase ---- A5


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

				std::cout << "Getting Phase Difference:  " << std::endl;
				for (int k = 0; k < pair_Aphases.size(); ++k) {
					std::cout << std::to_string(pair_Aphases[k].first) << "  " << pair_Aphases[k].second << std::endl;
				}

				for (int k = 0; k < pair_Aphases.size(); ++k) {

					if (distance[k].first < dmax) {

						antennas_map.insert(std::make_pair(distance[k].first, pair_Aphases[k].first));
						//IMPORTANTE//
						/*CUANDO SE CREA EL MAPA SI HAY ALGUN VALOR REPETIO ENTRE LAS DISTANCIAS ENTRE ANTENAS, SE ELEMINA UNA PAREJA DE ANTENAS
						CON LA DISTANCIA REPETIDA, POR LO QUE TAMBIEN SE ELIMINA SU PAREJA DE FASE*/

					}

				}
				std::cout << "Getting Valid Pair PHASE / ANTENNAS DISTANCE:  " << std::endl;
				std::cout << "   DISTANCE --> APHASE" << std::endl;
				for (itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
					std::cout << '\t' << itr->first
						<< '\t' << itr->second << '\n';
				}

			}

			if (antennas_map.empty()) {
				std::cout << "ERROR CALCULO ANGULO. Relacion frecuencia y distancia entre el array de antenas incompatible" << std::endl;
				return 1;
			}
			if (antennas_map.size() <= sourceNumber++) {
				std::cout << "ERROR CALCULO DE ANGULO. Relacion antenas validad y numero de señales incidentes erroneo. Numero de señales incidentes> numero de antenas " << std::endl;

				return 1;
			}


			std::vector< std::pair<float, std::string>>().swap(pair_Aphases);//free memory

			delete full_APhase;
			return 0;

		}
		catch (std::exception) {
			int pepe = 0;
		}
	}
}


float  AOATradicional::calculate_traditional_AOA(float freq, float *phase) {
	//lamda = frequency * light speed
	int number_elements = sizeof(phase);
	float frequency = freq;
	//int number_elements = sizeof(phase)/ sizeof(phase[0]);

	get_valid_setup(phase, frequency,number_elements);
	APhase = new float[antennas_map.size()];

	int j = 0;
	for (itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
		APhase[j] = itr->second;

		j++;
	}
	j = 0;


	//calculo una diferencia de phase menos en relacion al numero de phases.
	for (int x = 0; x < number_elements; x++) {
		AOA = asin((APhase[x] * frequency * arma::datum::c_0)/(2* arma::datum::pi *  distance_array[0]));
		std::cout << "AOA  " << AOA << std::endl;


		
	}
	
	return 0;
}