#pragma once

#include <memory>
template <typename K, typename V>
class splay_tree {
  public:
    splay_tree() : root(nullptr) {}

    void push(const K &key, const V &value) {
      if (!root) {
        root = make_shared<node>(node{key, value, nullptr, nullptr, nullptr});
        return;
      }

    }

    void remove(const K &key) {

    }

    V& find(const K &key) {

    }

    const V& find(const K &key) {

    }

  private:
    struct node {
      K key;
      V value;
      std::shared_ptr<node> left, right;
      // If the parent ptr was shared, then we would have circular references
      // This would hinder the destruction process
      std::weak_ptr<node> parent;
    };

    std::shared_ptr<node> root;
};
