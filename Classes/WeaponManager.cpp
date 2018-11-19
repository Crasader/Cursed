#include "Default.h"


WeaponManager* m_WeaponManager = new WeaponManager();

void WeaponManager::GetLayer(Layer* layer)
{
	m_layer = layer;
}

void WeaponManager::CreateMotion()
{
	static bool once = false;
	if (once == false)
	{
		once = true;

		m_MotionNum = 0;//idle
		m_WeaponNum = 0;//기본무기

		CloseWeapon = Sprite::create("Hero/BasicWeapon/Idle/idle1.png");
		//m_layer->addChild(CloseWeapon, 9);
		CC_SAFE_RETAIN(CloseWeapon);

		ForChange = Sprite::create();

		AnimationInit();
	}
	else
	{
		CloseWeapon->setOpacity(1000);
		CloseWeapon->removeFromParent();
		m_layer->addChild(CloseWeapon, 9);
	}
}

void WeaponManager::SettingWeapon(int tagNum)
{
	if (tagNum == BasicWeapon)
	{
		m_Durability = -10;
		m_WeaponNum = BasicWeapon;
		CloseWeapon->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY()));
	}
	else if (tagNum == Item::Bat)
	{
		m_Durability = 10;
		m_WeaponNum = tagNum;
		CloseWeapon->stopAllActions();
		CloseWeapon->initWithFile("Hero/Weapon1/Weapon1.png");
		CloseWeapon->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY()));
	}
	else if (tagNum == Item::Gun)
	{
		m_Durability = 10;
		m_WeaponNum = tagNum;
		CloseWeapon->stopAllActions();
	}
}

void WeaponManager::AtkMotionSwitch(int num)
{
	if (m_MotionNum == BasicWeapon)// 기본무기
	{
		Animation* ani = NULL;
		if (num == MotionNum::Dash)
			ani = beffect[7];
		else if (num == MotionNum::Stand)
			ani = beffect[1];
		else if (num == MotionNum::Move)
			ani = beffect[2];
		else if (num == MotionNum::Fall)
			ani = beffect[4];
		else if (num == MotionNum::HeroLadderUp)
			ani = beffect[6];
		else if (num == MotionNum::HeroLadderDown)
			ani = beffect[9];
		else if (num == MotionNum::HeroLadderEndUp)
			ani = beffect[10];
		else if (num == MotionNum::HeroLadderEndDown)
			ani = beffect[11];
		else if (num == MotionNum::HeroJump)
			ani = beffect[5];
		else if (num == MotionNum::Attack)
			ani = beffect[0];
		else if (num == MotionNum::HeroSkill1)
			ani = beffect[0];
		else if (num == MotionNum::HeroDamageLeft || num == MotionNum::HeroDamageRight)
			ani = beffect[1];
		else if (num == MotionNum::Nothing)
		{
			CloseWeapon->stopAllActions();
			return;
		}
		else if (num == MotionNum::HeroDeath)//
		{ 
			CloseWeapon->stopAllActions();
			CloseWeapon->setVisible(false);
			return;
		}

		//////////////////////////////////////////////////////////
		CloseWeapon->stopAllActions();
		if (num == MotionNum::Move)
		{
			CloseWeapon->runAction(RepeatForever::create(Animate::create(beffect[3])));

			/*CloseWeapon->runAction(Sequence::create(
				Animate::create(beffect[2]),
				CallFunc::create(CC_CALLBACK_0(WeaponManager::WeaponRun, this)), NULL));*/
		}
		else if (num == MotionNum::Attack)
		{
			CloseWeapon->runAction(Sequence::create(
				Animate::create(beffect[0]),
				Animate::create(beffect[8])
				, NULL));
		}
		else if(num == MotionNum::Dash)
			CloseWeapon->runAction(Animate::create(ani));
		else if (num == MotionNum::HeroLadderUp)
			CloseWeapon->runAction(Animate::create(ani));
		else if (num == MotionNum::HeroLadderDown)
			CloseWeapon->runAction(Animate::create(ani));

		else if (num == MotionNum::HeroLadderEndUp)
		{
			if (ObjectHero::getInstance()->MotionSwap)
			{
				CloseWeapon->runAction(Sequence::create(
					Animate::create(beffect[6]),
					Animate::create(ani), NULL));
			}
			else
			{
				CloseWeapon->runAction(Sequence::create(
					Animate::create(beffect[9]),
					Animate::create(ani), NULL));
			}
		}
		else if (num == MotionNum::HeroLadderEndDown)
		{
			if (ObjectHero::getInstance()->MotionSwap)
			{
				CloseWeapon->runAction(Sequence::create(
					Animate::create(ani),
					Animate::create(beffect[6]),NULL));
			}
			else
			{
				CloseWeapon->runAction(Sequence::create(
					Animate::create(ani),
					Animate::create(beffect[9]),NULL));
			}
		}
		else if (num == MotionNum::Fall)
		{
			/*Animation* one = Animation::create();
			one->addSpriteFrame(CloseWeapon->getSpriteFrame());
			one->addSpriteFrame(CloseWeapon->getSpriteFrame());
			one->setDelayPerUnit(FallDelay);*/
			CloseWeapon->runAction(Sequence::create(
				DelayTime::create(0.1f),
				//Animate::create(one),
				Animate::create(ani), NULL));
		}
		else
			CloseWeapon->runAction(RepeatForever::create(Animate::create(ani)));
	}
	//else if (m_MotionNum >= 1) // 근접무기
	//{
	//	Animation* ani = NULL;
	//	if (num == MotionNum::Dash)
	//		ani = effect[1 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::Fall)
	//		ani = effect[3 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::HeroLadderUp)
	//		ani = effect[2 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::HeroLadderDown)
	//		ani = effect[2 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::HeroJump)
	//		ani = effect[3 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::Attack)
	//	{
	//		m_Durability -= 1;
	//		ani = effect[0 + 6 * (m_MotionNum - 1)];
	//	}
	//	else if (num == MotionNum::HeroSkill1)
	//		ani = effect[0 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::Stand)
	//		ani = effect[5 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::Move)
	//		ani = effect[1 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::HeroDamageLeft || num == MotionNum::HeroDamageRight)
	//		ani = effect[1 + 6 * (m_MotionNum - 1)];
	//	else if (num == MotionNum::HeroDeath)
	//		ani = effect[1 + 6 * (m_MotionNum - 1)];
	//	CloseWeapon->stopAllActions();
	//	if (ObjectHero::getInstance()->m_Spr->isFlipX())
	//	{
	//		CloseWeapon->setFlipX(true);
	//		CloseWeapon->runAction(RepeatForever::create(Animate::create(ani)));
	//	}
	//	else
	//	{
	//		CloseWeapon->setFlipX(false);
	//		CloseWeapon->runAction(RepeatForever::create(Animate::create(ani)));
	//	}

	//}
}

void WeaponManager::FollowHero()
{
	if (ObjectHero::getInstance()->m_Spr->isFlipX())
		CloseWeapon->setFlipX(true);
	else
		CloseWeapon->setFlipX(false);
	if (m_MotionNum == BasicWeapon)
	{
		CloseWeapon->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY()));
	}
	else if (m_MotionNum == 1)// 근접 무기
	{
		CloseWeapon->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY()));
	}
	else if (m_MotionNum == 2)// 원거리 무기
	{
		CloseWeapon->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY()));
	}
}

void WeaponManager::WeaponRun()
{
	CloseWeapon->runAction(RepeatForever::create(Animate::create(beffect[3])));
}

void WeaponManager::AnimationInit()
{
	//애니메이션
	char str[100] = { 0 };

	for (int i = 0; i < WeaponEffectNum; i++)
	{
		effect[i] = Animation::create();
		effect[i]->setDelayPerUnit(0.1f);
	}
	for (int i = 0; i < BasicEffectNum; ++i)
	{
		beffect[i] = Animation::create();
		if(i == 0 || i == 8)// 공격1타 , 2타
			beffect[i]->setDelayPerUnit(BasicAttackDelay);
		else if(i == 1)// Idle
			beffect[i]->setDelayPerUnit(IdleDelay);
		else if (i == 2)// 걷기
			beffect[i]->setDelayPerUnit(WalkDelay);
		else if (i == 3)// 달리기
			beffect[i]->setDelayPerUnit(RunDelay);
		else if (i == 4)// 추락
			beffect[i]->setDelayPerUnit(FallDelay);
		else if (i == 5)// 점프
			beffect[i]->setDelayPerUnit(JumpDelay);
		else if (i == 6 || i == 9)// ladder
			beffect[i]->setDelayPerUnit(LadderDelay);
		else if (i == 10 || i == 11)// ladder end up/down
			beffect[i]->setDelayPerUnit(LadderEndDelay);
		else if(i == 7)//대쉬
			beffect[i]->setDelayPerUnit(DashDelay);
	}
	//////// 기본무기 ///////////////////////////////////////////
	for (int i = 1; i <= 7; i++)// 기본 무기 공격 모션 1타
	{
		sprintf(str, "Hero/BasicWeapon/Attack/BasicAttack%d.png", i);
		if (i == 4)//공격체크 모션
		{
			ForChange->initWithFile(str);
			beffect[0]->addSpriteFrame(ForChange->getSpriteFrame());
			m_Att[2] = ForChange->getSpriteFrame()->getTexture()->getName();
		}
		else
			beffect[0]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 7; i++)// 기본 무기 공격 모션 2타
	{
		sprintf(str, "Hero/BasicWeapon/Attack/Attack2_%d.png", i);
		if (i == 2)//공격체크 모션
		{
			ForChange->initWithFile(str);
			beffect[8]->addSpriteFrame(ForChange->getSpriteFrame());
			m_Att[3] = ForChange->getSpriteFrame()->getTexture()->getName();
		}
		else
			beffect[8]->addSpriteFrameWithFileName(str);
	}
	beffect[8]->setRestoreOriginalFrame(true);//애니메이션 종료시 원래 스프라이트로 복귀

	for (int i = 1; i <= 25; i++)// 기본 무기 Idle
	{
		sprintf(str, "Hero/BasicWeapon/Idle/idle%d.png", i);
		beffect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i <= 2; i++)// 기본 무기 Walk
	{
		sprintf(str, "Hero/BasicWeapon/Walk/weapon_idle-run_0%d.png", i);
		beffect[2]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 16; i++)// 기본 무기 Run
	{
		sprintf(str, "Hero/BasicWeapon/Run/Run%d.png", i);
		beffect[3]->addSpriteFrameWithFileName(str);
	}
	for (int i = 8; i <= 14; i++)// 기본 무기 추락
	{
		sprintf(str, "Hero/BasicWeapon/Jump/Jump%d.png", i);
		beffect[4]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 14; i++)// 기본 무기 Jump
	{
		sprintf(str, "Hero/BasicWeapon/Jump/Jump%d.png", i);
		beffect[5]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 5; i++)// 기본 무기 ladder UP
	{
		sprintf(str, "Hero/BasicWeapon/Ladder/Tick1/Ladder%d.png", i);
		beffect[6]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 5; i++)// 기본 무기 ladder Down
	{
		sprintf(str, "Hero/BasicWeapon/Ladder/Tick2/Ladder%d.png", i);
		beffect[9]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 9; i++)// 기본 무기 ladder End Up
	{
		sprintf(str, "Hero/BasicWeapon/climbdown/climb%d.png", i);
		beffect[10]->addSpriteFrameWithFileName(str);
	}
	for (int i = 9; i != 1; i--)// 기본 무기 ladder End Down
	{
		sprintf(str, "Hero/BasicWeapon/climbup/climb%d.png", i);
		beffect[11]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i <= 4; i++)// 기본 무기 Dash
	{
		sprintf(str, "Hero/BasicWeapon/Dash/weapon_dash_0%d.png", i);
		beffect[7]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i < WeaponEffectNum; ++i)
		CC_SAFE_RETAIN(effect[i]);
	for (int i = 0; i < BasicEffectNum; ++i)
		CC_SAFE_RETAIN(beffect[i]);
}