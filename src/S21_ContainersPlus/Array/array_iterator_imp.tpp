#include "s21_array.h"

namespace s21 {
template <typename T, size_t N>
template <bool IsConst>
array<T, N>::base_iterator<IsConst>::base_iterator(value_type* p) : ptr(p) {}

template <typename T, size_t N>
template <bool IsConst>
array<T, N>::base_iterator<IsConst>::base_iterator(const base_iterator& other)
    : ptr(other.ptr) {}

template <typename T, size_t N>
template <bool IsConst>
typename array<T, N>::base_iterator<IsConst>::ref_type
array<T, N>::base_iterator<IsConst>::operator*() const {
  return *ptr;
}

template <typename T, size_t N>
template <bool IsConst>
bool array<T, N>::base_iterator<IsConst>::operator==(
    const base_iterator<IsConst>& other) const {
  return ptr == other.ptr;
}

template <typename T, size_t N>
template <bool IsConst>
bool array<T, N>::base_iterator<IsConst>::operator!=(
    const base_iterator<IsConst>& other) const {
  return ptr != other.ptr;
}

template <typename T, size_t N>
template <bool IsConst>
typename array<T, N>::base_iterator<IsConst>&
array<T, N>::base_iterator<IsConst>::operator++() {
  ptr++;
  return *this;
}

template <typename T, size_t N>
template <bool IsConst>
typename array<T, N>::base_iterator<IsConst>
array<T, N>::base_iterator<IsConst>::operator++(int) {
  base_iterator copy = *this;
  ++ptr;
  return copy;
}

template <typename T, size_t N>
template <bool IsConst>
typename array<T, N>::base_iterator<IsConst>&
array<T, N>::base_iterator<IsConst>::operator--() {
  ptr--;
  return *this;
}

template <typename T, size_t N>
template <bool IsConst>
typename array<T, N>::base_iterator<IsConst>
array<T, N>::base_iterator<IsConst>::operator--(int) {
  base_iterator copy = *this;
  ptr--;
  return copy;
}

template <typename T, size_t N>
template <bool IsConst>
array<T, N>::base_iterator<IsConst>::operator base_iterator<true>() const {
  return ptr;
}
}  // namespace s21