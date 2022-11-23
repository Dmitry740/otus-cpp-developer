#include <iostream>

#include "db.h"

// Data Base manual control
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
  // qq.str("");
  // RentCar.CheckCarReserve("4");
  // qq.str("");
  // RentCar.CheckCarReserve("1");
  // RentCar.PrintClientData("1234567899");
}