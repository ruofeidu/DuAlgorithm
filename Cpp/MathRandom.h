#pragma once
#include <random>
#include "common.h"

namespace Randoms {
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> uniform_random(0.0, 1.0);  // [a, b)

// Use as sample = uniform_random(mt);
int getRandom(int low, int high) {
  auto sample = uniform_random(mt);
  return (int)floor(sample * (high - low + 1)) + low;
}

// Time: O(N), scan and swap a[i] with a[random(i, n - 1)].
void shuffle(vector<int> &a) {
  for (int i = 0; i < a.size(); ++i) {
    int id = getRandom(i, (int)a.size() - 1);
    swap(a[i], a[id]);
  }
}

// rand(): Returns a pseudo-random integral number in the range between 0 and
// RAND_MAX (32767).
}

// 381. Insert Delete GetRandom O(1) - Duplicates allowed
// Design a data structure that supports all following operations in average
// O(1) time.
class RandomizedCollection {
 private:
  unordered_map<int, unordered_set<int>> m_dict;
  vector<int> m_list;
  std::random_device m_rd;
  std::mt19937 m_mt;
  std::uniform_real_distribution<double> m_uniform_random{0.0, 1.0};

 public:
  /** Initialize your data structure here. */
  RandomizedCollection() {
    m_list = vector<int>();
    m_dict = unordered_map<int, unordered_set<int>>();
    m_mt = std::mt19937(m_rd());
  }

  /** Inserts a value to the collection. Returns true if the collection did not
   * already contain the specified element. */
  bool insert(int val) {
    bool res = m_dict.find(val) == m_dict.end();
    m_dict[val].insert((int)m_list.size());
    m_list.emplace_back(val);
    return res;
  }

  /** Removes a value from the collection. Returns true if the collection
   * contained the specified element. */
  bool remove(int val) {
    if (m_dict.find(val) == m_dict.end()) return false;

    int last = m_list.back();
    m_list.pop_back();
    m_dict[last].erase((int)m_list.size());
    if (last != val) {
      auto val_id = *m_dict[val].begin();
      m_dict[val].erase(val_id);
      m_dict[last].insert(val_id);
      m_list[val_id] = last;
    }

    if (m_dict[val].empty()) m_dict.erase(val);

    return true;
  }

  /** Get a random element from the collection. */
  int getRandom() {
    auto sample = m_uniform_random(m_mt);
    return m_list[(int)floor(sample * m_list.size())];
  }
};
