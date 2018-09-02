#pragma once
#include "common.h"

class TrieNode {
public:
	TrieNode *child[26];
	bool isWord;
	TrieNode() : isWord(false) {
		for (auto &a : child)
			a = nullptr;
	}
};

class Trie {
public:
	Trie() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string s) {
		TrieNode *p = root;
		for (auto &a : s) {
			int i = a - 'a';
			if (!p->child[i]) p->child[i] = new TrieNode();
			p = p->child[i];
		}
		p->isWord = true;
	}

	// Returns if the word is in the trie.
	bool search(string key) {
		TrieNode *p = root;
		for (auto &a : key) {
			int i = a - 'a';
			if (!p->child[i]) return false;
			p = p->child[i];
		}
		return p->isWord;
	}

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		TrieNode *p = root;
		for (auto &a : prefix) {
			int i = a - 'a';
			if (!p->child[i]) return false;
			p = p->child[i];
		}
		return true;
	}

private:
	TrieNode* root;
};
