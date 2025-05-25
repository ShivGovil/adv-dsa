#pragma once

#include <cstddef>
#include <functional>

namespace shiv {

template <typename T, typename Comp = std::less<T>>
class splay_tree {
  Comp comp;

  struct node {
    T key;
    node *left, *right, *parent;
  };

  node *root{};
  size_t sz{};

  void destroy_nodes(node *root) {
    if (!root) return;
    destroy_nodes(root->left);
    destroy_nodes(root->right);
    delete root;
  }

  node* min_in_tree(node *root) {
    while (root) root = root->left;
    return root;
  }
  
  node* max_in_tree(node *root) {
    while (root) root = root->right;
    return root;
  }

  void rotate_left(node *x) {
    node *y = x->right;
    if (y) {
      x->right = y->left;
      if (y->left) y->left->parent = x;
      y->parent = x->parent;
    }
    
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    if (y) y->left = x;
    x->parent = y;
  }

  void rotate_right(node *x) {
    node *y = x->left;
    if (y) {
      x->left = y->right;
      if (y->right) y->right->parent = x;
      y->parent = x->parent;
    }

    if (!x->parent) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;

    if (y) y->right = x;
    x->parent = y;
  }

  void replace(node *x, node *y) {
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    if (y) y->parent = x->parent;
  }

  void splay(node *x) {
    while (x->parent) {
      if (!x->parent->parent) {
        if (x->parent->left == x) rotate_right(x->parent);
        else rotate_left(x->parent);
      } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
        rotate_right(x->parent->parent);
        rotate_right(x->parent);
      } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
        rotate_left(x->parent->parent);
        rotate_left(x->parent);
      } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
        rotate_right(x->parent);
        rotate_left(x->parent);
      } else {
        rotate_left(x->parent);
        rotate_right(x->parent);
      }
    }
  }

public:
  void insert(const T &key) {
    node *r = root;
    node *seek = nullptr;

    while (r) {
      seek = r;
      if (comp(r->key, key)) r = r->right;
      else if (comp(key, r->key)) r = r->left;
      else {
        splay(r);
        return;
      }
    }

    r = new node{.key = key};
    r->parent = seek;

    if (!seek) {
      root = r;
    } else if (comp(seek->key, r->key)) {
      seek->right = r;
    } else {
      seek->left = r;
    }

    splay(r);
    ++sz;
  }

  node* find(const T &key) {
    node *seek = root;
    while (seek) {
      if (comp(seek->key, key)) seek = seek->right;
      else if (comp(key, seek->key)) seek = seek->left;
      else return seek;
    }
    return nullptr;
  }

  void erase(const T &key) {
    node *k = find(key);
    if (!k) return;

    // Split
    splay(k);
    node *left = k->left;
    node *right = k->right;
    delete k;

    // Join
    node *left_max{};
    if (left) {
      left->parent = nullptr;
      left_max = max_in_tree(left);
      splay(left_max);
      root = left_max;
    }

    if (right) {
      if (left) {
        left_max->right = right;
      } else {
        root = right;
      }
      right->parent = left_max;
    }

    --sz;
  }

  const T& maximum() const { return max_in_tree(root)->val; }
  const T& minimum() const { return min_in_tree(root)->val; }
  [[nodiscard]] size_t size() const { return sz; }
  [[nodiscard]] bool empty() const { return !sz; }

  ~splay_tree() { destroy_nodes(root); }
};

} // namespace shiv
