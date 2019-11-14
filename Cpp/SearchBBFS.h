#pragma once
#include "common.h"

namespace SearchBBFS {
class Solution {
 public:
  vector<vector<string>> findLadders(string beginWord, string endWord,
                                     vector<string>& wordList) {
    vector<vector<string>> ans;
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(endWord)) return ans;

    int l = beginWord.length();

    unordered_set<string> q1{beginWord};
    unordered_set<string> q2{endWord};
    unordered_map<string, vector<string>> children;

    bool found = false;
    bool backward = false;

    while (!q1.empty() && !q2.empty() && !found) {
      // Always expend the smaller queue first
      if (q1.size() > q2.size()) {
        std::swap(q1, q2);
        backward = !backward;
      }

      for (const string& w : q1) dict.erase(w);
      for (const string& w : q2) dict.erase(w);

      unordered_set<string> q;

      for (const string& word : q1) {
        string curr = word;
        for (int i = 0; i < l; i++) {
          char ch = curr[i];
          for (int j = 'a'; j <= 'z'; j++) {
            curr[i] = j;

            const string* parent = &word;
            const string* child = &curr;

            if (backward) std::swap(parent, child);

            if (q2.count(curr)) {
              found = true;
              children[*parent].push_back(*child);
            } else if (dict.count(curr) && !found) {
              q.insert(curr);
              children[*parent].push_back(*child);
            }
          }
          curr[i] = ch;
        }
      }

      std::swap(q, q1);
    }

    if (found) {
      vector<string> path{beginWord};
      getPaths(beginWord, endWord, children, path, ans);
    }

    return ans;
  }

 private:
  void getPaths(const string& word, const string& endWord,
                const unordered_map<string, vector<string>>& children,
                vector<string>& path, vector<vector<string>>& ans) {
    if (word == endWord) {
      ans.push_back(path);
      return;
    }

    const auto it = children.find(word);
    if (it == children.cend()) return;

    for (const string& child : it->second) {
      path.push_back(child);
      getPaths(child, endWord, children, path, ans);
      path.pop_back();
    }
  }
};
}
