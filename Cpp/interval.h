#pragma once
#include "common.h"

namespace TestIntervals{
	// Time: O(n log n)
	// Extra Space: O(1)
	// Given a collection of intervals, merge all overlapping intervals.
	// Input: [[1,3],[2,6],[8,10],[15,18]]
	// Output: [[1, 6], [8, 10], [15, 18]]
	// Sort then merge
	vector<Interval> merge(vector<Interval>& intervals) {
		auto &I = intervals;
		if (I.empty()) {
			return I;
		}
		sort(I.begin(), I.end(), [](const Interval& a, const Interval& b) {
			return a.start < b.start;
		});

		vector<Interval> res{ I[0] };
		const auto N = I.size();
		for (int i = 1; i < N; ++i) {
			// if there is overlap
			if (I[i].start <= res.back().end) {
				res.back().end = max(res.back().end, I[i].end);
			}
			else {
				res.emplace_back(I[i]);
			}
		}
		return res;
	}

	// count union length of intervals
	// Time: O(n log n)
	// [1, 4] [2, 5], [7, 9], [7, 2], [8, 10]
	// prev = [1, 4]
	// prev = [1, 5]
	// res = 4, prev = [7, 9]
	int getUnionLength(vector<Interval> &intervals) {
		auto &a = intervals;
		if (a.empty()) {
			return 0;
		}
		sort(a.begin(), a.end(), [](const Interval& a, const Interval& b) {
			return a.start < b.start;
		});

		// scan and merge
		int res = 0; 
		auto prev = intervals[0];
		const auto N = intervals.size(); 
		for (int i = 1; i < N; ++i) {
			if (intervals[i].start < prev.end) {
				if (intervals[i].end > prev.end) {
					prev.end = intervals[i].end;
				}
			}
			else {
				res += prev.end - prev.start;
				prev = intervals[i];
			}
		}
		res += prev.end - prev.start;
		return res;
	}

	// Given a set of sorted non-overlapping intervals, 
	// insert a new interval into the intervals (merge if necessary).
	// Time: O(N)
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		auto &I = intervals;
		const auto N = I.size();
		auto &X = newInterval;
		vector<Interval> res;

		size_t i = 0;
		while (i < N && X.start > I[i].end) {
			res.emplace_back(I[i]);
			++i;
		}

		while (i < N && X.end >= I[i].start) {
			X = { min(X.start, I[i].start),
				max(X.end, I[i].end) };
			++i;
		}
		res.emplace_back(X);

		// insert the rest of the invervals
		while (i < N) {
			res.emplace_back(I[i]);
			++i;
		}
		//res.insert(res.end(), I.cbegin() + i, I.cend());
		return res;
	}

	// Time: O(n log n)
	int eraseOverlapIntervals(vector<Interval>& intervals) {
		//[1, 4], [1, 2], [2, 5], [2, 4], [3, 4] 
		auto& I = intervals;
		sort(I.begin(), I.end(), [](const Interval& a, const Interval& b) {
			return a.start < b.start;
		});
		int res = 0, prev = 0;
		const auto N = I.size();
		for (int i = 1; i < N; ++i) {
			// the current interval overlaps with the previous one
			if (I[i].start < I[prev].end) {
				// the current interval is shorter than the previous one, remove previous
				if (I[i].end < I[prev].end) {
					prev = i;
				}
				// remove the current
				++res;
			}
			else {
				prev = i;
			}
		}
		return res;
	}

}