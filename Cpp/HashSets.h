#pragma once
#include "common.h"

namespace HashSets {
// 202. Happy Number [E]
// Write an algorithm to determine if a number is "happy".
// Starting with any positive integer, replace the number by the sum of the
// squares of its digits, and repeat the process until the number equals 1
// (where it will stay), or it loops endlessly in a cycle which does not include
// 1. Those numbers for which this process ends in 1 are happy numbers.
bool isHappy(int n) {
  unordered_set<int> h;
  while (n != 1 && !h.count(n)) {
    h.emplace(n);
    int m = 0;
    while (n > 0) {
      m += (n % 10) * (n % 10);
      n /= 10;
    }
    n = m;
  }
  return n == 1;
}

// 187. Repeated DNA Sequences [M]
// All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
// for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to
// identify repeated sequences within the DNA. Write a function to find all the
// 10 - letter - long sequences(substrings) that occur more than once in a DNA
// molecule.
vector<string> findRepeatedDnaSequences(string s) {
  auto hashcode = [](string &s) {
    int x = 0;
    for (const auto &c : s) {
      x <<= 2;
      if (c == 'T')
        x += 1;
      else if (c == 'C')
        x += 2;
      else if (c == 'G')
        x += 3;
    }
    return x;
  };

  unordered_set<int> d, r;
  vector<string> res;
  for (int i = 0; i < (int)s.size() - 9; ++i) {
    auto t = s.substr(i, 10);
    int h = hashcode(t);
    if (d.count(h)) {
      if (!r.count(h)) {
        res.emplace_back(t);
        r.emplace(h);
      }
    } else {
      d.emplace(h);
    }
  }
  return res;
}

// 217. Contains Duplicate [E]
// Given an array of integers, find if the array contains any duplicates. Your
// function should return true if any value appears at least twice in the array,
// and it should return false if every element is distinct.
bool containsDuplicate(vector<int> &nums) {
  unordered_set<int> s;
  for (const int &x : nums) {
    if (s.count(x)) return true;
    s.emplace(x);
  }
  return false;
}
}
