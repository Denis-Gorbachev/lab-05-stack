// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#include <stdexcept>

#include <gtest/gtest.h>

#include "stack.hpp"

TEST(method_tests, r_push) {
  Stack<int> stack;
  stack.push(7);
  EXPECT_EQ(stack.head(), 7);
}
TEST(method_tests, push_emplace) {
  Stack<int> stack;
  stack.push_emplace(1, 2, 3, 4);
  EXPECT_EQ(stack.head(), 4);
}
TEST(method_tests, pop) {
  Stack<int> stack;
  stack.push_emplace(1, 2);
  stack.pop();
  EXPECT_EQ(stack.head(), 1);
}
TEST(method_tests, l_push) {
  Stack<int> stack;
  int a = 1;
  stack.push(a);
  EXPECT_EQ(stack.head(), 1);
}
TEST(exeption_tests, empty_stack) {
  Stack<int> stack;
  EXPECT_ANY_THROW(stack.pop());
}