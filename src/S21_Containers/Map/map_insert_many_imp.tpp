#include "s21_map.h"

namespace s21 {

template <typename Key, typename T, template <typename> typename Compare>
template <typename... Args>

s21::vector<std::pair<typename map<Key, T, Compare>::iterator, bool>>
map<Key, T, Compare>::insert_many(Args&&... args) {
  s21::vector<std::pair<typename map<Key, T, Compare>::iterator, bool>> result;

  if (sizeof...(args) < 1) return result;

  (result.push_back(insert(std::forward<Args>(args))), ...);

  return result;
}
}  // namespace s21