#pragma once
#include "common.h"
#include <algorithm>

// See STLSort, STLLinear for more STL references.
namespace STLAlgorithm {
int a[] = {3, 2, 1, 3, 3, 5};
vector<int> v{2, 3, 5, 3, 2};
vector<int> v2{2, 3, 5, 3, 2};

// adjacent_find

// bineary_search, equal_range, lower_bound, upper_bound
// log2(N) + 2
void binary_search_test() {
  vector<int> b = {10, 10, 10, 20, 20, 20, 30, 30};
  auto bounds = equal_range(b.begin(), b.end(), 20);
  bool found = binary_search(b.begin(), b.end(), 20);
}

// copy, copy_backward
void copy_test() {
  // copy the first 3 elements from v2 to v
  copy(v2.begin(), v2.begin() + 3, v.begin() + 4);
}

// count, count_if
// Returns count of occurrences of value in range [begin, end]
void test_count() {
  cout << count(v.begin(), v.end(), 3) << endl;
  cout << count(a, a + sizeof(a) / sizeof(a[0]), 3) << endl;

  auto is_odd = [](const int x) { return (x & 1) == 1; };
  cout << count_if(v.begin(), v.end(), is_odd) << endl;
}

// equal
bool is_palindrome(const string& s) {
  return equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}

// fill, fill_n

// find, find_end, find_first_of, find_if

// for_each
void for_each_test() {
  auto print = [](const int& n) { std::cout << " " << n; };
  std::for_each(v.begin(), v.end(), print);
}

// generate, generate_n

// includes

// inplace_merge

// iter_swap

// lexicographical_compare

// max / min / max_element / min_element
void max_min_test() {
  auto min_it = min_element(v.begin(), v.end());
  cout << *min_it << endl;
}
// merge

// mismatch

// next_permutation, prev_permutation

// nth_element

// partial_sort, partial_sort_copy

// partition

// make_heap O(N), pop_heap O(log N), push_heap O(N), is_heap O(N)

// random_shuffle

// remove, remove_copy, remove_copy_if, remove_if

// reverse, reverse_copy

// replace_copy_if, replace_if

// reverse, reverse_copy

// rotate, rotate_copy

// search, search_n

// set_difference

// set_intersection

// set_symmetric_difference

// set_union

// sort, sort_heap

// stable_partition, stable_sort

// swap, swap_ranges

// transform

// unique

// unique_copy
}
