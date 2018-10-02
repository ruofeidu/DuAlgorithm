#pragma once
#include "common.h"

namespace GeoPoints {
	using Polygon = vector<Point>;
	struct Segment { Point a, b; };
	const float EP = 1e-10f;

	bool operator == (const Point& p1, const Point& p2) {
		return (fabs(p1.x - p2.x) < EP) && (fabs(p1.y - p2.y) < EP);
	}

	bool operator != (const Point& p1, const Point& p2) {
		return (fabs(p1.x - p2.x) > EP) || (fabs(p1.y - p2.y) > EP);
	}

	double cross(Point p1, Point p2, Point p0) {
		return((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
	}

	int intersectsTolerent(Segment u, Segment v)
	{
		return((max(u.a.x, u.b.x) >= min(v.a.x, v.b.x)) &&
			(max(v.a.x, v.b.x) >= min(u.a.x, u.b.x)) &&
			(max(u.a.y, u.b.y) >= min(v.a.y, v.b.y)) &&
			(max(v.a.y, v.b.y) >= min(u.a.y, u.b.y)) &&

			(cross(v.a, u.b, u.a)*cross(u.b, v.b, u.a) >= 0) &&

			(cross(u.a, v.b, v.a)*cross(v.b, u.b, v.a) >= 0));
	}

	// test if two segment intersects
	int intersects(Segment u, Segment v) {
		return((intersectsTolerent(u, v)) && (u.a != v.a) && (u.a != v.b) && (u.b != v.a) && (u.b != v.b));
	}

	int ponls(Segment l, Point p) {
		return((cross(l.b, p, l.a) == 0) && (((p.x - l.a.x)*(p.x - l.b.x) < 0) || ((p.y - l.a.y)*(p.y - l.b.y) < 0)));
	}

	bool pointInPolygon(int vcount, Polygon Polygon, Point q)
	{
		int c = 0, i, n;
		Segment l1, l2;
		l1.a = q; l1.b = q;
		l1.b.x = numeric_limits<int>::max();
		n = vcount;
		for (i = 0; i < vcount; ++i) {
			l2.a = Polygon[i];
			l2.b = Polygon[(i + 1) % n];
			if ((intersects(l1, l2)) || (
				(ponls(l1, Polygon[(i + 1) % n])) && (
				(!ponls(l1, Polygon[(i + 2) % n])) && (cross(Polygon[i], Polygon[(i + 1) % n], l1.a) *
					cross(Polygon[(i + 1) % n], Polygon[(i + 2) % n], l1.a) > 0)
					|| (ponls(l1, Polygon[(i + 2) % n])) &&
					(cross(Polygon[i], Polygon[(i + 2) % n], l1.a) *
						cross(Polygon[(i + 2) % n], Polygon[(i + 3) % n], l1.a) > 0)
					))) c++;
		}
		return(c % 2 != 0);
	}

}