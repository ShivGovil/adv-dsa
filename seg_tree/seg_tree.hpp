#ifndef seg_tree_HPP
#define seg_tree_HPP

#include <cstddef>
#include <cstring>
#include <vector>

class seg_tree {
  public:
    seg_tree(std::vector<int> &data) : N(data.size()) {
      tree.resize(N << 1);
      std::memcpy(&tree[N], data.data(), N * sizeof(int));
      for (size_t i = N - 1; i > 0; --i) {
        tree[i] = tree[i << 1] + tree[(i << 1) + 1];
      }
    }

    [[nodiscard]] int query(size_t l, size_t r) const {
      int res = 0;
      for (l += N, r += N; l < r; l /= 2, r /= 2) {
        if (l % 2) { res += tree[l++]; }
        if (r % 2) { res += tree[--r]; }
      }
      return res;
    }

    void update_index(size_t index, int value) {
      index += N;
      int delta = value - tree[index];
      while (index > 0) {
        tree[index] += delta;
        index /= 2;
      }
    }

  private:
    size_t N;
    std::vector<int> tree;
};

#endif
