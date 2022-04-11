// Copyright 2022 Denis Gorbachev <denis.gorbachev2002@yandex.ru>

#include <stdexcept>
#include <gtest/gtest.h>
#include <stack_second.hpp>
#include <stack_first.hpp>
class StackTest{
 public:
  struct Copyable {
    Copyable() = default;
    Copyable(const Copyable &) = default;
    Copyable(Copyable &&) = default;

    int value = 0;
  };
  struct NotCopyable {
    NotCopyable() = default;
    NotCopyable(const NotCopyable &) = delete;
    NotCopyable(NotCopyable &&) = default;

    int value = 0;
  };
};
stack_not_copyable<StackTest::Copyable> copyableStack{};
stack_not_copyable<StackTest::Copyable> copyableStackEmpty{};
stack_copyable<StackTest::NotCopyable> notCopyableStack{};
stack_copyable<StackTest::NotCopyable> notCopyableStackEmpty{};
  stack_not_copyable<std::string> stringStackEmpty{};
  void SetUp()
  {
    copyableStack.push({1});
    copyableStack.push({2});
    copyableStack.push({3});
    copyableStack.push({4});
    copyableStack.push({5});

    notCopyableStack.push({1});
    notCopyableStack.push({2});
    notCopyableStack.push({3});
    notCopyableStack.push({4});
    notCopyableStack.push({5});
  }

TEST(StackFixture, TestForTest)
{
  EXPECT_EQ(std::is_move_constructible_v<StackTest::Copyable>, true);
  EXPECT_EQ(std::is_copy_constructible_v<StackTest::Copyable>, true);
  EXPECT_EQ(std::is_move_constructible_v<StackTest::NotCopyable>, true);
  EXPECT_EQ(std::is_copy_constructible_v<StackTest::NotCopyable>, false);
}

TEST(constructor_tests, default_constructor) {
  EXPECT_EQ(copyableStackEmpty.head().value, NULL);
}

TEST(StackFixture, PushMove)
{
  std::string string{"I am a string"};
  stringStackEmpty.push(std::move(string));
  EXPECT_EQ(stringStackEmpty.head(), std::string{"I am a string"});
}

TEST(StackFixture, PushCopy)
{
  StackTest::Copyable copyable{60};
  copyableStackEmpty.push(copyable);
  EXPECT_EQ(copyableStackEmpty.head().value, 60);
}

TEST(StackFixture, PushEmplace)
{
  notCopyableStackEmpty.push_emplace(1, 2, 3, 600);
  EXPECT_EQ(notCopyableStackEmpty.head().value, 600);
}

TEST(StackFixture, PopSfinaeNotCopy)
{
  using PopType = decltype(notCopyableStack.pop());
  constexpr bool isSame = std::is_same_v<PopType, StackTest::NotCopyable>;
  EXPECT_EQ(isSame, true);
}

TEST(StackFixture, PopSfinaeCopy)
{
  using PopType = decltype(copyableStack.pop());
  constexpr bool isSame = std::is_same_v<PopType, void>;
  EXPECT_EQ(isSame, true);
}

TEST(StackFixture, PopCopy)
{
  ::SetUp();
  EXPECT_EQ(copyableStack.head().value, 5);
  copyableStack.pop();
  EXPECT_EQ(copyableStack.head().value, 4);
}

TEST(StackFixture, Head)
{
  ::SetUp();
  EXPECT_EQ(copyableStack.head().value, 5);
}
