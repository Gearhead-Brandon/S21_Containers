#include <gtest/gtest.h>

#include "../s21_containers.h"

class S21ContainersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// TEST_F(S21ContainersTest, DefaultConstructor) {
//     s21::stack<int> a;

//     EXPECT_EQ(a.size(), 0);
//     EXPECT_TRUE(a.empty());
// }

// TEST_F(S21ContainersTest, InitializerListConstructor) {
//     s21::stack<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//     EXPECT_EQ(a.size(), 10);
//     EXPECT_FALSE(a.empty());

//     for(int i = 0; i < 10; ++i) {
//         EXPECT_EQ(a.top(), i + 1);
//         a.pop();
//     }
// }

// TEST_F(S21ContainersTest, CopyConstructor) {
//     s21::stack<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     EXPECT_EQ(a.size(), 10);
//     EXPECT_FALSE(a.empty());

//     s21::stack<int> b(a);
//     EXPECT_EQ(b.size(), 10);
//     EXPECT_FALSE(b.empty());

//     for(int i = 0; i < 10; ++i) {
//         EXPECT_EQ(b.top(), i + 1);
//         b.pop();
//     }
// }

// TEST_F(S21ContainersTest, MoveConstructor) {
//     s21::stack<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     EXPECT_EQ(a.size(), 10);
//     EXPECT_FALSE(a.empty());

//     s21::stack<int> b(std::move(a));
//     EXPECT_EQ(b.size(), 10);
//     EXPECT_FALSE(b.empty());

//     EXPECT_EQ(a.size(), 0);
//     EXPECT_TRUE(a.empty());

//     for(int i = 0; i < 10; ++i) {
//         EXPECT_EQ(b.top(), i + 1);
//         b.pop();
//     }
// }

// TEST_F(S21ContainersTest, CopyAssignmentOperator) {
//     s21::stack<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     EXPECT_EQ(a.size(), 10);
//     EXPECT_FALSE(a.empty());

//     s21::stack<int> b;
//     b = a;

//     EXPECT_EQ(b.size(), 10);
//     EXPECT_FALSE(b.empty());

//     EXPECT_EQ(a.size(), 10);
//     EXPECT_FALSE(a.empty());

//     for(int i = 0; i < 10; ++i) {
//         EXPECT_EQ(a.top(), i + 1);
//         a.pop();
//     }

//     b = b;

//     for(int i = 0; i < 10; ++i) {
//         EXPECT_EQ(b.top(), i + 1);
//         b.pop();
//     }
// ///////////////////////////////////////////

//     s21::stack<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//     s21::stack<int> c_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

//     c_ = c;

//     EXPECT_EQ(c_.size(), 10);
//     EXPECT_FALSE(c_.empty());

//     EXPECT_EQ(c.size(), 10);
//     EXPECT_FALSE(c.empty());

//     for(int i = 0; i < 10; ++i) {
//         EXPECT_EQ(c.top(), i + 1);
//         c.pop();
//     }

//     for(int i = 0; i < 10; ++i) {
//         EXPECT_EQ(c_.top(), i + 1);
//         c_.pop();
//     }
// }

TEST_F(S21ContainersTest, MoveAssignmentOperator) {
  s21::stack<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::stack<int> b;
  b = std::move(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  b = std::move(b);

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(b.top(), i + 1);
    b.pop();
  }
  ////////////////////////////////////////////////

  s21::stack<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::stack<int> c_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  c_ = std::move(c);

  // EXPECT_EQ(c_.size(), 10);
  // EXPECT_FALSE(c_.empty());

  // EXPECT_EQ(c.size(), 0);
  // EXPECT_TRUE(c.empty());

  // for(int i = 0; i < 10; ++i) {
  //     EXPECT_EQ(c_.top(), i + 1);
  //     c_.pop();
  // }
}

TEST_F(S21ContainersTest, ElementAccess) {
  s21::stack<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.top(), 1);
  a.pop();
  EXPECT_EQ(a.top(), 2);
  a.pop();
  EXPECT_EQ(a.top(), 3);
  a.pop();
  EXPECT_EQ(a.top(), 4);
  a.pop();
  EXPECT_EQ(a.top(), 5);
  a.pop();
  EXPECT_EQ(a.top(), 6);
  a.pop();
  EXPECT_EQ(a.top(), 7);
  a.pop();
  EXPECT_EQ(a.top(), 8);
  a.pop();
  EXPECT_EQ(a.top(), 9);
  a.pop();
  EXPECT_EQ(a.top(), 10);
  a.pop();
}

TEST_F(S21ContainersTest, Capacity) {
  s21::stack<int> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  a.push(1);
  a.push(2);
  a.push(3);

  EXPECT_EQ(a.size(), 3);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.top(), 3);
}

TEST_F(S21ContainersTest, Modifiers) {
  s21::stack<int> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  a.push(1);
  a.push(2);
  a.push(3);

  EXPECT_EQ(a.size(), 3);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.top(), 3);

  a.pop();

  EXPECT_EQ(a.size(), 2);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.top(), 2);

  for (int i = 0; i < 64; ++i) {
    a.push(i);
  }

  a.pop();

  EXPECT_EQ(a.size(), 65);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.top(), 62);
  ///////////////////////////////////////

  s21::stack<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::stack<int> b_ = {5, 4, 3, 2, 1};

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(b_.size(), 5);
  EXPECT_FALSE(b_.empty());

  b.swap(b_);

  EXPECT_EQ(b.size(), 5);
  EXPECT_EQ(b_.size(), 10);

  for (int i = 5; i > 0; --i) {
    EXPECT_EQ(b.top(), i);
    b.pop();
  }

  b.swap(b);

  for (int i = 1; i < 11; ++i) {
    EXPECT_EQ(b_.top(), i);
    b_.pop();
  }
}

TEST_F(S21ContainersTest, InsertManyFront) {
  s21::stack<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  a.insert_many_front();

  a.insert_many_front(11, 12, 45, 67);

  int temp[] = {67, 45, 12, 11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0, s = a.size(); i < s; ++i) {
    EXPECT_EQ(a.top(), temp[i]);
    a.pop();
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}