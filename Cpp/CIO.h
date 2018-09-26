#pragma once
#include "common.h"

namespace FileIO {
	void c_io() {
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);

		FILE * pFile;
		char buffer[] = { 'x' , 'y' , 'z' };
		pFile = fopen("myfile.bin", "wb");
		fwrite(buffer, sizeof(char), sizeof(buffer), pFile);
		fclose(pFile);

		int zoffset_[100];
		auto count = fread(&zoffset_, sizeof(decltype(zoffset_)), 1, pFile);
	}
}
