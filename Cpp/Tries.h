#pragma once
#include "common.h"

// 208. Implement Trie (Prefix Tree) [M]
// Implement a trie with insert, search, and startsWith methods.
// Time:  O(n), per operation
// Space : O(1)
class TrieNode {
 public:
  TrieNode *child[26];
  bool isWord;
  TrieNode() : isWord(false) {
    for (auto &a : child) a = nullptr;
  }
};

class Trie {
 public:
  Trie() { root = new TrieNode(); }

  // Inserts a word into the trie.
  void insert(string s) {
    TrieNode *p = root;
    for (auto &a : s) {
      int i = a - 'a';
      if (!p->child[i]) p->child[i] = new TrieNode();
      p = p->child[i];
    }
    p->isWord = true;
  }

  // Returns if the word is in the trie.
  bool search(string key) {
    TrieNode *p = root;
    for (auto &a : key) {
      int i = a - 'a';
      if (!p->child[i]) return false;
      p = p->child[i];
    }
    return p->isWord;
  }

  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(string prefix) {
    TrieNode *p = root;
    for (auto &a : prefix) {
      int i = a - 'a';
      if (!p->child[i]) return false;
      p = p->child[i];
    }
    return true;
  }

 private:
  TrieNode *root;
};

namespace TestTrie {
void test() {
  Trie trie;
  trie.insert("apple");
  trie.search("apple");    // returns true
  trie.search("app");      // returns false
  trie.startsWith("app");  // returns true
  trie.insert("app");
  trie.search("app");  // returns true
}

// 211. Add and Search Word - Data structure design [M]
// See Python
}

// 212. Word Search II [H]
// Given a 2D board and a list of words from the dictionary, find all words in
// the board.
/*
        Input:
        words = ["oath","pea","eat","rain"] and board =
        [
        ['o','a','a','n'],
        ['e','t','a','e'],
        ['i','h','k','r'],
        ['i','f','l','v']
        ]

        Output: ["eat","oath"]
*/
class WordSearchII {
  struct TrieNode {
    TrieNode *child[26];
    string str;
    TrieNode() : str("") {
      for (auto &a : child) a = NULL;
    }
  };
  struct Trie {
    TrieNode *root;
    Trie() : root(new TrieNode()) {}
    void insert(string s) {
      TrieNode *p = root;
      for (auto &a : s) {
        int i = a - 'a';
        if (!p->child[i]) p->child[i] = new TrieNode();
        p = p->child[i];
      }
      p->str = s;
    }
  };
  vector<string> findWords(vector<vector<char> > &board,
                           vector<string> &words) {
    vector<string> res;
    if (words.empty() || board.empty() || board[0].empty()) return res;
    vector<vector<bool> > vd(board.size(),
                             vector<bool>(board[0].size(), false));
    Trie T;
    for (auto &a : words) T.insert(a);
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
        if (T.root->child[board[i][j] - 'a']) {
          search(board, T.root->child[board[i][j] - 'a'], i, j, vd, res);
        }
      }
    }
    return res;
  }
  void search(vector<vector<char> > &board, TrieNode *p, int i, int j,
              vector<vector<bool> > &vd, vector<string> &res) {
    if (!p->str.empty()) {
      res.push_back(p->str);
      p->str.clear();
    }
    int d[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vd[i][j] = true;
    for (auto &a : d) {
      int nx = a[0] + i, ny = a[1] + j;
      if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() &&
          !vd[nx][ny] && p->child[board[nx][ny] - 'a']) {
        search(board, p->child[board[nx][ny] - 'a'], nx, ny, vd, res);
      }
    }
    vd[i][j] = false;
  }
};
