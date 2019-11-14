#pragma once
#include "common.h"

// 460. LFU Cache
// Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.
/*
	Example:
	LFUCache cache = new LFUCache( 2 );

	cache.put(1, 1);
	cache.put(2, 2);
	cache.get(1);       // returns 1
	cache.put(3, 3);    // evicts key 2
	cache.get(2);       // returns -1 (not found)
	cache.get(3);       // returns 3.
	cache.put(4, 4);    // evicts key 1.
	cache.get(1);       // returns -1 (not found)
	cache.get(3);       // returns 3
	cache.get(4);       // returns 4
*/
class LFUCache {
private:
	enum Data { KEY, VAL, FREQ };
	int m_capacity;
	int m_size;
	int m_min_freq;
	unordered_map<int, list<tuple<int, int, int>>> m_freq_to_nodes;            // freq to list of {key, val, freq}
	unordered_map<int, list<tuple<int, int, int>>::iterator> m_key_to_nodeit;  // key to list iterator
public:
	LFUCache(int m_capacity) : m_capacity(m_capacity), m_size(0), m_min_freq(0) {
	}

	int get(int key) {
		if (!m_key_to_nodeit.count(key)) {
			return -1;
		}

		auto new_node = *m_key_to_nodeit[key];
		auto& freq = std::get<FREQ>(new_node);
		m_freq_to_nodes[freq].erase(m_key_to_nodeit[key]);
		if (m_freq_to_nodes[freq].empty()) {
			m_freq_to_nodes.erase(freq);
			if (m_min_freq == freq) {
				++m_min_freq;
			}
		}
		++freq;
		m_freq_to_nodes[freq].emplace_back(move(new_node));
		m_key_to_nodeit[key] = prev(m_freq_to_nodes[freq].end());

		return std::get<VAL>(*m_key_to_nodeit[key]);
	}

	void put(int key, int value) {
		if (m_capacity <= 0) {
			return;
		}

		if (get(key) != -1) {
			std::get<VAL>(*m_key_to_nodeit[key]) = value;
			return;
		}

		if (m_size == m_capacity) {
			m_key_to_nodeit.erase(std::get<KEY>(m_freq_to_nodes[m_min_freq].front()));
			m_freq_to_nodes[m_min_freq].pop_front();
			if (m_freq_to_nodes[m_min_freq].empty()) {
				m_freq_to_nodes.erase(m_min_freq);
			}
			--m_size;
		}

		m_min_freq = 1;
		m_freq_to_nodes[m_min_freq].emplace_back(key, value, m_min_freq);
		m_key_to_nodeit[key] = prev(m_freq_to_nodes[m_min_freq].end());
		++m_size;
	}
};

/**
* Your LFUCache object will be instantiated and called as such:
* LFUCache obj = new LFUCache(capacity);
* int param_1 = obj.get(key);
* obj.put(key,value);
*/
