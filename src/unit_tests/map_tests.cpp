#include <gtest/gtest.h>

#include <algorithm>
#include <map>

#include "../s21_containers.h"

class S21ContainersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(S21ContainersTest, DefaultConstructor) {
  s21::map<int, bool> a;

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
  EXPECT_THROW(a.at(0), std::out_of_range);
}

TEST_F(S21ContainersTest, InitializeListConstructor) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a[1], true);
  EXPECT_EQ(a[2], false);
  EXPECT_EQ(a[3], true);
  EXPECT_EQ(a[4], false);
}

TEST_F(S21ContainersTest, CopyConstructor) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  s21::map<int, bool> b(a);

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(b.size(), 4);
  EXPECT_FALSE(b.empty());

  int t_[] = {1, 2, 3, 4};
  bool t[] = {true, false, true, false};
  int i = 0;

  for (auto n : b) EXPECT_TRUE(n.first == t_[i] && n.second == t[i++]);

  i = 0;

  for (auto n : a) EXPECT_TRUE(n.first == t_[i] && n.second == t[i++]);
}

TEST_F(S21ContainersTest, MoveConstructor) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a.at(1), true);

  s21::map<int, bool> b(std::move(a));

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  EXPECT_EQ(b.size(), 4);
  EXPECT_FALSE(b.empty());
  EXPECT_EQ(b.at(1), true);

  int t_[] = {1, 2, 3, 4};
  bool t[] = {true, false, true, false};
  int i = 0;

  for (auto n : b) EXPECT_TRUE(n.first == t_[i] && n.second == t[i++]);
}

TEST_F(S21ContainersTest, CopyAssignmentOperator) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  s21::map<int, bool> b;
  b = a;

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(b.size(), 4);
  EXPECT_FALSE(b.empty());

  int t_[] = {1, 2, 3, 4};
  bool t[] = {true, false, true, false};
  int i = 0;

  for (auto n : b) EXPECT_TRUE(n.first == t_[i] && n.second == t[i++]);

  i = 0;

  for (auto n : a) EXPECT_TRUE(n.first == t_[i] && n.second == t[i++]);

  b = b;
}

TEST_F(S21ContainersTest, MoveAssignmentOperator) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  s21::map<int, bool> b;
  b = std::move(a);

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  EXPECT_EQ(b.size(), 4);
  EXPECT_FALSE(b.empty());

  int t_[] = {1, 2, 3, 4};
  bool t[] = {true, false, true, false};
  int i = 0;

  for (auto n : b) EXPECT_TRUE(n.first == t_[i] && n.second == t[i++]);

  b = std::move(b);
}

TEST_F(S21ContainersTest, ElementAccess) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  EXPECT_THROW(a.at(0), std::out_of_range);
  EXPECT_EQ(a.at(1), true);
  EXPECT_EQ(a.at(2), false);
  EXPECT_EQ(a.at(3), true);
  EXPECT_EQ(a.at(4), false);
  EXPECT_THROW(a.at(5), std::out_of_range);
  /////////////////////////////////////////////////////

  EXPECT_EQ(a[1], true);
  EXPECT_EQ(a[2], false);
  EXPECT_EQ(a[3], true);
  EXPECT_EQ(a[4], false);
  EXPECT_EQ(a[5] = 0, 0);

  EXPECT_EQ(a.size(), 5);

  EXPECT_EQ(a[8] = 1, 1);

  EXPECT_EQ(a.size(), 6);
}

TEST_F(S21ContainersTest, Capacity) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.max_size(), 461168601842738790);

  a.clear();

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());
}

TEST_F(S21ContainersTest, Modifiers) {
  s21::map<int, int> a = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                          {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

  EXPECT_EQ(a.size(), 10);
  EXPECT_FALSE(a.empty());

  a.clear();

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  a.clear();
  /////////////////////////////////////////////////

  auto pair1 = a.insert({5, 5});

  EXPECT_TRUE(pair1.first == a.begin());
  EXPECT_TRUE(pair1.second);

  pair1 = a.insert({5, 5});

  EXPECT_TRUE(pair1.first == a.begin());
  EXPECT_FALSE(pair1.second);

  pair1 = a.insert({10, 10});

  EXPECT_TRUE(pair1.first == ++a.begin());
  EXPECT_TRUE(pair1.second);

  pair1 = a.insert({1, 1});

  EXPECT_TRUE(pair1.first == a.begin());
  EXPECT_TRUE(pair1.second);
  ///////////////////////////////////////////////////

  a.erase(a.begin());

  int i = 0;
  int t[] = {5, 10};

  for (auto n : a) EXPECT_EQ(n.second, t[i++]);

  s21::map<int, int> b;

  b.erase(b.begin());
  ///////////////////////////////////////////////////

  s21::map<int, int> a_ = {{5, 5}, {1, 1}, {10, 10}, {9, 9}, {11, 11}};

  s21::map<int, int>::iterator it_ = a_.begin();
  ++it_;
  ++it_;
  ++it_;
  a_.erase(it_);

  int t_[] = {1, 5, 9, 11};

  i = 0;
  for (auto n : a_) {
    EXPECT_EQ(n.first, t_[i]);
    EXPECT_EQ(n.second, t_[i++]);
  }
  ///////////////////////////////////////////////////

  b.swap(a);

  EXPECT_EQ(b.size(), 2);
  EXPECT_FALSE(b.empty());

  EXPECT_EQ(a.size(), 0);
  EXPECT_TRUE(a.empty());

  i = 0;
  for (auto n : b) {
    EXPECT_EQ(n.first, t[i]);
    EXPECT_EQ(n.second, t[i++]);
  }

  b.swap(b);
  ///////////////////////////////////////////////////

  s21::map<int, int> c = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                          {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

  s21::map<int, int> d = {
      {100, 100}, {-200, -200}, {-300, -300}, {17, 17}, {1, 1}};

  d.merge(d);

  d.merge(c);

  int t2[] = {-300, -200, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 17, 100};

  i = 0;
  for (auto n : d) {
    EXPECT_EQ(n.first, t2[i]);
    EXPECT_EQ(n.second, t2[i++]);
  }

  d.clear();

  c.merge(d);
  ///////////////////////////////////////////////////

  s21::map<int, int> v;
  v.insert({50, 50});
  v.insert({60, 60});
  v.insert({40, 40});
  v.insert({70, 70});
  v.insert({59, 59});
  v.insert({80, 80});

  int t3[] = {40, 50, 59, 60, 70, 80};

  i = 0;
  for (auto n : v) {
    EXPECT_EQ(n.first, t3[i]);
    EXPECT_EQ(n.second, t3[i++]);
  }

  s21::map<int, int>::iterator v_it = v.begin();
  v_it++;

  v.erase(v_it);

  int t4[] = {40, 59, 60, 70, 80};

  i = 0;
  for (auto n : v) {
    EXPECT_EQ(n.first, t4[i]);
    EXPECT_EQ(n.second, t4[i++]);
  }
}

TEST_F(S21ContainersTest, OthersInsert) {
  s21::map<int, int> a = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  auto it = a.insert(6, 6);

  EXPECT_EQ(it.first->first, 6);
  EXPECT_EQ(it.first->second, 6);
  EXPECT_EQ(it.second, true);
  EXPECT_EQ(a.size(), 6);

  auto it_ = a.begin();

  for (int i = 1; i < 6; i++) it_++;

  EXPECT_EQ(it.first, it_);

  it = a.insert(2, 40);

  EXPECT_EQ(it.first->first, 2);
  EXPECT_EQ(it.first->second, 2);
  EXPECT_EQ(it.second, false);

  EXPECT_EQ(a.size(), 6);
  ///////////////////////////////////////////////////

  auto it2 = a.insert_or_assign(1, 100);

  EXPECT_EQ(it2.second, false);
  EXPECT_EQ(it2.first->first, 1);
  EXPECT_EQ(it2.first->second, 100);
  EXPECT_EQ(a.size(), 6);

  it2 = a.insert_or_assign(10, -10);

  EXPECT_EQ(it2.second, true);
  EXPECT_EQ(it2.first->first, 10);
  EXPECT_EQ(it2.first->second, -10);
  EXPECT_EQ(a.size(), 7);
}

TEST_F(S21ContainersTest, Iterators) {
  s21::map<int, int> a = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                          {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};

  s21::map<int, int>::iterator it = a.begin();
  s21::map<int, int>::const_iterator cit = it;
  EXPECT_EQ((*cit).second, 1);

  it++;
  it--;
  EXPECT_TRUE(it == a.begin());

  it++;
  it++;
  it++;
  --it;
  EXPECT_EQ((*it).second, 3);

  it--;
  EXPECT_EQ((*it).second, 2);

  /////////////////////////////////////////////////

  s21::map<int, int> e;

  it = e.begin();
  ++it;
  it++;
  --it;
  it--;

  EXPECT_EQ((*it).second, 0);
  // /////////////////////////////////////////////////

  s21::map<int, int> e_1;
  s21::map<int, int> e_2;

  it = e_1.begin();
  s21::map<int, int>::iterator it_ = e_2.begin();

  EXPECT_FALSE(it != it_);

  e_1.insert({10, 10});

  it = e_1.begin();

  EXPECT_FALSE(it != it_);
  // /////////////////////////////////////////////////

  s21::map<int, int> j_1;
  s21::map<int, int> j_2;

  it = j_1.begin();
  s21::map<int, int>::iterator it_j = j_2.begin();

  EXPECT_FALSE(it == it_j);

  j_1.insert({10, 10});

  it = j_1.begin();

  EXPECT_FALSE(it == it_j);
}

TEST_F(S21ContainersTest, Lookup) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  EXPECT_EQ(a.size(), 4);
  EXPECT_FALSE(a.empty());

  EXPECT_EQ(a.contains(1), true);
  EXPECT_EQ(a.contains(2), true);
  EXPECT_EQ(a.contains(3), true);
  EXPECT_EQ(a.contains(4), true);
  EXPECT_EQ(a.contains(5), false);

  a.insert({5, true});

  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.contains(5), true);
}

TEST_F(S21ContainersTest, InsertMany) {
  s21::map<int, bool> a = {{1, true}, {2, false}, {3, true}, {4, false}};

  a.insert_many();

  std::pair<int, bool> t1 = {1, false};
  std::pair<int, bool> t2 = {2, true};
  std::pair<int, bool> t3 = {10, false};
  std::pair<int, bool> t4 = {4, true};

  auto vec = a.insert_many(t1, t2, t3, t4);

  EXPECT_EQ(vec.size(), 4);

  EXPECT_EQ((*vec[0].first).first == 1 && vec[0].second == 0, true);
  EXPECT_EQ((*vec[1].first).first == 2 && vec[1].second == 0, true);
  EXPECT_EQ((*vec[2].first).first == 10 && vec[2].second == 1, true);
  EXPECT_EQ((*vec[3].first).first == 4 && vec[3].second == 0, true);

  int t[] = {1, 2, 3, 4, 10};

  int i = 0;

  for (auto n : a) EXPECT_EQ(n.first, t[i++]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}