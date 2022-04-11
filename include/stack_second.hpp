// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#ifndef INCLUDE_STACK_SECOND_HPP_
#define INCLUDE_STACK_SECOND_HPP_
#include <utility>

template <typename T>
class Stack {
 public:
  Stack();
  explicit Stack(const T& a) = delete;
  explicit Stack(T&& a);
  ~Stack();
  auto operator=(const T &a) -> Stack<T>& = delete;
  auto operator=(T &&a) -> Stack<T>&;
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
Stack<T>::Stack() {
  top_node = new Node;
  top_node->next = nullptr;
}

template <typename T>
Stack<T>::Stack(T&& a) {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
}

template <typename T>
auto Stack<T>::operator=(T&& a) -> Stack<T>& {
  top_node = new Node;
  top_node->val = a;
  top_node->next = nullptr;
  return *this;
}

template <typename T>
Stack<T>::~Stack() {
  while (top_node->next != nullptr){
    Node *new_node = top_node;
    top_node = top_node->next;
    delete new_node;
  }
  delete top_node;
}

template <typename T>
void Stack<T>::push(T&& value) {
  Node *new_node = new Node{std::forward<T>(value), top_node};
//  new_node->val = value;
//  new_node->next = top_node;
  top_node = new_node;
}

template <typename T>
T Stack<T>::pop() {
  if (top_node == nullptr)
    throw std::runtime_error("stack is empty");
  Node *node = top_node;
  top_node = top_node->next;
  return node->val;
}

template <typename T>
const T& Stack<T>::head() const {
  const std::string s = "stack is empty";
  if (top_node == nullptr)
    throw std::runtime_error(s);
  return top_node->val;
}

template <typename T>
template <typename ...Args>
void Stack<T>::push_emplace(Args&&... value) {
  auto *new_node = top_node;
  top_node = new Node{std::forward<Args>(value)..., new_node};
}

#endif // INCLUDE_STACK_SECOND_HPP_
