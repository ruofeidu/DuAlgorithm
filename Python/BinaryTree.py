class TreeNode(object):
  """Definition for a binary tree node."""

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


# 222. Count Complete Tree Nodes
# Given a complete binary tree, count the number of nodes.
# @param {TreeNode} root
# @return {integer}
def countNodes(self, root):
  if root is None:
    return 0

  node, level = root, 0
  while node.left is not None:
    node = node.left
    level += 1

  # Binary search.
  left, right = 1 << level, 1 << (level + 1)
  while left < right:
    mid = left + ((right - left) >> 1)
    if not self.exist(root, mid):
      right = mid
    else:
      left = mid + 1

  return left - 1


# Check if the nth node exist.
def exist(self, root, n):
  k = 1
  while k <= n:
    k <<= 1
  k >>= 2

  node = root
  while k > 0:
    if (n & k) == 0:
      node = node.left
    else:
      node = node.right
    k >>= 1
  return node is not None


# 226. Invert Binary Tree [E]
def invertTree(self, root):
  """
    :type root: TreeNode
    :rtype: TreeNode
    """
  if root is None:
    return
  tmp = self.invertTree(root.left)
  root.left = self.invertTree(root.right)
  root.right = tmp
  return root
