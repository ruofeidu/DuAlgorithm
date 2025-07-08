class UnionSet:

  def __init(self, n: int):
    self.roots = list(range(n))

  def find(self, i):
    while i != self.roots[i]:
      self.roots[i] = self.roots[self.roots[i]]
      i = self.roots[i]
    return i

  def union(self, a, b):
    self.roots[b] = self.find(b)
    self.roots[a] = self.roots[b]
