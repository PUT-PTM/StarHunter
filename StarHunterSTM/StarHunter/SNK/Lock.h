#pragma once

#include <Windows.h>

class Lock
{
public:
	Lock();
	~Lock();

	void acquire();
	void release();
private:

	CRITICAL_SECTION m_cs;
};