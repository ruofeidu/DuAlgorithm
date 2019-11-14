#pragma once
#include "common.h"

class Permutations {
  // 47. Unique Permutation
  using Iter = vector<pair<int, int>>::const_iterator;
  void DFSUniquePermutation(Iter first, Iter last, vector<int> &p,
                            vector<vector<int>> &result, size_t n) {
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
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    do {
      result.push_back(nums);
    } while (nextPermutation(nums.begin(), nums.end()));
    return result;
  }

  template <typename T>
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

  // 77. Combinations
  // Given two integers n and k, return all possible combinations of k numbers
  // out of 1 ... n.
 public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> path;
    int depth = 0;
    combineDFS(res, path, 1, n, k, 0);
    return res;
  }

  void combineDFS(vector<vector<int>> &res, vector<int> &path, int cur, int n,
                  int k, int depth) {
    if (depth == k) {
      vector<int> new_path(k);
      for (int i = 0; i < k; ++i) new_path[i] = path[i];
      res.push_back(new_path);
      return;
    }

    for (int i = cur; i <= n - (k - depth - 1); ++i) {
      path.push_back(i);
      combineDFS(res, path, i + 1, n, k, depth + 1);
      path.pop_back();
    }
  }

  // 78. Subsets
  // Given a set of distinct integers, nums, return all possible subsets (the
  // power set).
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> path;
    sort(nums.begin(), nums.end());

    subsetsDFS(nums, nums.begin(), path, res);
    return res;
  }

  static void subsetsDFS(const vector<int> &S, vector<int>::iterator start,
                         vector<int> &path, vector<vector<int>> &result) {
    result.push_back(path);
    for (auto i = start; i < S.end(); i++) {
      if (i != start && *i == *(i - 1)) continue;
      path.push_back(*i);
      subsetsDFS(S, i + 1, path, result);
      path.pop_back();
    }
  }

  // 90. Subsets II
  // Given a collection of integers that might contain duplicates, nums, return
  // all possible subsets (the power set).
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    const int n = (int)nums.size();
    sort(nums.begin(), nums.end());

    vector<int> uniques(nums);
    vector<int> counts(n, 1);

    int k = 0;
    for (int i = 1; i < n; ++i) {
      if (nums[i] == uniques[k]) {
        ++counts[k];
      } else {
        uniques[++k] = nums[i];
      }
    }
    ++k;

    vector<vector<int>> ans;
    vector<int> path;
    subsetWithDupDFS(uniques, counts, k, 0, path, ans);
    return ans;
  }

  void subsetWithDupDFS(vector<int> &uniques, vector<int> &counts, int n,
                        int dep, vector<int> &path, vector<vector<int>> &ans) {
    if (dep >= n) {
      ans.push_back(path);
      return;
    }
    subsetWithDupDFS(uniques, counts, n, dep + 1, path, ans);

    for (int i = 1; i <= counts[dep]; ++i) {
      path.push_back(uniques[dep]);
      subsetWithDupDFS(uniques, counts, n, dep + 1, path, ans);
    }
    for (int i = 0; i < counts[dep]; ++i) path.pop_back();
  }

  // 93. Restore IP Addresses
  // Given a string containing only digits, restore it by returning all possible
  // valid IP address combinations.
  // Input: "25525511135"
  // Output: ["255.255.11.135", "255.255.111.35"]
  vector<string> restoreIpAddresses(string s) {
    vector<string> ans;
    if (s.empty() || s.size() < 4) return ans;
    restoreIpAddressesDFS(ans, s, "", 0);
    return ans;
  }

  void restoreIpAddressesDFS(vector<string> &ans, string s, string path,
                             int depth) {
    if (depth >= 4) {
      ans.push_back(path);
      return;
    }
    if (s.empty() || s.size() < 4 - depth || s.size() > 3 * (4 - depth)) return;

    if (depth == 3) {
      if (s[0] == '0') {
        if (s.size() != 1) return;
        return restoreIpAddressesDFS(ans, s.substr(1), path + s.substr(0, 1),
                                     depth + 1);
      }
      int ip = stoi(s);
      if (ip <= 255) return restoreIpAddressesDFS(ans, "", path + s, depth + 1);
      return;
    }
    if (s[0] == '0')
      return restoreIpAddressesDFS(ans, s.substr(1),
                                   path + s.substr(0, 1) + ".", depth + 1);

    if (depth < 0) return;

    for (int i = 0; i < 2; ++i)
      if (s.size() >= i + 1) {
        restoreIpAddressesDFS(ans, s.substr(i + 1),
                              path + s.substr(0, i + 1) + ".", depth + 1);
      }

    if (stoi(s.substr(0, 3)) <= 255 && s.size() >= 3)
      restoreIpAddressesDFS(ans, s.substr(3), path + s.substr(0, 3) + ".",
                            depth + 1);
  }

  // 47. Permutations II
  // Given a collection of numbers that might contain duplicates, return all
  // possible unique permutations.
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
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    unordered_map<int, int> count_map;

    for_each(nums.begin(), nums.end(), [&count_map](int e) {
      if (count_map.find(e) != count_map.end()) {
        ++count_map[e];
      } else {
        count_map[e] = 1;
      }
    });

    vector<pair<int, int>> elements;
    for_each(count_map.begin(), count_map.end(),
             [&elements](const pair<int, int> &e) { elements.push_back(e); });

    vector<vector<int>> result;
    vector<int> path;

    size_t n = nums.size();
    DFSUniquePermutation(elements.begin(), elements.end(), path, result, n);
    return result;
  }

  // 31. Next Permutation
  // Implement next permutation, which rearranges numbers into the
  // lexicographically next greater permutation of numbers.
  // 1,2,3 -> 1,3,2
  // 3, 2, 1 -> 1, 2, 3
  // 1, 1, 5 -> 1, 5, 1
  void nextPermutation(vector<int> &nums) {
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

    if (pos == -1)
      sort(nums.begin() + pos + 1, nums.end());
    else if (pos + 1 < n)
      sort(nums.begin() + pos + 1, nums.end());
  }

  // 60. Permutation Sequence
  // Given n and k, return the kth permutation sequence.
 public:
  string getPermutation(int n, int k) {
    string s(n, '0');
    string result;
    for (int i = 0; i < n; ++i) s[i] += i + 1;
    return kth_permutation(s, k);
  }

 private:
  int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) result *= i;
    return result;
  }

  template <typename Sequence>
  Sequence kth_permutation(const Sequence &seq, int k) {
    const int n = (int)seq.size();
    Sequence S(seq);
    Sequence result;
    int base = factorial(n - 1);
    --k;
    for (int i = n - 1; i > 0; k %= base, base /= i, --i) {
      auto a = next(S.begin(), k / base);
      result.push_back(*a);
      S.erase(a);
    }
    result.push_back(S[0]);
    return result;
  }

  // 17. Letter Combinations of a Phone Number
  // Given a string containing digits from 2-9 inclusive, return all possible
  // letter combinations that the number could represent.
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
  vector<string> keyboard{" ",   "",    "abc",  "def", "ghi",
                          "jkl", "mno", "pqrs", "tuv", "wxyz"};

  void DFS_letterCombinations(const string &digits, size_t cur, string cur_str,
                              vector<string> &ans) {
    if (cur == digits.size()) {
      ans.push_back(cur_str);
    }
    for (auto c : keyboard[digits[cur] - '0']) {
      DFS_letterCombinations(digits, cur + 1, cur_str + c, ans);
    }
  }

  // 22. Generate Parentheses
  // Given n pairs of parentheses, write a function to generate all combinations
  // of well-formed parentheses.
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
  void DFSgenerateParenthesis(int n, string &sol, vector<string> &ans, int l,
                              int r) {
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

  // 95. Unique Binary Search Trees II
  // Given an integer n, generate all structurally unique BST's (binary search
  // trees) that store values 1 ... n.
  /*
  Input: 3
  Output:
  [
    [1,null,3,2],
    [3,2,null,1],
    [3,1,null,null,2],
    [2,1,3],
    [1,null,2,null,3]
  ]
  Explanation:
  The above output corresponds to the 5 unique BST's shown below:

     1         3     3      2      1
          \       /     /      / \      \
           3     2     1      1   3      2
          /     /       \                 \
     2     1         2                 3
  */
  vector<TreeNode *> generateTrees(int n) {
    vector<TreeNode *> ans;
    if (n == 0) return ans;
    return generateTrees(1, n);
  }
  // 1 2 3

  TreeNode *cloneTree(TreeNode *root) {
    if (root == NULL) return NULL;
    TreeNode *node = new TreeNode(root->val);
    node->left = cloneTree(root->left);
    node->right = cloneTree(root->right);
    return node;
  }

  vector<TreeNode *> generateTrees(int lowerbound, int upperbound) {
    vector<TreeNode *> ans;
    if (upperbound < lowerbound) {
      ans.push_back(nullptr);
      return ans;
    }
    for (int k = lowerbound; k <= upperbound; ++k) {
      vector<TreeNode *> left = generateTrees(lowerbound, k - 1);
      vector<TreeNode *> right = generateTrees(k + 1, upperbound);
      for (auto i : left) {
        for (auto j : right) {
          TreeNode *root = new TreeNode(k);
          root->left = i;
          root->right = j;
          ans.push_back(root);
        }
      }
    }
    return ans;
  }
};
