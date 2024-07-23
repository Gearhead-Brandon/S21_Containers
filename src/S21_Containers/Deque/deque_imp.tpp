#include "s21_deque.h"

namespace s21 {
template <typename T>
deque<T>::Point::Point() : y(0), x(0) {}

template <typename T>
deque<T>::Point::Point(const Point& other) : y(other.y), x(other.x) {}

template <typename T>
deque<T>::Point::Point(int num) : y(num), x(num) {}

template <typename T>
typename deque<T>::Point& deque<T>::Point::operator=(Point& other) {
  y = other.y;
  x = other.x;
  return *this;
}

template <typename T>
deque<T>::deque()
    : matrix_(nullptr),
      rows_(0),
      cols_(-1),
      size_(0),
      first_elem_(0),
      last_elem_(0) {}

template <typename T>
deque<T>::deque(std::initializer_list<value_type> const& items) : deque() {
  for (auto it = items.begin(); it != items.end(); ++it) push_back(*it);
}

template <typename T>
deque<T>::deque(const deque& other) : deque() {
  for (auto it = other.begin(); it != other.end(); ++it) push_back(*it);
}

template <typename T>
deque<T>::deque(deque&& other) noexcept : deque() {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  size_ = other.size_;

  first_elem_ = other.first_elem_;
  last_elem_ = other.last_elem_;

  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;

  other.first_elem_.x = 0;
  other.first_elem_.y = 0;

  other.last_elem_.x = 0;
  other.last_elem_.y = 0;

  other.size_ = 0;
}

template <typename T>
deque<T>& deque<T>::operator=(const deque& other) {
  if (this == &other) return *this;

  if (matrix_)
    for (size_type i = 0, size = size_; i < size; ++i) pop_back();

  for (auto it = other.begin(); it != other.end(); ++it) push_back(*it);

  return *this;
}

template <typename T>
deque<T>& deque<T>::operator=(deque&& other) noexcept {
  if (this == &other) return *this;

  if (matrix_) remove();

  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  size_ = other.size_;

  first_elem_ = other.first_elem_;
  last_elem_ = other.last_elem_;

  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
  other.size_ = 0;

  other.first_elem_.x = 0;
  other.first_elem_.y = 0;

  other.last_elem_.x = 0;
  other.last_elem_.y = 0;

  return *this;
}

template <typename T>
deque<T>::~deque() {
  if (matrix_) remove();
}

template <typename T>
void deque<T>::remove() {
  for (size_type i = 0, size = size_; i < size; ++i) pop_back();

  for (size_type i = 0; i < rows_; ++i) {
    if (!matrix_[i]) continue;

    delete[] reinterpret_cast<byte*>(matrix_[i]);
  }

  delete[] reinterpret_cast<byte*>(matrix_);
}

template <typename T>
void deque<T>::push_back(const value_type& value) {
  isMatrixNull();

  isRowNull(last_elem_.y);

  new (matrix_[last_elem_.y] + last_elem_.x++) value_type(value);

  reserve();

  size_++;
}

template <typename T>
void deque<T>::pop_back() {
  last_elem_.x--;

  if (last_elem_.x < 0) {
    last_elem_.x = cols_ - 1;
    last_elem_.y--;
  }

  matrix_[last_elem_.y][last_elem_.x].~value_type();

  size_--;
}

template <typename T>
void deque<T>::push_front(const value_type& value) {
  isMatrixNull();

  first_elem_.x--;

  reserve();

  isRowNull(first_elem_.y);

  new (matrix_[first_elem_.y] + first_elem_.x) value_type(value);

  size_++;
}

template <typename T>
void deque<T>::pop_front() {
  matrix_[first_elem_.y][first_elem_.x].~value_type();

  first_elem_.x++;

  if (static_cast<size_type>(first_elem_.x) >= cols_) {
    first_elem_.x = 0;
    first_elem_.y++;
  }

  size_--;
}

template <typename T>
typename deque<T>::size_type deque<T>::size() const noexcept {
  return size_;
}

template <typename T>
bool deque<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
void deque<T>::swap(deque& other) {
  if (this == &other) return;

  swap(matrix_, other.matrix_);
  swap(rows_, other.rows_);
  swap(cols_, other.cols_);

  swap(size_, other.size_);

  swap(first_elem_.x, other.first_elem_.x);
  swap(first_elem_.y, other.first_elem_.y);

  swap(last_elem_.y, other.last_elem_.y);
  swap(last_elem_.x, other.last_elem_.x);
}

template <typename T>
typename deque<T>::reference deque<T>::operator[](size_type index) {
  Point temp;

  temp.y = first_elem_.y + index / cols_;
  temp.x = first_elem_.x + index % cols_;

  if (temp.x >= cols_) {
    temp.x = temp.x - cols_;
    temp.y++;
  }

  return matrix_[temp.y][temp.x];
}

template <typename T>
typename deque<T>::const_reference deque<T>::front() const {
  return matrix_[first_elem_.y][first_elem_.x];
}

template <typename T>
typename deque<T>::const_reference deque<T>::back() const {
  int x = last_elem_.x - 1;
  int y = last_elem_.y;

  if (x < 0) {
    x = cols_ - 1;
    y--;
  }

  return matrix_[y][x];
}

template <typename T>
template <typename U>
void deque<T>::swap(U& a, U& b) {
  U temp = std::move(a);
  a = std::move(b);
  b = std::move(temp);
}

template <typename T>
void deque<T>::reserve() {
  if (static_cast<size_type>(last_elem_.x) >= cols_) {
    last_elem_.x = 0;
    last_elem_.y++;

    if (static_cast<size_type>(last_elem_.y) == rows_)
      matrixExpansionInDirection(static_cast<bool>(direction::Down));

    return;
  }

  if (first_elem_.x < 0) {
    first_elem_.x = cols_ - 1;
    first_elem_.y--;

    if (first_elem_.y <= -1) {
      size_type oldrows = rows_;

      matrixExpansionInDirection(static_cast<bool>(direction::Up));

      first_elem_.y = rows_ - oldrows - 1;

      last_elem_.y += rows_ - oldrows;
    }

    return;
  }
}

template <typename T>
void deque<T>::isMatrixNull() {
  if (!matrix_) new_primary_matrix();
}

template <typename T>
void deque<T>::isRowNull(int index) {
  if (!matrix_[index]) matrix_[index] = newRawRow();
}

template <typename T>
void deque<T>::matrixExpansionInDirection(const bool direction) {
  const size_type oldrows = rows_;

  rows_ *= 2;

  const size_type shift = direction ? (rows_ - oldrows) : 0;

  value_type** newmatrix = newArrayOfPointers();

  for (size_type i = 0 + shift, j = 0, size = oldrows + shift; (i < size);
       ++i, ++j)
    newmatrix[i] = matrix_[j];

  // Down i = 0   size = oldrows
  // Up i = shift size = oldrows + shiftt

  size_type i = shift ? 0 : oldrows;
  size_type j = shift ? shift : rows_;

  for (; i < j; ++i) newmatrix[i] = nullptr;

  // Down  i = oldrows j = rows_
  // Up i = 0 J = shift

  delete[] reinterpret_cast<byte*>(matrix_);

  matrix_ = newmatrix;
}

template <typename T>
void deque<T>::new_primary_matrix() {
  rows_ = 11;
  cols_ = static_cast<size_type>(bucket::size);

  value_type** newmatrix = newArrayOfPointers();

  std::fill(newmatrix, newmatrix + rows_, nullptr);

  first_elem_.y = 5;
  first_elem_.x = 0;

  last_elem_.y = 5;
  last_elem_.x = 0;

  matrix_ = newmatrix;
}

template <typename T>
typename deque<T>::value_type** deque<T>::newArrayOfPointers() {
  return reinterpret_cast<value_type**>(new byte[rows_ * sizeof(value_type*)]);
}

template <typename T>
typename deque<T>::value_type* deque<T>::newRawRow() {
  return reinterpret_cast<value_type*>(new byte[cols_ * sizeof(value_type)]);
}

template <typename T>
typename deque<T>::iterator deque<T>::begin() {
  return {matrix_, first_elem_};
}

template <typename T>
typename deque<T>::iterator deque<T>::end() {
  return {matrix_, last_elem_};
}

template <typename T>
typename deque<T>::const_iterator deque<T>::begin() const {
  return {matrix_, first_elem_};
}

template <typename T>
typename deque<T>::const_iterator deque<T>::end() const {
  return {matrix_, last_elem_};
}
}  // namespace s21