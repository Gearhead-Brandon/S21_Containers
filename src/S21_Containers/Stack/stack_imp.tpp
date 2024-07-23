#include "s21_stack.h"

namespace s21 {
template <typename T, template <typename> typename Container>
stack<T, Container>::stack() : Container_() {}

template <typename T, template <typename> typename Container>
stack<T, Container>::stack(std::initializer_list<T> const& items)
    : Container_(items) {}

template <typename T, template <typename> typename Container>
stack<T, Container>::stack(const stack& other) : Container_(other.Container_) {}

template <typename T, template <typename> typename Container>
stack<T, Container>::stack(stack&& other) noexcept
    : Container_(std::move(other.Container_)) {}

template <typename T, template <typename> typename Container>
stack<T, Container>::~stack() {}

template <typename T, template <typename> typename Container>
stack<T, Container>& stack<T, Container>::operator=(const stack& other) {
  Container_ = other.Container_;

  return *this;
}

template <typename T, template <typename> typename Container>
stack<T, Container>& stack<T, Container>::operator=(stack&& other) noexcept {
  Container_ = std::move(other.Container_);

  return *this;
}

template <typename T, template <typename> typename Container>
void stack<T, Container>::push(const_reference value) {
  Container_.push_front(value);
}

template <typename T, template <typename> typename Container>
void stack<T, Container>::pop() {
  Container_.pop_front();
}

template <typename T, template <typename> typename Container>
typename stack<T, Container>::const_reference stack<T, Container>::top()
    const noexcept {
  return Container_.front();
}

template <typename T, template <typename> typename Container>
void stack<T, Container>::swap(stack& other) noexcept {
  Container_.swap(other.Container_);
}

template <typename T, template <typename> typename Container>
typename stack<T, Container>::size_type stack<T, Container>::size()
    const noexcept {
  return Container_.size();
}

template <typename T, template <typename> typename Container>
bool stack<T, Container>::empty() const noexcept {
  return Container_.empty();
}
}  // namespace s21