#pragma once
#include "common.h"

namespace CppWired {
	int pointer() {
		int a[5] = { 1, 2, 3, 4, 5 };

		int *ptr = (int*)(&a + 1);
		// the output is 5
		printf("%d\n", *(ptr - 1));

		system("pause");
		return 0;
	}

	/*
	
	int i;main(){for(;i["]<i;++i){--i;}"];read('-'-'-',i+++"hell\
	o, world!\n",'/'/'/'));}read(j,i,p){write(j/p+p,i---j,i/i);}

	*/
}