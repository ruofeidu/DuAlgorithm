#pragma once
#include "common.h"

namespace GamesGo {
// 130. Surrounded Regions
// Given a 2D board containing 'X' and 'O' (the letter O), capture all regions
// surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in
// that surrounded region.
/*
X X X X
X O O X
X X O X
X O X X

X X X X
X X X X
X X X X
X O X X
*/
void solve(vector<vector<char>>& board) {
  const int n = (int)board.size();
  if (n == 0) return;
  const int m = (int)board[0].size();
  if (m == 0) return;

  queue<pair<int, int>> q;
  for (int i = 0; i < n; ++i) {
    q.push({i, -1});
    q.push({i, m});
  }
  for (int j = 0; j < m; ++j) {
    q.push({-1, j});
    q.push({n, j});
  }

  vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    for (const auto& v : dir) {
      pair<int, int> next = {cur.first + v.first, cur.second + v.second};
      if (next.first >= 0 && next.first < n && next.second >= 0 &&
          next.second < m && board[next.first][next.second] == 'O') {
        board[next.first][next.second] = 'o';
        q.push(next);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      auto& c = board[i][j];
      if (c == 'O') c = 'X';
      if (c == 'o') c = 'O';
    }
  }
}
}
