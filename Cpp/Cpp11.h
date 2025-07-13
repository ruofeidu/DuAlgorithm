#pragma once
#include "common.h"
#include <cstdint>
#include <memory>

namespace Cpp11 {
enum class Colors : std::int8_t { RED = 1, GREEN = 2, BLUE = 3 };
auto lambda = [](int x, int y) {
  return x + y;
};  // C++ 11, in C++ 14, int can be replaced by auto

void functionList() {
  vector<function<int(int)>> funlist;
  for (int i = 0; i < 10; i++) {
    funlist.push_back([=](int j) { return i + j; });
  }
  cout << funlist[5](8) << endl;
}

int outputNumbers() {
  int val = 0b11110000;
  std::cout << "Output mask: " << 0b1000'0001'1000'0000 << "\n";
  std::cout << "Proposed salary: $" << 300'000.00 << "\n";
  return 0;
}

// deprecated("Consider using something other than cranky")
int debug() { return 0; }
}
