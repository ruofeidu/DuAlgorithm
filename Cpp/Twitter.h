#pragma once
#include "common.h"

// 355. Design Twitter
/*
  Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

	* postTweet(userId, tweetId): Compose a new tweet.
	* getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
	* follow(followerId, followeeId): Follower follows a followee.
	* unfollow(followerId, followeeId): Follower unfollows a followee.
*/
class Twitter {

private:
	const size_t CACHE_LEN = 10;
	unordered_map<int, unordered_set<int>> m_follow;
	unordered_map<int, deque<pair<size_t, int>>> m_msg;
	size_t m_time;

public:
	/** Initialize your data structure here. */
	Twitter(): m_time(0) {
	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		m_msg[userId].emplace_back(make_pair(++m_time, tweetId));
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		using RIT = deque<pair<size_t, int>>::reverse_iterator;
		priority_queue<tuple<size_t, RIT, RIT>> heap;

		if (!m_msg[userId].empty()) {
			heap.emplace(make_tuple(m_msg[userId].rbegin()->first,
				m_msg[userId].rbegin(),
				m_msg[userId].rend()));
		}
		for (const auto& id : m_follow[userId]) {
			if (m_msg[id].size()) {
				heap.emplace(make_tuple(m_msg[id].rbegin()->first,
					m_msg[id].rbegin(),
					m_msg[id].rend()));
			}
		}
		vector<int> res;
		while (!heap.empty() && res.size() < CACHE_LEN) {
			const auto& top = heap.top();
			size_t t;
			RIT begin, end;
			tie(t, begin, end) = top;
			heap.pop();

			auto next = begin + 1;
			if (next != end) {
				heap.emplace(make_tuple(next->first, next, end));
			}

			res.emplace_back(begin->second);
		}
		return res;
	}

	/** 
	  * Follower follows a followee. If the operation is invalid, it should be a no-op. 
	  */
	void follow(int followerId, int followeeId) {
		if (followerId != followeeId && !m_follow[followerId].count(followeeId)) {
			m_follow[followerId].emplace(followeeId);
		}
	}

	/** 
	  * Follower unfollows a followee. If the operation is invalid, it should be a no-op. 
	  */
	void unfollow(int followerId, int followeeId) {
		if (m_follow[followerId].count(followeeId)) {
			m_follow[followerId].erase(followeeId);
		}
	}
};
