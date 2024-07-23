#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 private:
  using byte = char;
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  value_type* arr_;
  size_type size_;
  size_type cap_;

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

    friend class vector<value_type>;

   public:
    base_iterator(const base_iterator& other);
    base_iterator& operator=(const base_iterator& other) = default;

    bool operator!=(const base_iterator<IsConst>& other) const;

    bool operator==(const base_iterator<IsConst>& other) const;

    ref_type operator*() const;
    ptr_type operator->() const;

    base_iterator& operator++();

    base_iterator operator++(int);

    base_iterator& operator--();

    base_iterator operator--(int);

    base_iterator operator+(int n);

    int operator-(const base_iterator<IsConst>& other) const;

    base_iterator operator-(int n) const;

    operator base_iterator<true>() const;
  };

 public:
  using iterator = base_iterator<false>;
  using const_iterator = base_iterator<true>;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  vector();

  vector(size_type n);

  vector(std::initializer_list<value_type> const& items);

  vector(const vector& v);

  vector(vector&& v) noexcept;

  vector& operator=(const vector& v);

  vector& operator=(vector&& v) noexcept;

  ~vector();

  void shrink_to_fit();

  void reserve(size_type newcap);

  void push_back(const_reference value);

  void pop_back() noexcept;

  reference operator[](size_type index) noexcept;
  const_reference operator[](size_type index) const noexcept;

  reference at(size_type index);

  const_reference at(size_type index) const;

  reference front() noexcept;
  const_reference front() const noexcept;

  reference back() noexcept;
  const_reference back() const noexcept;

  size_type size() const noexcept;

  size_type capacity() const noexcept;

  pointer data() const noexcept;

  bool empty() const noexcept;

  void clear();

  size_type max_size() const noexcept;

  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);

  void swap(vector& other) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename Arg, typename... Args>
  iterator insert_many_helper(iterator p, Arg&& arg, Args&&... args);

  iterator insert_many_helper(iterator p);

  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  value_type* newRawArray(size_type newcap);

  void delete_arr(value_type* arr, size_type size);

  void resize_capacity(size_type newcap);
};

}  // namespace s21
#include "vector_imp.tpp"
#include "vector_insert_many_imp.tpp"
#include "vector_iterator_imp.tpp"

#endif