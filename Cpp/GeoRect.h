#pragma once
#include "common.h"

namespace GeoRect {
	// 223. Rectangle Area [M]
	// Find the total area covered by two rectilinear rectangles in a 2D plane.
	// Input: 4 * 2 points, bottom left and top right
	int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
		long long area1 = (D - B) * (C - A), area2 = (H - F) * (G - E);
		long long b1 = max(0LL, ((long long)min(C, G) - max(A, E))), b2 = max(0LL, ((long long)min(D, H) - max(B, F)));
		return (int)(area1 + area2 - b1 * b2);
	}
}