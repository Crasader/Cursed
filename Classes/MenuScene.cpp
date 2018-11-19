#include "Default.h"

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();
	scene->addChild(layer, 1);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CSoundManager::getInstance()->playBgm("Sound/Terminal_D.mp3", true, true, 0.7f);

	m_winSize = Director::getInstance()->getWinSize();
	
	this->RunTitle();

	m_Effect[0] = Sprite::create("MenuScene/Effect1.png");
	m_Effect[0]->setPosition(Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f));
	m_Effect[0]->runAction(
		RepeatForever::create(
		Sequence::create(
		MoveTo::create(15.0f,Vec2(m_winSize.width*1.5f, m_winSize.height*0.5f)),
		Place::create(Vec2(-m_winSize.width*0.5f, m_winSize.height*0.5f)),
		MoveTo::create(15.0f,Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f)),
		MoveTo::create(15.0f, Vec2(m_winSize.width*1.5f, m_winSize.height*0.5f)),
		NULL)));
	this->addChild(m_Effect[0], 1);

	m_Effect[1] = Sprite::create("MenuScene/Effect2.png");
	m_Effect[1]->setPosition(Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f));
	m_Effect[1]->runAction(
		RepeatForever::create(
			Sequence::create(
				MoveTo::create(10.0f, Vec2(m_winSize.width*1.5f, m_winSize.height*0.5f)),
				Place::create(Vec2(-m_winSize.width*0.5f, m_winSize.height*0.5f)),
				MoveTo::create(10.0f, Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f)),
				MoveTo::create(10.0f, Vec2(m_winSize.width*1.5f, m_winSize.height*0.5f)),
				NULL)));
	this->addChild(m_Effect[1], 1);

	m_Effect[2] = Sprite::create("MenuScene/Effect3.png");
	m_Effect[2]->setPosition(Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f));
	m_Effect[2]->runAction(
		RepeatForever::create(
			Sequence::create(
				MoveTo::create(12.0f, Vec2(m_winSize.width*1.5f, m_winSize.height*0.5f)),
				Place::create(Vec2(-m_winSize.width*0.5f, m_winSize.height*0.5f)),
				MoveTo::create(12.0f, Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f)),
				MoveTo::create(12.0f, Vec2(m_winSize.width*1.5f, m_winSize.height*0.5f)),
				NULL)));
	this->addChild(m_Effect[2], 1);

	m_once = false;
	auto label = Label::createWithTTF("Press any key to Start", "fonts/Assassin$.ttf", 60);
	label->setPosition(Vec2(m_winSize.width*0.5f, 150));
	label->setColor(Color3B(7, 181, 232));
	label->runAction(RepeatForever::create(Sequence::create(
		FadeOut::create(1.0f),DelayTime::create(0.5f),FadeIn::create(1.0f),
		DelayTime::create(2.0f),
		NULL)));
	this->addChild(label, 3);

	//키보드 리스너
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

	//RunTitle();
	m_twice = false;
	return true;
}
void MenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	GameMenu1(NULL);
}
void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}
//선택화면으로이동
void MenuScene::GameMenu1(Object* pSender)
{
	if (m_once == false)
	{
		m_once = true;
		Scene* s = TransitionFade::create(1.0f, LoadingScene::createScene());
		Director::getInstance()->replaceScene(s);
	}
}

void MenuScene::update(float dt)
{
	//UI업데이트
	//GameUI* pad = (GameUI*)this->getParent()->getChildByTag(200);
	//pad->UIupdate();
}

void MenuScene::RunTitle()
{
	m_TitleAni = new Animation();
	
	Vector<SpriteFrame*> frames;

	char str[100] = { 0 };
	for (int i = 1; i <= 81; i++)// 걷기 
	{
		sprintf(str, "UI/Title/Title (%d).png", i);
		SpriteFrame* frame = SpriteFrame::create(str, Rect(0, 0, 1920, 1080));
		frames.pushBack(frame);
	}
	Animation* test1 = new Animation();
	test1->initWithSpriteFrames(frames, 0.05f);
	Animate* test = Animate::create(test1);

	BackGround = Sprite::create("UI/Title/Title (1).png");
	BackGround->setPosition(Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f));
	
	BackGround->runAction(RepeatForever::create(test));
	this->addChild(BackGround,2);
	
}