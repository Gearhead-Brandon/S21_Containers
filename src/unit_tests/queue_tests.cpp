#include <gtest/gtest.h>

#include "../s21_containers.h"

class S21ContainersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(S21ContainersTest, DefaultConstructor) {
  s21::queue<int> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
}

TEST_F(S21ContainersTest, InitializerListConstructor) {
  s21::queue<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(a.front(), i + 1);
    a.pop();
  }
}

TEST_F(S21ContainersTest, CopyConstructor) {
  s21::queue<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::queue<int> b(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(b.front(), i + 1);
    b.pop();
  }

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(a.front(), i + 1);
    a.pop();
  }
}

TEST_F(S21ContainersTest, MoveConstructor) {
  s21::queue<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::queue<int> b(std::move(a));

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(b.front(), i + 1);
    b.pop();
  }
}

TEST_F(S21ContainersTest, CopyAssignmentOperator) {
  s21::queue<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_FALSE(a.empty());

  s21::queue<int> b;

  b = a;

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(b.front(), i + 1);
    b.pop();
  }

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(a.front(), i + 1);
    a.pop();
  }
}

TEST_F(S21ContainersTest, MoveAssignmentOperator) {
  s21::queue<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_FALSE(a.empty());

  s21::queue<int> b;

  b = std::move(a);

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(b.front(), i + 1);
    b.pop();
  }
}

TEST_F(S21ContainersTest, ElementAccess) {
  s21::queue<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 10);
}

TEST_F(S21ContainersTest, Capacity) {
  s21::queue<int> a;

  EXPECT_TRUE(a.empty());

  a.push(1);

  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.size(), 1);

  a.push(2);
  a.push(3);

  EXPECT_EQ(a.size(), 3);
}

TEST_F(S21ContainersTest, Modifiers) {
  s21::queue<int> a;

  EXPECT_TRUE(a.empty());

  a.push(1);

  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.size(), 1);

  a.push(2);
  a.push(3);

  EXPECT_EQ(a.size(), 3);

  a.pop();

  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.front(), 2);
  EXPECT_EQ(a.back(), 3);

  a.pop();

  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.front(), 3);
  EXPECT_EQ(a.back(), 3);

  a.pop();

  EXPECT_EQ(a.size(), 0);
  ///////////////////////////////////////

  s21::queue<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(b.size(), 10);

  s21::queue<int> b_ = {100, 200, 300};

  EXPECT_EQ(b_.size(), 3);

  b.swap(b_);

  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(b_.size(), 10);

  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(b.front(), 100 + 100 * i);
    b.pop();
  }

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(b_.front(), i + 1);
    b_.pop();
  }
}

TEST_F(S21ContainersTest, InsertManyBack) {
  s21::queue<int> a = {1, 3, 4, 5};

  EXPECT_EQ(a.size(), 4);

  a.insert_many_back();

  EXPECT_EQ(a.size(), 4);

  a.insert_many_back(-100, -200, -300);

  int t[7] = {1, 3, 4, 5, -100, -200, -300};

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(a.front(), t[i]);
    a.pop();
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}