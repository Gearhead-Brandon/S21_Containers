#include "s21_multiset.h"

template <typename W>
bool Comparator<W>::operator()(const W &a, const W &b) const {
  return a < b;
}

namespace s21 {
template <typename T, template <typename> typename Compare>
multiset<T, Compare>::BaseNode_::BaseNode_()
    : left(nullptr), right(nullptr), parent(nullptr) {}

template <typename T, template <typename> typename Compare>
multiset<T, Compare>::Node_::Node_() : key(), height(0) {}

template <typename T, template <typename> typename Compare>
multiset<T, Compare>::Node_::Node_(const key_type &key) : key(key), height(1) {}

template <typename T, template <typename> typename Compare>
multiset<T, Compare>::multiset() : fakeNode_(new BaseNode_), size_(0) {}

template <typename T, template <typename> typename Compare>
multiset<T, Compare>::multiset(std::initializer_list<key_type> const &list)
    : multiset() {
  for (auto it = list.begin(); it != list.end(); ++it) insert(*it);
}

template <typename T, template <typename> typename Compare>
multiset<T, Compare>::multiset(const multiset &other) : multiset() {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
}

template <typename T, template <typename> typename Compare>
multiset<T, Compare>::multiset(multiset &&other) noexcept : multiset() {
  swap(other);
}

template <typename T, template <typename> typename Compare>
multiset<T, Compare>::~multiset() {
  clearTreeRecursive(size_ > 0 ? getRoot() : nullptr);

  delete fakeNode_;
}

template <typename T, template <typename> typename Compare>
multiset<T, Compare> &multiset<T, Compare>::operator=(const multiset &other) {
  if (this == &other) return *this;

  multiset temp(other);

  swap(temp);

  return *this;
}

template <typename T, template <typename> typename Compare>
multiset<T, Compare> &multiset<T, Compare>::operator=(
    multiset &&other) noexcept {
  if (this == &other) return *this;

  multiset temp(std::move(other));

  swap(temp);

  return *this;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::insert(
    const key_type &value) {
  Node_ *newNode = new Node_(value);

  return insertNode(newNode);
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::erase(iterator pos) {
  if (!pos.ptr) return;

  fakeNode_->left = deleteNodeRecursive(getRoot(), *pos);
}

template <typename T, template <typename> typename Compare>
bool multiset<T, Compare>::empty() const noexcept {
  return size_ == 0;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::size()
    const noexcept {
  return size_;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename multiset<key_type>::Node_);
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::swap(multiset &other) noexcept {
  std::swap(fakeNode_, other.fakeNode_);
  std::swap(size_, other.size_);
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::clear() noexcept {
  if (!size_) return;

  clearTreeRecursive(getRoot());

  fakeNode_->left = nullptr;

  size_ = 0;
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::merge(multiset &other) {
  if (this == &other) return;

  // for (auto it = other.begin(); it != other.end(); ++it) {
  //   Node_ *newNode = new Node_(*it);
  //   insertNode(newNode);
  // }
  // other.clear();
  mergeBypass(other.getRoot());

  other.size_ = 0;
  other.fakeNode_->left = nullptr;
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::mergeBypass(BaseNode_ *node) {
  if (!node) return;

  mergeBypass(node->left);

  mergeBypass(node->right);

  leafNodeTransfer(node);
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::leafNodeTransfer(BaseNode_ *node) {
  if (!node->left && !node->right) {
    if (node == node->parent->left) node->parent->left = nullptr;

    if (node == node->parent->right) node->parent->right = nullptr;

    node->parent = nullptr;

    insertNode(static_cast<Node_ *>(node));
  }
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::size_type multiset<T, Compare>::count(
    const key_type &key) const {
  if (!size_ || !contains(key)) return 0;

  size_type count = 0;
  bool flag = false;

  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      flag = true;
      ++count;
    } else if (flag)
      break;
  }

  return count;
}

template <typename T, template <typename> typename Compare>
bool multiset<T, Compare>::contains(const key_type &key) const {
  BaseNode_ *current = static_cast<BaseNode_ *>(getRoot());

  Node_ *content = nullptr;

  while (current != nullptr) {
    content = static_cast<Node_ *>(current);

    if (comparator(key, content->key, current)) return true;
  }

  return false;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::find(
    const key_type &key) const {
  BaseNode_ *current = getRoot();

  Node_ *content = nullptr;

  iterator it(current);

  while (current != nullptr) {
    it.ptr = current;

    content = static_cast<Node_ *>(current);

    if (comparator(key, content->key, current)) return it;
  }

  return it;
}

template <typename T, template <typename> typename Compare>
std::pair<typename multiset<T, Compare>::iterator,
          typename multiset<T, Compare>::iterator>
multiset<T, Compare>::equal_range(const key_type &key) {
  iterator first(begin()), last(begin());

  if (!size_ || !contains(key)) return std::make_pair(first, last);

  BaseNode_ *end_node = const_cast<BaseNode_ *>(end().ptr);

  for (auto it = begin(); it != end_node; ++it) {
    first = it;
    last = it;

    if (*it == key) break;
  }

  if (last.ptr)
    while (last != end_node && *last == key) ++last;

  return std::make_pair(first, last);
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::lower_bound(
    const key_type &key) {
  iterator first = begin();

  if (!size_) return first;

  BaseNode_ *end_node = end().ptr;

  for (auto it = begin(); it.ptr != end_node; ++it) {
    first = it;

    if (*it == key) break;

    if (*it > key) {
      first = it;
      break;
    }
  }

  return first;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::upper_bound(
    const key_type &key) {
  iterator last = end();

  if (!size_) return last;

  BaseNode_ *end_node = end().ptr;

  for (auto it = begin(); it.ptr != end_node; ++it) {
    last = it;

    if (*it > key) break;
  }

  return last;
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::clearTreeRecursive(BaseNode_ *node) {
  if (!node) return;

  clearTreeRecursive(node->left);

  clearTreeRecursive(node->right);

  delete static_cast<Node_ *>(node);
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::insertNode(
    Node_ *newNode) {
  BaseNode_ *current = getRoot();

  iterator it(current);

  if (!current) {
    fakeNode_->left = newNode;
    newNode->parent = fakeNode_;

    it.ptr = newNode;
  } else {
    BaseNode_ *parent = current->parent;

    while (current != nullptr) {
      parent = current;

      it.ptr = parent;

      insertionComparator(newNode->key, static_cast<Node_ *>(current)->key,
                          current);
    }

    if (comp_(newNode->key, static_cast<Node_ *>(parent)->key))
      parent->left = newNode;
    else
      parent->right = newNode;

    newNode->parent = parent;
    it.ptr = newNode;

    heightAdjustment(newNode);
  }

  size_++;

  return it;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::BaseNode_ *multiset<T, Compare>::findMinNode(
    BaseNode_ *node) {
  if (node)
    while (node->left) node = static_cast<Node_ *>(node->left);

  return node;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::BaseNode_ *multiset<T, Compare>::detachMinNode(
    BaseNode_ *node) {
  if (!node->left) return node->right;

  node->left = detachMinNode(node->left);

  if (node->left) node->left->parent = node;

  return Balance(node);
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::BaseNode_ *
multiset<T, Compare>::deleteNodeRecursive(Node_ *node, const key_type &key) {
  if (!node) return nullptr;

  if (comp_(key, node->key))
    node->left = deleteNodeRecursive(static_cast<Node_ *>(node->left), key);
  else if (comp_(node->key, key))
    node->right = deleteNodeRecursive(static_cast<Node_ *>(node->right), key);
  else {
    BaseNode_ *left = node->left;
    BaseNode_ *right = node->right;
    BaseNode_ *parent = node->parent;

    size_--;

    if (!right) {
      if (left) left->parent = parent;

      delete node;

      return left;
    }

    BaseNode_ *min = findMinNode(right);  // in right subtree

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
void multiset<T, Compare>::insertionComparator(const key_type &a,
                                               const key_type &b,
                                               BaseNode_ *&current) {
  if (comp_(a, b))
    current = current->left;
  else
    current = current->right;
}

template <typename T, template <typename> typename Compare>
bool multiset<T, Compare>::comparator(const key_type &a, const key_type &b,
                                      BaseNode_ *&current) const {
  if (comp_(a, b))
    current = current->left;
  else if (comp_(b, a))
    current = current->right;
  else
    return true;

  return false;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::BaseNode_ *multiset<T, Compare>::rotateRight(
    BaseNode_ *node) {
  BaseNode_ *leftChild = node->left;

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
typename multiset<T, Compare>::BaseNode_ *multiset<T, Compare>::rotateLeft(
    BaseNode_ *node) {
  BaseNode_ *rightChild = node->right;

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
typename multiset<T, Compare>::BaseNode_ *multiset<T, Compare>::Balance(
    BaseNode_ *node) {
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
typename multiset<T, Compare>::size_type multiset<T, Compare>::height(
    BaseNode_ *node) {
  return node ? static_cast<Node_ *>(node)->height : 0;
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::FixHeight(BaseNode_ *node) {
  size_type leftHeight = height(node->left);
  size_type rightHeight = height(node->right);

  static_cast<Node_ *>(node)->height = 1 + std::max(leftHeight, rightHeight);
}

template <typename T, template <typename> typename Compare>
void multiset<T, Compare>::heightAdjustment(BaseNode_ *node) {
  node = node->parent;

  BaseNode_ *newRoot = getRoot();

  while (node != fakeNode_) {
    newRoot = Balance(node);

    node = node->parent;
  }

  fakeNode_->left = newRoot;
}

template <typename T, template <typename> typename Compare>
int multiset<T, Compare>::BalanceFactor(BaseNode_ *node) {
  if (!node) return 0;

  return height(node->right) - height(node->left);
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::Node_ *multiset<T, Compare>::getBegin() const {
  if (!size_) return nullptr;

  Node_ *node = getRoot();

  if (node)
    while (node->left != nullptr) node = static_cast<Node_ *>(node->left);

  return node;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::Node_ *multiset<T, Compare>::getEnd() const {
  Node_ *node = getRoot();

  if (node)
    while (node->right != nullptr) node = static_cast<Node_ *>(node->right);

  return node;
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::Node_ *multiset<T, Compare>::getRoot() const {
  return static_cast<Node_ *>(fakeNode_->left);
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::begin() {
  return {getBegin()};
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::iterator multiset<T, Compare>::end() {
  return {fakeNode_};
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::begin()
    const {
  return {getBegin()};
}

template <typename T, template <typename> typename Compare>
typename multiset<T, Compare>::const_iterator multiset<T, Compare>::end()
    const {
  return {fakeNode_};
}
}  // namespace s21