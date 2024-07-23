#include <gtest/gtest.h>

#include "../s21_containersplus.h"

class S21ContainersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(S21ContainersTest, DefaultConstructor) {
  s21::multiset<int> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
}

TEST_F(S21ContainersTest, InitializeListConstructor) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  int i = 1;

  for (auto n : a) EXPECT_EQ(n, i++);
}

TEST_F(S21ContainersTest, CopyConstructor) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::multiset<int> b(a);

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  int i = 1;

  for (auto n : a) EXPECT_EQ(n, i++);

  i = 1;

  for (auto n : b) EXPECT_EQ(n, i++);
}

TEST_F(S21ContainersTest, MoveConstructor) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::multiset<int> b(std::move(a));

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  int i = 1;

  for (auto n : b) EXPECT_EQ(n, i++);
}

TEST_F(S21ContainersTest, CopyAssignmentOperator) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::multiset<int> b;
  b = a;

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  int i = 1;

  for (auto n : a) EXPECT_EQ(n, i++);

  i = 1;

  for (auto n : b) EXPECT_EQ(n, i++);

  b = b;
}

TEST_F(S21ContainersTest, MoveAssignmentOperator) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  s21::multiset<int> b;
  b = std::move(a);

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  EXPECT_EQ(b.size(), 10);
  EXPECT_FALSE(b.empty());

  int i = 1;
  ;

  for (auto n : b) EXPECT_EQ(n, i++);

  b = std::move(b);
}

TEST_F(S21ContainersTest, Capacity) {
  s21::multiset<int> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  a.insert(1);

  EXPECT_EQ(a.size(), 1);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.max_size(), 461168601842738790);
}

TEST_F(S21ContainersTest, Modifiers) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  a.clear();

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  a.clear();
  /////////////////////////////////////////////////

  auto pair1 = a.insert(5);

  EXPECT_TRUE(pair1 == a.begin());

  pair1 = a.insert(5);

  EXPECT_TRUE(pair1 == ++a.begin());

  pair1 = a.insert(10);

  auto it_ = a.begin();

  it_++;
  it_++;

  EXPECT_TRUE(pair1 == it_);

  pair1 = a.insert(1);

  EXPECT_TRUE(pair1 == a.begin());
  ///////////////////////////////////////////////////

  a.erase(a.begin());

  int i = 0;
  int t[] = {5, 5, 10};

  for (auto n : a) EXPECT_EQ(n, t[i++]);

  s21::multiset<int> b;

  b.erase(b.begin());
  // /////////////////////////////////////////////////

  s21::multiset<int> a_ = {5, 1, 10, 9, 11};

  s21::multiset<int>::iterator it_2 = a_.begin();
  ++it_2;
  ++it_2;
  ++it_2;
  a_.erase(it_2);

  int t_[] = {1, 5, 9, 11};

  i = 0;
  for (auto n : a_) EXPECT_EQ(n, t_[i++]);
  ///////////////////////////////////////////////////

  b.swap(a_);

  EXPECT_EQ(b.size(), 4);
  EXPECT_FALSE(b.empty());

  i = 0;
  for (auto n : b) EXPECT_EQ(n, t_[i++]);

  EXPECT_EQ(a_.size(), 0);
  EXPECT_TRUE(a_.empty());

  b.swap(b);
  ///////////////////////////////////////////////////

  s21::multiset<int> c = {1, 2, 3, 4, 5, 6, 17, 7, 8, 9, 10};
  s21::multiset<int> d = {100, -200, -300, 17};

  d.merge(d);

  d.merge(c);

  EXPECT_EQ(c.size(), 0);
  EXPECT_TRUE(c.empty());

  int t2[] = {-300, -200, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 17, 17, 100};

  i = 0;
  for (auto n : d) EXPECT_EQ(n, t2[i++]);

  d.clear();

  c.merge(d);
  // /////////////////////////////////////////////////

  s21::multiset<int> v;
  v.insert(50);
  v.insert(60);
  v.insert(40);
  v.insert(70);
  v.insert(59);
  v.insert(59);
  v.insert(80);

  int t3[] = {40, 50, 59, 59, 60, 70, 80};

  i = 0;
  for (auto n : v) EXPECT_EQ(n, t3[i++]);

  s21::multiset<int>::iterator v_it = v.begin();
  v_it++;
  v_it++;

  v.erase(v_it);

  int t4[] = {40, 50, 59, 60, 70, 80};

  i = 0;
  for (auto n : v) EXPECT_EQ(n, t4[i++]);
}

TEST_F(S21ContainersTest, SetLookup) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_TRUE(a.contains(7));
  EXPECT_FALSE(a.contains(-7));
  EXPECT_FALSE(a.contains(11));
  /////////////////////////////////////////////////

  s21::multiset<int>::iterator it = a.find(7);
  s21::multiset<int>::iterator it_ = a.begin();

  for (int i = 0; i < 6; ++i) ++it_;

  EXPECT_TRUE(it == it_);

  for (int i = 0; i < 3; ++i) ++it_;

  it = a.find(11);

  EXPECT_TRUE(it == it_);
  ///////////////////////////////////////////////////

  s21::multiset<int> c = {1, 2, 3, 4, 5, 6, 3, 8, 3, 9, 10};

  EXPECT_EQ(c.count(3), 3);

  c.clear();

  EXPECT_EQ(c.count(3), 0);
  ///////////////////////////////////////////////////

  s21::multiset<int> d = {1, 2, 3, 3, 3, 3, 8, 9, 10};

  s21::multiset<int>::iterator lb = d.lower_bound(3);
  s21::multiset<int>::iterator test_it = d.begin();
  ++test_it;
  ++test_it;
  EXPECT_TRUE(lb == test_it);
  ++test_it;
  lb++;
  EXPECT_TRUE(lb == test_it);
  ++test_it;
  lb++;
  EXPECT_TRUE(lb == test_it);
  ++test_it;
  lb++;
  EXPECT_TRUE(lb == test_it);

  s21::multiset<int>::iterator ub = d.upper_bound(3);
  ++test_it;

  EXPECT_TRUE(ub == test_it);

  d.clear();
  d.lower_bound(3);
  d.upper_bound(3);

  s21::multiset<int> d2 = {1, 2, 4, 4, 4, 8, 9, 10};
  lb = d2.lower_bound(3);
  test_it = d2.begin();
  test_it++;
  test_it++;
  EXPECT_TRUE(lb == test_it);
  ///////////////////////////////////////////////////

  s21::multiset<int> h = {1, 2, 3, 5, 5, 5, 5, 5, 9, 10};

  EXPECT_EQ(h.count(5), 5);

  auto p = h.equal_range(5);

  s21::multiset<int>::iterator ith_b = h.begin();
  for (int i = 0; i < 3; ++i) ++ith_b;
  EXPECT_TRUE(ith_b == p.first);

  s21::multiset<int>::iterator ith_e = h.begin();
  for (int i = 0; i < 8; ++i) ++ith_e;

  EXPECT_TRUE(ith_e == p.second);

  h.clear();
  h.equal_range(5);

  h.insert(1);
  h.insert(2);
  h.insert(3);
  auto y = h.equal_range(5);

  EXPECT_TRUE(y.first == h.begin());
  EXPECT_TRUE(y.second == h.begin());
}

TEST_F(S21ContainersTest, Iterators) {
  s21::multiset<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  s21::multiset<int>::iterator it = a.begin();
  s21::multiset<int>::const_iterator cit = it;
  EXPECT_EQ(*cit, 1);

  it++;
  it--;
  EXPECT_TRUE(it == a.begin());

  it++;
  it++;
  it++;
  --it;
  EXPECT_EQ(*it, 3);

  it--;
  EXPECT_EQ(*it, 2);

  /////////////////////////////////////////////////

  s21::multiset<int> e;

  it = e.begin();
  ++it;
  it++;
  --it;
  it--;

  EXPECT_EQ(*it, 0);
  /////////////////////////////////////////////////

  s21::multiset<int> e_1;
  s21::multiset<int> e_2;

  it = e_1.begin();
  s21::multiset<int>::iterator it_ = e_2.begin();

  EXPECT_FALSE(it != it_);

  e_1.insert(10);

  it = e_1.begin();

  EXPECT_FALSE(it != it_);
  /////////////////////////////////////////////////

  s21::multiset<int> j_1;
  s21::multiset<int> j_2;

  it = j_1.begin();
  s21::multiset<int>::iterator it_j = j_2.begin();

  EXPECT_FALSE(it == it_j);

  j_1.insert(10);

  it = j_1.begin();

  EXPECT_FALSE(it == it_j);
}

TEST_F(S21ContainersTest, InsertMany) {
  s21::multiset<int> a = {5, 1, 10};

  a.insert_many();

  auto vec = a.insert_many(1, 2, 10, 4);

  EXPECT_EQ(vec.size(), 4);

  EXPECT_EQ(*vec[0].first == 1 && vec[0].second == 1, true);
  EXPECT_EQ(*vec[1].first == 2 && vec[1].second == 1, true);
  EXPECT_EQ(*vec[2].first == 10 && vec[2].second == 1, true);
  EXPECT_EQ(*vec[3].first == 4 && vec[3].second == 1, true);

  int t[] = {1, 1, 2, 4, 5, 10, 10};

  int i = 0;

  for (auto n : a) EXPECT_EQ(n, t[i++]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}