#pragma once

#include <cstddef>
#include <cstdint>

namespace shiv {

enum class Color : uint8_t {
  BLACK = 0,
  RED = 1
};

enum class Direction : uint8_t {
  LEFT = 0,
  RIGHT = 1
};

template<typename T>
class red_black_tree {
  struct node {
    node *parent;

    union {
      struct {
        node *left, *right;
      } lr;
      node *child[2];
    } children;

    Color color;
    T val;
  };


  public:
    red_black_tree();
    ~red_black_tree();
};

} // namespace
