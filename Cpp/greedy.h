#pragma once
#include "common.h"

namespace Greedy {
	// 630. Course Schedule III [H]
	// There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.
	// Given n online courses represented by pairs(t, d), your task is to find the maximal number of courses that can be taken.
	// Solution: Greedy
	// Time: O(n)
	// Proof: Sort by end date, if the current course cannot be completed, we have to remove one course
	// if we remove something longer than the maximum one, 
	// it is possible we can have a smaller end date which yields the next one to the schedule -> contradictory!
	int scheduleCourse(vector<vector<int>>& courses) {
		sort(courses.begin(), courses.end(), [](const vector<int>& a, const vector<int>& b) {
			return a[1] < b[1];
		});

		// a max heap
		priority_queue<int> h;
		// time
		int t = 0;

		for (const auto &c : courses) {
			h.emplace(c[0]);
			t += c[0];
			if (t > c[1]) {
				t -= h.top();
				h.pop();
			}
		}
		return (int)h.size();
	}

	// 853. Car Fleet [M]
	// Given positions and speeds of cars and a target destination, count number of fleets
	// Time:  O(n log n)
	// Space: O(n)
	int carFleet(int target, vector<int>& position, vector<int>& speed) {
		using PosTime = pair<int, double>;
		vector<PosTime> cars;
		const int N = (int)position.size();
		for (int i = 0; i < N; ++i) {
			cars.emplace_back(position[i], (double)(target - position[i]) / speed[i]);
		}
		sort(cars.begin(), cars.end(), [](const PosTime& a, const PosTime &b) {
			return a.first == b.first ? a.second < b.second : a.first < b.first;
		});
		int res = 0;
		double cur = 0;
		for (int i = N - 1; i >= 0; --i) {
			if (cars[i].second > cur) {
				cur = cars[i].second;
				++res;
			}
		}
		return res;
	}

	// 134. Gas Station
	// There are N gas stations along a circular route, where the amount of gas at station i is gas[i]. You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station(i + 1).You begin the journey with an empty tank at one of the gas stations. Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		const int n = (int)gas.size();
		int total_gas = 0, total_cost = 0, highest_cost = 0, start = 0;
		for (int i = 0; i < n; ++i) {
			total_gas += gas[i];
			total_cost += cost[i];
			if (cost[i] > highest_cost && gas[(i + 1) % n] > cost[(i + 1) % n]) {
				highest_cost = cost[i];
				start = (i + 1) % n;
			}
		}
		if (total_gas < total_cost) return -1; else return start;
	}

	// 330. Patching Array
	// Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required.
	// Time: O(M + log N)
	// Space: O(1)
	int minPatches(vector<int>& nums, int n) {
		// nums = [1, 2, 4, 11, 30], n = 50
		// 1,2,4 => [0, 8), add 8
		// 1,2,4,8 => [0, 16), no need for 16 because 1+4+11
		// 1,2,4,8,11 => [0, 27), add 27
		const int M = (int)nums.size();
		int i = 0, res = 0;
		const long long N = (long long)n;
		long long miss = 1;
		while (miss <= N) {
			if (i < M && nums[i] <= miss) {
				miss += nums[i++];
			}
			else {
				miss += miss;
				++res;
			}
		}
		return res;
	}
}