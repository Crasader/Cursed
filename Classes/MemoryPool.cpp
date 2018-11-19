#include "Default.h"

MemoryPool::MemoryPool()
{
}

MemoryPool::~MemoryPool()
{
}

BulletClass* MemoryPool::PoP()
{
	return *m_BulletPool.begin();
}
