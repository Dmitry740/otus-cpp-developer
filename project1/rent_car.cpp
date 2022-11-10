#include <iostream>

#include "chat_bot.h"
#include "db.h"

struct Client {
  std::string last_name;
  std::string first_name;
  size_t lisence = 0;
  std::string rented_car;
  size_t rent_period;
};

int main() {
  DB RentCar;
  Client client;
  int answer = 0;
  RentCar.UpdateData();

  std::cout << "Hi, i'm Nic. Chose what's you like and enter the number"
            << std::endl;
  std::cout << "1. Look a list of cars" << std::endl;
  std::cout << "2. Cancel" << std::endl;

  std::cin >> answer;

  if (answer > 2 || answer < 1) {
    std::cout << "Error: Entered wrong value" << std::endl;
    return -1;
  } else if (answer == 2) {
    std::cout << "Thanks for your visit, good buy" << std::endl;
    return 0;
  } else {
    RentCar.ShowTable();
  }

  std::cout << "If you want to rent a car - enter car ID number" << std::endl;
  std::cout << "For cancel enter '0'" << std::endl;

  std::cin >> answer;

  if (answer > 5 || answer < 0) {
    std::cout << "Error: Entered wrong value" << std::endl;
    return -1;
  } else if (answer == 0) {
    std::cout << "Thanks for your visit, good buy" << std::endl;
    return 0;
  } else {
    RentCar.ShowTable();
  }

  return 0;
}