#pragma once
#include "common.h"

class Sudoku {
public:
	// 36. Valid Sudoku
	bool isValidSudoku(vector<vector<char>>& board) {
		// check each 3x3
		const int n = 3;
		const int m = n * n;
		for (int k = 0; k < m; ++k) {
			unordered_map<char, bool> visited;
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					int y = int(k / 3) * 3 + i;
					int x = int(k % 3) * 3 + j;
					char c = board[y][x];
					if (c == '.') continue;
					if (visited.find(c) != visited.end()) return false;
					visited[c] = true;
				}
			}
		}

		// check each row and column
		for (int k = 0; k < m; ++k) {
			unordered_map<char, bool> row_vd;
			for (int i = 0; i < m; ++i) {
				char c = board[k][i];
				if (c == '.') continue;
				if (row_vd.find(c) != row_vd.end()) return false;
				row_vd[c] = true;
			}

			unordered_map<char, bool> col_vd;
			for (int i = 0; i < m; ++i) {
				char c = board[i][k];
				if (c == '.') continue;
				if (col_vd.find(c) != col_vd.end()) return false;
				col_vd[c] = true;
			}
		}
		return true;
	}

public:
	// 37. Sudoku solver
	void solveSudoku(vector<vector<char>>& board) {
		solveSudokuDFS(board);
	}

private:
	bool solveSudokuDFS(vector<vector<char>>& board) {
		const int n = 9;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == '.') {
					for (int k = 0; k < n; ++k) {
						board[i][j] = '1' + k;
						if (isSudokuValid(board, i, j) && solveSudokuDFS(board)) return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		}
		return true;
	}

	bool isSudokuValid(const vector<vector<char>> &board, int x, int y) {
		const int n = 9;
		int i, j;
		for (int i = 0; i < n; ++i)
			if (i != x && board[i][y] == board[x][y]) return false;
		for (int j = 0; j < n; ++j)
			if (j != y && board[x][j] == board[x][y]) return false;
		for (i = 3 * (x / 3); i < 3 * (x / 3 + 1); i++)
			for (j = 3 * (y / 3); j < 3 * (y / 3 + 1); j++)
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
		return true;
	}
};
