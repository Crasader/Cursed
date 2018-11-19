#ifndef __STAGE2_3_H__
#define __STAGE2_3_H__

#include "Default.h"

class Stage2_3 : public Layer
{
public:
	ShadowLayer* _shadowLayer;
	float _timer;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage2_3);

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
	bool m_PotalOn;
	Boss* m_Boss;
	Sprite* m_Chatbox;
	bool m_SceneStop;
	Label* EmotionLabel;
	ObjectEnemy* m_Demon;
	Boss* m_Elite;
	Boss* m_Boss1;
	bool m_Lock;
	Sprite* m_Spine;
	Sprite* potalRect;
	void BackScene();//메뉴화면으로 돌아가기
	void GameOver();
	void BossAct1();
	void BossAct2()
	{
		m_Boss = new Boss;
		m_Boss->CreateBoss2(m_EnemyPos[0]);
		m_Boss->m_Lock = true;
		m_Boss->AnimationSwitch(BossMotion::BossIdle);

		CSoundManager::getInstance()->playEffect("Monster/Boss2/bosstalk1.mp3", false, 1.0f);
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(960,1000));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "용케 여기까지 오다니", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(2.0f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox = Sprite::create("UI/Chat.png");
		m_Chatbox->setPosition(HeroChat1->getPosition());
		m_Chatbox->setVisible(true);
		m_Chatbox->runAction(Sequence::create(DelayTime::create(2.0f), Hide::create(), NULL));
		this->addChild(m_Chatbox, 9);

		RUN_WITH_DELAY(3.1f, CC_CALLBACK_0(Stage2_3::BossAct3, this));
	}
	void BossAct3()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(960, 1000));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "이곳에 온걸 후회하게 될거다", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox->setVisible(true);
		m_Chatbox->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(3.1f, CC_CALLBACK_0(Stage2_3::BossAct4, this));
	}
	void BossAct4()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), ObjectHero::getInstance()->m_Rect->getPositionY() + 190));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "내 소중한 사람들을 위해 끝까지 싸우겠다", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox->setVisible(true);
		m_Chatbox->setPosition(HeroChat1->getPosition());
		m_Chatbox->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(3.1f, CC_CALLBACK_0(Stage2_3::BossAct5, this));
	}
	void BossAct5()
	{
		CSoundManager::getInstance()->playEffect("Monster/Boss2/bosstalk2.mp3", false, 1.0f);

		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(960, 1000));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "우습군,, 발버둥 쳐봐라", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(2.0f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox->setVisible(true);
		m_Chatbox->setPosition(HeroChat1->getPosition());
		m_Chatbox->runAction(Sequence::create(DelayTime::create(2.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(2.5f, CC_CALLBACK_0(Stage2_3::BossAct6, this));
	}
	void BossAct6()
	{
		Makethunder();
		m_EventOn = true;
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->m_KeyLock = false;
		pad->m_BossHP_Exit = true;
		pad->BossHPCreate(m_Boss->m_HP);
		m_UpdateStart = true;
		for(int i = 0; i < 8; ++i)
			MoveRedTile(m_MidTile[i], i);

		RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(Stage2_3::BossAct7, this));
	}

	void BossAct7()
	{
		m_Boss->m_Lock = false;
	}
	bool m_Event[5];

	//업데이트
	bool m_UpdateStart;
	void GuideCheck();
	Sprite* m_Guide[2];
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//타일맵
	Sprite* m_Potal;//맵테스트
	Sprite* m_PotalEvent;

	Sprite* m_MidTile[10];
	Sprite* m_MidRed[10];

	Sprite* m_LeftTile[10];
	Sprite* m_LeftRed[10];

	Sprite* m_RightTile[10];
	Sprite* m_RightRed[10];

	Vec2 Portal;
	int MapRedXY[20][24];
	int MapMonXY[20][24];
	int MapRed2XY[20][24];

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
	void CreatePotal();

	//MoveTo* MAct[8];
	void CreateBack();
	void MoveRedTile(Sprite* sender,int num);
	//void CloudUpdate();
	
	void Makethunder();
};
extern bool Boss2Clear;

#endif 
