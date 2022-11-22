#include <iostream>

#include "db.h"

int main() {
  DB RentCar;
  // RentCar.CreateCarTable();
  // RentCar.InsertCarData();
  // RentCar.CreateClientTable();
  // RentCar.PrintCarData();
  RentCar.RemoveCarReserve("1");
  RentCar.RemoveCarReserve("2");
  RentCar.RemoveCarReserve("3");
  RentCar.RemoveCarReserve("4");
  RentCar.RemoveCarReserve("5");
}