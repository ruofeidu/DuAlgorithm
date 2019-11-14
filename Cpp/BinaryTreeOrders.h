#pragma once
#include "common.h"

namespace BinaryTreeOrders {
// 94. Binary Tree Inorder Traversal
vector<int> inorderTraversal(TreeNode* root) {
  stack<TreeNode*> s;
  typedef unsigned char byte;
  stack<byte> d;

  s.push(root);
  d.push(0);

  vector<int> ans;
  if (root == NULL) return ans;

  while (!s.empty()) {
    TreeNode* node = s.top();
    byte depth = d.top();

    if (depth == 0) {
      // first step, deal with left
      d.top() = 1;
      if (node->left != NULL) {
        s.push(node->left);
        d.push(0);
      }
    } else if (depth == 1) {
      // left done, deal itself
      ans.push_back(node->val);
      d.top() = 2;
    } else {
      d.pop();
      s.pop();
      if (node->right != NULL) {
        s.push(node->right);
        d.push(0);
      }
    }
  }
  return ans;
}

// 144. Binary Tree Preorder Traversal
vector<int> preorderTraversal(TreeNode* root) {
  vector<int> ans;
  if (root == nullptr) return ans;
  stack<TreeNode*> s;
  s.emplace(root);
  while (!s.empty()) {
    TreeNode* node = s.top();
    s.pop();
    ans.emplace_back(node->val);
    if (node->right) s.emplace(node->right);
    if (node->left) s.emplace(node->left);
  }
  return ans;
}

// 145. Binary Tree Postorder Traversal
vector<int> postorderTraversal(TreeNode* root) {
  vector<int> ans;
  if (root == nullptr) return ans;

  using DFSNode = pair<TreeNode*, bool>;
  stack<DFSNode> s;
  s.emplace(DFSNode(root, false));

  while (!s.empty()) {
    DFSNode t = s.top();
    s.pop();
    TreeNode* node = t.first;
    bool output = t.second;
    if (output) {
      ans.emplace_back(node->val);
    } else {
      s.push(DFSNode(node, true));
      if (node->right) s.emplace(DFSNode(node->right, false));
      if (node->left) s.emplace(DFSNode(node->left, false));
    }
  }
  return ans;
}

// 102. Binary Tree Level Order Traversal [M]
// Given a binary tree, return the level order traversal of its nodes' values.
// (ie, from left to right, level by level).
vector<vector<int>> levelOrder(TreeNode* root) {
  vector<vector<int>> res;
  if (root == nullptr) return res;
  using Level = pair<TreeNode*, int>;

  queue<Level> q;
  q.emplace(Level(root, 0));
  int curLevel = -1;

  while (!q.empty()) {
    Level node = q.front();
    q.pop();
    if (node.second > curLevel) {
      ++curLevel;
      vector<int> values(1, node.first->val);
      res.emplace_back(values);
    } else {
      res[curLevel].emplace_back(node.first->val);
    }
    if (node.first->left != nullptr)
      q.push(Level(node.first->left, curLevel + 1));
    if (node.first->right != nullptr)
      q.push(Level(node.first->right, curLevel + 1));
  }
  return res;
}

// 107. Binary Tree Level Order Traversal II
// Given a binary tree, return the bottom-up level order traversal of its nodes'
// values. (ie, from left to right, level by level from leaf to root).
vector<vector<int>> levelOrderBottom(TreeNode* root) {
  vector<vector<int>> res;
  if (root == nullptr) return res;
  typedef pair<TreeNode*, int> Level;

  queue<Level> q;
  q.push(Level(root, 0));
  int curLevel = -1;

  while (!q.empty()) {
    Level node = q.front();
    q.pop();
    if (node.second > curLevel) {
      ++curLevel;
      vector<int> values(1, node.first->val);
      res.push_back(values);
    } else {
      res[curLevel].push_back(node.first->val);
    }
    if (node.first->left != nullptr)
      q.push(Level(node.first->left, curLevel + 1));
    if (node.first->right != nullptr)
      q.push(Level(node.first->right, curLevel + 1));
  }

  for (int i = 0; i<res.size()>> 1; ++i) {
    swap(res[i], res[res.size() - i - 1]);
  }
  return res;
}

// 103. Binary Tree Zigzag Level Order Traversal
// Given a binary tree, return the zigzag level order traversal of its nodes'
// values. (ie, from left to right, then right to left for the next level and
// alternate between).
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
  vector<vector<int>> res;
  if (root == nullptr) return res;
  using Level = pair<TreeNode*, int>;

  queue<Level> q;
  q.push(Level(root, 0));
  int curLevel = -1;

  while (!q.empty()) {
    Level node = q.front();
    q.pop();
    if (node.second > curLevel) {
      ++curLevel;
      vector<int> values(1, node.first->val);
      res.emplace_back(values);
    } else {
      if (curLevel % 2 == 0) {
        res[curLevel].emplace_back(node.first->val);
      } else {
        res[curLevel].insert(res[curLevel].begin(), node.first->val);
      }
    }

    if (node.first->left != nullptr)
      q.push(Level(node.first->left, curLevel + 1));
    if (node.first->right != nullptr)
      q.push(Level(node.first->right, curLevel + 1));
  }
  return res;
}

// 331. Verify Preorder Serialization of a Binary Tree
// Given a string of comma separated values, verify whether it is a correct
// preorder traversal serialization of a binary tree. Find an algorithm without
// reconstructing the tree.
bool isValidSerialization(string preorder) {
  if (preorder.empty()) return false;
  istringstream in(preorder);
  vector<string> v;
  string val;
  int d = 0;
  while (getline(in, val, ',')) v.push_back(val);
  for (int i = 0; i < v.size() - 1; ++i) {
    if (v[i] == "#") {
      if (d == 0)
        return false;
      else
        --d;
    } else
      ++d;
  }
  return d != 0 ? false : v.back() == "#";
}
};

// 105. Construct Binary Tree from Preorder and Inorder Traversal
// Given preorder and inorder traversal of a tree, construct the binary tree.
// MLR LMR
class preorderInorder {
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return buildTree(preorder, 0, (int)preorder.size() - 1, inorder, 0,
                     (int)inorder.size() - 1);
  }

  TreeNode* buildTree(vector<int>& preorder, int pl, int pr,
                      vector<int>& inorder, int il, int ir) {
    printf("%d %d %d %d\n", pl, pr, il, ir);
    if (pr - pl != ir - il) return nullptr;
    if (pr - pl < 0 || ir - il < 0) return nullptr;
    int val = preorder[pl];
    TreeNode* root = new TreeNode(val);
    if (pl == pr) return root;
    int j = -1;
    for (int i = il; i <= ir; ++i)
      if (inorder[i] == val) {
        j = i;
        break;
      }
    // check if finds or not, assume we always find it
    root->left =
        buildTree(preorder, pl + 1, pl + 1 + (j - 1 - il), inorder, il, j - 1);
    root->right =
        buildTree(preorder, pr - (ir - j - 1), pr, inorder, j + 1, ir);
    return root;
  }
};

// 106. Construct Binary Tree from Inorder and Postorder Traversal
// Given inorder and postorder traversal of a tree, construct the binary tree.
class InorderPostorder {
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return buildTree(inorder, 0, (int)inorder.size() - 1, postorder, 0,
                     (int)postorder.size() - 1);
  }

  TreeNode* buildTree(vector<int>& inorder, int il, int ir,
                      vector<int>& postorder, int pl, int pr) {
    if (ir - il != pr - pl || pl > pr || il > ir) return nullptr;
    int val = postorder[pr];
    TreeNode* root = new TreeNode(val);

    if (pl == pr) return root;
    int j = -1;
    for (int i = il; i <= ir; ++i)
      if (inorder[i] == val) {
        j = i;
        break;
      }
    // check if finds or not
    root->left = buildTree(inorder, il, j - 1, postorder, pl, pl + j - 1 - il);
    root->right =
        buildTree(inorder, j + 1, ir, postorder, pr - 1 - (ir - j - 1), pr - 1);
    return root;
  }
};
