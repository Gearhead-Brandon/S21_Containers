#include "s21_array.h"

namespace s21 {
template <typename T, size_t N>
array<T, N>::array() {}

template <typename T, size_t N>
array<T, N>::array(const std::initializer_list<value_type>& items) {
  if (empty()) return;

  size_type i = 0;

  for (auto it = items.begin(); it != items.end(); it++, i++) {
    if (i >= N) break;

    arr_[i] = *it;
  }

  if (i < N) {
    value_type stub = value_type();

    for (; i < N; i++) arr_[i] = stub;
  }
}

template <typename T, size_t N>
array<T, N>::array(const array& other) {
  for (size_type i = 0; i < N; ++i) arr_[i] = other.arr_[i];
}

template <typename T, size_t N>
array<T, N>::array(array&& other) noexcept {
  std::swap(arr_, other.arr_);
}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(const array& other) {
  if (this == &other) return *this;

  for (size_type i = 0; i < N; ++i) arr_[i] = other.arr_[i];

  return *this;
}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array&& other) noexcept {
  if (this == &other) return *this;

  std::swap(arr_, other.arr_);
  return *this;
}

template <typename T, size_t N>
array<T, N>::~array() {}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) throw std::out_of_range("out of range in array");

  return arr_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return arr_[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return arr_[N > 0 ? N - 1 : 0];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return {arr_};
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

template <typename T, size_t N>
bool array<T, N>::empty() const {
  return N == 0;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;
}

template <typename T, size_t N>
void array<T, N>::swap(array& other) noexcept {
  std::swap(arr_, other.arr_);
}

template <typename T, size_t N>
void array<T, N>::fill(const value_type& value) {
  for (size_type i = 0; i < N; ++i) arr_[i] = value;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return {arr_};
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return {arr_ + N};
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const {
  return {const_cast<value_type*>(arr_)};
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const {
  return {const_cast<value_type*>(arr_) + N};
}
}  // namespace s21