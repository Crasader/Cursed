#pragma once
#include "Default.h"

//// 메모리풀 구조 예상도
//// 로딩씬 진입 -> 로딩씬에서 원하는 객체 갯수만큼 미리 생성 -> 게임씬에서 호출

class MemoryPool : public CSingletonBase<MemoryPool>
{
public:
	MemoryPool();
	~MemoryPool();

	std::list<ObjectEnemy*> m_Enemy1Pool;			//몬스터1
	std::list<ObjectEnemy*> m_Enemy2Pool;			//몬스터2
	std::list<ObjectEnemy*> m_DemonPool;			//악령
	std::list<ObjectEnemy*> m_Demon2Pool;			//악령2
	std::list<MiniEnemy*> m_LadyBugPool;			//무당벌레
	std::list<MiniEnemy*> m_BombBugPool;			//폭탄벌레
	std::list<MiniEnemy*> m_BatPool;				//박쥐벌레
	std::list<MiniEnemy*> m_Colony;				//콜로니
	
	std::list<BulletClass*> m_BulletPool;			//총알 클래스
	std::vector<ObjectItem*> m_ItemPool;			//아이템 클래스

	std::vector<ObjectBarrier*> m_BarrierPool;		//장애물 클래스

	BulletClass* PoP();
	//std::vector<Object
};

