#pragma once
#include "common.h"

namespace StringTricks {
// 151. Reverse Words in a String
// Given s = "the sky is blue",
// return "blue is sky the".
void reverseWords(string &s) {
  istringstream is(s);
  string tmp;
  is >> s;
  while (is >> tmp) s = tmp + " " + s;
  if (!s.empty() && s[0] == ' ') s = "";
}
}
