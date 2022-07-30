#include "gess_number.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <map>

//Generator of max_value
int GeneretorNumber(const int new_value) {

	std::srand(std::time(nullptr)); // use current time as seed for random generator
	const int random_value = std::rand() % new_value;

	return random_value;
}

//Print Scores Table
void PrintScoresTable() {

	const std::string high_scores_filename = "high_scores.txt";
	std::ifstream in_file(high_scores_filename);
	if (!in_file.is_open()) {
		std::cout << "Faild to open file " << high_scores_filename << "!" << std::endl;
		return;
	}

	std::string user_name;
	int high_score = 0;
	std::map<std::string, int> table;
		
	while (true) {
		std::getline(in_file, user_name, '-');
		in_file >> high_score;
		if (!table.empty() && table.count(user_name) == 1) {
			if (high_score < table.at(user_name)) {
				table[user_name] = high_score;
			}
		}
		else {
			table[user_name] = high_score;
		}	
		
		in_file.ignore();

		if (in_file.fail()) {
			break;
		}
	}
	std::cout << std::endl;
	std::cout << "High scores table:" << std::endl;

	int pos = 1;
	for (int i = 0; i < 2000; ++i) {
		for (const auto n : table) {
			if (n.second == pos && !n.first.empty()) {
			std::cout << n.first << '\t' << '\t'<< n.second << std::endl;
			}
		}
		++pos;
	}
	in_file.close();
}

//Print in file
void PrintInFile(const std::string& user_name, const int& attempts) {
	std::ofstream out_file;
	out_file.open("high_scores.txt", std::ios_base::app);
	out_file.close();

	const std::string high_scores_filename = "high_scores.txt";
	std::ifstream in_file(high_scores_filename);
	if (!in_file.is_open()) {
		std::cout << "Faild to open file " << high_scores_filename << "!" << std::endl;
		return;
	}
	std::string name;
	int high_score = 0;
	std::map<std::string, int> table;
	
	while (true) {
		std::getline(in_file, name, '-');
		in_file >> high_score;
		if (!table.empty() && table.count(name) == 1) {
			if (high_score < table.at(name)) {
				table[name] = high_score;
			}
		} 
		else {
			table[name] = high_score;
		}	
	
	in_file.ignore();

	if (in_file.fail()) {
		break;
	}
	}
	in_file.close();

	if (table.count(user_name) == 1 && attempts < table.at(user_name)) {
		table[user_name] = attempts;
		std::ofstream out_file;
		out_file.open(high_scores_filename, std::ios_base::out);
		if (!out_file.is_open()) {
			std::cout << "Faild to open file " << high_scores_filename << "!" << std::endl;
			return;
		}
	for (const auto n : table) {
		out_file << n.first << '-';
		out_file << n.second;
		out_file << std::endl;
	}
		out_file.close();

	}
	else {
		std::ofstream out_file;
		out_file.open("high_scores.txt", std::ios_base::app);
		if (!out_file.is_open()) {
			std::cout << "Faild to open file " << high_scores_filename << "!" << std::endl;
			return;
		}
		out_file << user_name << '-';
		out_file << attempts;
		out_file << std::endl;

		out_file.close();
	}
}