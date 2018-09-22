#pragma once
#include "common.h"

class DP2D {
public:
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
				if (ir[i][j - 1] && matrix[i][j] >= matrix[i][j - 1]) ir[i][j] = true;


			for (int j = m - 2; j >= 0; --j)
				if (dr[i][j + 1] && matrix[i][j] >= matrix[i][j + 1]) dr[i][j] = true;
		}


		for (int j = 0; j < m; ++j) {
			ic[0][j] = true;
			dc[n - 1][j] = true;
			irc[0][j] = true;
			drc[n - 1][j] = true;
			for (int i = 1; i < n; ++i)
				if (ic[i - 1][j] && matrix[i][j] >= matrix[i - 1][j]) ic[i][j] = true;

			for (int i = n - 2; i >= 0; --i)
				if (dc[i][j + 1] && matrix[i][j] >= matrix[i + 1][j]) dc[i][j] = true;
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
				if (irc[i][j] && drc[i][j]) ans.push_back(pair<int, int>(i, j));
			}
		}


		return ans;
	}



	// 85. Maximal Rectangle
	/*
	1 0 1 0 0
	1 0 1 1 1
	1 1 1 1 1
	1 0 0 1 0
	*/
public:
	int maximalRectangle(vector<vector<char> > &matrix) {
		if (matrix.empty()) return 0;
		const int m = (int)matrix.size();
		const int n = (int)matrix[0].size();
		vector<int> H(n, 0);
		vector<int> L(n, 0);
		vector<int> R(n, n);
		int ret = 0;
		for (int i = 0; i < m; ++i) {
			int left = 0, right = n;
			// calculate L(i, j) from left to right
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '1') {
					++H[j];
					L[j] = max(L[j], left);
				}
				else {
					left = j + 1;
					H[j] = 0; L[j] = 0; R[j] = n;
				}
			}
			// calculate R(i, j) from right to left
			for (int j = n - 1; j >= 0; --j) {
				if (matrix[i][j] == '1') {
					R[j] = min(R[j], right);
					ret = max(ret, H[j] * (R[j] - L[j]));
				}
				else {
					right = j;
				}
			}
		}
		return ret;
	};

	// 221. Maximal Square
	int maximalSquare(vector<vector<char> >& matrix) {
		int res = 0;
		for (int i = 0; i < matrix.size(); ++i) {
			vector<int> v(matrix[i].size(), 0);
			for (int j = i; j < matrix.size(); ++j) {
				for (int k = 0; k < matrix[j].size(); ++k) {
					if (matrix[j][k] == '1') ++v[k];
				}
				res = max(res, getSquareArea(v, j - i + 1));
			}
		}
		return res;
	}
	int getSquareArea(vector<int> &v, int k) {
		if (v.size() < k) return 0;
		int count = 0;
		for (int i = 0; i < v.size(); ++i) {
			if (v[i] != k) count = 0;
			else ++count;
			if (count == k) return k * k;
		}
		return 0;
	}


	// 174. Dungeon Game
	// https://leetcode.com/problems/dungeon-game/
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
};

