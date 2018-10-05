import collections
from heapq import heappush, heappop

# 211. Add and Search Word - Data structure design [M]
# Design a data structure that supports the following two operations:
# void addWord(word)
# bool search(word)
# search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.
class Trie:
    def __init__(self):
        self.is_str = False
        self.children = {}

class WordDictionary:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = Trie()

    def addWord(self, word):
        """
        Adds a word into the data structure.
        :type word: str
        :rtype: void
        """
        node = self.root
        for c in word:
            if c not in node.children:
                node.children[c] = Trie()
            node = node.children[c]
        node.is_str = True
        
    def lookup(self, node, word):
        # print(node.children.keys(), node.is_str, word)
        if node is None:
            return False
        if not word:
            return node.is_str
        c = word[0]
        if c == '.':
            for x in node.children.keys():
                if len(word) == 1 and node.children[x].is_str:
                    return True
                if self.lookup(node.children[x], word[1:]):
                    return True
            return False
        else:
            if c not in node.children:
                return False
            if len(word) > 1:
                return self.lookup(node.children[c], word[1:])
            else:
                return node.children[c].is_str

    def search(self, word):
        """
        Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
        :type word: str
        :rtype: bool
        """
        return self.lookup(self.root, word)


# Your WordDictionary object will be instantiated and called as such:
# obj = WordDictionary()
# obj.addWord(word)
# param_2 = obj.search(word)


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

        
# 208. Implement Trie (Prefix Tree)
# Time:  O(n), per operation
# Space: O(1)
#
# Implement a trie with insert, search, and startsWith methods.
#
# Note:
# You may assume that all inputs are consist of lowercase letters a-z.
#

class TrieNode:
    # Initialize your data structure here.
    def __init__(self):
        self.is_word = False
        self.child = {}


class Trie:

    def __init__(self):
        self.root = TrieNode()

    # @param {string} word
    # @return {void}
    # Inserts a word into the trie.
    def insert(self, word):
        cur = self.root
        for c in word:
            if not c in cur.child:
                cur.child[c] = TrieNode()
            cur = cur.child[c]
        cur.is_word = True

    # @param {string} word
    # @return {boolean}
    # Returns if the word is in the trie.
    def search(self, word):
        node = self.childSearch(word)
        if node:
            return node.is_word
        return False

    # @param {string} prefix
    # @return {boolean}
    # Returns if there is any word in the trie
    # that starts with the given prefix.
    def startsWith(self, prefix):
        return self.childSearch(prefix) is not None

    def childSearch(self, word):
        cur = self.root
        for c in word:
            if c in cur.child:
                cur = cur.child[c]
            else:
                return None
        return cur

# Your Trie object will be instantiated and called as such:
# trie = Trie()
# trie.insert("somestring")
# trie.search("key")
