#pragma once
#include "common.h"

namespace BitsManipulation {

	// 231. Power of Two
	bool isPowerOfTwo(int n) {
		return n <= 0 ? false : n == (n & (n ^ (n - 1)));
		// return (n > 0) && (!(n & (n - 1))); // both correct
	}

	// 266. Palindrome Permutation
	// Given a string, determine if a permutation of the string could form a palindrome.
	bool canPermutePalindrome(string s) {
		bitset<256> b;
		for (auto a : s) b.flip(a);
		return b.count() < 2;
	}

	// 421. Maximum XOR of Two Numbers in an Array
	// O(n)
	int findMaximumXOR(vector<int>& nums) {
		int res = 0, mask = 0;
		for (int i = 31; i >= 0; --i) {
			mask |= (1 << i);
			set<int> s;
			for (int x : nums) {
				s.insert(x & mask);
			}
			// if t ^ prefix == res 
			// then t = prefix ^ res
			int t = res | (1 << i);
			for (int prefix : s) {
				if (s.count(t ^ prefix)) {
					res = t;
					break;
				}
			}
		}
		return res;
	}

	// 318.
	// Given a list of words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters
	int maxProduct(vector<string>& words) {
		int ans = 0;
		int n = (int)words.size();

		vector<int> mask(n);
		for (int i = 0; i < n; ++i) {
			for (char c : words[i]) mask[i] |= (1 << (c - 'a'));
			for (int j = 0; j < i; ++j) if (!(mask[i] & mask[j]))
				ans = max(ans, int(words[i].size() * words[j].size()));
		}
		return ans;
	}


	// 338. Counting Bits
	// For every numbers i in the range 0 <= i <= num calculate the number of 1's in their binary representation and return them as an array.
	/**
	* 0    0000    0
	* -------------
	* 1    0001    1
	* -------------
	* 2    0010    1
	* 3    0011    2
	* -------------
	* 4    0100    1
	* 5    0101    2
	* 6    0110    2
	* 7    0111    3
	* -------------
	* 8    1000    1
	* 9    1001    2
	* 10   1010    2
	* 11   1011    3
	* 12   1100    2
	* 13   1101    3
	* 14   1110    3
	* 15   1111    4
	**/
	vector<int> countBits(int num) {
		vector<int> res(num + 1, 0);
		for (int i = 1; i <= num; ++i) {
			res[i] = res[i & (i - 1)] + 1;
		}
		return res;
	}

	vector<int> countBitsBitset(int num) {
		vector<int> res;
		for (int i = 0; i <= num; ++i) {
			res.push_back((int)bitset<32>(i).count());
		}
		return res;
	}


	// 416. Partition Equal Subset Sum
	bool canPartition(vector<int>& nums) {
		bitset<5001> bits(1);
		int sum = accumulate(nums.begin(), nums.end(), 0);
		for (int num : nums) bits |= bits << num;
		return (sum % 2 == 0) && bits[sum >> 1];
	}

	// 691. Stickers to spell word
	int minStickers(vector<string>& stickers, string target) {
		using Freq = vector<int>;
		const int MAX_ALPHABET = 26;
		const int T = (int)target.size();
		vector<Freq> freqs(stickers.size());

		// calc frequency statistics
		auto buildFreqFromString = [=](const string &s) {
			Freq ans(MAX_ALPHABET);
			for (const auto &c : s)
				++ans[c - 'a'];
			return ans;
		};
		Freq targetFreq = buildFreqFromString(target);
		for (int i = 0; i < stickers.size(); ++i) {
			freqs[i] = buildFreqFromString(stickers[i]);
			// remove higher frequency than the target
			for (int j = 0; j < MAX_ALPHABET; ++j)
				freqs[i][j] = min(freqs[i][j], targetFreq[j]);
		}

		// test if a is the proper subset of b
		auto isProperSubset = [=](const Freq &a, const Freq &b) {
			for (int i = 0; i < a.size(); ++i)
				if (a[i] >= b[i]) return false;
			return true;
		};
		// remove the proper subset of stickets
		for (int i = (int)freqs.size() - 1; i >= 0; --i) {
			for (int j = 0; j < (int)freqs.size(); ++j)
				if (i != j && isProperSubset(freqs[i], freqs[j]))
					freqs.erase(freqs.begin() + i);
		}

		auto getStringFromFreq = [=](const Freq &a) {
			string ans = "";
			for (int i = 0; i < a.size(); ++i) {
				ans += string(a[i], 'a' + i);
			}
			return ans;
		};
		vector<string> pieces(freqs.size());
		for (int i = 0; i < freqs.size(); ++i) {
			pieces[i] = getStringFromFreq(freqs[i]);
			cout << i << " " << pieces[i] << endl;
		}

		const int MAX_T = 1 << T;
		vector<int> f(MAX_T, -1);
		f[0] = 0;
		for (int i = 0; i < MAX_T; ++i) {
			if (f[i] < 0)
				continue;
			for (const auto &piece : pieces) {
				int j = i;
				for (const auto &c : piece) {
					// find the first k that does not appear in state i
					for (int k = 0; k < T; ++k) {
						if ((j >> k) & 1)
							continue;
						if (target[k] == c) {
							j |= (1 << k);
							break;
						}
					}
					if (f[j] < 0 || f[j] > f[i] + 1) {
						f[j] = f[i] + 1;
					}
				}
			}
		}
		return f[MAX_T - 1];
	}
};