#ifndef __OBJECT_ENEMY_H__
#define __OBJECT_ENEMY_H__

#include <spine/spine-cocos2dx.h>
#include "Default.h"

enum MonsterKind {//1번 근접형1, 2번 원거리형1번, 악령
	Monster1,Monster2, Demon,Demon2
};
typedef enum 
{
	LeftWalk = 50, RightWalk, Standing, CloseAtk, DistanceAtk, Die, Hit, Howling
}EnemyMotion;

enum Monter_DifY
{
	DifY1 =  40, DifY2 = 30, DifY3 = 0
};
#define EnemyEffectNum 9

class ObjectEnemy
{
public:
	////////////공용 달리기 보간 함수/////////
	void MonsterRun()
	{
		if(m_MonsterNum == MonsterKind::Monster1)
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
		else if(m_MonsterNum == MonsterKind::Monster2)
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
	}
	void MonsterIdle()
	{
		if (m_MonsterNum == MonsterKind::Monster1)
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[1])));
		else if (m_MonsterNum == MonsterKind::Monster2)
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[1])));
	}
	////////////////////////////////////////
	Animation *effect[EnemyEffectNum];
	Sprite* m_Rect;//실제 충돌박스 Sprite
	Sprite* m_Spr;
	Sprite* m_Weapon;

	//무기
	Sprite* m_WeaponRect[10];

	Vec2 m_Pos;
	bool m_AddFirst;
	int m_HP;
	bool m_Death;
	int m_CurMotionNum;
	float m_Timer;
	float m_ATimer;
	int m_MonsterNum;
	bool m_HitCheck;
	int m_AttNum[3];
	bool m_AtkCheck;
	void AtkChange()
	{
		m_AtkCheck = false;
	}
	void ChangeHit()
	{
		m_HitCheck = false;
		m_AtkCheck = false;
	}
	// 특수행동처리(ex총알)
	void EnemyUpdate();

	//함수 내부 static대체용
	int AniLoop = 0;
	int randNum = 0;
	int State = 0;
	//////////////////////////////////////
	std::vector<int> m_dir;
	int JumpPower;

	void ReCreateMonster();
	void ChangeDeath();

	//MonsterKind1
	void CreateObject();
	void SetPosObject(float x, float y);

	//MonsterKind2
	Vector<Sprite*>m_bullet;
	void CreateObject2();
	void MakeSpine();
	void MakeBullet();
	void DeleteBullet();
	bool m_Attack;

	void SetMoveDir();
	void MoveCharacter();
	void AnimationSwitch(int num);
	void AttackCheck();
	void EnemyDelete();
	void SetHP(int num);

	//Demon
	void CreateDemon();
	void HowlingSound()
	{
		CSoundManager::getInstance()->playEffect("Sound/MySound/dragon_appear3.mp3", false, 1.0f);
	}
	void MakeLight();
	void DemonDelete();

	//Demon2
	void CreateDemon2();
	void DemonDelete2();

	// 메모리제거

	void Delete();
	//Spine
	spine::SkeletonAnimation* m_spineAni;
	spAtlas* m_atl;

};

#endif 