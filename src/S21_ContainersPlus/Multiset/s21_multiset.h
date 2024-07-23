#ifndef MULTISET_H
#define MULTISET_H

#include <iostream>
#include <limits>

#include "../../S21_Containers/Vector/s21_vector.h"

template <typename W>
class Comparator {
 public:
  bool operator()(const W &a, const W &b) const;
};

namespace s21 {
template <typename Key, template <typename> typename Compare = Comparator>
class multiset {
 private:
  using key_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using size_type = std::size_t;

  struct BaseNode_ {
    BaseNode_ *left;
    BaseNode_ *right;
    BaseNode_ *parent;

    BaseNode_();
  };

  struct Node_ : BaseNode_ {
    key_type key;
    size_type height;

    Node_();

    Node_(const key_type &key);
  };

  BaseNode_ *fakeNode_;
  size_type size_;
  Compare<Key> comp_;

  template <bool IsConst>
  class base_iterator {
   public:
    using value_type = Key;
    using ptr_type =
        std::conditional_t<IsConst, const BaseNode_ *, BaseNode_ *>;
    using node_type = std::conditional_t<IsConst, const Node_ *, Node_ *>;
    using ref_type = std::conditional_t<IsConst, const key_type &, key_type &>;

   private:
    ptr_type ptr;
    key_type stub;

    base_iterator();

    base_iterator(BaseNode_ *node);

    friend class multiset<Key>;

   public:
    base_iterator(const base_iterator &other);

    base_iterator &operator=(const base_iterator &other);

    bool operator!=(const base_iterator<IsConst> &other) const;

    bool operator==(const base_iterator<IsConst> &other) const;

    ref_type operator*() const;

    base_iterator &operator++();

    base_iterator operator++(int);

    base_iterator &operator--();

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

  /////////////////////////////////////////////////////////////////////////////////

  multiset();

  multiset(std::initializer_list<key_type> const &list);

  multiset(const multiset &other);

  multiset(multiset &&other) noexcept;

  ~multiset();

  multiset &operator=(const multiset &other);

  multiset &operator=(multiset &&other) noexcept;

  iterator insert(const key_type &value);

  void erase(iterator pos);

  bool empty() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  void swap(multiset &other) noexcept;

  void clear() noexcept;

  void merge(multiset &other);

  size_type count(const key_type &key) const;

  bool contains(const key_type &key) const;

  iterator find(const key_type &key) const;

  std::pair<iterator, iterator> equal_range(const key_type &key);

  iterator lower_bound(const key_type &key);

  iterator upper_bound(const key_type &key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  void mergeBypass(BaseNode_ *node);

  void leafNodeTransfer(BaseNode_ *node);

  void clearTreeRecursive(BaseNode_ *node);

  iterator insertNode(Node_ *newNode);

  BaseNode_ *findMinNode(BaseNode_ *node);

  BaseNode_ *detachMinNode(BaseNode_ *node);

  BaseNode_ *deleteNodeRecursive(Node_ *node, const key_type &key);

  void insertionComparator(const key_type &a, const key_type &b,
                           BaseNode_ *&current);

  bool comparator(const key_type &a, const key_type &b,
                  BaseNode_ *&current) const;

  BaseNode_ *rotateRight(BaseNode_ *node);

  BaseNode_ *rotateLeft(BaseNode_ *node);

  BaseNode_ *Balance(BaseNode_ *node);

  size_type height(BaseNode_ *node);

  void FixHeight(BaseNode_ *node);

  void heightAdjustment(BaseNode_ *node);

  int BalanceFactor(BaseNode_ *node);

  Node_ *getBegin() const;

  Node_ *getEnd() const;

  Node_ *getRoot() const;
};
}  // namespace s21

#include "multiset_imp.tpp"
#include "multiset_insert_many_imp.tpp"
#include "multiset_iterator_imp.tpp"

#endif