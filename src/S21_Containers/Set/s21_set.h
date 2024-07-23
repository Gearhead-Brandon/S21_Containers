#ifndef SET_H
#define SET_H

#include <iostream>
#include <limits>

#include "../Vector/s21_vector.h"

template <typename W>
class ComparatorSet {
 public:
  bool operator()(const W& a, const W& b) const;
};

namespace s21 {
template <typename T, template <typename> typename Compare = ComparatorSet>
class set {
 private:
  using value_type = T;
  using key_type = T;
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

    Node_(const value_type& key);
  };

  BaseNode_* fakeNode_;
  size_type size_;
  Compare<T> comp_;

  template <bool IsConst>
  class base_iterator {
   public:
    using value_type = T;
    using ptr_type = std::conditional_t<IsConst, const BaseNode_*, BaseNode_*>;
    using node_type = std::conditional_t<IsConst, const Node_*, Node_*>;
    using ref_type =
        std::conditional_t<IsConst, const value_type&, value_type&>;

   private:
    ptr_type node_ptr;
    value_type stub;

    base_iterator(BaseNode_* node);

    friend class set<T>;

   public:
    base_iterator(const base_iterator& other);

    base_iterator& operator=(const base_iterator& other);

    bool operator!=(const base_iterator<IsConst>& other) const;

    bool operator==(const base_iterator<IsConst>& other) const;

    ref_type operator*() const;

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
  
  set();

  set(std::initializer_list<value_type> const& list);

  set(const set& other);

  set(set&& other) noexcept;

  ~set();

  set& operator=(const set& other);

  set& operator=(set&& other) noexcept;

  std::pair<iterator, bool> insert(const value_type& value);

  iterator find(const value_type& key) const;

  bool contains(const value_type& key) const;

  void erase(iterator pos);

  bool empty() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  void swap(set& other) noexcept;

  void clear() noexcept;

  void merge(set& other);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  void mergeBypass(BaseNode_* node);

  void leafNodeTransfer(BaseNode_* node);

  void clearTreeRecursive(BaseNode_* node);

  std::pair<iterator, bool> insertNode(Node_* newNode);

  BaseNode_* findMinNode(BaseNode_* node);

  BaseNode_* detachMinNode(BaseNode_* node);

  BaseNode_* deleteNodeRecursive(Node_* node, const value_type& key);

  bool comparator(const value_type& a, const value_type& b, BaseNode_*& current,
                  Node_* newNode);

  bool comparator(const value_type& a, const value_type& b,
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
#include "set_imp.tpp"
#include "set_insert_many_imp.tpp"
#include "set_iterator_imp.tpp"

#endif