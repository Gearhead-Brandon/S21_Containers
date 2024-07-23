#include "s21_multiset.h"

namespace s21 {
template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>::base_iterator()
    : ptr(nullptr), stub() {}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>::base_iterator(BaseNode_ *node)
    : ptr(node), stub() {}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>::base_iterator(
    const base_iterator &other)
    : ptr(other.ptr), stub() {}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>
    &multiset<T, Compare>::base_iterator<IsConst>::operator=(
        const base_iterator &other) {
  ptr = other.ptr;

  return *this;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
bool multiset<T, Compare>::base_iterator<IsConst>::operator!=(
    const base_iterator<IsConst> &other) const {
  if (!ptr || !other.ptr) return false;

  return ptr != other.ptr;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
bool multiset<T, Compare>::base_iterator<IsConst>::operator==(
    const base_iterator<IsConst> &other) const {
  if (!ptr || !other.ptr) return false;

  return ptr == other.ptr;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
typename multiset<T, Compare>::base_iterator<IsConst>::ref_type
multiset<T, Compare>::base_iterator<IsConst>::operator*() const {
  if (!ptr || !ptr->parent) return const_cast<key_type &>(stub);

  return static_cast<node_type>(ptr)->key;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>
    &multiset<T, Compare>::base_iterator<IsConst>::operator++() {
  if (!ptr) return *this;

  if (ptr->right) {
    ptr = ptr->right;

    while (ptr->left) ptr = ptr->left;
  } else {
    BaseNode_ *parent = ptr->parent;

    while (parent->parent && ptr == parent->right) {
      ptr = parent;
      parent = parent->parent;
    }

    ptr = parent;
  }

  return *this;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>
multiset<T, Compare>::base_iterator<IsConst>::operator++(int) {
  if (!ptr) return *this;

  base_iterator copy = *this;

  ++(*this);

  return copy;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>
    &multiset<T, Compare>::base_iterator<IsConst>::operator--() {
  if (!ptr) return *this;

  if (ptr->left) {
    ptr = ptr->left;

    while (ptr->right) ptr = ptr->right;
  } else {
    BaseNode_ *parent = ptr->parent;

    while (parent->parent && ptr == parent->left) {
      ptr = parent;
      parent = parent->parent;
    }

    ptr = parent;
  }

  return *this;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>
multiset<T, Compare>::base_iterator<IsConst>::operator--(int) {
  if (!ptr) return *this;

  base_iterator copy = *this;

  --(*this);

  return copy;
}

template <typename T, template <typename> typename Compare>
template <bool IsConst>
multiset<T, Compare>::base_iterator<IsConst>::operator base_iterator<true>()
    const {
  return ptr;
}
}  // namespace s21