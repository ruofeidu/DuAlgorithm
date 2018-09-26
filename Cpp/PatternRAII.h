#pragma once
#include <iostream>
#include <windows.h>
#include <process.h>

using namespace std;
static int gGlobal = 0;
CRITICAL_SECTION cs;
//Resource Acquisition Is Initialization
class MyLock
{
public:
	MyLock()
	{
		EnterCriticalSection(&cs);
	}

	~MyLock()
	{
		LeaveCriticalSection(&cs);
	}

private:
	//MyLock(const MyLock &);
	MyLock operator =(const MyLock &);
};

void DoComplex(MyLock lock)
{
}

unsigned int __stdcall ThreadFun(PVOID pv)
{
	MyLock lock;
	int *para = (int *)pv;

	// I need the lock to do some complex thing
	DoComplex(lock);

	for (int i = 0; i < 10; ++i)
	{
		++gGlobal;
		cout << "Thread " << *para << endl;
		cout << gGlobal << endl;
	}
	return 0;
}
