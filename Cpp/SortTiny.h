#pragma once
#include "common.h"

namespace SmallSort {
// Sorts four elements.
template <class T>
vector<T> sort(T i, T j, T k, T l) {
  if (i < j) {
    if (j < k) {
      if (k < l) return {i, j, k, l};
      if (j < l) return {i, j, l, k};
      if (i < l) return {i, l, j, k};
      return {l, i, j, k};
    } else if (i < k) {
      if (j < l) return {i, k, j, l};
      if (k < l) return {i, k, l, j};
      if (i < l) return {i, l, k, j};
      return {l, i, k, j};
    } else {
      if (j < l) return {k, i, j, l};
      if (i < l) return {k, i, l, j};
      if (k < l) return {k, l, i, j};
      return {l, k, i, j};
    }
  } else {
    if (i < k) {
      if (k < l) return {j, i, k, l};
      if (i < l) return {j, i, l, k};
      if (j < l) return {j, l, i, k};
      return {l, j, i, k};
    } else if (j < k) {
      if (i < l) return {j, k, i, l};
      if (k < l) return {j, k, l, i};
      if (j < l) return {j, l, k, i};
      return {l, j, k, i};
    } else {
      if (i < l) return {k, j, i, l};
      if (j < l) return {k, j, l, i};
      if (k < l) return {k, l, j, i};
      return {l, k, j, i};
    }
  }
}
}
