// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#ifndef INCLUDE_STACK_FIRST_HPP_
#define INCLUDE_STACK_FIRST_HPP_
#include <utility>
#include <stdexcept>

template <typename T>
class stack {
 public:
  stack();
  explicit stack(const T& a) = delete;
  explicit stack(T&& a);
  ~stack();
  auto operator=(const T &a) -> stack<T>& = delete;
  auto operator=(T &&a) -> stack<T>&;
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
stack<T>::stack() {
  top_node = new Node;
  top_node->next = nullptr;
}

template <typename T>
stack<T>::stack(T&& a) {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
}

template <typename T>
auto stack<T>::operator=(T&& a) -> stack<T>& {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
  return *this;
}

template <typename T>
stack<T>::~stack() {
  while (top_node->next != nullptr){
    Node *new_node = top_node;
    top_node = top_node->next;
    delete new_node;
  }
  delete top_node;
}

template <typename T>
void stack<T>::push(const T& value) {
  Node *new_node = new Node{std::move(value), top_node};
  top_node = new_node;
}

template <typename T>
void stack<T>::push(T&& value) {
  Node *new_node = new Node{value, top_node};
  top_node = new_node;
}

template <typename T>
void stack<T>::pop() {
  if (top_node == nullptr)
    throw std::runtime_error("stack is empty");
  Node *node = top_node;
  top_node = top_node->next;
  delete node->next;
  delete node;
}

template <typename T>
const T& stack<T>::head() const {
  if (top_node == nullptr)
    throw std::runtime_error("stack is empty");
  return top_node->val;
}

#endif  // INCLUDE_STACK_FIRST_HPP_
