#pragma once
#include "common.h"

namespace FileIO {
	void c_io() {
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	}
}
