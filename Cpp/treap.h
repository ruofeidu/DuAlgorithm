#pragma once
#include "common.h"

/// <summary>
/// The treap and the randomized binary search tree are two closely related forms of binary search tree data structures that maintain a dynamic set of ordered keys and allow binary searches among the keys. 
/// http://blog.ruofeidu.com/treap-in-45-lines-of-c/
/// </summary>
template <class T>
class Treap {
public:
	static const int MOD_MAX = numeric_limits<int>::max();
	class Node {
	public:
		T x;
		int y, c;
		Node *l, *r;
		Node(int data = 0) :x(data), c(0), l(0), r(0) {
			y = ((rand() << 15) + rand()) % MOD_MAX;
		}
	};
	Node *root, *dummy;
public:
	Treap() {
		dummy = new Node();
		dummy->l = dummy->r = dummy;
		dummy->y = INT_MAX;
		root = dummy;
	}
	void update(Node*&p) {
		if (p != dummy) {
			p->c = p->l->c + p->r->c + 1;
		}
	}
	// left rotate
	void lr(Node *&p) {
		Node *q = p->l;
		p->l = q->r;
		q->r = p;
		update(p);
		update(q);
		p = q;
	}
	// right rotate
	void rr(Node *&p) {
		Node *q = p->r;
		p->r = q->l;
		q->l = p;
		update(p);
		update(q);
		p = q;
	}
	void ins(Node *&p, int x) {
		if (p == dummy) {
			p = new Node(x);
			p->l = p->r = dummy;
			p->c = 1;
		}
		else
		if (x < p->x) {
			ins(p->l, x);
			if (p->l->y < p->y)
				lr(p);
		}
		else
		{
			ins(p->r, x);
			if (p->r->y < p->y)
				rr(p);
		}
		update(p);
	}
	void del(Node *&p, int x) {
		if (p == dummy) return;
		if (p->x == x) del(p); else
			if (x < p->x) del(p->l, x); else del(p->r, x);
		if (p != dummy) update(p);
	}
	void del(Node *&p) {
		if (p->l == dummy && p->r == dummy) {
			delete p;
			p = dummy;
			return;
		}
		if (p->l->y < p->r->y) {
			lr(p);
			del(p->r);
		}
		else { rr(p); del(p->l); }
		update(p);
	}

	bool find(Node *&p, int x) {
		if (p == dummy) return false;
		if (x == p->x) return true;
		return (x < p->x) ? find(p->l, x) : find(p->r, x);
	}

	int kth(Node *&p, int k) {
		if (k <= p->l->c) return kth(p->l, k); else
			return (k == p->l->c + 1) ? p->x : kth(p->r, k - p->l->c - 1);
	}

	void ins(int x) {
		ins(root, x);
	}
	void del(int x) {
		del(root, x);
	}
	bool find(int x) {
		return find(root, x);
	}
	int kth(int k) {
		return (k >= 1 && k <= root->c) ? kth(root, k) : -1;
	}
};