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
}