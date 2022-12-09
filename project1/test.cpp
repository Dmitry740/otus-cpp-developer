#include <gtest/gtest.h>
#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")

#include "db.h"
#include "headers.h"

TEST(DB, car_check_reserve) {
  DB TestDB;
  extern stringstream qq;
  string a = "1";

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

  ASSERT_EQ(qq.str(), "BMW M3");
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
  string a = "9898989898";

  TestDB.ClientGetLicenese(a);

  ASSERT_EQ(qq.str(), a);
}

TEST(Bot, final_auto) {
  State state;
  int id = 0;
  map<int, State> chat_states = {
      {1, State::Init}, {2, State::MyRent}, {3, State::ChooseCar}};
  for (auto temp : chat_states) {
    id = temp.first;
    state = temp.second;

    switch (state) {
      case State::Init:
        chat_states.insert_or_assign(id, State::MyRent);
        break;
      case State::MyRent:
        chat_states.insert_or_assign(id, State::ChooseCar);
        break;
      case State::ChooseCar:
        chat_states.insert_or_assign(id, State::Init);
        break;
    }
  }

  for (const auto temp : chat_states) {
    if (temp.first == 1) {
      EXPECT_EQ(temp.second, State::MyRent);
    }
  }
  for (const auto temp : chat_states) {
    if (temp.first == 2) {
      EXPECT_EQ(temp.second, State::ChooseCar);
    }
  }
  for (const auto temp : chat_states) {
    if (temp.first == 3) {
      EXPECT_EQ(temp.second, State::Init);
    }
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}