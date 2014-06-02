#include "Lock.h"

Lock::Lock()
{
	InitializeCriticalSection(&m_cs);
}

Lock::~Lock()
{
	DeleteCriticalSection(&m_cs);
}

void Lock::acquire()
{
	EnterCriticalSection(&m_cs);
}

void Lock::release()
{
	LeaveCriticalSection(&m_cs);
}
