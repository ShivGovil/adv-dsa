#include <cassert>
#include <iostream>
#include "bloom_filter.hpp"

int main() {
  shiv::bloom_filter bf(1000, 0.0001);
  bf.insert("hello");
  assert(bf.contains("hello"));
  assert(!bf.contains("Hello"));
  return 0;
}
