#pragma once
#include "common.h"

class StringMisc {
	// 6. ZigZag Conversion
	// Input: s = "PAYPALISHIRING", numRows = 3
	// Output : "PAHNAPLSIIGYIR"
	/*
	P   A   H   N
	A P L S I I G
	Y   I   R
	*/
	string convert(string s, int numRows) {
		if (numRows == 1) return s;
		int y = 0, x = 0, k = 0;
		string ans = "";
		for (int i = 0; i < numRows; ++i) {
			k = i;
			bool odd = false;
			while (k < s.size()) {
				ans += s[k];
				odd = !odd;
				if (i == 0 || i == numRows - 1) {
					k += numRows - 1 + numRows - 1;
				}
				else {
					k += odd ? (numRows - i - 1 + numRows - i - 1) : (i + i);
				}
			}
		}
		return ans;
	}

	// 30. Substring with Concatenation of All Words [H]
	/*
	Input:
	  s = "barfoothefoobarman",
	  words = ["foo","bar"]
	Output: [0,9]
	Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
	The output order does not matter, returning [9,0] is fine too.
	*/
	vector<int> findSubstring(string s, vector<string>& words) {
		auto n = words.size();
		auto m = words.front().size();

		vector<int> ans;
		if (s.length() < m * n) return ans;
		unordered_map<string, int> wordCount;
		for (auto const& w : words) ++wordCount[w];
		for (auto i = s.begin(); i <= prev(s.end(), m * n); ++i) {
			unordered_map<string, int> unused(wordCount);
			for (auto j = i; j < next(i, m * n); j += m) {
				auto pos = unused.find(string(j, next(j, m)));
				if (pos == unused.end() || pos->second == 0) break;
				if (--pos->second == 0) unused.erase(pos);
			}
			if (unused.size() == 0) ans.push_back((int)distance(s.begin(), i));
		}
		return ans;
	}
};

// 10. Regular Expression Matching
class RegularMatchDotStar {
	// Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
public:
	// find s in p
	bool isMatch(string s, string p) {
		return isMatch(s.c_str(), p.c_str());
	}

private:
	// Input: aab, c*a*b
	// Output: true

	// find s in p; 
	bool isMatch(const char* s, const char* p) {
		if (*p == '\0') return *s == '\0';

		if (*(p + 1) != '*') {
			if (*p == *s || (*p == '.' && *s != '\0')) {
				return isMatch(s + 1, p + 1);
			}
			else {
				return false;
			}
		}
		else {
			while (*p == *s || (*p == '.' && *s != '\0')) {
				if (isMatch(s, p + 2)) {
					return true;
				}
				s++;
			}
			return isMatch(s, p + 2);
		}
	}
};

// 44. Wildcard Matching
// Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.
class RegularMatchQuestionStar {
	bool isMatch(string s, string p) {
		return isMatch(s.c_str(), p.c_str());
	}

	bool isMatch(const char* s, const char* p) {
		bool star = false;
		const char* ss, *pp;
		for (ss = s, pp = p; *ss != '\0'; ++ss, ++pp) {
			switch (*pp) {
			case '?':
				break;
			case '*':
				star = true;
				s = ss, p = pp;
				while (*p == '*') ++p; // skip continuous stars
				if (*p == '\0') return true;
				ss = s - 1;
				pp = p - 1;
				break;
			default:
				if (*ss != *pp) {
					if (!star) return false;
					++s;
					ss = s - 1;
					pp = p - 1; // has star, whatever
				}
			}
		}

		while (*pp == '*') ++pp;
		return (*pp == '\0');
	}

	// 68. Text Justification
	// Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		auto n = words.size();
		int curWidth = 0;
		int preID = 0;
		int curID = -1;
		vector<string> ans;

		while (curID + 1 < n) {
			++curID;
			int extraSpace = (curWidth == 0) ? 0 : 1;
			if (curWidth == 0 && (int)words[curID].size() > maxWidth) {
				ans.push_back(words[curID]);
				++preID;
				continue;
			}
			if (curWidth + extraSpace + (int)words[curID].size() <= maxWidth) {
				curWidth += extraSpace + (int)words[curID].size();
				continue;
			}
			else {
				int numCurLine = curID - preID;
				--curID;
				if (numCurLine == 1) {
					string res = words[curID] + string(maxWidth - words[curID].size(), ' ');
					ans.push_back(res);
					cout << res << endl;
					preID = curID + 1;
					curWidth = 0;
					continue;
				}
				else {
					int numSpace = (maxWidth - curWidth) / (numCurLine - 1);
					int extraSpace = (maxWidth - curWidth) % (numCurLine - 1);
					string res = "";
					for (int i = preID; i < preID + extraSpace; ++i) {
						res += words[i] + string(numSpace + 1 + 1, ' ');
					}
					for (int i = preID + extraSpace; i < preID + numCurLine; ++i) {
						res += words[i];
						if (i != preID + numCurLine - 1) res += string(numSpace + 1, ' ');
					}
					cout << res << endl;
					ans.push_back(res);
					preID = curID + 1;
					curWidth = 0;
					continue;
				}
			}
		}
		string last = "";
		for (int i = preID; i < n; ++i) {
			if (i != preID) last += " ";
			last += words[i];
		}
		curWidth = (int)last.size();
		last += string(maxWidth - curWidth, ' ');
		cout << last << endl;
		ans.push_back(last);
		return ans;
	}
};
