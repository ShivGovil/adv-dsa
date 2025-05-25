#include <ctime>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <random>

#include "splay_tree.hpp"

int main() {
  std::cout << "Starting Splay Tree Tests...\n\n";

  shiv::splay_tree<int> tree;

  // Test 1: Empty tree properties
  std::cout << "Test 1: Empty tree\n";
  assert(tree.empty() == true);
  assert(tree.size() == 0);
  assert(!tree.find(42));
  std::cout << "✓ Empty tree tests passed\n\n";

  // Test 2: Single element insertion and retrieval
  std::cout << "Test 2: Single element operations\n";
  tree.insert(10);
  assert(tree.empty() == false);
  assert(tree.size() == 1);
  assert(tree.find(10)->key == 10);
  assert(!tree.find(5));
  std::cout << "✓ Single element tests passed\n\n";

  // Test 3: Multiple insertions
  std::cout << "Test 3: Multiple insertions\n";
  std::vector<int> values = {5, 15, 3, 7, 12, 18, 1, 6, 9, 14};
  for (int val : values) {
    tree.insert(val);
  }
  assert(tree.size() == 11);

  // Verify all elements can be found
  assert(tree.find(10)->key == 10);
  for (int val : values) {
    assert(tree.find(val)->key == val);
  }
  std::cout << "✓ Multiple insertion tests passed\n\n";

  // Test 4: Duplicate insertion handling
  std::cout << "Test 4: Duplicate insertions\n";
  size_t size_before = tree.size();
  tree.insert(10); // Insert duplicate
  tree.insert(5);  // Insert another duplicate
  // Size should remain same if duplicates aren't allowed
  // or increase if they are - adjust based on your implementation
  assert(size_before == tree.size());
  std::cout << "✓ Duplicate insertion test completed\n\n";

  // Test 5: Erase operations
  std::cout << "Test 5: Erase operations\n";

  // Erase a leaf node
  assert(tree.find(1)->key == 1);
  tree.erase(1);
  assert(!tree.find(1));

  // Erase a node with one child
  assert(tree.find(3)->key == 3);
  tree.erase(3);
  assert(!tree.find(3));

  // Erase a node with two children
  assert(tree.find(15)->key == 15);
  tree.erase(15);
  assert(!tree.find(15));

  // Verify remaining elements are still there
  std::vector<int> remaining = {10, 5, 7, 12, 18, 6, 9, 14};
  for (int val : remaining) {
    assert(tree.find(val)->key == val);
  }

  std::cout << "Size after erasures: " << tree.size() << "\n";
  std::cout << "✓ Erase operation tests passed\n\n";

  // Test 6: Erase non-existent elements
  std::cout << "Test 6: Erase non-existent elements\n";
  size_t size_before_invalid = tree.size();
  tree.erase(100); // Element that doesn't exist
  tree.erase(1);   // Element already erased
  assert(tree.size() == size_before_invalid); // Size should remain same
  std::cout << "✓ Invalid erase tests passed\n\n";

  // Test 7: Sequential access pattern (tests splay behavior)
  std::cout << "Test 7: Sequential access pattern\n";
  for (int i = 0; i < 5; ++i) {
    assert(tree.find(10)->key == 10);
  }
  std::cout << "✓ Sequential access test completed\n\n";

  // Test 8: Clear all elements
  std::cout << "Test 8: Clear all elements\n";
  std::vector<int> all_remaining = {10, 5, 7, 12, 18, 6, 9, 14};
  for (int val : all_remaining) {
    tree.erase(val);
  }

  assert(tree.empty());
  assert(!tree.size());

  // Verify no elements can be found
  for (int val : all_remaining) {
    assert(!tree.find(val));
  }
  std::cout << "✓ Clear all elements test passed\n\n";

  // Test 9: Rebuild and stress test
  std::cout << "Test 9: Stress test with larger dataset\n";
  std::vector<int> stress_data;
  for (int i = 1; i <= 100; ++i) {
    stress_data.push_back(i);
  }

  // Shuffle for more interesting splay behavior
  std::mt19937 rng(std::time(nullptr));
  std::shuffle(stress_data.begin(), stress_data.end(), rng);

  // Insert all elements
  for (int val : stress_data) {
    tree.insert(val);
  }
  assert(tree.size() == 100);

  // Verify all elements
  for (int i = 1; i <= 100; ++i) {
    assert(tree.find(i)->key == i);
  }

  // Random access pattern
  std::vector<int> random_access = {50, 25, 75, 12, 88, 3, 97, 45, 67, 33};
  for (int val : random_access) {
    assert(tree.find(val)->key == val);
  }

  // Erase half the elements
  for (int i = 1; i <= 100; i += 2) {
    tree.erase(i);
  }
  assert(tree.size() == 50);

  // Verify correct elements remain
  for (int i = 1; i <= 100; ++i) {
    if (i % 2 == 0) {
      assert(tree.find(i)->key == i);
    } else {
      assert(!tree.find(i));
    }
  }

  std::cout << "✓ Stress test passed\n\n";

  std::cout << "🎉 All Splay Tree tests passed successfully!\n";
  std::cout << "Your implementation appears to be working correctly.\n";

  return 0;
}
