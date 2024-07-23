#ifndef DEQUE_H
#define DEQUE_H

#include <deque>
#include <iostream>

namespace s21 {
enum class direction : bool {
  Up = true,
  Down = false,
};

enum class bucket : int { size = 32 };

template <typename T>
class deque {
 private:
  using byte = char;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Point {
    long long int y;  // row
    long long int x;  // column

    Point();

    Point(const Point& other);

    Point(int num);

    Point& operator=(Point& other);
  };

  value_type** matrix_;
  size_type rows_;
  size_type cols_;

  size_type size_;

  Point first_elem_;
  Point last_elem_;

  template <bool IsConst>
  class base_iterator {
   public:
    using value_type = T;
    using ptr_type =
        std::conditional_t<IsConst, const value_type**, value_type**>;
    using ref_type =
        std::conditional_t<IsConst, const value_type&, value_type&>;

   private:
    ptr_type ptr;
    Point current;

    base_iterator(value_type** p, Point point);

    friend class deque<value_type>;

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

  deque();

  deque(std::initializer_list<value_type> const& items);

  deque(const deque& other);

  deque(deque&& other) noexcept;

  deque& operator=(const deque& other);

  deque& operator=(deque&& other) noexcept;

  ~deque();

  void push_back(const value_type& value);

  void pop_back();

  void push_front(const value_type& value);

  void pop_front();

  size_type size() const noexcept;
  bool empty() const noexcept;

  void swap(deque& other);

  reference operator[](size_type index);

  const_reference front() const;
  const_reference back() const;

 private:
  void remove();

  template <typename U>
  void swap(U& a, U& b);

  void reserve();

  void isMatrixNull();

  void isRowNull(int index);

  void matrixExpansionInDirection(const bool direction);

  void new_primary_matrix();

  value_type** newArrayOfPointers();

  value_type* newRawRow();
};
}  // namespace s21
#include "deque_imp.tpp"
#include "deque_iterator_imp.tpp"

#endif