#include <gtest/gtest.h>
#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")

#include "db.h"
#include "headers.h"

TEST(DB, car_check_reserve) {
  DB TestDB;
  extern stringstream qq;
  string a = "2";

  TestDB.CheckCarReserve(a);

  ASSERT_EQ(qq.str(), "Available");
}

TEST(DB, car_reserve) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");
  string a = "2";

  TestDB.SetCarReserve(a);
  TestDB.CheckCarReserve(a);

  ASSERT_EQ(qq.str(), "Reserved");
}

TEST(DB, car_name) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");
  string a = "3";

  TestDB.CarName(a);

  ASSERT_EQ(qq.str(), "Toyota Camry");
}

TEST(DB, car_price) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");
  string a = "5";

  TestDB.CarPrice(a);

  ASSERT_EQ(qq.str(), "1800.0");
}

TEST(DB, car_remove_reserve) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");
  string a = "3";

  TestDB.CheckCarReserve(a);
  if (qq.str() == "Reserved") {
    qq.str("");
    TestDB.RemoveCarReserve(a);
    TestDB.CheckCarReserve(a);
  }

  ASSERT_EQ(qq.str(), "Available");
}

TEST(DB, client_license) {
  DB TestDB;
  extern stringstream qq;
  qq.str("");
  string a = "1234567899";

  TestDB.ClientGetLicenese(a);

  ASSERT_EQ(qq.str(), a);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}