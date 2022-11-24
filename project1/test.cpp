#include <gtest/gtest.h>
#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")

#include "db.h"

TEST(DB, check_reserve_car) {
  DB TestDB;

  TestDB.CheckCarReserve("2");

  ASSERT_EQ(qq.str(), "Available");
}

TEST(DB, reserve_car) {
  DB TestDB;
  qq.str("");

  TestDB.SetCarReserve("3");
  TestDB.CheckCarReserve("3");

  ASSERT_EQ(qq.str(), "Reserved");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}