#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <ctime>

using namespace std;


const float threshold = 30;
const int the_number_of_dataset = 3;
const int feature_dim = 256;
const string model = "mobilenet_256";


int main(int argc, char **argv){
		
	float final_feature[feature_dim];
    float dataset_feature[feature_dim];
		
	ifstream feature_file;

	feature_file.open(argv[1]);
   
	
	if(!feature_file.is_open()){
		cout << "The file didn't open sucessfully" << endl;
		exit(EXIT_FAILURE);
	}
	string feature;
	getline(feature_file,feature,(char) feature_file.eof());
	
	//cout << feature<< endl;
	//cout << "HI"<< endl;

	feature_file.close();

	size_t pos = 0;
	string token;
	string indicate = " ";
	int i=0;
	while ((pos = feature.find(indicate)) != string::npos){
		token = feature.substr(0,pos);
		feature.erase(0,token.length()+1);
		istringstream iss (token);
		iss >> final_feature[i] ;
		i++;
	}
	//cout << final_feature[0] << endl;
	//cout << final_feature[255] << endl;


	string path1 = "/home/pi/Desktop/Face_identification_Raspberry_pi/database/";
	string path2 = "/";
	string file_name = ".txt";
	
	ifstream dataset_list;
	dataset_list.open("dataset_list.txt");
	string dataset_list_content[the_number_of_dataset];
    int w=0;
    while(!dataset_list.eof()){
		getline(dataset_list,dataset_list_content[w]);
		w++;
	}
	dataset_list.close();


	
	for (int k=0;k<the_number_of_dataset;k++){
	
		feature_file.open(path1 + model + path2 + to_string(k) + file_name);
		if(!feature_file.is_open()){
			cout << "SHIT" << endl;
			cout << "The file didn't open sucessfully" << endl;
			exit(EXIT_FAILURE);
		}
	
		getline(feature_file,feature,(char) feature_file.eof());
	
		i=0;
		while ((pos = feature.find(indicate)) != string::npos){
			token = feature.substr(0,pos);
			feature.erase(0,token.length()+1);
			istringstream iss (token);
			iss >> dataset_feature[i] ;
			i++;
		}
		//cout << dataset_feature[0] << endl;
		//cout << dataset_feature[255] << endl;

    


		float difference = 0;
		for (int j=0 ; j<feature_dim ;j++){
			difference = difference + pow(dataset_feature[j]-final_feature[j],2);
		}
		//difference = sqrt(difference);

		cout << "The distance between you and " << dataset_list_content[k] <<" is " << difference << endl;


		//Read the face information of dataset
		feature_file.close();
		
		if (difference<threshold){
			cout << "HI! " << dataset_list_content[k] << endl;
			ofstream log;
			log.open("log.txt",fstream::app);
			time_t now = time(0);

			cout << dataset_list_content[k] << " loggd in at " << ctime(&now) << endl;

			
			log << dataset_list_content[k] << " logged in at " << ctime(&now) << endl;
			log.close();
			break;
		}
		if (k==the_number_of_dataset-1){
			cout << "Please try again " << endl;
		}
	}



	cout << "Press Enter to continue... " << endl;
	cin.get();
}


