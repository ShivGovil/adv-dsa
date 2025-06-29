#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <numbers>
#include "xxhash.h"
#include "../bitset/bitset.hpp"

using namespace std::numbers;

namespace shiv {

class bloom_filter {
  size_t bit_count;
  uint8_t hash_count;
  shiv::bitset bs{0};

  [[nodiscard]] std::pair<uint64_t, uint64_t> hash(const std::string &s) const {
    XXH128_hash_t hash_result = XXH3_128bits(s.c_str(), s.length());
    return {hash_result.high64, hash_result.low64};
  }

public:
  bloom_filter(double est_num_objects, double false_positive_rate) {
    double bits_needed = -((est_num_objects * std::log(false_positive_rate)) / (ln2 * ln2));
    bit_count = static_cast<size_t>(std::ceil(bits_needed));
    hash_count = static_cast<uint8_t>(std::round(bits_needed / est_num_objects * ln2));
    bs.resize(bit_count);
  }

  void insert(const std::string &s) {
    auto hash_pair = hash(s);
    for (uint8_t i = 0; i < hash_count; ++i) {
      uint64_t new_hash = (hash_pair.first + i * hash_pair.second) % bit_count;
      bs.set(new_hash, true);
    }
  }

  bool contains(const std::string &s) {
    auto hash_pair = hash(s);
    for (uint8_t i = 0; i < hash_count; ++i) {
      uint64_t new_hash = (hash_pair.first + i * hash_pair.second) % bit_count;
      if(!bs.test(new_hash)) { return false; }
    }
    return true;
  }
};

} // namespace
