#include <gtest/gtest.h>

#include "../s21_containersplus.h"

class S21ContainersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(S21ContainersTest, DefaultConstructor) {
  s21::array<int, 10> a;

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::array<int, 0> b;

  EXPECT_EQ(b.size(), 0);
  EXPECT_TRUE(b.empty());
}

TEST_F(S21ContainersTest, InitializerListConstructor) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(a[i], i + 1);
  ////////////////////////////////////////

  s21::array<int, 10> b = {1, 2, 3, 4};

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 4; ++i) EXPECT_EQ(b[i], i + 1);

  for (int i = 4; i < 10; ++i) EXPECT_EQ(b[i], 0);
  ///////////////////////////////////////////

  s21::array<int, 5> c = {1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ(c.size(), 5);
  EXPECT_FALSE(c.empty());

  for (int i = 0; i < 5; ++i) EXPECT_EQ(c[i], i + 1);
  /////////////////////////////////////////

  s21::array<int, 0> d = {1, 2, 3, 4};

  EXPECT_EQ(d.size(), 0);
  EXPECT_TRUE(d.empty());
}

TEST_F(S21ContainersTest, CopyConstructor) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::array<int, 10> b(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], a[i]);
}

TEST_F(S21ContainersTest, MoveConstructor) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::array<int, 10> b(std::move(a));

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], a[i]);
}

TEST_F(S21ContainersTest, CopyAssignmentOperator) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::array<int, 10> b;

  b = a;

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], a[i]);

  b = b;
}

TEST_F(S21ContainersTest, MoveAssignmentOperator) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::array<int, 10> b;

  b = std::move(a);

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], a[i]);

  b = std::move(b);
}

TEST_F(S21ContainersTest, ElementAccess) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a[3], 4);
  EXPECT_EQ(a[4], 5);
  EXPECT_EQ(a[5], 6);
  EXPECT_EQ(a[6], 7);
  EXPECT_EQ(a[7], 8);
  EXPECT_EQ(a[8], 9);
  EXPECT_EQ(a[9], 10);

  EXPECT_EQ(a.at(0), 1);
  EXPECT_EQ(a.at(1), 2);
  EXPECT_EQ(a.at(2), 3);
  EXPECT_EQ(a.at(3), 4);
  EXPECT_EQ(a.at(4), 5);
  EXPECT_EQ(a.at(5), 6);
  EXPECT_EQ(a.at(6), 7);
  EXPECT_EQ(a.at(7), 8);
  EXPECT_EQ(a.at(8), 9);
  EXPECT_EQ(a.at(9), 10);

  EXPECT_THROW(a.at(10), std::out_of_range);

  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 10);

  auto it = a.data();

  EXPECT_EQ(*it, 1);
  it++;
  EXPECT_EQ(*it, 2);
  it++;
  EXPECT_EQ(*it, 3);
  it++;
  EXPECT_EQ(*it, 4);
  it++;
  EXPECT_EQ(*it, 5);
  it++;
  EXPECT_EQ(*it, 6);
  it++;
  EXPECT_EQ(*it, 7);
  it++;
  EXPECT_EQ(*it, 8);
  it++;
  EXPECT_EQ(*it, 9);
  it++;
  EXPECT_EQ(*it, 10);
}

TEST_F(S21ContainersTest, Capacity) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.max_size(), 10);

  s21::array<int, 5> b = {1, 2, 3, 4, 5};

  EXPECT_EQ(b.size(), 5);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(b.max_size(), 5);
}

TEST_F(S21ContainersTest, Modifiers) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  a.fill(8);

  for (int i = 0; i < 10; ++i) EXPECT_EQ(a[i], 8);

  s21::array<int, 10> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  b.fill(20);

  a.swap(b);

  for (int i = 0; i < 10; ++i) EXPECT_EQ(a[i], 20);

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], 8);
}

TEST_F(S21ContainersTest, Iterators) {
  s21::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(*a.begin(), 1);
  EXPECT_EQ(*(--a.end()), 10);

  s21::array<int, 10>::iterator ita = a.begin();
  s21::array<int, 10>::const_iterator cita = ita;

  EXPECT_EQ(*cita, 1);
  //////////////////////////////////////

  const s21::array<int, 10> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(*b.begin(), 1);
  EXPECT_EQ(*(--b.end()), 10);

  //////////////////////////////////////

  s21::array<int, 10> c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(c.size(), 10);
  EXPECT_FALSE(c.empty());

  s21::array<int, 10>::iterator it = c.begin();

  EXPECT_EQ(it == c.begin(), 1);

  EXPECT_EQ(*it, 1);
  it++;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  it--;
  EXPECT_EQ(*it, 2);

  size_t i = 1;
  for (auto n : c) EXPECT_EQ(n, i++);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}