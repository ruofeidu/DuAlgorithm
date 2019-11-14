#pragma once
#include "common.h"

namespace DFSTree {
int dfsLeafSimilar(vector<TreeNode*>& s) {
  while (true) {
    const auto node = s.back();
    s.pop_back();
    if (node->right) {
      s.emplace_back(node->right);
    }
    if (node->left) {
      s.emplace_back(node->left);
    }
    if (!node->left && !node->right) {
      return node->val;
    }
  }
}

bool leafSimilar(TreeNode* root1, TreeNode* root2) {
  vector<TreeNode *> s1{root1}, s2{root2};
  while (!s1.empty() && !s2.empty()) {
    if (dfsLeafSimilar(s1) != dfsLeafSimilar(s2)) {
      return false;
    }
  }
  return s1.empty() && s2.empty();
}

void addOperatorsDFS(string num, int target, long long diff, long long curNum,
                     string out, vector<string>& res) {
  if ((int)num.size() == 0 && curNum == target) res.push_back(out);

  for (int i = 1; i <= (int)num.size(); ++i) {
    string s = num.substr(0, i);
    string next = num.substr(i);
    long long n = stoll(s);
    if (s.size() > 1 && s[0] == '0') return;
    if (out.size() > 0) {
      addOperatorsDFS(next, target, n, curNum + n, out + "+" + s, res);
      addOperatorsDFS(next, target, -n, curNum - n, out + "-" + s, res);
      // 3-5*2
      addOperatorsDFS(next, target, diff * n, (curNum - diff) + diff * n,
                      out + "*" + s, res);
    } else {
      addOperatorsDFS(next, target, n, n, s, res);
    }
  }
}

vector<string> addOperators(string num, int target) {
  vector<string> res;
  addOperatorsDFS(num, target, 0, 0, "", res);
  return res;
}
}

class DFSLinear {
 public:
  // 39. Combination Sum [M]
  // Given a set of candidate numbers (candidates) (without duplicates) and a
  // target number (target), find all unique combinations in candidates where
  // the candidate numbers sums to target.
  // DFS O(n!)
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans;
    vector<int> sol;
    combinationSumDFS(candidates, target, sol, ans, 0);
    return ans;
  }

 private:
  void combinationSumDFS(vector<int>& candidates, int target, vector<int>& sol,
                         vector<vector<int>>& ans, int pos) {
    if (target == 0) {
      ans.push_back(sol);
      return;
    }
    for (int i = pos; i < (int)candidates.size(); ++i) {
      if (candidates[i] > target) return;
      sol.push_back(candidates[i]);
      combinationSumDFS(candidates, target - candidates[i], sol, ans, i);
      sol.pop_back();
    }
  }

  // 40. Combination Sum II
  // Given a collection of candidate numbers (candidates) and a target number
  // (target), find all unique combinations in candidates where the candidate
  // numbers sums to target.
 public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans;
    vector<int> sol;
    combinationSumDFS2(candidates, target, sol, ans, 0);
    return ans;
  }

 private:
  void combinationSumDFS2(vector<int>& candidates, int target, vector<int>& sol,
                          vector<vector<int>>& ans, int pos) {
    if (target == 0) {
      ans.push_back(sol);
      return;
    }
    int previous = INT_MIN;
    for (int i = pos; i < (int)candidates.size(); ++i) {
      if (previous == candidates[i]) continue;
      if (candidates[i] > target) return;
      previous = candidates[i];
      sol.push_back(candidates[i]);
      combinationSumDFS2(candidates, target - candidates[i], sol, ans, i + 1);
      sol.pop_back();
    }
  }

 public:
  // 241. Different Ways to Add Parentheses
  // Given a string of numbers and operators, return all possible results from
  // computing all the different possible ways to group numbers and operators.
  // The valid operators are +, - and *.
  vector<int> diffWaysToCompute(string s) {
    const int n = (int)s.size();
    vector<vector<vector<int>>> d(n + 1, vector<vector<int>>(n + 1));
    return diffWaysToComputeDFS(s, 0, n, d);
  }

 private:
  vector<int> diffWaysToComputeDFS(const string& s, const int l, const int r,
                                   vector<vector<vector<int>>>& d) {
    if (!d[l][r].empty()) {
      return d[l][r];
    }
    vector<int> res;
    for (int i = l; i < r; ++i) {
      const auto c = s[i];
      if (c == '+' || c == '-' || c == '*') {
        auto left = diffWaysToComputeDFS(s, l, i, d);
        auto right = diffWaysToComputeDFS(s, i + 1, r, d);
        for (const auto& x : left) {
          for (const auto& y : right) {
            if (c == '+') {
              res.emplace_back(x + y);
            } else if (c == '-') {
              res.emplace_back(x - y);
            } else {
              res.emplace_back(x * y);
            }
          }
        }
      }
    }
    // If the input string contains only number.
    if (res.empty()) {
      res.emplace_back(stoi(s.substr(l, r - l)));
    }
    d[l][r] = res;
    return d[l][r];
  }
};
