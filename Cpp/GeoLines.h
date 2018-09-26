#pragma once
#include "common.h"
// glm support
#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"

namespace Lines {
	using namespace glm;
	bool isSameSide(vec3 p1, vec3 p2, vec3 a, vec3 b) {
		vec3 c1 = cross(b - a, p1 - a);
		vec3 c2 = cross(b - a, p2 - a);
		return dot(c1, c2) >= 0;
	}

	bool isPointInTriangle(vec3 p, vec3 a, vec3 b, vec3 c) {
		return isSameSide(p, a, b, c) && isSameSide(p, b, a, c) && isSameSide(p, c, a, b);
	}

	// compute the intersected point between a line p0, p1, and a plane a, b, c, d
	vec3 calcLinePlaneIntersection(vec3 p0, vec3 p1, vec3 a, vec3 b, vec3 c, vec3 d) {
		vec3 center = (a + b + c + d) / 4.0f;
		vec3 normal = cross(a - b, b - c);
		vec3 line = normalize(p1 - p0);
		float dist = 0.0;
		bool intersected = intersectRayPlane(p0, line, center, normal, dist);
		if (dist <= glm::length(p0 - p1)) {
			vec3 intersected = p0 + line * dist;
			if (isPointInTriangle(intersected, a, b, c) || isPointInTriangle(intersected, b, c, d)) {
				return intersected;
			}
		}
		return vec3(-1, -1, -1);
	}
}