#pragma once
#include "common.h"

namespace Grids {
	vector<pair<int, int>> pacificAtlanticAnother(Grid& matrix) {
		int n = (int)matrix.size();
		int m = n ? (int)matrix[0].size() : 0;

		int dx[] = { 1, 0, -1,  0 };
		int dy[] = { 0, 1,  0, -1 };

		Grid ir(n, vector<int>(m));  // whether increasing in row
		Grid ic(n, vector<int>(m));  // whether increasing in col
		Grid irc(n, vector<int>(m));  // whether increasing

		Grid dr(n, vector<int>(m));  // whether decreasing in row
		Grid dc(n, vector<int>(m));  // whether decreasing in col
		Grid drc(n, vector<int>(m));  // whether decreasing

		for (int i = 0; i < n; ++i) {
			ir[i][0] = true;
			irc[i][0] = true;
			dr[i][m - 1] = true;
			drc[i][m - 1] = true;
			for (int j = 1; j < m; ++j)
				if (ir[i][j - 1] && matrix[i][j] >= matrix[i][j - 1])
					ir[i][j] = true;

			for (int j = m - 2; j >= 0; --j)
				if (dr[i][j + 1] && matrix[i][j] >= matrix[i][j + 1])
					dr[i][j] = true;
		}

		for (int j = 0; j < m; ++j) {
			ic[0][j] = true;
			dc[n - 1][j] = true;
			irc[0][j] = true;
			drc[n - 1][j] = true;
			for (int i = 1; i < n; ++i)
				if (ic[i - 1][j] && matrix[i][j] >= matrix[i - 1][j])
					ic[i][j] = true;

			for (int i = n - 2; i >= 0; --i)
				if (dc[i][j + 1] && matrix[i][j] >= matrix[i + 1][j])
					dc[i][j] = true;
		}

		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				if (ir[i][j] || ic[i][j]) irc[i][j] = true; else
					for (int k = 0; k < 4; ++k) {
						int y = i + dy[k];
						int x = j + dx[k];
						if (y < 0 || x < 0 || y >= n || x >= m) continue;
						if (irc[y][x] && matrix[i][j] >= matrix[y][x])
							irc[i][j] = true;
					}
			}
		}

		for (int i = n - 2; i >= 0; --i) {
			for (int j = m - 2; j >= 0; --j) {
				if (dr[i][j] || dc[i][j]) drc[i][j] = true; else
					for (int k = 0; k < 4; ++k) {
						int y = i + dy[k];
						int x = j + dx[k];
						if (y < 0 || x < 0 || y >= n || x >= m) continue;
						if (drc[y][x] && matrix[i][j] >= matrix[y][x])
							drc[i][j] = true;
					}
			}
		}

		vector<pair<int, int>> ans; // answers
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (irc[i][j] && drc[i][j]) ans.emplace_back(pair<int, int>(i, j));
			}
		}

		return ans;
	}

	// 54. Spiral Matrix [M]
	// Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> ans;
		if (matrix.size() == 0) return ans;
		int ymin = 0, ymax = (int)matrix.size() - 1;
		int xmin = 0, xmax = (int)matrix[0].size() - 1;
		int y = 0, x = 0;
		int dir[4][2] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
		int dirid = 0;

		for (auto i = 0; i < (int)matrix.size() * (int)matrix[0].size(); ++i) {
			ans.push_back(matrix[y][x]);
			cout << matrix[y][x] << "\t";
			y += dir[dirid][0];
			x += dir[dirid][1];

			if (y < ymin || x < xmin || y > ymax || x > xmax) {
				if (x > xmax) ++ymin; else
					if (y > ymax) --xmax; else
						if (x < xmin)--ymax; else
							++xmin;
				y -= dir[dirid][0];
				x -= dir[dirid][1];
				dirid = (dirid + 1) % 4;
				y += dir[dirid][0];
				x += dir[dirid][1];
			}
		}

		return ans;
	}

	// 59. Spiral Matrix II
	// Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> ans(n, vector<int>(n));
		if (n == 0) return ans;
		int ymin = 0, ymax = n - 1;
		int xmin = 0, xmax = n - 1;
		int y = 0, x = 0;
		int dir[4][2] = { { 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 } };
		int dirid = 0;

		for (auto i = 0; i < n; ++i) {
			for (auto j = 0; j < n; ++j) {
				ans[y][x] = i * n + j + 1;
				y += dir[dirid][0];
				x += dir[dirid][1];

				if (y < ymin || x < xmin || y > ymax || x > xmax) {
					if (x > xmax) ++ymin; else
						if (y > ymax) --xmax; else
							if (x < xmin)--ymax; else
								++xmin;
					y -= dir[dirid][0];
					x -= dir[dirid][1];
					dirid = (dirid + 1) % 4;
					y += dir[dirid][0];
					x += dir[dirid][1];
				}
			}
		}

		return ans;
	}
};
