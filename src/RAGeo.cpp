//============================================================================
// Name        : RAGeo.cpp
// Author      : Mohamed-Amjad LASRI
// Version     : 0.0.0
// Copyright   : Work done during my PhD
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <armadillo>

#define MAX_MATRIX_ROWS 500000

using namespace std;
using namespace arma;

/**
 * \brief
 */
typedef struct{
	string name;
	mat time_serie;
}receiver, *preceiver;


string separateur = ",";

vector <receiver> receivers;


/**
 * \brief test if a receiver name exists in receivers list
 * @param receiver_name le nom du récepteur qu'on cherche dans la liste
 * @return true si le recepteur existe dans la liste des recepteurs et false sinon.
 */
bool receiverExists(string receiver_name){
	short int i;
	unsigned char number_of_receivers = (unsigned char)receivers.size();
	for(i=0; i<number_of_receivers; i++){
		if( receiver_name == receivers[i].name){
			return true;
		}
	}
	return false;
}

/**
 * \brief parse une ligne csv et renvoie les éléments dans un vecteur string
 * @param line est la ligne qu'on veut parser
 * @param delim est le séparateur
 * @return le vecteur qui contient les sub-chaines contenues dans la ligne CSV
 */
vector <string> parse_csv_line(string line, string delim){

	vector <string> parsed_values;
	size_t found;
	while(1){
		found = line.find(separateur);

		if(found == string::npos){
			// Parser la dernière valeur de la ligne et sortir
			parsed_values.push_back(line);
			break;
		}
		parsed_values.push_back(line.substr(0, found));
		line = line.erase(0, found+1);
	}
	return parsed_values;
}

/**
 * \brief
 * @param sep
 * @param line
 * @param end_pos
 * @return
 */
size_t get_separator_occurences(string sep, string line, size_t end_pos){

	size_t pos;
	size_t count;
	count = 1;
	pos = line.find(sep); // trouver la première occurence de separateur
	while (pos <= end_pos && pos != string::npos){
		pos = line.find(sep,pos+1);
		count++;
	}
	return count;
}


/**
 *
 * @param:
 * @return:
 */
void get_position(string line, size_t &name_pos, size_t &unix_time_pos, size_t &x_pos, size_t &y_pos, size_t &z_pos, size_t &pdop_pos, size_t &rms_pos,
		size_t &sig_x_pos, size_t &sig_y_pos, size_t &sig_z_pos, short int &count){

	size_t found;
	string tmp_substr;

	// Chercher l'emplacement de name
	found = line.find("NAME");

	if (found == std::string::npos){
		cerr<<"FATAL ERROR: NAME not found in CSV header line. "<<endl;
		// TODO: Il faut sortir ou continuer
	} else {
		unix_time_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de unix_time
	found = line.find("UNIX_TIME");

	if (found == std::string::npos){
		cerr<<"FATAL ERROR: UNIX_TIME not found in CSV header line. "<<endl;
		// TODO: Il faut sortir ou continuer
	} else {
		unix_time_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de x_pos
	found = line.find("X_CART");

	if(found == string::npos){
		cerr<<"FATAL ERROR: X not found in CSV header line. "<<endl;
	} else {
		x_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de y_pos
	found = line.find("Y_CART");

	if(found == string::npos){
		cerr<<"FATAL ERROR: Y not found in CSV header line. "<<endl;
	} else {
		y_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de z_pos
	found = line.find("Z_CART");

	if(found == string::npos){
		cerr<<"FATAL ERROR: Z not found in CSV header line. "<<endl;
	} else {
		z_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de pdop_pos
	found = line.find("PDOP");

	if(found == string::npos){
		cerr<<"FATAL ERROR: PDOP not found in CSV header line. "<<endl;
	} else {
		pdop_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de rms_pos
	found = line.find("RMS");

	if(found == string::npos){
		cerr<<"FATAL ERROR: RMS not found in CSV header line. "<<endl;
	} else {
		rms_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de sig_x_pos
	found = line.find("SIGMA_X");

	if(found == string::npos){
		cerr<<"FATAL ERROR: SIGMA X not found in CSV header line. "<<endl;
	} else {
		sig_x_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de sig_y_pos
	found = line.find("SIGMA_Y");

	if(found == string::npos){
		cerr<<"FATAL ERROR: SIGMA Y not found in CSV header line. "<<endl;
	} else {
		sig_y_pos = get_separator_occurences(separateur, line, found);
		count++;
	}

	// Chercher l'emplacement de sig_z_pos
	found = line.find("SIGMA_Z");

	if(found == string::npos){
		cerr<<"FATAL ERROR: SIGMA Z not found in CSV header line. "<<endl;
	} else {
		sig_z_pos = get_separator_occurences(separateur, line, found);
		count++;
	}
}


/**
 * \brief
 */


/*
 * @param:
 * @return:
 */
bool parse_csv_file(const char *filename) {

  size_t x_pos = string::npos,
		 y_pos = string::npos,
		 z_pos = string::npos,
		 rms_pos = string::npos,
		 pdop_pos = string::npos,
		 sig_x_pos = string::npos,
		 sig_y_pos = string::npos,
		 sig_z_pos = string::npos,
		 unix_time_pos = string::npos,
  	  	 name_pos = string::npos;

  string line;

  ifstream results_file (filename);

  string receiver_name;

  vector<string> csv_values;

  receiver tmp_receiver;

  vec tmp_vec;

  short int count;
  count = 0;

  if(results_file.is_open()){

	  // Check the header
	  getline(results_file, line);
	  get_position( line, name_pos, unix_time_pos, x_pos, y_pos, z_pos, pdop_pos, rms_pos, sig_x_pos, sig_y_pos, sig_z_pos, count);
	  cout<<"NAME: "<<name_pos<<endl;
	  cout<<"UNIX_TIME: "<<unix_time_pos<<endl;
	  cout<<"X: "<<x_pos<<endl;
	  cout<<"Y: "<<y_pos<<endl;
	  cout<<"Z: "<<z_pos<<endl;
	  cout<<"PDOP: "<<pdop_pos<<endl;
	  cout<<"RMS: "<<rms_pos<<endl;
	  cout<<"SIGMA_X: "<<sig_x_pos<<endl;
	  cout<<"SIGMA_Y: "<<sig_y_pos<<endl;
	  cout<<"SIGMA_Z: "<<sig_z_pos<<endl;


	  while(getline(results_file, line)){
		  csv_values = parse_csv_line(line, separateur);
		  tmp_receiver.name = csv_values[name_pos-1];
		  tmp_receiver.time_serie.set_size(MAX_MATRIX_ROWS, count);

		  // Tester si le récepteur a déjà été rencontré dans le fichier csv

	  }
	  results_file.close();
	  return true;
  }else{
	  return false;
  }
}

/**
 * @param:
 * @return:
 */
int main(int argc, char **argv){

	// Open the CSV file
	if (parse_csv_file(argv[1])){

		return 0;
	}else{
		cout<<"A problem occured when tryin to open the CSV file. Please make sure that:"<<endl;
		cout<<"* The input file exists and it has the appropriate access rights."<<endl;
		cout<<"* The input file is a comma (,) sepparated file."<<endl;

		return 1;
	}

}
