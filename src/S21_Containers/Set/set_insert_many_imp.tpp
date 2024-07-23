#include "s21_set.h"

namespace s21 {
template <typename T, template <typename> typename Compare>
template <typename... Args>
s21::vector<std::pair<typename set<T, Compare>::iterator, bool>>
set<T, Compare>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> result;

  if (sizeof...(args) < 1) return result;

  (result.push_back(insert(std::forward<Args>(args))), ...);

  return result;
}
}  // namespace s21