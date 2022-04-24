// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#ifndef INCLUDE_STACK_FIRST_HPP_
#define INCLUDE_STACK_FIRST_HPP_
#include <utility>
#include <exception>
template <typename T>
class stack_not_copyable {
 public:
  stack_not_copyable() = default;
  stack_not_copyable(const stack_not_copyable& a) = delete;
  stack_not_copyable(stack_not_copyable&& a) noexcept = default;
  ~stack_not_copyable();
  auto operator=(const stack_not_copyable &a)
      -> stack_not_copyable<T>& = delete;
  auto operator=(stack_not_copyable &&a)  noexcept
      -> stack_not_copyable<T>& = default;
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;

 private:
  struct Node{
    T val;
    Node *next = nullptr;
  };
  Node *top_node = nullptr;
};

template <typename T>
stack_not_copyable<T>::~stack_not_copyable() {
  while (top_node){
    Node *new_node = top_node;
    top_node = top_node->next;
    delete new_node;
  }
}

template <typename T>
void stack_not_copyable<T>::push(const T& value) {
  Node *new_node = new Node{std::move(value), top_node};
  top_node = new_node;
}

template <typename T>
void stack_not_copyable<T>::push(T&& value) {
  Node *new_node = new Node{std::forward<T>(value), top_node};
  top_node = new_node;
}

template <typename T>
void stack_not_copyable<T>::pop() {
  if (top_node == nullptr)
    throw std::exception();
  top_node = top_node->next;
}

template <typename T>
const T& stack_not_copyable<T>::head() const {
  if (top_node == nullptr)
    throw std::exception();
  return top_node->val;
}

#endif  // INCLUDE_STACK_FIRST_HPP_
