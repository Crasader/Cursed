#ifndef __MINI_ENEMY_H__
#define __MINI_ENEMY_H__

#include "Default.h"

#define MiniEffectNum 7

enum MiniMonster {
	Ladybug, Bombbug, Batbug, Colony
};

typedef enum
{
	Run, MiniHit, MiniDeath
}MiniMotion;

enum Mini_DifY
{
	LadyDifY = 15, BobmDifY, BatDifY
};
class MiniEnemy
{
public:
	// 애니메이션 및 이미지
	Animation* effect[MiniEffectNum];
	Sprite* m_Rect; // 실제 충돌박스
	Sprite* m_Spr;
	bool m_AddFirst;//레이어 추가 1회 체크
	int m_CurMotion;

	void AnimationSwitch(int num);

	// 몬스터 정보
	int m_MonsterNum;
	int m_HP;
	bool m_Death;
	std::vector<int> m_dir;

	// 함수
	void Delete();
	void MiniUpdate();
	void SetPosObject(float x, float y);

	// 콜로니 전용변수 및 함수
	void CreateColony();
	void SetColony(bool flip, float Angle);

	// 무당벌레 전용변수 및 함수
	bool m_RunAct;
	bool m_RunAct2;
	bool m_Boom;
	Vec2 m_TargetPos;			//목표물 위치
	Vec2 m_SavePos;				//젠 위치
	bool m_OnGround;			//지면 도달체크
	void ChangeState()
	{
		m_RunAct = true;
		m_RunAct2 = true;
	}
	void ChangeBoom()
	{
		m_Boom = true;
	}
	void CreateLadybug();
	void LadyBugUpdate();
	void ColideCheck();			//주인공과 충돌체크

	// 폭탄벌레 전용변수 및 함수
	void CreateBombbug();
	void BombBugRotate(Sprite* sender, float delay);
	void Recreate();

	// 박쥐 전용변수 및 함수
	bool m_Hit;
	void CreateBat();
	void MoveBat(Sprite* sender, float delay);
	void BackMove()
	{
		m_CurMotion = NULL;
		m_Hit = false;
		MoveBat(m_Spr, 0);
	}
};
#endif