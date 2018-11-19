#include "Default.h"

void ObjectEnemy::CreateObject()
{
	extern Timer2* m_Timer2;
	m_Timer = m_Timer2->GetTime();

	//애니메이션
	char str[100] = { 0 };
	//////////// 기본 캐릭터
	for (int i = 0; i < EnemyEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0 || i == 5 || i == 6)
			effect[i]->setDelayPerUnit(M1RunDly);
		else if (i == 1)
			effect[i]->setDelayPerUnit(M1IdleDly);
		else if (i == 2)
			effect[i]->setDelayPerUnit(M1AttackDly);
		else if (i == 3 || i == 7)
			effect[i]->setDelayPerUnit(M1DieDly);
		else if (i == 4)
			effect[i]->setDelayPerUnit(M1HitDly);
	}
	for (int i = 1; i <= 15; i++)// 걷기 
	{
		sprintf(str, "Monster/Monster1/idle-walk/walk%d.png", i);
		effect[5]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 27; i++)// 달리기
	{
		sprintf(str, "Monster/Monster1/run/Run%d.png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}
	//effect[0]->setRestoreOriginalFrame(true);//애니메이션 종료시 원래 스프라이트로 복귀
	for (int i = 1; i <= 15; i++)// 서있기
	{
		sprintf(str, "Monster/Monster1/idle/Idle%d.png", i);
		effect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 4; i++)// 달리기->서있기
	{
		sprintf(str, "Monster/Monster1/idle-walk/walk%d.png", 5 - i);
		effect[6]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 28; i++)// 공격 - 준비
	{
		sprintf(str, "Monster/Monster1/attack_ready/Attack%d.png", i);
		effect[2]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 24; ++i)// 공격
	{
		sprintf(str, "Monster/Monster1/attack/Attack%d.png", i);
		if (i == 2)
		{
			Sprite* spr = Sprite::create(str);
			effect[2]->addSpriteFrame(spr->getSpriteFrame());
			m_AttNum[0] = spr->getSpriteFrame()->getTexture()->getName();
		}
		else
			effect[2]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 4; ++i)// 공격->idle
	{
		sprintf(str, "Monster/Monster1/attack-idle/Attack%d.png", i);
		effect[2]->addSpriteFrameWithFileName(str);
	}

	for (int i = 1; i <= 18; i++)// 사망
	{
		sprintf(str, "Monster/Monster1/die/die%d.png", i);
		effect[3]->addSpriteFrameWithFileName(str);
	}

	for (int i = 1; i <= 18; i++)// 사망회귀
	{
		sprintf(str, "Monster/Monster1/die/die%d.png", 19 - i);
		effect[7]->addSpriteFrameWithFileName(str);
	}

	for (int i = 1; i <= 5; i++)// 타격
	{
		sprintf(str, "Monster/Monster1/hit0.png", i);
		effect[4]->addSpriteFrameWithFileName(str);
	}

	for (int i = 0; i < EnemyEffectNum; i++)
		CC_SAFE_RETAIN(effect[i]);

	m_MonsterNum = MonsterKind::Monster1; // 몬스터 종류 구별
	m_Death = false;
	m_AtkCheck = false;
	m_AddFirst = false;
	m_Spr = Sprite::create("Monster/Monster1/idle/Idle1.png");
	m_Rect = Sprite::create("Monster/Monster1/IdleRect.png");
	m_Rect->setVisible(ColiideRect);
	m_Weapon = Sprite::create("Enemy/Enemy2/WeaponRect.png");
	m_Weapon->setScaleX(0.9f);
	m_Weapon->setVisible(ColiideRect);

	CC_SAFE_RETAIN(m_Spr);
	CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Weapon);
}

void ObjectEnemy::CreateObject2()
{
	//애니메이션
	char str[100] = { 0 };
	//////////// 기본 캐릭터
	for (int i = 0; i < EnemyEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0)
			effect[i]->setDelayPerUnit(M2RunDly);
		else if (i == 1)
			effect[i]->setDelayPerUnit(M2IdleDly);
		else if (i == 2)
			effect[i]->setDelayPerUnit(M2AttackDly);
		else if (i == 3 || i == 5)
			effect[i]->setDelayPerUnit(M2DieDly);
		else if (i == 4)
			effect[i]->setDelayPerUnit(M2HitDly);
		else if (i == 6)//촉수
			effect[i]->setDelayPerUnit(0.03f);
	}
	for (int i = 0; i <= 15; i++)// walk
	{
		sprintf(str, "Monster/Monster2/walk/mon02_walk_%d.png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}

	for (int i = 0; i <= 13; i++)// idle
	{
		sprintf(str, "Monster/Monster2/idle/mon02_idle_%d.png", i);
		effect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i <= 36; i++)// attack
	{
		sprintf(str, "Monster/Monster2/attack/mon02_attack_%d.png", i);
		if (i == 24)
		{
			Sprite* spr = Sprite::create(str);
			effect[2]->addSpriteFrame(spr->getSpriteFrame());
			m_AttNum[0] = spr->getSpriteFrame()->getTexture()->getName();
		}
		else
			effect[2]->addSpriteFrameWithFileName(str);
	}
	effect[2]->setRestoreOriginalFrame(true);//애니메이션 종료시 원래 스프라이트로 복귀
	for (int i = 0; i <= 17; i++)// 사망
	{
		sprintf(str, "Monster/Monster2/die/mon02_die_%d.png", i);
		effect[3]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i <= 17; i++)// 사망
	{
		sprintf(str, "Monster/Monster2/die/mon02_die_%d.png", 17 - i);
		effect[5]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 5; i++)// 타격
	{
		sprintf(str, "Monster/Monster2/hit/mon02_hit_0.png", i);
		effect[4]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 34; ++i)// 촉수
	{
		sprintf(str, "Monster/Monster2/Object/object%d.png", i);
		effect[6]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i < EnemyEffectNum; i++)
		CC_SAFE_RETAIN(effect[i]);

	m_MonsterNum = MonsterKind::Monster2; // 몬스터 종류구별

	m_Death = false;
	m_AddFirst = false;
	m_AtkCheck = false;
	m_Spr = Sprite::create("Monster/Monster2/idle/mon02_idle_0.png");
	m_Rect = Sprite::create("Monster/Monster2/MonsterRect.png");
	m_Weapon = Sprite::create("Monster/Monster2/Spine.png");
	m_Weapon->setScale(1.2f);
	m_WeaponRect[0] = Sprite::create("Monster/Monster2/SpineRect.png");

	m_Rect->setVisible(ColiideRect);
	CC_SAFE_RETAIN(m_Spr);
	CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Weapon);
	CC_SAFE_RETAIN(m_WeaponRect[0]);
}

void ObjectEnemy::CreateDemon2()
{
	//애니메이션
	char str[100] = { 0 };
	//////////// 기본 캐릭터
	for (int i = 0; i < EnemyEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0)
			effect[i]->setDelayPerUnit(0.05);
		else if (i == 1)
			effect[i]->setDelayPerUnit(0.03);
		else if (i == 2)
			effect[i]->setDelayPerUnit(0.03);
		else if (i == 3)
			effect[i]->setDelayPerUnit(0.08);
		else if (i == 4)
			effect[4]->setDelayPerUnit(0.05f);
	}
	for (int i = 1; i <= 21; i++)// 달리기
	{
		sprintf(str, "Monster/Demon2/Run/Run (%d).png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 81; i++)// 울부짖기
	{
		sprintf(str, "Monster/Demon2/Howling/Howling (%d).png", i);
		effect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 49; i++)// 공격당함(피격)
	{
		sprintf(str, "Monster/Demon2/Damage/Damage (%d).png", i);
		effect[2]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 21; i++)// 공격
	{
		sprintf(str, "Monster/Demon2/Attack/Attack (%d).png", i);
		effect[3]->addSpriteFrameWithFileName(str);
	}
	//for (int i = 1; i <= 22; i++)// 빛공격
	//{
	//	sprintf(str, "Monster/Demon/Light/Light%d.png", i);
	//	if (i == 14)
	//	{
	//		Sprite* spr = Sprite::create(str);
	//		effect[4]->addSpriteFrame(spr->getSpriteFrame());
	//		m_AttNum[0] = spr->getSpriteFrame()->getTexture()->getName();
	//	}
	//	else
	//		effect[4]->addSpriteFrameWithFileName(str);
	//}

	for (int i = 0; i < EnemyEffectNum; i++)
		CC_SAFE_RETAIN(effect[i]);

	m_MonsterNum = MonsterKind::Demon2; // 몬스터 종류 구별
	m_Death = false;
	m_AtkCheck = false;
	m_AddFirst = false;
	m_Spr = Sprite::create("Monster/Demon2/Run/Run (1).png");
	m_Rect = Sprite::create("Monster/Demon/DemonRect.png");
	m_Rect->setVisible(ColiideRect);
	m_Weapon = Sprite::create("Monster/Demon/WeaponRect.png");
	m_Weapon->setVisible(ColiideRect);
	/*m_WeaponRect[0] = Sprite::create("Monster/Demon/Light/Light1.png");
	m_WeaponRect[0]->setVisible(false);
	m_WeaponRect[1] = Sprite::create("Monster/Demon/LightRect.png");
	m_WeaponRect[1]->setVisible(ColiideRect);*/

	CC_SAFE_RETAIN(m_Spr);
	CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Weapon);
	//CC_SAFE_RETAIN(m_WeaponRect[0]);
	//CC_SAFE_RETAIN(m_WeaponRect[1]);
}

void ObjectEnemy::CreateDemon()
{
	//애니메이션
	char str[100] = { 0 };
	//////////// 기본 캐릭터
	for (int i = 0; i < EnemyEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0)
			effect[i]->setDelayPerUnit(0.05);
		else if (i == 1)
			effect[i]->setDelayPerUnit(0.03);
		else if (i == 2)
			effect[i]->setDelayPerUnit(0.03);
		else if (i == 3)
			effect[i]->setDelayPerUnit(0.03);
		else if (i == 4)
			effect[4]->setDelayPerUnit(0.05f);
	}
	for (int i = 0; i <= 20; i++)// 달리기
	{
		sprintf(str, "Monster/Demon/Move/Ghost-Move_%d.png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i <= 93; i++)// 울부짖기
	{
		sprintf(str, "Monster/Demon/Howling/Ghost-Howling_%d.png", i);
		effect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i <= 39; i++)// 공격당함(피격)
	{
		sprintf(str, "Monster/Demon/Damage/Ghost-Damage_%d.png", i);
		effect[2]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i <= 39; i++)// 공격
	{
		sprintf(str, "Monster/Demon/Attack/Ghost-Attack_%d.png", i);
		effect[3]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 22; i++)// 빛공격
	{
		sprintf(str, "Monster/Demon/Light/Light%d.png", i);
		if (i == 14)
		{
			Sprite* spr = Sprite::create(str);
			effect[4]->addSpriteFrame(spr->getSpriteFrame());
			m_AttNum[0] = spr->getSpriteFrame()->getTexture()->getName();
		}
		else
			effect[4]->addSpriteFrameWithFileName(str);
	}

	for (int i = 0; i < EnemyEffectNum; i++)
		CC_SAFE_RETAIN(effect[i]);

	m_MonsterNum = MonsterKind::Demon; // 몬스터 종류 구별
	m_Death = false;
	m_AtkCheck = false;
	m_AddFirst = false;
	m_Spr = Sprite::create("Monster/Demon/Move/Ghost-Move_0.png");
	m_Rect = Sprite::create("Monster/Demon/DemonRect.png");
	m_Rect->setVisible(ColiideRect);
	m_Weapon = Sprite::create("Monster/Demon/WeaponRect.png");
	m_Weapon->setVisible(ColiideRect);
	m_WeaponRect[0] = Sprite::create("Monster/Demon/Light/Light1.png");
	m_WeaponRect[0]->setVisible(false);
	m_WeaponRect[1] = Sprite::create("Monster/Demon/LightRect.png");
	m_WeaponRect[1]->setVisible(ColiideRect);

	CC_SAFE_RETAIN(m_Spr);
	CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Weapon);
	CC_SAFE_RETAIN(m_WeaponRect[0]);
	CC_SAFE_RETAIN(m_WeaponRect[1]);
}

void ObjectEnemy::ChangeDeath()
{
	m_Death = false;
	extern EnemyManager* m_EnemyManager;
	m_EnemyManager->m_List.push_back(this);
}

void ObjectEnemy::SetPosObject(float x, float y)
{
	extern EnemyManager* m_EnemyManager;
	m_Spr->setVisible(true);

	m_Pos.x = x;
	m_Pos.y = y;
	if (m_MonsterNum == MonsterKind::Monster1)
	{
		m_HitCheck = false;
		m_Attack = false;
		m_HP = 100;
		m_CurMotionNum = 0;
		m_ATimer = 0;
		m_Timer = 0;

		m_Spr->setPosition(Vec2(x, y));
		m_Rect->setPosition(Vec2(x, y));
		m_Weapon->setPosition(Vec2(x, y));


		if (m_Death)
		{
			m_Spr->setPosition(Vec2(x, y + 40));
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[7]),
				CallFunc::create(CC_CALLBACK_0(ObjectEnemy::ChangeDeath, this)),
				NULL));
		}
		else
		{
			m_Death = false;
			m_EnemyManager->m_List.push_back(this);
		}
		if (m_AddFirst == false)
		{
			m_AddFirst = true;
			m_EnemyManager->m_layer->addChild(m_Spr, 7);
			m_EnemyManager->m_layer->addChild(m_Rect, 6);
			m_EnemyManager->m_layer->addChild(m_Weapon, 5);
		}
	}
	else if (m_MonsterNum == MonsterKind::Monster2)
	{
		m_HitCheck = false;
		m_Attack = false;
		m_HP = 100;
		m_CurMotionNum = 0;
		m_ATimer = 0;
		m_Timer = 0;

		m_Spr->setPosition(Vec2(x, y));
		m_Rect->setPosition(Vec2(x, y));
		m_Weapon->setPosition(Vec2(x, y));
		m_Weapon->setVisible(false);
		m_WeaponRect[0]->setPosition(Vec2(x, y));
		m_WeaponRect[0]->setVisible(ColiideRect);

		if (m_Death)
		{
			m_Spr->setPosition(Vec2(x, y + 30));
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[5]),
				CallFunc::create(CC_CALLBACK_0(ObjectEnemy::ChangeDeath, this)),
				NULL));
		}
		else
		{
			m_Death = false;
			m_EnemyManager->m_List.push_back(this);
		}
		if (m_AddFirst == false)
		{
			m_AddFirst = true;
			m_EnemyManager->m_layer->addChild(m_Spr, 7);
			m_EnemyManager->m_layer->addChild(m_Rect, 6);
			m_EnemyManager->m_layer->addChild(m_Weapon, 1);
			m_EnemyManager->m_layer->addChild(m_WeaponRect[0], 0);
		}
	}
	else if (m_MonsterNum == MonsterKind::Demon2)
	{
		m_HitCheck = false;
		m_Attack = false;
		m_HP = 100;
		m_CurMotionNum = 0;
		m_ATimer = 0;
		m_Timer = 0;

		m_Spr->setPosition(Vec2(x, y));
		m_Rect->setPosition(Vec2(x, y));
		m_Weapon->setPosition(Vec2(x + 300, y - 80));

		if (m_Death)
		{
			m_Spr->setPosition(Vec2(x, y));
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[0]),
				CallFunc::create(CC_CALLBACK_0(ObjectEnemy::ChangeDeath, this)),
				NULL));
		}
		else
		{
			m_Death = false;
			//m_EnemyManager->m_List.push_back(this);
		}
		if (m_AddFirst == false)
		{
			m_AddFirst = true;
			m_EnemyManager->m_layer->addChild(m_Spr, 7);
			m_EnemyManager->m_layer->addChild(m_Rect, 5);
			m_EnemyManager->m_layer->addChild(m_Weapon, 6);
		}
	}
	else if (m_MonsterNum == MonsterKind::Demon)
	{
		m_HitCheck = false;
		m_Attack = false;
		m_HP = 100;
		m_CurMotionNum = 0;
		m_ATimer = 0;
		m_Timer = 0;

		m_WeaponRect[0]->setScale(0.7f);//7680 8040
		m_WeaponRect[0]->setOpacity(200);
		m_WeaponRect[1]->setScale(0.7f);//7680 8040
		m_WeaponRect[1]->setOpacity(200);

		m_Spr->setPosition(Vec2(x, y));
		m_Rect->setPosition(Vec2(x, y));
		m_Weapon->setPosition(Vec2(x + 300, y - 80));

		if (m_Death)
		{
			m_Spr->setPosition(Vec2(x, y));
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[0]),
				CallFunc::create(CC_CALLBACK_0(ObjectEnemy::ChangeDeath, this)),
				NULL));
		}
		else
		{
			m_Death = false;
		}
		if (m_AddFirst == false)
		{
			m_AddFirst = true;
			m_EnemyManager->m_layer->addChild(m_Spr, 7);
			m_EnemyManager->m_layer->addChild(m_Rect, 5);
			m_EnemyManager->m_layer->addChild(m_Weapon, 6);
			m_EnemyManager->m_layer->addChild(m_WeaponRect[0], 7);
			m_EnemyManager->m_layer->addChild(m_WeaponRect[1], 8);

		}
	}
}

void ObjectEnemy::AnimationSwitch(int num)
{
	int trackIndex = 0;
	extern EnemyManager* m_EnemyManager;
	///////////////////////// 1번 몬스터
	if (m_MonsterNum == MonsterKind::Monster1)
	{
		if (num == EnemyMotion::LeftWalk || num == EnemyMotion::RightWalk)//걷기
		{
			if (State != num  && m_AtkCheck == false)
			{
				//CSoundManager::getInstance()->playEffect("Sound/Sound/monster1_walk.mp3", false, 1.0f);

				m_CurMotionNum = EnemyMotion::LeftWalk;
				State = EnemyMotion::LeftWalk;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[5]),
					CallFunc::create(CC_CALLBACK_0(ObjectEnemy::MonsterRun, this)), NULL));
			}
		}
		else if (num == EnemyMotion::CloseAtk)// 공격
		{
			m_CurMotionNum = num;
			State = EnemyMotion::CloseAtk;
			m_Spr->stopAllActions();
			m_Spr->setColor(Color3B(255, 255, 255));
			m_Spr->runAction(Sequence::create(Animate::create(effect[2]),
				CallFunc::create(CC_CALLBACK_0(ObjectEnemy::AtkChange, this)), NULL));
		}
		else if (num == EnemyMotion::Standing)// 서있기(기본)
		{
			if (State != num && m_AtkCheck == false)
			{
				if (State == EnemyMotion::LeftWalk || State == EnemyMotion::RightWalk)
				{
					m_CurMotionNum = num;
					State = EnemyMotion::Standing;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[6]),
						CallFunc::create(CC_CALLBACK_0(ObjectEnemy::MonsterIdle, this)), NULL));
				}
				else
				{
					m_CurMotionNum = num;
					m_Spr->setColor(Color3B(255, 255, 255));
					State = EnemyMotion::Standing;
					m_Spr->stopAllActions();
					m_Spr->runAction(RepeatForever::create(Animate::create(effect[1])));
				}
			}
		}
		else if (num == EnemyMotion::Hit)// 타격
		{
			if (State != num)
			{
				//공격시 실행하지 않음
				//if (State == EnemyMotion::CloseAtk)
					//return;
				m_AtkCheck = false;
				m_HitCheck = true;
				bool HitAct = true;
				m_CurMotionNum = num;
				State = EnemyMotion::Hit;

				m_Spr->setFlipX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? true : false);
				m_Rect->setFlipX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? true : false);
				m_Weapon->setFlipX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? true : false);

				EffectManager::getInstance()->EffectSwitch(random(4, 5), m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());

				m_Spr->stopAllActions();
				m_Rect->stopAllActions();
				m_Rect->setPositionX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? m_Rect->getPositionX() - 10 : m_Rect->getPositionX() + 10);
				for (Sprite* box : m_EnemyManager->m_Source->m_Stg1_2MBox)
				{
					if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()) &&
						box->getPositionY() > m_Rect->getPositionY() - 40)
					{
						HitAct = false;
						m_Rect->setPositionX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? m_Rect->getPositionX() + 10 : m_Rect->getPositionX() - 10);
						break;
					}
				}
				int move = ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? -10 : 10;
				if (HitAct == false)
					move = 0;

				m_Spr->setColor(Color3B(255, 0, 0));
				m_Spr->runAction(Sequence::create(
					Spawn::create(
						MoveTo::create(0.2f, Vec2(m_Spr->getPositionX() + move, m_Spr->getPositionY())),
						Animate::create(effect[4]),
						NULL),
					CallFunc::create(CC_CALLBACK_0(ObjectEnemy::ChangeHit, this)),
					NULL));
				m_Rect->runAction(Spawn::create(
					MoveTo::create(0.2f, Vec2(m_Rect->getPositionX() + move, m_Rect->getPositionY())),
					NULL));
			}
		}
		else if (num == EnemyMotion::Die)// 사망
		{
			if (State != num)
			{
				CSoundManager::getInstance()->playEffect("Sound/Sound/monster2_death.mp3", false, 1.0f);

				m_CurMotionNum = num;
				m_ATimer = m_Timer;
				State = EnemyMotion::Die;
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[3]),
					Hide::create(),
					NULL));
				RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(ObjectEnemy::EnemyDelete, this));
			}
		}
	}
	///////////////////////// 2번 몬스터
	else if (m_MonsterNum == MonsterKind::Monster2)
	{
		if (num == EnemyMotion::LeftWalk || num == EnemyMotion::RightWalk)//걷기
		{
			if (State != num  && m_AtkCheck == false)
			{
				m_CurMotionNum = EnemyMotion::LeftWalk;
				State = EnemyMotion::LeftWalk;
				m_Spr->stopAllActions();
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(ObjectEnemy::MonsterRun, this)), NULL));
			}
		}
		else if (num == EnemyMotion::CloseAtk)// 공격
		{
			//CSoundManager::getInstance()->playEffect("Sound/Sound/monster1_attack.mp3", false, 1.0f);
			m_CurMotionNum = num;
			State = EnemyMotion::CloseAtk;
			m_Spr->stopAllActions();
			m_Spr->setColor(Color3B(255, 255, 255));
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[2]),
				CallFunc::create(CC_CALLBACK_0(ObjectEnemy::AtkChange, this)),
				NULL));
		}
		else if (num == EnemyMotion::Standing)// 서있기(기본)
		{
			if (State != num && m_AtkCheck == false)
			{
				if (State == EnemyMotion::LeftWalk || State == EnemyMotion::RightWalk)
				{
					m_CurMotionNum = num;
					State = EnemyMotion::Standing;
					m_Spr->stopAllActions();
					m_Spr->setColor(Color3B(255, 255, 255));
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[1]),//보간작업 walk->idle
						CallFunc::create(CC_CALLBACK_0(ObjectEnemy::MonsterIdle, this)), NULL));
				}
				else
				{
					m_CurMotionNum = num;
					State = EnemyMotion::Standing;
					m_Spr->stopAllActions();
					m_Spr->runAction(RepeatForever::create(Animate::create(effect[1])));
				}
			}
		}
		else if (num == EnemyMotion::Hit)// 타격
		{
			if (State != num)
			{
				m_AtkCheck = false;
				m_HitCheck = true;
				bool HitAct = true;
				m_CurMotionNum = num;
				State = EnemyMotion::Hit;

				m_Spr->setFlipX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? true : false);
				m_Rect->setFlipX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? true : false);
				m_Weapon->setFlipX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? true : false);

				EffectManager::getInstance()->EffectSwitch(random(4, 5), m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());

				m_Spr->stopAllActions();
				m_Rect->stopAllActions();
				m_Rect->setPositionX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? m_Rect->getPositionX() - 10 : m_Rect->getPositionX() + 10);
				for (Sprite* box : m_EnemyManager->m_Source->m_Stg1_2MBox)
				{
					if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()) &&
						box->getPositionY() > m_Rect->getPositionY() - 40)
					{
						HitAct = false;
						m_Rect->setPositionX(ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? m_Rect->getPositionX() + 10 : m_Rect->getPositionX() - 10);
						break;
					}
				}
				int move = ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX() ? -10 : 10;
				if (HitAct == false)
					move = 0;

				m_Spr->setColor(Color3B(255, 0, 0));
				m_Spr->runAction(Sequence::create(
					Spawn::create(
						MoveTo::create(0.2f, Vec2(m_Spr->getPositionX() + move, m_Spr->getPositionY())),
						Animate::create(effect[4]),
						NULL),
					CallFunc::create(CC_CALLBACK_0(ObjectEnemy::ChangeHit, this)),
					NULL));
				m_Rect->runAction(Spawn::create(
					MoveTo::create(0.2f, Vec2(m_Rect->getPositionX() + move, m_Rect->getPositionY())),
					NULL));
			}

		}
		else if (num == EnemyMotion::Die)// 사망
		{
			if (State != num)
			{
				CSoundManager::getInstance()->playEffect("Sound/Sound/monster2_death.mp3", false, 1.0f);

				m_CurMotionNum = num;
				m_ATimer = m_Timer;
				State = EnemyMotion::Die;
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[3]),
					Hide::create(),
					NULL));
				RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(ObjectEnemy::EnemyDelete, this));
			}
		}
	}
	//// Demon2
	else if (m_MonsterNum == MonsterKind::Demon2)
	{
		if (num == EnemyMotion::LeftWalk || num == EnemyMotion::RightWalk)//걷기
		{
			if (State != num  && m_AtkCheck == false)
			{
				m_CurMotionNum = EnemyMotion::LeftWalk;
				State = EnemyMotion::LeftWalk;
				m_Spr->stopAllActions();
				m_Spr->runAction(RepeatForever::create(
					Animate::create(effect[0])));
			}
		}
		else if (num == EnemyMotion::Howling)
		{
			if (State != num)
			{
				m_CurMotionNum = EnemyMotion::Howling;
				State = EnemyMotion::Howling;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Spawn::create(Animate::create(effect[1]),
						CallFunc::create(CC_CALLBACK_0(ObjectEnemy::HowlingSound, this)), NULL),
					Repeat::create(Animate::create(effect[0]), 50), NULL));
			}
		}
		else if (num == EnemyMotion::Hit)
		{
			m_Spr->stopAllActions();
			m_Spr->runAction(Sequence::create(Animate::create(effect[2]),
				Repeat::create(Animate::create(effect[0]), 50), NULL));
		}
		else if (num == EnemyMotion::CloseAtk)
		{
			if (State != num)
			{
				m_CurMotionNum = EnemyMotion::CloseAtk;
				State = EnemyMotion::CloseAtk;
				m_Spr->stopAllActions();
				m_Spr->runAction(
					Animate::create(effect[3]));
			}
		}
	}
	else if (m_MonsterNum == MonsterKind::Demon)
	{
		if (num == EnemyMotion::LeftWalk || num == EnemyMotion::RightWalk)//걷기
		{
			if (State != num  && m_AtkCheck == false)
			{
				m_CurMotionNum = EnemyMotion::LeftWalk;
				State = EnemyMotion::LeftWalk;
				m_Spr->stopAllActions();
				m_Spr->runAction(RepeatForever::create(
					Animate::create(effect[0])));
			}
		}
		else if (num == EnemyMotion::Howling)
		{
			if (State != num)
			{
				m_CurMotionNum = EnemyMotion::Howling;
				State = EnemyMotion::Howling;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					//Repeat::create(Animate::create(effect[0]), 2),
					Spawn::create(Animate::create(effect[1]),
						CallFunc::create(CC_CALLBACK_0(ObjectEnemy::HowlingSound, this)), NULL),
					Repeat::create(Sequence::create(
						Animate::create(effect[0]),
						Spawn::create(
							Animate::create(effect[3]),
							CallFunc::create(CC_CALLBACK_0(ObjectEnemy::MakeLight, this)), NULL),
						NULL),
						50),
					NULL));
			}
		}
		else if (num == EnemyMotion::Hit)
		{
			{
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[2]),
					Repeat::create(Sequence::create(
						Animate::create(effect[0]),
						Spawn::create(
							Animate::create(effect[3]),
							CallFunc::create(CC_CALLBACK_0(ObjectEnemy::MakeLight, this)), NULL),
						NULL),
						50),
					NULL));
			}
		}
	}
}

// 악령 빛생성
void ObjectEnemy::MakeLight()
{
	if (m_Death == false)
	{
		if (ObjectHero::getInstance()->m_Rect->getPositionX() < 4880)
			m_WeaponRect[0]->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1010));
		else if (ObjectHero::getInstance()->m_OnGround && ObjectHero::getInstance()->m_Rect->getPositionX() < 7340 &&
			ObjectHero::getInstance()->m_Rect->getPositionX() >= 5250)
			m_WeaponRect[0]->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1170));
		else if (ObjectHero::getInstance()->m_Rect->getPositionX() >= 7700 && ObjectHero::getInstance()->m_Rect->getPositionX() <= 7940)
			m_WeaponRect[0]->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1000));
		else if (ObjectHero::getInstance()->m_Rect->getPositionX() >= 8040 && ObjectHero::getInstance()->m_Rect->getPositionX() <= 8400)
			m_WeaponRect[0]->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1160));
		else if (ObjectHero::getInstance()->m_Rect->getPositionX() >= 8565)
			m_WeaponRect[0]->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1240));

		m_WeaponRect[1]->setPosition(m_WeaponRect[0]->getPosition());

		m_WeaponRect[0]->runAction(Sequence::create(Show::create(),
			Animate::create(effect[4]), Hide::create(),
			NULL));
	}
}

// 몬스터2 촉수생성
void ObjectEnemy::MakeSpine()
{
	m_Weapon->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), ObjectHero::getInstance()->m_GroundPos.y + 50));
	m_WeaponRect[0]->setPosition(Vec2(m_Weapon->getPositionX(), m_Weapon->getPositionY() - 40));

	bool Colide = false;
	float ypos = 0;
	for (Sprite* box : SourceManager::getInstance()->m_metabox)
	{
		if (m_WeaponRect[0]->getBoundingBox().intersectsRect(box->getBoundingBox()))
		{
			Colide = true;
			m_WeaponRect[0]->setPosition(Vec2(-500, -500));
			ypos = box->getPositionY() + 40;
			break;
		}
	}

	m_Weapon->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), ypos));
	m_WeaponRect[0]->setPosition(Vec2(m_Weapon->getPositionX(), m_Weapon->getPositionY() - 40));

	if (Colide)
	{
		m_Weapon->runAction(Sequence::create(Show::create(),
			Animate::create(effect[6]), Hide::create(),
			NULL));

		m_WeaponRect[0]->runAction(Sequence::create(
			MoveTo::create(0.6f, Vec2(m_Weapon->getPositionX(), m_Weapon->getPositionY() + 50)),
			MoveTo::create(0.2f, Vec2(m_Weapon->getPositionX(), m_Weapon->getPositionY() - 40)),
			Place::create(Vec2(-500, -500)),
			NULL));
	}
}

// 총알삭제
void ObjectEnemy::DeleteBullet()
{
	extern EnemyManager* m_EnemyManager;
	if (m_MonsterNum == MonsterKind::Monster2)
	{
		Vector<Sprite*>::iterator iter = m_bullet.begin();
		int bulletSize = m_bullet.size();
		for (int i = 0; i < bulletSize; ++i)
		{
			iter = m_bullet.begin();
			m_EnemyManager->m_layer->removeChild(*iter);
			m_bullet.erase(iter);
		}
	}
}

// 몬스터2 총알생서
void ObjectEnemy::MakeBullet()
{
	extern EnemyManager* m_EnemyManager;

	Sprite* bullet = Sprite::createWithSpriteFrame(m_EnemyManager->m_Source->EnemyBullet->getSpriteFrame());
	if (m_Spr->isFlipX())// >>
	{
		bullet->setFlipX(true);
		bullet->setPosition(Vec2(m_Spr->getPositionX() + 80, m_Spr->getPositionY() + 00));
	}
	else if (!m_Spr->isFlipX())// <<
	{
		bullet->setFlipX(false);
		bullet->setPosition(Vec2(m_Spr->getPositionX() - 80, m_Spr->getPositionY() + 00));
	}
	bullet->setVisible(true);

	m_bullet.pushBack(bullet);
	m_EnemyManager->m_layer->addChild(bullet, 7);
}

// 공격 체크
void ObjectEnemy::AttackCheck()
{
	if (m_MonsterNum == MonsterKind::Monster1)
	{
		if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Weapon->getBoundingBox()))
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
	else if (m_MonsterNum == MonsterKind::Monster2)
	{
		MakeSpine();
		m_AtkCheck = false;
	}
}

void ObjectEnemy::MoveCharacter()
{
	extern EnemyManager* m_EnemyManager;

	// 충돌박스와 몬스터 중력체크
	int AniNum = 0;
	if (m_Death == false)
	{
		////////////////////////////////////////////////////////////////////////////////
		// 공격체크
		if (m_Spr->getTexture()->getName() == m_AttNum[0] && m_Attack == false)
		{
			m_Attack = true;
			AttackCheck();
		}
		else if (m_Spr->getTexture()->getName() != m_AttNum[0])
			m_Attack = false;
		///////////////////////////////////////////////////////////////////////////////
		// 중력 적용
		m_Rect->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() - 8));
		AniNum = EnemyMotion::LeftWalk;
		for (Sprite* box : m_EnemyManager->m_Source->m_Stg1_2MBox)
		{
			// 박스체크 : 중력으로 인한 하락체크이기 때문에 박스Y가 주인공Y 이하값 이여야 함
			if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()) && box->getPositionY() < m_Rect->getPositionY() + 50)
			{
				m_Rect->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 8));//중력으로 인해 감소한 값만큼 다시 높혀준다
				AniNum = EnemyMotion::LeftWalk;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////
		// 이동 및 공격
		//if (onGround)
		{
			if (m_HitCheck)
			{
				return;
			}
			float speed = 0.0f;
			if (m_MonsterNum == MonsterKind::Monster1)
				speed = 2.0f;
			else if (m_MonsterNum == MonsterKind::Monster2)
				speed = 1.5f;

			for (int iter : m_dir)
			{
				if (iter == EnemyMotion::CloseAtk)
					AniNum = EnemyMotion::CloseAtk;
				else if (iter == EnemyMotion::Standing)
					AniNum = EnemyMotion::Standing;
				else if (m_AtkCheck == false && (iter == EnemyMotion::RightWalk || iter == EnemyMotion::LeftWalk))
				{
					m_Rect->setPositionX((iter == EnemyMotion::RightWalk ?
						m_Rect->getPositionX() + speed : m_Rect->getPositionX() - speed));
					m_Rect->setFlipX(iter == EnemyMotion::RightWalk ? true : false);
					m_Spr->setFlipX(iter == EnemyMotion::RightWalk ? true : false);
				}

				for (Sprite* box : m_EnemyManager->m_Source->m_Stg1_2MBox)
				{
					if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()) &&
						box->getPositionY() > m_Rect->getPositionY() - 40)
					{
						if (iter == EnemyMotion::RightWalk)
						{
							if (box->getPositionX() > m_Rect->getPositionX())
								m_Rect->setPositionX(m_Rect->getPositionX() - speed);
						}
						else if (iter == EnemyMotion::LeftWalk)
						{
							if (box->getPositionX() < m_Rect->getPositionX())
								m_Rect->setPositionX(m_Rect->getPositionX() + speed);
						}

					}
				}
			}
		}
		if (m_MonsterNum == MonsterKind::Monster1)
		{
			if (m_Rect->isFlipX())
			{
				m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 00, m_Rect->getPositionY() + Monter_DifY::DifY1));
				m_Weapon->setPosition(Vec2(m_Spr->getPositionX() + 40, m_Spr->getPositionY() + 20));
			}
			else
			{
				m_Spr->setPosition(Vec2(m_Rect->getPositionX() - 00, m_Rect->getPositionY() + Monter_DifY::DifY1));
				m_Weapon->setPosition(Vec2(m_Spr->getPositionX() - 40, m_Spr->getPositionY() + 20));
			}
		}
		else if (m_MonsterNum == MonsterKind::Monster2)
		{
			if (m_Rect->isFlipX())
				m_Spr->setPosition(Vec2(m_Rect->getPositionX() + 00, m_Rect->getPositionY() + Monter_DifY::DifY2));
			else
				m_Spr->setPosition(Vec2(m_Rect->getPositionX() - 00, m_Rect->getPositionY() + Monter_DifY::DifY2));
		}
		switch (AniNum)
		{
		case EnemyMotion::LeftWalk:
		case EnemyMotion::RightWalk:
			AnimationSwitch(EnemyMotion::LeftWalk);
			break;
		case EnemyMotion::Standing:
			AnimationSwitch(EnemyMotion::Standing);
			break;
		case EnemyMotion::CloseAtk:
			AnimationSwitch(EnemyMotion::CloseAtk);
			break;
		default:
			AnimationSwitch(EnemyMotion::Standing);
			break;
		}
	}
}

void ObjectEnemy::EnemyUpdate()
{
	extern EnemyManager* m_EnemyManager;

	if (m_MonsterNum == MonsterKind::Monster2)
	{
		if (m_Weapon->isVisible())
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_WeaponRect[0]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->isFlipX() == false)
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
			}
		}
	}
	else if (m_MonsterNum == MonsterKind::Demon2)
	{
		m_Weapon->setPosition(Vec2(m_Spr->getPositionX() + 300, m_Spr->getPositionY() - 80));

	}
	else if (m_MonsterNum == MonsterKind::Demon)
	{
		m_Weapon->setPosition(Vec2(m_Spr->getPositionX() + 300, m_Spr->getPositionY() - 80));
		if (m_WeaponRect[0]->getTexture()->getName() == m_AttNum[0])
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_WeaponRect[1]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Rect->getPositionX() > m_WeaponRect[0]->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
			}
		}
	}

}
// 적 객체삭제  ( 죽음 )
void ObjectEnemy::EnemyDelete()
{
	if (m_MonsterNum == MonsterKind::Monster1)
	{
		m_Spr->setVisible(false);
		m_Rect->setVisible(false);
		m_Weapon->setVisible(false);
		m_Spr->stopAllActions();
		m_dir.clear();
		MemoryPool::getInstance()->m_Enemy1Pool.push_back(this);
		//int size = MemoryPool::getInstance()->m_Enemy1Pool.size();
		RUN_WITH_DELAY(5.0f, CC_CALLBACK_0(ObjectEnemy::ReCreateMonster, this));
	}
	else if (m_MonsterNum == MonsterKind::Monster2)
	{
		m_Spr->setVisible(false);
		m_Spr->stopAllActions();
		m_dir.clear();

		MemoryPool::getInstance()->m_Enemy2Pool.push_back(this);
		//int size = MemoryPool::getInstance()->m_Enemy2Pool.size();
		RUN_WITH_DELAY(3.0f, CC_CALLBACK_0(ObjectEnemy::ReCreateMonster, this));
	}
}

void ObjectEnemy::ReCreateMonster()
{
	if (m_MonsterNum == MonsterKind::Monster1)
	{
		ObjectEnemy* enemy3 = *MemoryPool::getInstance()->m_Enemy1Pool.begin();
		enemy3->m_dir.clear();
		enemy3->m_Death = true;
		enemy3->m_Attack = false;
		enemy3->m_HitCheck = false;
		enemy3->m_AtkCheck = false;
		enemy3->State = 0;
		MemoryPool::getInstance()->m_Enemy1Pool.erase(MemoryPool::getInstance()->m_Enemy1Pool.begin());
		enemy3->SetPosObject(m_Pos.x, m_Pos.y);
	}
	else if (m_MonsterNum == MonsterKind::Monster2)
	{
		ObjectEnemy* enemy3 = *MemoryPool::getInstance()->m_Enemy2Pool.begin();
		enemy3->m_dir.clear();
		enemy3->m_Death = true;
		enemy3->m_Attack = false;
		enemy3->m_HitCheck = false;
		enemy3->m_AtkCheck = false;
		enemy3->State = 0;
		MemoryPool::getInstance()->m_Enemy2Pool.erase(MemoryPool::getInstance()->m_Enemy2Pool.begin());
		enemy3->SetPosObject(m_Pos.x, m_Pos.y);
	}
}

void ObjectEnemy::SetMoveDir()
{
	extern Timer2* m_Timer2;

	if (m_Death == false)
	{
		if (m_MonsterNum == MonsterKind::Monster1)
		{
			if (sqrt((ObjectHero::getInstance()->m_Rect->getPositionX() - m_Rect->getPositionX())*(ObjectHero::getInstance()->m_Rect->getPositionX() - m_Rect->getPositionX()) +
				(ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY())*(ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY())) < 300
				&& ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY() < 80)
			{
				m_dir.clear();

				if (m_AtkCheck)
					return;
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Weapon->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_Rect->getPositionX() > m_Rect->getPositionX())
					{
						m_Spr->setFlipX(true);
						m_Rect->setFlipX(true);
					}
					else
					{
						m_Spr->setFlipX(false);
						m_Rect->setFlipX(false);
					}

					if (m_AtkCheck == false)
					{
						m_AtkCheck = true;
						m_dir.push_back(EnemyMotion::CloseAtk);
					}
				}
				else
				{
					if (ObjectHero::getInstance()->m_Rect->getPositionX() > m_Rect->getPositionX())
						m_dir.push_back(EnemyMotion::RightWalk);
					else
						m_dir.push_back(EnemyMotion::LeftWalk);
				}
			}
			else
			{
				if (m_Timer2->GetTime() - m_Timer > 2.0f)
				{
					m_Timer = m_Timer2->GetTime();
					randNum = random(1, 4);
					m_dir.clear();
					if (randNum == 1)
						m_dir.push_back(EnemyMotion::RightWalk);
					else if (randNum == 2)
						m_dir.push_back(EnemyMotion::LeftWalk);
					else
						m_dir.push_back(EnemyMotion::Standing);
				}
			}
		}
		else if (m_MonsterNum == MonsterKind::Monster2)
		{
			if (sqrt((ObjectHero::getInstance()->m_Rect->getPositionX() - m_Rect->getPositionX())*(ObjectHero::getInstance()->m_Rect->getPositionX() - m_Rect->getPositionX()) +
				(ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY())*(ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY())) < 500
				&& ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY() < 80)
			{
				m_dir.clear();

				if (m_AtkCheck)
					return;
				if (sqrt((ObjectHero::getInstance()->m_Rect->getPositionX() - m_Rect->getPositionX())*(ObjectHero::getInstance()->m_Rect->getPositionX() - m_Rect->getPositionX()) +
					(ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY())*(ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY())) < 300
					&& ObjectHero::getInstance()->m_Rect->getPositionY() - m_Rect->getPositionY() < 80)
				{
					if (ObjectHero::getInstance()->m_Rect->getPositionX() > m_Rect->getPositionX())
					{
						m_Spr->setFlipX(true);
						m_Rect->setFlipX(true);
					}
					else
					{
						m_Spr->setFlipX(false);
						m_Rect->setFlipX(false);
					}

					if (m_AtkCheck == false)
					{
						m_AtkCheck = true;
						m_dir.push_back(EnemyMotion::CloseAtk);
					}
				}
				else
				{
					if (ObjectHero::getInstance()->m_Rect->getPositionX() > m_Rect->getPositionX())
						m_dir.push_back(EnemyMotion::RightWalk);
					else
						m_dir.push_back(EnemyMotion::LeftWalk);
				}
			}
			else
			{
				if (m_Timer2->GetTime() - m_Timer > 2.0f)
				{
					m_Timer = m_Timer2->GetTime();
					randNum = random(1, 4);
					m_dir.clear();
					if (randNum == 1)
						m_dir.push_back(EnemyMotion::RightWalk);
					else if (randNum == 2)
						m_dir.push_back(EnemyMotion::LeftWalk);
					else
						m_dir.push_back(EnemyMotion::Standing);
				}
			}
		}
	}
}

void ObjectEnemy::SetHP(int num)
{
	m_HP += num;
	if (m_HP < 0)
		m_Death = true;
}

void ObjectEnemy::Delete()
{
	CC_SAFE_RELEASE(m_Spr);
	CC_SAFE_RELEASE(m_Rect);
	CC_SAFE_RELEASE(m_Weapon);

	for (int i = 0; i < EnemyEffectNum; ++i)
	{
		CC_SAFE_RELEASE(effect[i]);
	}

}

void ObjectEnemy::DemonDelete2()
{
	CC_SAFE_RELEASE(m_Spr);
	CC_SAFE_RELEASE(m_Rect);
	CC_SAFE_RELEASE(m_Weapon);

	for (int i = 0; i < EnemyEffectNum; ++i)
	{
		CC_SAFE_RELEASE(effect[i]);
	}
}

void ObjectEnemy::DemonDelete()
{
	CC_SAFE_RELEASE(m_Spr);
	CC_SAFE_RELEASE(m_Rect);
	CC_SAFE_RELEASE(m_Weapon);
	CC_SAFE_RELEASE(m_WeaponRect[0]);
	CC_SAFE_RELEASE(m_WeaponRect[1]);

	CC_SAFE_RELEASE(effect[0]);

	for (int i = 0; i < EnemyEffectNum; ++i)
	{
		CC_SAFE_RELEASE(effect[i]);
	}
}