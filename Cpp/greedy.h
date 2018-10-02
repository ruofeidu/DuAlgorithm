#pragma once
#include "common.h"
namespace Greedy {
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
}