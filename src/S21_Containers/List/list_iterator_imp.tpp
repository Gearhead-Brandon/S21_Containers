#include "s21_list.h"

namespace s21 {
template <typename T>
template <bool IsConst>
list<T>::base_iterator<IsConst>::base_iterator(BaseNode_* node) : ptr(node) {}

template <typename T>
template <bool IsConst>
list<T>::base_iterator<IsConst>::base_iterator(const base_iterator& other)
    : ptr(other.ptr) {}

template <typename T>
template <bool IsConst>
typename list<T>::base_iterator<IsConst>::ref_type
list<T>::base_iterator<IsConst>::operator*() const {
  return static_cast<node_type>(ptr)->data;
}

template <typename T>
template <bool IsConst>
bool list<T>::base_iterator<IsConst>::operator==(
    const base_iterator<IsConst>& other) const {
  return ptr == other.ptr;
}

template <typename T>
template <bool IsConst>
bool list<T>::base_iterator<IsConst>::operator!=(
    const base_iterator<IsConst>& other) const {
  return ptr != other.ptr;
}

template <typename T>
template <bool IsConst>
typename list<T>::base_iterator<IsConst>&
list<T>::base_iterator<IsConst>::operator++() {
  ptr = ptr->next;
  return *this;
}

template <typename T>
template <bool IsConst>
typename list<T>::base_iterator<IsConst>
list<T>::base_iterator<IsConst>::operator++(int) {
  base_iterator copy = *this;
  ptr = ptr->next;
  return copy;
}

template <typename T>
template <bool IsConst>
typename list<T>::base_iterator<IsConst>&
list<T>::base_iterator<IsConst>::operator--() {
  ptr = ptr->prev;
  return *this;
}

template <typename T>
template <bool IsConst>
typename list<T>::base_iterator<IsConst>
list<T>::base_iterator<IsConst>::operator--(int) {
  base_iterator copy = *this;
  ptr = ptr->prev;
  return copy;
}

template <typename T>
template <bool IsConst>
list<T>::base_iterator<IsConst>::operator base_iterator<true>() const {
  return ptr;
}
}  // namespace s21