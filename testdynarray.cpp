#include <cstdlib>
#include <print>

#include "dynarray.hpp"

template <typename T>
void printdyn(DynArray<T> dyn) {
  for (const auto n : dyn) {
    std::print("{} ", n);
  }
  std::println();
}

int main() {
  DynArray<int> dyn(5);

  dyn[0] = 1;
  dyn[1] = 2;
  dyn[2] = 3;
  dyn[3] = 4;
  dyn[4] = 5;

  printdyn(dyn);

  int arr[] = {6, 7, 8, 9, 10};
  DynArray<int> dyn2(arr, 5);
  printdyn(dyn2);

  DynArray<int> dyn3({11, 12, 13, 14, 15});
  printdyn(dyn3);

  return EXIT_SUCCESS;
}
