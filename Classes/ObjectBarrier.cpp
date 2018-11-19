#include "Default.h"

void ObjectBarrier::SetOption(float distance, float delay, float delay2, float Speed)
{
	extern BarrierManager* m_BarrierManager;
	m_delay = delay;
	m_Speed = Speed;
	m_distance = distance;
	Sprite* foract = Sprite::create();
	//첫 액션 스타트 delay2
	foract->runAction(Sequence::create(
		DelayTime::create(delay2), CallFunc::create(
			CC_CALLBACK_0(ObjectBarrier::RepeatDrop, this)), NULL));
	m_BarrierManager->m_layer->addChild(foract);
}
void ObjectBarrier::CreateIronMace(float x, float y, float Angle)
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierNum = BarrierType::IronMace;
	m_Spr = Sprite::create("Barrier/IronMace.png");
	m_Spr->setAnchorPoint(Vec2(0.5f, 1.0f));
	m_Spr->setPosition(Vec2(x, y));
	m_Spr->setRotation(Angle);
	m_Spr->runAction(RepeatForever::create(
		RotateBy::create(4.0f, Vec3(0, 0, 360))));
	m_BarrierManager->m_layer->addChild(m_Spr, 6);

	m_Rect = Sprite::create("Barrier/MaceRect.png");
	m_Rect->setPosition(Vec2(x, y));
	m_Rect->setAnchorPoint(Vec2(0.5f, 4.1f));
	m_Rect->setRotation(Angle);
	m_Rect->setVisible(ColiideRect);
	m_Rect->runAction(RepeatForever::create(
		RotateBy::create(4.0f, Vec3(0, 0, 360))));
	m_BarrierManager->m_layer->addChild(m_Rect, 7);

	m_BarrierManager->m_List.push_back(this);
}
void ObjectBarrier::CreateBarrier(float x, float y, int num)
{
	m_FootHoldNum = 0;
	m_BarrierNum = num;
	extern BarrierManager* m_BarrierManager;
	if (num == BarrierType::Spine)
	{
		m_Spr = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->spine->getSpriteFrame());
		m_Spr->setPosition(Vec2(x - 5, y - 5));
		m_BarrierManager->m_layer->addChild(m_Spr, 1);
		m_pos[0] = m_Spr->getPosition();
		m_delay = 0.1f;
		for (int i = 0; i < 7; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->spineRect[i]->getSpriteFrame());
			m_SpineRect[i]->setScaleX(0.6f);
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x, y - 40));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x, y - 30));
			else if (i == 2)
				m_SpineRect[i]->setPosition(Vec2(x, y - 19));
			else if (i == 3)
				m_SpineRect[i]->setPosition(Vec2(x, y - 9));
			else if (i == 4)
				m_SpineRect[i]->setPosition(Vec2(x - 5, y + 1));
			else if (i == 5)
				m_SpineRect[i]->setPosition(Vec2(x - 10, y + 12));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 0);
		}
		m_BarrierManager->m_List.push_back(this);
	}
	else if (num == BarrierType::Spine2)
	{
		m_Spr = Sprite::create("Object/Tutorial/Spine2.png");
		m_Spr->setPosition(Vec2(x, y - 5));
		m_BarrierManager->m_layer->addChild(m_Spr, 0);
		m_pos[0] = m_Spr->getPosition();
		m_delay = 0.1f;
		for (int i = 0; i < 9; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->spineRect2[i]->getSpriteFrame());
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x, y - 95));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x, y - 82));
			else if (i == 2)
				m_SpineRect[i]->setPosition(Vec2(x + 6, y - 63));
			else if (i == 3)
				m_SpineRect[i]->setPosition(Vec2(x + 12, y - 32));
			else if (i == 4)
				m_SpineRect[i]->setPosition(Vec2(x, y - 5));
			else if (i == 5)
				m_SpineRect[i]->setPosition(Vec2(x + 60, y - 2));
			else if (i == 6)
				m_SpineRect[i]->setPosition(Vec2(x - 10, y + 14));
			else if (i == 7)
				m_SpineRect[i]->setPosition(Vec2(x - 10, y + 39));
			else if (i == 8)
				m_SpineRect[i]->setPosition(Vec2(x - 10, y + 62));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 0);
		}
		m_BarrierManager->m_List.push_back(this);
	}
	else if (num == BarrierType::Stage1Spine1)
	{
		m_Spr = Sprite::create("Barrier/FixBarrier1.png");
		m_Spr->setPosition(Vec2(x, y));
		m_BarrierManager->m_layer->addChild(m_Spr, 0);
		m_pos[0] = m_Spr->getPosition();
		m_delay = 0.1f;
		for (int i = 0; i < 3; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->stg1Spine1[i]->getSpriteFrame());
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x + 10, y));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x + 45, y - 10));
			else if (i == 2)
				m_SpineRect[i]->setPosition(Vec2(x - 20, y - 10));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 0);
		}
		m_BarrierManager->m_List.push_back(this);
	}
	else if (num == BarrierType::Stage1Spine2)
	{
		m_Spr = Sprite::create("Barrier/FixBarrier2.png");
		m_Spr->setPosition(Vec2(x, y));
		m_BarrierManager->m_layer->addChild(m_Spr, 0);
		m_pos[0] = m_Spr->getPosition();
		m_delay = 0.1f;
		for (int i = 0; i < 5; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->stg1Spine2[i]->getSpriteFrame());
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x - 25, y));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x + 5, y - 15));
			else if (i == 2)
				m_SpineRect[i]->setPosition(Vec2(x + 80, y - 35));
			else if (i == 3)
				m_SpineRect[i]->setPosition(Vec2(x + 45, y - 55));
			else if (i == 4)
				m_SpineRect[i]->setPosition(Vec2(x - 55, y - 55));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 0);
		}
		m_BarrierManager->m_List.push_back(this);
	}
	else if (num == BarrierType::Stone1)
	{
		m_Spr = Sprite::create("Object/Tutorial/Stone1.png");
		m_Spr->setPosition(Vec2(x, y));
		m_BarrierManager->m_layer->addChild(m_Spr, 0);
		m_pos[0] = m_Spr->getPosition();
		m_delay = 0.1f;
		for (int i = 0; i < 4; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->stoneRect[i]->getSpriteFrame());
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x, y + 20));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x, y + 30));
			else if (i == 2)
				m_SpineRect[i]->setPosition(Vec2(x, y + 35));
			else if (i == 3)
				m_SpineRect[i]->setPosition(Vec2(x, y + 35));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 0);
		}
		m_BarrierManager->m_List.push_back(this);
	}
	else if (num == BarrierType::Stage1Drop1)
	{
		m_Spr = Sprite::create("Barrier/Drop1.png");
		m_Save = Sprite::createWithSpriteFrame(m_Spr->getSpriteFrame());
		m_Save->setVisible(false);
		m_BarrierManager->m_layer->addChild(m_Save, 1);

		m_Spr->setPosition(Vec2(x, y));
		m_pos[0] = m_Spr->getPosition();
		m_pos[1].x = -5; m_pos[1].y = -40;
		m_pos[2].x = 0; m_pos[2].y = 35;
		m_BarrierManager->m_layer->addChild(m_Spr, 1);
		m_BarrierManager->m_List.push_back(this);
		//m_delay = 5.0f;
		for (int i = 0; i < 2; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->stg1Drop1[i]->getSpriteFrame());
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x - 5, y - 40));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x, y + 35));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 1);
		}
		char str[100] = { 0 };
		for (int i = 0; i < BarrierEffectNum - 4; ++i)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.05f);
		}
		for (int i = 0; i <= 10; ++i)
		{
			sprintf(str, "Barrier/DropAni/ex1_%d.png", i + 1);
			effect[0]->addSpriteFrameWithFileName(str);
		}
		effect[0]->setRestoreOriginalFrame(true);

		for (int i = 0; i < BarrierEffectNum - 4; ++i)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음

		//RepeatDrop();
	}
	else if (num == BarrierType::Stage1Drop2)
	{
		m_Spr = Sprite::create("Barrier/Drop2.png");
		m_Save = Sprite::createWithSpriteFrame(m_Spr->getSpriteFrame());
		m_Save->setVisible(false);
		m_BarrierManager->m_layer->addChild(m_Save, 1);

		m_Spr->setPosition(Vec2(x, y));
		m_BarrierManager->m_layer->addChild(m_Spr, 1);
		m_BarrierManager->m_List.push_back(this);
		m_pos[0] = m_Spr->getPosition();
		m_pos[1].x = 0; m_pos[1].y = 30;
		m_pos[2].x = 8; m_pos[2].y = -35;
		for (int i = 0; i < 2; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->stg1Drop2[i]->getSpriteFrame());
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x, y + 30));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x + 8, y - 35));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 1);
		}
		char str[100] = { 0 };
		for (int i = 0; i < BarrierEffectNum; ++i)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.05f);
		}
		for (int i = 0; i <= 10; ++i)
		{
			sprintf(str, "Barrier/DropAni/ex1_%d.png", i + 1);
			effect[0]->addSpriteFrameWithFileName(str);
		}
		effect[0]->setRestoreOriginalFrame(true);

		for (int i = 0; i < BarrierEffectNum; ++i)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음

		//RepeatDrop();
	}
	else if (num == BarrierType::Stage1Drop3)
	{
		m_Spr = Sprite::create("Barrier/Drop2Ani/Drop1.png");
		m_Save = Sprite::createWithSpriteFrame(m_Spr->getSpriteFrame());
		m_Save->setVisible(false);
		m_BarrierManager->m_layer->addChild(m_Save, 1);

		m_Spr->setPosition(Vec2(x, y));
		m_pos[0] = m_Spr->getPosition();
		m_BarrierManager->m_layer->addChild(m_Spr, 1);
		m_BarrierManager->m_List.push_back(this);
		//m_delay = 6.0f;
		for (int i = 0; i < 3; ++i)
		{
			m_SpineRect[i] = Sprite::createWithSpriteFrame(m_BarrierManager->m_Source->stg1Drop3[i]->getSpriteFrame());
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(x - 15, y + 15));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(x + 15, y - 18));
			else if (i == 2)
				m_SpineRect[i]->setPosition(Vec2(x + 30, y - 33));
			m_SpineRect[i]->setVisible(ColiideRect);
			m_BarrierManager->m_layer->addChild(m_SpineRect[i], 1);
		}
		char str[100] = { 0 };
		for (int i = 0; i < BarrierEffectNum ; ++i)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.05f);
		}
		for (int i = 0; i <= 10; ++i)
		{
			sprintf(str, "Barrier/DropAni/ex1_%d.png", i + 1);
			effect[0]->addSpriteFrameWithFileName(str);
		}
		effect[0]->setRestoreOriginalFrame(true);
		for (int i = 0; i < 8; ++i)
		{
			sprintf(str, "Barrier/Drop2Ani/Drop%d.png", i + 1);
			effect[1]->addSpriteFrameWithFileName(str);
		}
		

		for (int i = 0; i < BarrierEffectNum ; ++i)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음

		//RepeatDrop();
	}
	else if (num == BarrierType::Gate)
	{
		m_Spr = Sprite::create("Barrier/Gate1.png");
		m_Spr->setPosition(Vec2(x - 40, y + 150));
		m_BarrierManager->m_layer->addChild(m_Spr, -1);
		m_BarrierManager->m_List.push_back(this);
		extern EnemyManager* m_EnemyManager;
		m_EnemyManager->m_Source->m_metabox.pushBack(m_Spr);
	}
	else if (num == BarrierType::Gate2)
	{
		m_Spr = Sprite::create("Object/Tutorial/Interact1.png");
		m_Spr->setPosition(Vec2(x - 40, y + 147));//3278, 807
		m_Rect = Sprite::create("Object/Tutorial/InteractRect.png");
		m_Rect->setPosition(Vec2(m_Spr->getPositionX(), m_Spr->getPositionY()));
		m_Rect->setVisible(ColiideRect);
		m_BarrierManager->m_layer->addChild(m_Rect, 0);
		m_BarrierManager->m_layer->addChild(m_Spr, -1);
		m_BarrierManager->m_List.push_back(this);
		m_ButtonUse = false;

		m_Guide = Sprite::create("UI/Guide_X.png");
		m_Guide->setPosition(Vec2(m_Spr->getPositionX(), m_Spr->getPositionY() + 240));
		m_Guide->setVisible(false);
		m_Guide->setScale(0.6f);
		m_BarrierManager->m_layer->addChild(m_Guide);

		m_FootHold[0] = Sprite::create("Object/Tutorial/Floor1.png");
		m_FootHold[0]->setPosition(Vec2(3350, 750));
		m_FootHold[0]->setScale(0.5f);
		m_FootHold[0]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootHold[0]->runAction(FadeOut::create(0.0f));
		m_BarrierManager->m_layer->addChild(m_FootHold[0], -1);

		m_FootHold[1] = Sprite::create("Object/Tutorial/Floor2.png");
		m_FootHold[1]->setPosition(Vec2(3560, 600));
		m_FootHold[1]->setScale(0.5f);
		m_FootHold[1]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootHold[1]->runAction(FadeOut::create(0.0f));
		m_BarrierManager->m_layer->addChild(m_FootHold[1], -1);

		m_FootHold[2] = Sprite::createWithSpriteFrame(m_FootHold[0]->getSpriteFrame());
		m_FootHold[2]->setPosition(Vec2(3770, 750));
		m_FootHold[2]->setScale(0.5f);
		m_FootHold[2]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootHold[2]->runAction(FadeOut::create(0.0f));
		m_BarrierManager->m_layer->addChild(m_FootHold[2], -1);

		m_FootHold[3] = Sprite::createWithSpriteFrame(m_FootHold[1]->getSpriteFrame());
		m_FootHold[3]->setPosition(Vec2(3980, 880));
		m_FootHold[3]->setScale(0.5f);
		m_FootHold[3]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootHold[3]->runAction(FadeOut::create(0.0f));
		m_BarrierManager->m_layer->addChild(m_FootHold[3], -1);
	}
}

void ObjectBarrier::CreateButton(float x, float y)
{
	extern BarrierManager* m_BarrierManager;
	m_Button = Sprite::create("Barrier/GateButton1.png");
	m_Button->setPosition(Vec2(x, y));
	m_BarrierManager->m_layer->addChild(m_Button, 1);
	m_ButtonUse = false;
	// 
	char str[100] = { 0 };
	for (int i = 0; i < BarrierEffectNum - 4; ++i)
	{
		effect[i] = Animation::create();
		effect[i]->setDelayPerUnit(0.5f);
	}
	for (int i = 1; i < 5; ++i)
	{
		sprintf(str, "Barrier/GateButton%d.png", i);
		effect[0]->addSpriteFrameWithFileName(str);
	}

	for (int i = 0; i < BarrierEffectNum - 4; ++i)
		CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
}

void ObjectBarrier::SpineAction()
{
	// 배리어 매니저에서 관리
	//충돌체크
	if (m_BarrierNum == BarrierType::Spine)
	{
		for (int i = 0; i < 7; ++i)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_SpineRect[i]->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
					}
					ObjectHero::getInstance()->SetHP(-10);
				}
				// 밀려나는 동작
			}
		}
	}
	else if (m_BarrierNum == BarrierType::Spine2)
	{
		for (int i = 0; i < 9; ++i)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_SpineRect[i]->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
					}
					ObjectHero::getInstance()->SetHP(-10);
				}
			}
		}
	}
	else if (m_BarrierNum == BarrierType::Stone1)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_HeroHit == false)
					{
						if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_SpineRect[i]->getPositionX())
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
						else
							ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
					}
					ObjectHero::getInstance()->SetHP(-10);
				}
			}
		}
	}
	else if (m_BarrierNum == BarrierType::Stage1Spine1)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_SpineRect[i]->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
					ObjectHero::getInstance()->SetHP(-10);
				}
			}
		}
	}
	else if (m_BarrierNum == BarrierType::Stage1Spine2)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_SpineRect[i]->getBoundingBox()))
			{
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_SpineRect[i]->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
					ObjectHero::getInstance()->SetHP(-10);

				}
			}
		}
	}
}

void ObjectBarrier::DropBallAction()
{
	extern EnemyManager* m_EnemyManager;

	if (Updown == false)
		return;
	if (m_BarrierNum == BarrierType::Stage1Drop1 || m_BarrierNum == BarrierType::Stage1Drop2)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(m_Spr->getPositionX() + m_pos[1].x, m_Spr->getPositionY() + m_pos[1].y));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(m_Spr->getPositionX() + m_pos[2].x, m_Spr->getPositionY() + m_pos[2].y));

			if (m_SpineRect[i]->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
			{
				ColideBallAction();
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_SpineRect[i]->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
				return;
			}
		}
	}
	else if (m_BarrierNum == BarrierType::Stage1Drop3)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == 0)
				m_SpineRect[i]->setPosition(Vec2(m_Spr->getPositionX() - 15, m_Spr->getPositionY() + 15));
			else if (i == 1)
				m_SpineRect[i]->setPosition(Vec2(m_Spr->getPositionX() + 15, m_Spr->getPositionY() - 18));
			else if (i == 2)
				m_SpineRect[i]->setPosition(Vec2(m_Spr->getPositionX() + 30, m_Spr->getPositionY() - 33));

			if (m_SpineRect[i]->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
			{
				ColideBallAction();
				if (ObjectHero::getInstance()->m_HeroHit == false)
				{
					if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_SpineRect[i]->getPositionX())
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
					else
						ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				}
				ObjectHero::getInstance()->SetHP(-10);
				return;
			}
		}
	}
}

void ObjectBarrier::RepeatDrop()
{
	Updown = false;
	Vec2 pos = m_pos[0];
	m_Spr->setPosition(pos);
	if (m_BarrierNum == BarrierType::Stage1Drop1 || m_BarrierNum == BarrierType::Stage1Drop2)
	{
		m_SpineRect[0]->setPosition(Vec2(pos.x + m_pos[1].x, pos.y + m_pos[1].y));
		m_SpineRect[1]->setPosition(Vec2(pos.x + m_pos[2].x, pos.y + m_pos[2].y));
	}
	else if (m_BarrierNum == BarrierType::Stage1Drop3)
	{
		m_Spr->setRotation3D(Vec3(0, 0, 0));
		m_SpineRect[0]->setPosition(Vec2(pos.x - 15, pos.y + 15));
		m_SpineRect[1]->setPosition(Vec2(pos.x + 15, pos.y - 18));
		m_SpineRect[2]->setPosition(Vec2(pos.x + 30, pos.y - 33));
	}
	m_Spr->setOpacity(0);

	if (m_BarrierNum != BarrierType::Stage1Drop3)
	{
		m_Spr->runAction(Sequence::create(
			FadeIn::create(1.0f),
			Spawn::create(
				CallFunc::create(CC_CALLBACK_0(ObjectBarrier::SetTrigger, this)),
				MoveTo::create(m_Speed, Vec2(pos.x, pos.y + m_distance)),
				NULL),
			CallFunc::create(CC_CALLBACK_0(ObjectBarrier::ColideBallAction, this)),
			NULL));
	}
	else if (m_BarrierNum == BarrierType::Stage1Drop3)
	{
		m_Spr->runAction(Sequence::create(
			FadeIn::create(1.0f),
			Spawn::create(
				CallFunc::create(CC_CALLBACK_0(ObjectBarrier::SetTrigger, this)),
				RotateTo::create(m_Speed,Vec3(0,0,-35)),
				MoveTo::create(m_Speed, Vec2(pos.x, pos.y + m_distance)),
				NULL),
			
			CallFunc::create(CC_CALLBACK_0(ObjectBarrier::ColideBallAction, this)),
			NULL));
	}
}

void ObjectBarrier::GateAction()
{
	if (m_BarrierNum == BarrierType::Gate)
	{
		if (m_ButtonUse == false)
		{
			if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Button->getBoundingBox()))
			{
				m_ButtonUse = true;
				m_Button->runAction(Animate::create(effect[0]));
				m_Spr->runAction(MoveTo::create(1.0f, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY() + 400)));
			}
		}
	}
	else if (m_BarrierNum == BarrierType::Gate2)
	{
		if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()) && m_Guide->isVisible() == false)
		{
			m_Guide->setVisible(true);
			m_Guide->runAction(Repeat::create(
				Sequence::create(ScaleTo::create(0.8f,0.5f),
					ScaleTo::create(0.8f,0.6f),NULL),20));
		}
		else if(!ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
		{
			m_Guide->stopAllActions();
			m_Guide->setScale(0.6f);
			m_Guide->setVisible(false);
		}
		if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()) && m_ButtonUse == false && ObjectHero::getInstance()->m_Interact)
		{
			CSoundManager::getInstance()->playEffect("Sound/Sound/interaction.mp3", false, 1.0f);

			m_ButtonUse = true;
			CreateFoothold();
		}
	}
}

// 발판생성
void ObjectBarrier::CreateFoothold()
{
	if (m_ButtonUse)
	{
		extern BarrierManager* m_BarrierManager;
		if (m_FootHoldNum == 0)
		{
			m_FootHoldNum += 1;
			RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(ObjectBarrier::CreateFoothold2, this));
		}
		else if (m_FootHoldNum == 1)
		{
			m_FootHoldNum += 1;
			RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(ObjectBarrier::CreateFoothold2, this));
		}
		else if (m_FootHoldNum == 2)
		{
			m_FootHoldNum += 1;
			RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(ObjectBarrier::CreateFoothold2, this));
		}
		else if (m_FootHoldNum == 3)
		{
			m_FootHoldNum += 1;
			RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(ObjectBarrier::CreateFoothold2, this));
		}
	}
}

void ObjectBarrier::CreateFoothold2()
{
	static float Num = 0;
	if (Num == 4)
		Num = 0;
	extern BarrierManager* m_BarrierManager;
	extern EnemyManager* m_EnemyManager;
	if (Num == 0)
	{
		Num += 1;
		m_FootHold[0]->runAction(Sequence::create(
			FadeIn::create(0.5f), NULL));
		m_FootHold[0]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootHold[0]->getPositionX(), m_FootHold[0]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootHold[0]->getPositionX(), m_FootHold[0]->getPositionY())),
				NULL)));
		m_FootRect[0] = Sprite::create("Object/Tutorial/FloorRect.png");
		m_FootRect[0]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootRect[0]->setScale(0.5f);
		m_FootRect[0]->setVisible(ColiideRect);
		m_FootRect[0]->setTag(MetaNum::Red);
		m_FootRect[0]->setPosition(Vec2(m_FootHold[0]->getPositionX() + 10, m_FootHold[0]->getPositionY() - 10));
		m_FootRect[0]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootRect[0]->getPositionX(), m_FootRect[0]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootRect[0]->getPositionX(), m_FootRect[0]->getPositionY())),
				NULL)));
		m_BarrierManager->m_layer->addChild(m_FootRect[0], -1);
		m_BarrierManager->m_Source->m_metabox.pushBack(m_FootRect[0]);
		CreateFoothold();
	}
	else if (Num == 1)
	{
		Num += 1;
		m_FootHold[1]->runAction(FadeIn::create(0.5f));
		m_FootHold[1]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootHold[1]->getPositionX(), m_FootHold[1]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootHold[1]->getPositionX(), m_FootHold[1]->getPositionY())),
				NULL)));
		m_FootRect[1] = Sprite::create("Object/Tutorial/FloorRect.png");
		m_FootRect[1]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootRect[1]->setScale(0.5f);
		m_FootRect[1]->setVisible(ColiideRect);
		m_FootRect[1]->setTag(MetaNum::Red);
		m_FootRect[1]->setPosition(Vec2(m_FootHold[1]->getPositionX() + 5, m_FootHold[1]->getPositionY() - 20));
		m_FootRect[1]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootRect[1]->getPositionX(), m_FootRect[1]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootRect[1]->getPositionX(), m_FootRect[1]->getPositionY())),
				NULL)));
		m_BarrierManager->m_layer->addChild(m_FootRect[1], -1);
		m_BarrierManager->m_Source->m_metabox.pushBack(m_FootRect[1]);
		CreateFoothold();
	}
	else if (Num == 2)
	{
		Num += 1;
		m_FootHold[2]->runAction(FadeIn::create(0.5f));
		m_FootHold[2]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootHold[2]->getPositionX(), m_FootHold[2]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootHold[2]->getPositionX(), m_FootHold[2]->getPositionY())),
				NULL)));
		m_FootRect[2] = Sprite::create("Object/Tutorial/FloorRect.png");
		m_FootRect[2]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootRect[2]->setScale(0.5f);
		m_FootRect[2]->setVisible(ColiideRect);
		m_FootRect[2]->setTag(MetaNum::Red);
		m_FootRect[2]->setPosition(Vec2(m_FootHold[2]->getPositionX() + 10, m_FootHold[2]->getPositionY() - 10));
		m_FootRect[2]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootRect[2]->getPositionX(), m_FootRect[2]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootRect[2]->getPositionX(), m_FootRect[2]->getPositionY())),
				NULL)));
		m_BarrierManager->m_layer->addChild(m_FootRect[2], -1);
		m_BarrierManager->m_Source->m_metabox.pushBack(m_FootRect[2]);
		CreateFoothold();
	}
	else if (Num == 3)
	{
		Num += 1;
		m_FootHold[3]->runAction(FadeIn::create(0.5f));
		m_FootHold[3]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootHold[3]->getPositionX(), m_FootHold[3]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootHold[3]->getPositionX(), m_FootHold[3]->getPositionY())),
				NULL)));
		m_FootRect[3] = Sprite::create("Object/Tutorial/FloorRect.png");
		m_FootRect[3]->setAnchorPoint(Vec2(0.0f, 1.0f));
		m_FootRect[3]->setScale(0.5f);
		m_FootRect[3]->setVisible(ColiideRect);
		m_FootRect[3]->setTag(MetaNum::Red);
		m_FootRect[3]->setPosition(Vec2(m_FootHold[3]->getPositionX() + 5, m_FootHold[3]->getPositionY() - 20));
		m_FootRect[3]->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(0.8f, Vec2(m_FootRect[3]->getPositionX(), m_FootRect[3]->getPositionY() + 40)),
				MoveTo::create(0.8f, Vec2(m_FootRect[3]->getPositionX(), m_FootRect[3]->getPositionY())),
				NULL)));
		m_BarrierManager->m_layer->addChild(m_FootRect[3], -1);
		m_BarrierManager->m_Source->m_metabox.pushBack(m_FootRect[3]);
	}
}

//각도, 디레이
void ObjectBarrier::SetRotation(float angle, float delay)
{
	m_Spr->setRotation(angle);
	m_delay = delay;

	if (angle == -1)// -1은 정지로 바꿈
	{
		return;
	}

	if (angle == 0)
	{
		if (m_BarrierNum == BarrierType::Spine)
		{
			m_Spr->runAction(RepeatForever::create(
				Sequence::create(
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY() + 80)),
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY())),
					NULL)));
			for (int i = 0; i < 7; ++i)
			{
				m_SpineRect[i]->runAction(RepeatForever::create(
					Sequence::create(
						MoveTo::create(m_delay, Vec2(m_SpineRect[i]->getPositionX(), m_SpineRect[i]->getPositionY() + 80)),
						MoveTo::create(m_delay, Vec2(m_SpineRect[i]->getPositionX(), m_SpineRect[i]->getPositionY())),
						NULL)));
			}
		}
		else if (m_BarrierNum == BarrierType::Spine2)
		{
			m_Spr->runAction(RepeatForever::create(
				Sequence::create(
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY() + 300)),
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY())),
					NULL)));
			for (int i = 0; i < 9; ++i)
			{
				m_SpineRect[i]->runAction(RepeatForever::create(
					Sequence::create(
						MoveTo::create(m_delay, Vec2(m_SpineRect[i]->getPositionX(), m_SpineRect[i]->getPositionY() + 300)),
						MoveTo::create(m_delay, Vec2(m_SpineRect[i]->getPositionX(), m_SpineRect[i]->getPositionY())),
						NULL)));
			}
		}
		else if (m_BarrierNum == BarrierType::Stone1)
		{
			m_Spr->runAction(RepeatForever::create(
				Sequence::create(
					MoveTo::create(1.0f, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY() + 300)),
					MoveTo::create(0.15f, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY())),
					NULL)));
			for (int i = 0; i < 4; ++i)
			{
				m_SpineRect[i]->runAction(RepeatForever::create(
					Sequence::create(
						MoveTo::create(1.0f, Vec2(m_SpineRect[i]->getPositionX(), m_SpineRect[i]->getPositionY() + 300)),
						MoveTo::create(0.15f, Vec2(m_SpineRect[i]->getPositionX(), m_SpineRect[i]->getPositionY())),
						NULL)));
			}
		}
	}
	if (angle == -90)
	{
		for (int i = 0; i < 7; ++i)
		{
			m_SpineRect[i]->setRotation(angle);
		}
		m_Spr->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(m_delay, Vec2(m_Spr->getPositionX() - 80, m_Spr->getPositionY())),
				MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY())),
				NULL)));
		for (int i = 0; i < 7; ++i)
		{
			m_SpineRect[i]->runAction(RepeatForever::create(
				Sequence::create(
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX() - 80, m_Spr->getPositionY())),
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY())),
					NULL)));
		}
	}
	else if (angle == 90)
	{
		m_Spr->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(m_delay, Vec2(m_Spr->getPositionX() + 80, m_Spr->getPositionY())),
				MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY())),
				NULL)));
		for (int i = 0; i < 7; ++i)
		{
			m_SpineRect[i]->runAction(RepeatForever::create(
				Sequence::create(
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX() + 80, m_Spr->getPositionY())),
					MoveTo::create(m_delay, Vec2(m_Spr->getPositionX(), m_Spr->getPositionY())),
					NULL)));
		}
	}
}

void ObjectBarrier::IromMaceUpdate()
{
	if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
	{
		if (ObjectHero::getInstance()->m_HeroHit == false)
		{
			CSoundManager::getInstance()->playEffect("Sound/mace2.mp3", false, 1.0f);
			if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Rect->getPositionX())
				ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
			else
				ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
			ObjectHero::getInstance()->SetHP(-10);
		}
	}
}