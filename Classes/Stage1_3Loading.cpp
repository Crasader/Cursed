#include "Default.h"

#pragma once

Scene* Stage1_3Loading::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage1_3Loading::create();

	scene->addChild(layer);

	return scene;
}

bool Stage1_3Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();

	_numberOfLoadedSprites = 0;
	_numberOfSprites = 1039;//367
	//_numberOfSprites = 435;//367


	auto size = Director::getInstance()->getWinSize();

	Sprite* LoadingBack = Sprite::create("UI/LoadingStage1_3.png");
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


	_labelLoading = Label::createWithTTF("LOADING", "fonts/Marker Felt.ttf", 70);
	_labelPercent = Label::createWithTTF("  0%", "fonts/Marker Felt.ttf", 70);

	_labelLoading->setPosition(Vec2(size.width / 2 - 100, size.height / 2 - 160));
	_labelPercent->setPosition(Vec2(size.width / 2 + 180, size.height / 2 - 160));
	
	this->addChild(_labelLoading, 1);
	this->addChild(_labelPercent, 1);

	Label* LabelPer = Label::createWithTTF("%", "fonts/gabia_napjakBlock.ttf", 70);
	LabelPer->setPosition(Vec2(size.width / 2 + 270, size.height / 2 - 160));
	this->addChild(LabelPer, 1);

	auto txtLabel = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 70);
	txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	txtLabel->setPosition(Vec2(size.width / 2 - 700, size.height / 2 + 400));
	LabelTypingEffect::typeMessage(txtLabel, "Stage1_3 ", 0.1f, Color3B::GREEN);
	this->addChild(txtLabel, 15);

	auto tip = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 52);
	tip->setPosition(Vec2(size.width / 2, size.height / 2 - 400));
	LabelTypingEffect::typeMessage(tip, "Tip. 화살 발사수에는 제한이 있습니다 ", 0.1f);
	this->addChild(tip, 15);

	CSoundManager::getInstance()->preloadAudioFile("Monster/Elite/bgm.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Monster/Elite/elite_claw.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Monster/Elite/elite_growling.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Monster/Elite/elite_skill.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Monster/Boss1/howling.mp3");// 로딩

	//배경 리소스1_3 - 6
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_3/Node1.png", CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_3/Node2.png", CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_3/Node3.png", CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_3/Map1.png", CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_3/Map2.png", CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_3/Map3.png", CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));

	char str[100] = { 0 };

	//엘리트보스
	for (int i = 1; i <= 25; i++)// 25
	{
		sprintf(str, "Monster/Elite/Idle/Idle (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 0; i <= 100; i++)// 101
	{
		sprintf(str, "Monster/Elite/Run/Elite-Run_%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 0; i <= 60; i++)// 61
	{
		sprintf(str, "Monster/Elite/Howling/Elite-Howling_%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 30; i++)// 30
	{
		sprintf(str, "Monster/Elite/Attack2/Attack2 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 25; i++)// 25
	{
		sprintf(str, "Monster/Elite/Attack1/Attack1 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 116; i++)// 116
	{
		sprintf(str, "Monster/Elite/Dash/Rush (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 19; i++)// 19
	{
		sprintf(str, "Monster/Elite/Skill/Skill (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 49; i++)// 49
	{
		sprintf(str, "Monster/Elite/Dead/Dead (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}

	//Stage1보스
	for (int i = 1; i <= 48; i++)// 48
	{
		sprintf(str, "Monster/Boss1/Idle/Idle (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 43; i++)// 43
	{
		sprintf(str, "Monster/Boss1/Attack1/Attack1 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 49; i++)// 49
	{
		sprintf(str, "Monster/Boss1/Attack2/Attack2 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 73; i++)// 73
	{
		sprintf(str, "Monster/Boss1/Attack3/Attack3 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 37; i++)// 37
	{
		sprintf(str, "Monster/Boss1/Attack4/Attack4 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 58; i++)// 58
	{
		sprintf(str, "Monster/Boss1/Attack5/Attack5 (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 91; i++)// 91
	{
		sprintf(str, "Monster/Boss1/Howling/Howling (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 61; i++)// 61
	{
		sprintf(str, "Monster/Boss1/Dead/Dead (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	// 아빠-Idle  21
	for (int i = 1; i <= 21; ++i)
	{
		sprintf(str, "Monster/Father/Idle/Idle (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}//아빠 Hadn - 102
	for (int i = 1; i <= 102; ++i)
	{
		sprintf(str, "Monster/Father/Hand/Hand (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	// Idle 20
	for (int i = 1; i <= 20; ++i)
	{
		sprintf(str, "Monster/Boss2/Idle/Idle (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	}
	// 악령2 1마리 생성
	for (int i = 0; i < 1; ++i)
	{
		ObjectEnemy* enemy = new ObjectEnemy;
		enemy->CreateDemon2();
		MemoryPool::getInstance()->m_Demon2Pool.push_back(enemy);
		loadingCallBack(NULL);
	}
	// 3
	sprintf(str, "Monster/Elite/EliteRect.png");
	Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	
	sprintf(str, "Monster/Elite/SampleRect.png");
	Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));
	
	sprintf(str, "Monster/Elite/WeaponRect1.png");
	Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_3Loading::loadingCallBack, this));

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

void Stage1_3Loading::loadingCallBack(Texture2D *texture)
{
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp, "%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(tmp);
}

void Stage1_3Loading::update(float dt)
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

		Scene* s2 = Stage1_3::createScene();
		Director::getInstance()->replaceScene(s2);
	}
}
