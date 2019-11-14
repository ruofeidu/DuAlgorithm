#pragma once
#include "common.h"

class CountSort {
  // 75. Sort Colors [M]
  // Given an array with n objects colored red, white or blue, sort them
  // in-place so that objects of the same color are adjacent, with the colors in
  // the order red, white and blue. (0, 1, 2)
  void sortColors(vector<int>& nums) {
    int red = 0, blue = (int)nums.size() - 1;
    for (int i = 0; i <= blue; ++i) {
      if (nums[i] == 0) {
        swap(nums[i], nums[red++]);
      } else if (nums[i] == 2) {
        swap(nums[i--], nums[blue--]);
      }
    }
  }

  // 318. Maximum Product of Word Lengths
  // Time:  O(n) ~ O(n^2)
  // Space: O(n)
  // Counting Sort + Pruning + Bit Manipulation
  int maxProduct(vector<string>& words) {
    words = counting_sort(words);
    vector<int> bits(words.size());
    for (int i = 0; i < words.size(); ++i) {
      for (const auto& c : words[i]) {
        bits[i] |= (1 << (c - 'a'));
      }
    }
    int max_product = 0;
    for (int i = 0;
         i + 1 < words.size() && pow(words[i].length(), 2) > max_product; ++i) {
      for (int j = i + 1; j < words.size() &&
                          words[i].length() * words[j].length() > max_product;
           ++j) {
        if (!(bits[i] & bits[j])) {
          max_product = (int)(words[i].length() * words[j].length());
        }
      }
    }
    return max_product;
  }

  vector<string> counting_sort(const vector<string>& words) {
    const int k = 1000;  // k is max length of words in the dictionary
    vector<vector<string>> buckets(k);
    for (const auto& word : words) {
      buckets[word.length()].emplace_back(word);
    }
    vector<string> res;
    for (int i = k - 1; i >= 0; --i) {
      if (!buckets[i].empty()) {
        move(buckets[i].begin(), buckets[i].end(), back_inserter(res));
      }
    }
    return res;
  }
};
