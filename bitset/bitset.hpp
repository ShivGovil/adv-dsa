#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace shiv {

using chunk = uint64_t;
static constexpr uint8_t BITS_PER_CHUNK = sizeof(chunk) * CHAR_BIT;

template <size_t B>
requires(B > 0)
class bitset {
  size_t n_chunks, n_bits;
  chunk *data;

  size_t chunk_index(size_t bit) {
    return bit / BITS_PER_CHUNK;
  }
  size_t bit_index(size_t bit) {
    return bit % BITS_PER_CHUNK;
  }

  class bit_ref {

  };

public:
  bitset() :
    n_chunks((B + BITS_PER_CHUNK - 1) / BITS_PER_CHUNK),
    n_bits(B),
    data(new chunk[n_chunks]{}) {}

  ~bitset() {
    delete[] data;
  }

  bool test(size_t bit) {
    if (bit > n_bits) return false;

    
    

  }

  void flip(size_t bit) {}

  void set(size_t bit, bool value = true) {
    if (bit > n_bits) return;
    if (value) {
      data[chunk_index(bit)] |= (1LL << (BITS_PER_CHUNK - bit_index(bit)));
    } else {
      data[chunk_index(bit)] &= ~(1LL << (BITS_PER_CHUNK - bit_index(bit)));
    }
  }

  size_t count() {
    // Keep counting leading ones
  }

  void reset() {
    std::memset(data, 0, (B + BITS_PER_CHUNK - 1) / BITS_PER_CHUNK);
  }
  // all, any, none
};

}
