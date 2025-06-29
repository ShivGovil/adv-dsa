#pragma once

#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>

namespace shiv {
// TODO: Binary operators + equality
// This is awesome

using chunk = uint32_t; // To use __builtin_popcount()
constexpr chunk CHUNK_MAX = static_cast<chunk>(-1);
static constexpr uint8_t BITS_PER_CHUNK = sizeof(chunk) * CHAR_BIT;

class bitset {
  size_t n_chunks, n_bits;
  chunk *data{};

  [[nodiscard]] size_t chunk_index(size_t bit) const {
    return bit / BITS_PER_CHUNK;
  }
  [[nodiscard]] size_t bit_index(size_t bit) const {
    return bit % BITS_PER_CHUNK;
  }

  class bit_ref {
    chunk &e, mask; // NOLINT

  public:
    bit_ref(chunk &e_, chunk mask_) : e(e_), mask(mask_) {}

    operator bool() const { return e & mask; }

    bit_ref &operator=(bool b) {
      b ? e |= mask : e &= ~mask;
      return *this;
    }

    bool operator!() const { return !(e & mask); }

    bool operator==(bool rhs) const {
      return static_cast<bool>(*this) == rhs;
    }

    bool operator!=(bool rhs) const {
      return !(*this == rhs);
    }

    bool operator==(int rhs) const {
      return *this == static_cast<bool>(rhs);
    }

    bool operator!=(int rhs) const {
      return !(*this == rhs);
    }
  };

public:
  bitset(size_t B) :
    n_chunks((B + BITS_PER_CHUNK - 1) / BITS_PER_CHUNK),
    n_bits(B),
    data(new chunk[n_chunks]{}) {}

  bitset(const bitset &other) :
    n_chunks(other.n_chunks),
    n_bits(other.n_bits),
    data(new chunk[n_chunks]) {
    memcpy(data, other.data, n_chunks * sizeof(chunk));
  }

  bitset &operator=(const bitset &other) {
    if (&other == this) return *this;

    n_chunks = other.n_chunks;
    n_bits = other.n_bits;
    delete[] data;
    data = new chunk[n_chunks];
    memcpy(data, other.data, n_chunks * sizeof(chunk));

    return *this;
  }

  bitset &operator=(bitset &&other) noexcept {
    if (&other == this) return *this;

    n_chunks = other.n_chunks;
    n_bits = other.n_bits;
    delete[] data;
    data = other.data;
    other.data = nullptr;
    other.n_chunks = 0;
    other.n_bits = 0;

    return *this;
  }

  ~bitset() {
    delete[] data;
  }

  bit_ref operator[](const size_t &bit) {
    return {data[chunk_index(bit)], static_cast<chunk>(1) << bit_index(bit)};
  }

  bool operator[](const size_t &bit) const {
    return test(bit);
  }

  bitset &operator<<=(size_t shift) {
    if (!shift || none()) return *this;

    if (shift >= size()) {
      reset();
      return *this;
    }

    size_t chunk_shift = shift / BITS_PER_CHUNK;
    size_t bit_shift = shift % BITS_PER_CHUNK;

    if (chunk_shift > 0) {
      for (size_t c = n_chunks; c-- > chunk_shift;) {
        data[c] = data[c - chunk_shift];
      }
      memset(data, 0, chunk_shift * sizeof(chunk));
    }

    if (bit_shift > 0) {
      chunk carry{};
      for (size_t c = 0; c < n_chunks; ++c) {
        chunk next_carry = (data[c] >> (BITS_PER_CHUNK - bit_shift)) & ((static_cast<chunk>(1) << bit_shift) - 1);
        data[c] = (data[c] << bit_shift) | carry;
        carry = next_carry;
      }
    }

    return *this;
  }

  bitset &operator>>=(size_t shift) {
    if (!shift || none()) return *this;

    if (shift >= size()) {
      reset();
      return *this;
    }

    size_t chunk_shift = shift / BITS_PER_CHUNK;
    size_t bit_shift = shift % BITS_PER_CHUNK;

    if (chunk_shift > 0) {
      for (size_t c = 0; c < n_chunks - chunk_shift; ++c) {
        data[c] = data[c + chunk_shift];
      }
      memset(data + n_chunks - chunk_shift, 0, chunk_shift * sizeof(chunk));
    }

    if (bit_shift > 0) {
      chunk carry{};
      for (size_t c = n_chunks; c-- > 0;) {
        chunk next_carry = data[c] << (BITS_PER_CHUNK - bit_shift);
        data[c] = (data[c] >> bit_shift) | (carry << (BITS_PER_CHUNK - bit_shift));
        carry = next_carry;
      }
    }

    return *this;
  }

  friend bitset operator<<(bitset lhs, size_t shift);
  friend bitset operator>>(bitset lhs, size_t shift);

  [[nodiscard]] bool test(const size_t &bit) const {
    assert(bit < n_bits);
    return data[chunk_index(bit)] &
    (static_cast<chunk>(1) << bit_index(bit));
  }

  void flip(const size_t &bit) {
    assert(bit < n_bits);
    set(bit, test(bit));
  }

  void flip_all() {
    for (size_t c = 0; c < n_chunks; ++c) {
      data[c] = ~data[c];
    }
  }

  void set(const size_t &bit, bool value = true) {
    assert(bit < n_bits);
    if (value) {
      data[chunk_index(bit)] |= (static_cast<chunk>(1) << bit_index(bit));
    } else {
      data[chunk_index(bit)] &= ~(static_cast<chunk>(1) << bit_index(bit));
    }
  }

  void set_all(bool value = true) {
    std::memset(data, value ? 0xFF : 0, n_chunks * sizeof(chunk));
  }

  size_t count() {
    size_t res{};
    for (size_t c = 0; c < n_chunks; ++c) {
      res += __builtin_popcount(data[c]);
    }
    return res;
  }

  void reset() {
    std::memset(data, 0, n_chunks * sizeof(chunk));
  }

  bool all() {
    for (size_t c = 0; c < n_chunks; ++c) {
      if (data[c] != CHUNK_MAX) return false;
    }
    return true;
  }

  bool any() {
    for (size_t c = 0; c < n_chunks; ++c) {
      if (data[c]) return true;
    }
    return false;
  }

  bool none() {
    for (size_t c = 0; c < n_chunks; ++c) {
      if (data[c]) return false;
    }
    return true;
  }

  [[nodiscard]] size_t size() const {
    return n_bits;
  }

  void print() const {
    size_t bit = n_bits - 1;
    for (int c = n_chunks - 1; c >= 0; --c) {
      for (; bit >= 0 && bit / BITS_PER_CHUNK == c; --bit) {
        std::cout << static_cast<bool>(data[c] & static_cast<chunk>(1) << (bit % BITS_PER_CHUNK));
      }
    }
  }

  void resize(size_t new_size) {
    if (new_size == n_bits) return;

    size_t new_n_chunks = (new_size + BITS_PER_CHUNK - 1) / BITS_PER_CHUNK;

    if (new_n_chunks != n_chunks) {
      auto new_data = new chunk[new_n_chunks]{};

      // Find minimum as we could be shrinking
      size_t chunks_to_copy = (n_chunks < new_n_chunks) ? n_chunks : new_n_chunks;
      if (data && chunks_to_copy > 0) {
        memcpy(new_data, data, chunks_to_copy * sizeof(chunk));
      }

      delete[] data;
      data = new_data;
      n_chunks = new_n_chunks;
    }

    n_bits = new_size;

    // If we're shrinking within the same number of chunks, clear unused bits
    if (new_size > 0 && new_n_chunks == n_chunks && new_size < (n_chunks * BITS_PER_CHUNK)) {
      size_t last_chunk_idx = (new_size - 1) / BITS_PER_CHUNK;
      size_t bits_in_last_chunk = ((new_size - 1) % BITS_PER_CHUNK) + 1;

      if (bits_in_last_chunk < BITS_PER_CHUNK) {
        chunk mask = (static_cast<chunk>(1) << bits_in_last_chunk) - 1;
        data[last_chunk_idx] &= mask;
      }
    }
  }
};

inline bitset operator<<(bitset lhs, size_t shift) {
  return lhs <<= shift;
}

inline bitset operator>>(bitset lhs, size_t shift) {
  return lhs <<= shift;
}

} // namespace shiv
