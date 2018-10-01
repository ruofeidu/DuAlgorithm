#pragma once
#include "common.h"

class Permutations {
	// 47. Unique Permutation
	using Iter = vector<pair<int, int>>::const_iterator;
	void DFSUniquePermutation(Iter first, Iter last, vector<int> &p, vector<vector<int>> &result, size_t n) {
		if (n == p.size()) {
			result.push_back(p);
		}
		for (auto i = first; i != last; ++i) {
			int count = 0;
			for (auto j = p.begin(); j != p.end(); ++j) {
				if (i->first == *j) {
					++count;
				}
			}

			if (count < i->second) {
				p.push_back(i->first);
				DFSUniquePermutation(first, last, p, result, n);
				p.pop_back();
			}
		}
	}

	// Full Permutation
	// 46. Permutations
	// Given a collection of distinct integers, return all possible permutations.
	/*
	Input: [1,2,3]
	Output:
	[
	  [1,2,3],
	  [1,3,2],
	  [2,1,3],
	  [2,3,1],
	  [3,1,2],
	  [3,2,1]
	]
	*/
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do {
			result.push_back(nums);
		} while (nextPermutation(nums.begin(), nums.end()));
		return result;
	}

	template<typename T>
	bool nextPermutation(T first, T last) {
		const auto rFirst = reverse_iterator<T>(last);
		const auto rLast = reverse_iterator<T>(first);

		// begin from the second last element to the first element.
		auto pivot = next(rFirst);

		// find pivot, which is the first element that is no less than its success
		while (pivot != rLast && *pivot >= *prev(pivot)) ++pivot;

		if (pivot == rLast) {
			std::reverse(rFirst, rLast);
			return false;
		}

		// find the first element that is greater than pivot
		auto change = find_if(rFirst, pivot, bind1st(less<int>(), *pivot));

		swap(*change, *pivot);
		std::reverse(rFirst, pivot);

		return true;
	}

	// 47. Permutations II
	// Given a collection of numbers that might contain duplicates, return all possible unique permutations.
	/*
	Input: [1,1,2]
	Output:
	[
	  [1,1,2],
	  [1,2,1],
	  [2,1,1]
	]
	*/
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		unordered_map<int, int> count_map;

		for_each(nums.begin(), nums.end(), [&count_map](int e) {
			if (count_map.find(e) != count_map.end()) {
				++count_map[e];
			}
			else
			{
				count_map[e] = 1;
			}
		});

		vector<pair<int, int>> elements;
		for_each(count_map.begin(), count_map.end(), [&elements](const pair<int, int> &e) {
			elements.push_back(e);
		});

		vector<vector<int>> result;
		vector<int> path;

		size_t n = nums.size();
		DFSUniquePermutation(elements.begin(), elements.end(), path, result, n);
		return result;
	}

	// 31. Next Permutation
	// Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
	// 1,2,3 -> 1,3,2
	// 3, 2, 1 -> 1, 2, 3
	// 1, 1, 5 -> 1, 5, 1
	void nextPermutation(vector<int>& nums) {
		const int n = (int)nums.size();
		if (n < 2) return;
		int pos = -1, bid = -1;
		for (int i = n - 1; i >= 0; --i) {
			if (nums[i] > nums[i - 1]) {
				pos = i - 1;
				bid = i;
			}
			if (pos > -1) break;
		}

		if (pos != -1) {
			for (int i = pos + 1; i < n; ++i) {
				if (nums[i] > nums[pos] && nums[i] < nums[bid]) {
					bid = i;
				}
			}
			swap(nums[pos], nums[bid]);
		}

		if (pos == -1) sort(nums.begin() + pos + 1, nums.end()); else
			if (pos + 1 < n) sort(nums.begin() + pos + 1, nums.end());
	}

	// 17. Letter Combinations of a Phone Number
	// Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
	// Input: "23"
	// Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
public:
	vector<string> letterCombinations(string digits) {
		vector<string> ans;
		if (digits.empty()) return ans;
		DFS_letterCombinations(digits, 0, "", ans);
		return ans;
	}

private:
	vector<string> keyboard{ " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

	void DFS_letterCombinations(const string &digits, size_t cur, string cur_str, vector<string> &ans) {
		if (cur == digits.size()) {
			ans.push_back(cur_str);
		}
		for (auto c : keyboard[digits[cur] - '0']) {
			DFS_letterCombinations(digits, cur + 1, cur_str + c, ans);
		}
	}

	// 22. Generate Parentheses
	// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
	// n = 3
	/*
	[
	  "((()))",
	  "(()())",
	  "(())()",
	  "()(())",
	  "()()()"
	]
	*/
public:
	vector<string> generateParenthesis(int n) {
		vector<string> ans;
		if (n == 0) return ans;
		string sol = "";
		DFSgenerateParenthesis(n, sol, ans, 0, 0);
		return ans;
	}

private:
	void DFSgenerateParenthesis(int n, string& sol, vector<string> &ans, int l, int r) {
		if (l == n && r == n) {
			ans.push_back(sol);
			return;
		}
		if (l < n) {
			sol.push_back('(');
			DFSgenerateParenthesis(n, sol, ans, l + 1, r);
			sol.pop_back();
		}

		if (r < n && l > r) {
			sol.push_back(')');
			DFSgenerateParenthesis(n, sol, ans, l, r + 1);
			sol.pop_back();
		}
	}
};
