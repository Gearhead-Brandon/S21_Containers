#include "s21_queue.h"

namespace s21 {
template <typename T, template <typename> typename Container>
queue<T, Container>::queue() : Container_() {}

template <typename T, template <typename> typename Container>
queue<T, Container>::queue(std::initializer_list<T> const& items)
    : Container_(items) {}

template <typename T, template <typename> typename Container>
queue<T, Container>::queue(const queue& other) : Container_(other.Container_) {}

template <typename T, template <typename> typename Container>
queue<T, Container>::queue(queue&& other) noexcept
    : Container_(std::move(other.Container_)) {}

template <typename T, template <typename> typename Container>
queue<T, Container>::~queue() {}

template <typename T, template <typename> typename Container>
queue<T, Container>& queue<T, Container>::operator=(const queue& other) {
  if (this != &other) Container_ = other.Container_;

  return *this;
}

template <typename T, template <typename> typename Container>
queue<T, Container>& queue<T, Container>::operator=(queue&& other) noexcept {
  if (this != &other) Container_ = std::move(other.Container_);

  return *this;
}

template <typename T, template <typename> typename Container>
void queue<T, Container>::push(const_reference value) {
  Container_.push_back(value);
}

template <typename T, template <typename> typename Container>
void queue<T, Container>::pop() {
  Container_.pop_front();
}

template <typename T, template <typename> typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::front()
    const noexcept {
  return Container_.front();
}

template <typename T, template <typename> typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::back()
    const noexcept {
  return Container_.back();
}

template <typename T, template <typename> typename Container>
void queue<T, Container>::swap(queue& other) noexcept {
  Container_.swap(other.Container_);
}

template <typename T, template <typename> typename Container>
typename queue<T, Container>::size_type queue<T, Container>::size()
    const noexcept {
  return Container_.size();
}

template <typename T, template <typename> typename Container>
bool queue<T, Container>::empty() const noexcept {
  return Container_.empty();
}
}  // namespace s21