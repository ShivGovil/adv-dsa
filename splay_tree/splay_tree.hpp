#pragma once

template <typename K, typename V>
class splay_tree {
public:
  splay_tree() = default;

  void push(const K& key, const V& value) {}

  void remove(const K& key) {}

  V& find(const K& key) {}

  const V& find(const K& key) const {}

private:
  struct node {
    K key;
    V value;
    node *left, *right; // Parent?
  };

  // height calc for balancing
  // rotation functions
  // (swim up, swim down)

  node *root;
};
