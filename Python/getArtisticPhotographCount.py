# Writes any import statements here


def getArtisticPhotographCount(N, C, X, Y):
  """
  For every A, find how many Ps are there in front, how mnay Bs are there in back.
  Find Ps, sumP[r] - sumP[l] etc.
  Time complexity: O(N)
  Space complexity: O(N)
  """
  sumP = [0 for i in range(N + 1)]
  sumB = [0 for i in range(N + 1)]

  for i, c in enumerate(C):
    sumP[i + 1] = sumP[i] + int(c == 'P')
    sumB[i + 1] = sumB[i] + int(c == 'B')

  def getP(l, r):
    left = 0 if l < 0 else (sumP[l] if l <= N else sumP[N])
    right = (sumP[r + 1] if
             (r + 1 >= 0) else sumP[0]) if r + 1 <= N else sumP[N]
    return right - left

  def getB(l, r):
    left = 0 if l < 0 else (sumB[l] if l <= N else sumB[N])
    right = (sumB[r + 1] if
             (r + 1 >= 0) else sumB[0]) if r + 1 <= N else sumB[N]
    return right - left

  res = 0
  for i, c in enumerate(C):
    if c == 'A':
      numP = getP(i - Y, i - X)
      numB = getB(i + X, i + Y)
      res += numP * numB

      numB = getB(i - Y, i - X)
      numP = getP(i + X, i + Y)
      res += numP * numB

  return res


getArtisticPhotographCount(5, 'APABA', 1, 2)
getArtisticPhotographCount(5, 'APABA', 2, 3)
getArtisticPhotographCount(8, '.PBAAP.B', 1, 3)
