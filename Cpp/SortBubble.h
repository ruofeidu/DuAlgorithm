#pragma once
#include "common.h"

// Bubble sort
// While not sorted, scan and float the largest to the end.
// Time: O(N^2)
void bubble_sort(vector<int>* arr, int l = -2, int r = -1) {
  if (arr == nullptr || l >= r) {
    return;
  }

  std::vector<int>& a = *arr;
  if (l < 0) {
    l = 0;
  }
  if (r < 0) {
    r = a.size();
  }

  bool swapped_in_pass = false;
  const auto n = a.size();
  for (size_t i = l; i <= r; ++i) {
    swapped_in_pass = true;
    for (size_t j = l; j < r - (i - l); ++j) {
      if (a[j] > a[j + 1]) {
        swap(a[j], a[j + 1]);
        swapped_in_pass = false;
      }
    }
    if (!swapped_in_pass) break;
  }
}
