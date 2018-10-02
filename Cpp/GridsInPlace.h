#pragma once
#include "common.h"

namespace GridsInPlace {
	// 48. Rotate Image
	// Rotate the image by 90 degrees (clockwise).
	void rotate(vector<vector<int>>& matrix) {
		size_t n = matrix.size();
		size_t m = n - 1;
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < n - i; ++j) {
				swap(matrix[i][j], matrix[m - j][m - i]);
			}
		}

		for (size_t i = 0; i < n / 2; ++i) {
			for (size_t j = 0; j < n; ++j) {
				swap(matrix[i][j], matrix[m - i][j]);
			}
		}
	}

	// 73. Set Matrix Zeroes
	// Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.
	void setZeroes(vector<vector<int>>& matrix) {
		const size_t n = matrix.size();
		const size_t m = matrix[0].size();

		bool first_row_zero = false;
		bool first_col_zero = false;

		for (size_t j = 0; j < m; ++j) {
			if (matrix[0][j] == 0) {
				first_row_zero = true;
				break;
			}
		}

		for (size_t i = 0; i < n; ++i) {
			if (matrix[i][0] == 0) {
				first_col_zero = true;
				break;
			}
		}

		for (size_t i = 1; i < n; ++i) {
			for (size_t j = 1; j < m; ++j) {
				if (matrix[i][j] == 0) {
					matrix[0][j] = 0;
					matrix[i][0] = 0;
				}
			}
		}

		for (size_t i = 1; i < n; ++i) {
			for (size_t j = 1; j < m; ++j) {
				if (matrix[i][0] == 0 || matrix[0][j] == 0) {
					matrix[i][j] = 0;
				}
			}
		}

		if (first_row_zero) {
			for (size_t j = 0; j < m; ++j) {
				matrix[0][j] = 0;
			}
		}

		if (first_col_zero) {
			for (size_t i = 0; i < n; ++i) {
				matrix[i][0] = 0;
			}
		}
	}
}