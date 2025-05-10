#include "sqrt_decomp.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<double> nums = {0.5, 1, 7, 15, 0.2, 1, 1.2, 4.3, 6, 10, 14};
  sqrt_decomp<double> s(nums);

  s.print();
  std::cout << s.query(0, 7) << '\n';
  s.update_elt(5, 7.5);
  std::cout << s.query(0, 7) << '\n';
  return 0;
}
