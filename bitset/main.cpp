#include <cassert>
#include <iostream>
#include "bitset.hpp"

int main() {
  shiv::bitset bs(100);
  bs.set_all();
  bs.print();
  std::cout << '\n';
  bs <<= 64;
  bs.print();
  std::cout << '\n';
  bs >>= 64;
  bs.print();
  std::cout << '\n';
  bs.flip_all();
  bs.print();

  // set different bits
  for (size_t i = 0; i < bs.size(); ++i) {
    bs[i] = static_cast<bool>(i % 2);
  }

  // check bits
  for (size_t i = 0; i < bs.size(); ++i) {
    assert(static_cast<bool>(bs[i]) == (i % 2));
  }

  // set bits to the same thing to make sure they don't flip
  for (size_t i = 0; i < bs.size(); ++i) {
    bs[i] = static_cast<bool>(i % 2);
  }
  // check bits
  for (size_t i = 0; i < bs.size(); ++i) {
    assert(static_cast<bool>(bs[i]) == (i % 2));
  }

  // check assignment operator and destructor
  {
    shiv::bitset temp(0);
    temp = bs;
    // check bits of the temp;
    for (size_t i = 0; i < bs.size(); ++i) {
      assert(static_cast<bool>(bs[i]) == (i % 2));
    }
  }

  // check int assignment operator
  bs[3] = 0;
  assert(bs[3] == 0);

  // check equality operators
  assert(bs[0] != bs[1]);
  assert(bs[0] == bs[2]);

  assert(bs[0] != true);
  assert(bs[1] == true);

  std::cout << "\nPASS\n" << '\n';
}
