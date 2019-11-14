#pragma once
#include "common.h"
// glm support
#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"

namespace Geometry {
	using byte = unsigned char;
	using TriIndexList = std::vector<unsigned int>;
	using Point3f = glm::vec3;
	using Vector3f = glm::vec3;
	using Point2f = glm::vec2;

	bool operator < (const Point3f &a, const Point3f &b) {
		return a.x < b.x && a.y < b.y && a.z < b.z;
	}
	bool operator <= (const Point3f &a, const Point3f &b) {
		return a.x <= b.x && a.y <= b.y && a.z <= b.z;
	}


	struct Ray3f {
		glm::vec3 o;     ///< Ray origin
		glm::vec3 d;    ///< Ray direction
		glm::vec3 dRcp; ///< Componentwise reciprocals of the ray direction
		float mint;     ///< Minimum position on the ray segment
		float maxt;     ///< Maximum position on the ray segment
	};

	struct Frame {

	};

	struct Intersection {
		/// Position of the surface intersection
		Point3f p;
		/// Unoccluded distance along the ray
		float t;
		/// UV coordinates, if any
		Point2f uv;
		/// Pointer to the associated mesh
		// const Mesh *mesh;

		/// Shading frame (based on the shading normal)
		Frame shFrame;
		/// Geometric frame (based on the true geometry)
		Frame geoFrame;

		/// Create an uninitialized intersection record
		Intersection() { }

		/// Return a human-readable summary of the intersection record
		std::string toString() const;
	};

	const size_t MIN_NUM_TRIANGLES = 10;
	const int OCTREE_DEPTH_LIMIT = 7;

	struct BoundingBox3f {
		Point3f min;
		Point3f max;
		Point3f getCenter() const {
			return (max + min) * 0.5f;
		}
		BoundingBox3f(Point3f _min, Point3f _max) :min(_min), max(_max) {};
		BoundingBox3f() :min(0), max(0) {};

		bool overlaps(const BoundingBox3f &bbox, bool strict = false) {
			if (strict) {
				return (bbox.min < max) && (min < bbox.max);
			}
			else {
				return (bbox.min <= max) && (min <= bbox.max);
			}
		}

		/// Check if a ray intersects a bounding box
		bool rayIntersect(const Ray3f &ray) {
			float nearT = -std::numeric_limits<float>::infinity();
			float farT = std::numeric_limits<float>::infinity();

			for (int i = 0; i < 3; i++) {
				float origin = ray.o[i];
				float minVal = min[i], maxVal = max[i];

				if (ray.d[i] == 0) {
					if (origin < minVal || origin > maxVal)
						return false;
				}
				else {
					float t1 = (minVal - origin) * ray.dRcp[i];
					float t2 = (maxVal - origin) * ray.dRcp[i];

					if (t1 > t2)
						std::swap(t1, t2);

					nearT = std::max(t1, nearT);
					farT = std::min(t2, farT);

					if (!(nearT <= farT))
						return false;
				}
			}

			return ray.mint <= farT && nearT <= ray.maxt;
		}


		/// Return the overlapping region of the bounding box and an unbounded ray
		bool rayIntersect(const Ray3f &ray, float &nearT, float &farT) const {
			nearT = -std::numeric_limits<float>::infinity();
			farT = std::numeric_limits<float>::infinity();

			for (int i = 0; i<3; i++) {
				float origin = ray.o[i];
				float minVal = min[i], maxVal = max[i];

				if (ray.d[i] == 0) {
					if (origin < minVal || origin > maxVal)
						return false;
				}
				else {
					float t1 = (minVal - origin) * ray.dRcp[i];
					float t2 = (maxVal - origin) * ray.dRcp[i];

					if (t1 > t2)
						std::swap(t1, t2);

					nearT = std::max(t1, nearT);
					farT = std::min(t2, farT);

					if (!(nearT <= farT))
						return false;
				}
			}

			return true;
		}

	};


	struct Mesh {
		int numTriangles;

		Mesh() : numTriangles(0) {};
		//// Return an axis-aligned bounding box containing the given triangle
		BoundingBox3f getBoundingBox(uint32_t index) {
			// minmax
			return BoundingBox3f();
		}
		BoundingBox3f getBoundingBox() {
			// minmax
			return BoundingBox3f();
		}

		int getTriangleCount() {
			return numTriangles;
		}


		bool Mesh::rayIntersect(uint32_t index, const Ray3f &ray, float &u, float &v, float &t) const {
			//uint32_t i0 = m_F(0, index), i1 = m_F(1, index), i2 = m_F(2, index);
			//const Point3f p0 = m_V.col(i0), p1 = m_V.col(i1), p2 = m_V.col(i2);
			uint32_t i0 = 0, i1 = 0, i2 = 0;
			const Point3f p0, p1, p2;
			/* Find vectors for two edges sharing v[0] */
			Vector3f edge1 = p1 - p0, edge2 = p2 - p0;

			/* Begin calculating determinant - also used to calculate U parameter */
			Vector3f pvec = glm::cross(ray.d, edge2);

			/* If determinant is near zero, ray lies in plane of triangle */
			float det = glm::dot(edge1, pvec);

			if (det > -1e-8f && det < 1e-8f)
				return false;
			float inv_det = 1.0f / det;

			/* Calculate distance from v[0] to ray origin */
			Vector3f tvec = ray.o - p0;

			/* Calculate U parameter and test bounds */
			u = glm::dot(tvec, pvec) * inv_det;
			if (u < 0.0 || u > 1.0)
				return false;

			/* Prepare to test V parameter */
			Vector3f qvec = glm::cross(tvec, edge1);

			/* Calculate V parameter and test bounds */
			v = dot(ray.d, qvec) * inv_det;
			if (v < 0.0 || u + v > 1.0)
				return false;

			/* Ray intersects triangle -> compute t */
			t = dot(edge2, qvec) * inv_det;

			return t >= ray.mint && t <= ray.maxt;
		}
	};


	class Octree
	{
		using BoundingBoxList = BoundingBox3f[8];

	protected:
		class Node
		{
		public:
			byte depth;
			vector<Node*> child;
			Node() {
				child = vector<Node*>(8);
				depth = 0;
			};

			Node(byte _depth) : depth(_depth) {
				child = vector<Node*>(8);
			};
		};

		class LeafNode : public Node
		{
		public:
			TriIndexList m_triangles;
			LeafNode(TriIndexList _triangles) {
				child = vector<Node*>(0);
				depth = 0;
				m_triangles = _triangles;
			}
		};

	private:

		void calcSubBoxes(BoundingBox3f &_box, BoundingBoxList &boxes) {
			auto pMin = _box.min;
			auto pMax = _box.max;
			auto pCenter = _box.getCenter();
			boxes[0] = BoundingBox3f(pMin, pCenter);
			boxes[1] = BoundingBox3f(Point3f(pCenter.x, pMin.y, pMin.z), Point3f(pMax.x, pCenter.y, pCenter.z));
			boxes[2] = BoundingBox3f(Point3f(pMin.x, pCenter.y, pMin.z), Point3f(pCenter.x, pMax.y, pCenter.z));
			boxes[3] = BoundingBox3f(Point3f(pMin.x, pMin.y, pCenter.z), Point3f(pCenter.x, pCenter.y, pMax.z));
			boxes[4] = BoundingBox3f(Point3f(pCenter.x, pCenter.y, pMin.z), Point3f(pMax.x, pMax.y, pCenter.z));
			boxes[5] = BoundingBox3f(Point3f(pCenter.x, pMin.y, pCenter.z), Point3f(pMax.x, pCenter.y, pMax.z));
			boxes[6] = BoundingBox3f(Point3f(pMin.x, pCenter.y, pCenter.z), Point3f(pCenter.x, pMax.y, pMax.z));
			boxes[7] = BoundingBox3f(Point3f(pCenter.x, pCenter.y, pCenter.z), Point3f(pMax.x, pMax.y, pMax.z));
		}
	protected:
		struct BuildStackItem {
		public:
			Node* node = nullptr;
			Node* parent = nullptr;
			size_t child_id = 8;
			BoundingBox3f &box;
			TriIndexList &triangles;
			TriIndexList sets[8];
			BoundingBoxList boxes;
			bool splitted = false;
			BuildStackItem(BoundingBox3f &_box, TriIndexList &_triangles, Node* _parent, int _child_id = 8) :
				box(_box), triangles(_triangles), parent(_parent), child_id(_child_id) {};
		};

	public:
		Node* build(BoundingBox3f &_box, TriIndexList &_triangles) {
			while (!m_stack.empty()) m_stack.pop();
			if (_triangles.size() < MIN_NUM_TRIANGLES) return new LeafNode(_triangles);

			BuildStackItem rootItem(_box, _triangles, nullptr, 8);
			Node* root = new Node();
			rootItem.node = root;
			m_stack.push(rootItem);
			m_total_nodes = 1;

			while (!m_stack.empty()) {
				auto item = &m_stack.top();
				if (item->triangles.empty() || item->splitted) {
					m_stack.pop();
					continue;
				}
				if (item->triangles.size() < MIN_NUM_TRIANGLES || (item->parent && item->parent->depth > OCTREE_DEPTH_LIMIT)) {
					++m_total_nodes;
					++m_leaf_nodes;
					m_total_triangles += (int)item->triangles.size();
					item->node = new LeafNode(item->triangles);
					if (item->parent != nullptr) item->parent->child[item->child_id] = item->node;
					m_stack.pop();
					continue;
				}
				calcSubBoxes(item->box, item->boxes);

				// assume that a triangle overlaps with an octree cell if the bounding box of the triangle's vertices overlap with the cell
				for (const auto &triIndex : item->triangles) {
					const auto &triBox = m_mesh->getBoundingBox(triIndex);
					//#pragma omp parallel for
					for (int i = 0; i < 8; ++i)
						if (item->boxes[i].overlaps(triBox))
							item->sets[i].push_back(triIndex);
				}

				++m_total_nodes;
				if (item->node == nullptr) item->node = new Node(item->parent->depth + 1);
				++m_interior_nodes;
				if (item->parent != nullptr) item->parent->child[item->child_id] = item->node;
				item->splitted = true;
				for (int i = 0; i < 8; ++i) {
					m_stack.push(BuildStackItem(item->boxes[i], item->sets[i], item->node, i));
				}
			}
			return root;
		}

		Node* build_DFS(BoundingBox3f &_box, TriIndexList &_triangles) {
			if (_triangles.empty())
				return nullptr;

			if (_triangles.size() < MIN_NUM_TRIANGLES) {
				++m_total_nodes;
				++m_leaf_nodes;
				return new LeafNode(_triangles);
			}

			TriIndexList sets[8];
			BoundingBoxList boxes;
			calcSubBoxes(_box, boxes);

			for (const auto &triIndex : _triangles) {
				// assume that a triangle overlaps with an octree cell if the bounding box of the triangle's vertices overlap with the cell
				const auto &triBox = m_mesh->getBoundingBox(triIndex);

				for (int i = 0; i < 8; ++i) {
					if (boxes[i].overlaps(triBox)) {
						sets[i].push_back(triIndex);
					}
				}
				// TODO: get the exact triangle
				//uint32_t i0 = m_mesh->getIndices()(0, triIndex), i1 = m_mesh->getIndices()(1, triIndex), i2 = m_mesh->getIndices()(2, triIndex);
				//const Point3f p0 = m_mesh->getVertexPositions().col(triIndex), p1 = m_mesh->getVertexPositions().col(i1), p2 = m_mesh->getVertexPositions().col(i2);
				//Vector3f edge0 = p1 - p2, edge1 = p1 - p0, edge2 = p2 - p0;
				// test if the three edges intersect with the bounding box
			}
			_triangles.clear();
			++m_total_nodes;
			++m_interior_nodes;
			Node *node = new Node();
			for (int i = 0; i < 8; ++i)
				node->child[i] = build_DFS(boxes[i], sets[i]);

			return node;
		}

		void rayIntersect(Ray3f &_ray, Intersection &_its, bool _shadowRay, bool &foundIntersection, uint32_t &resIndex) {
			rayIntersectNode(m_root, m_box, _ray, _its, _shadowRay, foundIntersection, resIndex);
		}

	private:

		void rayIntersectNode(Node* _node, BoundingBox3f _box, Ray3f &_ray, Intersection &_its, bool _shadowRay, bool &foundIntersection, uint32_t &resIndex) {
			if (_node->child.empty()) {
				LeafNode* leaf = (LeafNode*)_node;
#if USE_OPENMP
#pragma omp parallel for
				for (int i = 0; i < leaf->m_triangles.size(); ++i) {
					const auto triIndex = leaf->m_triangles[i];
#else
				for (auto triIndex : leaf->m_triangles) {
#endif
					float u, v, t;
					if (m_mesh->rayIntersect(triIndex, _ray, u, v, t)) {
						/* An intersection was found! Can terminate
						immediately if this is a shadow ray query */
						if (_shadowRay) return;
						_ray.maxt = _its.t = t;
						_its.uv = Point2f(u, v);
						// _its.mesh = m_mesh;
						resIndex = triIndex;
						foundIntersection = true;
					}
				}
				//}
				return;
			}

			BoundingBoxList boxes;
			calcSubBoxes(_box, boxes);

			//// naive implementation
			//for (int i = 0; i < 8; ++i) {
			//	if (_node->child[i] != nullptr && boxes[i].rayIntersect(_ray)) {
			//		rayIntersectNode(_node->child[i], boxes[i], _ray, _its, _shadowRay, foundIntersection, resIndex);
			//	}
			//}

			// sort by nearT
			int intersects[8];
			float dummy;

			vector<pair<float, int>> nearT(8);

#if USE_OPENMP
#pragma omp parallel for
#endif
			for (int i = 0; i < 8; ++i) {
				nearT[i].second = i;
				intersects[i] = (_node->child[i] != nullptr && boxes[i].rayIntersect(_ray, nearT[i].first, dummy));
				if (!intersects[i]) nearT[i].first = INFINITY;
			}

			sort(nearT.begin(), nearT.end(), [](const pair<float, int> &left, const pair<float, int> &right) { return left.first < right.first; });
#if USE_OPENMP
#pragma omp parallel for
#endif
			for (int i = 0; i < 8; ++i) {
				int id = nearT[i].second;
				if (intersects[id] && nearT[i].first < _ray.maxt)
					rayIntersectNode(_node->child[id], boxes[id], _ray, _its, _shadowRay, foundIntersection, resIndex);
			}
		}

	public:
		Octree(Mesh *_mesh) {
			this->nodeCount = 0;
			m_total_triangles = 0;
			this->m_mesh = _mesh;
			TriIndexList initialTriSet(m_mesh->getTriangleCount());
			for (int i = 0; i < m_mesh->getTriangleCount(); ++i)
				initialTriSet[i] = i;

			m_box = _mesh->getBoundingBox();
			this->m_root = build(m_box, initialTriSet);
			cout << "Leaf nodes: " << m_leaf_nodes << endl;
			cout << "Interior nodes: " << m_interior_nodes << endl;
			cout << "Avereage Triangles Per Leaf Node: " << (double)m_total_triangles / m_leaf_nodes << endl;
			cout << "Total nodes: " << m_total_nodes << endl;
		}

	private:
		stack<BuildStackItem> m_stack;

		Mesh* m_mesh = nullptr;
		BoundingBox3f m_box;

	private:
		int m_total_nodes = 0;
		int m_total_triangles = 0;
		int m_interior_nodes = 0;
		int m_leaf_nodes = 0;

	public:
		Node* m_root;
		int nodeCount;
	};
}
