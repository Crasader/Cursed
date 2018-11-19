#pragma once
#include "Default.h"

//// �޸�Ǯ ���� ����
//// �ε��� ���� -> �ε������� ���ϴ� ��ü ������ŭ �̸� ���� -> ���Ӿ����� ȣ��

class MemoryPool : public CSingletonBase<MemoryPool>
{
public:
	MemoryPool();
	~MemoryPool();

	std::list<ObjectEnemy*> m_Enemy1Pool;			//����1
	std::list<ObjectEnemy*> m_Enemy2Pool;			//����2
	std::list<ObjectEnemy*> m_DemonPool;			//�Ƿ�
	std::list<ObjectEnemy*> m_Demon2Pool;			//�Ƿ�2
	std::list<MiniEnemy*> m_LadyBugPool;			//�������
	std::list<MiniEnemy*> m_BombBugPool;			//��ź����
	std::list<MiniEnemy*> m_BatPool;				//�������
	std::list<MiniEnemy*> m_Colony;				//�ݷδ�
	
	std::list<BulletClass*> m_BulletPool;			//�Ѿ� Ŭ����
	std::vector<ObjectItem*> m_ItemPool;			//������ Ŭ����

	std::vector<ObjectBarrier*> m_BarrierPool;		//��ֹ� Ŭ����

	BulletClass* PoP();
	//std::vector<Object
};

