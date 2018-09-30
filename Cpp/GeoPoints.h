#pragma once
#include "common.h"

namespace GeoPoints {
	using VecPoint = vector<Point>;

	// 149. Max Points on a Line [H]
	// Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
	int maxPoints(VecPoint& points) {
		int max_points = 0;
		int n = static_cast<int>(points.size());
		for (int i = 0; i < n; ++i) {
			unordered_map<double, int> slope_count;
			const auto& p = points[i];
			int same = 1;
			for (int j = i + 1; j < n; ++j) {
				const auto& q = points[j];
				if (p.x == q.x && p.y == q.y) {
					++same;
				}
				else {
					auto slope = numeric_limits<double>::max();
					if (p.x - q.x != 0) {
						slope = (p.y - q.y) * 1.0 / (p.x - q.x);
					}
					++slope_count[slope];
				}
			}

			int current_max = same;
			for (const auto& kvp : slope_count) {
				current_max = max(current_max, kvp.second + same);
			}
			max_points = max(max_points, current_max);
		}
		return max_points;
	}

	int maxPoints2(vector<Point>& points) {
		int n = points.size();
		if (n <= 0) return 0;
		unordered_map<float, int> map;
		int ans = 1;
		const float EPS = 1e-6;
		float INF = 1e6;
		for (int i = 0; i < n; ++i) {
			map.clear();
			int num_origin = 1;
			int cur_max = 0;
			for (int j = 0; j < n; ++j) if (i != j) {
				if (abs(points[j].x - points[i].x) < EPS) {
					if (abs(points[j].y - points[i].y) < EPS) {
						num_origin++;
						continue;
					}
					if (map.find(INF) != map.end()) map[INF]++; else map[INF] = 1;
					cur_max = max(cur_max, map[INF]);
				}
				else {
					float k = (float)(points[j].y - points[i].y) / (points[j].x - points[i].x);

					if (map.find(k) != map.end()) map[k]++; else map[k] = 1;
					cur_max = max(cur_max, map[k]);
				}
			}
			ans = max(ans, cur_max + num_origin);
		}
		return ans;
	}
}