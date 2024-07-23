#include "s21_vector.h"

namespace s21 {
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  size_type package_size = sizeof...(args);

  if (package_size < 1) return const_cast<value_type*>(pos.ptr);

  iterator p(const_cast<value_type*>(pos.ptr));

  p = insert_many_helper(p, std::forward<Args>(args)...);

  return p - package_size;
}

template <typename T>
template <typename Arg, typename... Args>
typename vector<T>::iterator vector<T>::insert_many_helper(iterator p,
                                                           Arg&& arg,
                                                           Args&&... args) {
  p = insert(p, std::forward<Arg>(arg));

  return insert_many_helper(++p, std::forward<Args>(args)...);
}

template <typename T>
typename vector<T>::iterator vector<T>::insert_many_helper(iterator p) {
  return p;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  if (sizeof...(args) < 1) return;

  (push_back(std::forward<Args>(args)), ...);
}
}  // namespace s21