#include <iostream>

#include "chat_bot.h"
#include "db.h"

// class Client {
//  public:
//   Client() = default;
//   ~Client() = default;

//   Client(const Client &other) {
//     m_first_name = other.m_first_name;
//     m_last_name = other.m_last_name;
//     m_lisence = other.m_lisence;
//     m_rent_period = other.m_rent_period;
//     m_rented_car = other.m_rented_car;
//   }

//   Client &operator=(const Client &other) {
//     Client temp{other};
//     *this = std::move(temp);

//     return *this;
//   }

//   Client(Client &&other) noexcept {
//     m_first_name = other.m_first_name;
//     other.m_first_name.clear();

//     m_last_name = other.m_last_name;
//     other.m_last_name.clear();

//     m_lisence = other.m_lisence;
//     other.m_lisence = 0;

//     m_rent_period = other.m_rent_period;
//     other.m_rent_period.clear();

//     m_rented_car = other.m_rented_car;
//     other.m_rented_car.clear();
//   }

//   Client &operator=(Client &&other) noexcept {
//     if (this == &other) {
//       return *this;
//     }
//     m_first_name = other.m_first_name;
//     other.m_first_name.clear();

//     m_last_name = other.m_last_name;
//     other.m_last_name.clear();

//     m_lisence = other.m_lisence;
//     other.m_lisence = 0;

//     m_rent_period = other.m_rent_period;
//     other.m_rent_period.clear();

//     m_rented_car = other.m_rented_car;
//     other.m_rented_car.clear();
//   }

//  private:
//   std::string m_last_name;
//   std::string m_first_name;
//   size_t m_lisence = 0;
//   std::string m_rented_car;
//   std::string m_rent_period;
// };

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