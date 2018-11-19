#ifndef __STAGE1_3_H__
#define __STAGE1_3_H__

#include "Default.h"

class Stage1_3 : public Layer
{
public:
	ShadowLayer* _shadowLayer;
	float _timer;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage1_3);

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
	Sprite* m_Chat;
	bool m_SceneStop;
	Label* EmotionLabel;
	ObjectEnemy* m_Demon;
	Boss* m_Elite;
	Boss* m_Boss1;
	void Stage1_3EventCheck();
	bool m_Lock;
	Sprite* m_Spine;
	Sprite* potalRect;
	void BackScene();//메뉴화면으로 돌아가기
	void GameOver();
	void FatherEvent();
	void BossEvent1()
	{
		CSoundManager::getInstance()->playBgm("Sound/BossBgm.mp3", true, true, 0.4f);

		Label* FatherChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		FatherChat1->setPosition(Vec2(m_SavePoint[8].x-500, m_SavePoint[8].y));
		FatherChat1->setVisible(true);
		this->addChild(FatherChat1, 10);
		LabelTypingEffect::typeMessage(FatherChat1, "네놈 끝까지 방해만 하는구나", 0.1f, Color3B::WHITE);
		FatherChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), NULL));

		m_ChatBox->setPosition(FatherChat1->getPosition());
		m_ChatBox->setScaleX(1.0f);
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(3.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(3.7f, CC_CALLBACK_0(Stage1_3::BossChat2, this));
	}
	void BossChat2()
	{
		Vec2 hPos = ObjectHero::getInstance()->m_Rect->getPosition();
		Label* FatherChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		FatherChat1->setPosition(Vec2(hPos.x, hPos.y + 200));
		FatherChat1->setVisible(true);
		this->addChild(FatherChat1, 10);
		LabelTypingEffect::typeMessage(FatherChat1, "내 아버지와 마을을 이렇게 만든게 네녀석이냐", 0.1f, Color3B::WHITE);
		FatherChat1->runAction(Sequence::create(DelayTime::create(3.5f), Hide::create(), NULL));

		m_ChatBox->setPosition(FatherChat1->getPosition());
		m_ChatBox->setScaleX(1.0f);
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(3.5f), Hide::create(), NULL));
		
		RUN_WITH_DELAY(4.2f, CC_CALLBACK_0(Stage1_3::BossChat3, this));
	}

	void BossChat3()
	{
		Vec2 hPos = ObjectHero::getInstance()->m_Rect->getPosition();
		Label* FatherChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		FatherChat1->setPosition(Vec2(m_SavePoint[8].x - 500, m_SavePoint[8].y));
		FatherChat1->setVisible(true);
		this->addChild(FatherChat1, 10);
		LabelTypingEffect::typeMessage(FatherChat1, "대화는 필요없다, 어서 해치워라 나의 종이여", 0.1f, Color3B::WHITE);
		FatherChat1->runAction(Sequence::create(DelayTime::create(3.5f), Hide::create(), NULL));

		m_ChatBox->setPosition(FatherChat1->getPosition());
		m_ChatBox->setScaleX(1.0f);
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(3.5f), Hide::create(), NULL));

		RUN_WITH_DELAY(4.0f, CC_CALLBACK_0(Stage1_3::BossChat4, this));

	}
	void BossChat4()
	{
		m_Boss1->AnimationSwitch(10);

		RUN_WITH_DELAY(1.3f, CC_CALLBACK_0(Stage1_3::BossChat5, this));

	}
	void BossChat5()
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->m_KeyLock = false;
		pad->Boss1HPCreate(m_Boss1->m_HP);
		//보스2와 채팅
		m_Boss1->m_Lock = false;
	}

	void BossChat6()
	{
		Vec2 hPos = ObjectHero::getInstance()->m_Rect->getPosition();
		Label* FatherChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		FatherChat1->setPosition(Vec2(m_SavePoint[8].x - 500, m_SavePoint[8].y));
		FatherChat1->setVisible(true);
		this->addChild(FatherChat1, 10);
		LabelTypingEffect::typeMessage(FatherChat1, "네놈 제법이군, 두고보자", 0.1f, Color3B::WHITE);
		FatherChat1->runAction(Sequence::create(DelayTime::create(2.5f), Hide::create(), NULL));

		m_ChatBox->setPosition(FatherChat1->getPosition());
		m_ChatBox->setScaleX(1.0f);
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(2.5f), Hide::create(), NULL));

		Boss2->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f),NULL));

		CSoundManager::getInstance()->stopAllBgms();
		CSoundManager::getInstance()->playBgm("Sound/Sound/cavebgm2.mp3", true, true, 1.0f);
		
	}
	void BossEvent2()
	{
		m_Boss1->AnimationSwitch(10);
	}
	void GameClear()
	{
		exit(0);
		CCDirector::sharedDirector()->end();
	}

	bool m_Event[5];
	void Stg1_3Event()
	{
		m_Once[5] = true;
	}
	void Stg1_3Event2()
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->EliteHPCreate(m_Elite->m_HP);
		m_EventOn = true;
	}
	void EliteRoar()
	{
		CSoundManager::getInstance()->playEffect("Sound/MySound/Dragon_Roar5.mp3", false, 1.0f);
	}

	//업데이트
	void GuideCheck();
	Sprite* m_Guide[2];
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//아버지 이벤트
	ObjectEnemy* m_Enemy1;
	Animation* m_FatherEffect[2];
	Sprite* m_Father;
	void FatherCreate();

	//타일맵
	Vec2 Portal;
	int MapRedXY[23][228];
	int MapMonXY[23][228];
	int MapRed2XY[23][228];

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
	void CreateBack();
	
	Sprite* m_ChatBox;
	void FatherChat1()
	{
		m_Father->setPosition(Vec2(m_Father->getPositionX()-20, m_Father->getPositionY()));
		m_Father->stopAllActions();
		m_Father->runAction(Animate::create(m_FatherEffect[1]));

		Label* FatherChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		FatherChat1->setPosition(Vec2(m_Father->getPositionX(), 1000));
		FatherChat1->setVisible(true);
		this->addChild(FatherChat1, 10);
		LabelTypingEffect::typeMessage(FatherChat1, "아들아, 이 곳은 위험하다 도망치거라", 0.1f, Color3B::WHITE);
		FatherChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), NULL));

		m_ChatBox->setPosition(FatherChat1->getPosition());
		m_ChatBox->setScaleX(1.0f);
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(3.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(4.0f, CC_CALLBACK_0(Stage1_3::HeroChat2, this));
	}
	void HeroChat2()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1000));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "무슨 말씀이세요, 제가 도와 드릴게요 ", 0.06f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(3.5f), Hide::create(), NULL));
		
		m_ChatBox->setPosition(HeroChat1->getPosition());
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(3.5f), Hide::create(), NULL));

		RUN_WITH_DELAY(4.0f, CC_CALLBACK_0(Stage1_3::FatherChat3, this));
	}
	void FatherChat3()
	{
		m_Father->setPosition(Vec2(m_Father->getPositionX() + 20, m_Father->getPositionY()));
		m_Father->stopAllActions();
		m_Father->runAction(Animate::create(m_FatherEffect[0]));

		Label* FatherChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		FatherChat1->setPosition(Vec2(m_Father->getPositionX(), 1000));
		FatherChat1->setVisible(true);
		this->addChild(FatherChat1, 10);
		LabelTypingEffect::typeMessage(FatherChat1, "안돼 나는 이미 틀렸어 윽.. 크윽....", 0.1f, Color3B::WHITE);
		FatherChat1->runAction(Sequence::create(DelayTime::create(5.0f), Hide::create(), NULL));
		
		m_ChatBox->setPosition(FatherChat1->getPosition());
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(5.0f), Hide::create(), NULL));

		RUN_WITH_DELAY(5.5f, CC_CALLBACK_0(Stage1_3::HeroChat3, this));
	}
	
	void HeroChat3()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1000));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "아버지!!!!!", 0.06f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(3.5f), Hide::create(), NULL));

		m_ChatBox->setPosition(HeroChat1->getPosition());
		m_ChatBox->setScaleX(0.5f);
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(3.5f), Hide::create(), NULL));

		m_Father->runAction(Sequence::create(FadeOut::create(1.0f),NULL));
		RUN_WITH_DELAY(4.5f, CC_CALLBACK_0(Stage1_3::FatherEnemy, this));

	}
	
	void FatherEnemy()
	{
		m_Enemy1->SetPosObject(m_Father->getPositionX(), m_Father->getPositionY() + 40);
		RUN_WITH_DELAY(1.5f, CC_CALLBACK_0(Stage1_3::HeroChat4, this));
	}
	
	void HeroChat4()
	{
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1000));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "크읏,,, 이럴수가", 0.06f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(2.5f), Hide::create(), NULL));

		m_ChatBox->setPosition(HeroChat1->getPosition());
		m_ChatBox->setScaleX(0.5f);
		m_ChatBox->runAction(Sequence::create(Show::create(), DelayTime::create(2.5f), Hide::create(), NULL));

		RUN_WITH_DELAY(2.0f, CC_CALLBACK_0(Stage1_3::ChatEventEnd, this));
	}
	void ChatEventEnd()
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->KeyClear();
		pad->m_KeyLock = false;
		m_EventOn = true;

		CC_SAFE_RELEASE(m_FatherEffect[0]);
		CC_SAFE_RELEASE(m_FatherEffect[1]);
	}
	Sprite* Boss2;
	void Boss2Idle(Vec2 pos)
	{
		Vector<SpriteFrame*> frames;

		char str[100] = { 0 };
		for (int i = 1; i <= 20; i++)// 걷기 
		{
			sprintf(str, "Monster/Boss2/Idle/Idle (%d).png", i);
			SpriteFrame* frame = SpriteFrame::create(str, Rect(0, 0, 188, 457));
			frames.pushBack(frame);
		}
		Animation* test1 = new Animation();
		test1->initWithSpriteFrames(frames, 0.05f);
		Animate* test = Animate::create(test1);

		Boss2 = Sprite::create("Monster/Boss2/Idle/Idle (1).png");
		Boss2->setPosition(Vec2(pos.x+100, pos.y));
		Boss2->setScale(0.8f);
		Boss2->runAction(RepeatForever::create(test));
		this->addChild(Boss2, 2);
	}
};

extern bool EliteClear;
extern bool Boss1Clear;
#endif 
