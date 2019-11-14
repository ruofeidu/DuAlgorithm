#pragma once
#include "common.h"

namespace GraphFloyd {
	void Floyd(Grid &f) {
		int n = (int)f.size();
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i)
				if (i != k) {
					for (int j = 0; j < n; ++j)
						if (j != k && i != j)
							f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
				}
		}
	}

	// Floyd can further be used to compute the minimum circle in a graph
	// Proof: the greatest node in a circle is k, adjcent to i and j,
	// the minimum length of the circle is f[i][k] + f[k][j] + shortest path [i][j]
	vector<int> FloydMinCircle(Grid &f) {
		int n = (int)f.size();
		Grid d(n, Vector(n)); // shortest distance
		Grid p(n, Vector(n)); // passing through
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) {
				d[i][j] = f[i][j];
				p[i][j] = i;
			}

		int res = numeric_limits<int>::max();
		vector<int> circle(n);
		int ii = -1, jj = -1, kk = -1;

		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < k - 1; ++i) if (f[i][k] < INT_MAX)
				for (int j = i + 1; j < k - 1; ++j) {
					if (d[i][j] < INT_MAX && f[k][j] < INT_MAX && res > d[i][j] + f[i][k] + f[k][j]) {
						res = d[i][j] + f[i][k] + f[k][j];
						ii = i;
						jj = j;
						kk = k;
					}
				}

			for (int i = 0; i < n; ++i)
				if (i != k) {
					for (int j = 0; j < n; ++j)
						if (j != k && i != j && d[i][k] + d[k][j] < d[i][j]) {
							d[i][j] = d[i][k] + d[k][j];
						}
				}
		}


		// obtain the entire circle
		int l = 0;
		while (jj != ii) {
			circle[l++] = jj;
			jj = p[ii][jj];
		}
		circle[l++] = ii;
		circle[l++] = kk;
		circle.resize(res);

		return circle;
	}
}