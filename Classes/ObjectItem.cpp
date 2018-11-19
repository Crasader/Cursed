#include "Default.h"

void ObjectItem::CreateObject(float x, float y, int itemNum)
{
	m_Recreate = false;
	extern ItemManager* m_ItemManager;
	if (itemNum == Item::Box1)
	{
		m_Spr = Sprite::create("Object/Box1/Open1.png");
		m_Spr->setPosition(Vec2(x, y + 70));
		m_Spr->setName("ItemBox");
		m_ItemManager->m_layer->addChild(m_Spr, 1);

		m_Rect = Sprite::create("Object/Box1/BoxRect.png");
		m_Rect->setPosition(Vec2(x, y + 30));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);

		char str[100] = { 0 };

		sprintf(str, "Object/Item/potion/potion%d.png", random(1, 12));
		m_Item = Sprite::create(str);
		m_Item->setPosition(Vec2(m_Spr->getPositionX(),m_Spr->getPositionY()-50));
		m_Item->setTag(Item::Box1);
		m_Item->setVisible(false);
		m_ItemManager->m_layer->addChild(m_Item, 9);

		m_ItemManager->m_List.push_back(this);

		m_Guide = Sprite::create("UI/Guide_Z.png");
		m_Guide->setPosition(Vec2(m_Item->getPositionX(), m_Item->getPositionY() + 240));
		m_Guide->setVisible(false);
		m_Guide->setScale(0.3f);
		m_ItemManager->m_layer->addChild(m_Guide, 8);

		m_ItemExit = false;
		m_SaveObject = false;
		m_HP = 10;
		m_State = 0;

		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 10; i++)
		{
			sprintf(str, "Object/Box1/Open%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
	}
	else if (itemNum == Item::None)
	{

		m_Spr = Sprite::create("Object/Tutorial/pot.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setScale(0.6f);
		m_Spr->setName("Nothing");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/Tutorial/potRect.png");
		m_Rect->setScale(0.6f);
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);
		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_HP = 10;
	}
	else if (itemNum == Item::Jar1)
	{
		m_Spr = Sprite::create("Object/jar_1.png");
		m_Spr->setPosition(Vec2(x, y+20));
		m_Spr->setName("Nothing");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/Tutorial/potRect.png");
		m_Rect->setScale(0.6f);
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);
		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_HP = 10;
	}
	else if (itemNum == Item::Jar2)
	{
		m_Spr = Sprite::create("Object/jar_2.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("Nothing");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/Tutorial/potRect.png");
		m_Rect->setScale(0.6f);
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);
		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_HP = 10;
	}
	else if (itemNum == Item::Jar3)
	{
		m_Spr = Sprite::create("Object/jar_3.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("Nothing");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/Tutorial/potRect.png");
		m_Rect->setScale(0.6f);
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);
		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_HP = 10;
	}
	else if (itemNum == Item::Jar4)
	{
		m_Spr = Sprite::create("Object/jar_4.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("Nothing");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/Tutorial/potRect.png");
		m_Rect->setScale(0.6f);
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);
		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_HP = 10;
	}
	else if (itemNum == Item::Bat)
	{
		m_Spr = Sprite::create("Object/BoxStand1.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("ItemBox");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/BoxRect1.png");
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);

		m_Item = Sprite::create("Object/Weapon1.png");
		m_Item->setPosition(m_Spr->getPosition());
		m_Item->setTag(Item::Bat);
		m_Item->setScale(2.0f);
		m_Item->setVisible(false);
		m_ItemManager->m_layer->addChild(m_Item, 6);

		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_SaveObject = false;
		m_HP = 10;
		m_State = 0;

		char str[100] = { 0 };
		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)
		{
			sprintf(str, "Object/BoxOpen%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
	}
	else if (itemNum == Item::Gun)
	{
		m_Spr = Sprite::create("Object/BoxStand1.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("ItemBox");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/BoxRect1.png");
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);

		m_Item = Sprite::create("Object/Weapon2.png");
		m_Item->setPosition(m_Spr->getPosition());
		m_Item->setTag(Item::Gun);
		m_Item->setScale(2.0f);
		m_Item->setVisible(false);
		m_ItemManager->m_layer->addChild(m_Item, 6);

		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_SaveObject = false;
		m_HP = 10;
		m_State = 0;

		char str[100] = { 0 };
		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)
		{
			sprintf(str, "Object/BoxOpen%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
	}
	else if (itemNum == Item::SavePoint)
	{
		m_Spr = Sprite::create("Object/SavePoint.png");
		m_Spr->setPosition(Vec2(x, y + 70));
		m_Spr->setName("ItemSave");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/BoxRect1.png");
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);
		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_SaveObject = true;
		m_HP = 10;
		m_State = 0;
		m_SaveNum = 0;

		char str[100] = { 0 };
		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 8; i++)
		{
			sprintf(str, "Object/SaveAni%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
	}
	else if (itemNum >= Item::SkillScroll1 && itemNum <= Item::SkillScroll3)
	{
		m_Spr = Sprite::create("Object/BoxStand1.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("ItemBox");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/BoxRect1.png");
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);
		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_SaveObject = false;
		m_HP = 10;
		m_State = 0;

		char str[100] = { 0 };
		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)
		{
			sprintf(str, "Object/BoxOpen%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음

		if (itemNum == Item::SkillScroll1)
		{
			m_Item = Sprite::create("Item/SkillBook.png");
			m_Item->setPosition(m_Spr->getPosition());
			m_Item->setTag(Item::SkillScroll1);
			m_Item->setScale(1.0f);
			m_Item->setVisible(false);
			m_ItemManager->m_layer->addChild(m_Item, 6);
		}
		else if(itemNum == Item::SkillScroll2)
		{
			m_Item = Sprite::create("Item/SkillBook2.png");
			m_Item->setPosition(m_Spr->getPosition());
			m_Item->setTag(Item::SkillScroll2);
			m_Item->setScale(1.0f);
			m_Item->setVisible(false);
			m_ItemManager->m_layer->addChild(m_Item, 6);
		}
		else if (itemNum == Item::SkillScroll3)
		{
			m_Item = Sprite::create("Item/SkillBook3.png");
			m_Item->setPosition(m_Spr->getPosition());
			m_Item->setTag(Item::SkillScroll3);
			m_Item->setScale(1.0f);
			m_Item->setVisible(false);
			m_ItemManager->m_layer->addChild(m_Item, 6);
		}
	}
	else if (itemNum == Shield::Head1)
	{
		m_Spr = Sprite::create("Object/BoxStand1.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("ItemBox");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/BoxRect1.png");
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);

		m_Item = Sprite::create("Item/Head/Head1.png");
		m_Item->setPosition(m_Spr->getPosition());
		m_Item->setTag(Shield::Head1);
		m_Item->setScale(2.0f);
		m_Item->setVisible(false);
		m_ItemManager->m_layer->addChild(m_Item, 6);

		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_SaveObject = false;
		m_HP = 10;
		m_State = 0;
		
		char str[100] = { 0 };
		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)
		{
			sprintf(str, "Object/BoxOpen%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
	}
	else if (itemNum == Shield::Top1)
	{
		m_Spr = Sprite::create("Object/BoxStand1.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("ItemBox");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/BoxRect1.png");
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);

		m_Item = Sprite::create("Item/Top/Top1.png");
		m_Item->setPosition(m_Spr->getPosition());
		m_Item->setTag(Shield::Top1);
		m_Item->setScale(2.0f);
		m_Item->setVisible(false);
		m_ItemManager->m_layer->addChild(m_Item, 6);

		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_SaveObject = false;
		m_HP = 10;
		m_State = 0;

		char str[100] = { 0 };
		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)
		{
			sprintf(str, "Object/BoxOpen%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
	}
	else if (itemNum == Shield::Bottom1)
	{
		m_Spr = Sprite::create("Object/BoxStand1.png");
		m_Spr->setPosition(Vec2(x, y + 20));
		m_Spr->setName("ItemBox");
		m_ItemManager->m_layer->addChild(m_Spr, 5);

		m_Rect = Sprite::create("Object/BoxRect1.png");
		m_Rect->setPosition(Vec2(x, y + 20));
		m_Rect->setVisible(ColiideRect);
		m_ItemManager->m_layer->addChild(m_Rect, 6);

		m_Item = Sprite::create("Item/Bottom/Bottom1.png");
		m_Item->setPosition(m_Spr->getPosition());
		m_Item->setTag(Shield::Bottom1);
		m_Item->setScale(2.0f);
		m_Item->setVisible(false);
		m_ItemManager->m_layer->addChild(m_Item, 6);

		m_ItemManager->m_List.push_back(this);

		m_ItemExit = false;
		m_SaveObject = false;
		m_HP = 10;
		m_State = 0;

		char str[100] = { 0 };
		for (int i = 0; i < ObjectEffectNum; i++)
		{
			effect[i] = Animation::create();
			effect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)
		{
			sprintf(str, "Object/BoxOpen%d.png", i);
			effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);//강제로 메모리적재 -> addchild 를 실행하지 않으면 적재되지 않음
	}
}

void ObjectItem::AnimationSwitch(int num)
{
	if (num == ObjectEffect::Death)
	{
		if (m_State != num)
		{
			m_State = ObjectEffect::Death;
			m_Spr->stopAllActions();
			if (m_Spr->getName() == "Nothing")
			{
				extern ItemManager* m_ItemManager;
				m_Spr->runAction(RemoveSelf::create());
			}
			else
			{
				CSoundManager::getInstance()->playEffect("Sound/Sound/woodenbox_open.mp3", false, 1.0f);

				m_Spr->runAction(Sequence::create(
					Animate::create(effect[0]),
					CallFunc::create(CC_CALLBACK_0(ObjectItem::CreateItem, this)),
					RemoveSelf::create(),
					NULL));
			}
		}
	}
	else if(num == ObjectEffect::Saving)
	{
		if (m_State != num)
		{
			m_State = ObjectEffect::Saving;
			m_Spr->stopAllActions();
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[0]),
				NULL));
			m_SaveObject = false;
		}
	}
	/*else if (num == ObjectEffect::GetSkill)
	{
		if (m_State != num)
		{
			m_State = ObjectEffect::GetSkill;
			m_Spr->stopAllActions();
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[0]),
				NULL));
			m_SaveObject = false;
		}
	}*/
}

void ObjectItem::ReCreateItem(Sprite* item)
{
	extern ItemManager* m_ItemManager;

	m_Recreate = true;
	m_ItemExit = false;
	m_SaveObject = false;
	m_HP = 10;
	m_State = 0;
	m_Item = Sprite::createWithSpriteFrame(item->getSpriteFrame());
	m_Item->setPosition(ObjectHero::getInstance()->m_Spr->getPosition());
	m_Item->setTag(item->getTag());
	float tag = item->getTag();
	if(m_Item->getScale() != 2.0f)
		m_Item->setScale(2.0f);
	m_Item->setVisible(true);
	m_Item->runAction(Spawn::create(RotateTo::create(1.0f,Vec3(90,0,0)),
			JumpTo::create(1.0f, Vec2(ObjectHero::getInstance()->m_Spr->getPositionX(), ObjectHero::getInstance()->m_Spr->getPositionY()), 100.0f, 1),
			NULL));
	RUN_WITH_DELAY(1.2f, CC_CALLBACK_0(ObjectItem::ChangeItemState, this));
	m_ItemManager->m_layer->addChild(m_Item, 6);
	m_ItemManager->m_List.push_back(this);
}

void ObjectItem::CreateItem()
{
	m_Item->setVisible(true);
	m_Item->runAction(
		Spawn::create(
			RotateBy::create(1.0f, Vec3(0, 0, 720)),
			JumpTo::create(1.0f, Vec2(m_Item->getPositionX(), m_Item->getPositionY()), 150.0f, 1),
		NULL));
	RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(ObjectItem::ChangeItemState, this));
}

void ObjectItem::ChangeItemState()
{
	m_ItemExit = true;
}

void ObjectItem::ItemUpdate()
{
	if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Item->getBoundingBox()) && m_Guide->isVisible() == false)
	{
		m_Guide->setVisible(true);
		m_Guide->runAction(Repeat::create(
			Sequence::create(ScaleTo::create(0.8f, 0.3f),
				ScaleTo::create(0.8f, 0.4f), NULL), 20));
	}
	else if (!ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Item->getBoundingBox()))
	{
		m_Guide->stopAllActions();
		m_Guide->setScale(0.3f);
		m_Guide->setVisible(false);
	}
}

void ObjectItem::ItemDelete()
{
	extern ItemManager* m_ItemManager;
	if (m_Recreate)
	{
		m_ItemManager->m_layer->removeChild(m_Item);
	}
	else
	{
		if (m_Item->getTag() == Item::Box1)
		{
			ObjectHero::getInstance()->SetHP(60);
			CSoundManager::getInstance()->playEffect("Sound/Sound/potion.mp3", false, 1.0f);
		}
		m_Item->runAction(Sequence::create(
			EaseOut::create(MoveTo::create(0.4f,Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(),m_Item->getPositionY()+80)),2.0f),
			FadeOut::create(0.2f),RemoveSelf::create(),
			NULL));
		m_Guide->setVisible(false);
		m_ItemManager->m_layer->removeChild(m_Guide);
		m_ItemManager->m_layer->removeChild(m_Spr);
		//m_ItemManager->m_layer->removeChild(m_Item);
		m_ItemManager->m_layer->removeChild(m_Rect);
		//게임종료시 메모리해제
		for (int i = 0; i < ObjectEffectNum; i++)
			CC_SAFE_RELEASE(effect[i]);
	}
}