#pragma once
#include "common.h"

class QuadNode {
 public:
  bool val;
  bool isLeaf;
  QuadNode* topLeft;
  QuadNode* topRight;
  QuadNode* bottomLeft;
  QuadNode* bottomRight;

  QuadNode() {}

  QuadNode(bool _val, bool _isLeaf, QuadNode* _topLeft, QuadNode* _topRight,
           QuadNode* _bottomLeft, QuadNode* _bottomRight) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = _topLeft;
    topRight = _topRight;
    bottomLeft = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

class QuadTree {
 public:
  QuadNode* construct(vector<vector<int>>& grid) {
    if (grid.empty()) {
      return nullptr;
    }
    return dfs(grid, 0, 0, (int)grid.size());
  }

 private:
  QuadNode* dfs(const Grid& grid, int x, int y, int l) {
    if (l == 1) {
      return new QuadNode(grid[x][y] == 1, true, nullptr, nullptr, nullptr,
                          nullptr);
    }
    int half = l / 2;
    auto topLeftNode = dfs(grid, x, y, half);
    auto topRightNode = dfs(grid, x, y + half, half);
    auto bottomLeftNode = dfs(grid, x + half, y, half);
    auto bottomRightNode = dfs(grid, x + half, y + half, half);
    if (topLeftNode->isLeaf && topRightNode->isLeaf && bottomLeftNode->isLeaf &&
        bottomRightNode->isLeaf && topLeftNode->val == topRightNode->val &&
        topRightNode->val == bottomLeftNode->val &&
        bottomLeftNode->val == bottomRightNode->val) {
      return new QuadNode(topLeftNode->val, true, nullptr, nullptr, nullptr,
                          nullptr);
    }
    return new QuadNode(true, false, topLeftNode, topRightNode, bottomLeftNode,
                        bottomRightNode);
  }
};
