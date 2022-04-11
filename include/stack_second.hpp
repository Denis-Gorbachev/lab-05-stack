// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#ifndef INCLUDE_STACK_SECOND_HPP_
#define INCLUDE_STACK_SECOND_HPP_
#include <utility>
#include <exception>
template <typename T>
class stack_copyable {
 public:
  stack_copyable();
  explicit stack_copyable(const T& a) = delete;
  explicit stack_copyable(T&& a);
  ~stack_copyable();
  auto operator=(const T &a) -> stack_copyable<T>& = delete;
  auto operator=(T &&a) -> stack_copyable<T>&;
  template <typename... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  T pop();
  const T& head() const;

 private:
  struct Node{
    T val;
    Node *next;
  };
  Node *top_node;
};

template <typename T>
stack_copyable<T>::stack_copyable() {
  top_node = new Node;
  top_node->next = nullptr;
}

template <typename T>
stack_copyable<T>::stack_copyable(T&& a) {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
}

template <typename T>
auto stack_copyable<T>::operator=(T&& a) -> stack_copyable<T>& {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
  return *this;
}

template <typename T>
stack_copyable<T>::~stack_copyable() {
  while (top_node->next != nullptr){
    Node *new_node = top_node;
    top_node = top_node->next;
    delete new_node;
  }
  delete top_node;
}

template <typename T>
void stack_copyable<T>::push(T&& value) {
  Node *new_node = new Node{std::forward<T>(value), top_node};
  top_node = new_node;
}

template <typename T>
T stack_copyable<T>::pop() {
  if (top_node == nullptr)
    throw std::exception();
  Node *node = top_node;
  top_node = top_node->next;
  return node->val;
}

template <typename T>
const T& stack_copyable<T>::head() const {
  if (top_node == nullptr)
    throw std::exception();
  return top_node->val;
}

template <typename T>
template <typename ...Args>
void stack_copyable<T>::push_emplace(Args&&... value) {
  for (auto i : {value...}) {
    auto *new_node = top_node;
    top_node = new Node{{i}, new_node};
  }
}

#endif // INCLUDE_STACK_SECOND_HPP_
