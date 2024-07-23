#include <gtest/gtest.h>

#include "../s21_containers.h"

class S21ContainersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(S21ContainersTest, DefaultConstructor) {
  s21::vector<int> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.capacity(), 0);
  EXPECT_TRUE(a.empty());
  EXPECT_THROW(a.at(0), std::out_of_range);
}

TEST_F(S21ContainersTest, ParameterizedConstructor) {
  s21::vector<int> a(10);

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  a.at(0) = 10;
  EXPECT_EQ(a[0], 10);

  for (int i = 1; i < 10; ++i) EXPECT_EQ(a[i], 0);

  EXPECT_THROW(s21::vector<int> a(std::numeric_limits<size_t>::max()),
               std::length_error);
}

TEST_F(S21ContainersTest, InitializerListConstructor) {
  s21::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(a[i], i + 1);
}

TEST_F(S21ContainersTest, CopyConstructor) {
  s21::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::vector<int> b(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], i + 1);
}

TEST_F(S21ContainersTest, MoveConstructor) {
  s21::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::vector<int> b(std::move(a));

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], i + 1);

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  EXPECT_THROW(a.at(0), std::out_of_range);
}

TEST_F(S21ContainersTest, CopyAssignmentOperator) {
  s21::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::vector<int> b;

  b = a;

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], i + 1);

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(a[i], i + 1);
  //////////////////////////////////////////////////

  b = b;

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], i + 1);
  //////////////////////////////////////////////////

  s21::vector<int> c = {1, 2, 3, 4};

  c = b;

  EXPECT_EQ(c.size(), 10);
  EXPECT_FALSE(c.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(c[i], i + 1);
}

TEST_F(S21ContainersTest, MoveAssignmentOperator) {
  s21::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::vector<int> b;

  b = std::move(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], i + 1);

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  //////////////////////////////////////////////////

  b = std::move(b);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(b[i], i + 1);
  //////////////////////////////////////////////////

  s21::vector<int> c = {1, 2, 3, 4};

  c = std::move(b);

  EXPECT_EQ(c.size(), 10);
  EXPECT_FALSE(c.empty());

  for (int i = 0; i < 10; ++i) EXPECT_EQ(c[i], i + 1);
}

TEST_F(S21ContainersTest, at) {
  s21::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

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
}

TEST_F(S21ContainersTest, indexingOperator) {
  s21::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

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
}

TEST_F(S21ContainersTest, front) {
  s21::vector<int> a = {12, 2, 3};
  EXPECT_EQ(a.front(), 12);

  const s21::vector<int> b = {12, 2, 3};
  EXPECT_EQ(b.front(), 12);
}

TEST_F(S21ContainersTest, back) {
  s21::vector<int> a = {12, 2, 3};
  EXPECT_EQ(a.back(), 3);

  a.push_back(4);
  EXPECT_EQ(a.back(), 4);

  const s21::vector<int> b = {12, 2, 3};
  EXPECT_EQ(b.back(), 3);
}

TEST_F(S21ContainersTest, data) {
  s21::vector<int> a = {12, 2, 3};

  int* data = a.data();
  EXPECT_EQ(data[0], 12);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
}

TEST_F(S21ContainersTest, ConstElementAccess) {
  const s21::vector<int> a = {12, 2, 3};

  EXPECT_EQ(a.at(0), 12);
  EXPECT_EQ(a.at(1), 2);
  EXPECT_EQ(a.at(2), 3);
  EXPECT_THROW(a.at(3), std::out_of_range);

  EXPECT_EQ(a[0], 12);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
}

TEST_F(S21ContainersTest, Iterators) {
  s21::vector<int> a = {12, 2, 3, 4};

  EXPECT_EQ(*a.begin(), 12);
  EXPECT_EQ(*(a.end() - 1), 4);

  s21::vector<int>::iterator it = a.begin();
  EXPECT_EQ(*it, 12);
  EXPECT_EQ(*(it + 1), 2);
  EXPECT_EQ(*(it + 2), 3);
  EXPECT_EQ(*(it + 3), 4);

  s21::vector<int>::iterator eit = a.end();
  eit--;
  EXPECT_EQ(*eit, 4);
  EXPECT_EQ(*(eit - 1), 3);
  EXPECT_EQ(*(eit - 2), 2);
  EXPECT_EQ(*(eit - 3), 12);

  for (int i = 0; i < 3; ++i) --eit;

  EXPECT_EQ(*eit, 12);
  ++eit;
  EXPECT_EQ(*eit, 2);

  int arr[4] = {12, 2, 3, 4};
  int i = 0;

  for (int x : a) EXPECT_EQ(x, arr[i++]);
  ////////////////////////////////////////////////////

  const s21::vector<int> c = {12, 2, 3, 4};

  EXPECT_EQ(*c.begin(), 12);

  s21::vector<int>::const_iterator ceit = c.end();
  ceit--;
  EXPECT_EQ(*ceit, 4);

  s21::vector<int>::const_iterator cbit = c.begin();
  cbit++;
  EXPECT_EQ(*cbit, 2);
}

TEST_F(S21ContainersTest, Capacity) {
  s21::vector<int> a;

  EXPECT_FALSE(a.size());
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.capacity(), 0);
  EXPECT_EQ(a.max_size(), 2305843009213693951);

  a.push_back(1);

  EXPECT_EQ(a.size(), 1);
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.capacity(), 1);
  EXPECT_EQ(a.max_size(), 2305843009213693951);

  a.reserve(10);

  EXPECT_EQ(a.capacity(), 10);

  a.push_back(1);

  a.shrink_to_fit();

  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.capacity(), 2);

  a.shrink_to_fit();

  a.reserve(2);
}

TEST_F(S21ContainersTest, Modifiers) {
  s21::vector<int> a = {12, 2, 3, 4};
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.capacity(), 4);

  a.insert(a.begin(), 10);
  a.insert(a.end(), 5);
  a.insert(a.end(), 20);

  EXPECT_TRUE(a.insert(a.begin() - 2, 20) == a.begin());
  EXPECT_THROW(a.insert(a.end() + 10, 20), std::out_of_range);

  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.front(), 10);
  EXPECT_EQ(a.back(), 20);

  a.insert(a.end(), 30);
  a.insert(a.end(), 200);

  s21::vector<int>::iterator it = a.begin();
  it++;

  a.erase(it);

  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.front(), 10);
  EXPECT_EQ(a.back(), 200);

  a.insert(a.begin() + 2, 1000);

  EXPECT_EQ(a.size(), 5);

  a.erase(a.begin() - 2);

  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.front(), 20);
  EXPECT_EQ(a.back(), 200);

  a.erase(a.end() + 1);

  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.front(), 20);
  EXPECT_EQ(a.back(), 30);
  //////////////////////////////////////

  s21::vector<int> b = {12, 2, 3, 4};

  b.push_back(10);

  EXPECT_EQ(b.size(), 5);
  EXPECT_EQ(b[4], 10);

  b.pop_back();

  EXPECT_EQ(b.size(), 4);
  EXPECT_EQ(b[3], 4);

  b.clear();

  EXPECT_EQ(b.size(), 0);
  b.pop_back();
}

TEST_F(S21ContainersTest, Swap) {
  s21::vector<int> a = {12, 2, 3, 4};
  s21::vector<int> b = {5, 6, 7, 8, 10, 14};

  a.swap(b);

  EXPECT_EQ(a.size(), 6);
  EXPECT_EQ(b.size(), 4);

  int a_[6] = {5, 6, 7, 8, 10, 14};
  int b_[4] = {12, 2, 3, 4};

  int i = 0;
  for (int t : a) EXPECT_EQ(t, a_[i++]);

  i = 0;

  for (int t : b) EXPECT_EQ(t, b_[i++]);

  a.swap(a);
  EXPECT_EQ(a.size(), 6);
}

TEST_F(S21ContainersTest, InsertMany) {
  s21::vector<int> a = {12, 2, 3, 4};

  s21::vector<int>::iterator it = a.begin();

  it = a.insert_many(it);

  EXPECT_EQ(it, a.begin());

  it = a.insert_many(it, 5, 10, 120, 1000);

  EXPECT_EQ(a[0], 5);
  EXPECT_EQ(a[1], 10);
  EXPECT_EQ(a[2], 120);
  EXPECT_EQ(a[3], 1000);

  EXPECT_EQ(it, a.begin());

  it = a.insert_many(a.end(), -5, -10, -12);

  EXPECT_EQ(a[8], -5);
  EXPECT_EQ(a[9], -10);
  EXPECT_EQ(a[10], -12);

  EXPECT_EQ(a.size(), 11);
  EXPECT_EQ(it, a.end() - 3);

  int arr[11] = {
      5, 10, 120, 1000, 12, 2, 3, 4, -5, -10, -12,
  };

  int i = 0;
  for (auto n : a) EXPECT_EQ(n, arr[i++]);
}

TEST_F(S21ContainersTest, InsertManyBack) {
  s21::vector<int> a = {12, 2, 3, 4};

  a.insert_many_back();

  EXPECT_EQ(a.size(), 4);

  int y = 5, x = 100;
  int& yr = y;

  a.insert_many_back(5, 10, 12, x, yr);

  EXPECT_EQ(a.size(), 9);

  EXPECT_EQ(a[4], 5);
  EXPECT_EQ(a[5], 10);
  EXPECT_EQ(a[6], 12);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}