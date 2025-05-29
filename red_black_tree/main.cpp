#include "red_black_tree.hpp"
#include <cassert>
#include <iostream>

int main() {
  shiv::red_black_tree<size_t> tree;
  for (size_t i = 0; i < 100; ++i) {
    tree.insert(i);
  }

  for (size_t i = 0; i < 100; ++i) {
    assert(tree.find(rand() % 100)->key == i);
  }

  std::cout << "noice\n";

  return 0;
}
