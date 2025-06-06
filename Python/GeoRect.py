# 223. Rectangle Area
# Find the total area covered by two rectilinear rectangles in a 2D plane.
# Input: 4 * 2 points, bottom left and top right
def computeArea(self, A, B, C, D, E, F, G, H):
  """
  :type A: int
  :type B: int
  :type C: int
  :type D: int
  :type E: int
  :type F: int
  :type G: int
  :type H: int
  :rtype: int
  """
  r1, r2 = (D - B) * (C - A), (H - F) * (G - E)
  b1, b2 = max(0, (min(C, G) - max(A, E))), max(0, (min(D, H) - max(B, F)))
  return r1 + r2 - b1 * b2
