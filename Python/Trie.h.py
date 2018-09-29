import collections
from heapq import heappush, heappop


# 745. Prefix and Suffix Search
#  It will return the word with given prefix and suffix with maximum weight. If no word exists, return -1.
# init: O(w*l^2)
# search: O(p + s)
# space: O(t)
class WordFilter(object):
    def __init__(self, words):
        _Trie = lambda: collections.defaultdict(_Trie)
        self._trie = _Trie()

        for weight, word in enumerate(words):
            word += '#'
            n = len(word)
            # apple!aaple
            # pple!applea
            for i in range(n):
                T = self._trie
                T["$"] = weight
                for j in range(i, 2 * n - 1):
                    T = T[word[j % n]]
                    T["$"] = weight

    def f(self, prefix, suffix):
        """
        :type prefix: str
        :type suffix: str
        :rtype: int
        """
        T = self._trie
        for letter in suffix + '#' + prefix:
            if letter not in T:
                return -1
            T = T[letter]
        return T["$"]
