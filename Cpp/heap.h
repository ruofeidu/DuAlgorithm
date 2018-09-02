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