#include "s21_queue.h"

namespace s21 {
template <typename T, template <typename> typename Container>
template <typename... Args>
void queue<T, Container>::insert_many_back(Args&&... args) {
  if (sizeof...(args) < 1) return;

  (Container_.push_back(std::forward<Args>(args)), ...);
}
}  // namespace s21