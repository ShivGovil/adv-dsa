#include "splay_tree.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>

int main() {
  shiv::splay_tree<int> st;
  for (auto i = 0; i < 50; ++i) {
    st.insert(std::rand() % 100);
  }

  assert(!st.empty());

  for (size_t i = 0; i < st.size(); ++i) {
    std::cout << st.maximum() << '\n';
  }

  return 0;
}
