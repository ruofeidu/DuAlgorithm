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
		vector<TreeNode*> s1{ root1 }, s2{ root2 };
		while (!s1.empty() && !s2.empty()) {
			if (dfsLeafSimilar(s1) != dfsLeafSimilar(s2)) {
				return false;
			}
		}
		return s1.empty() && s2.empty();
	}

	void addOperatorsDFS(string num, int target, long long diff, long long curNum, string out, vector<string> &res) {
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
				addOperatorsDFS(next, target, diff * n, (curNum - diff) + diff * n, out + "*" + s, res);
			}
			else {
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