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
}

namespace HeapAlgos {
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

	/**
	295. Find Median from Data Stream
	[2,3,4] , the median is 3
	[2,3], the median is (2 + 3) / 2 = 2.5
	**/
	class MedianFinder {
	private:
		priority_queue<int> small, large;
	public:
		// Adds a number into the heap in O(log N)
		//  2, 3
		//  3
		void addNum(int num) {
			small.push(num);
			large.push(-small.top());
			small.pop();
			if (small.size() < large.size()) {
				small.push(-large.top());
				large.pop();
			}
		}

		// Returns the median of small and large
		double findMedian() {
			return small.size() > large.size() ? small.top() : 0.5 * (small.top() - large.top());
		}
	};
}