#pragma once
#include "common.h"
class NQueens {
	vector<vector<string>> NQresult;
	vector<int> NQpath;
	int NQtotal;
	int NQn;

	vector<vector<string>> solveNQueens(int n)
	{
		NQresult.clear();
		NQpath.clear();
		NQn = n;
		NQtotal = 0;
		bitNQueens(0, 0, 0);
		cout << NQtotal << endl;
		return NQresult;
	}	
	
	// col: whether this col is occupied
	// ld: left diagnal for the current row
	// rd: right diagnal for the current row
	void bitNQueensSimple(int col, int ld, int rd) {
		int allOccupied = (1 << NQn) - 1;
		if (col == allOccupied) {
			++NQtotal;
			return;
		}
		int pos = allOccupied & (~(col | ld | rd));
		while (pos != 0) {
			int p = pos & (-pos);		// which way to go
			pos = pos - p;					// get the rightmost 1 of position position
			bitNQueensSimple(col + p, (ld + p) << 1, (rd + p) >> 1);
		}
	}

	void addNQueenSolution() {
		vector<string> v; 
		for (int i = 0; i < NQn; ++i)
			v.emplace_back(string(NQn, '.'));
		for (int i = 0; i < NQn; ++i) {
			v[i][NQpath[i]] = 'Q';
			//cout << v[i] << endl; 
		}
		//cout << endl; 
		NQresult.emplace_back(v);
	}

	// col: whether this col is occupied
	// ld: left diagnal for the current row
	// rd: right diagnal for the current row
	void bitNQueens(int col, int ld, int rd) {
		int allOccupied = (1 << NQn) - 1;
		if (col == allOccupied) {
			++NQtotal;
			addNQueenSolution();
			return;
		}
		int pos = allOccupied & (~(col | ld | rd));
		while (pos != 0) {
			int p = pos & (-pos);		// which way to go
			pos = pos - p;					// get the rightmost 1 of position position
			NQpath.emplace_back(p == 1 ? 0 : (int)round(log(p) / log(2)));
			bitNQueens(col + p, (ld + p) << 1, (rd + p) >> 1);
			NQpath.pop_back();
		}
	}

	int totalNQueens(int n) {
		NQresult.clear();
		NQn = n;
		NQtotal = 0;
		bitNQueensSimple(0, 0, 0);
		return NQtotal;
	}

};