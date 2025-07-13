from typing import List


def getNumJumps(N: int, F: int, P: List[int]) -> int:
  if F < 1:
    return 0

  P.sort()
  num_jumps = 0

  for i in range(F):
    if i < F - 1:
      delta = P[i + 1] - P[i] - 1
      num_jumps += delta
    else:
      num_jumps += N - P[i] - 1 + F

  return num_jumps


print(getNumJumps(6, 3, [5, 2, 4]))
# print(getNumJumps(7, 3, [1, 3, 5]))
