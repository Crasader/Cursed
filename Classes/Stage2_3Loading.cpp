#include "Default.h"

#pragma once

Scene* Stage2_3Loading::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage2_3Loading::create();

	scene->addChild(layer);

	return scene;
}

bool Stage2_3Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();

	_numberOfLoadedSprites = 0;
	_numberOfSprites = 329;//367

	auto size = Director::getInstance()->getWinSize();

	Sprite* LoadingBack = Sprite::create("UI/LoadingStage2_3.png");
	LoadingBack->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
	this->addChild(LoadingBack);

	Sprite* LoadBarBack = Sprite::create("UI/LoadBar1.png");
	LoadBarBack->setAnchorPoint(Vec2(0.0f, 0.0f));
	LoadBarBack->setPosition(Vec2(size.width * 0.5f - 425, size.height * 0.2f));
	this->addChild(LoadBarBack, 2);

	LoadBarEmpty = Sprite::create("UI/LoadBar2.png");
	LoadBarEmpty->setAnchorPoint(Vec2(0.0f, 0.0f));
	LoadBarEmpty->setPosition(Vec2(size.width * 0.5f - 421, size.height * 0.2f));
	this->addChild(LoadBarEmpty, 1);


	_labelLoading = Label::createWithTTF("LOADING", "fonts/Marker Felt.ttf", 90);
	_labelPercent = Label::createWithTTF("  0%", "fonts/Marker Felt.ttf", 90);

	_labelLoading->setPosition(Vec2(size.width / 2 - 100, size.height / 2 - 160));
	_labelPercent->setPosition(Vec2(size.width / 2 + 250, size.height / 2 - 160));

	this->addChild(_labelLoading, 1);
	this->addChild(_labelPercent, 1);

	auto txtLabel = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 90);
	txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	txtLabel->setPosition(Vec2(size.width / 2 - 700, size.height / 2 + 400));
	LabelTypingEffect::typeMessage(txtLabel, "Stage2_3 ", 0.1f, Color3B::GREEN);
	this->addChild(txtLabel, 15);

	auto tip = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 52);
	tip->setPosition(Vec2(size.width / 2, size.height / 2 - 400));
	LabelTypingEffect::typeMessage(tip, "Tip. Shift키를 누르면 무기를 바꿀수 있습니다 ", 0.1f);
	this->addChild(tip, 15);

	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_3/Stage2_3.png", CC_CALLBACK_1(Stage2_3Loading::loadingCallBack, this));

	char str[100] = { NULL };
	
	// Attack1 78
	for (int i = 1; i <= 78; ++i)
	{
		sprintf(str, "Monster/Boss2/Attack1/Attack1 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage2_3Loading::loadingCallBack, this));
	}
	// Attack2 78
	for (int i = 1; i <= 78; ++i)
	{
		sprintf(str, "Monster/Boss2/Attack2/Attack2 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage2_3Loading::loadingCallBack, this));
	}
	// Dead 49
	for (int i = 1; i <= 49; ++i)
	{
		sprintf(str, "Monster/Boss2/Dead/Dead (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage2_3Loading::loadingCallBack, this));
	}

	//// 총알 40개 생성
	for (int i = 0; i < 70; ++i)
	{
		BulletClass* bullet = new BulletClass;
		bullet->CreateBullet(BulletKind::HeroBullet1);
		MemoryPool::getInstance()->m_BulletPool.push_back(bullet);
		loadingCallBack(NULL);
	}

	//Fire 30
	for (int i = 1; i <= 30; ++i)
	{
		sprintf(str, "Monster/Boss2/Effect/Fire/Fire (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage2_3Loading::loadingCallBack, this));
	}

	//Laser 23
	for (int i = 1; i <= 23; ++i)
	{
		sprintf(str, "Monster/Boss2/Effect/Laser/Laser (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage2_3Loading::loadingCallBack, this));
	}

	CSoundManager::getInstance()->preloadAudioFile("Monster/Boss2/lastbossbgm1.mp3");// 로딩

	// 무기 모션 생성
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->GetLayer(this);
	m_WeaponManager->CreateMotion();

	// 방어구 모션 생성
	extern ShieldManager* m_ShieldManager;
	m_ShieldManager->GetLayer(this);
	m_ShieldManager->CreateMotion();

	ObjectHero::getInstance()->CreateObject(-500, -500);

	return true;
}

void Stage2_3Loading::loadingCallBack(Texture2D *texture)
{
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp, "%%%d %", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(tmp);
}

void Stage2_3Loading::update(float dt)
{
	Rect BarRect = LoadBarEmpty->getTextureRect();
	float per = _numberOfLoadedSprites / _numberOfSprites;
	per = 836 * per;
	BarRect.size.width = per;
	LoadBarEmpty->setTextureRect(BarRect);

	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		this->unscheduleUpdate();
		this->removeChild(_labelLoading, true);
		this->removeChild(_labelPercent, true);

		Scene* s2 = Stage2_3::createScene();
		Director::getInstance()->replaceScene(s2);
	}
}
