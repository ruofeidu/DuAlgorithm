#pragma once
#include "common.h"
// glm support
#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"

/*
	Sample Warping and corresponding validation

	1. Compute the CDF of the 1D distribution
	2. Derive the inverse of the CDF
	3. Map a random variable through the inverse from the previous step.
*/
namespace MathSampling {
	using SquaredImage = vector<vector<float>>;
	const float M_PI = 3.1415926535897932f;
	const float M_PI_2 = M_PI / 2.0f;
	const float M_PI2 = M_PI * 2.0f;
	const float INV_PI = 1.0f / M_PI;
	const float INV_TWOPI = 0.5f / M_PI;
	const float INV_FOURPI = 0.25f / M_PI;

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

	float squareToUniformHemispherePdf(const vec3 &v) {
		float theta = acos(v.z);
		return (abs(v.x * v.x + v.y * v.y + v.z * v.z - 1.0f) < 1e-6
			&& theta > 0 && theta < M_PI_2) ? INV_TWOPI : 0.0f;
	}

	inline float tent_func(float x) {
		return (x > 1 || x < -1) ? 0 : 1 - abs(x);
	}

	float inverse_tent(float x) {
		if (x < 0.5f) return std::sqrt(2.0f * x) - 1.0f;
		return 1.0f - std::sqrt(2.0f - 2.0f * x);
	}


	vec3 squareToCosineHemisphere(const vec2 &sample) {
		float r1 = 2.0f * sample.x - 1.0f;
		float r2 = 2.0f * sample.y - 1.0f;
		float phi, r;
		if (r1 == 0 && r2 == 0) {
			r = phi = 0;
		}
		else if (r1 * r1 > r2 * r2) {
			r = r1;
			phi = (M_PI / 4.0f) * (r2 / r1);
		}
		else {
			r = r2;
			phi = (M_PI / 2.0f) - (r1 / r2) * (M_PI / 4.0f);
		}
		float cosPhi = cos(phi);
		float sinPhi = sin(phi);
		vec2 t = vec2(r * cosPhi, r * sinPhi);
		float z = sqrt(std::max(0.0f, 1.0f - t.x*t.x - t.y*t.y));
		return vec3(t.x, t.y, z);
	}

	float squareToCosineHemispherePdf(const vec3 &v) {
		float theta = acos(v.z);
		return (abs(v.x * v.x + v.y * v.y + v.z * v.z - 1.0f) < 1e-6
			&& theta > 0 && theta < M_PI_2) ? INV_PI * cos(theta) : 0.0f;
	}

	vec3 squareToBeckmann(const vec2 &sample, float alpha) {
		float logSample = -log(sample.x);
		if (std::isinf(logSample))
			logSample = 0;
		float tanTheta2 = alpha * alpha * logSample;
		float theta = atan(sqrt(tanTheta2));
		float phi = M_PI2 * sample.y;
		return vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
	}

	float squareToBeckmannPdf(const vec3 &m, float alpha) {
		if (m.z <= 0) return 0.0f;
		float cosTheta2 = m.z * m.z;
		float cosTheta3 = cosTheta2 * m.z;
		float sinTheta2 = 1.0f - cosTheta2;
		float tanTheta2 = sinTheta2 / cosTheta2;
		float alpha2 = alpha * alpha;
		return INV_TWOPI * 2 * exp(-tanTheta2 / alpha2) / alpha2 / cosTheta3;
	}

	vec2 squareToTent(const vec2 &sample) {
		return vec2(inverse_tent(sample.x), inverse_tent(sample.y));
	}

	float squareToTentPdf(const vec2 &p) {
		return tent_func(p.x) * tent_func(p.y);
	}

	//
	vec2 hierarchicalSampleWarping2x2(const vec2 & sample, const SquaredImage &a) {
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_real_distribution<float>  d0(0.0, 0.5);
		std::uniform_real_distribution<float>  d1(0.5, 1.0);

		float left = a[0][0] + a[1][0];
		if (sample.x < left) {
			if (sample.y < a[0][0] / left) {
				return vec2(d0(generator), d0(generator));
			}
			else {
				return vec2(d0(generator), d1(generator));
			}
		}
		else {
			if (sample.y < a[0][1] / (a[0][1] + a[1][1])) {
				return vec2(d1(generator), d0(generator));
			}
			else {
				return vec2(d1(generator), d1(generator));
			}
		}
	}

	vec2 hierarchicalSampleWarping(const vec2 & sample, const SquaredImage &a, int level, float xmin, float xmax, float ymin, float ymax, int cy, int cx) {
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		if (level == 10) {
			std::uniform_real_distribution<float>  dx(xmin, xmax);
			std::uniform_real_distribution<float>  dy(ymin, ymax);
			return vec2(dx(generator), dy(generator));
		}
		else {
			vec2 center = vec2((xmax - xmin) * 0.5f, (ymax - ymin) * 0.5f);
			std::uniform_real_distribution<float>  dx0(xmin, center.x);
			std::uniform_real_distribution<float>  dx1(center.x, xmax);
			std::uniform_real_distribution<float>  dy0(ymin, center.y);
			std::uniform_real_distribution<float>  dy1(center.y, ymax);

			float left = a[level][cy * 2, cx * 2] + a[level][cy * 2 + 1, cx * 2];
			if (sample.x < left) {
				if (sample.y < a[level][cy * 2, cx * 2] / left) {
					vec2 s = vec2(dx0(generator), dy0(generator));
					return hierarchicalSampleWarping(s, a, level + 1, xmin, center.x, ymin, center.y, cy * 2, cx * 2);
				}
				else {
					vec2 s = vec2(dx0(generator), dy1(generator));
					return hierarchicalSampleWarping(s, a, level + 1, xmin, center.x, center.y, ymax, cy * 2 + 1, cx * 2);
				}
			}
			else {
				if (sample.y < a[level][cy * 2, cx * 2 + 1] / (a[level][cy * 2, cx * 2 + 1] + a[level][cy * 2 + 1, cx * 2 + 1])) {
					vec2 s = vec2(dx1(generator), dy0(generator));
					return hierarchicalSampleWarping(s, a, level + 1, center.x, xmax, ymin, center.y, cy * 2, cx * 2 + 1);
				}
				else {
					vec2 s = vec2(dx1(generator), dy1(generator));
					return hierarchicalSampleWarping(s, a, level + 1, center.x, xmax, center.y, ymax, cy * 2 + 1, cx * 2 + 1);
				}

			}
		}
	}

	float hierarchicalSampleWarping2x2Pdf(const vec2 & p, const SquaredImage &a) {
		ivec2 v = ivec2((int)round(p.x * (1 << a.size())), (int)round(p.y * (1 << a.size())));
		return a[v.x][v.y];
	}
}