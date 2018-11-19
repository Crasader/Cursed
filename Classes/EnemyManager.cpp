#include "Default.h"

EnemyManager* m_EnemyManager = new EnemyManager;

void EnemyManager::GetLayer(Layer * layer)
{
	m_layer = layer;
}

void EnemyManager::GetSource(SourceManager* Source)
{
	m_Source = Source;
}

void EnemyManager::Update()
{
	// 보스 업데이트
	std::list<Boss*>::iterator iter3 = m_Boss.begin();
	for (iter3; iter3 != m_Boss.end(); ++iter3)
	{
		if ((*iter3)->m_Death == false)
		{
			(*iter3)->SetMoveDir();
			(*iter3)->MoveBoss();
			(*iter3)->BossUpdate();
		}
	}

	std::vector<ObjectEnemy*>::iterator iter = m_List.begin();
	for (iter; iter != m_List.end(); ++iter)
	{
		if ((*iter)->m_Death)
		{
			(*iter)->AnimationSwitch(EnemyMotion::Die);
			m_List.erase(iter);
			return;
		}
		else
		{
			(*iter)->SetMoveDir();
			(*iter)->MoveCharacter();
			(*iter)->EnemyUpdate();//적 총알 이동
		}
	}

	// 무당벌레, 거미
	std::list<MiniEnemy*>::iterator iter2 = m_MiniList.begin();
	for (iter2; iter2 != m_MiniList.end(); ++iter2)
	{
		(*iter2)->MiniUpdate();
	}
	
	iter2 = m_ColideMini.begin();
	for (iter2; iter2 != m_ColideMini.end(); ++iter2)
	{
		(*iter2)->MiniUpdate();
	}

}
