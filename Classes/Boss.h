#ifndef __BOSS_H__
#define __BOSS_H__

#include "Default.h"

enum BossKind {
	EliteBoss, Boss1, Boss2
};

enum BossMotion {
	BossIdle, BossHit, BossMoveLeft, BossMoveRight, BossAttack1, BossAttack2, BossAttack3, BossAttack4, BossAttack5,
	BossDeath, BossHowling, BossSkill, BossAttack6
};

enum Boss_DifY{
	EliteY1 = 40, Boss1Y1 = 40
};

struct Bullet {
	Sprite* Rect;
	Sprite* Spr;
};
#define BossEffectNum 10
#define PI 3.14159265358979

class Boss
{
public:
	int m_BossNum;
	Sprite* m_Rect;
	Sprite* m_Spr;
	Sprite* m_MoveRect;
	Sprite* m_WeaponRect[3];
	Sprite* m_HPBack;
	Sprite* m_HPBar;
	int m_HP;
	int randNum;
	int m_LastMotion;
	int m_Att[3];
	bool m_Death;
	bool m_HitCheck;
	bool m_Run;
	bool m_CanMove;
	bool m_Attack;
	bool m_Lock;
	float m_Timer;
	std::vector<int> m_dir;
	Animation* effect[BossEffectNum];
	int State;
	int m_CurMotion;

	void AnimationSwitch(int num);
	void MoveBoss();
	void SetMoveDir();
	void BossUpdate();
	void BossDeath();
	void BossHit();
	void BossDelete();

	//파이널 보스
	bool m_CurseOn;
	Sprite* m_Curse;
	Sprite* m_BulletRect;
	Vec2 m_SavePos[5];
	void HeroCurse()
	{
		m_Curse->runAction(Sequence::create(Show::create(),
			Spawn::create(
				Repeat::create(Animate::create(effect[9]),5),
			DelayTime::create(3.0f),NULL),Hide::create(),
			CallFunc::create(CC_CALLBACK_0(Boss::CurseChange,this)),
			NULL));
	}
	void CurseChange()
	{
		m_CurseOn = false;
	}
	//Attack1
	Sprite* m_GreenSample;
	std::vector<Bullet*> m_GreenL;
	void MakeAttack1Bullet();
	void MakeGreenBullet(Vec2,float);
	//Attack2
	Sprite* m_RedSample;
	std::vector<Bullet*> m_RedL;
	void MakeAttack2Bullet();
	void MakeRedBullet(Vec2);
	//Attack3
	Sprite* m_BlackSample;
	std::vector<Bullet*> m_BlackL;
	void MakeAttack3Bullet();
	//Attack4
	Sprite* m_PosionRect;
	Sprite* m_FogSample;
	std::vector<Bullet*> m_PoisonL;
	void MakeAttack4();
	void PoisonInit();
	//Attack5
	Bullet* m_Fire;
	void MakeAttack5();
	//Attacd6
	Sprite* m_Laser;
	Sprite* m_LaserRect[2];
	void MakeAttack6();

	void CreateBoss2(Vec2 pos);
	void BoosAttack1()
	{
		m_Attack = false;
		State = 999;
	}
	// 스테이지1 보스몹
	Sprite* m_Skill1Stone[20];
	Sprite* m_Skill1Rect[20];
	Sprite* m_Skill2Stone[20];
	Sprite* m_Skill2Rect[20];
	bool m_Skill5On;
	bool m_Patern;
	bool m_Random;
	void CreateStage1Boss(Vec2 pos, Layer* lay);
	void Skill3On();
	void Skill3Off();
	void Skill1On();
	void Skill2On();
	void Skill5On()
	{
		m_Skill5On = true;
	}
	void PaternExit()
	{
		m_Patern = false;
		ElietAttack2();
	}
	void CurAct2()
	{
		m_CurMotion = BossMotion::BossAttack2;
		RUN_WITH_DELAY(1.15f, CC_CALLBACK_0(Boss::Skill2On, this));
	}
	void CurAct3()
	{
		m_CurMotion = BossMotion::BossAttack3;
		RUN_WITH_DELAY(0.8f, CC_CALLBACK_0(Boss::Skill3On, this));
	}
	void BossAttack1Sound()
	{
		CSoundManager::getInstance()->playEffect("Monster/Boss1/FrontAttack.mp3", false, 1.0f);
	}
	void BossAttack2Sound()
	{
		CSoundManager::getInstance()->playEffect("Monster/Boss1/backattack.mp3", false, 1.0f);
	}
	void BossAttack3Sound()
	{
		CSoundManager::getInstance()->playEffect("Monster/Boss1/BlowAttack.mp3", false, 1.0f);
	}
	void BossAttack4Sound()
	{
		CSoundManager::getInstance()->playEffect("Monster/Boss1/HornAttack.mp3", false, 1.0f);
	}
	// 엘리트 보스몹
	void CreateElite(Vec2 pos);
	void EliteSkill();
	void EliteKeepRun()
	{
		if (State == BossMotion::BossMoveLeft || State == BossMotion::BossMoveRight)
		{
			m_Run = true;
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[1]),
				CallFunc::create(CC_CALLBACK_0(Boss::EliteKeepRun, this)),
				NULL));
			m_Rect->stopAllActions();
			if (m_CanMove)
			{
				float speed = State == BossMotion::BossMoveLeft ? -180 : 180;
				m_Rect->runAction(Sequence::create(
					MoveTo::create(1.0f, Vec2(m_Rect->getPositionX() + speed, m_Rect->getPositionY())),
					NULL));
			}
		}
		else
		{
			State = 999;
			m_Run = false;
			m_Spr->stopAllActions();
			m_Rect->stopAllActions();
		}
	}
	void ElietAttack2()
	{
		m_Attack = false;
		State = 999;
	}
	void EliteUnLock()
	{
		m_Lock = false;
	}
	void EliteHowlingSound()
	{
		CSoundManager::getInstance()->playEffect("Monster/Elite/elite_growling.mp3", false, 1.0f);
	}
	void EliteClawSound()
	{
		CSoundManager::getInstance()->playEffect("Monster/Elite/elite_claw.mp3", false, 1.0f);
	}
	void EliteSkillSound()
	{
		CSoundManager::getInstance()->playEffect("Monster/Elite/elite_skill.mp3", false, 1.0f);
	}

};
#endif