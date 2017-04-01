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

using namespace std;

string separateur = ",";


/**
 * @param:
 * @return:
 */
size_t get_separator_occurences(string sep, string line, size_t end_pos){

	size_t pos;
	size_t count;
	count = 1;
	pos = line.find(sep, 0); // trouver la première occurence de separateur

	cout<<"PREMIERE OCCURENCE SEPARATOR: "<<pos<<endl;

	while (pos <= end_pos && pos != string::npos){
		pos = line.find(sep,pos+1);
		count++;
		cout<<"------------ OCCURENCE SEPARATOR: "<<count<<endl;
	}
	return count;

}


/**
 *
 * @param:
 * @return:
 */
void get_position(string line, size_t &unix_time_pos, size_t &x_pos, size_t &y_pos, size_t &z_pos, size_t &pdop_pos, size_t &rms_pos,
		size_t &sig_x_pos, size_t &sig_y_pos, size_t &sig_z_pos){

	size_t found;
	string tmp_substr;

	// Chercher l'emplacement de unix_time
	found = line.find("UNIX_TIME");

	if (found == std::string::npos){
		cerr<<"FATAL ERROR: UNIX_TIME not found in CSV header line. "<<endl;
		// TODO: Il faut sortir ou continuer
	} else {
		unix_time_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de x_pos
	found = line.find("X");

	if(found == string::npos){
		cerr<<"FATAL ERROR: X not found in CSV header line. "<<endl;
	} else {
		x_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de y_pos
	found = line.find("Y");

	if(found == string::npos){
		cerr<<"FATAL ERROR: Y not found in CSV header line. "<<endl;
	} else {
		y_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de z_pos
	found = line.find("Z");

	if(found == string::npos){
		cerr<<"FATAL ERROR: Z not found in CSV header line. "<<endl;
	} else {
		z_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de pdop_pos
	found = line.find("PDOP");

	if(found == string::npos){
		cerr<<"FATAL ERROR: PDOP not found in CSV header line. "<<endl;
	} else {
		pdop_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de rms_pos
	found = line.find("RMS");

	if(found == string::npos){
		cerr<<"FATAL ERROR: RMS not found in CSV header line. "<<endl;
	} else {
		rms_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de sig_x_pos
	found = line.find("SIGMA_X");

	if(found == string::npos){
		cerr<<"FATAL ERROR: SIGMA X not found in CSV header line. "<<endl;
	} else {
		sig_x_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de sig_y_pos
	found = line.find("SIGMA_Y");

	if(found == string::npos){
		cerr<<"FATAL ERROR: SIGMA Y not found in CSV header line. "<<endl;
	} else {
		sig_y_pos = get_separator_occurences(separateur, line, found);
	}

	// Chercher l'emplacement de sig_z_pos
	found = line.find("SIGMA_Z");

	if(found == string::npos){
		cerr<<"FATAL ERROR: SIGMA Z not found in CSV header line. "<<endl;
	} else {
		sig_z_pos = get_separator_occurences(separateur, line, found);
	}
}


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
		  unix_time_pos = string::npos;

  string line;

  ifstream results_file (filename);

  if(results_file.is_open()){

    // Check the header
    getline(results_file, line);
    get_position( line, unix_time_pos, x_pos, y_pos, z_pos, pdop_pos, rms_pos, sig_x_pos, sig_y_pos, sig_z_pos);
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

      // Faire le traitement ici on cherche la colonne de chaque type de données


    }
    results_file.close();
    return true;
  } else {
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
