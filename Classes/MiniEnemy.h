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
	// �ִϸ��̼� �� �̹���
	Animation* effect[MiniEffectNum];
	Sprite* m_Rect; // ���� �浹�ڽ�
	Sprite* m_Spr;
	bool m_AddFirst;//���̾� �߰� 1ȸ üũ
	int m_CurMotion;

	void AnimationSwitch(int num);

	// ���� ����
	int m_MonsterNum;
	int m_HP;
	bool m_Death;
	std::vector<int> m_dir;

	// �Լ�
	void Delete();
	void MiniUpdate();
	void SetPosObject(float x, float y);

	// �ݷδ� ���뺯�� �� �Լ�
	void CreateColony();
	void SetColony(bool flip, float Angle);

	// ������� ���뺯�� �� �Լ�
	bool m_RunAct;
	bool m_RunAct2;
	bool m_Boom;
	Vec2 m_TargetPos;			//��ǥ�� ��ġ
	Vec2 m_SavePos;				//�� ��ġ
	bool m_OnGround;			//���� ����üũ
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
	void ColideCheck();			//���ΰ��� �浹üũ

	// ��ź���� ���뺯�� �� �Լ�
	void CreateBombbug();
	void BombBugRotate(Sprite* sender, float delay);
	void Recreate();

	// ���� ���뺯�� �� �Լ�
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