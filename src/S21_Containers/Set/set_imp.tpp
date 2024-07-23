#include "s21_set.h"

template <typename W>
bool ComparatorSet<W>::operator()(const W& a, const W& b) const {
  return a < b;
}

namespace s21 {
template <typename T, template <typename> typename Compare>
set<T, Compare>::BaseNode_::BaseNode_()
    : left(nullptr), right(nullptr), parent(nullptr) {}

template <typename T, template <typename> typename Compare>
set<T, Compare>::Node_::Node_() : key(), height(0) {}

template <typename T, template <typename> typename Compare>
set<T, Compare>::Node_::Node_(const value_type& key) : key(key), height(1) {}

template <typename T, template <typename> typename Compare>
set<T, Compare>::set() : fakeNode_(new BaseNode_()), size_(0) {}

template <typename T, template <typename> typename Compare>
set<T, Compare>::set(std::initializer_list<value_type> const& list) : set() {
  for (auto it = list.begin(); it != list.end(); ++it) insert(*it);
}

template <typename T, template <typename> typename Compare>
set<T, Compare>::set(const set& other) : set() {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
}

template <typename T, template <typename> typename Compare>
set<T, Compare>::set(set&& other) noexcept : set() {
  swap(other);
}

template <typename T, template <typename> typename Compare>
set<T, Compare>::~set() {
  clearTreeRecursive(getRoot());

  delete fakeNode_;
}

template <typename T, template <typename> typename Compare>
set<T, Compare>& set<T, Compare>::operator=(const set& other) {
  if (this == &other) return *this;

  set temp(other);

  swap(temp);

  return *this;
}

template <typename T, template <typename> typename Compare>
set<T, Compare>& set<T, Compare>::operator=(set&& other) noexcept {
  if (this == &other) return *this;

  set temp(std::move(other));

  swap(temp);

  return *this;
}

template <typename T, template <typename> typename Compare>
std::pair<typename set<T, Compare>::iterator, bool> set<T, Compare>::insert(
    const value_type& value) {
  Node_* newNode = new Node_(value);

  return insertNode(newNode);
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::iterator set<T, Compare>::find(
    const value_type& key) const {
  BaseNode_* current = getRoot();

  Node_* content = nullptr;

  iterator it(current);

  while (current != nullptr) {
    it.node_ptr = current;

    content = static_cast<Node_*>(current);

    if (comparator(key, content->key, current)) return it;
  }

  return it;
}

template <typename T, template <typename> typename Compare>
bool set<T, Compare>::contains(const value_type& key) const {
  BaseNode_* current = static_cast<BaseNode_*>(getRoot());

  Node_* content = nullptr;

  while (current != nullptr) {
    content = static_cast<Node_*>(current);

    if (comparator(key, content->key, current)) return true;
  }

  return false;
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::erase(iterator pos) {
  if (!pos.node_ptr) return;

  fakeNode_->left = deleteNodeRecursive(getRoot(), *pos);
}

template <typename T, template <typename> typename Compare>
bool set<T, Compare>::empty() const noexcept {
  return size_ == 0;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::size_type set<T, Compare>::size() const noexcept {
  return size_;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::size_type set<T, Compare>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename set<value_type>::Node_);
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::swap(set& other) noexcept {
  if (this == &other) return;

  std::swap(fakeNode_, other.fakeNode_);
  std::swap(size_, other.size_);
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::clear() noexcept {
  if (!size_) return;

  clearTreeRecursive(getRoot());

  fakeNode_->left = nullptr;

  size_ = 0;
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::merge(set& other)  // O(N * log(N)
{
  if (this == &other || other.empty()) return;

  if (empty()) {
    swap(other);
    return;
  }

  mergeBypass(other.getRoot());

  other.size_ = 0;
  other.fakeNode_->left = nullptr;
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::mergeBypass(BaseNode_* node) {
  if (!node) return;

  mergeBypass(node->left);

  mergeBypass(node->right);

  leafNodeTransfer(node);
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::leafNodeTransfer(BaseNode_* node) {
  if (!node->left && !node->right) {
    if (node == node->parent->left) node->parent->left = nullptr;

    if (node == node->parent->right) node->parent->right = nullptr;

    node->parent = nullptr;

    insertNode(static_cast<Node_*>(node));
  }
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::clearTreeRecursive(BaseNode_* node) {
  if (!node) return;

  clearTreeRecursive(node->left);

  clearTreeRecursive(node->right);

  delete static_cast<Node_*>(node);
}

template <typename T, template <typename> typename Compare>
std::pair<typename set<T, Compare>::iterator, bool> set<T, Compare>::insertNode(
    Node_* newNode) {
  BaseNode_* current = getRoot();

  iterator it(current);

  if (!current) {
    fakeNode_->left = newNode;
    newNode->parent = fakeNode_;

    it.node_ptr = newNode;
  } else {
    BaseNode_* parent = current->parent;

    while (current != nullptr) {
      parent = current;

      it.node_ptr = parent;

      if (!comparator(newNode->key, static_cast<Node_*>(current)->key, current,
                      newNode))
        return std::make_pair(it, false);
    }

    if (comp_(newNode->key, static_cast<Node_*>(parent)->key))
      parent->left = newNode;
    else
      parent->right = newNode;

    newNode->parent = parent;
    it.node_ptr = newNode;

    heightAdjustment(newNode);
  }

  size_++;

  return std::make_pair(it, true);
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::BaseNode_* set<T, Compare>::findMinNode(
    BaseNode_* node) {
  if (node)
    while (node->left) node = node->left;

  return node;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::BaseNode_* set<T, Compare>::detachMinNode(
    BaseNode_* node) {
  if (!node->left) return node->right;

  node->left = detachMinNode(node->left);

  if (node->left) node->left->parent = node;

  return Balance(node);
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::BaseNode_* set<T, Compare>::deleteNodeRecursive(
    Node_* node, const value_type& key) {
  if (!node) return nullptr;

  if (key < node->key)
    node->left = deleteNodeRecursive(static_cast<Node_*>(node->left), key);
  else if (key > node->key)
    node->right = deleteNodeRecursive(static_cast<Node_*>(node->right), key);
  else {
    BaseNode_* left = node->left;
    BaseNode_* right = node->right;
    BaseNode_* parent = node->parent;

    size_--;

    if (!right) {
      if (left) left->parent = parent;

      delete node;

      return left;
    }

    BaseNode_* min = findMinNode(right);  // in right subtree

    min->right = detachMinNode(right);

    if (min->right) min->right->parent = min;

    min->left = left;

    if (min->left) min->left->parent = min;

    if (min->parent) min->parent = parent;

    delete node;

    return Balance(min);
  }

  return Balance(node);
}

template <typename T, template <typename> typename Compare>
bool set<T, Compare>::comparator(const value_type& a, const value_type& b,
                                 BaseNode_*& current, Node_* newNode) {
  if (comp_(a, b))
    current = current->left;
  else if (comp_(b, a))
    current = current->right;
  else {
    delete newNode;
    return false;
  }

  return true;
}

template <typename T, template <typename> typename Compare>
bool set<T, Compare>::comparator(const value_type& a, const value_type& b,
                                 BaseNode_*& current) const {
  if (comp_(a, b))
    current = current->left;
  else if (comp_(b, a))
    current = current->right;
  else
    return true;

  return false;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::BaseNode_* set<T, Compare>::rotateRight(
    BaseNode_* node) {
  BaseNode_* leftChild = node->left;

  node->left = leftChild->right;

  if (leftChild->right) leftChild->right->parent = node;

  leftChild->parent = node->parent;

  if (node->parent != fakeNode_) {
    if (node == node->parent->left)
      node->parent->left = leftChild;
    else
      node->parent->right = leftChild;
  }

  leftChild->right = node;
  node->parent = leftChild;

  FixHeight(node);
  FixHeight(leftChild);

  return leftChild;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::BaseNode_* set<T, Compare>::rotateLeft(
    BaseNode_* node) {
  BaseNode_* rightChild = node->right;

  node->right = rightChild->left;

  if (rightChild->left) rightChild->left->parent = node;

  rightChild->parent = node->parent;

  if (node->parent != fakeNode_) {
    if (node == node->parent->left)
      node->parent->left = rightChild;
    else
      node->parent->right = rightChild;
  }

  rightChild->left = node;
  node->parent = rightChild;

  FixHeight(node);
  FixHeight(rightChild);

  return rightChild;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::BaseNode_* set<T, Compare>::Balance(BaseNode_* node) {
  FixHeight(node);

  int BF = BalanceFactor(node);

  if (BF == 2) {
    if (BalanceFactor(node->right) < 0) node->right = rotateRight(node->right);

    return rotateLeft(node);
  }

  if (BF == -2) {
    if (BalanceFactor(node->left) > 0) node->left = rotateLeft(node->left);

    return rotateRight(node);
  }

  return node;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::size_type set<T, Compare>::height(BaseNode_* node) {
  return node ? static_cast<Node_*>(node)->height : 0;
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::FixHeight(BaseNode_* node) {
  size_type leftHeight = height(node->left);
  size_type rightHeight = height(node->right);

  static_cast<Node_*>(node)->height = 1 + std::max(leftHeight, rightHeight);
}

template <typename T, template <typename> typename Compare>
void set<T, Compare>::heightAdjustment(BaseNode_* node) {
  node = node->parent;

  BaseNode_* newRoot = getRoot();

  while (node != fakeNode_) {
    newRoot = Balance(node);

    node = node->parent;
  }

  fakeNode_->left = newRoot;
}

template <typename T, template <typename> typename Compare>
int set<T, Compare>::BalanceFactor(BaseNode_* node) {
  if (!node) return 0;

  return height(node->right) - height(node->left);
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::Node_* set<T, Compare>::getBegin() const {
  if (!size_) return nullptr;

  Node_* node = getRoot();

  if (node)
    while (node->left != nullptr) node = static_cast<Node_*>(node->left);

  return node;
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::Node_* set<T, Compare>::getRoot() const {
  return static_cast<Node_*>(fakeNode_->left);
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::iterator set<T, Compare>::begin() {
  return {getBegin()};
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::iterator set<T, Compare>::end() {
  return {fakeNode_};
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::begin() const {
  return {getBegin()};
}

template <typename T, template <typename> typename Compare>
typename set<T, Compare>::const_iterator set<T, Compare>::end() const {
  return {fakeNode_};
}
}  // namespace s21