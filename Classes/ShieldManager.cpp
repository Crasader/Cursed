#include "Default.h"

ShieldManager* m_ShieldManager = new ShieldManager;

void ShieldManager::GetLayer(Layer* layer)
{
	m_layer = layer;
}

void ShieldManager::CreateMotion()
{
	static bool once = false;
	if (once == false)
	{
		once = true;
		m_MotionNum = 0;//idle
		for (int i = 0; i < 3; ++i)
		{
			m_Hard[i] = 0;
			m_Shield[i] = Sprite::create();
			//m_layer->addChild(m_Shield[i], 10);
			CC_SAFE_RETAIN(m_Shield[i]);
		}
		AnimationInit();
	}
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			m_Shield[i]->removeFromParent();
			m_layer->addChild(m_Shield[i], 10);
		}
	}
}

void ShieldManager::SettingShield(int tagNum)
{
	// 상의 = 3
	if (tagNum / 10 == 3)
	{
		if (tagNum == Shield::Head1)
		{
			m_Hard[0] = 100;
			m_Shield[0]->initWithFile("Item/Head/Head1.png");
			m_Shield[0]->setTag(tagNum);
			m_Shield[0]->setVisible(true);
			m_Shield[0]->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY() + 70));
			//m_layer->addChild(m_Shield[0], 10);
		}
	}
	else if (tagNum / 10 == 5)// 하의
	{
		if (tagNum == Shield::Top1)
		{
			m_Hard[1] = 100;
			m_Shield[1]->initWithFile("Item/Top/Top1.png");
			m_Shield[1]->setTag(tagNum);
			m_Shield[1]->setVisible(true);
			m_Shield[1]->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY() - 20));
			//m_layer->addChild(m_Shield[1], 10);
		}
	}
	else if (tagNum / 10 == 7)// 무릅
	{
		if (tagNum == Shield::Bottom1)
		{
			m_Hard[2] = 100;
			m_Shield[2]->initWithFile("Item/Bottom/Bottom1.png");
			m_Shield[2]->setTag(tagNum);
			m_Shield[2]->setVisible(true);
			m_Shield[2]->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY() - 60));
			//m_layer->addChild(m_Shield[2], 10);
		}
	}
}

void ShieldManager::MotionSwitch(int num)
{
	Animation* ani = NULL;
	for (int i = 0; i < 3; ++i)
	{
		if (ObjectHero::getInstance()->m_Shield[0])
		{
			if (num == MotionNum::Dash)
				ani = effect[0];
			else if (num == MotionNum::Fall)
				ani = effect[0];
			else if (num == MotionNum::HeroLadderUp)
				ani = effect[0];
			else if (num == MotionNum::HeroLadderDown)
				ani = effect[0];
			else if (num == MotionNum::HeroJump)
				ani = effect[0];
			else if (num == MotionNum::Attack)
				ani = effect[0];
			else if (num == MotionNum::HeroSkill1)
				ani = effect[0];
			else if (num == MotionNum::Stand)
				ani = effect[0];
			else if (num == MotionNum::Move)
				ani = effect[0];
			else if (num == MotionNum::HeroDamageLeft || num == MotionNum::HeroDamageRight)
				ani = effect[0];
			else if (num == MotionNum::HeroDeath)
				ani = effect[0];
			else if (num == MotionNum::Stand)
				ani = effect[0];
			m_Shield[0]->stopAllActions();
			m_Shield[0]->runAction(RepeatForever::create(Animate::create(ani)));
		}
		else if (ObjectHero::getInstance()->m_Shield[1])
		{
			if (num == MotionNum::Dash)
				ani = effect[1];
			else if (num == MotionNum::Fall)
				ani = effect[1];
			else if (num == MotionNum::HeroLadderUp)
				ani = effect[1];
			else if (num == MotionNum::HeroLadderDown)
				ani = effect[1];
			else if (num == MotionNum::HeroJump)
				ani = effect[1];
			else if (num == MotionNum::Attack)
				ani = effect[1];
			else if (num == MotionNum::HeroSkill1)
				ani = effect[1];
			else if (num == MotionNum::Stand)
				ani = effect[1];
			else if (num == MotionNum::Move)
				ani = effect[1];
			else if (num == MotionNum::HeroDamageLeft || num == MotionNum::HeroDamageRight)
				ani = effect[1];
			else if (num == MotionNum::HeroDeath)
				ani = effect[1];
			else if (num == MotionNum::Stand)
				ani = effect[1];
			m_Shield[1]->stopAllActions();
			m_Shield[1]->runAction(RepeatForever::create(Animate::create(ani)));
		}
		else if (ObjectHero::getInstance()->m_Shield[2])
		{
			if (num == MotionNum::Dash)
				ani = effect[2];
			else if (num == MotionNum::Fall)
				ani = effect[2];
			else if (num == MotionNum::HeroLadderUp)
				ani = effect[2];
			else if (num == MotionNum::HeroLadderDown)
				ani = effect[2];
			else if (num == MotionNum::HeroJump)
				ani = effect[2];
			else if (num == MotionNum::Attack)
				ani = effect[2];
			else if (num == MotionNum::HeroSkill1)
				ani = effect[2];
			else if (num == MotionNum::Stand)
				ani = effect[2];
			else if (num == MotionNum::Move)
				ani = effect[2];
			else if (num == MotionNum::HeroDamageLeft || num == MotionNum::HeroDamageRight)
				ani = effect[2];
			else if (num == MotionNum::HeroDeath)
				ani = effect[2];
			else if (num == MotionNum::Stand)
				ani = effect[2];
			m_Shield[2]->stopAllActions();
			m_Shield[2]->runAction(RepeatForever::create(Animate::create(ani)));
		}
	}
}

void ShieldManager::FollowHero()
{
	for (int i = 0; i < 3; ++i)
	{
		if (ObjectHero::getInstance()->m_Spr->isFlipX())
			m_Shield[i]->setFlipX(true);
		else
			m_Shield[i]->setFlipX(false);

		if(i == 0 && ObjectHero::getInstance()->m_Shield[i])
			m_Shield[i]->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY() + 70));
		else if(i == 1 && ObjectHero::getInstance()->m_Shield[i])
			m_Shield[i]->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY() - 20));
		else if(i == 2 && ObjectHero::getInstance()->m_Shield[i])
			m_Shield[i]->setPosition(Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY() - 60));
	}
}

void ShieldManager::AnimationInit()
{
	//애니메이션
	char str[100] = { 0 };

	for (int i = 0; i < ShieldMotionNum; i++)
	{
		effect[i] = Animation::create();
		effect[i]->setDelayPerUnit(0.1f);
	}
	for (int i = 1; i <= 4; i++)// 상의1 걷기
	{
		sprintf(str, "Item/Head/Head1.png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 4; i++)// 하의
	{
		sprintf(str, "Item/Top/Top1.png", i);
		effect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 1; i <= 4; i++)// 갑주
	{
		sprintf(str, "Item/Bottom/Bottom1.png", i);
		effect[2]->addSpriteFrameWithFileName(str);
	}
	for (int i = 0; i < ShieldMotionNum; ++i)
		CC_SAFE_RETAIN(effect[i]);
}