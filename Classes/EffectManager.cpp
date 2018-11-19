#include "Default.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::GetLayer(Layer* layer)
{
	m_layer = layer;
}

void EffectManager::CreateEffect()
{
	static bool once;
	if (once == false)
	{
		//애니메이션
		char str[100] = { 0 };

		for (int i = 0; i < EffectIndex; i++)
		{
			effect[i] = Animation::create();
			if (i == EffectName::LadyBugBoom)
				effect[i]->setDelayPerUnit(0.03f);
			else if (i == EffectName::Flame1)
				effect[i]->setDelayPerUnit(0.03f);
			else if (i == 10 || i == 11 || i == 12 || i == 13)
				effect[i]->setDelayPerUnit(0.05f);
			else
				effect[i]->setDelayPerUnit(0.1f);
		}

		for (int i = 1; i <= 3; i++)// 히어로 점프1
		{
			sprintf(str, "Effect/jumping1/jump%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 4; i++)// 히어로 점프2
		{
			sprintf(str, "Effect/jumping2/jump%d.png", i);
			effect[1]->addSpriteFrameWithFileName(str);
		}
		//for (int i = 1; i <= 8; i++)// 히어로 착지
		//{
		//	sprintf(str, "Effect/effect_get_%d.png", i);
		//	effect[2]->addSpriteFrameWithFileName(str);
		//}
		for (int i = 1; i <= 11; i++)// 스크롤 획득 이벤트
		{
			sprintf(str, "Item/BookEffect/ex1_%d.png", i);
			effect[3]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i <= 9; i++)// 몬스터 히트모션1
		{
			sprintf(str, "Effect/Hit1/mon_hit1_%d.png", i);
			effect[4]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i <= 9; i++)// 몬스터 히트모션1
		{
			sprintf(str, "Effect/Hit2/mon_hit2_%d.png", i);
			effect[5]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 13; ++i)//무당벌레 폭파모션
		{
			sprintf(str, "Monster/Ladybug/Boom/Boom%d.png", i);
			effect[6]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 9; ++i)
		{
			sprintf(str, "Effect/Protect/Protect%d.png", i);
			effect[7]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 4; ++i)// 걷는 이펙트
		{
			sprintf(str, "Effect/walking/walk%d.png", i);
			effect[8]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 50; ++i)// 텔포
		{
			sprintf(str, "Effect/Flame1/Flame (%d).png", i);
			effect[9]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 38; ++i)// Green - Effect
		{
			sprintf(str, "Monster/Boss2/Effect/Green/Effect (%d).png", i);
			effect[10]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 38; ++i)// Red - Effect
		{
			sprintf(str, "Monster/Boss2/Effect/Red/Effect (%d).png", i);
			effect[11]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 38; ++i)// Black - Effect
		{
			sprintf(str, "Monster/Boss2/Effect/Black/Effect (%d).png", i);
			effect[12]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 100; ++i)// Black - Effect
		{
			sprintf(str, "Effect/Teleport/Teleport (%d).png", i);
			effect[13]->addSpriteFrameWithFileName(str);
		}
		//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
		for (int i = 0; i < EffectIndex; ++i)
			CC_SAFE_RETAIN(effect[i]);
	}
}

void EffectManager::EffectSwitch(int num, float x, float y, bool Flip)
{
	if (num == EffectName::HeroJump1)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y - 130));
		m_layer->addChild(spr, 15);
		if (Flip)
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroJump1]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroJump1]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::HeroJump2)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y - 40));
		m_layer->addChild(spr, 15);
		if (Flip)
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroJump2]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroJump2]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::MonsterHit1)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x + (Flip ? -30 : 30), y));
		m_layer->addChild(spr, 6);
		spr->setFlipX(Flip ? true : false);
		spr->runAction(Sequence::create(
			Animate::create(effect[EffectName::MonsterHit1]),
			RemoveSelf::create(),
			NULL));
	}
	else if (num == EffectName::MonsterHit2)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x + (Flip ? -30 : 30), y));
		m_layer->addChild(spr, 6);
		spr->setFlipX(Flip ? true : false);
		spr->runAction(Sequence::create(
			Animate::create(effect[EffectName::MonsterHit2]),
			RemoveSelf::create(),
			NULL));
	}
	else if (num == EffectName::HeroLand)
	{
		auto spr = Sprite::create();
		spr->setVisible(false);//임시
		spr->setPosition(Vec2(x, y - 60));
		m_layer->addChild(spr, 9);
		if (Flip)
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroLand]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroLand]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::GetScroll)
	{
		auto spr = Sprite::create();
		spr->setVisible(false);//임시
		spr->setPosition(Vec2(x, y + 60));
		m_layer->addChild(spr, 9);
		if (Flip)
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::GetScroll]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::GetScroll]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::LadyBugBoom)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));
		m_layer->addChild(spr, 9);
		if (Flip)
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::LadyBugBoom]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::LadyBugBoom]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::Protect)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));
		spr->setScale(2.0f);
		m_layer->addChild(spr, 9);
		if (Flip)
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::Protect]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::Protect]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::HeroWalk)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y - 105));
		m_layer->addChild(spr, 8);
		if (Flip)
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroWalk]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::HeroWalk]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::Flame1)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));;
		m_layer->addChild(spr, 9);
		if (Flip)
		{
			spr->setScale(2.0f);
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::Flame1]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setScale(1.3f);
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				Animate::create(effect[EffectName::Flame1]),
				RemoveSelf::create(),
				NULL));
		}
	}
	else if (num == EffectName::GreenE)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));
		spr->setScale(0.7f);
		m_layer->addChild(spr, 9);
		spr->runAction(Sequence::create(DelayTime::create(0.5f),
			Animate::create(effect[EffectName::GreenE]),
			RemoveSelf::create(),
			NULL));
	}
	else if (num == EffectName::RedE)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));
		spr->setScale(0.7f);
		m_layer->addChild(spr, 9);
		spr->runAction(Sequence::create(DelayTime::create(0.5f),
			Animate::create(effect[EffectName::RedE]),
			RemoveSelf::create(),NULL));
	}
	else if (num == EffectName::BlackE)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));
		spr->setScale(0.7f);
		m_layer->addChild(spr, 9);
		spr->runAction(Sequence::create(DelayTime::create(0.5f),
			Animate::create(effect[EffectName::BlackE]),
			RemoveSelf::create(),NULL));
	}
	else if (num == EffectName::Teloport)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));
		m_layer->addChild(spr, 9);
		spr->runAction(Sequence::create(
			Animate::create(effect[EffectName::Teloport]),
			RemoveSelf::create(), NULL));
	}
}

void EffectManager::EffectSwitch(int num, float x, float y, bool Flip, float delay)
{
	if (num == EffectName::LadyBugBoom)
	{
		auto spr = Sprite::create();
		spr->setPosition(Vec2(x, y));
		spr->setScale(1.8f);
		m_layer->addChild(spr, 9);
		if (Flip)
		{
			spr->setFlipX(true);
			spr->runAction(Sequence::create(
				DelayTime::create(delay),
				Animate::create(effect[EffectName::LadyBugBoom]),
				RemoveSelf::create(),
				NULL));
		}
		else
		{
			spr->setFlipX(false);
			spr->runAction(Sequence::create(
				DelayTime::create(delay),
				Animate::create(effect[EffectName::LadyBugBoom]),
				RemoveSelf::create(),
				NULL));
		}
	}
}
