#pragma once
#include "common.h"

namespace StringTricks {
	void reverse(char *s) {
		size_t n = strlen(s);
		for (size_t i = 0; i < n / 2; ++i) {
			swap(s[i], s[n - i - 1]);
		}
	}

	void testReverse() {
		char s[] = "1234567890";
		reverse(s);
		cout << s << endl;
	}

	void removeDuplicate(char s[]) {
		size_t len = strlen(s);
		if (len < 2) return;
		bool c[256];
		memset(c, 0, sizeof(c));
		int p = 0;
		for (size_t i = 0; i < len; ++i) {
			if (!c[s[i]]) {
				s[p++] = s[i];
				c[s[i]] = true;
			}
		}
		s[p] = '\0';
	}

	void testDuplicate() {
		char ss1[] = "abcde";
		char ss2[] = "aaabbb";
		char ss3[] = "";
		char ss4[] = "abababc";
		char ss5[] = "ccccc";
		removeDuplicate(ss1);
		removeDuplicate(ss2);
		removeDuplicate(ss3);
		removeDuplicate(ss4);
		removeDuplicate(ss5);
		cout << ss1 << " " << ss2 << " " << ss3 << " " << ss4 << " " << ss5 << endl;
	}

	// Write a method to decide if two strings are anagrams or not.
	bool isAnagram(string s, string t) {
		if (s.length() != t.length() || s == "" || t == "")
			return false;

		int len = (int)s.length();
		int c[256];
		memset(c, 0, sizeof(c));
		for (int i = 0; i < len; ++i) {
			++c[(int)s[i]];
			--c[(int)t[i]];
		}
		for (int i = 0; i < 256; ++i)
			if (c[i] != 0)
				return false;
		return true;
	}

	void testAnagram() {
		cout << isAnagram("apex", "peax");
	}

	// Write a method to replace all spaces in a string with ?20?

	void replace(char *c) {
		if (c == NULL) return;
		int len = (int)strlen(c);
		if (len == 0) return;
		int cnt = 0;
		for (int i = 0; i < len; ++i) {
			if (c[i] == ' ')
				++cnt;
		}
		int p = len + 2 * cnt;
		c[p--] = '\0';//the space must be allocated first.
		for (int i = len - 1; i >= 0; --i) {
			if (c[i] == ' ') {
				c[p] = '0';
				c[p - 1] = '2';
				c[p - 2] = '%';
				p -= 3;
			}
			else {
				c[p] = c[i];
				--p;
			}
		}
	}

	void testReplace() {
		const int len = 100;
		char c[len] = "";
		replace(c);
		cout << c << endl;
	}

	void swap(int &a, int &b) {
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}

	// http://blog.csdn.net/holybin/article/details/36181061
	// Implement an algorithm to determine if a string has all unique characters. What if you can not use additional data structures?

	bool isUnique(string s) {
		bool a[256];
		memset(a, 0, sizeof(a));
		for (int i = 0; i < s.size(); ++i) {
			int v = (int)s[i];
			if (a[v]) return false;
			a[v] = true;
		}
		return true;
	}

	bool isUnique8(string s) {
		int check = 0;
		for (int i = 0; i < s.size(); ++i) {
			int v = (int)(s[i] - 'a');
			if (check & (1 << v)) return false;
			check |= (1 << v);
		}
		return true;
	}

	// 58. Length of Last Word
	int lengthOfLastWord(string s) {
		//from the reverse iterator, find the first alphabetic letter
		auto first = find_if(s.rbegin(), s.rend(), ::isalpha);
		//find the first which is not
		auto last = find_if_not(first, s.rend(), ::isalpha);
		return (int)distance(first, last);
	}
}