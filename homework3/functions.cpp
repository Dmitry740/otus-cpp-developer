#include "gess_number.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

//Generator of max_value

int GeneretorNumber(const int new_value)
{

	std::srand(std::time(nullptr)); // use current time as seed for random generator

	const int random_value = std::rand() % new_value;

	// std::cout << random_value << std::endl;

	return random_value;
}

//Print Scores Table

void PrintScoresTable() {
const std::string high_scores_filename = "high_scores.txt";
std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Faild to open file " << high_scores_filename << "!" << std::endl;
		return;
	}
	std::cout << std::endl;
	std::cout << "High scores table:" << std::endl;

	std::string username;
	int high_score = 0;
	std::string line;
	int min_score = 100;
	std::string name;
		
		//new version of printing High score table
		while(true) {
		
					
			in_file >> username;
			in_file >> high_score;
			in_file.ignore();

			if (in_file.fail()) {
				break;
		    }
		
			in_file.seekg(0L, std::ios_base::beg);
			do {
				if (line.find(username)) {
				in_file >> name >> high_score;
					if (high_score < min_score) {
					min_score = high_score;
					}
				}
				
			}
			while (std::getline(in_file, line));
			std::cout << username << '\t' << min_score << std::endl;
		}		
			
		
	
    //old version of printing High score table
	// while (true)
	// {
	// in_file >> username;
	// in_file >> high_score;

	// in_file.ignore();

	// if (in_file.fail()) {
	// 	break;
	// }
	// std::cout << username << '\t' << '\t' << high_score << std::endl;
	// }
}

//Print in file

void PrintInFile(const std::string& user_name, const int& attempts) {
	const std::string high_scores_filename = "high_scores.txt";
	std::ofstream out_file{high_scores_filename, std::ios_base::app};
	if (!out_file.is_open())
	{
		std::cout << "Faild to open file " << high_scores_filename << "!" << std::endl;
		return;
	}
	out_file << user_name << ' ';
	out_file << attempts;
	out_file << std::endl;
}