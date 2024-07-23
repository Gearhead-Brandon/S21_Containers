#include "s21_vector.h"

namespace s21 {
template <typename T>
vector<T>::vector() : arr_(nullptr), size_(0), cap_(0) {}

template <typename T>
vector<T>::vector(size_type count) : vector() {
  if (count > max_size())
    throw std::length_error(
        "In constructor: cannot create s21::vector larger than max_size()");

  arr_ = newRawArray(count);

  size_type i = 0;

  for (; i < count; ++i) new (arr_ + i) value_type();

  cap_ = count;
  size_ = count;
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : arr_(newRawArray(items.size())), size_(0), cap_(0) {
  size_type i = 0;

  for (const value_type& it : items) new (arr_ + i++) value_type(it);

  cap_ = items.size();
  size_ = items.size();
}

template <typename T>
vector<T>::vector(const vector& v)
    : arr_(newRawArray(v.cap_)), size_(v.size_), cap_(v.cap_) {
  for (size_type i = 0; i < v.size_; ++i) new (arr_ + i) value_type(v.arr_[i]);
}

template <typename T>
vector<T>::vector(vector&& v) noexcept
    : arr_(v.arr_), size_(v.size_), cap_(v.cap_) {
  v.arr_ = nullptr;
  v.size_ = 0;
  v.cap_ = 0;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& v) {
  if (this == &v) return *this;

  value_type* newArr = newRawArray(v.cap_);

  for (size_type i = 0; i < v.size_; ++i)
    new (newArr + i) value_type(v.arr_[i]);

  if (arr_) delete_arr(arr_, size_);

  arr_ = newArr;

  size_ = v.size_;
  cap_ = v.cap_;

  return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) noexcept {
  if (this == &v) return *this;

  if (arr_) delete_arr(arr_, size_);

  arr_ = v.arr_;
  size_ = v.size_;
  cap_ = v.cap_;

  v.arr_ = nullptr;
  v.size_ = 0;
  v.cap_ = 0;

  return *this;
}

template <typename T>
vector<T>::~vector() {
  if (arr_) delete_arr(arr_, size_);
}

template <typename T>
typename vector<T>::value_type* vector<T>::newRawArray(size_type newcap) {
  return reinterpret_cast<value_type*>(new byte[newcap * sizeof(value_type)]);
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ == cap_) return;

  resize_capacity(size_);
}

template <typename T>
void vector<T>::delete_arr(value_type* arr, size_type size) {
  for (size_type i = 0; i < size; ++i) (arr + i)->~T();

  delete[] reinterpret_cast<byte*>(arr);
}

template <typename T>
void vector<T>::resize_capacity(size_type newcap) {
  value_type* newarr = newRawArray(newcap);

  // size_type i = 0;
  // try{

  for (size_type i = 0; i < size_; ++i)
    new (newarr + i) value_type(std::move_if_noexcept(arr_[i]));
    
  // }catch(...){

  //     delete_arr(newarr, i);
  //     throw;
  // }

  delete_arr(arr_, size_);

  arr_ = newarr;
  cap_ = newcap;
}

template <typename T>
void vector<T>::reserve(size_type newcap) {
  if (newcap <= cap_) return;

  resize_capacity(newcap);
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == cap_) reserve(cap_ > 0 ? cap_ * 2 : 1);

  // try
  new (arr_ + size_++) value_type(value);
  // catch
}

template <typename T>
void vector<T>::pop_back() noexcept {
  if (size_ > 0) (arr_ + --size_)->~T();
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type index) noexcept {
  return *(arr_ + index);
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](
    size_type index) const noexcept {
  return *(arr_ + index);
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type index) {
  if (!size_ || index >= size_)
    throw std::out_of_range("out of range in vector");

  return *(arr_ + index);
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type index) const {
  if (!size_ || index >= size_)
    throw std::out_of_range("out of range in vector");

  return *(arr_ + index);
}

template <typename T>
typename vector<T>::reference vector<T>::front() noexcept {
  return *arr_;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const noexcept {
  return *arr_;
}

template <typename T>
typename vector<T>::reference vector<T>::back() noexcept {
  return *(arr_ + (size_ - 1));
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const noexcept {
  return *(arr_ + (size_ - 1));
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return cap_;
}

template <typename T>
typename vector<T>::pointer vector<T>::data() const noexcept {
  return arr_;
}

template <typename T>
bool vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
void vector<T>::clear() {
  for (size_type i = 0; i < size_; ++i) (arr_ + i)->~T();

  size_ = 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  long long int index = pos - begin();

  if (index < 0) return begin();

  if (index > static_cast<long long int>(size_))
    throw std::out_of_range("out of range in vector");

  if (size_ == cap_) reserve(cap_ > 0 ? cap_ * 2 : 1);

  size_type ind = index;

  for (size_type i = size_; i > ind; --i) {
    new (arr_ + i) value_type(arr_[i - 1]);
    (arr_ + (i - 1))->~T();
  }

  if (ind < size_) (arr_ + ind)->~T();

  new (arr_ + index) value_type(value);

  ++size_;

  return begin() + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  long long int index = pos - begin();

  if (index < 0) index = 0;

  if (index > static_cast<long long int>(size_)) index = size_ - 1;

  --size_;

  for (size_type i = index; i < size_; ++i) {
    arr_[i].~T();
    new (arr_ + i) value_type(arr_[i + 1]);
  }

  (arr_ + size_)->~value_type();
}

template <typename T>
void vector<T>::swap(vector& other) noexcept {
  if (this == &other) return;

  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(cap_, other.cap_);
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return {arr_};
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return {arr_ + size_};
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return {arr_};
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return {arr_ + size_};
}
}  // namespace s21