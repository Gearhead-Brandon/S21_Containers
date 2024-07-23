#include "s21_deque.h"

namespace s21 {
template <typename T>
template <bool IsConst>
deque<T>::base_iterator<IsConst>::base_iterator(value_type** p, Point point)
    : ptr(const_cast<ptr_type>(p)), current(point) {}

template <typename T>
template <bool IsConst>
deque<T>::base_iterator<IsConst>::base_iterator(const base_iterator& other)
    : ptr(other.ptr), current(other.current) {}

template <typename T>
template <bool IsConst>
bool deque<T>::base_iterator<IsConst>::operator!=(
    const base_iterator<IsConst>& other) const {
  return (current.y != other.current.y) || (current.x != other.current.x);
}

template <typename T>
template <bool IsConst>
bool deque<T>::base_iterator<IsConst>::operator==(
    const base_iterator<IsConst>& other) const {
  return (current.y == other.current.y) && (current.x == other.current.x);
}

template <typename T>
template <bool IsConst>
typename deque<T>::base_iterator<IsConst>::ref_type
deque<T>::base_iterator<IsConst>::operator*() const {
  return ptr[current.y][current.x];
}

template <typename T>
template <bool IsConst>
deque<T>::base_iterator<IsConst>&
deque<T>::base_iterator<IsConst>::operator++() {
  if (current.x == static_cast<int>(bucket::size) - 1) {
    current.y++;
    current.x = 0;
  } else
    current.x++;

  return *this;
}

template <typename T>
template <bool IsConst>
deque<T>::base_iterator<IsConst> deque<T>::base_iterator<IsConst>::operator++(
    int) {
  base_iterator copy = *this;

  if (current.x == static_cast<int>(bucket::size) - 1) {
    current.y++;
    current.x = 0;
  } else
    current.x++;

  return copy;
}

template <typename T>
template <bool IsConst>
deque<T>::base_iterator<IsConst>&
deque<T>::base_iterator<IsConst>::operator--() {
  if (current.x == 0) {
    current.y--;
    current.x = static_cast<int>(bucket::size) - 1;
  } else
    current.x--;

  return *this;
}

template <typename T>
template <bool IsConst>
deque<T>::base_iterator<IsConst> deque<T>::base_iterator<IsConst>::operator--(
    int) {
  base_iterator copy = *this;

  if (current.x == 0) {
    current.y--;
    current.x = static_cast<int>(bucket::size) - 1;
  } else
    current.x--;

  return copy;
}

template <typename T>
template <bool IsConst>
deque<T>::base_iterator<IsConst>::operator base_iterator<true>() const {
  return {ptr, current};
}
}  // namespace s21