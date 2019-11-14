#pragma once
#include "common.h"

namespace Hashmaps {
// 1. Two Sum
// Given an array of integers, return indices of the two numbers such that they
// add up to a specific target.
vector<size_t> twoSum(vector<int>& nums, int target) {
  unordered_map<int, size_t> dict;
  vector<size_t> res;
  for (size_t i = 0; i < nums.size(); ++i) {
    int cur = nums[i];
    if (dict.find(cur) == dict.end()) {
      dict[target - cur] = i;
    } else {
      res.emplace_back(dict[nums[i]]);
      res.emplace_back(i);
      break;
    }
  }
  return res;
}

// 167. Two Sum II - Input array is sorted
// Given an array of integers that is already sorted in ascending order, find
// two numbers such that they add up to a specific target number.
vector<int> twoSumSorted(vector<int>& numbers, int target) {
  int l = 0, r = (int)numbers.size() - 1;
  while (l < r) {
    int s = numbers[l] + numbers[r];
    if (s > target)
      --r;
    else if (s < target)
      ++l;
    else
      return {l + 1, r + 1};
  }
  return {};
}

// 15. 3Sum
vector<vector<int>> threeSum(vector<int>& nums) {
  vector<vector<int>> result;
  if (nums.size() < 3) return result;
  sort(nums.begin(), nums.end());
  const int target = 0;
  auto last = nums.end();
  for (auto i = nums.begin(); i < last - 2; ++i) {
    auto j = i + 1;
    if (i > nums.begin() && *i == *(i - 1)) continue;
    auto k = last - 1;
    while (j < k) {
      if (*i + *j + *k < target) {
        ++j;
        while (*j == *(j - 1) && j < k) ++j;
      } else if (*i + *j + *k > target) {
        --k;
        while (*k == *(k + 1) && j < k) --k;
      } else {
        result.push_back({*i, *j, *k});
        ++j;
        --k;
        while (*j == *(j - 1) && *k == *(k + 1) && j < k) ++j;
      }
    }
  }
  return result;
}

// 16. 3Sum Closest
int threeSumClosest(vector<int>& nums, int target) {
  size_t n = nums.size();
  sort(nums.begin(), nums.end());
  int min_gap = INT_MAX;
  int ans = 0;
  for (auto a = nums.begin(); a < nums.end(); ++a) {
    auto b = next(a);
    auto c = prev(nums.end());

    while (b < c) {
      const int sum = *a + *b + *c;
      const int gap = abs(sum - target);
      if (gap < min_gap) {
        ans = sum;
        min_gap = gap;
      }
      if (sum < target)
        ++b;
      else
        --c;
    }
  }
  return ans;
}

// 18. 4Sum
vector<vector<int>> fourSum(vector<int>& nums, int target) {
  vector<vector<int>> result;
  if (nums.size() < 4) return result;
  sort(nums.begin(), nums.end());
  auto last = nums.end();

  for (auto i = nums.begin(); i < last - 3; ++i) {
    if (i > nums.begin() && *i == *(i - 1)) continue;
    for (auto ii = i + 1; ii < last - 2; ++ii) {
      if (ii > i + 1 && *ii == *(ii - 1)) continue;
      auto j = ii + 1;
      auto k = last - 1;
      while (j < k) {
        if (*i + *ii + *j + *k < target) {
          ++j;
          while (*j == *(j - 1) && j < k) ++j;
        } else if (*i + *ii + *j + *k > target) {
          --k;
          while (*k == *(k + 1) && j < k) --k;
        } else {
          result.push_back({*i, *ii, *j, *k});
          ++j;
          --k;
          while (*j == *(j - 1) && *k == *(k + 1) && j < k) ++j;
        }
      }
    }
  }
  return result;
}

// 49. Group Anagrams
// Given an array of strings, group anagrams together.
vector<vector<string>> groupAnagrams(vector<string>& strs) {
  size_t n = strs.size();
  int total = 0;
  unordered_map<string, int> strMap;
  vector<vector<string>> result;

  for (int i = 0; i < n; ++i) {
    string s = strs[i];
    sort(s.begin(), s.end());
    auto iter = strMap.find(s);
    if (iter == strMap.end()) {
      strMap[s] = total;
      vector<string> v;
      v.push_back(strs[i]);
      result.push_back(v);
      total = total + 1;
    } else {
      result[iter->second].push_back(strs[i]);
    }
  }

  return result;
}

// 3. Longest Substring Without Repeating Characters
// Given a string, find the length of the longest substring without repeating
// characters.
// Input: "abcabcbb"
// Output: 3
int lengthOfLongestSubstring(string s) {
  vector<int> d(256, -1);
  int last_repeat_pos = -1, ans = 0;
  for (int i = 0; i < s.size(); ++i) {
    char c = s[i];
    last_repeat_pos = max(last_repeat_pos, d[c]);
    ans = max(ans, i - last_repeat_pos);
    d[c] = i;
  }
  return ans;
}

// 316. Remove Duplicate Letters [M]
// Given a string which contains only lowercase letters, remove duplicate
// letters so that every letter appear once and only once. You must make sure
// your result is the smallest in lexicographical order among all possible
// results.
/*
        Given "bcabc"
        Return "abc"

        Given "cbacdcbc"
        Return "acdb"
*/
string removeDuplicateLetters(string s) {
  int m[256] = {0}, visited[256] = {0};
  string res = "0";
  for (auto a : s) ++m[a];
  for (auto a : s) {
    --m[a];
    if (visited[a]) continue;
    while (a < res.back() && m[res.back()]) {
      visited[res.back()] = 0;
      res.pop_back();
    }
    res += a;
    visited[a] = 1;
  }
  return res.substr(1);
}

// 219. Contains Duplicate II
// Given an array of integers and an integer k, find out whether there are two
// distinct indices i and j in the array such that nums[i] = nums[j] and the
// difference between i and j is at most k.
bool containsNearbyDuplicate(vector<int>& nums, int k) {
  unordered_map<int, int> m;
  int i = 0;
  for (int x : nums) {
    if (m.count(x) && i - m[x] <= k)
      return true;
    else
      m[x] = i;
    ++i;
  }
  return false;
}

// 325. Maximum Size Subarray Sum Equals k
// Given an array nums and a target value k, find the maximum length of a
// subarray that sums to k.
int maxSubArrayLen(vector<int>& nums, int k) {
  int n = (int)nums.size();
  if (n == 0) return 0;

  unordered_map<int, int> m;
  int sum = 0, res = 0;

  for (int i = 0; i < n; ++i) {
    sum += nums[i];
    if (sum == k) res = max(res, i + 1);
    if (m.find(sum - k) != m.end()) {
      res = max(res, i - m[sum - k]);
    }
    if (m.find(sum) == m.end()) {
      m[sum] = i;
    }
  }
  return res;
}

// 349. Intersection of Two Arrays [E]
// Given two arrays, write a function to compute their intersection.
// Time:  O(m + n)
// Space: O(min(m, n))
// See log time and O(1) space in Binary Search
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
  if (nums1.size() > nums2.size()) {
    return intersection(nums2, nums1);
  }

  unordered_set<int> s{nums1.cbegin(), nums1.cend()};
  vector<int> res;

  for (const auto x : nums2) {
    if (s.count(x)) {
      res.emplace_back(x);
      s.erase(x);
    }
  }
  return res;
}

// 525. Contiguous Array [M]
// Time: O(N)
// Space: O(N)
// nums  0, 1, 1, 1, 0, 0, 0
// dict 0:2, -1:0, 1:2, 2:3,
int findMaxLength(vector<int>& nums) {
  int res = 0, cnt = 0, n = (int)nums.size();
  unordered_map<int, int> dict{{0, -1}};
  for (int i = 0; i < n; ++i) {
    cnt += (nums[i] << 1) - 1;
    if (dict.count(cnt)) {
      res = max(res, i - dict[cnt]);
    } else {
      dict[cnt] = i;
    }
  }
  return res;
}

// 554. Brick Wall
// Given a block of walls with bricks of the same height but different width.
// Draw a vertical line from the top to the bottom and cross the least bricks.
int leastBricks(vector<vector<int>>& wall) {
  const int n = (int)wall.size();
  unordered_map<int, int> d;
  int res = n;

  for (const auto& w : wall) {
    const int m = (int)w.size();
    int c = 0;
    for (int i = 0; i < m - 1; ++i) {
      c += w[i];
      d[c] += 1;
      res = min(res, n - d[c]);
    }
  }

  return res;
}

// 340. Longest Substring with At Most K Distinct Characters
// Given a string, find the length of the longest substring T that contains at
// most k distinct characters.
int lengthOfLongestSubstringKDistinct(string s, int k) {
  int res = 0, left = 0;
  unordered_map<char, int> m;
  for (int i = 0; i < s.size(); ++i) {
    ++m[s[i]];
    while (m.size() > k) {
      if (--m[s[left]] == 0) m.erase(s[left]);
      ++left;
    }
    res = max(res, i - left + 1);
  }
  return res;
}

// 128. Longest Consecutive Sequence
// Given an unsorted array of integers, find the length of the longest
// consecutive elements sequence.
/*
Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
Therefore its length is 4.
*/
int longestConsecutive(vector<int>& nums) {
  unordered_map<int, bool> used;
  for (auto i : nums) used[i] = false;
  int res = 0;
  for (auto i : nums) {
    if (used[i]) continue;
    int length = 1;
    used[i] = true;
    for (int j = i + 1; used.find(j) != used.end(); ++j) {
      used[j] = true;
      ++length;
    }
    for (int j = i - 1; used.find(j) != used.end(); --j) {
      used[j] = true;
      ++length;
    }
    res = max(res, length);
  }
  return res;
}

// 205. Isomorphic Strings [E][VE]
// Given two strings s and t, determine if they are isomorphic.
bool isIsomorphic(string s, string t) {
  if (s.size() != t.size()) return false;
  vector<int> f(256, -1), g(256, -1);
  for (size_t i = 0; i < s.size(); ++i) {
    if (f[s[i]] < 0 && g[t[i]] < 0) {
      f[s[i]] = t[i];
      g[t[i]] = s[i];
    } else if (f[s[i]] != t[i]) {
      return false;
    }
  }
  return true;
}
}
