#include "Default.h"

#pragma once

Scene* Stage1_1Loading::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage1_1Loading::create();

	scene->addChild(layer);

	return scene;
}


bool Stage1_1Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();

	LoadFinish = false;
	_numberOfLoadedSprites = 0;
	_numberOfSprites = 12;

	auto size = Director::getInstance()->getWinSize();

	_labelLoading = Label::createWithTTF("LOADING", "fonts/Marker Felt.ttf", 90);
	_labelPercent = Label::createWithTTF("  %0", "fonts/Marker Felt.ttf", 90);

	_labelLoading->setPosition(Vec2(size.width / 2 - 100, size.height / 2 + 100));
	_labelPercent->setPosition(Vec2(size.width / 2 + 150, size.height / 2 + 100));

	this->addChild(_labelLoading, 1);
	this->addChild(_labelPercent, 1);

	// 公扁 葛记 积己
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->GetLayer(this);
	m_WeaponManager->CreateMotion();

	// 规绢备 葛记 积己
	extern ShieldManager* m_ShieldManager;
	m_ShieldManager->GetLayer(this);
	m_ShieldManager->CreateMotion();

	ObjectHero::getInstance()->CreateObject(-500, -500);

	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Back1.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Back2.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Back3.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/BackTop1.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/BackTop2.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Base.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Front1.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Front2.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/pillar1.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/pillar2.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Top1.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_1/Back/Top2.png", CC_CALLBACK_1(Stage1_1Loading::loadingCallBack, this));

	return true;
}

void Stage1_1Loading::loadingCallBack(Texture2D *texture)
{
	if (LoadFinish == false)
	{
		if (_labelPercent != NULL)
		{
			++_numberOfLoadedSprites;
			char tmp[10];
			sprintf(tmp, "%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
			_labelPercent->setString(tmp);
		}
	}
}

void Stage1_1Loading::update(float dt)
{
	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		LoadFinish = true;
		this->unscheduleUpdate();
		this->removeChild(_labelLoading, true);
		this->removeChild(_labelPercent, true);
		Scene* s = Stage1_1::createScene();
		Director::getInstance()->replaceScene(s);
	}
}

