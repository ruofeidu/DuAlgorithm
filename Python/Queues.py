from typing import List
from collections import deque
from collections import Counter


# 225. Implement Stack using Queues
class Queue:

  def __init__(self):
    self.data = collections.deque()

  def push(self, x):
    self.data.append(x)

  def peek(self):
    return self.data[0]

  def pop(self):
    return self.data.popleft()

  def size(self):
    return len(self.data)

  def empty(self):
    return len(self.data) == 0


class MyStack:
  # initialize your data structure here.
  def __init__(self):
    self.q_ = Queue()
    self.top_ = None

  # @param x, an integer
  # @return nothing
  def push(self, x):
    self.q_.push(x)
    self.top_ = x

  # @return nothing
  def pop(self):
    for _ in range(self.q_.size() - 1):
      self.top_ = self.q_.pop()
      self.q_.push(self.top_)
    return self.q_.pop()

  # @return an integer
  def top(self):
    return self.top_

  # @return an boolean
  def empty(self):
    return self.q_.empty()


# Time Complexity: O(N)
# Space Complexity: O(K)
def getMaxDish(N: int, D: List[int], K: int) -> int:
  q = deque()
  counter = Counter()
  res = 0

  for dish in D:
    if counter[dish] < 1:
      res += 1
      counter[dish] += 1
      q.append(dish)
      if len(q) > K:
        dish_out = q.popleft()
        counter[dish_out] -= 1

  return res


if __name__ == "__main__":
  print(getMaxDish(6, [1, 2, 3, 3, 2, 1], 2))
