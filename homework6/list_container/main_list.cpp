#include <iostream>

#include "list_container.hpp"

template <typename T>
void print_container(ListContainer<T>& container) {
  std::cout << "Elements: ";
  container.getelements();
  std::cout << std::endl;

  std::cout << "Get 6th elenent: " << container[5];
  std::cout << std::endl;

  std::cout << "Size: " << container.size() << std::endl;
  std::cout << std::endl << std::endl;
}

void test_container() {
  ListContainer<int> int_container;

  if (!int_container.empty()) {
    for (auto iter = int_container.begin(); iter != int_container.end();
         ++iter) {
      std::cout << iter.get() << ' ';
    }
  }

  std::cout << std::endl;

  int_container.push_back(0);
  int_container.push_back(1);
  int_container.push_back(2);
  int_container.push_back(3);
  int_container.push_back(4);
  int_container.push_back(5);
  int_container.push_back(6);
  int_container.push_back(7);
  int_container.push_back(8);
  int_container.push_back(9);

  std::cout << "Elements from iterator: ";
  for (auto iter = int_container.begin(); iter != int_container.end(); iter++) {
    std::cout << iter.get() << ' ';
  }

  std::cout << std::endl;

  print_container(int_container);

  int_container.erase(7);
  int_container.erase(5);
  int_container.erase(3);

  print_container(int_container);

  int_container.insert(0, 10);

  print_container(int_container);

  int_container.insert(4, 20);

  print_container(int_container);

  int_container.push_back(30);

  std::cout << "Elements from iterator: ";
  for (auto iter = int_container.begin(); iter != int_container.end(); ++iter) {
    std::cout << *iter << ' ';
  }

  std::cout << std::endl;

  print_container(int_container);
}

int main() {
  test_container();

  return 0;
}