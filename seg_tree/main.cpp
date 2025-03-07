// Taken from Traders at Michigan segment tree implementation

#include "seg_tree.hpp"
#include <iostream>
#include <numeric>

void test(seg_tree& st, std::vector<int>& data, int l, int r) {
  static int test_num = 1;
  int actual = std::accumulate(data.begin() + l, data.begin() + r, 0);
  int observed = st.query(l, r);
  if (actual == observed) {
    std::cout << "Test num " << test_num << " passed\n";
  } else {
    std::cout << "FAILED TEST " << test_num << '\n';
    std::cout << "EXPECTED: " << actual << " GOT: " << observed << '\n';
  }
  ++test_num;
}

int main() {
  std::vector<int> data = {0, 1, 2, 3, 4, 5, 6};
  seg_tree st(data);

  test(st, data, 0, 7);
  test(st, data, 3, 5);
  test(st, data, 2, 6);
  test(st, data, 1, 4);

  st.update_index(1, 10);
  // syncing the vector to match the segment tree
  data[1] = 10;

  test(st, data, 0, 7);
  test(st, data, 3, 5);
  test(st, data, 2, 6);
  test(st, data, 1, 4);
}
