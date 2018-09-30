#include "common.h"

// Algorithms

/// Dynamic Programming
#include "DPLinear.h"
#include "DPNumbers.h"
#include "DPLCS.h"
#include "DPKnapsack.h"
#include "DPStock.h"
#include "DPLIS.h"

#include "DPGrid.h"

#include "DPTree.h"

/// Games
#include "GameTheory.h"
#include "GameNim.h"
#include "GameNQueen.h"
#include "GameTicTacToe.h"

/// Graph Theory
#include "GraphDijkstra.h"
#include "GraphMisc.h"
#include "GraphNetworkFlow.h"

/// Greedy
#include "Greedy.h"

/// Math
/// High Precision
#include "BigInt.h"
#include "Fraction.h"
#include "HighPrecision.h"

#include "MathCount.h"
#include "MathMisc.h"
#include "MathMods.h"
#include "MathNumbers.h"
#include "MathPermutation.h"
#include "MathPrime.h"
#include "MathRandom.h"
#include "MathSampling.h"

/// Hashing
#include "HashMaps.h"

/// Search
#include "SearchBFS.h"
#include "SearchBinary.h"
#include "SearchDFS.h"
#include "SearchGrid.h"

/// Simulation
#include "SimulationNum2Word.h"

/// Sorts
#include "SortQuick.h"
#include "SortMerge.h"
#include "SortBubble.h"
#include "SortInsert.h"
#include "SortTiny.h"

/// Strings
#include "StringCTricks.h"
#include "StringKMP.h"
#include "StringRabinKarp.h"

// Data Structures
/// linear
#include "Intervals.h"
#include "LinkedLists.h"
#include "Queues.h"
#include "Stacks.h"

/// geometry
#include "GeoLines.h"

/// cluster
#include "UnionSets.h"

/// spatial
#include "Grids.h"
#include "QuadTrees.h"

/// strings
#include "StringSuffixArrays.h"
#include "Tries.h"

/// trees
#include "BinarySearchTrees.h"
#include "Heaps.h"
#include "Multisets.h"
#include "SegmentTrees.h"
#include "Treaps.h"

// Design Patterns
#include "PatternAbstractFactory.h"
#include "PatternFactory.h"
#include "PatternSingleton.h"

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
