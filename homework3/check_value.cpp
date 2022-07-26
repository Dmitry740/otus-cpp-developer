#include "gess_number.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
			
	//change max value through console
	if (argc > 0) {
		std::cout << "We have at least one argument!" << std::endl;
		std::cout << "argv[0] = " << argv[0] << std::endl;
		std::cout << std::endl;
		std::cout << "If you want to play on your ruls - enter after file_name.exe an argument '-max'/ '-level' and a number" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter '-table' to look at High scores table" << std::endl;
		std::cout << std::endl;
	}

	int parametr_value = 120;
	if (argc >= 2) {
		std::cout << "We have one more argument = " << argv[1] << std::endl;
		std::string argv1_value = argv[1];
		if (argv1_value == "-table") {
			PrintScoresTable();
			return 0;
		}
		if (argv1_value == "-max" || argv1_value == "-level") {
			std::cout << argv1_value << " argument was detected!" << std::endl;
				if (argc < 3) {
				std::cout << "Wrong usage! The argument " << "'" << argv1_value << "'" << " requars some value" << std::endl;
				return -1;
			}

			parametr_value = std::stoi(argv[2]);
			if (argv1_value == "-level" && parametr_value == 1) {
				parametr_value = 10;
			}
			 else if (argv1_value == "-level" && parametr_value == 2) {
				parametr_value = 50;
			}
			else if (argv1_value == "-level" && parametr_value == 3) {
				parametr_value = 100;
			}
			else {
				std::cout << "Error: Permited numbers are '1', '2', '3'!" << std::endl;
				return -1;
			}
		}
	}
	std::cout << "The '-max' value = " << parametr_value << std::endl;
	
	// Ask about name and start the game
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
	std::cout << "GO!!" << std::endl;

	const int target_value = GeneretorNumber(parametr_value);
	int current_value = 0;
	bool not_win = true;

	// Game
	std::cout << "Enter your guess:" << std::endl;
	int attempts = 1;

	do {
		std::cin >> current_value;
		if(std::cin.fail()) {
			std::cout << "Enter ONLY number!" << std::endl;
			return -1;
		}
		else if (current_value < target_value) {
			attempts += 1;
			std::cout << "greater than " << current_value << std::endl;
		}
		else if (current_value > target_value) {
			attempts += 1;
			std::cout << "less than " << current_value << std::endl;
		}
		else {
			std::cout << "you win!" << std::endl;
			std::cout << "Your attempts: " << attempts << std::endl;
			break;
		}

	} while(true);

	//Print in file
	PrintInFile(user_name, attempts);
	
	//Print scores table
	PrintScoresTable();
	
	return 0;
}