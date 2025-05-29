#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>

namespace shiv {

enum class color : uint8_t {
  BLACK = 0,
  RED = 1
};

template<typename T>
class red_black_tree {
  struct node {
    node *parent, *left, *right;
    color c;
    T key;
  };

  node *root{};

  void delete_nodes(node *root) {
    if (!root) return;
    delete_nodes(root->children.lr.left);
    delete_nodes(root->children.lr.right);
    delete root;
  }

  void rotate_right() {}

  void rotate_left() {}

  void fix_insert(node *x) {}

public:
  red_black_tree() = default;
  ~red_black_tree() { delete_nodes(root); }

  void insert(const T &key) {}

  void erase(const T &key) {}

  node* find(const T &key) {}

  void clear() {
    delete_nodes(root);
    root = nullptr;
  }

};

} // namespace
