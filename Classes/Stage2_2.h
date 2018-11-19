#ifndef __STAGE2_2_H__
#define __STAGE2_2_H__

#include "Default.h"

class Stage2_2 : public Layer
{
public:
	ShadowLayer* _shadowLayer;
	float _timer;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage2_2);

	//Default
	CameraControl* m_CamControl;
	void CameraAction1();
	Size m_winSize;
	SourceManager* m_Soucre;
	void MemoryArrange();
	bool m_GameSwitch;
	float m_SaveNum;
	bool m_UpdateFirst;
	void setViewPointCenter();

	//게임이벤트(게임오버)
	Sprite* m_Chatbox;
	bool m_SceneStop;
	Label* EmotionLabel;
	ObjectEnemy* m_Demon;
	Boss* m_Elite;
	Boss* m_Boss1;
	void CheckEvent();
	bool m_Lock;
	Sprite* m_Spine;
	Sprite* potalRect;
	void BackScene();//메뉴화면으로 돌아가기
	void GameOver();


	bool m_Event[5];

	//업데이트
	void GuideCheck();
	Sprite* m_Guide[2];
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//타일맵
	Sprite* m_Potal;//맵테스트
	Sprite* m_PotalEvent;
	Vec2 Portal;
	int MapRedXY[372][24];
	int MapMonXY[372][24];
	int MapRed2XY[372][24];

	void RoadTileMap();
	TMXTiledMap* m_tmap;
	TMXLayer* m_background1;
	TMXLayer* m_background2;
	TMXLayer* m_background3;
	TMXLayer* m_background4;
	TMXLayer* m_background5;
	TMXLayer* m_background6;

	TMXLayer* m_Test;
	TMXLayer* m_MonsterCol;
	TMXLayer* m_Ground;
	TMXLayer* m_Ground2;
	TMXLayer* m_Jump;
	TMXLayer* m_Ladder;
	TMXLayer* m_LadderEnd;

	//장애물
	void UpdateBarrier();
	Vec2 m_BarrierPos[12];
	void CreateBarrier();

	//오브젝트 ( 아이템 ), ( 세이브포인트 )
	Vec2 m_SavePoint[10];
	Vec2 m_ItemPos[10];
	void CreateItem();

	//객체(Block),(Enemy)
	Vec2 m_EnemyPos[20];
	
	void CreateEnemy();
	void CheckColide();
	void UpdateEnemy();

	Sprite* m_Interact[20];

	//카메라
	bool m_EventOn;
	void CheckCamEvent();
	bool m_Once[20];
	void SetLetter();
	void SetLetter2();


	//터치
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

	//배경오브젝트
	Sprite *backbase;
	Sprite* Base[10];
	Sprite* Tower[10];
	Sprite* Cloud[10];
	void CreateBack();

	//채팅
	void HeroChat1()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), m_Potal->getPositionY() + 180));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "뭐지? 어떻게 말을?", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(1.5f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox->setPosition(HeroChat1->getPosition());
		m_Chatbox->setVisible(true);
		m_Chatbox->setScaleX(0.6f);
		m_Chatbox->runAction(Sequence::create(DelayTime::create(1.5f), Hide::create(), NULL));

		RUN_WITH_DELAY(2.0f, CC_CALLBACK_0(Stage2_2::HeroChat2, this));
	}
	void HeroChat2()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(m_Potal->getPositionX(), m_Potal->getPositionY() + 180));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "저희는 이탑의 주인에게 봉인된 영혼들입니다", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox->setPosition(HeroChat1->getPosition());
		m_Chatbox->setScaleX(1.0f);
		m_Chatbox->setVisible(true);
		m_Chatbox->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(3.2f, CC_CALLBACK_0(Stage2_2::HeroChat3, this));
	}
	void HeroChat3()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(m_Potal->getPositionX(), m_Potal->getPositionY() + 180));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "당신을 이 탑의 꼭대기로 보내드릴게요.", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox->setVisible(true);
		m_Chatbox->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(3.1f, CC_CALLBACK_0(Stage2_2::HeroChat4, this));
	}
	void HeroChat4()
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->m_dir.push_back(PadDir::RightMove);

		RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(Stage2_2::HeroChat5, this));
	}
	void HeroChat5()
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		
		pad->KeyClear();
		pad->DirClear();
		pad->m_KeyLock = true;

		RUN_WITH_DELAY(0.3f, CC_CALLBACK_0(Stage2_2::HeroChat6, this));
	}
	void HeroChat6()
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->SetLetter();
		pad->m_KeyLock = true;

		EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
			ObjectHero::getInstance()->m_Rect->getPositionX(), ObjectHero::getInstance()->m_Rect->getPositionY() + 60, false);
		ObjectHero::getInstance()->m_HoldPos = false;
		ObjectHero::getInstance()->m_Spr->runAction(FadeOut::create(1.0f));

		RUN_WITH_DELAY(1.6f, CC_CALLBACK_0(Stage2_2::Warp, this));
	}
	void Warp();
	void HeroWarp()
	{
		ObjectHero::getInstance()->m_Rect->setPosition(m_ItemPos[1].x, m_ItemPos[1].y-230);
		EffectManager::getInstance()->EffectSwitch(EffectName::Flame1,
			ObjectHero::getInstance()->m_Rect->getPositionX(), ObjectHero::getInstance()->m_Rect->getPositionY() + 60, false);
		ObjectHero::getInstance()->m_HoldPos = true;
		ObjectHero::getInstance()->m_Spr->setOpacity(1000);
		ObjectHero::getInstance()->m_Spr->setVisible(true);

		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->m_KeyLock = false;
		//ObjectHero::getInstance()->m_Spr->setZOrder(8);
		//RUN_WITH_DELAY(0.2f, CC_CALLBACK_0(Stage2_2::HeroSetting(), this));
	}
	void HeroSetting()
	{

	}
};

#endif 
