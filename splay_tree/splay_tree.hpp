#pragma once

#include <cstddef>
#include <functional>

template <typename T, typename Comp = std::less<T>>
class splay_tree {
  struct node {
    T key;
    node *left, *right, *parent;
  };

  node *root;
  size_t sz{};

  node* min_in_tree(node *root) {
    while (root) root = root->left;
    return root;
  }
  
  node* max_in_tree(node *root) {
    while (root) root = root->right;
    return root;
  }

  void rotate_left(node *x);
  void rotate_right(node *x);

  void replace(node *x, node *y);

  void splay(node *x);

public:
  void insert(const T &key);
  node* find(const T &key);
  void erase(const T &key);
  node* join(node *first, node *second);
  std::pair<node*, node*> split(node *root);
  
  const T& maximum(const T &key) const { return max_in_tree(key)->val; }
  const T& minimum(const T &key) const { return min_in_tree(key)->val; }
  size_t size() { return sz; }
  bool empty() { return !root; }
};
