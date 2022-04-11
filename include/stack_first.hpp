// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#ifndef INCLUDE_STACK_FIRST_HPP_
#define INCLUDE_STACK_FIRST_HPP_
#include <utility>
#include <exception>
template <typename T>
class stack_not_copyable {
 public:
  stack_not_copyable();
  explicit stack_not_copyable(const T& a) = delete;
  explicit stack_not_copyable(T&& a);
  ~stack_not_copyable();
  auto operator=(const T &a) -> stack_not_copyable<T>& = delete;
  auto operator=(T &&a) -> stack_not_copyable<T>&;
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;

 private:
  struct Node{
    T val;
    Node *next;
  };
  Node *top_node = nullptr;
};

template <typename T>
stack_not_copyable<T>::stack_not_copyable() {
  top_node = new Node;
  top_node->next = nullptr;
}

template <typename T>
stack_not_copyable<T>::stack_not_copyable(T&& a) {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
}

template <typename T>
auto stack_not_copyable<T>::operator=(T&& a) -> stack_not_copyable<T>& {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
  return *this;
}

template <typename T>
stack_not_copyable<T>::~stack_not_copyable() {
  while (top_node->next != nullptr){
    Node *new_node = top_node;
    top_node = top_node->next;
    delete new_node;
  }
  delete top_node;
}

template <typename T>
void stack_not_copyable<T>::push(const T& value) {
  Node *new_node = new Node{std::move(value), top_node};
  top_node = new_node;
}

template <typename T>
void stack_not_copyable<T>::push(T&& value) {
  Node *new_node = new Node{value, top_node};
  top_node = new_node;
}

template <typename T>
void stack_not_copyable<T>::pop() {
  if (top_node == nullptr)
    throw std::exception();
  Node *node = top_node;
  top_node = top_node->next;
  delete node->next;
  delete node;
}

template <typename T>
const T& stack_not_copyable<T>::head() const {
  if (top_node == nullptr)
    throw std::exception();
  return top_node->val;
}

#endif  // INCLUDE_STACK_FIRST_HPP_
