#include "common.h"

// Algorithms

/// Dynamic Programming
#include "DPLinear.h"
#include "DPCounts.h"
#include "DPKnapsack.h"
#include "DPLCS.h"
#include "DPLIS.h"
#include "DPNumbers.h"
#include "DPStock.h"

#include "DPGrid.h"

#include "DPTree.h"

/// Games
#include "GameTheory.h"
#include "GameNim.h"
#include "GameGo.h"
#include "GameRock.h"
#include "GameSudoku.h"
#include "GameNQueen.h"
#include "GameTicTacToe.h"

/// Graph Theory
#include "GraphDijkstra.h"
#include "GraphMisc.h"
#include "GraphFloyd.h"
#include "GraphPrim.h"
#include "GraphBipartite.h"
#include "GraphNetworkFlow.h"

/// Greedy
#include "Greedy.h"

#include "Palindrome.h"
#include "RMQ.h"
#include "RSQ.h"
#include "Scanning.h"

/// Math
/// High Precision
#include "BigInt.h"
#include "Fraction.h"
#include "HPMisc.h"

#include "MathCount.h"
#include "MathDeduction.h"
#include "MathMatrix.h"
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
#include "SortCount.h"
#include "STLSort.h"

/// Strings
#include "StringCTricks.h"
#include "StringKMP.h"
#include "StringRabinKarp.h"
#include "StringSTL.h"
#include "StringMisc.h"

#include "STLAlgorithms.h"

// Data Structures
/// linear
#include "ArrayInPlace.h"
#include "Intervals.h"
#include "LinkedLists.h"
#include "Queues.h"
#include "Stacks.h"

#include "STLLinear.h"

/// geometry
#include "GeoLines.h"
#include "GeoPoints.h"
#include "GeoPolygons.h"
#include "Geo3D.h"

/// cluster
#include "UnionSets.h"

/// spatial
#include "Grids.h"
#include "GridsInPlace.h"
#include "QuadTrees.h"
#include "Octree.h"
#include "SegmentTrees.h"
#include "SegmentTreeX2.h"

/// strings
#include "StringSuffixArrays.h"
#include "Tries.h"

/// trees
#include "BinaryTreeMisc.h"
#include "BinaryTreeOrders.h"
#include "BinarySearchTrees.h"
#include "Heaps.h"
#include "Multisets.h"
#include "RedBlackTree.h"
#include "Treaps.h"

/// Architecture
#include "LFUCache.h"
#include "LRUCache.h"
#include "Times.h"

// Operating System
#include "SharedPointers.h"

// Design Patterns
#include "PatternAbstractFactory.h"
#include "PatternFactory.h"
#include "PatternSingleton.h"
#include "PatternRAII.h"

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
      case 'I':
        t.ins(x);
        break;
      case 'D':
        t.del(x);
        break;
      case 'F':
        printf("%d\n", t.kth(x));
        break;
      case 'B':
        printf("%d\n", t.find(x));
        break;
    }
  }
  return 0;
}
}

int main() {
  TestTreap::main();
  // SharedPointers::main();

  system("pause");
  return 0;
}
