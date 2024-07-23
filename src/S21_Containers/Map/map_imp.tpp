#include "s21_map.h"

template <typename W>
bool ComparatorMap<W>::operator()(const W& a, const W& b) const {
  return a < b;
}

namespace s21 {
template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::BaseNode_::BaseNode_()
    : left(nullptr), right(nullptr), parent(nullptr) {}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::Node_::Node_() : key(), height(0) {}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::Node_::Node_(const value_type& value)
    : key(value.first, value.second), height(1) {}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::Node_::Node_(const key_type& key,
                                   const mapped_type& mapped)
    : key(key, mapped), height(1) {}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::map() : fakeNode_(new BaseNode_), size_(0) {}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::map(std::initializer_list<value_type> const& list)
    : map() {
  for (auto it = list.begin(); it != list.end(); ++it) insert(*it);
}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::map(const map& other) : map() {
  for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::map(map&& other) noexcept : map() {
  swap(other);
}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>::~map() {
  clearTreeRecursive(getRoot());

  delete fakeNode_;
}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>& map<Key, T, Compare>::operator=(const map& other) {
  if (this == &other) return *this;

  map temp(other);

  swap(temp);

  return *this;
}

template <typename Key, typename T, template <typename> typename Compare>
map<Key, T, Compare>& map<Key, T, Compare>::operator=(map&& other) noexcept {
  if (this == &other) return *this;

  map temp(std::move(other));

  swap(temp);

  return *this;
}

template <typename Key, typename T, template <typename> typename Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insert(const value_type& value) {
  Node_* newNode = new Node_(value);

  return insertNode(newNode);
}

template <typename Key, typename T, template <typename> typename Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insert(const key_type& key, const mapped_type& obj) {
  Node_* newNode = new Node_(key, obj);

  return insertNode(newNode);
}

template <typename Key, typename T, template <typename> typename Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insert_or_assign(const key_type& key,
                                       const mapped_type& obj) {
  iterator it = find(key);

  if (it.ptr) {
    static_cast<Node_*>(it.ptr)->key.second = obj;
    return std::make_pair(it, false);
  }

  Node_* newNode = new Node_(key, obj);

  return insertNode(newNode);
}

template <typename Key, typename T, template <typename> typename Compare>
bool map<Key, T, Compare>::contains(const key_type& value) const {
  BaseNode_* current = static_cast<BaseNode_*>(getRoot());

  Node_* content = nullptr;

  while (current != nullptr) {
    content = static_cast<Node_*>(current);

    if (comparator(value, content->key.first, current)) return true;
  }

  return false;
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::erase(iterator pos) {
  if (!pos.ptr || pos.ptr == fakeNode_) return;

  fakeNode_->left = deleteNodeRecursive(getRoot(), *pos);
}

template <typename Key, typename T, template <typename> typename Compare>
bool map<Key, T, Compare>::empty() const noexcept {
  return size_ == 0;
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::size_type map<Key, T, Compare>::size()
    const noexcept {
  return size_;
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::size_type map<Key, T, Compare>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node_);
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::swap(map& other) noexcept {
  std::swap(fakeNode_, other.fakeNode_);
  std::swap(size_, other.size_);
  std::swap(comp_, other.comp_);
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::clear() noexcept {
  if (!size_) return;

  clearTreeRecursive(getRoot());

  fakeNode_->left = nullptr;

  size_ = 0;
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::merge(map& other) {
  if (other.size_ == 0 || this == &other) return;

  mergeBypass(other.getRoot());

  other.size_ = 0;
  other.fakeNode_->left = nullptr;
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::mergeBypass(BaseNode_* node) {
  if (!node) return;

  mergeBypass(node->left);

  mergeBypass(node->right);

  leafNodeTransfer(node);
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::leafNodeTransfer(BaseNode_* node) {
  if (!node->left && !node->right) {
    if (node == node->parent->left) node->parent->left = nullptr;

    if (node == node->parent->right) node->parent->right = nullptr;

    node->parent = nullptr;

    insertNode(static_cast<Node_*>(node));
  }
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::reference map<Key, T, Compare>::at(
    const key_type& key) {
  iterator it = find(key);

  if (!it.ptr) throw std::out_of_range("Key not found");

  return static_cast<Node_*>(it.ptr)->key.second;
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::reference map<Key, T, Compare>::operator[](
    const key_type& key) {
  iterator it = find(key);

  if (it.ptr) return static_cast<Node_*>(it.ptr)->key.second;

  Node_* newNode = new Node_(key, mapped_type());

  return insertNode(newNode).first->second;
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::clearTreeRecursive(BaseNode_* node) {
  if (!node) return;

  clearTreeRecursive(node->left);

  clearTreeRecursive(node->right);

  delete static_cast<Node_*>(node);
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::find(
    const key_type& key) const {
  BaseNode_* current = static_cast<BaseNode_*>(getRoot());

  Node_* content = nullptr;

  while (current != nullptr) {
    content = static_cast<Node_*>(current);

    if (comparator(key, content->key.first, current)) return iterator(content);
  }

  return iterator(nullptr);
}

template <typename Key, typename T, template <typename> typename Compare>
std::pair<typename map<Key, T, Compare>::iterator, bool>
map<Key, T, Compare>::insertNode(Node_* newNode) {
  BaseNode_* current = getRoot();

  iterator it(current);

  if (!current) {
    fakeNode_->left = newNode;
    newNode->parent = fakeNode_;

    it.ptr = newNode;
  } else {
    BaseNode_* parent = current->parent;

    while (current) {
      parent = current;

      it.ptr = parent;

      if (!comparator(newNode->key.first,
                      static_cast<Node_*>(current)->key.first, current,
                      newNode))
        return std::make_pair(it, false);
    }

    if (comp_(newNode->key.first, static_cast<Node_*>(parent)->key.first))
      parent->left = newNode;
    else
      parent->right = newNode;

    newNode->parent = parent;
    it.ptr = newNode;

    heightAdjustment(static_cast<Node_*>(newNode));
  }

  size_++;

  return std::make_pair(it, true);
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::BaseNode_* map<Key, T, Compare>::findMinNode(
    BaseNode_* node) {
  if (node)
    while (node->left) node = static_cast<Node_*>(node->left);

  return node;
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::BaseNode_* map<Key, T, Compare>::detachMinNode(
    BaseNode_* node) {
  if (!node->left) return node->right;

  node->left = detachMinNode(node->left);

  if (node->left) node->left->parent = node;

  return Balance(node);
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::BaseNode_*
map<Key, T, Compare>::deleteNodeRecursive(Node_* node, const value_type& key) {
  if (!node) return nullptr;

  if (comp_(key.first, node->key.first))
    node->left = deleteNodeRecursive(static_cast<Node_*>(node->left), key);
  else if (comp_(node->key.first, key.first))
    node->right = deleteNodeRecursive(static_cast<Node_*>(node->right), key);
  else {
    BaseNode_* left = static_cast<Node_*>(node->left);
    Node_* right = static_cast<Node_*>(node->right);
    Node_* parent = static_cast<Node_*>(node->parent);

    if (parent == fakeNode_) fakeNode_->left = nullptr;

    size_--;

    if (!right) {
      if (left) left->parent = parent;

      delete node;

      return left;
    }

    BaseNode_* min = findMinNode(right);

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

template <typename Key, typename T, template <typename> typename Compare>
bool map<Key, T, Compare>::comparator(const key_type& a, const key_type& b,
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

template <typename Key, typename T, template <typename> typename Compare>
bool map<Key, T, Compare>::comparator(const key_type& a, const key_type& b,
                                      BaseNode_*& current) const {
  if (comp_(a, b))
    current = current->left;
  else if (comp_(b, a))
    current = current->right;
  else
    return true;

  return false;
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::BaseNode_* map<Key, T, Compare>::rotateRight(
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

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::BaseNode_* map<Key, T, Compare>::rotateLeft(
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

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::BaseNode_* map<Key, T, Compare>::Balance(
    BaseNode_* node) {
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

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::size_type map<Key, T, Compare>::height(
    BaseNode_* node) {
  return node ? static_cast<Node_*>(node)->height : 0;
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::FixHeight(BaseNode_* node) {
  size_type leftHeight = height(node->left);
  size_type rightHeight = height(node->right);

  static_cast<Node_*>(node)->height = 1 + std::max(leftHeight, rightHeight);
}

template <typename Key, typename T, template <typename> typename Compare>
void map<Key, T, Compare>::heightAdjustment(BaseNode_* node) {
  node = node->parent;

  BaseNode_* newRoot = getRoot();

  while (node != fakeNode_) {
    newRoot = Balance(node);

    node = node->parent;
  }

  fakeNode_->left = newRoot;
}

template <typename Key, typename T, template <typename> typename Compare>
int map<Key, T, Compare>::BalanceFactor(BaseNode_* node) {
  if (!node) return 0;

  return height(node->right) - height(node->left);
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::Node_* map<Key, T, Compare>::getBegin() const {
  if (!size_) return nullptr;

  Node_* node = getRoot();

  if (node)
    while (node->left != nullptr) node = static_cast<Node_*>(node->left);

  return node;
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::Node_* map<Key, T, Compare>::getRoot() const {
  return static_cast<Node_*>(fakeNode_->left);
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::begin() {
  return {getBegin()};
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::iterator map<Key, T, Compare>::end() {
  return {fakeNode_};
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::begin()
    const {
  return {getBegin()};
}

template <typename Key, typename T, template <typename> typename Compare>
typename map<Key, T, Compare>::const_iterator map<Key, T, Compare>::end()
    const {
  return {fakeNode_};
}
}  // namespace s21