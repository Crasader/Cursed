#include "Default.h"

#pragma once

Scene* Stage1_2Loading::createScene()
{
	auto scene = Scene::create();
	auto layer = Stage1_2Loading::create();
	scene->addChild(layer);
	return scene;
}

bool Stage1_2Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();
	_numberOfLoadedSprites = 0;
	_numberOfSprites = 813;//679

	auto size = Director::getInstance()->getWinSize();

	Sprite* LoadingBack = Sprite::create("UI/LoadingStage1_2.png");
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

	_labelLoading = Label::createWithTTF("LOADING", "fonts/gabia_napjakBlock.ttf", 70);
	_labelPercent = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 70);

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
	LabelTypingEffect::typeMessage(txtLabel, "Stage1_2 ", 0.1f, Color3B::GREEN);
	this->addChild(txtLabel, 15);

	auto tip = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 52);
	tip->setPosition(Vec2(size.width / 2, size.height / 2 - 400));
	LabelTypingEffect::typeMessage(tip, "Tip. Shift키를 누르면 무기를 바꿀수 있습니다 ", 0.1f);
	this->addChild(tip, 15);

	//사운드
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/cavebgm2.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/MySound/Ghost_walk2.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/MySound/Ghost_appear1.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/MySound/Door_MysticalOpen3.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/MySound/Quake_Tunnel_Loop2.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/MySound/Magic_Spell_Shield6.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/MySound/Ghost_attack.mp3");// 로딩

	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/monster1_death.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/ladybug_unburrow.mp3");// 로딩
	CSoundManager::getInstance()->preloadAudioFile("Sound/Sound/ladybug_exploding.mp3");// 로딩

	char str[100] = { 0 };

	//배경 리소스1_2 - 2
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_2/Basic.png", CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage1_2/Stage1_2_2.png", CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));

	//주인공
	for (int i = 1; i <= 24; i++)// 24
	{
		sprintf(str, "Hero/bow/bowAttack1%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 9; i++)// 9
	{
		sprintf(str, "Hero/climb/climb%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 9; i++)// 9
	{
		sprintf(str, "Hero/climb_fixed/climb%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 7; i++)// 7
	{
		sprintf(str, "Hero/HeroAttack/Attack1_%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 7; i++)// 7
	{
		sprintf(str, "Hero/HeroAttack/Attack2_%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 0; i <= 4; i++)// 5
	{
		sprintf(str, "Hero/HeroDash/dash_0%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 11; i++)// 11
	{
		sprintf(str, "Hero/HeroDeath/Death%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 8; i <= 14; i++)// 7
	{
		sprintf(str, "Hero/HeroFall/Jump%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 25; i++)// 25
	{
		sprintf(str, "Hero/HeroIdle/idle%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 14; i++)// 14
	{
		sprintf(str, "Hero/HeroJump/Jump%d", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 16; i++)// 16
	{
		sprintf(str, "Hero/HeroRun/Run/run (%d)", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}

	//몬스터1
	for (int i = 1; i <= 36; i++)// 36
	{
		sprintf(str,"Monster/Monster1/idle/Idle%d.png",i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 27; i++)// 27
	{
		sprintf(str, "Monster/Monster1/run/Run%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 24; i++)// 24
	{
		sprintf(str, "Monster/Monster1/attack/Attack%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 28; i++)// 28
	{
		sprintf(str, "Monster/Monster1/attack_ready/Attack%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 4; i++)// 4
	{
		sprintf(str, "Monster/Monster1/attack-idle/Attack%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 15; i++)// 15
	{
		sprintf(str, "Monster/Monster1/idle-walk/walk%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	//몬스터2
	for (int i = 0; i <= 36; i++)// 37
	{
		sprintf(str, "Monster/Monster2/attack/mon02_attack_%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 0; i <= 17; i++)// 18
	{
		sprintf(str, "Monster/Monster2/die/mon02_die_%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 0; i <= 13; i++)// 14
	{
		sprintf(str, "Monster/Monster2/idle/mon02_idle_%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 34; i++)// 34
	{
		sprintf(str, "Monster/Monster2/Object/object%d.png.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 0; i <= 15; i++)// 16
	{
		sprintf(str, "Monster/Monster2/walk/mon02_walk_%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	// LadyBug
	for (int i = 1; i <= 16; i++)// 16
	{
		sprintf(str, "Monster/Ladybug/walk/walk%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 36; i++)// 36
	{
		sprintf(str, "Monster/Ladybug/attack/attack%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 13; i++)// 13
	{
		sprintf(str, "Monster/Ladybug/Boom/Boom%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 24; i++)// 24
	{
		sprintf(str, "Monster/Ladybug/unburrow/unburrow%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}

	// Bat - 21
	for (int i = 1; i <= 21; i++)// 21
	{
		sprintf(str, "Monster/Bat/idle/bat_run_%d.png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}

	// Demon2
	for (int i = 1; i <= 21; i++)// 21
	{
		sprintf(str, "Monster/Demon2/Run/Run (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 81; i++)// 81
	{
		sprintf(str, "Monster/Demon2/Howling/Howling (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 49; i++)// 49
	{
		sprintf(str, "Monster/Demon2/Damage/Damage (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	for (int i = 1; i <= 21; i++)// 21
	{
		sprintf(str, "Monster/Demon2/Attack/Attack (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(Stage1_2Loading::loadingCallBack, this));
	}
	////몬스터1 15마리 생성 ( 근접 )
	for (int i = 0; i < 15; ++i)
	{
		ObjectEnemy* enemy = new ObjectEnemy;
		enemy->CreateObject();
		MemoryPool::getInstance()->m_Enemy1Pool.push_back(enemy);
		loadingCallBack(NULL);
	}
	////몬스터2 5마리 생성 ( 원거리접 )
	for (int i = 0; i < 5; ++i)
	{
		ObjectEnemy* enemy = new ObjectEnemy;
		enemy->CreateObject2();
		MemoryPool::getInstance()->m_Enemy2Pool.push_back(enemy);
		loadingCallBack(NULL);
	}
	////무당벌레 13마리 생성
	for (int i = 0; i < 13; ++i)
	{
		MiniEnemy* enemy = new MiniEnemy;
		enemy->CreateLadybug();
		MemoryPool::getInstance()->m_LadyBugPool.push_back(enemy);
		loadingCallBack(NULL);
	}
	////폭탄벌레 20마리 생성
	for (int i = 0; i < 20; ++i)
	{
		MiniEnemy* enemy = new MiniEnemy;
		enemy->CreateBombbug();
		MemoryPool::getInstance()->m_BombBugPool.push_back(enemy);
		loadingCallBack(NULL);
	}
	//// 박쥐 5마리 생성
	for (int i = 0; i < 5; ++i)
	{
		MiniEnemy* enemy = new MiniEnemy;
		enemy->CreateBat();
		MemoryPool::getInstance()->m_BatPool.push_back(enemy);
		loadingCallBack(NULL);
	}
	//// 콜로니 4마리 생성
	for (int i = 0; i < 4; ++i)
	{
		MiniEnemy* enemy = new MiniEnemy;
		enemy->CreateColony();
		MemoryPool::getInstance()->m_Colony.push_back(enemy);
		loadingCallBack(NULL);
	}
	//// 악령 1마리 생성
	/*for (int i = 0; i < 1; ++i)
	{
		ObjectEnemy* enemy = new ObjectEnemy;
		enemy->CreateDemon();
		MemoryPool::getInstance()->m_DemonPool.push_back(enemy);
		loadingCallBack(NULL);
	}*/
	
	//// 총알 80개 생성
	for (int i = 0; i < 80; ++i)
	{
		BulletClass* bullet = new BulletClass;
		bullet->CreateBullet(BulletKind::HeroBullet1);
		MemoryPool::getInstance()->m_BulletPool.push_back(bullet);
		loadingCallBack(NULL);
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

	return true;
}

void Stage1_2Loading::loadingCallBack(Texture2D *texture)
{
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp, "%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(tmp);
}

void Stage1_2Loading::ChangeScene()
{
	this->removeChild(_labelLoading, true);
	this->removeChild(_labelPercent, true);
	Scene* s = TransitionFade::create(1.0f, Stage1_2::createScene());
	Director::getInstance()->replaceScene(s);
}

void Stage1_2Loading::update(float dt)
{
	Rect BarRect = LoadBarEmpty->getTextureRect();
	float per = _numberOfLoadedSprites / _numberOfSprites;
	per = 836 * per;
	BarRect.size.width = per;
	LoadBarEmpty->setTextureRect(BarRect);

	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		std::list<ObjectEnemy*> *m_list = &MemoryPool::getInstance()->m_Enemy1Pool;
		int size = m_list->size();
		m_list = &MemoryPool::getInstance()->m_Enemy2Pool;
		size += m_list->size();

		if (size != 20)
			return;
		this->unscheduleUpdate();
		this->removeChild(_labelLoading, true);
		this->removeChild(_labelPercent, true);

		Scene* s2 = Stage1_2::createScene();
		Director::getInstance()->replaceScene(s2);
	}
}
