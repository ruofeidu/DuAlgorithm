#pragma once
#include "common.h"

namespace Permutations {
	// 47. Unique Permutation
	typedef vector<pair<int, int>>::const_iterator Iter;
	void DFSUniquePermutation(Iter first, Iter last, vector<int> &p, vector<vector<int>> &result, size_t n) {
		if (n == p.size()) {
			result.push_back(p);
		}
		for (auto i = first; i != last; ++i) {
			int count = 0;
			for (auto j = p.begin(); j != p.end(); ++j) {
				if (i->first == *j) {
					++count;
				}
			}

			if (count < i->second) {
				p.push_back(i->first);
				DFSUniquePermutation(first, last, p, result, n);
				p.pop_back();
			}
		}
	}

	// 46. Permutation
	template<typename T> bool nextPermutation(T first, T last) {
		const auto rFirst = reverse_iterator<T>(last);
		const auto rLast = reverse_iterator<T>(first);

		// begin from the second last element to the first element.
		auto pivot = next(rFirst);

		// find pivot, which is the first element that is no less than its success
		while (pivot != rLast && *pivot >= *prev(pivot)) ++pivot;

		if (pivot == rLast) {
			std::reverse(rFirst, rLast);
			return false;
		}

		// find the first element that is greater than pivot
		auto change = find_if(rFirst, pivot, bind1st(less<int>(), *pivot));

		swap(*change, *pivot);
		std::reverse(rFirst, pivot);

		return true;
	}
}