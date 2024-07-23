#include <gtest/gtest.h>

#include "../s21_containers.h"

class S21ContainersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(S21ContainersTest, DefaultConstructor) {
  s21::list<int> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
}

TEST_F(S21ContainersTest, ParameterizedConstructor) {
  s21::list<int> a(10);

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, i);
}

TEST_F(S21ContainersTest, InitializerListConstructor) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, ++i);
}

TEST_F(S21ContainersTest, CopyConstructor) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::list b(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, ++i);

  i = 0;

  for (auto n : b) EXPECT_EQ(n, ++i);
}

TEST_F(S21ContainersTest, MoveConstructor) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::list b(std::move(a));

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  int i = 0;

  for (auto n : b) EXPECT_EQ(n, ++i);
}

TEST_F(S21ContainersTest, CopyAssignmentOperator) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::list<int> b;

  b = a;

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, ++i);

  i = 0;

  for (auto n : b) EXPECT_EQ(n, ++i);

  b = b;
}

TEST_F(S21ContainersTest, MoveAssignmentOperator) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::list<int> b;

  b = std::move(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  int i = 0;

  for (auto n : b) EXPECT_EQ(n, ++i);

  b = std::move(b);
}

TEST_F(S21ContainersTest, ElementAccess) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 10);

  a.front() = 12;

  EXPECT_EQ(a.front(), 12);
  ///////////////////////////////////////////

  const s21::list<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(b.front(), 1);
  EXPECT_EQ(b.back(), 10);
}

TEST_F(S21ContainersTest, Capacity) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.max_size(), 384307168202282325);

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  a.clear();

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  EXPECT_EQ(a.max_size(), 384307168202282325);
}

TEST_F(S21ContainersTest, Iterators) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::list<int>::iterator it = a.begin();
  s21::list<int>::const_iterator cit = it;
  EXPECT_EQ(*cit, 1);

  it++;
  it--;
  EXPECT_TRUE(it == a.begin());

  it++;
  it++;
  it++;
  --it;
  EXPECT_EQ(*it, 3);
}

TEST_F(S21ContainersTest, Modifiers) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  a.clear();

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  /////////////////////////////////////////////

  s21::list<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  b.insert(b.begin(), 12);
  b.insert(b.end(), 13);

  int t[12] = {12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13};

  int i = 0;

  for (auto n : b) EXPECT_EQ(n, t[i++]);

  s21::list<int>::iterator it = b.begin();

  for (int i = 0; i < 6; ++i) it++;

  b.erase(it);

  int t2[11] = {12, 1, 2, 3, 4, 5, 7, 8, 9, 10, 13};

  i = 0;
  for (auto n : b) EXPECT_EQ(n, t2[i++]);
  ///////////////////////////////////////////////

  s21::list<int> c = {1, 2, 3, 4, 5};
  EXPECT_EQ(c.size(), 5);

  EXPECT_EQ(c.front(), 1);
  EXPECT_EQ(c.back(), 5);

  c.push_back(6);
  c.push_front(0);
  EXPECT_EQ(c.size(), 7);

  EXPECT_EQ(c.front(), 0);
  EXPECT_EQ(c.back(), 6);

  c.pop_back();
  EXPECT_EQ(c.size(), 6);

  EXPECT_EQ(c.front(), 0);
  EXPECT_EQ(c.back(), 5);

  c.pop_front();
  EXPECT_EQ(c.size(), 5);

  EXPECT_EQ(c.front(), 1);
  EXPECT_EQ(c.back(), 5);
  ///////////////////////////////////////////////

  s21::list<int> d = {1, 2, 3, 4, 5};
  s21::list<int> d2 = {6, 7, 8, 9, 10, 11, 12};

  EXPECT_EQ(d.size(), 5);
  EXPECT_EQ(d2.size(), 7);

  d.swap(d2);

  EXPECT_EQ(d.size(), 7);
  EXPECT_EQ(d2.size(), 5);

  i = 6;

  for (auto n : d) EXPECT_EQ(n, i++);

  i = 1;

  for (auto n : d2) EXPECT_EQ(n, i++);

  d.swap(d);
  /////////////////////////////////////////////////////

  s21::list<int> e = {-1, 3, 4, 5, 100};
  s21::list<int> e2 = {-5, 1, 2, 6, 12, 200};

  e.merge(e2);

  int t3[11] = {-5, -1, 1, 2, 3, 4, 5, 6, 12, 100, 200};
  i = 0;

  for (auto n : e) EXPECT_EQ(n, t3[i++]);

  s21::list<int> e_ = {-1, 3, 4, 5, 100};
  s21::list<int> e_2 = {-5, 1, 2, 6, 12};

  e_.merge(e_2);

  int t_3[10] = {-5, -1, 1, 2, 3, 4, 5, 6, 12, 100};
  i = 0;

  for (auto n : e_) EXPECT_EQ(n, t_3[i++]);
  /////////////////////////////////////////////////

  s21::list<int> f = {-1, 3, 4, 5, 100};
  s21::list<int> f2 = {-5, 1, 2, 6, 12, 200};

  f.merge(f);

  f.clear();

  f.merge(f);

  f.merge(f2);

  int t4[6] = {-5, 1, 2, 6, 12, 200};
  i = 0;

  for (auto n : f) EXPECT_EQ(n, t4[i++]);
  ///////////////////////////////////////////////////

  s21::list<int> g = {-1, 3, 4, 5, 100};
  s21::list<int> g2 = {-5, 1, 2, 6, 12, 200};

  g.splice(g.begin(), g2);

  int t5[11] = {-5, 1, 2, 6, 12, 200, -1, 3, 4, 5, 100};

  i = 0;
  for (auto n : g) EXPECT_EQ(n, t5[i++]);

  g.splice(g.end(), g2);

  s21::list<int> g3 = {1000, 2000};

  g.splice(--g.end(), g3);

  int t6[13] = {-5, 1, 2, 6, 12, 200, -1, 3, 4, 5, 1000, 2000, 100};

  i = 0;
  for (auto n : g) EXPECT_EQ(n, t6[i++]);
  /////////////////////////////////////////////////////

  s21::list<int> h = {-1, 3, 4, 5, 100};

  h.reverse();

  int t7[5] = {100, 5, 4, 3, -1};

  i = 0;

  for (auto n : h) EXPECT_EQ(n, t7[i++]);

  h.clear();

  h.reverse();
  ////////////////////////////////////////////////////

  s21::list<int> o = {-1, 3, -1, 4, 1000, 4, 5, 100, 1000, 5};

  o.unique();

  int t8[10] = {-1, 3, 4, 1000, 5, 100, 5};

  i = 0;
  for (auto n : o) EXPECT_EQ(n, t8[i++]);

  o.unique();

  int t9[6] = {-1, 3, 4, 1000, 5, 100};

  i = 0;
  for (auto n : o) EXPECT_EQ(n, t9[i++]);

  o.clear();

  o.unique();
  ////////////////////////////////////////////////////

  s21::list<int> p = {-1, 3, -1, 4, 1000, 4, 5, 100, 1000, 5};

  p.sort();

  int t10[10] = {-1, -1, 3, 4, 4, 5, 5, 100, 1000, 1000};

  i = 0;
  for (auto n : p) EXPECT_EQ(n, t10[i++]);

  p.clear();

  p.sort();
}

TEST_F(S21ContainersTest, InsertMany) {
  s21::list<int> a = {12, 2, 3, 4};

  s21::list<int>::iterator it = a.begin();

  a.insert_many(it);

  it = a.insert_many(it, 5, 6, 7);

  int t[7] = {5, 6, 7, 12, 2, 3, 4};

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, t[i++]);

  a.insert_many(it, 8, 10, 14);

  int t2[10] = {5, 6, 8, 10, 14, 7, 12, 2, 3, 4};

  i = 0;

  for (auto n : a) EXPECT_EQ(n, t2[i++]);

  it = a.end();

  it = a.insert_many(it, 100, 200, 300);

  EXPECT_TRUE(it == --a.end());

  int t3[13] = {5, 6, 8, 10, 14, 7, 12, 2, 3, 4, 100, 200, 300};

  i = 0;

  for (auto n : a) EXPECT_EQ(n, t3[i++]);
}

TEST_F(S21ContainersTest, InsertManyFront) {
  s21::list<int> a = {12, 2, 3, 4};

  a.insert_many_front();

  a.insert_many_front(5, 6, 7, 8, 10, 14);

  int t[10] = {14, 10, 8, 7, 6, 5, 12, 2, 3, 4};

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, t[i++]);
}

TEST_F(S21ContainersTest, InsertManyBack) {
  s21::list<int> a = {12, 2, 3, 4};

  a.insert_many_back();

  a.insert_many_back(5, 6, 7, 8, 10, 14);

  int t[10] = {12, 2, 3, 4, 5, 6, 7, 8, 10, 14};

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, t[i++]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}