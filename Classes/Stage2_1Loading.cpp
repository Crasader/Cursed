#include "Default.h"

#pragma once

Scene* Stage2_1Loading::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage2_1Loading::create();

	scene->addChild(layer);

	return scene;
}

bool Stage2_1Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();

	_numberOfLoadedSprites = 0;
	_numberOfSprites = 13;

	auto size = Director::getInstance()->getWinSize();

	Sprite* LoadingBack = Sprite::create("UI/LoadingStage2_1.png");
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
	_labelPercent = Label::createWithTTF("", "fonts/Marker Felt.ttf", 70);

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
	LabelTypingEffect::typeMessage(txtLabel, "Stage2_1 ", 0.1f, Color3B::GREEN);
	this->addChild(txtLabel, 15);

	auto tip = Label::createWithTTF("", "fonts/gabia_napjakBlock.ttf", 52);
	tip->setPosition(Vec2(size.width / 2, size.height / 2 - 400));
	LabelTypingEffect::typeMessage(tip, "Tip. Shift키를 누르면 무기를 바꿀수 있습니다 ", 0.1f);
	this->addChild(tip, 15);

	char str[100] = { 0 };

	//배경 리소스 2_1
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/BackBase.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Left1.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Left2.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Mid1.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Mid2.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Mid3.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Right1.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Smoke1.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Smoke2.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Smoke3.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Stage2_1map.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("Stage2_1/Stage2_1map2.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("UI/LoadingStage2_2.png", CC_CALLBACK_1(Stage2_1Loading::loadingCallBack, this));

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

void Stage2_1Loading::loadingCallBack(Texture2D *texture)
{
	++_numberOfLoadedSprites;
	char tmp[10];
	sprintf(tmp, "%d", (int)(((float)_numberOfLoadedSprites / _numberOfSprites) * 100));
	_labelPercent->setString(tmp);
}

void Stage2_1Loading::update(float dt)
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

		Scene* s2 = Stage2_1::createScene();
		Director::getInstance()->replaceScene(s2);
	}
}
