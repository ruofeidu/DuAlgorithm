#pragma once
#include "common.h"

namespace Queues {
// 239. Sliding Window Maximum [H]
// Given an array nums, there is a sliding window of size k which is moving from
// the very left of the array to the very right. You can only see the k numbers
// in the window. Each time the sliding window moves right by one position.
// Return the max sliding window.
// every element enque once and deque once
/*
        [1,3,-1,-3,5,3,6,7]
        3
        0
        1
        1	2
        1	2	3
        4
        4	5
        6
        7
*/
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  vector<int> res;
  deque<int> q;
  const int n = (int)nums.size();
  for (int i = 0; i < n; ++i) {
    if (!q.empty() && q.front() == i - k) q.pop_front();
    while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
    q.emplace_back(i);
    if (i >= k - 1) res.emplace_back(nums[q.front()]);
  }
  return res;
}

class MovingAverage {
 public:
  MovingAverage(int size) {
    this->size = size;
    sum = 0;
  }

  double next(int val) {
    if (q.size() >= size) {
      sum -= q.front();
      q.pop();
    }
    q.push(val);
    sum += val;
    return sum / q.size();
  }

 private:
  queue<int> q;
  int size;
  double sum;
};

// 225. Implement Stack using Queues
// See Python
};
