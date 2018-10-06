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

	// cross product of (P1-P0) and (P2-P0)
	double cross(Point p1, Point p2, Point p0) {
		return ((p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y));
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

	// test if point is on segment
	int pOnL(Segment l, Point p) {
		return (cross(l.b, p, l.a) == 0) && (((p.x - l.a.x)*(p.x - l.b.x) < 0) || ((p.y - l.a.y)*(p.y - l.b.y) < 0));
	}

	// test if a point is within a polygon
	bool pointInPolygon(int vcount, Polygon ply, Point q) {
		int intersections = 0, i, n;
		Segment l1, l2;
		l1.a = q; l1.b = q;
		l1.b.x = numeric_limits<int>::max();
		n = vcount;
		for (i = 0; i < vcount; ++i) {
			l2.a = ply[i];
			l2.b = ply[(i + 1) % n];
			if ((intersects(l1, l2)) || (
				(pOnL(l1, ply[(i + 1) % n])) && (
				  (!pOnL(l1, ply[(i + 2) % n])) && 
					(cross(ply[i], ply[(i + 1) % n], l1.a) * cross(ply[(i + 1) % n], ply[(i + 2) % n], l1.a) > 0)
					|| (pOnL(l1, ply[(i + 2) % n])) && 
					   (cross(ply[i], ply[(i + 2) % n], l1.a) * cross(ply[(i + 2) % n], ply[(i + 3) % n], l1.a) > 0)
					)))
				++intersections;
		}
		return intersections & 1;
	}

	// compute area of polygon
	double area(Polygon &ply) {
		const int n = (int)ply.size(); 
		if (n < 3) 
			return 0;

		double res = ply[0].y * (ply.back().x - ply[1].x); 
		for (int i = 1; i < n; ++i)
			res += ply[i].y * (ply[(i - 1)].x - ply[(i + 1) % n].x); 
		
		return res / 2;
	}


}