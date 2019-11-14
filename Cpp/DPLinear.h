#pragma once
#include "common.h"

class DP1D {
  // 42. Trapping Rain Water
  // Given n non-negative integers representing an elevation map where the width
  // of each bar is 1, compute how much water it is able to trap after raining.
  int trap(vector<int>& height) {
    const int n = (int)height.size();
    if (n < 3) return 0;
    vector<int> lmax(n, 0), rmax(n, 0);
    lmax[0] = height[0];
    rmax[n - 1] = height[n - 1];
    for (int i = 0; i < n - 1; ++i) {
      lmax[i + 1] = max(lmax[i], height[i + 1]);
      rmax[n - 2 - i] = max(rmax[n - 1 - i], height[n - 2 - i]);
    }
    int ans = 0;
    for (int i = 1; i < n - 1; ++i) {
      ans += min(lmax[i], rmax[i]) - height[i];
    }
    return ans;
  }

  // 256. Paint House
  // k = 3
  // There are a row of n houses, each house can be painted with one of the k
  // colors.
  // The cost of painting each house with a certain color is different.
  // You have to paint all the houses such that no two adjacent houses have the
  // same color.
  int minCost(vector<vector<int>>& costs) {
    if (costs.empty() || costs[0].empty()) return 0;
    vector<vector<int>> dp = costs;
    for (size_t i = 1; i < dp.size(); ++i) {
      for (size_t j = 0; j < 3; ++j) {
        dp[i][j] += min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
      }
    }
    return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
  }

  // 135. Candy [H]
  // There are N children standing in a line. Each child is assigned a rating
  // value. You are giving candies to these children subjected to the following
  // requirements : Each child must have at least one candy. Children with a
  // higher rating get more candies than their neighbors. What is the minimum
  // candies you must give ?
  // 1, 2, 3, 4, 5 ==>
  // 3, 2, 1, 2, 3 ==>
  // 1, 2, 1, 2, 1
  int candy(vector<int>& ratings) {
    const int n = (int)ratings.size();
    int ans = 0;
    vector<int> f(n, 1);  // longest increasing from left
    vector<int> g(n, 1);  // longest increasing from right
    for (int i = 1; i < n; ++i) {
      if (ratings[i] > ratings[i - 1]) f[i] = f[i - 1] + 1;
    }
    for (int i = n - 2; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) g[i] = g[i + 1] + 1;
    }
    for (int i = 0; i < n; ++i) {
      // cout << f[i] << "\t" << g[i] << endl;
      ans += max(f[i], g[i]);
    }
    return ans;
  }

  // 139. Word Break
  // Given a non-empty string s and a dictionary wordDict containing a list of
  // non-empty words, determine if s can be segmented into a space-separated
  // sequence of one or more dictionary words.
  bool wordBreak(string s, unordered_set<string>& wordDict) {
    const int n = (int)s.size(), m = (int)wordDict.size();
    if (n <= 0) return false;
    vector<bool> f(n + 1);
    f[0] = true;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= i; ++j)
        if (f[j - 1]) {
          if (wordDict.find(s.substr(j - 1, i - j + 1)) != wordDict.end()) {
            f[i] = true;
            break;
          }
        }
    }
    return f[n];
  }

  // 140. Word Break II
  // Given a non-empty string s and a dictionary wordDict containing a list of
  // non-empty words, add spaces in s to construct a sentence where each word is
  // a valid dictionary word. Return all such possible sentences.
  vector<string> wordBreak2(string s, unordered_set<string>& wordDict) {
    const int n = (int)s.size(), m = (int)wordDict.size();
    vector<string> ans;
    if (n <= 0) return ans;
    vector<bool> f(n + 1);
    vector<vector<int>> p(n + 1);
    f[0] = true;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= i; ++j)
        if (f[j - 1]) {
          if (wordDict.find(s.substr(j - 1, i - j + 1)) != wordDict.end()) {
            f[i] = true;
            p[i].push_back(j - 1);
          }
        }
    }
    if (!f[n]) return ans;
    findWordBreak(ans, f, p, s, n, "");
    return ans;
  }

  void findWordBreak(vector<string>& ans, vector<bool>& f,
                     vector<vector<int>>& p, string& s, int n, string path) {
    if (n <= 0) {
      ans.push_back(path);
      return;
    }
    if (!f[n]) return;
    for (int i = 0; i < p[n].size(); ++i) {
      int j = p[n][i];
      string newpath = path;
      if (newpath.empty()) {
        newpath = s.substr(j, n - j);
      } else {
        newpath = s.substr(j, n - j) + " " + newpath;
      }
      findWordBreak(ans, f, p, s, j, newpath);
    }
  }

  // 152. Maximum Product Subarray
  // Given an integer array nums, find the contiguous subarray within an array
  // (containing at least one number) which has the largest product.
  int maxProduct(vector<int>& nums) {
    if (nums.empty()) return 0;
    int res = nums[0], mn = nums[0], mx = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      int tmax = mx, tmin = mn;
      mx = max(max(nums[i], tmax * nums[i]), tmin * nums[i]);
      mn = min(min(nums[i], tmax * nums[i]), tmin * nums[i]);
      res = max(res, mx);
    }
    return res;
  }

  // 198. House Robber [E]
  // You are a professional robber planning to rob houses along a street. Each
  // house has a certain amount of money stashed, the only constraint stopping
  // you from robbing each of them is that adjacent houses have security system
  // connected and it will automatically contact the police if two adjacent
  // houses were broken into on the same night. Max.
  int rob(vector<int>& nums) {
    const int n = (int)nums.size();
    if (n == 0) return 0;
    vector<int> f(3);  // f[i] = maximum from 0 .. i - 1
    f[1] = nums[0];

    for (int i = 2; i <= n; ++i) {
      f[i % 3] = max(f[(i - 1) % 3], f[(i - 2) % 3] + nums[i - 1]);
    }

    return f[n % 3];
  }

  // 213. House Robber II [M]
  // All houses at this place are arranged in a circle.
  int rob2(vector<int>& nums) {
    const int n = (int)nums.size();
    if (n <= 1) return nums.empty() ? 0 : nums[0];
    return max(rob2(nums, 0, n - 1), rob2(nums, 1, n));
  }

  int rob2(vector<int>& nums, int l, int r) {
    if (r - l <= 1) return nums[l];
    vector<int> f(r, 0);
    f[l] = nums[l];
    f[l + 1] = max(nums[l], nums[l + 1]);
    for (int i = l + 2; i < r; ++i) {
      f[i] = max(nums[i] + f[i - 2], f[i - 1]);
    }
    return f.back();
  }

  // 312. Burst Balloons [H] [NOIP 2007?]
  // Given n balloons, indexed from 0 to n-1. Each balloon is painted with a
  // number on it represented by array nums. You are asked to burst all the
  // balloons. If the you burst balloon i you will get nums[left] * nums[i] *
  // nums[right] coins. Here left and right are adjacent indices of i. After the
  // burst, the left and right then becomes adjacent. Find the maximum coins you
  // can collect by bursting the balloons wisely.
  /*
          Input: [3,1,5,8]
          Output: 167
          Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  -->
     []
                                   coins =  3*1*5      +  3*5*8    +  1*3*8
     + 1*8*1   = 167
  */
  int maxCoins(vector<int>& nums) {
    const int n = (int)nums.size();
    vector<int> a;
    a.emplace_back(1);
    for (const auto& x : nums) a.emplace_back(x);
    a.emplace_back(1);

    vector<vector<int>> f(n + 2, vector<int>(n + 2));
    // f[i][j] indicates the maximum score we can get in [i, j]

    // k is number of bursts
    for (int k = 1; k <= n; ++k) {
      // infer [i, i + k]
      for (int i = 1; i <= n - k + 1; ++i) {
        int r = i + k - 1;
        for (int j = i; j <= r; ++j) {
          f[i][r] = max(f[i][r],
                        f[i][j - 1] + f[j + 1][r] + a[j] * a[i - 1] * a[r + 1]);
        }
      }
    }

    return f[1][n];
  }

  // 313. Super Ugly Number [M] [VH]
  // Super ugly numbers are positive numbers whose all prime factors are in the
  // given prime list primes of size k.
  /*
  Input: n = 12, primes = [2,7,13,19]
  Output: 32
  Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
  super ugly numbers given primes = [2,7,13,19] of size 4.
  */
  // Solution: f[i] = min(f[i], f[inx[j]] * primes[j]);
  // Time: O(n^2)
  // Space: O(n)
  int nthSuperUglyNumberN2(int n, vector<int>& primes) {
    const int m = (int)primes.size();
    vector<int> f(n, 1), idx(n, 0);
    for (int i = 1; i < n; ++i) {
      f[i] = INT_MAX;
      for (int j = 0; j < n; ++j) {
        f[i] = min(f[i], f[idx[j]] * primes[j]);
      }
      for (int j = 0; j < m; ++j) {
        if (f[i] == f[idx[j]] * primes[j]) {
          ++idx[j];
        }
      }
    }
    return f.back();
  }

  // Time:  O(n * k)
  // Space: O(n + k)
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    const int m = (int)primes.size();
    // min_heap
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>> heap;

    vector<int> uglies(n), idx(m), ugly_by_last_prime(n);
    uglies[0] = 1;

    for (int i = 0; i < m; ++i) {
      heap.emplace(primes[i], i);
    }
    for (int i = 1; i < n; ++i) {
      int k;
      tie(uglies[i], k) = heap.top();
      heap.pop();
      ugly_by_last_prime[i] = k;
      while (ugly_by_last_prime[++idx[k]] > k)
        ;  // average time: O(k)
      heap.emplace(uglies[idx[k]] * primes[k], k);
    }
    return uglies[n - 1];
  }
};
