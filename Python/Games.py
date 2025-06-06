# 299. Bulls and Cows
# Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows.
def getHint(self, secret, guess):
  """
	:type secret: str
	:type guess: str
	:rtype: str
	"""
  a, b = 0, 0
  c = [0 for c in range(len(guess))]
  gc = [0 for c in range(10)]
  sc = [0 for c in range(10)]
  for i, g in enumerate(guess):
    if g == secret[i]:
      c[i] = 1
      a += 1
    else:
      gc[int(g)] += 1
      sc[int(secret[i])] += 1

  for i in range(10):
    b += min(gc[i], sc[i])
  return "%dA%dB" % (a, b)
