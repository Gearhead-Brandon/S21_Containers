#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <limits>

#include "../Set/s21_set.h"

namespace s21 {
template <typename T>
class list {
 private:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  struct BaseNode_ {
    BaseNode_ *prev;
    BaseNode_ *next;

    BaseNode_();
  };

  struct Node_ : BaseNode_ {
    value_type data;

    Node_();

    Node_(const value_type &data);
  };

  BaseNode_ *fakeNode_;
  size_type size_;

  template <bool IsConst>
  class base_iterator {
   public:
    using value_type = T;
    using ptr_type =
        std::conditional_t<IsConst, const BaseNode_ *, BaseNode_ *>;
    using node_type = std::conditional_t<IsConst, const Node_ *, Node_ *>;
    using ref_type =
        std::conditional_t<IsConst, const value_type &, value_type &>;

   private:
    ptr_type ptr;

    base_iterator(BaseNode_ *node);

    friend class list<T>;

   public:
    base_iterator(const base_iterator &other);

    base_iterator &operator=(const base_iterator &other) = default;

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

  list();

  list(size_type n);

  list(std::initializer_list<value_type> const &items);

  list(const list &l);

  list(list &&l) noexcept;

  list &operator=(const list &l);

  list &operator=(list &&l) noexcept;

  ~list();

  void push_back(const T &value);

  void push_front(const T &value);

  void pop_back();

  void pop_front();

  void reverse();

  reference front();

  reference back();

  const_reference front() const;

  const_reference back() const;

  bool empty() const noexcept;

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  void clear() noexcept;

  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);

  void unique();

  void splice(const_iterator pos, list &other);

  void merge(list &other);

  void sort();

  void swap(list &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  void mergeSort();

  template <typename U>
  void swap(U &a, U &b);
};
}  // namespace s21
#include "list_imp.tpp"
#include "list_insert_many_imp.tpp"
#include "list_iterator_imp.tpp"

#endif