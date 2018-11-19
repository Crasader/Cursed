#include "Default.h"

Function::Function()
{
}

Function::~Function()
{
}


void Function::MakeColideWidth(int MapXY[][92], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (i - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j][i - 1] == -1)
				{
					MakeBlockWidth(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}

void Function::MakeColideHeight(int MapXY[][92], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int i = 0; i < size.x; ++i)
	{
		for (int j = 0; j < size.y; ++j)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (j - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j - 1][i] == -1)
				{
					MakeBlockHeight(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}

void Function::MakeColideWidth(int MapXY[][228], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (i - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j][i - 1] == -1)
				{
					MakeBlockWidth(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}

void Function::MakeColideHeight(int MapXY[][228], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int i = 0; i < size.x; ++i)
	{
		for (int j = 0; j < size.y; ++j)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (j - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j - 1][i] == -1)
				{
					MakeBlockHeight(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}


void Function::MakeColideWidth(int MapXY[][48], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (i - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j][i - 1] == -1)
				{
					MakeBlockWidth(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}

void Function::MakeColideHeight(int MapXY[][48], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int i = 0; i < size.x; ++i)
	{
		for (int j = 0; j < size.y; ++j)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (j - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j - 1][i] == -1)
				{
					MakeBlockHeight(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}

void Function::MakeColideWidth(int MapXY[][24], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (i - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j][i - 1] == -1)
				{
					MakeBlockWidth(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}

void Function::MakeColideHeight(int MapXY[][24], Vec2 size, int tag)
{
	int start = 0;
	Vec2 mapPos = { 0,0 };

	for (int i = 0; i < size.x; ++i)
	{
		for (int j = 0; j < size.y; ++j)
		{
			if (MapXY[j][i] == -1 && start == 0)
			{
				mapPos.x = i * 80;
				mapPos.y = (size.y - 1) * 80 - j * 80;
				start++;
			}
			else if (MapXY[j][i] == -1)
				start++;
			else if (j - 1 != 0)
			{
				if (MapXY[j][i] == 0 && MapXY[j - 1][i] == -1)
				{
					MakeBlockHeight(mapPos, (float)start, tag);
					start = 0; mapPos.x = 0; mapPos.y = 0;
				}
			}
		}
	}
}

void Function::MakeBlockWidth(Vec2 pos, float width, int tag)
{
	if (tag == MetaNum::Red)
	{
		Sprite* red = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxRed->getSpriteFrame());
		red->setAnchorPoint(Vec2(0.0f, 1.0f));
		red->setPosition(Vec2(pos.x, pos.y + 80));
		red->setScaleX(width);
		red->setTag(MetaNum::Red);
		red->setVisible(ColiideRect);
		m_Layer->addChild(red, 5);
		SourceManager::getInstance()->m_metabox.pushBack(red);
	}
	else if (tag == MetaNum::MonsterOnly)
	{
		Sprite* mons = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxBlue->getSpriteFrame());
		mons->setAnchorPoint(Vec2(0.0f, 1.0f));
		mons->setPosition(Vec2(pos.x, pos.y + 80));
		mons->setScaleX(width);
		mons->setTag(MetaNum::MonsterOnly);
		mons->setVisible(ColiideRect);
		m_Layer->addChild(mons, 5);
		SourceManager::getInstance()->m_Stg1_2MBox.pushBack(mons);
	}
}

void Function::MakeBlockHeight(Vec2 pos, float height, int tag)
{
	if (tag == MetaNum::Red)
	{
		Sprite* red = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxRed->getSpriteFrame());
		red->setAnchorPoint(Vec2(0.0f, 1.0f));
		red->setPosition(Vec2(pos.x, pos.y + 80));
		red->setScaleY(height);
		red->setTag(MetaNum::Red);
		red->setVisible(ColiideRect);
		m_Layer->addChild(red, 5);
		SourceManager::getInstance()->m_metabox.pushBack(red);
	}
}

Sprite* Function::CreateRedBlock(Vec2 pos)
{
	Sprite* RectRed = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxRed->getSpriteFrame());
	RectRed->setAnchorPoint(Vec2(0.0f, 1.0f));
	RectRed->setVisible(ColiideRect);
	RectRed->setPosition(pos);
	RectRed->setTag(MetaNum::Red);
	m_Layer->addChild(RectRed, 5);
	SourceManager::getInstance()->m_metabox.pushBack(RectRed);

	return RectRed;
}

Sprite* Function::CreateRedBlock(Vec2 pos, float width)
{
	Sprite* RectRed = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxRed->getSpriteFrame());
	RectRed->setAnchorPoint(Vec2(0.0f, 1.0f));
	RectRed->setVisible(ColiideRect);
	RectRed->setPosition(pos);
	RectRed->setScaleX(width);
	RectRed->setTag(MetaNum::Red);
	m_Layer->addChild(RectRed, 5);
	SourceManager::getInstance()->m_metabox.pushBack(RectRed);

	return RectRed;
}

void Function::MakeHeroPos()
{
	//char tmp[10];
	//sprintf(tmp, "%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	//_labelPercent->setString(tmp);

	m_HeroPos = Label::createWithTTF("", "fonts/210 ¾Æ¸óµåR.ttf", 45);
	m_HeroPos->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(),
		ObjectHero::getInstance()->m_Rect->getPositionY() + 150));
	m_Layer->addChild(m_HeroPos, 50);
}

void Function::LookHeroPos()
{
	char tmp[40];
	sprintf(tmp, "%.2f, %.2f", ObjectHero::getInstance()->m_Rect->getPositionX(), ObjectHero::getInstance()->m_Rect->getPositionY());
	m_HeroPos->setString(tmp);
	m_HeroPos->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(),
		ObjectHero::getInstance()->m_Rect->getPositionY() + 150));
}
void Function::GetLayer(Layer* layer)
{
	m_Layer = layer;
}
