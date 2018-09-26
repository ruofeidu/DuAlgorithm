#pragma once
#include <iostream>
using namespace std;

class Singleton
{
public:
	static Singleton *GetInstance()
	{
		return m_Instance;
	}

	int GetTest()
	{
		return m_Test;
	}

private:
	Singleton() { 
		m_Test = 10; 
	}
	static Singleton *m_Instance;
	int m_Test;

	// This is important
	class GC
	{
	public:
		~GC()
		{
			// We can destory all the resouce here, eg:db connector, file handle and so on
			if (m_Instance != NULL)
			{
				cout << "Garbage Collection" << endl;
				delete m_Instance;
				m_Instance = NULL;
			}
		}
	};
	static GC gc;
};
