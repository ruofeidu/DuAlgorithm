#pragma once
#include "common.h"

class TicTacToe {
 private:
  Grid m_rows, m_cols;
  Vector m_diagonal, m_anti_diagonal;

 public:
  TicTacToe(int n)
      : m_rows{n, {2, 0}},
        m_cols{n, {2, 0}},
        m_diagonal{2, 0},
        m_anti_diagonal{2, 0} {}

  int move(int row, int col, int player) {
    const auto i = player - 1;
    ++m_rows[row][i];
    ++m_cols[col][i];
    if (row == col) {
      ++m_diagonal[i];
    }
    if (col == m_rows.size() - row - 1) {
      ++m_anti_diagonal[i];
    }
    if (m_rows[row][i] == m_rows.size() || m_cols[col][i] == m_cols.size() ||
        m_diagonal[i] == m_rows.size() || m_anti_diagonal[i] == m_cols.size()) {
      return player;
    }
    return 0;
  }
};
