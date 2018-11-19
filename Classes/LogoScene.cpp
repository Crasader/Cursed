#include "Default.h"

Scene* LogoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LogoScene::create();
	scene->addChild(layer);
	return scene;
}

bool LogoScene::init()
{
	_numberOfLoadedSprites = 0;
	_numberOfSprites = 81;//367

	logo = Sprite::create("UI/TeamLogo.png");
	logo->setPosition(Vec2(960, 540));
	this->addChild(logo);

	char str[100] = { 0 };
	//Laser 23
	for (int i = 1; i <= 81; ++i)
	{
		sprintf(str, "UI/Title/Title (%d).png", i);
		Director::getInstance()->getTextureCache()->addImageAsync(str, CC_CALLBACK_1(LogoScene::loadingCallBack, this));
	}

	this->scheduleUpdate();

	return true;
}
void LogoScene::loadingCallBack(Texture2D *texture)
{
	++_numberOfLoadedSprites;
}

void LogoScene::update(float dt)
{
	if (_numberOfLoadedSprites == _numberOfSprites)
	{
		logo->runAction(FadeOut::create(1.0f));

		this->unscheduleUpdate();

		RUN_WITH_DELAY(1.1f, CC_CALLBACK_0(LogoScene::ChangeScene, this));
	}
}

void LogoScene::ChangeScene()
{
	Scene* s2 = MenuScene::createScene();
	Director::getInstance()->replaceScene(s2);
}