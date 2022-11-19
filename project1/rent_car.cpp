#include <iostream>

#include "db.h"

int main() {
  DB RentCar;
  // RentCar.CreateCarTable();
  // RentCar.InsertCarData();
  // RentCar.CreateClientTable();
  // RentCar.PrintData();
  // RentCar.CheckReserve("3");
  RentCar.UpdateData("1");
  RentCar.UpdateData("2");
  RentCar.UpdateData("3");
  RentCar.UpdateData("4");
  RentCar.UpdateData("5");
  // RentCar.CheckReserve("2");
}