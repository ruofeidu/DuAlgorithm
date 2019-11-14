#pragma once
#include "common.h"

// Time: O(n + m)
namespace KMP {
const int leng = 100;
void build(vector<int> &next, const string &s, const string &p) {
  int m = (int)p.size();
  int t = -1;
  for (int i = 0; i < m; ++i) {
    next[i] = t;
    while (t >= 0 && p[t] != p[i]) t = next[t];
    ++t;
  }
}

int KMP(const string &s, const string &p) {
  int n = (int)s.size();
  int m = (int)p.size();
  vector<int> next(m, 0);
  build(next, s, p);

  int t = 0;
  for (int i = 0; i < n; ++i) {
    while (t >= 0 && s[i] != p[t]) t = next[t];
    if (t == m) return i - m + 1;
    t++;
  }
  return -1;
}
}

namespace Naive {
// 28. Implement strStr()
int strStr(string haystack, string needle) {
  if (needle.empty()) return 0;
  const int N = (int)haystack.size() - (int)needle.size() + 1;
  for (int i = 0; i < N; ++i) {
    int j = i;
    int k = 0;
    while (j < haystack.size() && k < needle.size() &&
           haystack[j] == needle[k]) {
      ++j;
      ++k;
    }
    if (k == needle.size()) return i;
  }
  return -1;
}
}
