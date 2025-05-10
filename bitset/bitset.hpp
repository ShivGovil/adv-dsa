#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>

namespace shiv {

using chunk = uint64_t;
static constexpr uint8_t BITS_PER_CHUNK = sizeof(chunk) * CHAR_BIT;

template <size_t B>
requires(B > 0)
class bitset {
  size_t chunks, bits;
  chunk *data;

  size_t chunk_index(size_t bit);
  size_t bit_index(size_t bit);

  class bit_ref {

  };

public:
  bitset() :
    chunks((B + BITS_PER_CHUNK - 1) / BITS_PER_CHUNK),
    bits(B),
    data(new chunk[chunks]{}) {}

  ~bitset() {
    delete[] data;
  }

  bool test(size_t bit) {
    if (bit > bits) return false;
    

  }
  void flip(size_t bit);
  void set(size_t bit, bool value = true) {
    if (bit > bits) return;
    if (value) {

    }
  }
  size_t count();
  void reset();
  // all, any, none
};

}
