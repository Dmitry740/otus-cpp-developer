#include <gtest/gtest.h>

#include "successive_container.hpp"

class SucsTest : public ::testing::Test {
 protected:
  SuccessiveContainer<size_t> vect;
  size_t count = 10;
  void SetUp() {
    for (auto i = 0; i < count; ++i) {
      vect.push_back(i);
    }
  }

  void TearDown() {}
};

TEST_F(SucsTest, Empty) { ASSERT_FALSE(vect.empty()); }

TEST_F(SucsTest, Push_back) {
  ASSERT_EQ(vect.size(), count);
  ASSERT_FALSE(vect.empty());
}

TEST_F(SucsTest, InsertBegin) {
  vect.insert(0, 99);

  ASSERT_EQ(vect[0], 99);
  ASSERT_EQ(vect.size(), count + 1);
}

TEST_F(SucsTest, InsertMeddle) {
  vect.insert(5, 77);

  ASSERT_EQ(vect[5], 77);
  ASSERT_EQ(vect.size(), count + 1);
}

TEST_F(SucsTest, EraseEnd) {
  vect.erase(9);

  ASSERT_EQ(vect.size(), count - 1);
  ASSERT_EQ(vect[8], 8);
}

TEST_F(SucsTest, EraseMeddle) {
  vect.erase(5);

  ASSERT_EQ(vect.size(), count - 1);
  ASSERT_EQ(vect[5], 6);
}

TEST_F(SucsTest, EraseBegin) {
  vect.erase(0);

  ASSERT_EQ(vect[0], 1);
  ASSERT_EQ(vect.size(), count - 1);
}

TEST_F(SucsTest, GetElem) {
  vect[5];

  ASSERT_EQ(vect[5], 5);
}

TEST_F(SucsTest, Size) {
  ASSERT_EQ(vect.size(), count);
  ASSERT_FALSE(vect.empty());
}

TEST_F(SucsTest, ContainerDel) {
  for (auto i = 0; i < count; ++i) {
    vect.pop_back();
  }

  ASSERT_TRUE(vect.empty());
}

TEST_F(SucsTest, ContainerEQ) {
  SuccessiveContainer<size_t> vectcopy;

  vectcopy = vect;

  ASSERT_EQ(vectcopy, vect);
  ASSERT_EQ(vectcopy.size(), vect.size());
}

TEST_F(SucsTest, ContainerMove) {
  SuccessiveContainer<size_t> vectmove;

  vectmove = std::move(vect);

  ASSERT_NE(vectmove, vect);
  ASSERT_EQ(vectmove.size(), count);
  ASSERT_EQ(vect.size(), 0);
  ASSERT_TRUE(vect.empty());
}

TEST_F(SucsTest, Iterator) {
  vect[5] = 555;

  ASSERT_EQ(vect[5], 555);
}