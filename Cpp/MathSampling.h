#pragma once
#include "common.h"
// glm support
#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"

namespace MathSampling {
	const float M_PI = 3.1415926535897932f;
	const float INV_FOURPI = 0.25f * M_PI;

	using namespace glm;
	vec2 squareToUniformDisk(const vec2 &sample) {
		auto two_pi_y = 2 * M_PI * sample.y;
		auto sqrt_x = sqrt(sample.x);
		return vec2(cos(two_pi_y) * sqrt_x, sin(two_pi_y) * sqrt_x);
	}

	float squareToUniformDiskPdf(const vec2 &p) {
		return (p.x * p.x + p.y * p.y < 1.0f) ? 1.0f / M_PI : 0.0f;
	}

	vec3 squareToUniformSphere(const vec2 &sample) {
		float z = 1.0f - 2.0f * sample.x;
		float r = sqrt(std::max(0.0f, 1.0f - z * z));
		float two_pi_y = 2.0f * M_PI * sample.y;
		float sin_phi = sin(two_pi_y);
		float cos_phi = cos(two_pi_y);
		return vec3(r * cos_phi, r * sin_phi, z);
	}

	float squareToUniformSpherePdf(const vec3 &v) {
		return (abs(v.x * v.x + v.y * v.y + v.z * v.z - 1.0f) < 1e-6) ? INV_FOURPI : 0.0f;
	}

	vec3 squareToUniformHemisphere(const vec2 &sample) {
		float z = sample.x;
		float two_pi_y = 2.0f * M_PI * sample.y;
		float r = sqrt(1.0f - z * z);
		float sin_phi = sin(two_pi_y);
		float cos_phi = cos(two_pi_y);
		return vec3(r * cos_phi, r * sin_phi, z);
	}
}