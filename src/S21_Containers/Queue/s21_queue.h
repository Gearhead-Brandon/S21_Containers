#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

#include "../Deque/s21_deque.h"

namespace s21 {
template <typename T, template <typename> typename Container = s21::deque>
class queue {
 private:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;

  Container<T> Container_;

 public:
  queue();

  queue(std::initializer_list<value_type> const& items);

  queue(const queue& other);

  queue(queue&& other) noexcept;

  ~queue();

  queue& operator=(const queue& other);

  queue& operator=(queue&& other) noexcept;

  void push(const_reference value);

  void pop();

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  void swap(queue& other) noexcept;

  size_type size() const noexcept;
  bool empty() const noexcept;

  template <typename... Args>
  void insert_many_back(Args&&... args);
};
}  // namespace s21
#include "queue_imp.tpp"
#include "queue_insert_many_imp.tpp"

#endif