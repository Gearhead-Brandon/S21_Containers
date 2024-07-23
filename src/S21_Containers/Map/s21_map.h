#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <limits>

#include "../Vector/s21_vector.h"

template <typename W>
class ComparatorMap {
 public:
  bool operator()(const W& a, const W& b) const;
};

namespace s21 {
template <typename Key, typename T,
          template <typename> typename Compare = ComparatorMap>
class map {
 private:
  using key_type = const Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  struct BaseNode_ {
    BaseNode_* left;
    BaseNode_* right;
    BaseNode_* parent;

    BaseNode_();
  };

  struct Node_ : BaseNode_ {
    value_type key;
    size_type height;

    Node_();

    Node_(const value_type& value);

    Node_(const key_type& key, const mapped_type& mapped);
  };

  BaseNode_* fakeNode_;
  size_type size_;
  Compare<Key> comp_;

  template <bool IsConst>
  class base_iterator {
   public:
    using value_type = std::pair<const Key, T>;
    using ptr_type = BaseNode_*;
    using node_type = Node_*;
    using ref_type =
        std::conditional_t<IsConst, const value_type&, value_type&>;

   private:
    ptr_type ptr;
    value_type stub;

    base_iterator(BaseNode_* node);

    friend class map<Key, T>;

   public:
    base_iterator(const base_iterator& other);

    base_iterator& operator=(const base_iterator& other);

    bool operator!=(const base_iterator<IsConst>& other) const;

    bool operator==(const base_iterator<IsConst>& other) const;

    ref_type operator*() const;

    value_type* operator->() const;

    base_iterator& operator++();

    base_iterator operator++(int);

    base_iterator& operator--();

    base_iterator operator--(int);

    operator base_iterator<true>() const;
  };

 public:
  using iterator = base_iterator<false>;
  using const_iterator = base_iterator<true>;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  map();

  map(std::initializer_list<value_type> const& list);

  map(const map& other);

  map(map&& other) noexcept;

  ~map();

  map& operator=(const map& other);

  map& operator=(map&& other) noexcept;

  std::pair<iterator, bool> insert(const value_type& value);

  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);

  bool contains(const key_type& value) const;

  void erase(iterator pos);

  bool empty() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  void swap(map& other) noexcept;

  void clear() noexcept;

  void merge(map& other);

  reference at(const key_type& key);

  reference operator[](const key_type& key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  void mergeBypass(BaseNode_* node);

  void leafNodeTransfer(BaseNode_* node);

  void clearTreeRecursive(BaseNode_* node);

  iterator find(const key_type& key) const;

  std::pair<iterator, bool> insertNode(Node_* newNode);

  BaseNode_* findMinNode(BaseNode_* node);

  BaseNode_* detachMinNode(BaseNode_* node);

  BaseNode_* deleteNodeRecursive(Node_* node, const value_type& key);

  bool comparator(const key_type& a, const key_type& b, BaseNode_*& current,
                  Node_* newNode);

  bool comparator(const key_type& a, const key_type& b,
                  BaseNode_*& current) const;

  BaseNode_* rotateRight(BaseNode_* node);

  BaseNode_* rotateLeft(BaseNode_* node);

  BaseNode_* Balance(BaseNode_* node);

  size_type height(BaseNode_* node);

  void FixHeight(BaseNode_* node);

  void heightAdjustment(BaseNode_* node);

  int BalanceFactor(BaseNode_* node);

  Node_* getBegin() const;

  Node_* getRoot() const;
};
}  // namespace s21

#include "map_imp.tpp"
#include "map_insert_many_imp.tpp"
#include "map_iterator_imp.tpp"

#endif