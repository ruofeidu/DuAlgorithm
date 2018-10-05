#pragma once
#include "common.h"

namespace TestHeap {
	// priority_queue is by default a max heap
	priority_queue<int> max_heap;

	// priority_queue supports a constructor that requires two extra arguments to make it min heap.
	priority_queue <int, vector<int>, greater<int> > min_heap;

	class Point
	{
		int x;
		int y;
	public:
		Point(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
		int getX() const { return x; }
		int getY() const { return y; }
	};
	class myComparator
	{
	public:
		int operator() (const Point& p1, const Point& p2)
		{
			return p1.getX() > p2.getX();
		}
	};

	priority_queue <Point, vector<Point>, myComparator > pq;

	priority_queue< string, vector<string>, greater<string> > ascend;
	priority_queue< string, vector<string>, less<string> > descend;
}

namespace HeapAlgos {
	// 857. Minimum Cost to Hire K Workers
	// There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].
	// Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
	// Every worker in the paid group must be paid at least their minimum wage expectation.
	// Return the least amount of money needed to form a paid group satisfying the above conditions.
	double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
		vector<pair<double, int>> workers;
		const auto N = quality.size();
		for (int i = 0; i < N; ++i) {
			workers.emplace_back((double)wage[i] / quality[i], quality[i]);
		}
		sort(workers.begin(), workers.end());
		auto res = numeric_limits<double>::max();
		auto sum = 0.0;
		priority_queue<int> max_heap;
		for (const auto& worker : workers) {
			sum += worker.second;
			max_heap.emplace(worker.second);
			if (max_heap.size() > K) {
				sum -= max_heap.top();
				max_heap.pop();
			}
			if (max_heap.size() == K) {
				res = min(res, sum * worker.first);
			}
		}
		return res;
	}

	int minMeetingRooms(vector<Interval>& intervals) {
		sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) { return a.start < b.start; });
		// min heap
		priority_queue<int, vector<int>, greater<int>> q;
		for (auto &x : intervals) {
			if (!q.empty() && q.top() <= x.start) q.pop();
			q.push(x.end);
		}
		return (int)q.size();
	}

	// 215. Kth Largest Element in an Array [M]
	// Max heap
	// Time: O(n log k)
	// Space: O(k)
	int findKthLargest(vector<int>& nums, int k) {
		if (nums.empty() || k == 0)
			return -1;
		priority_queue<int> h;
		for (auto x : nums) {
			h.push(-x);
			if (h.size() > k)
				h.pop();
		}
		return -h.top();
	}

	// 295. Find Median from Data Stream
	// [2,3,4] , the median is 3
	// [2,3], the median is (2 + 3) / 2 = 2.5
	class MedianFinder {
	private:
		priority_queue<int> min_heap, max_heap;
	public:
		// Adds a number into the heap in O(log N)
		//  2, 3
		//  3
		void addNum(int num) {
			max_heap.push(num);
			min_heap.push(-max_heap.top());
			max_heap.pop();
			if (max_heap.size() < min_heap.size()) {
				max_heap.push(-min_heap.top());
				min_heap.pop();
			}
		}

		// Returns the median of small and large
		double findMedian() {
			return max_heap.size() > min_heap.size() ? max_heap.top() : 0.5 * (max_heap.top() - min_heap.top());
		}
	};
}