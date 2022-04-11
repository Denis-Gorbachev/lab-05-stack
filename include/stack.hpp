// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_
#include <stdexcept>
template <typename T>
class Stack{
 public:
  template <typename... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;

 private:
  T* stack  = new T[0];
  int size  = 0;
};

template <typename T>
void Stack<T>::push(T&& value){
  size++;
  T* new_stack = new T[size];
  for (int i = 0; i < size - 1; i++){
    new_stack[i] = stack[i];
  }
  new_stack[size-1] = value;
  for (int i = 0; i < size; ++i){
    stack[i] = new_stack[i];
  }
  delete[] new_stack;
}

template <typename T>
void Stack<T>::push(const T& value) {
  size++;
  T* new_stack = new T[size];
  for (int i = 0; i < size - 1; i++){
    new_stack[i] = stack[i];
  }
  new_stack[size-1] = value;
  for (int i = 0; i < size; ++i){
    stack[i] = new_stack[i];
  }
  delete[] new_stack;
}

template <typename T>
void Stack<T>::pop() {
  if (stack == nullptr)
    throw std::runtime_error("Stack is empty");
  size--;
  T* new_stack = new T[size];
  for (int i = 0; i < size; i++){
    new_stack[i] = stack[i];
  }
  for (int i = 0; i < size; ++i){
    stack[i] = new_stack[i];
  }
  delete[] new_stack;
}

template <typename T>
const T& Stack<T>::head() const {
  return stack[size-1];
}

template <typename T>
template <typename ...Args>
void Stack<T>::push_emplace(Args&&... value) {
  int arg_size = sizeof...(Args);
  T* new_stack = new T[size + arg_size];
  T* args_stack = new T[arg_size] {value...};
  for (int i = 0; i < size; ++i){
    new_stack[i] = stack[i];
  }
  for (int i = size; i < size + arg_size; ++i){
    new_stack[i] = args_stack[i - size];
  }
  delete[] args_stack;
  size += sizeof...(Args);
  for (int i = 0; i < size; ++i){
    stack[i] = new_stack[i];
  }
  delete[] new_stack;
}

#endif // INCLUDE_STACK_HPP_
