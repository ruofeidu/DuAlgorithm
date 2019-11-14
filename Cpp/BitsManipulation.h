#pragma once
#include "common.h"

// Ultimate Guide for Bits Manipulation
// Ruofei Du

// Remove the last digit (101101->10110)
// 	x >> 1
// Add 0 to the end (101101->1011010)
// 	x << 1
// Add 1 to the end (101101->1011011)
// 	(x << 1) + 1
// Make last digit 1 (101100->101101)
// 	x | 1
// Make last digit 0 (101101->101100)
// 	(x | 1) - 1
// Reverse last digit(101101->101100)
// 	x ^ 1
// Reverse last k_th digit(101101->101001, k = 3)
// 	x ^ (1 << (k - 1))
// Get last 3 digits(1101101->101)
// 	x & 7
// Get last k digits(1101101->1101, k = 5)
// 	x & ((1 << k) - 1)
// Turn last k digits to 1 (101001->101111, k = 4)
// 	x | ((1 << k) - 1)
// Reverse last k digits(101001->100110, k = 4)
// 	x ^ ((1 << k) - 1)
// Turn continuous right - side 1 to 0 (100101111->100100000)
// 	x & (x + 1)
// Make rightmost 0 one(100101111->100111111)
// 	x | (x + 1)
// Turn right - side continuous 0 to 1 (11011000->11011111)
// 	x or (x - 1)
// Get continuous ones in the right(100101111->1111)
// 	(x ^ (x + 1)) >> 1
// Remove the left - side before the first 1 from the right(100101000->1000,
// tree arrays)
// 	x & (x ^ (x - 1))

namespace BitsManipulation {
// a negative number's bit representation is its complement + 1
int calcAbs(int x) { return x ^ (!(x >> 31) + 1) + (x >> 31); }

// 231. Power of Two
bool isPowerOfTwo(int n) {
  // Insight: only the highest bit is 1
  return (n > 0) && (!(n & (n - 1)));
  return n <= 0 ? false : n == (n & (n ^ (n - 1)));

  int cnt = 0;
  while (n > 0) {
    cnt += (n & 1);
    n >>= 1;
  }
  return cnt == 1;
}

// 342. Power of Four [M]
bool isPowerOfFour(int n) {
  return (n > 0 && int(log10(n) / log10(4)) - log10(n) / log10(4) == 0);

  // Insight: the every 2 last bin digits are 0s
  return n > 0 && (n & (n - 1)) == 0 &&
         ((n & 0b01010101010101010101010101010101) == n);
  // 0b01010101010101010101010101010101 = 0x55555555

  while (n && !(n & 0b11)) {
    n >>= 2;
  }
  return (n == 1);

  // Insight II: 4^x - 1 can be divided by 3 and is power of 2
  return n > 0 && !(n & (n - 1)) && (n - 1) % 3 == 0;
}

// 266. Palindrome Permutation
// Given a string, determine if a permutation of the string could form a
// palindrome.
bool canPermutePalindrome(string s) {
  bitset<256> b;
  for (auto a : s) b.flip(a);
  return b.count() < 2;
}

// 421. Maximum XOR of Two Numbers in an Array
// O(n)
int findMaximumXOR(vector<int> &nums) {
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

// 318. Maximum Product of Word Lengths [M]
// Given a list of words, find the maximum value of length(word[i]) *
// length(word[j]) where the two words do not share common letters
// Time:  O(nlogn) ~ O(n^2)
// Space: O(n)
// See SortCount
int maxProduct(vector<string> &words) {
  const int n = (int)words.size();
  int ans = 0;

  vector<int> mask(n);
  for (int i = 0; i < n; ++i) {
    for (char c : words[i]) mask[i] |= (1 << (c - 'a'));
    for (int j = 0; j < i; ++j)
      if (!(mask[i] & mask[j]))
        ans = max(ans, int(words[i].size() * words[j].size()));
  }
  return ans;
}

// 338. Counting Bits [M]
// For every numbers i in the range 0 <= i <= num calculate the number of 1's in
// their binary representation and return them as an array.
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
    res.emplace_back((int)bitset<32>(i).count());
  }
  return res;
}

// 416. Partition Equal Subset Sum [M]
// Given a non-empty array containing only positive integers, find if the array
// can be partitioned into two subsets such that the sum of elements in both
// subsets is equal.
// Bitset Solution, refer to DPKnapsack for more details
// Time: O(N)
// Space: O(1)
bool canPartition(vector<int> &nums) {
  bitset<5001> bits(1);
  int sum = accumulate(nums.begin(), nums.end(), 0);
  for (const int &num : nums) bits |= bits << num;
  return (sum & 1 == 0) && bits[sum >> 1];
}

// 691. Stickers to spell word
int minStickers(vector<string> &stickers, string target) {
  using Freq = vector<int>;
  const int MAX_ALPHABET = 26;
  const int T = (int)target.size();
  vector<Freq> freqs(stickers.size());

  // calc frequency statistics
  auto buildFreqFromString = [=](const string &s) {
    Freq ans(MAX_ALPHABET);
    for (const auto &c : s) ++ans[c - 'a'];
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
    if (f[i] < 0) continue;
    for (const auto &piece : pieces) {
      int j = i;
      for (const auto &c : piece) {
        // find the first k that does not appear in state i
        for (int k = 0; k < T; ++k) {
          if ((j >> k) & 1) continue;
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

// 89. Gray Code
// The gray code is a binary numeral system where two successive values differ
// in only one bit.
// Given a non - negative integer n representing the total number of bits in the
// code, print the sequence of gray code.
// A gray code sequence must begin with 0.
vector<int> grayCode(int n) {
  // n ^ (n >> 1)
  vector<int> ans;
  ans.reserve((int)(1 << n));
  ans.push_back(0);
  for (int i = 0; i < n; ++i) {
    const int highest_bit = 1 << i;
    for (int j = (int)ans.size() - 1; j >= 0; --j) {
      ans.push_back(highest_bit | ans[j]);
    }
  }
  return ans;
}

/*
int solveMaximumXOR(vector<int>& nums0, vector<int>& nums1, int mask) {
        if (mask <= 1) return mask;

        vector<int> nums00, nums01, nums10, nums11;
        mask >>= 1;
        for (auto n : nums0) {
                if (n & mask == 0) nums00.push_back(n);
                if (n & mask) nums01.push_back(n);
        }
        for (auto n : nums1) {
                if (n & mask == 0) nums10.push_back(n);
                if (n & mask) nums11.push_back(n);
        }

        int ans = 0;
        if (!nums10.empty() && !nums01.empty()) {
                ans = max(ans, solveMaximumXOR(nums10, nums01, mask));
        }
        if (!nums00.empty() && !nums11.empty()) {
                ans = max(ans, solveMaximumXOR(nums00, nums11, mask));
        }
        if (!ans) {
                ans = solveMaximumXOR(nums0, nums1, mask) - mask;
        }
        return ans + (mask << 1);
}

int findMaximumXOR2(vector<int>& nums) {
        int mask = 1 << 31;
        vector<int> nums0, nums1;

        while (mask) {
                for (auto n : nums) {
                        if (n & mask == 0) nums0.push_back(n);
                        if (n & mask) nums1.push_back(n);
                }
                if (!nums0.empty() && !nums1.empty()) break;
                mask >>= 1;
        }

        return solveMaximumXOR(nums0, nums1, mask);
}
*/

// 201. Bitwise AND of Numbers Range
// Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND
// of all numbers in this range, inclusive
// Insight: for the range [m, n], if n > m, the lowest bit is always 0.
// Edge case: if m==n && (m&1) return 1 => m & n
int rangeBitwiseAnd(int m, int n) {
  while (m < n) {
    n = n & (n - 1);
  }
  return m & n;
}

int rangeBitwiseAnd2(int m, int n) {
  if (n > m) {
    return rangeBitwiseAnd(m >> 1, n >> 1) << 1;
  } else {
    return m;
  }
}

// 461. Hamming Distance
int hammingDistance(int x, int y) {
  int distance = 0;
  for (int z = x ^ y; z; z &= z - 1) {
    ++distance;
  }
  return distance;
}

// 191. Number of 1 Bits
// Takes an unsigned integer and returns the number of '1' bits it has (also
// known as the Hamming weight).
int hammingWeight(uint32_t n) {
  int ans = 0;
  while (n > 0) {
    ans += n & 1;
    n >>= 1;
  }
  return ans;
}

// 136. Single Number
// Given a non-empty array of integers, every element appears twice except for
// one. Find that single one.
int singleNumber(vector<int> &nums) {
  // int ans = 0;  for (int x : nums) ans ^= x;  return ans;
  return accumulate(nums.cbegin(), nums.cend(), 0, std::bit_xor<int>());
}

// 137. Single Number II
int singleNumberII(vector<int> &nums) {
  const int L = sizeof(int) * 8;
  vector<int> count(L, 0);
  for (int x : nums) {
    for (int i = 0; i < L; ++i) {
      count[i] += (x >> i) & 1;
      count[i] %= 3;
    }
  }
  for (int i = 0; i < L; ++i) count[i] <<= i;
  return accumulate(count.cbegin(), count.cend(), 0, std::plus<int>());
}

// 260. Single Number III
// Given an array of numbers nums, in which exactly two elements appear only
// once and all the other elements appear exactly twice. Find the two elements
// that appear only once.
vector<int> singleNumberIII(vector<int> &nums) {
  int s = 0;
  unordered_set<int> v;
  for (auto &x : nums) {
    s ^= x;
    v.emplace(x);
  }
  for (auto &x : nums) {
    if (v.count(s ^ x)) return {x, s ^ x};
  }
  return {-1, -1};
}

// Fast SQRT
// 15 times faster than the classical float sqrt. // Reasonably accurate up to
// root(32500) // Source:
// http://supp.iar.com/FilesPublic/SUPPORT/000419/AN-G-002.pdf
unsigned int root(unsigned int x) {
  unsigned int a, b;
  b = x;
  a = x = 0x3f;
  x = b / x;
  a = x = (x + a) >> 1;
  x = b / x;
  a = x = (x + a) >> 1;
  x = b / x;
  x = (x + a) >> 1;
  return (x);
}

// From Quake 3
float inv_sqrt(float x) {
  float half = 0.5 * x;
  int i = *((int *)&x);
  i = 0x5f3759df - (i >> 1);
  x = *((float *)&i);
  x = x * (1.5 - (half * x * x));
  return x;
}
};
