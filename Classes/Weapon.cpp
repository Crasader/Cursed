#include "Default.h"

void Weapon::FollowHero()
{
	if (ObjectHero::getInstance()->m_Spr->isFlipX())
		m_Spr->setFlipX(true);
	else
		m_Spr->setFlipX(false);

	//if (m_MotionNum == BasicWeapon)
	{
		m_Spr->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY()));
	}
	//else if (m_MotionNum == 1)// 근접 무기
	//{
	//	CloseWeapon->setPosition(Vec2(Hero->m_Spr->getPositionX(), Hero->m_Spr->getPositionY()));
	//}
	//else if (m_MotionNum == 2)// 원거리 무기
	//{
	//	CloseWeapon->setPosition(Vec2(Hero->m_Spr->getPositionX(), Hero->m_Spr->getPositionY()));
	//}
}

void Weapon::WeaponRun()
{
	m_Spr->runAction(RepeatForever::create(Animate::create(m_Effect[3])));
}

void Weapon::SetWeapon(int tag)
{
	if (tag == BasicWeapon)
	{
		m_Spr = Sprite::create("Hero/BasicWeapon/Idle/idle1.png");
		ObjectHero::getInstance()->m_layer->addChild(m_Spr, 9);
	}
}

void Weapon::AnimationSwitch(int num)
{
	static int State;
	if (State != num && num == BasicWeapon)// 기본무기
	{
		State = num;
		Animation* ani = NULL;
		if (num == MotionNum::Dash)
			ani = m_Effect[3];
		else if (num == MotionNum::Stand)
			ani = m_Effect[1];
		else if (num == MotionNum::Move)
			ani = m_Effect[2];
		else if (num == MotionNum::Fall)
			ani = m_Effect[4];
		else if (num == MotionNum::HeroLadderUp)
			ani = m_Effect[6];
		else if (num == MotionNum::HeroLadderDown)
			ani = m_Effect[6];
		else if (num == MotionNum::HeroJump)
			ani = m_Effect[5];
		else if (num == MotionNum::Attack)
			ani = m_Effect[0];
		else if (num == MotionNum::HeroSkill1)
			ani = m_Effect[0];
		else if (num == MotionNum::HeroDamageLeft || num == MotionNum::HeroDamageRight)
			ani = m_Effect[1];
		else if (num == MotionNum::HeroDeath)//
			ani = m_Effect[1];
		m_Spr->stopAllActions();
		//if (num == MotionNum::Move)
		//{
		//	if (Hero->m_Spr->isFlipX())
		//		m_Spr->setFlipX(true);
		//	else
		//		m_Spr->setFlipX(false);
		//	m_Spr->runAction(RepeatForever::create(Animate::create(m_Effect[3])));

		//	//m_Spr->runAction(Sequence::create(
		//	//	RepeatForever::create(Animate::create(m_Effect[3])),
		//	//	//CallFunc::create(CC_CALLBACK_0(Weapon::WeaponRun, this)),
		//	//	NULL));
		//}
		//else
		{
			if (ObjectHero::getInstance()->m_Spr->isFlipX())
				m_Spr->setFlipX(true);
			else
				m_Spr->setFlipX(false);
			m_Spr->runAction(RepeatForever::create(Animate::create(ani)));
		}
	}
}

void Weapon::AniInit(int tag)
{
	static bool first;
		
	if (first == false)
	{
		first = true;
		//애니메이션
		char str[100] = { 0 };
		ForChange = Sprite::create();
		for (int i = 0; i < WeaponAniNum; ++i)
		{
			m_Effect[i] = Animation::create();
			if (i == 0)// 공격
				m_Effect[i]->setDelayPerUnit(BasicAttackDelay);
			else if (i == 1)// Idle
				m_Effect[i]->setDelayPerUnit(IdleDelay);
			else if (i == 2)// 걷기
				m_Effect[i]->setDelayPerUnit(WalkDelay);
			else if (i == 3)// 달리기
				m_Effect[i]->setDelayPerUnit(RunDelay);
			else if (i == 4)// 추락
				m_Effect[i]->setDelayPerUnit(FallDelay);
			else if (i == 5)// 점프
				m_Effect[i]->setDelayPerUnit(JumpDelay);
			else if (i == 6)// ladder
				m_Effect[i]->setDelayPerUnit(LadderDelay);
		}
		//////// 기본무기 ///////////////////////////////////////////
		for (int i = 1; i <= 7; i++)// 기본 무기 공격 모션
		{
			sprintf(str, "Hero/BasicWeapon/Attack/BasicAttack%d.png", i);
			if (i == 4)//공격체크 모션
			{
				ForChange->initWithFile(str);
				m_Effect[0]->addSpriteFrame(ForChange->getSpriteFrame());
				m_Att[0] = ForChange->getSpriteFrame()->getTexture()->getName();
			}
			else
				m_Effect[0]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 25; i++)// 기본 무기 Idle
		{
			sprintf(str, "Hero/BasicWeapon/Idle/idle%d.png", i);
			m_Effect[1]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i <= 2; i++)// 기본 무기 Walk
		{
			sprintf(str, "Hero/BasicWeapon/Walk/weapon_idle-run_0%d.png", i);
			m_Effect[2]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 16; i++)// 기본 무기 Run
		{
			sprintf(str, "Hero/BasicWeapon/Run/Run%d.png", i);
			m_Effect[3]->addSpriteFrameWithFileName(str);
		}
		for (int i = 8; i <= 14; i++)// 기본 무기 추락
		{
			sprintf(str, "Hero/BasicWeapon/Jump/Jump%d.png", i);
			m_Effect[4]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 14; i++)// 기본 무기 Jump
		{
			sprintf(str, "Hero/BasicWeapon/Jump/Jump%d.png", i);
			m_Effect[5]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i <= 7; i++)// 기본 무기 ladder
		{
			sprintf(str, "Hero/BasicWeapon/Ladder/weapon_ladder_0%d.png", i);
			m_Effect[6]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i < WeaponAniNum; ++i)
			CC_SAFE_RETAIN(m_Effect[i]);
	}
}
