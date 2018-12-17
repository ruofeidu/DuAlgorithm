#pragma once
#include "common.h"

// for data, see PointIntervalTree.h
namespace HashCustomizedForCashier {
	ifstream fin("hash.in");
	ofstream fout("hash.out");

	class hash {
	public:
		static const int HMOD = 500000;

		class node {
		public:
			string data;
			node *next;
			node(string x = "") :data(x), next(0) {}
		};
		node *h[HMOD];

	public:
		int make(string x) {
			int ans = 0;
			for (int i = 0; i < x.size(); ++i)
				ans = (ans + int(x[i]) - int('A')) % HMOD;
			return ans;
		}

		bool find(string x) {
			int index = make(x);
			node *v = h[index];
			while (v && v->data != x) v = v->next;
			if (v) return true; else return false;
		}

		void ins(string x) {
			int index = make(x);
			node *v = new node(x);
			v->next = h[index];
			h[index] = v;
		}

		void del(string x) {
			int index = make(x);
			node *v = h[index];
			if (!v) return;
			if (v->data == x) { h[index] = v->next; return; }
			while (v->next && v->next->data != x) v = v->next;
			if (!v->next) return;
			v->next = v->next->next;
		}
	};

	hash h;
	int n;
	char c;
	string x;

	int main() {
		fin >> n;
		for (int i = 0; i < n; ++i) {
			fin >> c >> x;
			switch (c) {
			case 'I': h.ins(x); break;
			case 'D': h.del(x); break;
			case 'F': fout << h.find(x) << endl; break;
			}
		}
		return 0;
	}
}

namespace HashMaker {
	ofstream fout("hash.in");

	const int MAXN = 1000;
	const int MAXL = 30;

	string s[MAXN];

	int main() {
		srand(time(0) ^ 141592653);
		int n = rand() % MAXN;
		fout << 3 * n << endl;
		for (int i = 0; i < n; ++i) {
			fout << "I ";
			s[i] = "";
			char c;
			for (int j = 0; j < MAXL; ++j) {
				c = char('A' + rand() % 26);
				s[i] = s[i] + c;
				fout << c;
			}
			fout << endl;
		}

		for (int i = 0; i < 2 * n; ++i)
			if (rand() % 2 == 0) fout << "D " << s[rand() % n] << endl; else
				fout << "F " << s[rand() % n] << endl;

		return 0;
	}
}
