#include "common.h"
#include "math.h"
#include "sorts.h"
#include "graph.h"
#include "networkflow.h"

#include "linkedlist.h"
#include "unionset.h"
#include "trie.h"
#include "heap.h"
#include "treap.h"


namespace TestTreap {
	Treap<int> t;
	int n, m, x;
	char s[2];

	int main() {
		srand((unsigned int)time(0) ^ 141592653);
		freopen("BST.in", "r", stdin);
		freopen("BST.out", "w", stdout);
		scanf("%d%d", &m, &n);
		for (int i = 0; i < n; ++i) {
			scanf("%s%d", &s, &x);
			switch (s[0]) {
			case 'I': t.ins(x); break;
			case 'D': t.del(x); break;
			case 'F': printf("%d\n", t.kth(x)); break;
			case 'B': printf("%d\n", t.find(x)); break;
			}
		}
		return 0;
	}
}

int main() {
	TestTreap::main();

	system("pause");
	return 0;
}