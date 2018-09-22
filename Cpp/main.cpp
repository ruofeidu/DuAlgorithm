#include "common.h"

// Algorithms
#include "dp1d.h"

#include "math.h"
#include "randoms.h"

#include "graph.h"
#include "networkflow.h"

#include "greedy.h"

#include "palindrome.h"
#include "rsq.h"
#include "scan.h"

#include "games.h"

#include "bits.h"

#include "bigint.h"

#include "number2words.h"

#include "cstringtricks.h"

#include "quicksort.h"
#include "mergesort.h"
#include "bubblesort.h"
#include "instertsort.h"
#include "smallsort.h"

#include "bfs.h"
#include "binarysearch.h"
#include "dfs.h"

// Data Structures
/// linear
#include "interval.h"
#include "linkedlist.h"
#include "queues.h"
#include "stacks.h"

/// cluster
#include "unionset.h"

/// spatial
#include "grid.h"
#include "quadtree.h"

/// strings
#include "trie.h"

/// trees
#include "binarysearchtrees.h"
#include "heap.h"
#include "multisets.h"
#include "segmenttree.h"
#include "treap.h"

// Design Patterns
#include "abstractfactory.h"
#include "factory.h"
#include "singleton.h"

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