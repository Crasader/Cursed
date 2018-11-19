#include "Default.h"

#pragma once

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();
	_numberOfLoadedSprites = 0;
	_numberOfSprites = 181;

	//사운드 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/player_attack1.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/player_attack2.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/player_attack3.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/player_attack4.mp3");// 로딩
	
	CSoundManager::getInstance()->preloadAudioFile("Sound/MySound/Male_Jump_Grunt06.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Retreat.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/bowfullback.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/player_death2.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/arrowattacked.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/player_walk.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/arrowpass.mp3");// 로딩

	auto size = Director::getInstance()->getWinSize();

	Sprite* LoadingBack = Sprite::create("UI/LoadingTutorial.png");
	LoadingBack->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
	this->addChild(LoadingBack);

	Sprite* LoadBarBack = Sprite::create("UI/LoadBar1.png");
	LoadBarBack->setAnchorPoint(Vec2(0.0f, 0.0f));
	LoadBarBack->setPosition(Vec2(size.width * 0.5f - 425, size.height * 0.2f));
	this->addChild(LoadBarBack,2);

	LoadBarEmpty = Sprite::create("UI/LoadBar2.png");
	LoadBarEmpty->setAnchorPoint(Vec2(0.0f, 0.0f));
	LoadBarEmpty->setPosition(Vec2(size.width * 0.5f - 421, size.height * 0.2f ));
	this->addChild(LoadBarEmpty, 1);

	_labelLoading = Label::createWithTTF("LOADING", "fonts/Assassin$.ttf", 90);
	_labelPercent = Label::createWithTTF("%0", "fonts/Marker Felt.ttf", 90);

	_labelLoading->setPosition(Vec2(size.width / 2 - 100, size.height / 2 - 160));
	_labelPercent->setPosition(Vec2(size.width / 2 + 250, size.height / 2 - 160));

	this->addChild(_labelLoading, 1);
	this->addChild(_labelPercent, 1);

	auto txtLabel = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 70);
	txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	txtLabel->setPosition(Vec2(size.width / 2 - 700, size.height / 2 + 400));
	LabelTypingEffect::typeMessage(txtLabel, "Tutorial ", 0.1f, Color3B::GREEN);
	this->addChild(txtLabel, 15);

	auto tip = Label::createWithTTF("", "fonts/Assassin$.ttf", 52);
	tip->setPosition(Vec2(size.width / 2 , size.height / 2 - 400));
	LabelTypingEffect::typeMessage(tip, "Tip: Press [Shift] Change Weapon ", 0.1f);
	this->addChild(tip, 15);

	char str[100] = { 0 };

	//주인공
	for (int i = 1; i <= 24; i++)// 24
	{
		sprintf(str, "Hero/bow/bowAttack1%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 9; i++)// 9
	{
		sprintf(str, "Hero/climb/climb%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 9; i++)// 9
	{
		sprintf(str, "Hero/climb_fixed/climb%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 7; i++)// 7
	{
		sprintf(str, "Hero/HeroAttack/Attack1_%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 7; i++)// 7
	{
		sprintf(str, "Hero/HeroAttack/Attack2_%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 0; i <= 4; i++)// 5
	{
		sprintf(str, "Hero/HeroDash/dash_0%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 11; i++)// 11
	{
		sprintf(str, "Hero/HeroDeath/Death%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 8; i <= 14; i++)// 7
	{
		sprintf(str, "Hero/HeroFall/Jump%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 25; i++)// 25
	{
		sprintf(str, "Hero/HeroIdle/idle%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 14; i++)// 14
	{
		sprintf(str, "Hero/HeroJump/Jump%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	for (int i = 1; i <= 16; i++)// 16
	{
		sprintf(str, "Hero/HeroRun/Run/run (%d)", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	// 무기 모션 생성
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->GetLayer(this);
	m_WeaponManager->CreateMotion();

	// 방어구 모션 생성
	extern ShieldManager* m_ShieldManager;
	m_ShieldManager->GetLayer(this);
	m_ShieldManager->CreateMotion();

	ObjectHero::getInstance()->CreateObject(-500, -500);

	for (int i = 1; i <= 8; ++i)// 8
	{
		sprintf(str, "Tutorial/Cloud/Cloud%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	}
	//// 총알 20개 생성
	for (int i = 0; i < 20; ++i)
	{
		BulletClass* bullet = new BulletClass;
		bullet->CreateBullet(BulletKind::HeroBullet1);
		MemoryPool::getInstance()->m_BulletPool.push_back(bullet);
		loadingCallBack(NULL);
	}
	//2
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Right/Cage_Potal.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/CloseBack.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

	//7
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Left/Front_Left_Ground.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Left/Front_Left_Ground2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Left/Front_Left_Ground3.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Left/LeftShadow.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Left/LeftTree.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Left/Stone1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Left/Stone2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	
	// 7
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Mid/Mid_Back.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Mid/Mid_Back2.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Mid/Mid_Back3.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Mid/Mid_Grand.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Mid/Mid_Mountain.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Mid/Mid_Plant1.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Mid/Mid_Tree.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	
	// 2
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Right/Cage_Effect.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/Right/CageBack.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

	// 1
	Director::getInstance()->getTextureCache()->addImageAsync("Tutorial/TutorialBack.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

	return true;
}

void LoadingScene::update(float dt)
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
		Scene* s = TransitionFade::create(1.0f, Tutorial::createScene());
		Director::getInstance()->replaceScene(s);
	}
}
void LoadingScene::loadingCallBack(Texture2D *texture)
{
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp, "%%%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(tmp);
}

void LoadingScene::ChangeScene()
{
	this->removeChild(_labelLoading, true);
	this->removeChild(_labelPercent, true);
	Scene* s = TransitionFade::create(1.0f, Stage01::createScene());
	Director::getInstance()->replaceScene(s);
}
