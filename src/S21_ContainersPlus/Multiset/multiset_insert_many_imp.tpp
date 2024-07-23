#include "s21_multiset.h"

namespace s21 {
template <typename T, template <typename> typename Compare>
template <typename... Args>
s21::vector<std::pair<typename multiset<T, Compare>::iterator, bool>>
multiset<T, Compare>::insert_many(Args&&... args) {
  s21::vector<std::pair<typename multiset<T, Compare>::iterator, bool>> result;

  if (sizeof...(args) < 1) return result;

  (result.push_back(
       std::make_pair<iterator, bool>(insert(std::forward<Args>(args)), true)),
   ...);

  return result;
}
}  // namespace s21