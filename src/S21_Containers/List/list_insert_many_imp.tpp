#include "s21_list.h"

namespace s21 {
template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator p(const_cast<BaseNode_*>(pos.ptr));
  iterator it = p;

  if (sizeof...(args) < 1) return it;

  ((it = insert(p, std::forward<Args>(args))), ...);

  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  if (sizeof...(args) < 1) return;

  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  if (sizeof...(args) < 1) return;

  (push_front(std::forward<Args>(args)), ...);
}
}  // namespace s21