#include "Default.h"

BulletManager* m_BulletManager = new BulletManager;

void BulletManager::GetLayer(Layer * layer)
{
	m_layer = layer;
}

void BulletManager::AddBullet()
{
	std::list<BulletClass*> *m_list = &MemoryPool::getInstance()->m_BulletPool;
	std::list<BulletClass*>::iterator iter = m_list->begin();

	/*BulletClass* bul = *iter;
	bul->SetBullet();
	m_list->remove(*m_list->begin());*/

	for (int i = 0; i < 20; ++i)
	{
		BulletClass* bul = *iter;
		bul->SetBullet();
		iter++;
	}
	for (int i = 0; i < 20; ++i)
		m_list->remove(*m_list->begin());
}
