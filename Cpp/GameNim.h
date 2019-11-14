#pragma once
#include "common.h"

class NimGame {
  vector<string> generatePossibleNextMoves(string s) {
    vector<string> res;
    for (int i = 1; i < s.size(); ++i) {
      if (s[i] == '+' && s[i - 1] == '+') {
        res.emplace_back(s.substr(0, i - 1) + "--" + s.substr(i + 1));
      }
    }
    return res;
  }

  bool canWin(string s) {
    int n = (int)s.size();
    int l = 0;

    vector<bool> winStates(n + 1, false);
    vector<int> nim(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
      for (int j = 0; j <= i - j - 2; ++j) {
        winStates[nim[j] ^ nim[i - j - 2]] = true;
      }
      bool nimEmpty = true;
      for (int j = 0; j <= n; ++j) {
        if (!winStates[j] && nimEmpty) {
          nimEmpty = false;
          nim[i] = j;
        } else {
          winStates[j] = false;
        }
      }
    }

    int ans = 0;
    int len = 0;
    s = s + "-";
    for (char c : s) {
      if (c == '-') {
        ans = ans ^ nim[l];
        l = 0;
      } else {
        ++l;
      }
    }
    return ans != 0;
  }
};
