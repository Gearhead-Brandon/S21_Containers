#ifndef STACK_H
#define STACK_H

#include <iostream>

#include "../Deque/s21_deque.h"

namespace s21 {
template <typename T, template <typename> typename Container = s21::deque>
class stack {
 private:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;

  Container<T> Container_;

 public:
  stack();

  stack(std::initializer_list<value_type> const& items);

  stack(const stack& other);

  stack(stack&& other) noexcept;

  ~stack();

  stack& operator=(const stack& other);

  stack& operator=(stack&& other) noexcept;

  void push(const_reference value);

  void pop();

  const_reference top() const noexcept;

  void swap(stack& other) noexcept;

  size_type size() const noexcept;

  bool empty() const noexcept;

  template <typename... Args>
  void insert_many_front(Args&&... args);
};
}  // namespace s21

#include "stack_imp.tpp"
#include "stack_insert_many_imp.tpp"

#endif