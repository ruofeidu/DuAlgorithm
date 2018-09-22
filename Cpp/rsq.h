#pragma once
#include "common.h"

class RSQ {
public:
	// 303. Range Sum Query - Immutable
	// 1D RSQ, O(n) time
	class NumArray {
	public:
		// O(n)
		NumArray(vector<int> &nums) {
			sums.resize(nums.size() + 1, 0);
			for (int i = 1; i <= nums.size(); ++i) sums[i] = sums[i - 1] + nums[i - 1];
		}

		// O(1)
		int sumRange(int i, int j) {
			return sums[j + 1] - sums[i];
		}
	private:
		vector<int> sums;
	};

	// 307. Range Sum Query - Mutable
	// 1D Updated RSQ, O(n log n), BIT
	/**
	*	C1 = A1
	*	C2 = A1 + A2
	*	C3 = A3
	*	C4 = A1 + A2 + A3 + A4
	*	C5 = A5
	*	C6 = A5 + A6
	*	C7 = A7
	*	C8 = A1 + A2 + A3 + A4 + A5 + A6 + A7 + A8
	**/
	class NumArrayMutable {
	public:
		// O(N log N)
		NumArrayMutable(vector<int> &nums) {
			num.resize(nums.size() + 1);
			bit.resize(nums.size() + 1);
			for (int i = 0; i < nums.size(); ++i) update(i, nums[i]);
		}

		// O (log N)
		void update(int i, int val) {
			int diff = val - num[i + 1];
			for (int j = i + 1; j < num.size(); j += (j & -j)) { // calc the low bit
				bit[j] += diff;
			}
			num[i + 1] = val;
		}

		// O (log N)
		int sumRange(int i, int j) {
			return getSum(j + 1) - getSum(i);
		}

		// O (log N)
		int getSum(int i) {
			int res = 0;
			for (int j = i; j > 0; j -= (j& -j)) {
				res += bit[j];
			}
			return res;
		}

	private:
		vector<int> num;
		vector<int> bit;
	};

	// 304. Range Sum Query 2D - Immutable
	// Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

	class NumMatrix {
	public:
		// sums[i, j] = sigma { matrx[0][0] ... matrix[i][j] }
		NumMatrix(vector<vector<int> > &matrix) {
			if (matrix.empty() || matrix[0].empty()) return;
			sums.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
			for (int i = 1; i <= matrix.size(); ++i) {
				for (int j = 1; j <= matrix[0].size(); ++j) {
					sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];
				}
			}
		}
		int sumRegion(int row1, int col1, int row2, int col2) {
			return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] - sums[row2 + 1][col1] + sums[row1][col1];
		}

	private:
		vector<vector<int> > sums;
	};

	// 308. Range Sum Query 2D - Mutable
	// Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).
	class NumMatrixMutable {
	public:
		NumMatrixMutable(vector<vector<int>> &matrix) {
			if (matrix.empty() || matrix[0].empty()) return;
			mat.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
			bit.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
			for (int i = 0; i < matrix.size(); ++i) {
				for (int j = 0; j < matrix[i].size(); ++j) {
					update(i, j, matrix[i][j]);
				}
			}
		}

		void update(int row, int col, int val) {
			int diff = val - mat[row + 1][col + 1];
			for (int i = row + 1; i < mat.size(); i += i&-i) {
				for (int j = col + 1; j < mat[i].size(); j += j&-j) {
					bit[i][j] += diff;
				}
			}
			mat[row + 1][col + 1] = val;
		}

		int sumRegion(int row1, int col1, int row2, int col2) {
			return getSum(row2 + 1, col2 + 1) - getSum(row1, col2 + 1) - getSum(row2 + 1, col1) + getSum(row1, col1);
		}

		int getSum(int row, int col) {
			int res = 0;
			for (int i = row; i > 0; i -= i&-i) {
				for (int j = col; j > 0; j -= j&-j) {
					res += bit[i][j];
				}
			}
			return res;
		}

		vector<vector<int>> mat;
		vector<vector<int>> bit;
	};
};