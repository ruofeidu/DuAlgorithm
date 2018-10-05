# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Item(object):
    def __init__(self, _node, _level):
        self.node = _node
        self.level = _level
            
# 199. Binary Tree Right Side View
# Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
class Solution(object):
    def rightSideView(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        ans = []
        if root is None:
            return ans
        q = [Item(root, 0)]
        last = q[0]
        while len(q) > 0:
            cur = q.pop(0)
            if cur.level > last.level:
                ans.append(last.node.val)
            last = cur
            if cur.node.left:
                q.append(Item(cur.node.left, cur.level + 1))
            if cur.node.right:
                q.append(Item(cur.node.right, cur.level + 1))
        ans.append(last.node.val)
        return ans
        