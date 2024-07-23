#include "s21_vector.h"

namespace s21 {
template <typename T>
template <bool IsConst>
vector<T>::base_iterator<IsConst>::base_iterator(value_type* p) : ptr(p) {}

template <typename T>
template <bool IsConst>
vector<T>::base_iterator<IsConst>::base_iterator(const base_iterator& other)
    : ptr(other.ptr) {}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>::ref_type
vector<T>::base_iterator<IsConst>::operator*() const {
  return *ptr;
}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>::ptr_type
vector<T>::base_iterator<IsConst>::operator->() const {
  return ptr;
}

template <typename T>
template <bool IsConst>
bool vector<T>::base_iterator<IsConst>::operator==(
    const base_iterator<IsConst>& other) const {
  return ptr == other.ptr;
}

template <typename T>
template <bool IsConst>
bool vector<T>::base_iterator<IsConst>::operator!=(
    const base_iterator<IsConst>& other) const {
  return ptr != other.ptr;
}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>&
vector<T>::base_iterator<IsConst>::operator++() {
  ptr++;
  return *this;
}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>
vector<T>::base_iterator<IsConst>::operator++(int) {
  base_iterator copy = *this;
  ++ptr;
  return copy;
}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>&
vector<T>::base_iterator<IsConst>::operator--() {
  ptr--;
  return *this;
}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>
vector<T>::base_iterator<IsConst>::operator--(int) {
  base_iterator copy = *this;
  ptr--;
  return copy;
}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>
vector<T>::base_iterator<IsConst>::operator+(int n) {
  return ptr + n;
}

template <typename T>
template <bool IsConst>
int vector<T>::base_iterator<IsConst>::operator-(
    const base_iterator<IsConst>& other) const {
  return ptr - other.ptr;
}

template <typename T>
template <bool IsConst>
typename vector<T>::base_iterator<IsConst>
vector<T>::base_iterator<IsConst>::operator-(int n) const {
  return ptr - n;
}

template <typename T>
template <bool IsConst>
vector<T>::base_iterator<IsConst>::operator base_iterator<true>() const {
  return ptr;
}
}  // namespace s21