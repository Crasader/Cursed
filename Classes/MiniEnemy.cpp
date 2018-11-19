#include "Default.h"

void MiniEnemy::CreateColony()
{
	m_MonsterNum = MiniMonster::Colony;
	m_HP = 1000;
	m_Death = false;

	//애니메이션
	char str[100] = { 0 };
	for (int i = 0; i < MiniEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0)
			effect[i]->setDelayPerUnit(BombMoveDly);
	}

	for (int i = 1; i <= 14; i++)// walk
	{
		sprintf(str, "Monster/Colony/Attack/Attack (%d).png", i);
		effect[0]->addSpriteFrameWithFile(str);
	}

	m_Spr = Sprite::create("Monster/Colony/Attack/Attack (1).png");
	m_Spr->setScale(0.6f);
	//m_Rect = Sprite::create("Monster/Bombbug/SampleRect.png");
	//m_Rect->setVisible(ColiideRect);

	//CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Spr);

	for (int i = 0; i < MiniEffectNum; ++i)
		CC_SAFE_RETAIN(effect[i]);
}

void MiniEnemy::CreateBombbug()
{
	//
	m_MonsterNum = MiniMonster::Bombbug;
	m_HP = 10;
	m_Death = false;
	m_AddFirst = false;
	m_CurMotion = 0;
	//애니메이션
	char str[100] = { 0 };
	for (int i = 0; i < MiniEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0)
			effect[i]->setDelayPerUnit(BombMoveDly);
	}

	for (int i = 0; i <= 7; i++)// walk
	{
		sprintf(str, "Monster/Bombbug/walk/mon_05-walk_%d.png", i);
		effect[0]->addSpriteFrameWithFile(str);
	}

	for (int i = 0; i < MiniEffectNum; ++i)
		CC_SAFE_RETAIN(effect[i]);

	m_Spr = Sprite::create("Monster/Bombbug/Sample.png");
	m_Rect = Sprite::create("Monster/Bombbug/SampleRect.png");
	m_Rect->setVisible(ColiideRect);

	CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Spr);
}

void MiniEnemy::CreateLadybug()
{
	//정보
	m_MonsterNum = MiniMonster::Ladybug;
	m_HP = 100;
	m_Death = false;
	m_AddFirst = false;
	m_CurMotion = 0;
	m_OnGround = false;
	m_RunAct = false;
	m_RunAct2 = false;
	m_Boom = false;
	//애니메이션
	char str[100] = { 0 };
	
	for (int i = 0; i < MiniEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0)
			effect[i]->setDelayPerUnit(BugUnburrowDly);
		else if (i == 1)
			effect[i]->setDelayPerUnit(BugRunDly);
		else if (i == 2)
			effect[i]->setDelayPerUnit(BugAttackDly);
	}

	for (int i = 1; i <= 24; i++)// unburrow
	{
		sprintf(str, "Monster/Ladybug/unburrow/unburrow%d.png", i);
		effect[0]->addSpriteFrameWithFile(str);
	}
	for (int i = 1; i <= 16; i++)// walk
	{
		sprintf(str, "Monster/Ladybug/walk/walk%d.png", i);
		effect[1]->addSpriteFrameWithFile(str);
	}
	for (int i = 1; i <= 36; i++)// attack
	{
		sprintf(str, "Monster/Ladybug/attack/attack%d.png", i);
		effect[2]->addSpriteFrameWithFile(str);
	}
	for(int i = 0; i < MiniEffectNum; ++i)
		CC_SAFE_RETAIN(effect[i]);

	m_Spr = Sprite::create("Monster/Ladybug/LadyBug.png");
	m_Rect = Sprite::create("Monster/Ladybug/DummyRect.png");
	m_Rect->setVisible(ColiideRect);

	CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Spr);
}

void MiniEnemy::CreateBat()
{
	//정보
	m_MonsterNum = MiniMonster::Batbug;
	m_HP = 100;
	m_Hit = false;
	m_Death = false;
	m_AddFirst = false;
	m_CurMotion = 0;
	m_OnGround = false;
	m_RunAct = false;
	m_RunAct2 = false;
	m_Boom = false;
	//애니메이션
	char str[100] = { 0 };

	for (int i = 0; i < MiniEffectNum; i++)
	{
		effect[i] = Animation::create();
		if (i == 0)
			effect[i]->setDelayPerUnit(0.035f);
		else if( i == 1 )
			effect[i]->setDelayPerUnit(0.05f);
	}

	for (int i = 1; i <= 21; i++)// idle
	{
		sprintf(str, "Monster/Bat/idle/bat_run_%d.png", i);
		effect[0]->addSpriteFrameWithFile(str);
	}
	
	for (int i = 1; i <= 5; i++)// Hit
	{
		sprintf(str, "Monster/Bat/Hit.png", i);
		effect[1]->addSpriteFrameWithFile(str);
	}

	for (int i = 0; i < MiniEffectNum; ++i)
		CC_SAFE_RETAIN(effect[i]);

	m_Spr = Sprite::create("Monster/Bat/idle/bat_run_1.png");
	m_Rect = Sprite::create("Monster/Bat/SampleRect.png");
	m_Rect->setVisible(ColiideRect);

	CC_SAFE_RETAIN(m_Rect);
	CC_SAFE_RETAIN(m_Spr);
}

void MiniEnemy::SetColony(bool flip, float Angle)
{
	if (flip)
	{
		m_Spr->setFlipX(true);
		m_Spr->setPositionX(m_Spr->getPositionX() + 50);
	}
}

void MiniEnemy::SetPosObject(float x, float y)
{
	extern EnemyManager* m_EnemyManager;

	if (m_MonsterNum == MiniMonster::Ladybug)
	{
		m_Rect->setPosition(Vec2(x, y + 85));
		m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + Mini_DifY::LadyDifY));

		m_EnemyManager->m_MiniList.push_back(this);

		m_Rect->removeFromParent();
		m_Spr->removeFromParent();
		m_SavePos = m_Rect->getPosition();

		//if (m_AddFirst == false)
		{
			//m_AddFirst = true;
			m_EnemyManager->m_layer->addChild(m_Spr, 1);
			m_EnemyManager->m_layer->addChild(m_Rect, 6);
		}
	}
	else if (m_MonsterNum == MiniMonster::Bombbug)
	{
		m_Rect->setPosition(Vec2(x + 40, y + 57));
		m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		m_Spr->setName("Bombbug");
		m_EnemyManager->m_MiniList.push_back(this);

		m_TargetPos = Vec2(x , y - 80);
		if (m_AddFirst == false)
		{
			m_AddFirst = true;
			m_EnemyManager->m_layer->addChild(m_Spr, 7);
			m_EnemyManager->m_layer->addChild(m_Rect, 6);
		}
		static float delay;
		delay += 0.5;
		BombBugRotate(m_Spr, delay);
		BombBugRotate(m_Rect, delay);
	}
	else if (m_MonsterNum == MiniMonster::Batbug)
	{
		m_TargetPos = Vec2(x, y);
		m_Rect->setPosition(Vec2(x , y ));
		m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));
		m_Spr->setName("Batbug");
		m_EnemyManager->m_ColideMini.push_back(this);

		if (m_AddFirst == false)
		{
			m_AddFirst = true;
			m_EnemyManager->m_layer->addChild(m_Spr, 7);
			m_EnemyManager->m_layer->addChild(m_Rect, 6);
		}
		MoveBat(m_Spr, 0);
	}
	else if (m_MonsterNum == MiniMonster::Colony)
	{
		m_Spr->setPosition(Vec2(x+15, y+35));
		m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));

		m_EnemyManager->m_MiniList.push_back(this);
		m_Spr->removeFromParent();

		m_EnemyManager->m_layer->addChild(m_Spr, 1);
	}
}

void MiniEnemy::MoveBat(Sprite* sender, float delay)
{
	auto TopLeft = MoveTo::create(random(2, 3), Vec2(m_TargetPos.x - 800, m_TargetPos.y + 400));

	auto MidLeft = MoveTo::create(random(1, 2), Vec2(m_TargetPos.x - 1000, m_TargetPos.y));

	auto BottomLeft = MoveTo::create(random(1, 2), Vec2(m_TargetPos.x - 800, m_TargetPos.y - 400));

	auto MidZero = MoveTo::create(random(2, 3), Vec2(m_TargetPos.x, m_TargetPos.y));

	auto TopRight = MoveTo::create(random(2, 3), Vec2(m_TargetPos.x + 800, m_TargetPos.y + 400));

	auto MidRight = MoveTo::create(random(1, 2), Vec2(m_TargetPos.x + 1000, m_TargetPos.y));

	auto BottomRight = MoveTo::create(random(1, 2), Vec2(m_TargetPos.x + 800, m_TargetPos.y - 400));

	if (sender->getName() == "Batbug")
	{
		sender->stopAllActions();
		sender->runAction(RepeatForever::create(Animate::create(effect[0])));
		m_Rect->runAction(Sequence::create(
			TopLeft, MidLeft, BottomLeft, MidZero, TopRight, MidRight,
			BottomRight, MidZero, CallFunc::create(CC_CALLBACK_0(MiniEnemy::BackMove, this)),
			NULL));
	}
}

void MiniEnemy::BombBugRotate(Sprite* sender, float delay)
{
	auto TopLeft = Sequence::create(
		MoveTo::create(0.25f - delay*0.05, Vec2(sender->getPositionX() - 30, sender->getPositionY())),
		NULL);

	auto TopLeftRotate = Spawn::create(
		MoveTo::create(0.3f - delay*0.05, Vec2(sender->getPositionX() - 63, sender->getPositionY() - 15)),
		RotateBy::create(0.3f - delay*0.05, Vec3(0, 0, -45)), NULL);

	auto TopLeftMid = Spawn::create(
		MoveTo::create(0.3f - delay*0.05, Vec2(sender->getPositionX() - 95, sender->getPositionY() - 50)),
		RotateBy::create(0.3f - delay*0.05, Vec3(0, 0, -45)), NULL);

	auto LeftMid = MoveTo::create(0.5f - delay*0.05, Vec2(sender->getPositionX() - 95, sender->getPositionY() - 110));

	auto DownLeftRotate = Spawn::create(
		MoveTo::create(0.3f - delay*0.05, Vec2(sender->getPositionX() - 83, sender->getPositionY() - 150)),
		RotateBy::create(0.3f - delay*0.05, Vec3(0, 0, -45)), NULL);

	auto DownLeft = Spawn::create(
		MoveTo::create(0.3f - delay*0.05, Vec2(sender->getPositionX() - 43, sender->getPositionY() - 180)),
		RotateBy::create(0.3f - delay*0.05, Vec3(0, 0, -45)), NULL);

	auto DownMid = MoveTo::create(1.2f, Vec2(sender->getPositionX() + 105, sender->getPositionY() - 180));

	auto DownRightRotate = Spawn::create(
		MoveTo::create(0.3f - delay*0.1, Vec2(sender->getPositionX() + 145, sender->getPositionY() - 155)),
		RotateBy::create(0.3f - delay*0.1, Vec3(0, 0, -45)), NULL);

	auto RightRotate = Spawn::create(
		MoveTo::create(0.3f - delay*0.05, Vec2(sender->getPositionX() + 175, sender->getPositionY() - 125)),
		RotateBy::create(0.3f - delay*0.05, Vec3(0, 0, -45)), NULL);

	auto RightMid = MoveTo::create(0.5f - delay*0.05, Vec2(sender->getPositionX() + 175, sender->getPositionY() - 60));

	auto TopRightRotate = Spawn::create(
		MoveTo::create(0.3f - delay*0.05, Vec2(sender->getPositionX() + 150, sender->getPositionY() - 27)),
		RotateBy::create(0.3f - delay*0.05, Vec3(0, 0, -45)), NULL);

	auto TopRightRotate2 = Spawn::create(
		MoveTo::create(0.3f - delay*0.05, Vec2(sender->getPositionX() + 100, sender->getPositionY())),
		RotateBy::create(0.3f - delay*0.05, Vec3(0, 0, -45)), NULL);

	auto TopRight = MoveTo::create(0.8f - delay*0.05, Vec2(sender->getPositionX(), sender->getPositionY()));

	if (sender->getName() == "Bombbug")
	{
		sender->runAction(RepeatForever::create(Animate::create(effect[0])));
		sender->runAction(RepeatForever::create(
				Sequence::create(
					TopLeft, TopLeftRotate, TopLeftMid,
					LeftMid, DownLeftRotate, DownLeft, DownMid, DownRightRotate, RightRotate,
					RightMid, TopRightRotate, TopRightRotate2, TopRight, NULL)));
	}
	else
	{
		sender->runAction(RepeatForever::create(Sequence::create(
				TopLeft, TopLeftRotate, TopLeftMid,
				LeftMid, DownLeftRotate, DownLeft, DownMid, DownRightRotate, RightRotate,
				RightMid, TopRightRotate, TopRightRotate2, TopRight, NULL)));
	}
}

void MiniEnemy::AnimationSwitch(int num)
{
	if (m_MonsterNum == MiniMonster::Ladybug)
	{
		if (num == MiniMotion::Run)
		{
			if (m_CurMotion != num)
			{
				m_CurMotion = num;
				m_Spr->stopAllActions();
				m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
			}
		}
	}
	else if (m_MonsterNum == MiniMonster::Batbug)
	{
		if (num == MiniMotion::MiniHit)
		{
			if (m_CurMotion != num)
			{
				m_CurMotion = num;
				//m_Hit = true;
				m_Spr->stopAllActions();
				m_Rect->stopAllActions();
				m_Spr->setColor(Color3B::RED);
				m_Spr->runAction(Animate::create(effect[1]));
				m_Spr->runAction(Sequence::create(DelayTime::create(0.25f),
					TintTo::create(0.0f,Color3B(255,255,255)),
					CallFunc::create(CC_CALLBACK_0(MiniEnemy::BackMove,this)),
					NULL));
			}
		}
		else if (num == MiniMotion::MiniDeath)
		{
			if (m_CurMotion != num)
			{
				m_CurMotion = num;
				m_Spr->setColor(Color3B(255, 255, 255));
				m_Spr->stopAllActions();
				m_Rect->stopAllActions();
				m_Spr->runAction(Sequence::create(FadeOut::create(0.5f),
					Hide::create(), NULL));
			}
		}
	}
}

void MiniEnemy::MiniUpdate()
{
	if (m_MonsterNum == MiniMonster::Ladybug)
		LadyBugUpdate();
	else if (m_MonsterNum == MiniMonster::Bombbug )
	{
		if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
		{
			if (ObjectHero::getInstance()->m_HeroHit == false)
			{
				if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
					ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
				else
					ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				ObjectHero::getInstance()->SetHP(-10);
			}
		}
	}
	else if (m_MonsterNum == MiniMonster::Batbug)
	{
		m_Spr->setPosition(m_Rect->getPosition());
		if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
		{
			if (ObjectHero::getInstance()->m_HeroHit == false)
			{
				if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
					ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
				else
					ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				ObjectHero::getInstance()->SetHP(-10);
			}
		}
	}
}

void MiniEnemy::LadyBugUpdate()
{
	if (m_Death)
		return;
	m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + Mini_DifY::LadyDifY));
	Vec2 HeroPos = ObjectHero::getInstance()->m_Rect->getPosition();
	if (m_OnGround == false && m_RunAct == false)
	{
		float y = m_Rect->getPositionY();
		if (sqrt((HeroPos.x - m_Rect->getPositionX())*(HeroPos.x - m_Rect->getPositionX()) +
			(HeroPos.y - m_Rect->getPositionY())*(HeroPos.y - m_Rect->getPositionY())) < 500 &&
			(HeroPos.y - (m_Rect->getPositionY()+90)) < 10)
		{
			CSoundManager::getInstance()->playEffect("Sound/Sound/ladybug_unburrow.mp3", false, 0.8f);
			m_OnGround = true;
			m_Spr->stopAllActions();
			m_Spr->runAction(Animate::create(effect[0]));
			m_Spr->setFlipX(ObjectHero::getInstance()->m_Rect->getPositionX() < m_Rect->getPositionX() ? false : true);
			m_Rect->setFlipX(ObjectHero::getInstance()->m_Rect->getPositionX() < m_Rect->getPositionX() ? false : true);
			m_Rect->runAction(Sequence::create(
				EaseIn::create(MoveTo::create(0.8f, Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 35)),2.0f), 
					CallFunc::create(CC_CALLBACK_0(MiniEnemy::ChangeState,this)), NULL));
		}
	}
	else if (m_OnGround)
	{
		if (m_RunAct2)//충돌애니메이션
		{
			extern EnemyManager* m_EnemyManager;
			for (Sprite* box : m_EnemyManager->m_Source->m_Stg1_2MBox)
			{
				if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()))
				{
					m_Rect->stopAllActions();
					m_Boom = true;
					m_Death = true;
					m_RunAct2 = false;
					m_Spr->stopAllActions();
					m_Spr->runAction(Sequence::create(
						Animate::create(effect[2]),
						CallFunc::create(CC_CALLBACK_0(MiniEnemy::ColideCheck, this)),
						Hide::create(), NULL));
					EffectManager::getInstance()->EffectSwitch(EffectName::LadyBugBoom, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX(), 1.0f);
					break;
				}
			}
		}
		if (m_RunAct)
		{
			float speed = abs(ObjectHero::getInstance()->m_Rect->getPositionX() - m_Rect->getPositionX()) * 0.0025f;
			m_TargetPos = HeroPos;
			m_Spr->setZOrder(7);
			m_RunAct = false;
			m_Spr->stopAllActions();
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[1])));
			m_Rect->runAction(Sequence::create(
				EaseIn::create(MoveTo::create(speed, Vec2(m_TargetPos.x, m_Rect->getPositionY())), 3.0f),
				CallFunc::create(CC_CALLBACK_0(MiniEnemy::ChangeBoom, this)), NULL));
		}
		else
		{
			//주인공과 충돌하거나 이동할 목표지점 까지 이동한경우(m_Boom) 폭발함
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()) || m_Boom )
			{
				m_Rect->stopAllActions();
				m_Boom = true;
				m_Death = true;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[2]),
					CallFunc::create(CC_CALLBACK_0(MiniEnemy::ColideCheck, this)),
					Hide::create(), NULL));
				EffectManager::getInstance()->EffectSwitch(EffectName::LadyBugBoom, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX(), 1.0f);
			}
		}
		
	}
}

void MiniEnemy::ColideCheck()
{
	CSoundManager::getInstance()->playEffect("Sound/Sound/ladybug_exploding.mp3", false, 1.0f);

	if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
	{
		ObjectHero::getInstance()->SetHP(-10);
	}
}

void MiniEnemy::Recreate()
{
	if (m_MonsterNum == MiniMonster::Ladybug && m_Death)
	{
		m_HP = 100;
		m_Death = false;
		m_AddFirst = false;
		m_CurMotion = 0;
		m_OnGround = false;
		m_RunAct = false;
		m_RunAct2 = false;
		m_Boom = false;
		m_TargetPos = Vec2(0, 0);

		m_Spr->setZOrder(0);
		m_Rect->setPosition(m_SavePos);

		m_Rect->stopAllActions();
		m_Spr->stopAllActions();
		m_Spr->setVisible(true);
	}
}

void MiniEnemy::Delete()
{
	for (int i = 0; i < MiniEffectNum; ++i)
	{
		CC_SAFE_RELEASE(effect[i]);
	}

	if(m_MonsterNum != MiniMonster::Colony)
		CC_SAFE_RELEASE(m_Rect);
	CC_SAFE_RELEASE(m_Spr);
}