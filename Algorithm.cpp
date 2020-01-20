#include "Algorithm.h"

//std::string filename = "input.xml";
//std::string tag = "numberAntennas";
//std::string text = getFile(filename);
//std::vector<string> all = getData(text, tag);

int antennasNumber = 4;
float antennas_dist[3] = { 0.025, 1, 3 };
double intervalSearch[3] = { -90, 90, 0.1 };

Antenna *setupArrayAtennas = new Antenna(antennasNumber, antennas_dist, intervalSearch);


Algorithm* Algorithm::Singleton_instance = 0;

std::map< float, float > antennas_map;
std::map<float, float>::iterator itr;

int antNumber;
int snapShots = 50;
std::vector< std::pair<float, std::string>>antennas_distance;
float *pair_antennas;
double *IntervalSearch;


Algorithm::Algorithm(Antenna * array_antenna_setup)
{
	antNumber = array_antenna_setup->numberAntennas;
	antennas_distance = array_antenna_setup->pair_antennas;
	IntervalSearch = array_antenna_setup->intervalSearch;
}

Algorithm::~Algorithm()
{
}
Algorithm* Algorithm::getInstance() {
	if (Singleton_instance == 0) {
		Singleton_instance = new Algorithm(setupArrayAtennas);
	}

	return Singleton_instance;

}

int Algorithm::get_valid_setup(float *phase, float frequency, int sourceNumber) {

	float distanceMaxAntennas = arma::datum::c_0 / (2 * frequency);

	std::vector<std::pair<float, std::string>> pair_Aphases;

	float *full_APhase = NULL;

		try {
		//CHECK IF DISTANCE BETWEEN ANTENNAS ARE NOT BIGGER THAN DMAX
		//TAKE ONLY PAIR ANTENNAS WITH VALID DISTANCE
		//AND PAIR DISTANCE PAIR WITH APHASE PAIR

		if (antNumber == 3) {
				
			full_APhase = new float[3];
			full_APhase[0] = phase[1] - phase[0];// A1 ---- APhase ---- A2
			full_APhase[1] = phase[2] - phase[0];// A1 ---- APhase ---- A3
			full_APhase[2] = phase[2] - phase[1];// A2 ---- APhase ---- A3

			pair_Aphases.push_back(std::make_pair(full_APhase[0], std::string("A1 ---- AP1 ---- A2")));
			pair_Aphases.push_back(std::make_pair(full_APhase[1], std::string("A1 ---- AP2 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[2], std::string("A1 ---- AP3 ---- A4")));
 
		}


		if (antNumber == 4) {

			full_APhase = new float[6];
			full_APhase[0] = phase[1] - phase[0];// A1 ---- APhase ---- A2
			full_APhase[1] = phase[2] - phase[0];// A1 ---- APhase ---- A3
			full_APhase[2] = phase[3] - phase[0];// A1 ---- APhase ---- A4
			full_APhase[3] = phase[2] - phase[1];// A2 ---- APhase ---- A3
			full_APhase[4] = phase[3] - phase[2];// A3 ---- APhase ---- A4
			full_APhase[5] = phase[3] - phase[1];// A2 ---- APhase ---- A4

			//check algorith DELETE with distance prefixed
			full_APhase[0] = 0.408143178;// A1 ---- APhase ---- A2
			full_APhase[1] = 2.040715892;// A1 ---- APhase ---- A3
			full_APhase[2] = 5.101789729;// A1 ---- APhase ---- A4
			full_APhase[3] = 1.632572713;// A2 ---- APhase ---- A3
			full_APhase[4] = 3.06107383;// A3 ---- APhase ---- A4
			full_APhase[5] = 4.693646551;// A2 ---- APhase ---- A4

			pair_Aphases.push_back(std::make_pair(full_APhase[0], std::string("A1 ---- AP1 ---- A2")));
			pair_Aphases.push_back(std::make_pair(full_APhase[1], std::string("A1 ---- AP2 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[2], std::string("A1 ---- AP3 ---- A4")));
			pair_Aphases.push_back(std::make_pair(full_APhase[3], std::string("A2 ---- AP4 ---- A3")));
			pair_Aphases.push_back(std::make_pair(full_APhase[4], std::string("A3 ---- AP5 ---- A4")));
			pair_Aphases.push_back(std::make_pair(full_APhase[5], std::string("A2 ---- AP6 ---- A4")));
				
		}


		if (antNumber == 5) {

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

			
		/*// PRINT  PHASE DIFFERENCE
		std::cout << "Getting Phase Difference:  " << std::endl;
		for (int k = 0; k < pair_Aphases.size(); ++k) {
			std::cout << std::to_string(pair_Aphases[k].first) << "  " << pair_Aphases[k].second << std::endl;
		}*/

		for (int k = 0; k < pair_Aphases.size(); ++k) {

			if (antennas_distance[k].first < distanceMaxAntennas) {

				antennas_map.insert(std::make_pair(antennas_distance[k].first, pair_Aphases[k].first));
				//IMPORTANTE//
				/*CUANDO SE CREA EL MAPA SI HAY ALGUN VALOR REPETIO ENTRE LAS DISTANCIAS ENTRE ANTENAS, SE ELEMINA UNA PAREJA DE ANTENAS
				CON LA DISTANCIA REPETIDA, POR LO QUE TAMBIEN SE ELIMINA SU PAREJA DE FASE*/

			}

		}

		// PRINT VALID PHASE DIFFERENCE
		std::cout << "Getting Valid Pair PHASE / ANTENNAS DISTANCE:  " << std::endl;
		std::cout << "   DISTANCE --> APHASE" << std::endl;
		for (itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
			std::cout << '\t' << itr->first
				<< '\t' << itr->second << '\n';
		}

		if (antennas_map.empty()) {
				std::cout << "ERROR CALCULO ANGULO. Relacion frecuencia y distancia entre el array de antenas incompatible" << std::endl;
				return -1;
			}
		if (antennas_map.size() <= sourceNumber++) {
			std::cout << "ERROR CALCULO DE ANGULO. Relacion antenas validad y numero de señales incidentes erroneo. Numero de señales incidentes> numero de antenas " << std::endl;

			return -1;
		}

		//free memory
		std::vector< std::pair<float, std::string>>().swap(pair_Aphases);

		delete full_APhase;
		return 0;

	}
	catch (std::exception) {
			int pepe = 0;
	}
	
}
arma::cx_mat Algorithm::getSteeringMat_DOA(float *DOA, float lamda, int AntNumber, int NumSources, float distance) {

	arma::cx_mat mat;
	float *Doa_rad = NULL;
	
	//[rows x cols]
	mat.ones(NumSources, AntNumber);
	Doa_rad = new float[NumSources];
	for (int k = 0; k < NumSources; k++) {
		Doa_rad[k] = DOA[k] / 180 * arma::datum::pi;
	}

	for (int m = 0; m < NumSources; m++) {
		for (int k = 0; k < AntNumber; k++) {
			
			double aux = k * ((2 * arma::datum::pi * distance * sin(Doa_rad[m])) / lamda);
			arma::cx_double aux2 = arma::cx_double(aux, 0); //get complex number
			mat.row(m).col(k) = exp(-i * aux2);
		}
	}
	mat = mat.t();
	return mat;



}
arma::cx_mat  Algorithm::getSteeringMat_Phase(float* APhase, int NumSources, int numDetec) {

	int realNumberAntennas = 2;
	arma::cx_mat steeringMatrix;

	steeringMatrix.ones(NumSources, realNumberAntennas);//[rows x cols]


	for (int m = 0; m < NumSources; m++) {
		for (int k = 0; k < realNumberAntennas; k++) {

			arma::cx_double aux2 = arma::cx_double((k * APhase[m + numDetec]), 0); //get complex number
			steeringMatrix.row(m).col(k) = exp(-i * aux2);
		}
	}
	steeringMatrix = steeringMatrix.t();
	
	return steeringMatrix;
}

arma::cx_mat Algorithm::simulateSignal(arma::cx_mat &steeringMatrix, float frequency, int snapShots, int NumSources) {
	arma::cx_mat signal;

	signal.zeros(NumSources, snapShots);

	//arma::rowvec   crea vector fila
	//arma::vec crea vector columna
	arma::rowvec cadena(snapShots);
	for (int k = 0; k < snapShots; k++) {
		cadena.col(k) = k + 1;

		for (int m = 0; m < NumSources; m++) {
			arma::cx_double aux2 = arma::cx_double((frequency * cadena[k]), 0);
			signal.col(k).row(m) = arma::cx_double(2, 0) * exp(i*aux2);
		}
	}
	signal = steeringMatrix * signal;

	return signal;

}

arma::cx_mat Algorithm::noise(arma::cx_mat &signal) { 

	//modificar funcion para aceptar la configuracion del SNR
	arma::cx_mat signalWithNoise;
	const double mean = 0.0;
	const double stddev = 0.1;
	std::default_random_engine generator;
	std::normal_distribution<double> dist(mean, stddev);

	// Add Gaussian noise
	for (auto& signalWithNoise : signalWithNoise) {
		signalWithNoise = signalWithNoise + dist(generator);
	}

	return signalWithNoise;
}

arma::mat Algorithm::music(arma::cx_mat &signal, int NumSources, int AntNumber, double *scan, float lamda, float distance) {
	arma::cx_mat R; //dense matrix
	
	R = signal * trans(signal);

	//eigenvalues, eigenvectors = LA.eig(R)
	arma::cx_vec eigval;
	arma::cx_mat eigvec;
	arma::cx_mat sorteigvec;
	arma::cx_mat En;
	arma::mat Pmusic;
	En.ones(AntNumber, AntNumber - NumSources);
	sorteigvec.ones(AntNumber, AntNumber);



	arma::eig_gen(eigval, eigvec, R);

	arma::uvec indexval = sort_index(eigval, "descend");

	int ind;
	for (int k = 0; k < AntNumber; k++) {
		for (int m = 0; m < AntNumber; m++) {
			ind = int(indexval[m]);
			sorteigvec.row(k).col(m) = eigvec.row(k).col(ind);
		}

	}
	//estimate noise subspace

	for (int k = 0; k < (AntNumber - NumSources); k++) {
		En.col(k) = sorteigvec.col(AntNumber - (AntNumber - NumSources) + k);
	}

	//linspace( start, end, N )
	//Generate a vector with N elements; the values of the elements are linearly spaced from start to (and including) end
	//Caveat : if N ≤ 1, the generated vector will have a size of one, with the single element equal to end


	float precision = (scan[1] - scan[0]) / scan[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(scan[0], scan[1], precision);


	
	Pmusic.zeros(1, precision);
	for (int k = 0; k < precision - 1; k++) {
		arma::cx_mat SS;
		SS.zeros(1, AntNumber);
		for (int m = 0; m < AntNumber; m++) {

			double aux = 2 * m*arma::datum::pi* distance * sin(search[k] / 180 * arma::datum::pi) / lamda;
			arma::cx_double aux2 = arma::cx_double(aux, 0);
			SS.col(m) = exp(i*aux2);

		}

		arma::cx_mat PP;
		PP.zeros(1);

		PP = SS * En*arma::trans(En)*arma::trans(SS);


		//PP=SS*NN*NN'*SS'; 1x3*3x1
		Pmusic.col(k) = abs(1 / PP);


	}

	return Pmusic;
}
arma::mat Algorithm::Improve_Algorithm_Music(arma::cx_mat &signal, float *ADistance, int NumSources, float frequency, double *intervalSearch, int numDetection) {
	arma::cx_mat R;
	arma::cx_vec eigval;
	arma::cx_mat eigvec;
	arma::cx_mat sorteigvec;
	arma::cx_mat En;
	arma::cx_mat PP;
	arma::mat Pmusic;
	int real_antennas_number = 2;
	float lambda = arma::datum::c_0 / frequency;
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);
	R = signal * trans(signal); //work


	//Different Code to improve Music  between {}
	//{
	arma::mat J = arma::eye<arma::mat>(real_antennas_number, real_antennas_number);
	J = arma::fliplr(J);
	R = R + J * arma::conj(R)*J;
	//}

	//eigenvalues, eigenvectors = LA.eig(R)

	En.ones(real_antennas_number, real_antennas_number - NumSources);
	sorteigvec.ones(real_antennas_number, real_antennas_number);

	arma::eig_gen(eigval, eigvec, R);

	arma::uvec indexval = sort_index(eigval, "descend");

	int ind;
	for (int k = 0; k < real_antennas_number; k++) {
		for (int m = 0; m < real_antennas_number; m++) {
			ind = int(indexval[m]);
			sorteigvec.row(k).col(m) = eigvec.row(k).col(ind);
		}

	}

	//estimate noise subspace
	for (int k = 0; k < (real_antennas_number - NumSources); k++) {
		En.col(k) = sorteigvec.col(real_antennas_number - (real_antennas_number - NumSources) + k);
	}

	Pmusic.zeros(1, precision);

	for (int k = 0; k < precision - 1; k++) {
		arma::cx_mat SS;
		SS.zeros(1, real_antennas_number);
		for (int m = 0; m < real_antennas_number; m++) {
			arma::cx_double aux2 = arma::cx_double((m * (2 * arma::datum::pi* ADistance[numDetection] * sin(search[k] / 180 * arma::datum::pi) / lambda)), 0);
			SS.col(m) = exp(i*aux2);
		}

		PP = SS * En*arma::trans(En)*arma::trans(SS);
		Pmusic.col(k) = abs(1 / PP);

	}

	return Pmusic;

}
arma::mat Algorithm::music_Phase(arma::cx_mat &signal, float *ADistance, int NumSources, float frequency, double *intervalSearch, int numDetection) {
	arma::cx_mat R; 
	arma::cx_vec eigval;
	arma::cx_mat eigvec;
	arma::cx_mat sorteigvec;
	arma::cx_mat En;
	arma::cx_mat PP;
	arma::mat Pmusic;
	int real_antennas_number = 2;
	float lambda = arma::datum::c_0 / frequency;
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);

	R = signal * trans(signal);

	//eigenvalues, eigenvectors = LA.eig(R)
	
	En.ones(real_antennas_number, real_antennas_number - NumSources);
	sorteigvec.ones(real_antennas_number, real_antennas_number);

	arma::eig_gen(eigval, eigvec, R);

	arma::uvec indexval = sort_index(eigval, "descend");

	int ind;
	for (int k = 0; k < real_antennas_number; k++) {
		for (int m = 0; m < real_antennas_number; m++) {
			ind = int(indexval[m]);
			sorteigvec.row(k).col(m) = eigvec.row(k).col(ind);
		}

	}

	//estimate noise subspace
	for (int k = 0; k < (real_antennas_number - NumSources); k++) {
		En.col(k) = sorteigvec.col(real_antennas_number - (real_antennas_number - NumSources) + k);
	}

	Pmusic.zeros(1, precision);

	for (int k = 0; k < precision - 1; k++) {
		arma::cx_mat SS;
		SS.zeros(1, real_antennas_number);
		for (int m = 0; m < real_antennas_number; m++) {
			arma::cx_double aux2 = arma::cx_double((m * (2 * arma::datum::pi* ADistance[numDetection] * sin(search[k] / 180 * arma::datum::pi) / lambda)), 0);
			SS.col(m) = exp(i*aux2);
		}

		PP = SS * En*arma::trans(En)*arma::trans(SS);
		Pmusic.col(k) = abs(1 / PP);

	}

	return Pmusic;
}

double Algorithm::AOA_one_source(arma::mat &music, int NumSources, double *intervalSearch) {
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);//generate vector with angles intervals

	arma::uword j = music.index_max();
	double AOA = (-1)*search(j);

	return AOA;
}
std::vector<float> Algorithm::AOA(arma::mat &music, int NumSources, double *scan) {
	float precision = (intervalSearch[1] - intervalSearch[0]) / intervalSearch[2];
	arma::rowvec search = arma::linspace<arma::rowvec>(intervalSearch[0], intervalSearch[1], precision);//generate vector with angles intervals
	std::vector<float> aoaArray;

	for (int k = 1; k < (music.size() - 1); k++) {
		float aux = music(k);
		float aux1 = music(k - 1);
		float aux2 = music(k + 1);

		if (music(k) > music(k - 1) && music(k) > music(k + 1)) {
			aoaArray.push_back((-1)*search(k));
		}
	}

	return aoaArray;

}


float Algorithm::startMusic_real_signal(float *phase, float frequency) {
	
	double AOA_MUSIC;
	int sourceNum = 1;
	float *APhase;
	float *ADistance;
	int numberDetections;

	float lamda = arma::datum::c_0 / frequency;

	static arma::cx_mat steeringMatrix;//Mat<cx_double>//
	static arma::cx_mat signal; // misma fila que matrix//
	static arma::mat music;// signal after music//
	static arma::mat AngleOfArrival;
	std::vector<float> arrayAOA;

	get_valid_setup(phase, frequency, sourceNum);

	APhase = new float[antennas_map.size()];
	ADistance = new float[antennas_map.size()];
	int j = 0;
	for (itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
		APhase[j] = itr->second;
		ADistance[j] = itr->first;
		j++;
	}

	for (numberDetections = 0; numberDetections < antennas_map.size(); numberDetections++) {
		steeringMatrix = getSteeringMat_Phase(APhase, sourceNum, numberDetections);
		signal = simulateSignal(steeringMatrix, frequency, snapShots, sourceNum);
		//noise(steeringMatrix, signal);
		music = music_Phase(signal, ADistance, sourceNum, frequency, IntervalSearch, numberDetections);
		AOA_MUSIC = AOA_one_source(music, sourceNum, IntervalSearch);
		arrayAOA.push_back(AOA_MUSIC);
	}
	std::cout << std::endl;
	std::cout << "AOA_music Array  " << std::endl << std::endl;
	for (auto i = arrayAOA.begin(); i != arrayAOA.end(); ++i) {
		std::cout << *i << ' ';
		AOA_MUSIC = *i + AOA_MUSIC;
	}
	std::cout << std::endl << std::endl;
	delete APhase;
	delete ADistance;

	return AOA_MUSIC;
}
float Algorithm::startMusic_simulate_signal(float frequency) {

	float lamda = arma::datum::c_0 / frequency;
	int numberAntennas = 2;
	float distance = 0.2; 
	float DOA[] = { 76 };//degress
	//float freq[] = { 0.7853 };//rad
	float freq =  frequency*2*arma::datum::pi;//rad
	int sourceNum = 1;
	float angle;

	static arma::cx_mat steeringMatrix;//Mat<cx_double>//
	static arma::cx_mat signal; // misma fila que matrix//
	static arma::mat signal_music;// signal after music//
	static arma::mat AngleOfArrival;

	steeringMatrix = getSteeringMat_DOA(DOA, lamda, numberAntennas, sourceNum, distance);
	signal = simulateSignal(steeringMatrix, freq, snapShots, sourceNum);
	//noise(steeringMatrix, signal);
	signal_music = music(signal, sourceNum, numberAntennas, IntervalSearch, lamda, distance);
	//AngleOfArrival = AOA(signal_music, sourceNum, IntervalSearch);
	//std::cout << "AngleOfArrival simulate signal :\n" << AngleOfArrival << "\n";
	angle = AOA_one_source(signal_music, sourceNum, IntervalSearch);

	return angle;


}
float  Algorithm::calculate_traditional_AOA( float *phase, float frequency) {
	float lamda = arma::datum::c_0 / frequency;
	float AOATraditional;
	
	int sourceNum = 1;
	int numberAntennasElements;
	float *APhase;
	float *ADistance;

	get_valid_setup(phase, frequency, sourceNum);
	numberAntennasElements =antennas_map.size();
	APhase = new float[antennas_map.size()];
	ADistance = new float[antennas_map.size()];
	int j = 0;
	for (itr = antennas_map.begin(); itr != antennas_map.end(); ++itr) {
		APhase[j] = itr->second;
		ADistance[j] = itr->first;
		j++;
	}
	j = 0;

	for (int x = 0; x < numberAntennasElements; x++) {
		
		//Radianes
		float a = APhase[x] * lamda;
		float b = 2 * arma::datum::pi *  ADistance[x];
		float aux = (APhase[x] * lamda) / (2 * arma::datum::pi *  ADistance[x]);
		AOATraditional = asin((APhase[x] * lamda) / (2 * arma::datum::pi *  ADistance[x]));

		//Degrees
		AOATraditional = AOATraditional * (180 / arma::datum::pi);

		std::cout << "AOA_traditional  " << AOATraditional << std::endl;

	}
	
	return AOATraditional;
}
