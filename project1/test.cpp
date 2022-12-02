#include <gtest/gtest.h>
#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")

#include "headers.h"

TEST(DB, car_check_reserve) {
  DB TestDB;
  extern stringstream qq;

  TestDB.CheckCarReserve("2");

  ASSERT_EQ(qq.str(), "Available");
}

TEST(DB, car_reserve) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");

  TestDB.SetCarReserve("3");
  TestDB.CheckCarReserve("3");

  ASSERT_EQ(qq.str(), "Reserved");
}

TEST(DB, car_name) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");

  TestDB.CarName("1");

  ASSERT_EQ(qq.str(), "Toyota Camry");
}

TEST(DB, car_price) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");

  TestDB.CarPrice("5");

  ASSERT_EQ(qq.str(), "1800.0");
}

TEST(DB, car_remove_reserve) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");

  TestDB.CheckCarReserve("3");
  if (qq.str() == "Reserved") {
    qq.str("");
    TestDB.RemoveCarReserve("3");
    TestDB.CheckCarReserve("3");
  }

  ASSERT_EQ(qq.str(), "Available");
}

TEST(DB, client_license) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");

  TestDB.ClientGetLicenese("1234567899");

  ASSERT_EQ(qq.str(), "1234567899");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}