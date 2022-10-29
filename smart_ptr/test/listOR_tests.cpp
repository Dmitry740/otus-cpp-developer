#include <gtest/gtest.h>

#include "list_container_one_root.hpp"

class ListORTest : public ::testing::Test {
 protected:
  ListContainerOR<size_t> list;
  size_t count = 10;
  void SetUp() {
    for (auto i = 0; i < count; ++i) {
      list.push_back(i);
    }
  }

  void TearDown() {}
};

TEST_F(ListORTest, Empty) { ASSERT_FALSE(list.empty()); }

TEST_F(ListORTest, Push_back) {
  ASSERT_EQ(list.size(), count);
  ASSERT_FALSE(list.empty());
}

TEST_F(ListORTest, InsertBegin) {
  list.insert(0, 77);

  ASSERT_EQ(list[0], 77);
  ASSERT_EQ(list.size(), count + 1);
}

TEST_F(ListORTest, InsrtMiddle) {
  list.insert(5, 99);

  ASSERT_EQ(list[5], 99);
  ASSERT_EQ(list.size(), count + 1);
}

TEST_F(ListORTest, EraseEnd) {
  list.erase(9);

  ASSERT_EQ(list.size(), count - 1);
  ASSERT_EQ(list[8], 8);
}

TEST_F(ListORTest, EraseMiddle) {
  list.erase(5);

  ASSERT_EQ(list.size(), count - 1);
  ASSERT_EQ(list[5], 6);
}

TEST_F(ListORTest, EraseBegin) {
  list.erase(0);

  ASSERT_EQ(list.size(), count - 1);
  ASSERT_EQ(list[0], 1);
}

TEST_F(ListORTest, GetElem) {
  for (size_t i = 0; i != list.size(); ++i) {
    ASSERT_EQ(list[i], i);
  }
}

TEST_F(ListORTest, Size) {
  ASSERT_EQ(list.size(), count);
  ASSERT_FALSE(list.empty());
}

TEST_F(ListORTest, ContainersEQ) {
  ListContainerOR<size_t> listcopy;

  listcopy = list;

  ASSERT_EQ(listcopy, list);
  ASSERT_EQ(listcopy.size(), list.size());
}

TEST_F(ListORTest, ContainerDel) {
  for (auto i = 0; i != count; ++i) {
    list.pop_back();
  }

  ASSERT_TRUE(list.empty());
  ASSERT_EQ(list.size(), 0);
}

TEST_F(ListORTest, ContainerMove) {
  ListContainerOR<size_t> movelist;

  movelist = std::move(list);

  ASSERT_NE(movelist, list);
  ASSERT_EQ(movelist.size(), count);
  ASSERT_EQ(list.size(), 0);
  ASSERT_TRUE(list.empty());
}