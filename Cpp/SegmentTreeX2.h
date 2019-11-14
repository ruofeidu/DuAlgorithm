#pragma once
#include "common.h"

namespace SegmentTreeX2 {
const int N = 1000;
const int M = 500;

struct node {
  int st, ed, c;  // c: level
  double m;       // m: measurement
} ST[N];

struct line {
  double x, y1,
      y2;  // vertical segments, y1 and y2 are two vertical coordinates
  bool s;  // s=1, left; s=0, right
} Line[M];
double y[M], ty[M];  // y: int2double, ty: aux y

void build(int root, int st, int ed) {
  ST[root].st = st;
  ST[root].ed = ed;
  ST[root].c = 0;
  ST[root].m = 0;
  if (ed - st > 1) {
    int mid = (st + ed) / 2;
    build(root * 2, st, mid);
    build(root * 2 + 1, mid, ed);
  }
}

inline void updata(int root) {
  if (ST[root].c > 0)
    // map to double
    ST[root].m = y[ST[root].ed - 1] - y[ST[root].st - 1];
  else if (ST[root].ed - ST[root].st == 1)
    ST[root].m = 0;
  else
    ST[root].m = ST[root * 2].m + ST[root * 2 + 1].m;
}

void insert(int root, int st, int ed) {
  if (st <= ST[root].st && ST[root].ed <= ed) {
    ST[root].c++;
    updata(root);
    return;

    using namespace std;
  }
  // redundant
  if (ST[root].ed - ST[root].st == 1) return;

  int mid = (ST[root].ed + ST[root].st) / 2;
  if (st < mid) insert(root * 2, st, ed);
  if (ed > mid) insert(root * 2 + 1, st, ed);
  updata(root);
}

void Delete(int root, int st, int ed) {
  if (st <= ST[root].st && ST[root].ed <= ed) {
    ST[root].c--;
    updata(root);
    return;
  }
  // redundant
  if (ST[root].ed - ST[root].st == 1) return;
  int mid = (ST[root].st + ST[root].ed) / 2;
  if (st < mid) Delete(root * 2, st, ed);
  if (ed > mid) Delete(root * 2 + 1, st, ed);
  updata(root);
}

// binary search
int Correspond(int n, double t) {
  int low = 0, high = n - 1;
  while (low < high) {
    int mid = (low + high) / 2;
    if (t > y[mid])
      low = mid + 1;
    else
      high = mid;
  }
  return high + 1;
}
bool cmp(line l1, line l2) { return l1.x < l2.x; }

int main() {
  int n, i, num, l = 0, r, c = 0;
  double area, x1, x2, y1, y2;
  while (cin >> n, n) {
    for (i = 0; i < n; i++) {
      cin >> x1 >> y1 >> x2 >> y2;
      Line[2 * i].x = x1;
      Line[2 * i].y1 = y1;
      Line[2 * i].y2 = y2;
      Line[2 * i].s = 1;
      Line[2 * i + 1].x = x2;
      Line[2 * i + 1].y1 = y1;
      Line[2 * i + 1].y2 = y2;
      Line[2 * i + 1].s = 0;
      ty[2 * i] = y1;
      ty[2 * i + 1] = y2;
    }
    n <<= 1;
    sort(Line, Line + n, cmp);
    sort(ty, ty + n);
    y[0] = ty[0];
    // ty so that y contains unique elements
    for (i = num = 1; i < n; i++)
      if (ty[i] != ty[i - 1]) y[num++] = ty[i];
    build(1, 1, num);
    area = 0;
    for (i = 0; i < n - 1; i++) {
      // segment in tre Correspond(num, Line[i].y1);
      r = Correspond(num, Line[i].y2);
      if (Line[i].s)  // insert to left
        insert(1, l, r);
      else  // remove right
        Delete(1, l, r);
      area += ST[1].m * (Line[i + 1].x - Line[i].x);
    }
    cout << "Test case #" << ++c << endl << "Total explored area : ";
    cout << fixed << setprecision(2) << area << endl << endl;
  }
  return 0;
}
}
