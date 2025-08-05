#include "dynarray.hpp"
#include "test.hpp"
#include <array>
#include <spanstream>
#include <vector>
#include <span>

void test_size_constructor() {
  DynArray<int> arr(5);
  ASSERT_EQ(arr.size(), 5);
}

void test_pointer_constructor() {
  int data[] = {1, 2, 3, 4, 5};
  DynArray<int> arr(data, 5);
  ASSERT_EQ(arr.size(), 5);
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_EQ(arr[i], data[i]);
  }
}

void test_initializer_list_constructor() {
  DynArray<int> arr({1, 2, 3, 4, 5});
  ASSERT_EQ(arr.size(), 5);
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_EQ(arr[i], static_cast<int>(i + 1));
  }
}

void test_copy_constructor() {
  DynArray<int> original({1, 2, 3});
  DynArray<int> copy(original);
  ASSERT_EQ(original.size(), copy.size());
  for (size_t i = 0; i < original.size(); ++i) {
    ASSERT_EQ(original[i], copy[i]);
  }
}

void test_move_constructor() {
  DynArray<int> original({1, 2, 3});
  DynArray<int> moved(std::move(original));
  ASSERT_EQ(moved.size(), 3);
  ASSERT_EQ(original.size(), 0);
  ASSERT_EQ(original.data(), nullptr);
}

void test_copy_assignment() {
  DynArray<int> original({1, 2, 3});
  DynArray<int> copy(5);
  copy = original;
  ASSERT_EQ(original.size(), copy.size());
  for (size_t i = 0; i < original.size(); ++i) {
    ASSERT_EQ(original[i], copy[i]);
  }
}

void test_move_assignment() {
  DynArray<int> original({1, 2, 3});
  DynArray<int> moved(5);
  moved = std::move(original);
  ASSERT_EQ(moved.size(), 3);
  ASSERT_EQ(original.size(), 0);
  ASSERT_EQ(original.data(), nullptr);
}

void test_at_operator() {
  DynArray<int> arr({1, 2, 3});
  ASSERT_EQ(arr.at(0), 1);
  ASSERT_EQ(arr.at(1), 2);
  ASSERT_EQ(arr.at(2), 3);
  ASSERT_THROW(arr.at(3), std::out_of_range);
}

void test_bracket_operator() {
  DynArray<int> arr({1, 2, 3});
  ASSERT_EQ(arr[0], 1);
  ASSERT_EQ(arr[1], 2);
  ASSERT_EQ(arr[2], 3);
  arr[0] = 10;
  ASSERT_EQ(arr[0], 10);
}

void test_iterators() {
  DynArray<int> arr({1, 2, 3, 4, 5});
  std::vector<int> vec;
  for (const auto &item : arr) {
    vec.push_back(item);
  }
  ASSERT_EQ(vec.size(), 5);
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_EQ(vec[i], static_cast<int>(i + 1));
  }
}

void test_const_iterators() {
  const DynArray<int> arr({1, 2, 3, 4, 5});
  std::vector<int> vec;
  for (const auto &item : arr) {
    vec.push_back(item);
  }
  ASSERT_EQ(vec.size(), 5);
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_EQ(vec[i], static_cast<int>(i + 1));
  }
}

void test_data() {
  DynArray<int> arr({1, 2, 3});
  int *p = arr.data();
  ASSERT_EQ(*p, 1);
  *(p + 1) = 10;
  ASSERT_EQ(arr[1], 10);
}

void test_span_view() {
  DynArray<int> dyn({1, 2, 3, 4, 5});

  std::span<int> s = dyn.span();
  
  int i = 1;
  for (int& j : s) {
    ASSERT_EQ(i, j);
    i++;
  }
}

void test_span_constructor() {
    std::array<int, 5> arr({1, 2, 3, 4, 5});
    std::span<int> sp = std::span(arr);
    DynArray<int> dyn(sp);

    int i = 1;
    for (int& j : dyn) {
      ASSERT_EQ(i, j);
      i++;
    }
}

int main() {
    run_test(test_size_constructor, "Size constructor");
    run_test(test_pointer_constructor, "Pointer constructor");
    run_test(test_initializer_list_constructor, "Initializer list constructor");
    run_test(test_copy_constructor, "Copy constructor");
    run_test(test_move_constructor, "Move constructor");
    run_test(test_copy_assignment, "Copy assignment");
    run_test(test_move_assignment, "Move assignment");
    run_test(test_at_operator, "at() operator");
    run_test(test_bracket_operator, "[] operator");
    run_test(test_iterators, "Iterators");
    run_test(test_const_iterators, "Const iterators");
    run_test(test_data, "data()");
    run_test(test_span_view, "Span view method");
    run_test(test_span_constructor, "Span constructor");

    return EXIT_SUCCESS;
}
