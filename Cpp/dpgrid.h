#pragma once
#include "common.h"

class DP2D {
public:
	// 64. Minimum Path Sum
	int minPathSum(vector<vector<int>>& grid) {
		auto m = grid.size();
		auto n = grid[0].size();

		vector<int> f(n, 0);
		f[0] = grid[0][0];
		for (auto j = 1; j < n; ++j) f[j] = f[j - 1] + grid[0][j];

		for (auto i = 1; i < m; ++i) {
			f[0] += grid[i][0];
			for (int j = 1; j < n; ++j) {
				f[j] = min(f[j], f[j - 1]) + grid[i][j];
			}
		}

		return f[n - 1];
	}

	// 120. Triangle
	// Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
	int minimumTotal(vector<vector<int>>& triangle) {
		const int n = (int)triangle.size();
		if (n <= 0)
			return 0;

		vector<vector<int>> f(2, vector<int>(n + 1));

		for (int j = 0; j < n; ++j)
			f[(n - 1) % 2][j] = triangle[n - 1][j];

		for (int i = n - 2; i >= 0; --i) {
			for (int j = 0; j < i + 1; ++j) {
				f[i % 2][j] = triangle[i][j] + min(f[(i + 1) % 2][j], f[(i + 1) % 2][j + 1]);
			}
		}
		return f[0][0];
	}

	vector<pair<int, int>> pacificAtlanticAnother(Grid& matrix) {
		const int n = (int)matrix.size();
		const int m = n ? (int)matrix[0].size() : 0;

		const int dx[] = { 1, 0, -1,  0 };
		const int dy[] = { 0, 1,  0, -1 };

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
				if (ir[i][j] || ic[i][j])
					irc[i][j] = true;
				else
					for (int k = 0; k < 4; ++k) {
						int y = i + dy[k];
						int x = j + dx[k];
						if (y < 0 || x < 0 || y >= n || x >= m)
							continue;
						if (irc[y][x] && matrix[i][j] >= matrix[y][x])
							irc[i][j] = true;
					}
			}
		}
		for (int i = n - 2; i >= 0; --i) {
			for (int j = m - 2; j >= 0; --j) {
				if (dr[i][j] || dc[i][j])
					drc[i][j] = true;
				else
					for (int k = 0; k < 4; ++k) {
						int y = i + dy[k];
						int x = j + dx[k];
						if (y < 0 || x < 0 || y >= n || x >= m)
							continue;
						if (drc[y][x] && matrix[i][j] >= matrix[y][x])
							drc[i][j] = true;
					}
			}
		}
		vector<pair<int, int>> ans; // answers
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (irc[i][j] && drc[i][j]) ans.push_back(pair<int, int>(i, j));
			}
		}
		return ans;
	}

public:
	// 85. Maximal Rectangle [M]
	// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
	/*
	1 0 1 0 0
	1 0 1 1 1
	1 1 1 1 1
	1 0 0 1 0
	*/
	int maximalRectangle(vector<vector<char> > &matrix) {
		if (matrix.empty())
			return 0;
		const int n = (int)matrix.size(), m = (int)matrix[0].size();
		vector<int> H(n, 0), L(n, 0), R(n, n);
		int res = 0;
		for (int i = 0; i < n; ++i) {
			int l = 0, r = m;
			// calculate L(i, j) from left to right
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '1') {
					++H[j];
					L[j] = max(L[j], l);
				}
				else {
					l = j + 1;
					H[j] = 0; L[j] = 0; R[j] = n;
				}
			}
			// calculate R(i, j) from right to left
			for (int j = n - 1; j >= 0; --j) {
				if (matrix[i][j] == '1') {
					R[j] = min(R[j], r);
					res = max(res, H[j] * (R[j] - L[j]));
				}
				else {
					r = j;
				}
			}
		}
		return res;
	};

	// 221. Maximal Square [M]
	// Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
	// Time: O(nm), Space: O(m)
	int maximalSquare(vector<vector<char>>& a) {
		if (a.empty())
			return 0;
		const int n = (int)a.size(), m = (int)a[0].size();
		Grid f(2, vector<int>(m, 0));
		int res = 0;

		for (int j = 0; j < m; ++j) {
			f[0][j] = a[0][j] - '0';
			res = max(res, f[0][j]);
		}

		for (int i = 1; i < n; ++i) {
			f[i % 2][0] = a[i][0] - '0';
			for (int j = 0; j < m; ++j) {
				if (a[i][j] == '1') {
					f[i % 2][j] = min(f[i % 2][j - 1], min(f[(i - 1) % 2][j], f[(i - 1) % 2][j - 1])) + 1;
					res = max(res, f[i % 2][j]);
				}
				else {
					f[i % 2][j] = 0;
				}
			}
		}
		return res * res;
	}

	// 174. Dungeon Game
	// Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.
	// top left to bottom right
	int calculateMinimumHP(vector<vector<int> > &dungeon) {
		int m = (int)dungeon.size();
		int n = (int)dungeon[0].size();
		vector<vector<int>> dp(m, vector<int>(n));
		dp[m - 1][n - 1] = max(1, 1 - dungeon[m - 1][n - 1]);
		for (int i = m - 2; i >= 0; --i) {
			dp[i][n - 1] = max(1, dp[i + 1][n - 1] - dungeon[i][n - 1]);
		}
		for (int j = n - 2; j >= 0; --j) {
			dp[m - 1][j] = max(1, dp[m - 1][j + 1] - dungeon[m - 1][j]);
		}
		for (int i = m - 2; i >= 0; --i) {
			for (int j = n - 2; j >= 0; --j) {
				dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
			}
		}
		return dp[0][0];
	}

	// 62. Unique Paths [M]
	// A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
	// How many possible unique paths are there?
	// f[i][j] = f[i-1][j] + f[i][j-1]
	int uniquePaths(int m, int n) {
		vector<int> f(n, 0);
		f[0] = 1;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				f[j] = f[j] + f[j - 1];
			}
		}
		return f[n - 1];
	}

	// 63. Unique Paths II [M]
	// With obstacles
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		auto m = obstacleGrid.size();
		auto n = obstacleGrid[0].size();

		if (n == 0 || m == 0 || obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) return 0;

		vector<int> f(n, 0);
		f[0] = 1;

		for (auto i = 0; i < m; ++i) {
			f[0] = f[0] == 0 ? 0 : (!obstacleGrid[i][0]);
			for (int j = 1; j < n; ++j) if (!obstacleGrid[i][j]) {
				f[j] = f[j] + f[j - 1];
			}
			else {
				f[j] = 0;
			}
		}
		return f[n - 1];
	} 
};
