#include <gtest/gtest.h>

#include "list_container.hpp"

TEST(ListContainer, Empty) {
  ListContainer<int> list;

  ASSERT_TRUE(list.empty());
}

TEST(ListContainer, Push_back) {
  const size_t count = 10;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  ASSERT_EQ(list.size(), count);
  ASSERT_FALSE(list.empty());
}

TEST(ListContainer, InsertBegin) {
  const size_t count = 10;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  list.insert(0, 77);

  ASSERT_EQ(list[0], 77);
  ASSERT_NE(list.size(), count);
}

TEST(ListContainer, InsrtMedle) {
  const size_t count = 10;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  list.insert(5, 77);

  ASSERT_EQ(list[5], 77);
  ASSERT_NE(list.size(), count);
}

TEST(ListContainer, EraseBegine) {
  const size_t count = 10;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  list.erase(0);

  ASSERT_EQ(list.size(), count - 1);
}

TEST(ListContainer, EraseEnd) {
  const size_t count = 10;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  list.pop_back();

  ASSERT_EQ(list.size(), count - 1);
}

TEST(ListContainer, Erasemedle) {
  const size_t count = 10;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  list.erase(5);

  ASSERT_EQ(list.size(), count - 1);
}

TEST(ListContainer, GetElement) {
  const size_t count = 10;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  ASSERT_EQ(list[5], 5);
  ASSERT_EQ(list[8], 8);
  ASSERT_EQ(list[0], 0);
}

TEST(ListContainer, Size) {
  const size_t count = 17;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  ASSERT_EQ(list.size(), count);
}

TEST(ListContainer, containerEQ) {
  const size_t count = 10;
  ListContainer<size_t> list;
  ListContainer<size_t> listCopy;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }

  listCopy = list;

  ASSERT_EQ(list, listCopy);
}

TEST(ListContainer, containerDel) {
  size_t count = 3;
  ListContainer<size_t> list;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(1);
  }

  for (size_t i = 0; i < count; ++i) {
    list.pop_back();
  }

  EXPECT_TRUE(list.empty());
}

TEST(ListContainer, containerMove) {
  const size_t count = 10;
  ListContainer<size_t> list;
  ListContainer<size_t> listMove;

  for (size_t i = 0; i < count; ++i) {
    list.push_back(i);
  }
  listMove = std::move(list);

  EXPECT_NE(listMove.size(), list.size());
  ASSERT_TRUE(list.empty());
  ASSERT_EQ(listMove.size(), count);
}