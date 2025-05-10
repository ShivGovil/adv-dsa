#pragma once

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

template<typename T>
class sqrt_decomp {
  std::vector<T> nums;
  std::vector<T> data;
  size_t N;
  size_t S;

public:
  sqrt_decomp(const std::vector<T> &nums_) :
    nums(nums_),
    N(nums.size()),
    S(static_cast<size_t>(std::ceil(std::sqrt(N)))) {

    data.resize((N + S - 1) / S);
    for (size_t i = 0; i < N; ++i) {
      data[i / S] += nums[i];
    }
  }

  T query(size_t l, size_t r) {
    T sum{};
    size_t blk_l = l / S;
    size_t blk_r = r / S;
    if (blk_l == blk_r) {
      for (size_t i = l; i < r; ++i)
        sum += nums[i];
    } else {
      size_t end = std::min((blk_l + 1) * S, r + 1);
      for (size_t i = l; i <= end; ++i)
        sum += nums[i];
      for (size_t i = blk_l + 1; i <= blk_r - 1; ++i)
        sum += data[i];
      for (size_t i = blk_r * S; i <= r && i < nums.size(); ++i)
        sum += nums[i];
    }

    return sum;
  }

  void update_elt(size_t index, T new_value) {
    assert(index < N);
    data[index / S] += new_value - nums[index];
    nums[index] = new_value;
  }

  void print() {
    for (size_t i = 0; i < data.size(); ++i) {
      std::cout << data[i] << ' ';
    }
    std::cout << '\n';
  }

  // void update_interval(size_t l, size_t r) {}
};
