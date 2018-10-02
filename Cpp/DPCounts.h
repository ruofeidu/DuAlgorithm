#pragma once
#include "common.h"

namespace DPCounts {
	// 70. Climbing Stairs
	// you are climbing a stair case. It takes n steps to reach to the top.
	// Each time you can either climb 1 or 2 steps.
	// In how many distinct ways can you climb to the top?
	int climbStairs(int n) {
		if (n <= 0) return 0;
		vector<int> f(3, 1);
		for (int i = 2; i <= n; ++i) {
			f[i % 3] = f[(i - 1) % 3] + f[(i - 2) % 3];
		}
		return f[n % 3];
	}

	// 91. Decode Ways [M]
	// A message containing letters from A-Z is being encoded to numbers using the following mapping: 'Z' -> 26
	// Given a non - empty string containing only digits, determine the total number of ways to decode it.
	int numDecodings(string s) {
		int n = s.size();
		if (n == 0) return 0;
		vector<int> f(n + 1, 0);
		f[0] = 1;
		f[1] = (s[0] != '0');
		for (int i = 2; i <= n; ++i) {
			if (s[i - 1] == '0' && (s[i - 2] == '0' || s[i - 2] > '2')) {
				return 0;
			}
			else
				if (s[i - 1] == '0') {
					f[i] = f[i - 2];
				}
				else
					if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')) {
						f[i] = f[i - 1] + f[i - 2];
					}
					else {
						f[i] = f[i - 1];
					}
		}
		return f[n];
	}


	// 96. Unique Binary Search Trees
	// Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?
	int numTrees(int n) {
		if (n == 0) return 1;
		vector<int> f(n + 1, 0);
		f[0] = 1;
		f[1] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int k = 1; k <= i; ++k) {
				f[i] += f[k - 1] * f[i - k];
			}
		}
		return f[n];
	}
}