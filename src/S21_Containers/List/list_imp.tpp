#include "s21_list.h"

namespace s21 {
template <typename T>
list<T>::BaseNode_::BaseNode_() : prev(nullptr), next(nullptr) {}

template <typename T>
list<T>::Node_::Node_() : data() {}

template <typename T>
list<T>::Node_::Node_(const value_type &data) : data(data) {}

template <typename T>
list<T>::list() : fakeNode_(new BaseNode_()), size_(0) {
  fakeNode_->prev = fakeNode_;
  fakeNode_->next = fakeNode_;
}

template <typename T>
list<T>::list(size_type n) : list() {
  value_type value{};

  for (size_type i = 0; i < n; i++) push_back(value);
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto &item : items) push_back(item);
}

template <typename T>
list<T>::list(const list &l) : list() {
  for (auto it = l.begin(); it != l.end(); it++) push_back(*it);
}

template <typename T>
list<T>::list(list &&l) noexcept : list() {
  swap(l);
}

template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (this == &l) return *this;

  clear();

  for (auto it = l.begin(); it != l.end(); it++) push_back(*it);

  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this == &l) return *this;

  swap(l);

  l.clear();

  return *this;
}

template <typename T>
list<T>::~list() {
  clear();

  delete fakeNode_;
}

template <typename T>
void list<T>::push_back(const T &value) {
  Node_ *newNode = new Node_(value);

  newNode->prev = fakeNode_->prev;
  newNode->next = fakeNode_;

  fakeNode_->prev->next = newNode;
  fakeNode_->prev = newNode;

  size_++;
}

template <typename T>
void list<T>::push_front(const T &value) {
  Node_ *newNode = new Node_(value);

  newNode->prev = fakeNode_;
  newNode->next = fakeNode_->next;

  fakeNode_->next->prev = newNode;
  fakeNode_->next = newNode;

  size_++;
}

template <typename T>
void list<T>::pop_back() {
  BaseNode_ *lastNode = fakeNode_->prev;

  fakeNode_->prev = lastNode->prev;

  lastNode->prev->next = fakeNode_;

  delete lastNode;

  size_--;
}

template <typename T>
void list<T>::pop_front() {
  BaseNode_ *firstNode = fakeNode_->next;

  fakeNode_->next = firstNode->next;

  firstNode->next->prev = fakeNode_;

  delete firstNode;

  size_--;
}

template <typename T>
void list<T>::reverse() {
  if (size_ < 2) return;

  BaseNode_ *currentNode = fakeNode_->next;

  swap(fakeNode_->next, fakeNode_->prev);

  for (size_type i = 0; i < size_; i++) {
    swap(currentNode->next, currentNode->prev);
    currentNode = currentNode->prev;
  }
}

template <typename T>
typename list<T>::reference list<T>::front() {
  return static_cast<Node_ *>(fakeNode_->next)->data;
}

template <typename T>
typename list<T>::reference list<T>::back() {
  return static_cast<Node_ *>(fakeNode_->prev)->data;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return static_cast<Node_ *>(fakeNode_->next)->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return static_cast<Node_ *>(fakeNode_->prev)->data;
}

template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename list<value_type>::Node_) / 2;
}

template <typename T>
void list<T>::clear() noexcept {
  for (size_type i = 0, size = size_; i < size; i++) pop_front();
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node_ *newNode = new Node_(value);

  BaseNode_ *current = pos.ptr;

  newNode->next = current;
  newNode->prev = current->prev;

  current->prev->next = newNode;
  current->prev = newNode;

  size_++;

  return iterator(newNode);
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node_ *current = static_cast<Node_ *>(pos.ptr);

  current->prev->next = current->next;
  current->next->prev = current->prev;

  delete current;

  size_--;
}

template <typename T>
void list<T>::unique()  // O(n * log n)
{
  if (size_ < 2) return;

  BaseNode_ *current = fakeNode_->next;

  s21::set<T> set;

  Node_ *node = nullptr;

  while (current != fakeNode_) {
    node = static_cast<Node_ *>(current);
    current = current->next;

    if (set.contains(node->data))
      erase(iterator(node));
    else
      set.insert(node->data);
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (other.empty()) return;

  BaseNode_ *current = const_cast<BaseNode_ *>(pos.ptr);
  BaseNode_ *other_current = other.fakeNode_->next;

  current->prev->next = other_current;
  other_current->prev = current->prev;

  other_current = other.fakeNode_->prev;

  other_current->next = current;
  current->prev = other_current;

  size_ += other.size_;

  other.fakeNode_->next = other.fakeNode_;
  other.fakeNode_->prev = other.fakeNode_;

  other.size_ = 0;
}

template <typename T>
void list<T>::merge(list &other) {
  if (other.empty() || this == &other) return;

  if (empty()) {
    swap(other);
    return;
  }

  BaseNode_ *current = fakeNode_->next;

  BaseNode_ *otherCurrent = other.fakeNode_->next;

  BaseNode_ dummyNode;
  BaseNode_ *tail = &dummyNode;

  Node_ *first = nullptr;
  Node_ *second = nullptr;

  while (current != fakeNode_ && otherCurrent != other.fakeNode_) {
    first = static_cast<Node_ *>(current);
    second = static_cast<Node_ *>(otherCurrent);

    if (first->data < second->data) {
      tail->next = current;
      current = current->next;
    } else {
      tail->next = otherCurrent;
      otherCurrent = otherCurrent->next;
    }

    tail->next->prev = tail;
    tail = tail->next;
  }
  if (current != fakeNode_) {
    tail->next = current;
    current->prev = tail;
  } else if (otherCurrent != other.fakeNode_) {
    tail->next = otherCurrent;
    otherCurrent->prev = tail;

    other.fakeNode_->prev->next = fakeNode_;

    fakeNode_->prev = other.fakeNode_->prev;
  }

  fakeNode_->next = dummyNode.next;

  other.fakeNode_->next = other.fakeNode_;
  other.fakeNode_->prev = other.fakeNode_;

  size_ += other.size_;

  other.size_ = 0;
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) return;

  mergeSort();
}

template <typename T>
void list<T>::swap(list &other) {
  if (this == &other) return;

  swap(fakeNode_, other.fakeNode_);
  swap(size_, other.size_);
}

template <typename T>
void list<T>::mergeSort() {
  size_type half_size = size_ / 2;

  iterator it = begin();

  list<value_type> half_hearted;

  BaseNode_ *half_hearted_node = half_hearted.fakeNode_;

  for (size_type i = 0; i < half_size; i++, it++) {
    half_hearted_node->next = it.ptr;
    half_hearted.size_++;
    half_hearted_node = half_hearted_node->next;
  }

  half_hearted_node->next = half_hearted.fakeNode_;
  half_hearted.fakeNode_->prev = half_hearted_node;

  list<value_type> post_half;

  BaseNode_ *post_half_node = post_half.fakeNode_;

  for (; it != fakeNode_; it++) {
    post_half_node->next = it.ptr;
    post_half.size_++;
    post_half_node = post_half_node->next;
  }

  post_half_node->next = post_half.fakeNode_;
  post_half.fakeNode_->prev = post_half_node;

  fakeNode_->next = fakeNode_;
  fakeNode_->prev = fakeNode_;
  size_ = 0;

  if (half_hearted.size_ > 1) half_hearted.sort();

  if (post_half.size_ > 1) post_half.sort();

  half_hearted.merge(post_half);

  swap(half_hearted);
}

template <typename T>
template <typename U>
void list<T>::swap(U &a, U &b) {
  U temp = std::move(a);
  a = std::move(b);
  b = std::move(temp);
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return {fakeNode_->next};
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return {fakeNode_};
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  return {fakeNode_->next};
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return {fakeNode_};
}
}  // namespace s21