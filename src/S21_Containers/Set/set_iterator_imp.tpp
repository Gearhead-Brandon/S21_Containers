#include "s21_set.h"

namespace s21 {
template <typename T, template <typename> typename Compare>
template <bool IsConst>
set<T, Compare>::base_iterator<IsConst>::base_iterator(BaseNode_* node)
    : node_ptr(node), stub() {}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
set<T, Compare>::base_iterator<IsConst>::base_iterator(
    const base_iterator& other)
    : node_ptr(other.node_ptr), stub() {}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
set<T, Compare>::base_iterator<IsConst>&
set<T, Compare>::base_iterator<IsConst>::operator=(const base_iterator& other) {
  node_ptr = other.node_ptr;

  return *this;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
bool set<T, Compare>::base_iterator<IsConst>::operator!=(
    const base_iterator<IsConst>& other) const {
  if (!node_ptr || !other.node_ptr) return false;

  return node_ptr != other.node_ptr;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
bool set<T, Compare>::base_iterator<IsConst>::operator==(
    const base_iterator<IsConst>& other) const {
  if (!node_ptr || !other.node_ptr) return false;

  return node_ptr == other.node_ptr;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
typename set<T, Compare>::base_iterator<IsConst>::ref_type
set<T, Compare>::base_iterator<IsConst>::operator*() const {
  if (!node_ptr || !node_ptr->parent) return const_cast<value_type&>(stub);

  return static_cast<node_type>(node_ptr)->key;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
typename set<T, Compare>::base_iterator<IsConst>&
set<T, Compare>::base_iterator<IsConst>::operator++() {
  if (!node_ptr) return *this;

  if (node_ptr->right) {
    node_ptr = node_ptr->right;

    while (node_ptr->left) node_ptr = node_ptr->left;
  } else {
    BaseNode_* parent = node_ptr->parent;

    while (parent->parent && node_ptr == parent->right) {
      node_ptr = parent;
      parent = parent->parent;
    }

    node_ptr = parent;
  }

  return *this;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
typename set<T, Compare>::base_iterator<IsConst>
set<T, Compare>::base_iterator<IsConst>::operator++(int) {
  if (!node_ptr) return *this;

  base_iterator copy = *this;

  ++(*this);

  return copy;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
typename set<T, Compare>::base_iterator<IsConst>&
set<T, Compare>::base_iterator<IsConst>::operator--() {
  if (!node_ptr) return *this;

  if (node_ptr->left) {
    node_ptr = node_ptr->left;

    while (node_ptr->right) node_ptr = node_ptr->right;
  } else {
    BaseNode_* parent = node_ptr->parent;

    while (parent->parent && node_ptr == parent->left) {
      node_ptr = parent;
      parent = parent->parent;
    }

    node_ptr = parent;
  }

  return *this;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
typename set<T, Compare>::base_iterator<IsConst>
set<T, Compare>::base_iterator<IsConst>::operator--(int) {
  if (!node_ptr) return *this;

  base_iterator copy = *this;

  --(*this);

  return copy;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
set<T, Compare>::base_iterator<IsConst>::operator base_iterator<true>() const {
  return node_ptr;
}
}  // namespace s21