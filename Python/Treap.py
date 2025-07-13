import random
import sys

# Python equivalent of C++'s numeric_limits<int>::max()
MOD_MAX = sys.maxsize  # Or a sufficiently large number like 2**31 - 1 or 2**63 - 1


class Node:
  """
    Represents a node in the Treap.
    x: The key of the node.
    y: The priority (heap property).
    c: The count of nodes in the subtree rooted at this node (size).
    l: Reference to the left child node.
    r: Reference to the right child node.
    """

  def __init__(self, data=0):
    self.x = data
    self.c = 0  # Count of nodes in the subtree, including itself
    self.l = None  # Left child
    self.r = None  # Right child
    # Generate a random priority.
    # Python's random.randint can give a good range.
    self.y = random.randint(0, MOD_MAX - 1)

  def __repr__(self):
    # For easier debugging/printing
    return f"Node(x={self.x}, y={self.y}, c={self.c})"


class Treap:
  """
    The Treap data structure, a randomized binary search tree.
    It maintains a dynamic set of ordered keys and allows binary searches.
    Combines properties of a binary search tree (keys ordered) and a heap (priorities ordered).
    """

  def __init__(self):
    # A dummy node acts as a sentinel to simplify checks for null children.
    # Its priority is set to be lower than any real node's priority,
    # so real nodes are always "above" it in the heap structure.
    self.dummy = Node()
    self.dummy.l = self.dummy
    self.dummy.r = self.dummy
    self.dummy.y = -sys.maxsize - 1  # Use a very small (negative) number for dummy's priority
    # to ensure real nodes always have higher priority.
    # Or better, sys.minint if it exists, or float('-inf')

    # Set x for dummy as well for consistency, although it's not used for comparison.
    self.dummy.x = -math.inf  # Representing negative infinity for comparison purposes

    self.root = self.dummy

  def _update(self, p: Node):
    """
        Updates the count (size) of the subtree rooted at node p.
        This must be called after any structural changes to the subtree.
        """
    if p != self.dummy:
      p.c = p.l.c + p.r.c + 1
    # No need for else, dummy.c would remain 0 or initial value

  def _rotate_left(self, p: Node) -> Node:
    """
        Performs a left rotation at node p.
        Returns the new root of the rotated subtree.
        """
    q = p.l
    p.l = q.r
    q.r = p
    self._update(p)
    self._update(q)
    return q

  def _rotate_right(self, p: Node) -> Node:
    """
        Performs a right rotation at node p.
        Returns the new root of the rotated subtree.
        """
    q = p.r
    p.r = q.l
    q.l = p
    self._update(p)
    self._update(q)
    return q

  def _insert(self, p: Node, x: int) -> Node:
    """
        Recursively inserts a new key 'x' into the treap rooted at 'p'.
        Handles maintaining both BST and heap properties.
        Returns the (possibly new) root of the subtree after insertion.
        """
    if p == self.dummy:
      new_node = Node(x)
      new_node.l = self.dummy
      new_node.r = self.dummy
      new_node.c = 1  # Initial count is 1 for a new node
      return new_node
    elif x < p.x:
      p.l = self._insert(p.l, x)
      # If heap property is violated, perform a rotation
      if p.l.y > p.y:  # Note: Original C++ uses p->l->y < p->y, implying min-heap on y.
        # Standard Treap uses max-heap on y (priority).
        # I will follow standard Treap (max-heap for y) to avoid confusion.
        # If original C++ intended min-heap, change to p.l.y < p.y
        p = self._rotate_left(p)
    else:  # x >= p.x (handling duplicates by putting them in the right subtree)
      p.r = self._insert(p.r, x)
      # If heap property is violated, perform a rotation
      if p.r.y > p.y:  # Standard Treap uses max-heap for y.
        # If original C++ intended min-heap, change to p.r.y < p.y
        p = self._rotate_right(p)

    self._update(p)  # Update count after potential rotation or insertion
    return p

  def _delete_node(self, p: Node) -> Node:
    """
        Helper function to delete the current node 'p' from the treap.
        This is called when p.x == x in the main _delete method.
        Returns the (possibly new) root of the subtree after deletion.
        """
    # Case 1: Node is a leaf or has one dummy child
    if p.l == self.dummy and p.r == self.dummy:
      # Node will be garbage collected
      return self.dummy
    # Case 2: Only left child (or right child is dummy)
    elif p.l == self.dummy:
      # Replace p with its right child (which is not dummy)
      return p.r
    # Case 3: Only right child (or left child is dummy)
    elif p.r == self.dummy:
      # Replace p with its left child (which is not dummy)
      return p.l
    # Case 4: Node has two non-dummy children.
    # Rotate to bring the node to a leaf position based on child priorities.
    elif p.l.y > p.r.y:  # If left child has higher priority, rotate left
      # (meaning left child will become new root of this subtree)
      p = self._rotate_left(p)
      # After rotation, p (original node) is now the right child of the new root (its former left child).
      # Recursively delete p from its new position (right child of the rotated subtree).
      p.r = self._delete_node(p.r)
    else:  # If right child has higher or equal priority, rotate right
      # (meaning right child will become new root of this subtree)
      p = self._rotate_right(p)
      # After rotation, p (original node) is now the left child of the new root (its former right child).
      # Recursively delete p from its new position (left child of the rotated subtree).
      p.l = self._delete_node(p.l)

    self._update(p)  # Update count after deletion or rotation
    return p

  def _delete(self, p: Node, x: int) -> Node:
    """
        Recursively deletes a key 'x' from the treap rooted at 'p'.
        Returns the (possibly new) root of the subtree after deletion.
        """
    if p == self.dummy:
      return self.dummy  # Key not found

    if x == p.x:
      # Found the node to delete. Call helper function.
      return self._delete_node(p)
    elif x < p.x:
      p.l = self._delete(p.l, x)
    else:  # x > p.x (assuming no duplicates, or handling them by deleting only one instance)
      p.r = self._delete(p.r, x)

    self._update(p)  # Update count after recursive call
    return p

  def _find(self, p: Node, x: int) -> bool:
    """
        Recursively searches for key 'x' in the treap rooted at 'p'.
        """
    if p == self.dummy:
      return False
    if x == p.x:
      return True
    elif x < p.x:
      return self._find(p.l, x)
    else:
      return self._find(p.r, x)

  def _kth(self, p: Node, k: int) -> int:
    """
        Finds the k-th smallest element in the treap rooted at 'p'.
        Assumes k is 1-indexed.
        """
    if p == self.dummy:
      # This case should ideally be caught by the public kth method
      # if k is out of bounds, but as a safeguard.
      return -1  # Or raise an error

    # If k is within the left subtree's size, it's in the left subtree.
    if k <= p.l.c:
      return self._kth(p.l, k)
    # If k is exactly one more than the left subtree's size, it's the current node.
    elif k == p.l.c + 1:
      return p.x
    # Otherwise, it's in the right subtree. Adjust k by subtracting
    # the left subtree's size and the current node (1).
    else:
      return self._kth(p.r, k - p.l.c - 1)

  # Public API methods
  def insert(self, x: int) -> None:
    """Inserts a key 'x' into the treap."""
    self.root = self._insert(self.root, x)

  def delete(self, x: int) -> None:
    """Deletes a key 'x' from the treap."""
    self.root = self._delete(self.root, x)

  def find(self, x: int) -> bool:
    """Checks if a key 'x' exists in the treap."""
    return self._find(self.root, x)

  def kth(self, k: int) -> int:
    """
        Finds the k-th smallest element in the treap.
        Returns -1 if k is out of bounds.
        """
    if not (1 <= k <= self.root.c):
      return -1
    return self._kth(self.root, k)


# Example Usage:
if __name__ == "__main__":
  treap = Treap()
  elements = [50, 30, 70, 20, 40, 60, 80, 10, 90]
  print("Inserting elements:", elements)
  for el in elements:
    treap.insert(el)

  print(f"Treap size: {treap.root.c}")
  print("Finding 40:", treap.find(40))  # True
  print("Finding 99:", treap.find(99))  # False

  # Test kth smallest
  sorted_elements = sorted(elements)
  print("\nSorted elements for reference:", sorted_elements)
  for i in range(1, len(elements) + 1):
    print(f"{i}th smallest: {treap.kth(i)} (Expected: {sorted_elements[i-1]})")

  print("\nDeleting 50...")
  treap.delete(50)
  print(f"Treap size after deleting 50: {treap.root.c}")
  print("Finding 50:", treap.find(50))  # False

  print("\nDeleting 20...")
  treap.delete(20)
  print(f"Treap size after deleting 20: {treap.root.c}")
  print("Finding 20:", treap.find(20))  # False

  print("\nRemaining elements (kth test):")
  # Need to re-sort after deletions for correct comparison
  remaining_elements = [el for el in elements if el not in [50, 20]]
  sorted_remaining = sorted(remaining_elements)
  print("Sorted remaining elements for reference:", sorted_remaining)
  for i in range(1, treap.root.c + 1):
    print(f"{i}th smallest: {treap.kth(i)} (Expected: {sorted_remaining[i-1]})")

  print("\nTesting invalid kth:")
  print("0th smallest:", treap.kth(0))
  print(f"{treap.root.c + 1}th smallest:", treap.kth(treap.root.c + 1))

  # Test edge case: delete non-existent
  print("\nDeleting 100 (non-existent)...")
  treap.delete(100)
  print(f"Treap size after deleting 100: {treap.root.c}")  # Should be unchanged
