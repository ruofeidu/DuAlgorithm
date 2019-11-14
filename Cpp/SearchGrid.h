#pragma once
#include "common.h"

class SearchGrid {
  // 240. Search a 2D Matrix II [M]
  // Write an efficient algorithm that searches for a value in an m x n matrix.
  /*
          [1,   4,  7, 11, 15],
          [2,   5,  8, 12, 19],
          [3,   6,  9, 16, 22],
          [10, 13, 14, 17, 24],
          [18, 21, 23, 26, 30]
  */
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) return false;
    int n = (int)matrix.size(), m = (int)matrix[0].size();
    if (target < matrix[0][0] || target > matrix.back().back()) return false;

    int y = n - 1, x = 0;
    while (true) {
      if (matrix[y][x] > target)
        --y;
      else if (matrix[y][x] < target)
        ++x;
      else
        return true;
      if (y < 0 || x >= m) break;
    }
    return false;
  }

  inline bool valid(int y, int x, int n, int m) {
    return y >= 0 && y <= n - 1 && x >= 0 && x <= m - 1;
  }

  int minArea(vector<vector<char>> &image, int y, int x) {
    int n = (int)image.size();
    int m = n ? (int)image[0].size() : 0;
    if (!valid(y, x, n, m) || image[y][x] != '1') return 0;

    int ans = 0;
    typedef pair<int, int> CT;  // CoordType
    vector<vector<bool>> vd(n, vector<bool>(m));
    CT start = CT(y, x);
    CT topleft = start, botright = start;
    vd[y][x] = true;
    queue<CT> q;
    q.push(start);
    vector<vector<int>> dir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!q.empty()) {
      int i = q.front().first;
      int j = q.front().second;
      q.pop();
      for (int k = 0; k < dir.size(); ++k) {
        int r = i + dir[k][0];
        int c = j + dir[k][1];
        if (!valid(r, c, n, m) || vd[r][c] || image[r][c] == '0') continue;
        vd[r][c] = true;
        CT newc = CT(r, c);
        if (r < topleft.first) topleft.first = r;
        if (c < topleft.second) topleft.second = c;
        if (r > botright.first) botright.first = r;
        if (c > botright.second) botright.second = c;
        q.push(newc);
      }
    }
    return (botright.first - topleft.first + 1) *
           (botright.second - topleft.second + 1);
  }

  // 79. Word Search
  // Given a 2D board and a word, find if the word exists in the grid.
 public:
  bool exist(vector<vector<char>> &board, string word) {
    if (board.empty()) return word.empty();
    const int n = (int)board.size(), m = (int)board[0].size();

    vector<vector<bool>> vd(n, vector<bool>(m, false));

    for (int y = 0; y < n; ++y) {
      for (int x = 0; x < m; ++x)
        if (board[y][x] == word[0]) {
          if (existDFS(board, word, "", y, x, vd, 0)) return true;
        }
    }

    return false;
  }

  bool existDFS(vector<vector<char>> &board, string &word, string curword,
                int y, int x, vector<vector<bool>> &vd, int depth) {
    const int dir[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    curword += board[y][x];
    if (curword[depth] != word[depth]) return false;
    vd[y][x] = true;
    if (curword == word) return true;
    if (curword.size() > word.size()) return false;
    for (int i = 0; i < 4; ++i) {
      int ny = y + dir[i][0];
      int nx = x + dir[i][1];
      if (ny < 0 || nx < 0 || ny >= board.size() || nx >= board[0].size() ||
          vd[ny][nx])
        continue;
      if (existDFS(board, word, curword, ny, nx, vd, depth + 1)) return true;
    }
    vd[y][x] = false;
    return false;
  }

  // 200. Number of Islands
  int numIslands(vector<vector<char>> &grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int m = (int)grid.size(), n = (int)grid[0].size(), res = 0;
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '1' && !visited[i][j]) {
          numIslandsDFS(grid, visited, i, j);
          ++res;
        }
      }
    }
    return res;
  }
  void numIslandsDFS(vector<vector<char>> &grid, vector<vector<bool>> &visited,
                     int x, int y) {
    if (x < 0 || x >= grid.size()) return;
    if (y < 0 || y >= grid[0].size()) return;
    if (grid[x][y] != '1' || visited[x][y]) return;
    visited[x][y] = true;
    numIslandsDFS(grid, visited, x - 1, y);
    numIslandsDFS(grid, visited, x + 1, y);
    numIslandsDFS(grid, visited, x, y - 1);
    numIslandsDFS(grid, visited, x, y + 1);
  }
};
