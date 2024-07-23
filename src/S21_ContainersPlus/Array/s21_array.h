#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <set>
#include <vector>

namespace s21 {
template <typename T, size_t N>
class array {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  value_type arr_[N];

  template <bool IsConst>
  class base_iterator {
   public:
    using value_type = T;
    using ptr_type =
        std::conditional_t<IsConst, const value_type*, value_type*>;
    using ref_type =
        std::conditional_t<IsConst, const value_type&, value_type&>;

   private:
    ptr_type ptr;

    base_iterator(value_type* p);

    friend class array<T, N>;

   public:
    base_iterator(const base_iterator& other);

    base_iterator& operator=(const base_iterator& other) = default;

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

  array();

  array(const std::initializer_list<value_type>& items);

  array(const array& other);

  array(array&& other) noexcept;

  array& operator=(const array& other);

  array& operator=(array&& other) noexcept;

  ~array();

  reference at(size_type pos);

  reference operator[](size_type pos);

  const_reference front();

  const_reference back() const;

  size_type size() const;

  bool empty() const;

  size_type max_size() const;

  iterator data();

  void swap(array& other) noexcept;

  void fill(const value_type& value);
};
}  // namespace s21
#include "array_imp.tpp"
#include "array_iterator_imp.tpp"

#endif