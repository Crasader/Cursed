#include "Default.h"
extern EnemyManager* m_EnemyManager;
extern bool Boss2Clear;

void Boss::CreateBoss2(Vec2 pos)
{
	m_BossNum = BossKind::Boss2;

	m_Rect = Sprite::create("Monster/Boss2/Rect.png");
	m_Rect->setPosition(Vec2(pos.x, pos.y));
	m_Rect->setVisible(ColiideRect);
	m_EnemyManager->m_layer->addChild(m_Rect, 8);
	m_SavePos[0] = m_Rect->getPosition();
	m_SavePos[1] = Vec2(200, pos.y);
	m_SavePos[2] = Vec2(960, pos.y);

	m_Spr = Sprite::create("Monster/Boss2/Idle/Idle (1).png");
	m_Spr->setPosition(Vec2(pos.x, pos.y));
	//if(Stage2_3Boss)
		m_Spr->setOpacity(0);
	m_EnemyManager->m_layer->addChild(m_Spr, 7);

	m_GreenSample = Sprite::create("Monster/Boss2/Bullet/Green/Bullet (1).png");
	m_GreenSample->setPosition(Vec2(-500, -500));
	m_GreenSample->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_GreenSample);

	m_RedSample = Sprite::create("Monster/Boss2/Bullet/Red/Bullet (1).png");
	m_RedSample->setPosition(Vec2(-500, -500));
	m_RedSample->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_RedSample);

	m_BlackSample = Sprite::create("Monster/Boss2/Bullet/Black/Bullet (1).png");
	m_BlackSample->setPosition(Vec2(-500, -500));
	m_BlackSample->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_BlackSample);

	m_FogSample = Sprite::create("Monster/Boss2/Effect/Poison/Poison (1).png");
	m_FogSample->setPosition(Vec2(-500, -500));
	m_FogSample->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_FogSample);

	m_PosionRect = Sprite::create("Monster/Boss2/Effect/Poison/PoisonRect.png");
	m_PosionRect->setPosition(Vec2(-500, -500));
	m_PosionRect->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_PosionRect);

	m_BulletRect = Sprite::create("Monster/Boss2/Bullet/BulletRect.png");
	m_BulletRect->setPosition(Vec2(-500, 500));
	m_BulletRect->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_BulletRect);

	m_Fire = new Bullet();
	m_Fire->Spr = Sprite::create("Monster/Boss2/Effect/Fire/Fire (1).png");
	m_Fire->Spr->setAnchorPoint(Vec2(0, 0));
	m_Fire->Spr->setPosition(Vec2(0, 0));
	m_Fire->Spr->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_Fire->Spr,11);

	m_Fire->Rect = Sprite::create("Monster/Boss2/Effect/Fire/FireRect.png");
	m_Fire->Rect->setAnchorPoint(Vec2(0, 0));
	m_Fire->Rect->setPosition(Vec2(0, -800));
	m_Fire->Rect->setVisible(ColiideRect);
	m_EnemyManager->m_layer->addChild(m_Fire->Rect);

	m_Laser = Sprite::create("Monster/Boss2/Effect/Laser/Laser (1).png");
	m_Laser->setAnchorPoint(Vec2(0, 0.5f));
	m_Laser->setScale(1.2f);
	m_Laser->setPosition(Vec2(-120, pos.y));
	m_Laser->setVisible(false);
	m_EnemyManager->m_layer->addChild(m_Laser,3);

	m_LaserRect[0] = Sprite::create("Monster/Boss2/Effect/Laser/LaserRect1.png");
	m_LaserRect[0]->setPosition(m_SavePos[2]);
	m_LaserRect[0]->setVisible(ColiideRect);
	m_EnemyManager->m_layer->addChild(m_LaserRect[0],4);

	m_LaserRect[1] = Sprite::create("Monster/Boss2/Effect/Laser/LaserRect2.png");
	m_LaserRect[1]->setPosition(m_SavePos[2]);
	m_LaserRect[1]->setVisible(ColiideRect);
	m_EnemyManager->m_layer->addChild(m_LaserRect[1], 4);

	m_Curse = Sprite::create("Effect/Lock/Lock1.png");
	m_Curse->setPosition(Vec2(-500, -500));
	m_Curse->setVisible(false);
	m_Curse->setScale(0.4f);
	m_EnemyManager->m_layer->addChild(m_Curse, 3);

	State = 999;
	m_LastMotion = 999;
	m_CurseOn = false;
	m_Skill5On = false;
	m_Patern = false;
	m_Random = false;
	m_CanMove = true;
	m_Death = false;
	m_HitCheck = false;
	m_Run = false;
	m_Attack = false;
	m_Lock = false;
	m_HP = 450;//150
	m_Timer = 0.0f;
	randNum = 0;
	m_CurMotion = 999;

	char str[100] = { 0 };

	for (int i = 0; i < BossEffectNum; ++i)
	{
		effect[i] = Animation::create();
		if (i == 0)// Idle
			effect[i]->setDelayPerUnit(0.05f);
		else if (i == 1)// Attack1
			effect[i]->setDelayPerUnit(0.05f);
		else if (i == 2)// Attack2
			effect[i]->setDelayPerUnit(0.05f);
		else if (i == 3)// Dead
			effect[i]->setDelayPerUnit(0.05f);
		else if (i == 4 || i == 5 || i == 6)// Green, Red, Black
			effect[i]->setDelayPerUnit(0.05f);
		else if(i==7)//Fire
			effect[i]->setDelayPerUnit(0.1f);
		else if (i == 8)//Laser
			effect[i]->setDelayPerUnit(0.1f);
		else if(i == 9)
			effect[i]->setDelayPerUnit(0.1f);
	}

	for (int i = 1; i <= 20; ++i)// Idle
	{
		sprintf(str, "Monster/Boss2/Idle/Idle (%d).png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}

	for (int i = 1; i <= 78; ++i)// Attack1
	{
		sprintf(str, "Monster/Boss2/Attack1/Attack1 (%d).png", i);
		effect[1]->addSpriteFrameWithFileName(str);
	}

	for (int i = 1; i <= 78; ++i)// Attack2
	{
		sprintf(str, "Monster/Boss2/Attack2/Attack2 (%d).png", i);
		effect[2]->addSpriteFrameWithFileName(str);
	}

	for (int i = 1; i <= 49; ++i)// Dead
	{
		sprintf(str, "Monster/Boss2/Dead/Dead (%d).png", i);
		effect[3]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 7; ++i)// Green
	{
		sprintf(str, "Monster/Boss2/Bullet/Green/Bullet (%d).png", i);
		effect[4]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 7; ++i)// Red
	{
		sprintf(str, "Monster/Boss2/Bullet/Red/Bullet (%d).png", i);
		effect[5]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 7; ++i)// Black
	{
		sprintf(str, "Monster/Boss2/Bullet/Black/Bullet (%d).png", i);
		effect[6]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 30; ++i)// Fire
	{
		sprintf(str, "Monster/Boss2/Effect/Fire/Fire (%d).png", i);
		effect[7]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 23; ++i)// Laser
	{
		sprintf(str, "Monster/Boss2/Effect/Laser/Laser (%d).png", i);
		effect[8]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 4; ++i)// 
	{
		sprintf(str, "Effect/Lock/Lock%d.png", i);
		effect[9]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i < BossEffectNum; i++)
		CC_SAFE_RETAIN(effect[i]);

	m_EnemyManager->m_Boss.push_back(this);
}

void Boss::CreateStage1Boss(Vec2 pos, Layer* lay)
{
	m_BossNum = BossKind::Boss1;

	m_Rect = Sprite::create("Monster/Boss1/Boss1Rect.png");
	m_Rect->setPosition(Vec2(pos.x, pos.y));
	m_Rect->setVisible(ColiideRect);
	m_EnemyManager->m_layer->addChild(m_Rect, 6);

	m_Spr = Sprite::create("Monster/Boss1/Idle/Idle (1).png");
	m_Spr->setPosition(Vec2(pos.x + 20, pos.y + 60));
	m_EnemyManager->m_layer->addChild(m_Spr, 7);

	m_WeaponRect[0] = Sprite::create("Monster/Boss1/AttackRect.png");
	m_WeaponRect[0]->setPosition(Vec2(m_Rect->getPositionX() - 210
		, m_Rect->getPositionY()));
	m_WeaponRect[0]->setVisible(ColiideRect);
	m_EnemyManager->m_layer->addChild(m_WeaponRect[0], 6);

	// 스킬1 돌 생성
	for (int i = 0; i < 17; ++i)
	{
		if (i == 0)
			m_Skill1Stone[i] = Sprite::create("Monster/Boss1/Skill1/Skill1 (1).png");
		else
			m_Skill1Stone[i] = Sprite::createWithSpriteFrame(m_Skill1Stone[0]->getSpriteFrame());
		m_Skill1Stone[i]->setPosition(Vec2(15360 + i * 80, 750));
		m_Skill1Stone[i]->setVisible(false);
		m_EnemyManager->m_layer->addChild(m_Skill1Stone[i], 0);
	}

	for (int i = 0; i < 17; ++i)
	{
		if (i == 0)
			m_Skill1Rect[i] = Sprite::create("Monster/Boss1/Skill1/Skill1Rect.png");
		else
			m_Skill1Rect[i] = Sprite::createWithSpriteFrame(m_Skill1Rect[0]->getSpriteFrame());
		m_Skill1Rect[i]->setPosition(Vec2(15360 + i * 80, 500));
		m_Skill1Rect[i]->setVisible(ColiideRect);
		m_EnemyManager->m_layer->addChild(m_Skill1Rect[i], 1);
	}

	// 스킬2 돌 추락
	for (int i = 0; i < 17; ++i)
	{
		if (i == 0)
			m_Skill2Stone[i] = Sprite::create("Monster/Boss1/Skill2/Skill2 (1).png");
		else
			m_Skill2Stone[i] = Sprite::createWithSpriteFrame(m_Skill2Stone[0]->getSpriteFrame());
		m_Skill2Stone[i]->setPosition(Vec2(15440 + i * 80, 1650));
		m_Skill2Stone[i]->setVisible(false);
		m_EnemyManager->m_layer->addChild(m_Skill2Stone[i], 0);
	}

	for (int i = 0; i < 17; ++i)
	{
		if (i == 0)
			m_Skill2Rect[i] = Sprite::create("Monster/Boss1/Skill1/Skill1Rect.png");
		else
			m_Skill2Rect[i] = Sprite::createWithSpriteFrame(m_Skill2Rect[0]->getSpriteFrame());
		m_Skill2Rect[i]->setPosition(Vec2(15455 + i * 80, 1650));
		m_Skill2Rect[i]->setVisible(ColiideRect);
		m_Skill2Rect[i]->setOpacity(60);
		m_EnemyManager->m_layer->addChild(m_Skill2Rect[i], 1);
	}
	State = 999;
	m_LastMotion = 999;
	m_Skill5On = false;
	m_Patern = false;
	m_Random = false;
	m_CanMove = true;
	m_Death = false;
	m_HitCheck = false;
	m_Run = false;
	m_Attack = false;
	m_Lock = false;
	m_HP = 250;//250
	m_Timer = 0.0f;
	randNum = 0;
	m_CurMotion = 999;

	char str[100] = { 0 };

	for (int i = 0; i < BossEffectNum; ++i)
	{
		effect[i] = Animation::create();
		if (i == 0)// Idle
			effect[i]->setDelayPerUnit(Boss1IdleDly);
		else if (i == 1)// Attack1
			effect[i]->setDelayPerUnit(Boss1Atk1Dly);
		else if (i == 2)// Attack2
			effect[i]->setDelayPerUnit(Boss1Atk2Dly);
		else if (i == 3)// Attack3
			effect[i]->setDelayPerUnit(Boss1Atk3Dly);
		else if (i == 4)// Attack4
			effect[i]->setDelayPerUnit(Boss1Atk4Dly);
		else if (i == 5)// Attack5
			effect[i]->setDelayPerUnit(Boss1Atk5Dly);
		else if (i == 6)// Howling
			effect[i]->setDelayPerUnit(Boss1HowlingDly);
		else if (i == 7)// Dead
			effect[i]->setDelayPerUnit(Boss1Death);
		else if (i == 8)// 바닥 돌생성
			effect[i]->setDelayPerUnit(Boss1Skill1);
		else if (i == 9)// 천장 돌생성
			effect[i]->setDelayPerUnit(Boss1Skill1);
	}

	for (int i = 1; i <= 48; ++i)// Idle
	{
		sprintf(str, "Monster/Boss1/Idle/Idle (%d).png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 43; ++i)// Attack1
	{
		sprintf(str, "Monster/Boss1/Attack1/Attack1 (%d).png", i);
		effect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 49; ++i)// Attack2
	{
		sprintf(str, "Monster/Boss1/Attack2/Attack2 (%d).png", i);
		effect[2]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 73; ++i)// Attack3
	{
		sprintf(str, "Monster/Boss1/Attack3/Attack3 (%d).png", i);
		effect[3]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 37; ++i)// Attack4
	{
		sprintf(str, "Monster/Boss1/Attack4/Attack4 (%d).png", i);
		effect[4]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 58; ++i)// Attack5
	{
		sprintf(str, "Monster/Boss1/Attack5/Attack5 (%d).png", i);
		effect[5]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 91; ++i)// Howling
	{
		sprintf(str, "Monster/Boss1/Howling/Howling (%d).png", i);
		effect[6]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 61; ++i)// Dead
	{
		sprintf(str, "Monster/Boss1/Dead/Dead (%d).png", i);
		effect[7]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 10; ++i)// Skill1 - 바닥에서 돌생성
	{
		sprintf(str, "Monster/Boss1/Skill1/Skill1 (%d).png", i);
		effect[8]->addSpriteFrameWithFileName(str);
	}
	effect[8]->setRestoreOriginalFrame(true);//애니메이션 종료시 원래 스프라이트로 복귀
	for (int i = 3; i <= 7; ++i)// Skill2 - 천장에서 돌생성
	{
		sprintf(str, "Monster/Boss1/Skill2/Skill2 (%d).png", i);
		effect[9]->addSpriteFrameWithFileName(str);
	}
	effect[9]->setRestoreOriginalFrame(true);//애니메이션 종료시 원래 스프라이트로 복귀

	for (int i = 0; i < BossEffectNum; i++)
		CC_SAFE_RETAIN(effect[i]);

	m_EnemyManager->m_Boss.push_back(this);
}

void Boss::CreateElite(Vec2 pos)
{
	bool static first;
	if (first == false)
	{
		first = true;

		m_BossNum = BossKind::EliteBoss;

		m_Spr = Sprite::create("Monster/Elite/Idle/Idle (1).png");
		m_Spr->setPosition(Vec2(pos.x + 20, pos.y + 100));
		m_Spr->setScale(0.8f);
		m_EnemyManager->m_layer->addChild(m_Spr, 7);

		m_Rect = Sprite::create("Monster/Elite/EliteRect.png");
		m_Rect->setOpacity(100);
		m_Rect->setScale(0.8f);
		m_Rect->setPosition(Vec2(pos.x, pos.y + 100));
		m_Rect->setVisible(ColiideRect);
		m_EnemyManager->m_layer->addChild(m_Rect, 6);

		m_MoveRect = Sprite::create("Monster/Elite/SampleRect.png");
		m_MoveRect->setOpacity(125);
		m_MoveRect->setPosition(m_Rect->getPosition());
		m_MoveRect->setVisible(ColiideRect);
		m_EnemyManager->m_layer->addChild(m_MoveRect, 5);

		m_WeaponRect[0] = Sprite::create("Monster/Elite/WeaponRect1.png");
		m_WeaponRect[0]->setOpacity(125);
		m_WeaponRect[0]->setPosition(Vec2(pos.x, pos.y + 200));
		m_WeaponRect[0]->setVisible(ColiideRect);
		m_EnemyManager->m_layer->addChild(m_WeaponRect[0], 5);

		m_WeaponRect[1] = Sprite::create("Monster/Elite/SkillRect.png");
		m_WeaponRect[1]->setOpacity(120);
		m_WeaponRect[1]->setVisible(ColiideRect);
		m_EnemyManager->m_layer->addChild(m_WeaponRect[1], 5);

		State = 999;
		m_LastMotion = 999;
		m_CanMove = true;
		m_Death = false;
		m_HitCheck = false;
		m_Run = false;
		m_Attack = false;
		m_Lock = Stage1_3Elite ? false : true;
		m_HP = 250;//250
		m_Timer = 0.0f;
		randNum = 0;
		m_CurMotion = 999;

		char str[100] = { 0 };

		for (int i = 0; i < BossEffectNum; ++i)
		{
			effect[i] = Animation::create();
			if (i == 0)// Idle
				effect[i]->setDelayPerUnit(EliteIdleDly);
			else if (i == 1)// Run
				effect[i]->setDelayPerUnit(EliteRunDly);
			else if (i == 2)// Howling
				effect[i]->setDelayPerUnit(EliteHowlingDly);
			else if (i == 3)// Attack2
				effect[i]->setDelayPerUnit(EliteAttack2Dly);
			else if (i == 4)// Attack1
				effect[i]->setDelayPerUnit(EliteAttack1Dly);
			else if (i == 5)// Hit
				effect[i]->setDelayPerUnit(EliteHitDly);
			else if (i == 6)// Attack3
				effect[i]->setDelayPerUnit(EliteAttack3Dly);
			else if (i == 7)// Skill
				effect[i]->setDelayPerUnit(EliteSkillDly);
			else if (i == 8)// Dead
				effect[i]->setDelayPerUnit(EliteDeadDly);
		}

		for (int i = 1; i <= 25; ++i)// Idle
		{
			sprintf(str, "Monster/Elite/Idle/Idle (%d).png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i <= 100; ++i)// Run
		{
			sprintf(str, "Monster/Elite/Run/Elite-Run_%d.png", i);
			effect[1]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i <= 60; ++i)// Howling
		{
			sprintf(str, "Monster/Elite/Howling/Elite-Howling_%d.png", i);
			effect[2]->addSpriteFrameWithFileName(str);
		}

		for (int i = 1; i <= 30; ++i)// Attack2 (원거리 공격)
		{
			sprintf(str, "Monster/Elite/Attack2/Attack2 (%d).png", i);
			if (i == 19)
			{
				Sprite* spr = Sprite::create(str);
				effect[3]->addSpriteFrame(spr->getSpriteFrame());
				m_Att[0] = spr->getSpriteFrame()->getTexture()->getName();
			}
			else
				effect[3]->addSpriteFrameWithFileName(str);
		}

		for (int i = 1; i <= 25; ++i)// Attack1 (근거리 공격)
		{
			sprintf(str, "Monster/Elite/Attack1/Attack1 (%d).png", i);
			if (i == 9)
			{
				Sprite* spr = Sprite::create(str);
				effect[4]->addSpriteFrame(spr->getSpriteFrame());
				m_Att[1] = spr->getSpriteFrame()->getTexture()->getName();
			}
			else
				effect[4]->addSpriteFrameWithFileName(str);
		}


		for (int i = 0; i < 10; ++i)// Hit
		{
			effect[5]->addSpriteFrameWithFileName("Monster/Elite/Hit/Hit.png");
		}

		for (int i = 1; i < 116; ++i)// Dash - Attack3
		{
			sprintf(str, "Monster/Elite/Dash/Rush (%d).png", i);
			effect[6]->addSpriteFrameWithFileName(str);
		}

		for (int i = 1; i <= 19; ++i)// Skill
		{
			sprintf(str, "Monster/Elite/Skill/Skill (%d).png", i);
			effect[7]->addSpriteFrameWithFileName(str);
		}

		for (int i = 1; i <= 49; ++i)// Dead
		{
			sprintf(str, "Monster/Elite/Dead/Dead (%d).png", i);
			effect[8]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < BossEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);

		m_EnemyManager->m_Boss.push_back(this);
	}
	else
	{
		m_Spr->setPosition(Vec2(pos.x + 20, pos.y + 180));
		m_Rect->setPosition(Vec2(pos.x, pos.y + 100));
		m_MoveRect->setPosition(m_Rect->getPosition());
		m_WeaponRect[0]->setPosition(Vec2(pos.x, pos.y + 200));
		State = 999;
		m_LastMotion = 999;
		m_CanMove = true;
		m_Death = false;
		m_HitCheck = false;
		m_Run = false;
		m_Attack = false;
		m_Lock = true;
		m_HP = 250;//250
		m_Timer = 0.0f;
		randNum = 0;
		m_CurMotion = 999;
	}
}

void Boss::AnimationSwitch(int num)
{
	if (m_BossNum == BossKind::EliteBoss)
	{
		if (num == BossMotion::BossIdle)
		{
			if (State != num && m_Run == false)
			{
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->stopAllActions();
				m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
			}
		}
		else if (num == BossMotion::BossMoveLeft || num == BossMotion::BossMoveRight)
		{
			if (State != num)
			{
				m_CurMotion = num;
				m_Run = true;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[1]),
					CallFunc::create(CC_CALLBACK_0(Boss::EliteKeepRun, this)),
					NULL));
				m_Rect->stopAllActions();
				if (m_CanMove)
				{
					float speed = num == BossMotion::BossMoveLeft ? -180 : 180;
					m_Rect->runAction(Sequence::create(
						MoveTo::create(1.0f, Vec2(m_Rect->getPositionX() + speed, m_Rect->getPositionY())),
						NULL));
				}
			}
		}
		else if (num == BossMotion::BossAttack2)// 원거리 공격
		{
			if (State != num && m_Run == false)
			{
				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Spawn::create(Animate::create(effect[3]),
						CallFunc::create(CC_CALLBACK_0(Boss::EliteSkill, this)),
						Sequence::create(DelayTime::create(0.25f),
							CallFunc::create(CC_CALLBACK_0(Boss::EliteSkillSound, this)), NULL),
						NULL),
					CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)),
					NULL));
				m_Rect->stopAllActions();
			}
		}
		else if (num == BossMotion::BossAttack1)// 근거리 공격
		{
			if (State != num && m_Run == false)
			{
				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Spawn::create(Animate::create(effect[4]),
						CallFunc::create(CC_CALLBACK_0(Boss::EliteClawSound, this)),
						NULL),

					CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)),
					NULL));
				m_Rect->stopAllActions();
			}
		}
		else if (num == BossMotion::BossAttack3)// 박치기 공격
		{
			if (State != num && m_Run == false)
			{
				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[6]),
					CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)),
					NULL));
				m_Rect->stopAllActions();
				if (m_CanMove)
				{
					m_Rect->runAction(
						Sequence::create(
							DelayTime::create(1.5f),
							EaseOut::create(MoveTo::create(0.85, Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? 550 : -550), m_Rect->getPositionY())), 2.0f),
							NULL));
				}
			}
		}
		else if (num == BossMotion::BossHowling)// Howling
		{
			if (State != num && m_Lock)
			{
				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					DelayTime::create(1.5f),
					Spawn::create(
						CallFunc::create(CC_CALLBACK_0(Boss::EliteHowlingSound, this)),
						Animate::create(effect[2]), NULL),
					CallFunc::create(CC_CALLBACK_0(Boss::EliteUnLock, this)),
					NULL));
			}
		}
		else if (num == BossMotion::BossDeath)// 보스 사망
		{
			if (State != num)
			{
				ObjectHero::getInstance()->m_EliteClear = true;
				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Spawn::create(
						Animate::create(effect[8]),
						FadeOut::create(1.4f), NULL),
					CallFunc::create(CC_CALLBACK_0(Boss::BossDeath, this)),
					NULL));
				m_Rect->stopAllActions();
				EliteClear = true;
				CSoundManager::getInstance()->playEffect("Monster/Elite/elite_death.mp3", false, 0.8f);
			}
		}
		else if (num == BossMotion::BossHit)// Hit
		{
			if (State != num)
			{
				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[5]),
					NULL));
				m_Rect->stopAllActions();
			}
		}
	}

	else if (m_BossNum == BossKind::Boss1)
	{
		if (num == BossMotion::BossIdle)
		{
			if (State != num)
			{
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->stopAllActions();
				m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
			}
		}
		else if (num == BossMotion::BossAttack1)// 앞발찍기
		{
			if (State != num)
			{
				if (m_Patern == false)
				{
					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[1]),
						CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)), NULL));
					m_Rect->stopAllActions();
					RUN_WITH_DELAY(1.1f, CC_CALLBACK_0(Boss::Skill1On, this));
					m_EnemyManager->m_layer->getParent()->runAction(
						Sequence::create(DelayTime::create(0.8f),
							ActionShake::create(0.5f, 50.0f, 50.0f), NULL));
					RUN_WITH_DELAY(0.5f, CC_CALLBACK_0(Boss::BossAttack1Sound, this));
				}
				else
				{
					RUN_WITH_DELAY(0.5f, CC_CALLBACK_0(Boss::BossAttack1Sound, this));
					int randNum = random(2, 3);
					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					if (randNum == 2)
					{
						m_Spr->runAction(Sequence::create(
							Animate::create(effect[1]), Spawn::create(
								CallFunc::create(CC_CALLBACK_0(Boss::CurAct2, this)),
								Animate::create(effect[2]), NULL),
							CallFunc::create(CC_CALLBACK_0(Boss::PaternExit, this)), NULL));
						m_EnemyManager->m_layer->getParent()->runAction(
							Sequence::create(DelayTime::create(0.8f),
								ActionShake::create(0.5f, 50.0f, 50.0f), NULL));
						RUN_WITH_DELAY(1.3f, CC_CALLBACK_0(Boss::BossAttack2Sound, this));
						RUN_WITH_DELAY(2.1f, CC_CALLBACK_0(Boss::BossAttack2Sound, this));
					}
					else
					{
						m_Spr->runAction(Sequence::create(
							Animate::create(effect[1]), Spawn::create(
								CallFunc::create(CC_CALLBACK_0(Boss::CurAct3, this)),
								Animate::create(effect[3]), NULL),
							CallFunc::create(CC_CALLBACK_0(Boss::PaternExit, this)), NULL));
						m_EnemyManager->m_layer->getParent()->runAction(
							Sequence::create(DelayTime::create(0.8f),
								ActionShake::create(0.5f, 50.0f, 50.0f), NULL));
						RUN_WITH_DELAY(1.3f, CC_CALLBACK_0(Boss::Skill3On, this));
						RUN_WITH_DELAY(2.1f, CC_CALLBACK_0(Boss::BossAttack3Sound, this));
					}
					RUN_WITH_DELAY(1.1f, CC_CALLBACK_0(Boss::Skill1On, this));
					m_Rect->stopAllActions();
				}
			}
		}
		else if (num == BossMotion::BossAttack2)// 뒷발차기
		{
			if (State != num)
			{
				if (m_Patern == false)
				{
					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[2]),
						CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)),
						NULL));
					m_Rect->stopAllActions();
					RUN_WITH_DELAY(1.15f, CC_CALLBACK_0(Boss::Skill2On, this));
					RUN_WITH_DELAY(0.7f, CC_CALLBACK_0(Boss::BossAttack2Sound, this));
				}
				else
				{
					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[2]),
						Spawn::create(
							CallFunc::create(CC_CALLBACK_0(Boss::CurAct3, this)),
							Animate::create(effect[3]), NULL),
						CallFunc::create(CC_CALLBACK_0(Boss::PaternExit, this)),
						NULL));
					m_Rect->stopAllActions();
					RUN_WITH_DELAY(1.15f, CC_CALLBACK_0(Boss::Skill2On, this));
					RUN_WITH_DELAY(0.7f, CC_CALLBACK_0(Boss::BossAttack2Sound, this));
					RUN_WITH_DELAY(2.0f, CC_CALLBACK_0(Boss::BossAttack3Sound, this));
				}
			}
		}
		else if (num == BossMotion::BossAttack3)// 콧바람공격
		{
			if (State != num)
			{
				CSoundManager::getInstance()->playEffect("Monster/Boss1/BlowAttack.mp3", false, 1.0f);

				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[3]),
					CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)),
					NULL));
				m_Rect->stopAllActions();
				RUN_WITH_DELAY(0.8f, CC_CALLBACK_0(Boss::Skill3On, this));
			}
		}
		else if (num == BossMotion::BossAttack4)// 뿔공격
		{
			if (State != num)
			{
				if (m_Patern == false)
				{
					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(Animate::create(effect[4]),
						CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)), NULL));
					m_WeaponRect[0]->runAction(Sequence::create(
						MoveTo::create(0.5f, Vec2(m_WeaponRect[0]->getPositionX() + 30, m_WeaponRect[0]->getPositionY() - 50)),
						MoveTo::create(0.9f, Vec2(m_WeaponRect[0]->getPositionX() - 100, m_WeaponRect[0]->getPositionY() + 230)),
						Place::create(Vec2(m_WeaponRect[0]->getPositionX(), m_WeaponRect[0]->getPositionY())),
						NULL));
					m_Rect->stopAllActions();
					RUN_WITH_DELAY(0.3f, CC_CALLBACK_0(Boss::BossAttack4Sound, this));
				}
				else
				{
					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[4]), Spawn::create(
							CallFunc::create(CC_CALLBACK_0(Boss::CurAct3, this)),
							Animate::create(effect[3]), NULL),
						CallFunc::create(CC_CALLBACK_0(Boss::PaternExit, this)), NULL));
					m_WeaponRect[0]->runAction(Sequence::create(
						MoveTo::create(1.8f, Vec2(m_WeaponRect[0]->getPositionX() - 80, m_WeaponRect[0]->getPositionY() + 110)),
						Place::create(Vec2(m_WeaponRect[0]->getPositionX(), m_WeaponRect[0]->getPositionY())),
						NULL));
					m_Rect->stopAllActions();
					RUN_WITH_DELAY(0.3f, CC_CALLBACK_0(Boss::BossAttack4Sound, this));
					RUN_WITH_DELAY(1.85f, CC_CALLBACK_0(Boss::BossAttack3Sound, this));
				}
			}
		}
		else if (num == BossMotion::BossAttack5)// 쿵쾅쿵쾅
		{
			if (State != num)
			{
				if (m_Patern == false)
				{
					CSoundManager::getInstance()->playEffect("Monster/Boss1/Insect.mp3", false, 1.0f);

					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[5]),
						CallFunc::create(CC_CALLBACK_0(Boss::ElietAttack2, this)),
						NULL));
					m_Rect->stopAllActions();
					RUN_WITH_DELAY(0.3f, CC_CALLBACK_0(Boss::Skill5On, this));
					m_EnemyManager->m_layer->getParent()->runAction(
						Sequence::create(DelayTime::create(0.3f),
							ActionShake::create(1.6f, 50.0f, 50.0f), NULL));
				}
				else
				{
					CSoundManager::getInstance()->playEffect("Monster/Boss1/Insect.mp3", false, 1.0f);

					m_CurMotion = num;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[5]), Spawn::create(
							CallFunc::create(CC_CALLBACK_0(Boss::CurAct2, this)),
							Animate::create(effect[2]), NULL),
						CallFunc::create(CC_CALLBACK_0(Boss::PaternExit, this)),
						NULL));
					m_Rect->stopAllActions();
					RUN_WITH_DELAY(0.3f, CC_CALLBACK_0(Boss::Skill5On, this));
					RUN_WITH_DELAY(3.2f, CC_CALLBACK_0(Boss::BossAttack2Sound, this));

					m_EnemyManager->m_layer->getParent()->runAction(
						Sequence::create(DelayTime::create(0.3f),
							ActionShake::create(1.6f, 50.0f, 50.0f), NULL));
				}
			}
		}
		else if (num == BossMotion::BossHowling)
		{
			CSoundManager::getInstance()->playEffect("Monster/Boss1/howling.mp3", false, 0.7f);

			m_CurMotion = num;
			m_Spr->stopAllActions();
			m_Spr->setColor(Color3B(255, 255, 255));
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[6]), NULL));
			m_Rect->stopAllActions();
		}
		else if (num == BossMotion::BossDeath)
		{
			CSoundManager::getInstance()->playEffect("Monster/Boss1/BossDeath.mp3", false, 0.7f);

			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + Boss_DifY::EliteY1));
			m_CurMotion = num;
			m_Spr->stopAllActions();
			m_Spr->setColor(Color3B(255, 255, 255));
			m_Spr->runAction(Sequence::create(
				Spawn::create(
					Animate::create(effect[7]),
					FadeOut::create(1.4f), NULL),
				CallFunc::create(CC_CALLBACK_0(Boss::BossDelete, this)),
				NULL));
			Boss1Clear = true;
			m_Rect->stopAllActions();
		}
	}
	else if (m_BossNum == BossKind::Boss2)
	{
		if (num == BossMotion::BossIdle)
		{
			static bool first;
			if (State != num)
			{
				if (first == false)
				{
					first = true;
					m_CurMotion = num;
					m_Rect->stopAllActions();
					m_Spr->stopAllActions();
					m_Spr->runAction(Sequence::create(FadeIn::create(1.0f),
						Repeat::create(Animate::create(effect[0]),30), NULL));
				}
				else
				{
					m_CurMotion = num;
					m_Rect->stopAllActions();
					m_Spr->stopAllActions();
					m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
				}
				m_Spr->setColor(Color3B(255, 255, 255));
			}
		}
		else if (num == BossMotion::BossAttack1)//오른쪽 탄막패턴
		{
			if (State != num)
			{
				if (m_Rect->getPosition() != m_SavePos[0])
				{
					m_Rect->setPosition(m_SavePos[0]);
					m_Spr->setPosition(m_SavePos[0]);
					m_Rect->setFlipX(false);
					m_Spr->setFlipX(false);
					EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
						m_Rect->getPositionX(), m_Rect->getPositionY() + 20, true);
				}
				m_Spr->setColor(Color3B(255, 255, 255));
				EffectManager::getInstance()->
					EffectSwitch(EffectName::GreenE, m_Spr->getPositionX()-70, m_Spr->getPositionY() + 170, false);
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[1]), Animate::create(effect[0]), Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(Boss::BoosAttack1,this)), NULL));
				
				RUN_WITH_DELAY(0.25f, CC_CALLBACK_0(Boss::MakeAttack1Bullet, this));
			}
		}
		else if (num == BossMotion::BossAttack2)//왼쪽 탄막패턴
		{
			if (State != num)
			{
				if (m_Rect->getPosition() != m_SavePos[1])
				{
					m_Rect->setPosition(m_SavePos[1]);
					m_Spr->setPosition(m_SavePos[1]);
					m_Rect->setFlipX(true);
					m_Spr->setFlipX(true);
					EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
						m_Rect->getPositionX(), m_Rect->getPositionY() + 20, true);
				}
				m_Spr->setColor(Color3B(255, 255, 255));
				EffectManager::getInstance()->
					EffectSwitch(EffectName::RedE, m_Spr->getPositionX() + 70, m_Spr->getPositionY() + 170, false);
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[1]), Animate::create(effect[0]), Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(Boss::BoosAttack1, this)), NULL));

				RUN_WITH_DELAY(0.25f, CC_CALLBACK_0(Boss::MakeAttack2Bullet, this));
			}
		}
		else if (num == BossMotion::BossAttack3)//중앙 탄막패턴
		{
			if (State != num)
			{
				CSoundManager::getInstance()->playEffect("Monster/Boss2/darkmagic2.mp3", false, 1.0f);

				if (m_Rect->getPosition() != m_SavePos[2])
				{
					m_Rect->setPosition(m_SavePos[2]);
					m_Spr->setPosition(m_SavePos[2]);
					m_Rect->setFlipX(false);
					m_Spr->setFlipX(false);
					EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
						m_Rect->getPositionX(), m_Rect->getPositionY() + 20, true);
				}
				m_Spr->setColor(Color3B(255, 255, 255));
				EffectManager::getInstance()->
					EffectSwitch(EffectName::BlackE, m_Spr->getPositionX() - 70, m_Spr->getPositionY() + 170, false);
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[1]), Animate::create(effect[0]), Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(Boss::BoosAttack1, this)), NULL));

				RUN_WITH_DELAY(0.25f, CC_CALLBACK_0(Boss::MakeAttack3Bullet, this));
			}
		}
		else if (num == BossMotion::BossAttack4)//독안개 패턴
		{
			if (State != num)
			{
				CSoundManager::getInstance()->playEffect("Monster/Boss2/poisoncloud.mp3", false, 1.0f);

				if (m_Rect->getPosition() != m_SavePos[1])
				{
					m_Rect->setPosition(m_SavePos[1]);
					m_Spr->setPosition(m_SavePos[1]);
					m_Rect->setFlipX(true);
					m_Spr->setFlipX(true);
					EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
						m_Rect->getPositionX(), m_Rect->getPositionY() + 20, true);
				}
				EffectManager::getInstance()->
					EffectSwitch(EffectName::GreenE, m_Spr->getPositionX() + 70, m_Spr->getPositionY() + 170, false);
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[2]), Animate::create(effect[0]), Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(Boss::BoosAttack1, this)), NULL));

				RUN_WITH_DELAY(0.25f, CC_CALLBACK_0(Boss::MakeAttack4, this));
			}
		}
		else if (num == BossMotion::BossAttack5)//불 패턴
		{
			if (State != num)
			{
				CSoundManager::getInstance()->playEffect("Monster/Boss2/Magic_Spell_Fire1.mp3", false, 1.0f);

				if (m_Rect->getPosition() != m_SavePos[0])
				{
					m_Rect->setPosition(m_SavePos[0]);
					m_Spr->setPosition(m_SavePos[0]);
					m_Rect->setFlipX(false);
					m_Spr->setFlipX(false);
					EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
						m_Rect->getPositionX(), m_Rect->getPositionY() + 20, true);
				}
				EffectManager::getInstance()->
					EffectSwitch(EffectName::RedE, m_Spr->getPositionX()- 70, m_Spr->getPositionY() + 170, false);
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[2]), Animate::create(effect[0]), Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(Boss::BoosAttack1, this)), NULL));

				RUN_WITH_DELAY(0.25f, CC_CALLBACK_0(Boss::MakeAttack5, this));
			}
		}
		else if (num == BossMotion::BossAttack6)//레이저 패턴
		{
			if (State != num)
			{
				CSoundManager::getInstance()->playEffect("Monster/Boss2/laser1.mp3", false, 1.0f);

				if (m_Rect->getPosition() != m_SavePos[2])
				{
					m_Rect->setPosition(m_SavePos[2]);
					m_Spr->setPosition(m_SavePos[2]);
					m_Rect->setFlipX(false);
					m_Spr->setFlipX(false);
					EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
						m_Rect->getPositionX(), m_Rect->getPositionY() + 20, true);
				}
				m_Spr->setColor(Color3B(255, 255, 255));
				EffectManager::getInstance()->
					EffectSwitch(EffectName::BlackE, m_Spr->getPositionX() - 70, m_Spr->getPositionY() + 170, false);
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[2]), Animate::create(effect[0]), Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(Boss::BoosAttack1, this)), NULL));

				RUN_WITH_DELAY(0.25f, CC_CALLBACK_0(Boss::MakeAttack6, this));
			}
		}
		else if (num == BossMotion::BossDeath)
		{
			if (State != num)
			{
				m_Spr->setColor(Color3B(255, 255, 255));
				CSoundManager::getInstance()->playEffect("Monster/Boss2/bossdeath1.mp3", false, 1.0f);
				CSoundManager::getInstance()->stopAllBgms();
				m_CurMotion = num;
				m_Rect->stopAllActions();
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[3]), FadeOut::create(1.5f),
					CallFunc::create(CC_CALLBACK_0(Boss::BossDelete, this)),
					NULL));
				m_EnemyManager->m_Boss.clear();
			}
		}
	}
	State = num;
}

void Boss::EliteSkill()
{
	auto Skill = Sprite::create();
	Skill->setPosition(Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? 450 : -450), m_Rect->getPositionY() - 40));
	m_EnemyManager->m_layer->addChild(Skill, 7);
	Skill->setFlipX(m_Spr->isFlipX());
	Skill->runAction(Sequence::create(
		DelayTime::create(0.5f),
		Animate::create(effect[7]),
		RemoveSelf::create(),
		NULL));
	m_WeaponRect[1]->runAction(Sequence::create(
		DelayTime::create(0.5f), Place::create(Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? 250 : -250), Skill->getPositionY())),
		MoveTo::create(0.8f, Vec2(Skill->getPositionX() + (m_Spr->isFlipX() ? 200 : -200), Skill->getPositionY())),
		Place::create(Vec2(-500, -500)),
		NULL));
}

void Boss::BossUpdate()
{
	// 엘리트 보스
	if (m_BossNum == BossKind::EliteBoss)
	{
		m_WeaponRect[0]->setPosition(Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? 100 : -100)
			, m_Rect->getPositionY()));

		if (ObjectHero::getInstance()->m_Death)
			return;
		//스킬 공격 충돌체크
		if (m_CurMotion == BossMotion::BossAttack2)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_WeaponRect[1]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
			}
		}

		//박치기 공격체크
		if (m_CurMotion == BossMotion::BossAttack3)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
			}
		}

		//근접공격 충돌체크
		if (m_Spr->getTexture()->getName() == m_Att[1])
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_WeaponRect[0]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
			}
		}
	}

	// 스테이이지1 보스
	else if (m_BossNum == BossKind::Boss1)
	{
		if (ObjectHero::getInstance()->m_Death)
			return;
		//하늘돌
		//if (m_CurMotion == BossMotion::BossAttack3)
		{
			for (int i = 0; i < 17; ++i)
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Skill2Rect[i]->getBoundingBox()) &&
					m_Skill2Stone[i]->isVisible())
				{
					m_Skill2Stone[i]->stopAllActions();
					m_Skill2Stone[i]->runAction(Sequence::create(
						Animate::create(effect[9]), Hide::create(),
						Place::create(Vec2(m_Skill2Stone[i]->getPositionX(), 1650)), NULL));

					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
						ObjectHero::getInstance()->SetHP(-10);
					}
					break;
				}
			}
		}
		//else if (m_CurMotion == BossMotion::BossAttack2)
		{
			for (int i = 0; i < 17; ++i)
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Skill1Rect[i]->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
					}
					ObjectHero::getInstance()->SetHP(-10);
					break;
				}
			}
		}
		// 뿔공격일때
		if (m_CurMotion == BossMotion::BossAttack4)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_WeaponRect[0]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
			}
		}
	}

	// 파이널 보스
	else if (m_BossNum == BossKind::Boss2)
	{
		m_Curse->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), ObjectHero::getInstance()->m_Rect->getPositionY() + 150));
		//불체크
		if (m_CurMotion == BossMotion::BossAttack5)
		{
			if (m_Fire->Spr->isVisible() && m_Fire->Rect->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Fire->Rect->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
					ObjectHero::getInstance()->SetHP(-10);
					CSoundManager::getInstance()->playEffect("Monster/Boss2/crush1.mp3", false, 1.0f);
				}
			}
		}
		//레이저 체크
		if (m_CurMotion == BossMotion::BossAttack6)
		{
			for (int i = 0; i < 2; i++)
			{
				if (m_Laser->isVisible() && m_LaserRect[i]->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_LaserRect[i]->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
						ObjectHero::getInstance()->SetHP(-10);
					}
				}
			}
		}
		//녹색탄환
		if (m_GreenL.size() > 0)
		{
			std::vector<Bullet*>::iterator iter = m_GreenL.begin();
			for (iter; iter != m_GreenL.end(); iter++)
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect((*iter)->Rect->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > (*iter)->Rect->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
						ObjectHero::getInstance()->SetHP(-10);
						CSoundManager::getInstance()->playEffect("Monster/Boss2/crush1.mp3", false, 1.0f);
					}
					(*iter)->Rect->stopAllActions();
					(*iter)->Rect->removeFromParent();
					(*iter)->Spr->runAction(Sequence::create(
						Animate::create(effect[4]),RemoveSelf::create(), NULL));
					m_GreenL.erase(iter);
					return;
				}
				else if ((*iter)->Rect->getPositionX() < -100)
				{
					(*iter)->Rect->stopAllActions();
					(*iter)->Rect->removeFromParent();
					(*iter)->Spr->removeFromParent();
					m_GreenL.erase(iter);
					return;
				}
			}
		}
		//붉은 탄환
		if (m_RedL.size() > 0)
		{
			std::vector<Bullet*>::iterator iter = m_RedL.begin();
			for (iter; iter != m_RedL.end(); iter++)
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect((*iter)->Rect->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > (*iter)->Rect->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
						ObjectHero::getInstance()->SetHP(-10);
						CSoundManager::getInstance()->playEffect("Monster/Boss2/crush1.mp3", false, 1.0f);
					}
					(*iter)->Rect->stopAllActions();
					(*iter)->Rect->removeFromParent();
					(*iter)->Spr->runAction(Sequence::create(
						Animate::create(effect[5]), RemoveSelf::create(), NULL));
					m_RedL.erase(iter);
					return;
				}
				else if ((*iter)->Rect->getPositionX() < 0 || (*iter)->Rect->getPositionX() > 1600 ||
					(*iter)->Rect->getPositionY() < 0 || (*iter)->Rect->getPositionY() > 1920 )
				{
					(*iter)->Rect->stopAllActions();
					(*iter)->Rect->removeFromParent();
					(*iter)->Spr->removeFromParent();
					m_RedL.erase(iter);
					return;
				}
			}
		}
		//검은탄환
		if (m_BlackL.size() > 0)
		{
			std::vector<Bullet*>::iterator iter = m_BlackL.begin();
			for (iter; iter != m_BlackL.end(); iter++)
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect((*iter)->Rect->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (m_CurseOn == false)
						{
							HeroCurse();
							m_CurseOn = true;
						}
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > (*iter)->Rect->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
						ObjectHero::getInstance()->SetHP(-10);
						CSoundManager::getInstance()->playEffect("Monster/Boss2/crush1.mp3", false, 1.0f);
					}
					(*iter)->Rect->stopAllActions();
					(*iter)->Rect->removeFromParent();
					(*iter)->Spr->runAction(Sequence::create(
						Animate::create(effect[6]), RemoveSelf::create(), NULL));
					m_BlackL.erase(iter);
					return;
				}
				else if ((*iter)->Rect->getPositionX() < 0 || (*iter)->Rect->getPositionX() > 1600 ||
					(*iter)->Rect->getPositionY() < 0 || (*iter)->Rect->getPositionY() > 1920)
				{
					(*iter)->Rect->stopAllActions();
					(*iter)->Rect->removeFromParent();
					(*iter)->Spr->removeFromParent();
					m_BlackL.erase(iter);
					return;
				}
			}
		}
		//독탄환
		if (m_PoisonL.size() > 0)
		{
			std::vector<Bullet*>::iterator iter = m_PoisonL.begin();
			for (iter; iter != m_PoisonL.end(); iter++)
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect((*iter)->Rect->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > (*iter)->Rect->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
						ObjectHero::getInstance()->SetHP(-10);
						CSoundManager::getInstance()->playEffect("Monster/Boss2/crush1.mp3", false, 1.0f);
					}
				}
			}
		}
	}	
}

void Boss::MoveBoss()
{
	if (m_BossNum == BossKind::EliteBoss)
	{
		int AniNum = 0;
		if (m_Death == false)
		{
			AniNum = BossMotion::BossIdle;
			m_Rect->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() - 8));
			m_MoveRect->setPosition(Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? 250 : -250)
				, m_Rect->getPositionY()));
			for (Sprite* box : SourceManager::getInstance()->m_Stg1_2MBox)
			{
				if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()))
				{
					m_Rect->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 8));
					break;
				}
			}

			//타격 체크
			if (m_HitCheck || m_Lock)
			{
				if (State == BossMotion::BossHowling)
					m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 40));
				else
					m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 40, m_Rect->getPositionY()));

				return;
			}

			//공격 체크
			if (m_Attack)
			{
				AniNum = m_LastMotion;
				if (AniNum == BossMotion::BossAttack3 && m_BossNum == BossKind::EliteBoss)
				{
					bool check = false;
					for (Sprite* box : SourceManager::getInstance()->m_Stg1_2MBox)
					{
						if (m_MoveRect->getBoundingBox().intersectsRect(box->getBoundingBox()) &&
							m_MoveRect->getPositionY() < box->getPositionY() + 150)
						{
							m_Rect->stopAllActions();
							check = true;
							break;
						}
					}
					m_CanMove = check ? false : true;
				}
			}
			else//공격외 동작
			{
				float speed = 0.0f;
				if (m_BossNum == BossKind::EliteBoss)
					speed = 3.0f;
				for (int iter : m_dir)
				{
					if (m_Run)
					{
						AniNum = m_Spr->isFlipX() ? BossMotion::BossMoveRight : BossMotion::BossMoveLeft;
					}
					/*else if (iter == BossMotion::BossAttack2)
					{
						AniNum = iter;
					}*/
					if (iter == BossMotion::BossMoveLeft || iter == BossMotion::BossMoveRight)
					{
						AniNum = iter;
						m_Rect->setFlipX(iter == BossMotion::BossMoveLeft ? false : true);
						m_Spr->setFlipX(iter == BossMotion::BossMoveLeft ? false : true);
					}

					bool check = false;
					for (Sprite* box : SourceManager::getInstance()->m_Stg1_2MBox)
					{
						if (m_MoveRect->getBoundingBox().intersectsRect(box->getBoundingBox()) &&
							m_MoveRect->getPositionY() < box->getPositionY() + 150)
						{
							if (iter == BossMotion::BossMoveLeft || iter == BossMotion::BossMoveRight)
							{
								m_Rect->stopAllActions();
								check = true;
								break;
							}
						}
					}
					m_CanMove = check ? false : true;
				}
			}
			if (m_CurMotion == BossMotion::BossMoveLeft || m_CurMotion == BossMotion::BossMoveRight)
				m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + Boss_DifY::EliteY1));
			else if (m_CurMotion == BossMotion::BossIdle)
				m_Spr->setPosition(Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? -40 : 40)
					, m_Rect->getPositionY() + Boss_DifY::EliteY1 + 5));
			else if (m_CurMotion == BossMotion::BossAttack2)//원거리공격
				m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + Boss_DifY::EliteY1 + 95));
			else if (m_CurMotion == BossMotion::BossAttack1)//근거리 공격
				m_Spr->setPosition(Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? +70 : -70)
					, m_Rect->getPositionY() + Boss_DifY::EliteY1 + -5));
			else if (m_CurMotion == BossMotion::BossAttack3)// 박치기 공격
				m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + Boss_DifY::EliteY1));
			//else if (m_CurMotion == BossMotion::BossDeath)// 사망
			switch (AniNum)
			{
			case BossMotion::BossIdle:
				AnimationSwitch(AniNum);
				break;
			case BossMotion::BossMoveLeft:
			case BossMotion::BossMoveRight:
				AnimationSwitch(AniNum);
				break;
			case BossMotion::BossAttack2:
				AnimationSwitch(AniNum);
				break;
			case BossMotion::BossAttack1:
				AnimationSwitch(AniNum);
				break;
			case BossMotion::BossAttack3:
				AnimationSwitch(AniNum);
				break;
			}
		}
	}

	//스테이지 보스
	else if (m_BossNum == BossKind::Boss1)
	{
		int AniNum = 999;
		if (m_Lock == false)
			AniNum = BossMotion::BossIdle;

		// 공격중이면
		if (m_Attack)
		{
			AniNum = m_LastMotion;
		}

		if (m_CurMotion == BossMotion::BossIdle)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 20, m_Rect->getPositionY() + 60));
		else if (m_CurMotion == BossMotion::BossAttack1)//앞발찍기
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 20, m_Rect->getPositionY() + 143));
		else if (m_CurMotion == BossMotion::BossAttack2)//뒷발차기
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 37, m_Rect->getPositionY() + 65));
		else if (m_CurMotion == BossMotion::BossAttack3)//콧바람
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 10, m_Rect->getPositionY() + 70));
		else if (m_CurMotion == BossMotion::BossAttack4)//근접공격
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 15, m_Rect->getPositionY() + 73));
		else if (m_CurMotion == BossMotion::BossAttack5)//쿵쾅
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 15, m_Rect->getPositionY() + 73));
		else if (m_CurMotion == BossMotion::BossHowling)//하울링
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 7, m_Rect->getPositionY() + 73));

		switch (AniNum)
		{
		case BossMotion::BossIdle:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack1:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack2:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack3:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack4:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack5:
			AnimationSwitch(AniNum);
			break;
		}
	}

	//파이널 보스
	else if (m_BossNum == BossKind::Boss2)
	{
		int AniNum = BossMotion::BossIdle;
		if (m_Lock)
			return;

		// 공격중이면
		if (m_Attack)
		{
			AniNum = m_LastMotion;
		}

		if (m_CurMotion == BossMotion::BossIdle)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		else if(m_CurMotion == BossMotion::BossAttack1)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		else if (m_CurMotion == BossMotion::BossAttack2)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		else if (m_CurMotion == BossMotion::BossAttack3)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		else if (m_CurMotion == BossMotion::BossAttack4)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		else if (m_CurMotion == BossMotion::BossAttack5)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		else if (m_CurMotion == BossMotion::BossAttack6)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		else if (m_CurMotion == BossMotion::BossDeath)
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));

		switch (AniNum)
		{
		case BossMotion::BossIdle:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack1:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack2:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack3:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack4:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack5:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossAttack6:
			AnimationSwitch(AniNum);
			break;
		case BossMotion::BossDeath:
			AnimationSwitch(AniNum);
			break;
		}
	}
}

void Boss::SetMoveDir()
{
	extern Timer2* m_Timer2;

	if (m_Death == false)
	{
		if (m_BossNum == BossKind::EliteBoss)
		{
			if (m_Lock)
				return;
			if (m_Attack)
			{
				m_dir.clear();
				return;
			}
			m_dir.clear();

			if (m_HP > 100)// HP 조건문
			{
				//거리차 700이상
				if (abs(m_Rect->getPositionX() - ObjectHero::getInstance()->m_Rect->getPositionX()) >= 700)
				{
					if (m_Rect->getPositionX() < ObjectHero::getInstance()->m_Rect->getPositionX())
					{
						m_dir.push_back(BossMotion::BossMoveRight);
						m_LastMotion = BossMotion::BossMoveRight;
					}
					else
					{
						m_dir.push_back(BossMotion::BossMoveLeft);
						m_LastMotion = BossMotion::BossMoveLeft;
					}

				}
				//거리차 500이상 700미만
				else if (abs(m_Rect->getPositionX() - ObjectHero::getInstance()->m_Rect->getPositionX()) > 500 &&
					abs(m_Rect->getPositionX() - ObjectHero::getInstance()->m_Rect->getPositionX()) < 800)
				{
					m_dir.push_back(BossMotion::BossAttack2);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack2;
				}
				else// 거리차 500 미만
				{
					if (m_Rect->getPositionX() < ObjectHero::getInstance()->m_Rect->getPositionX())
					{
						m_Spr->setFlipX(true);
						m_Rect->setFlipX(true);
					}
					else
					{
						m_Spr->setFlipX(false);
						m_Rect->setFlipX(false);
					}
					m_dir.push_back(BossMotion::BossAttack1);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack1;
				}
			}
			else
			{
				if (ObjectHero::getInstance()->m_Rect->getPositionX() > m_Rect->getPositionX())
				{
					m_Spr->setFlipX(true);
					m_Rect->setFlipX(true);
					m_MoveRect->setFlipX(true);
					m_dir.push_back(BossMotion::BossAttack3);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack3;
				}
				else
				{
					m_Spr->setFlipX(false);
					m_Rect->setFlipX(false);
					m_MoveRect->setFlipX(false);
					m_dir.push_back(BossMotion::BossAttack3);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack3;
				}
			}
		}
		// 스테이지1 보스
		else if (m_BossNum == BossKind::Boss1)
		{
			if (m_Patern == false)
			{
				if (m_Lock)
					return;
				if (m_Attack)
				{
					m_dir.clear();
					return;
				}
				m_dir.clear();
			}
			else
				return;

			if (m_HP > 100)
			{
				if (m_Random == false)
				{
					//근접범위 안인가? - 400이하
					if (m_Rect->getPositionX() - ObjectHero::getInstance()->m_Rect->getPositionX() < 400)
					{
						m_dir.push_back(BossMotion::BossAttack4);
						m_Attack = true;
						m_LastMotion = BossMotion::BossAttack4;
					}
					else//근접범위 박 / 콧바람공격
					{
						m_dir.push_back(BossMotion::BossAttack3);
						m_Attack = true;
						m_LastMotion = BossMotion::BossAttack3;
					}
					m_Random = true;
				}
				else//랜덤
				{
					int randNum = random(1, 3);
					if (randNum == 1)//앞발찍기
					{
						m_dir.push_back(BossMotion::BossAttack1);
						m_Attack = true;
						m_LastMotion = BossMotion::BossAttack1;
						m_Random = false;
					}
					else if (randNum == 2)//뒷발차기
					{
						m_dir.push_back(BossMotion::BossAttack2);
						m_Attack = true;
						m_LastMotion = BossMotion::BossAttack2;
						m_Random = false;
					}
					else//쿵쾅쿵쾅
					{
						m_dir.push_back(BossMotion::BossAttack5);
						m_Attack = true;
						m_LastMotion = BossMotion::BossAttack5;
						m_Random = false;
					}
				}
			}
			else // 체력 적음
			{
				int randNum = random(1, 5);
				//앞발찍기 -> 뒷발차기
				if (randNum == 1)
				{
					m_dir.push_back(BossMotion::BossAttack1);
					m_LastMotion = BossMotion::BossAttack1;
				}
				//쿵쾅쿵쾅 -> 뒷발차기
				else if (randNum == 5)
				{
					m_dir.push_back(BossMotion::BossAttack5);
					m_LastMotion = BossMotion::BossAttack5;
				}
				//뿔 휘두르기 -> 콧바람 불기
				else if (randNum == 4)
				{
					m_dir.push_back(BossMotion::BossAttack4);
					m_LastMotion = BossMotion::BossAttack4;
				}
				//뒷발차기 -> 콧바람 불기
				else if (randNum == 2)
				{
					m_dir.push_back(BossMotion::BossAttack2);
					m_LastMotion = BossMotion::BossAttack2;
				}
				if (randNum != 3)
				{
					m_Attack = true;
					m_Patern = true;
				}
			}
		}
		// 파이널 보스
		else if (m_BossNum == BossKind::Boss2)
		{
			if (m_Lock)
				return;
			if (m_Attack)
			{
				m_dir.clear();
				return;
			}
			m_dir.clear();

			if (m_HP > 250)
			{
				if (m_Random == false)
				{
					int randNum = random(1, 2);
					if (randNum == 1)
					{
						m_dir.push_back(BossMotion::BossAttack1);
						m_Attack = true;
						m_LastMotion = BossMotion::BossAttack1;
						m_Random = false;
					}
					else if (randNum == 2)
					{
						m_dir.push_back(BossMotion::BossAttack2);
						m_Attack = true;
						m_LastMotion = BossMotion::BossAttack2;
						m_Random = false;
					}
				}
			}
			else
			{
				int randNum = random(3, 6);
				if (randNum == 3)
				{
					m_dir.push_back(BossMotion::BossAttack3);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack3;
					m_Random = false;
				}
				else if (randNum == 4)
				{
					m_dir.push_back(BossMotion::BossAttack4);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack4;
					m_Random = false;
				}
				else if (randNum == 5)
				{
					m_dir.push_back(BossMotion::BossAttack5);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack5;
					m_Random = false;
				}
				else if (randNum == 6)
				{
					m_dir.push_back(BossMotion::BossAttack6);
					m_Attack = true;
					m_LastMotion = BossMotion::BossAttack6;
					m_Random = false;
				}
			}
		}
	}
}

void Boss::BossHit()
{
	//if (m_BossNum != BossKind::Boss2)
	{
		m_Spr->runAction(Sequence::create(
			TintTo::create(0.0f, Color3B::RED), DelayTime::create(0.2f), TintTo::create(0.0f, Color3B(255, 255, 255)),
			NULL));
	}
}

void Boss::BossDeath()
{
	if (m_BossNum == BossKind::EliteBoss)
	{
		extern EnemyManager* m_EnemyManager;
		for (int i = 0; i < BossEffectNum; ++i)
			CC_SAFE_RELEASE(effect[i]);

		m_Spr->removeFromParent();
		m_Rect->removeFromParent();
		m_MoveRect->removeFromParent();
		m_WeaponRect[0]->removeFromParent();
	}
	else if (m_BossNum == BossKind::Boss1)
	{
		extern EnemyManager* m_EnemyManager;
		for (int i = 0; i < BossEffectNum; ++i)
			CC_SAFE_RELEASE(effect[i]);
		m_Spr->removeFromParent();
		m_Rect->removeFromParent();
		m_WeaponRect[0]->removeFromParent();

		for (int i = 0; i < 20; i++)
		{
			m_Skill1Stone[i]->removeFromParent();
			m_Skill1Rect[i]->removeFromParent();
			m_Skill2Stone[i]->removeFromParent();
			m_Skill2Rect[i]->removeFromParent();
		}
	}
}

void Boss::Skill2On()
{
	for (int i = 0; i < 17; ++i)
	{
		if (i < 5 || i > 8)
		{
			m_Skill2Stone[i]->runAction(Sequence::create(
				Show::create(),
				MoveTo::create(0.8f, Vec2(m_Skill2Stone[i]->getPositionX(), m_Skill2Stone[i]->getPositionY() - 935)),
				Animate::create(effect[9]), Hide::create(),
				Place::create(m_Skill2Stone[i]->getPosition()),
				NULL));
			m_Skill2Rect[i]->runAction(Sequence::create(
				MoveTo::create(0.8f, Vec2(m_Skill2Rect[i]->getPositionX(), m_Skill2Rect[i]->getPositionY() - 935)),
				Place::create(m_Skill2Stone[i]->getPosition()),
				NULL));
		}
		else
		{
			m_Skill2Stone[i]->runAction(Sequence::create(
				Show::create(),
				MoveTo::create(0.5f, Vec2(m_Skill2Stone[i]->getPositionX(), m_Skill2Stone[i]->getPositionY() - 635)),
				Animate::create(effect[9]), Hide::create(),
				Place::create(m_Skill2Stone[i]->getPosition()),
				NULL));
			m_Skill2Rect[i]->runAction(Sequence::create(
				MoveTo::create(0.5f, Vec2(m_Skill2Rect[i]->getPositionX(), m_Skill2Rect[i]->getPositionY() - 635)),
				Place::create(m_Skill2Stone[i]->getPosition()),
				NULL));
		}
	}
}

void Boss::Skill1On()
{
	for (int i = 0; i < 17; ++i)
	{
		m_Skill1Stone[i]->runAction(Sequence::create(
			Show::create(), Animate::create(effect[8]), Hide::create(), NULL));
		m_Skill1Rect[i]->runAction(Sequence::create(
			MoveTo::create(0.65f, Vec2(m_Skill1Rect[i]->getPositionX(), m_Skill1Rect[i]->getPositionY() + 180)),
			Place::create(m_Skill1Rect[i]->getPosition()), NULL));
	}
}

void Boss::Skill3On()
{
	ObjectHero::getInstance()->m_BossSkill1 = true;
	RUN_WITH_DELAY(1.3f, CC_CALLBACK_0(Boss::Skill3Off, this));
}

void Boss::Skill3Off()
{
	ObjectHero::getInstance()->m_BossSkill1 = false;
}

void Boss::BossDelete()
{
	if (m_BossNum == BossKind::EliteBoss)
	{
		m_Spr->removeFromParent();
		m_Rect->removeFromParent();
		m_MoveRect->removeFromParent();
		m_WeaponRect[0]->removeFromParent();
		m_WeaponRect[1]->removeFromParent();
	}
	else if (m_BossNum == BossKind::Boss1)
	{
		m_Spr->removeFromParent();
		m_Rect->removeFromParent();
		m_WeaponRect[0]->removeFromParent();

		for (int i = 0; i < 17; ++i)
		{
			m_Skill1Stone[i]->removeFromParent();
			m_Skill1Rect[i]->removeFromParent();
			m_Skill2Stone[i]->removeFromParent();
			m_Skill2Rect[i]->removeFromParent();
		}
	}
	else if (m_BossNum == BossKind::Boss2)
	{
		Boss2Clear = true;
		m_Spr->removeFromParent();
		m_Rect->removeFromParent();
	}
	for (int i = 0; i < BossEffectNum; ++i)
		CC_SAFE_RELEASE(effect[i]);
}

void Boss::MakeAttack1Bullet()
{
	for(int i = 0; i < 4; ++i)
		MakeGreenBullet(Vec2(2000, i*350 + 300),0);
	for(int i = 0; i < 4; ++i)
		MakeGreenBullet(Vec2(2000, i * 350 + 300), 1.0f);
	for (int i = 0; i < 4; ++i)
		MakeGreenBullet(Vec2(2000, i * 350 + 300), 2.0f);
}

void Boss::MakeGreenBullet(Vec2 pos,float delay)
{
	Bullet* bul = new Bullet;
	bul->Rect = Sprite::createWithSpriteFrame(m_BulletRect->getSpriteFrame());
	bul->Rect->setScale(0.6f);
	bul->Rect->setPosition(pos);
	bul->Rect->setVisible(ColiideRect);
	bul->Rect->runAction(Sequence::create(DelayTime::create(delay),
		MoveTo::create(3.0f, Vec2(pos.x - 2500, pos.y)), NULL));

	bul->Spr = Sprite::createWithSpriteFrame(m_GreenSample->getSpriteFrame());
	bul->Spr->setPosition(pos);
	bul->Spr->setScale(0.6f);
	bul->Spr->runAction(Sequence::create(DelayTime::create(delay),
		MoveTo::create(3.0f, Vec2(pos.x - 2500, pos.y)), NULL));
	m_EnemyManager->m_layer->addChild(bul->Rect, 5);
	m_EnemyManager->m_layer->addChild(bul->Spr, 4);

	m_GreenL.push_back(bul);
}

void Boss::MakeAttack2Bullet()
{
	static int num;
	if (num != 6)
	{
		num++;
		MakeRedBullet(Vec2(m_Spr->getPositionX() + 70, m_Spr->getPositionY() + 170));
		RUN_WITH_DELAY(0.3f, CC_CALLBACK_0(Boss::MakeAttack2Bullet, this));
	}
	else
		num = 0;
}

void Boss::MakeRedBullet(Vec2 pos)
{
	Vec2 hpos = ObjectHero::getInstance()->m_Rect->getPosition();
	Bullet* bul = new Bullet;
	bul->Rect = Sprite::createWithSpriteFrame(m_BulletRect->getSpriteFrame());
	bul->Rect->setScale(0.6f);
	bul->Rect->setPosition(pos);
	bul->Rect->setVisible(ColiideRect);
	bul->Rect->runAction(RepeatForever::create(
		MoveBy::create(1.0f, Vec2(hpos.x - pos.x, hpos.y - pos.y))));

	bul->Spr = Sprite::createWithSpriteFrame(m_RedSample->getSpriteFrame());
	bul->Spr->setPosition(pos);
	bul->Spr->setScale(0.6f);
	bul->Spr->runAction(RepeatForever::create(
		MoveBy::create(1.0f, Vec2(hpos.x - pos.x, hpos.y - pos.y))));
	m_EnemyManager->m_layer->addChild(bul->Rect, 5);
	m_EnemyManager->m_layer->addChild(bul->Spr, 4);

	m_RedL.push_back(bul);
}

void Boss::MakeAttack3Bullet()
{
	for (int i = 0; i < 12; i++)
	{
		float de = i * 30;
		de = (double)de * PI / 180;

		Bullet* bul = new Bullet;
		bul->Rect = Sprite::createWithSpriteFrame(m_BulletRect->getSpriteFrame());
		bul->Rect->setScale(0.6f);
		bul->Rect->setPosition(m_Rect->getPosition());
		bul->Rect->setVisible(ColiideRect);
		bul->Rect->runAction(MoveTo::create(3.0f, Vec2(m_Rect->getPositionX() + cos(de) * (2000), m_Rect->getPositionY() + sin(de) * (2000))));

		bul->Spr = Sprite::createWithSpriteFrame(m_BlackSample->getSpriteFrame());
		bul->Spr->setPosition(m_Rect->getPosition());
		bul->Spr->setScale(0.6f);
		bul->Spr->runAction(MoveTo::create(3.0f, Vec2(m_Rect->getPositionX() + cos(de) * (2000), m_Rect->getPositionY() + sin(de) * (2000))));
		m_EnemyManager->m_layer->addChild(bul->Rect, 5);
		m_EnemyManager->m_layer->addChild(bul->Spr, 4);

		m_BlackL.push_back(bul);
	}
}

void Boss::MakeAttack4()
{
	for (int i = 0; i < 4; ++i)
	{
		float x = random(100, 1900);
		float y = random(100, 1500);

		Bullet* bul = new Bullet;
		bul->Rect = Sprite::createWithSpriteFrame(m_PosionRect->getSpriteFrame());
		bul->Rect->setScale(0.6f);
		bul->Rect->setPosition(Vec2(x,y));
		bul->Rect->setVisible(ColiideRect);
		bul->Rect->runAction(
			MoveTo::create(3.5f, Vec2(x + 500, y)));

		bul->Spr = Sprite::createWithSpriteFrame(m_FogSample->getSpriteFrame());
		bul->Spr->setPosition(Vec2(x,y));
		bul->Spr->setScale(0.6f);
		bul->Spr->runAction(
			MoveTo::create(3.5f, Vec2(x + 500, y)));
		m_EnemyManager->m_layer->addChild(bul->Rect, 5);
		m_EnemyManager->m_layer->addChild(bul->Spr, 4);

		m_PoisonL.push_back(bul);
	}

	RUN_WITH_DELAY(3.7f, CC_CALLBACK_0(Boss::PoisonInit, this));
}

void Boss::PoisonInit()
{
	std::vector<Bullet*>::iterator iter = m_PoisonL.begin();
	int size = m_PoisonL.size();
	for (int i = 0; i < size; i++)
	{
		(*iter)->Rect->runAction(Sequence::create(FadeOut::create(0.5f),
			RemoveSelf::create(), NULL));
		(*iter)->Spr->runAction(Sequence::create(FadeOut::create(0.5f),
			RemoveSelf::create(), NULL));
		m_PoisonL.erase(iter);
		iter = m_PoisonL.begin();
	}
}

void Boss::MakeAttack5()
{
	m_Fire->Spr->runAction(Sequence::create(
		Show::create(), Animate::create(effect[7]), Hide::create(), NULL));
	m_Fire->Rect->runAction(Sequence::create(
		MoveTo::create(1.0f,Vec2(0,000)), DelayTime::create(1.2f), MoveTo::create(1.0f, Vec2(0, -800)), NULL));
}

void Boss::MakeAttack6()
{
	m_Laser->runAction(Sequence::create(
		Show::create(), Animate::create(effect[8]), Hide::create(), NULL));
}

