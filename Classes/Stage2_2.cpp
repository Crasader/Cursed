#include "Default.h"

Scene* Stage2_2::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage2_2::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Stage2_2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CSoundManager::getInstance()->playBgm("Stage2_2/towerbgm.mp3", true, true, 0.25f);

	m_winSize = Director::getInstance()->getWinSize();

	SourceManager::getInstance()->LoadingSource(this);
	Function::getInstance()->GetLayer(this);
	Function::getInstance()->MakeHeroPos();

	this->scheduleUpdate();

	for (int i = 0; i < 20; i++)
		m_Once[i] = false;

	m_UpdateFirst = false;
	m_EventOn = true;

	RoadTileMap();

	m_CamControl = new CameraControl(m_winSize, Size(1920, 29680), this, ObjectHero::getInstance()->m_Rect->getPosition());
	m_CamControl->m_StageNum = 21;
	Vec2 fpos = ObjectHero::getInstance()->m_Rect->getPosition();
	m_CamControl->FadeScene(Vec2(fpos.x, fpos.y - 350));

	CreateBack();

	return true;
}

void Stage2_2::RoadTileMap()
{
	m_tmap = TMXTiledMap::create("Stage2_2/Stage2_2.tmx");
	this->addChild(m_tmap, 3);

	//Sprite* turorialback = Sprite::create("Stage2_1/Stage2_1map.png");
	//turorialback->setPosition(Vec2(1920, 640));
	//this->addChild(turorialback, 2);

	m_Ground = m_tmap->getLayer("ColideRed");//충돌박스
	m_Ground->setVisible(false);

	m_Ground2 = m_tmap->getLayer("ColideRed2");		//충돌박스
	m_Ground2->setVisible(false);

	m_Ladder = m_tmap->getLayer("ColideGreen");
	m_Ladder->setVisible(false);

	m_LadderEnd = m_tmap->getLayer("GreenEnd");
	m_LadderEnd->setVisible(false);

	m_Jump = m_tmap->getLayer("ColideBlue");
	m_Jump->setVisible(false);

	TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("Spawn");
	ValueMap& spawnPoint = Spawn_Pos->getObject("HeroSpawn");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	char str[100] = {};

	for (int i = 0; i <= 5; ++i)
	{
		sprintf(str, "Mace%d", i + 1);
		spawnPoint = Spawn_Pos->getObject(str);
		m_BarrierPos[i].x = spawnPoint["x"].asFloat();
		m_BarrierPos[i].x = m_BarrierPos[i].x - ((int)m_BarrierPos[i].x % 80);
		m_BarrierPos[i].y = spawnPoint["y"].asFloat();
		m_BarrierPos[i].y = m_BarrierPos[i].y - ((int)m_BarrierPos[i].y % 80);
	}

	sprintf(str, "Ladder");
	spawnPoint = Spawn_Pos->getObject(str);
	m_BarrierPos[6].x = spawnPoint["x"].asFloat();
	m_BarrierPos[6].y = spawnPoint["y"].asFloat();

	sprintf(str, "Test1");
	spawnPoint = Spawn_Pos->getObject(str);
	m_ItemPos[0].x = spawnPoint["x"].asFloat();
	m_ItemPos[0].y = spawnPoint["y"].asFloat();

	sprintf(str, "Warp2");
	spawnPoint = Spawn_Pos->getObject(str);
	m_ItemPos[1].x = spawnPoint["x"].asFloat();
	m_ItemPos[1].y = spawnPoint["y"].asFloat();

	Sprite* Ladder = Sprite::create("Stage2_2/Ladder.png");
	Ladder->setPosition(Vec2(m_BarrierPos[6].x - 20, m_BarrierPos[6].y - 100));
	this->addChild(Ladder, 7);

	// 무기 모션 생성
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->GetLayer(this);
	m_WeaponManager->CreateMotion();

	// 방어구 모션 생성
	extern ShieldManager* m_ShieldManager;
	m_ShieldManager->GetLayer(this);
	m_ShieldManager->CreateMotion();

	//주인공 생성및 초기화
	ObjectHero::getInstance()->GetLayer(this);
	ObjectHero::getInstance()->CreateObject(x, y);
	ObjectHero::getInstance()->m_RebornPos = Vec2(x, y);

	auto meta4 = Sprite::create("TileMap/Dummy/MetaSet4.png");
	auto ladder = Sprite::create("TileMap/Dummy/Ladder1.png");

	Vec2 ladderPos;
	Vec2 tileCoord;
	int tileGid;
	Vec2 size = m_tmap->getMapSize();

	//충돌박스 Vector에 삽입
	for (int i = 0; i < size.y; ++i)
	{
		for (int j = 0; j < size.x; ++j)
		{
			tileCoord.x = j;
			tileCoord.y = i;
			tileGid = m_Ground->getTileGIDAt(tileCoord);
			if (tileGid)
			{
				Value property2 = m_tmap->getPropertiesForGID(tileGid);
				property2 = m_Ground->getProperties();
				if (!property2.isNull())
				{
					std::string wall = property2.asValueMap()["Wall"].asString();
					if (wall == "YES")
					{
						MapRedXY[i][j] = -1;
					}
				}
			}
			if (MapRedXY[i][j] != -1)
				MapRedXY[i][j] = 0;
			///////////////////////////////////////////////////////////
			tileCoord.x = j;
			tileCoord.y = i;
			tileGid = m_Ground2->getTileGIDAt(tileCoord);
			if (tileGid)
			{
				Value property2 = m_tmap->getPropertiesForGID(tileGid);
				property2 = m_Ground2->getProperties();
				if (!property2.isNull())
				{
					std::string wall = property2.asValueMap()["Wall"].asString();
					if (wall == "YES")
					{
						MapRed2XY[i][j] = -1;
					}
				}
			}
			if (MapRed2XY[i][j] != -1)
				MapRed2XY[i][j] = 0;
			//블루박스
			tileGid = m_Jump->getTileGIDAt(tileCoord);
			if (tileGid)
			{
				Value property2 = m_tmap->getPropertiesForGID(tileGid);
				property2 = m_Jump->getProperties();
				if (!property2.isNull())
				{
					std::string wall = property2.asValueMap()["Wall"].asString();
					if (wall == "YES")
					{
						int x = tileCoord.x * m_tmap->getTileSize().width;
						int y = (size.y - 1) * 80 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxBlue->getSpriteFrame());
						spr->setTag(MetaNum::Blue);
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y + 80);
						this->addChild(spr, 5);
						SourceManager::getInstance()->m_metabox.pushBack(spr);
					}
				}
			}
			//사다리
			tileGid = m_Ladder->getTileGIDAt(tileCoord);
			if (tileGid)
			{
				Value property2 = m_tmap->getPropertiesForGID(tileGid);
				property2 = m_Ladder->getProperties();
				if (!property2.isNull())
				{
					std::string wall = property2.asValueMap()["Wall"].asString();
					if (wall == "YES")
					{
						int x = tileCoord.x * m_tmap->getTileSize().width;
						int y = (size.y - 1) * 80 - tileCoord.y * m_tmap->getTileSize().height;
						ladderPos.x = x; ladderPos.y = y;
						auto spr = Sprite::createWithSpriteFrame(meta4->getSpriteFrame());
						spr->setTag(MetaNum::GreenR);
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y + 80);
						this->addChild(spr, 5);
						SourceManager::getInstance()->m_metabox.pushBack(spr);
					}
				}
			}
			//사다리 끝(모션및 내려가기 체크용)
			tileGid = m_LadderEnd->getTileGIDAt(tileCoord);
			if (tileGid)
			{
				Value property2 = m_tmap->getPropertiesForGID(tileGid);
				property2 = m_LadderEnd->getProperties();
				if (!property2.isNull())
				{
					std::string wall = property2.asValueMap()["Wall"].asString();
					if (wall == "YES")
					{
						int x = tileCoord.x * m_tmap->getTileSize().width;
						int y = (size.y - 1) * 80 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(meta4->getSpriteFrame());
						spr->setTag(MetaNum::GreenEnd);
						spr->setFlipX(false);//오른쪽
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y + 80);
						this->addChild(spr, 5);
						SourceManager::getInstance()->m_metabox.pushBack(spr);
					}
				}
			}
		}
	}

	Sprite* FirstTile = Sprite::create("Stage2_2/FirstTile.png");
	FirstTile->setAnchorPoint(Vec2(0.0, 1.0f));
	FirstTile->setPosition(Vec2(0, 80));
	FirstTile->setTag(MetaNum::Red);
	FirstTile->setVisible(ColiideRect);
	this->addChild(FirstTile, 5);
	SourceManager::getInstance()->m_metabox.pushBack(FirstTile);

	Function::getInstance()->MakeColideWidth(MapRedXY, size, MetaNum::Red);
	Function::getInstance()->MakeColideHeight(MapRed2XY, size, MetaNum::Red);
	//Function::getInstance()->MakeColideWidth(MapMonXY, size, MetaNum::MonsterOnly);

	// 이펙트 생성
	EffectManager::getInstance()->GetLayer(this);
	EffectManager::getInstance()->CreateEffect();

	// 장애물 생성
	CreateBarrier();
}

void Stage2_2::CreateBarrier()
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierManager->m_List.clear();
	m_BarrierManager->GetLayer(this);
	m_BarrierManager->GetSource(SourceManager::getInstance());

	for (int i = 0; i < 6; i++)
	{
		ObjectBarrier* mace1 = new ObjectBarrier;
		if (i == 0 || i == 1)
			mace1->CreateIronMace(m_BarrierPos[i].x + 40, m_BarrierPos[i].y + 40, i * 180);
		else if (i == 4 || i == 5)
			mace1->CreateIronMace(m_BarrierPos[i].x + 40, m_BarrierPos[i].y + 40, (i - 4) * 180 + 90);
	}
}

void Stage2_2::UpdateBarrier()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern BarrierManager* m_BarrierManager;
		m_BarrierManager->BarrierUpdate();
	}
}

void Stage2_2::CheckEvent()
{
	//포탈이벤트
	if (m_Once[1] == false && m_PotalEvent->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
	{
		m_Once[1] = true;

		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->SetLetter();
		pad->KeyClear();
		pad->m_KeyLock = true;
		pad->DirClear();

		m_EventOn = false;

		m_CamControl->m_Camera->runAction(MoveTo::create(1.0f, Vec2(m_CamControl->m_Camera->getPositionX(), m_CamControl->m_Camera->getPositionY() + 200)));

		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(m_Potal->getPositionX(), m_Potal->getPositionY() + 180));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "저주받은 자여, 저희를 해방시켜 주세요", 0.1f, Color3B::WHITE);
		HeroChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), RemoveSelf::create(), NULL));

		m_Chatbox = Sprite::create("UI/Chat.png");
		m_Chatbox->setPosition(HeroChat1->getPosition());
		m_Chatbox->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), NULL));
		this->addChild(m_Chatbox, 9);

		RUN_WITH_DELAY(3.0f, CC_CALLBACK_0(Stage2_2::HeroChat1, this));
	}
}

void Stage2_2::Warp()
{
	//포탈이동
	if (m_Once[0] == false)
	{
		CSoundManager::getInstance()->playEffect("Sound/wind4.mp3", false, 1.0f);

		m_Once[0] = true;
		m_CamControl->m_Camera->runAction(MoveTo::create(5.0f, Vec2(m_CamControl->m_Camera->getPositionX(), 29200)));
		RUN_WITH_DELAY(5.0f, CC_CALLBACK_0(Stage2_2::HeroWarp, this));
	}
}
void Stage2_2::update(float dt)
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);

	extern Timer2* m_Timer2;
	m_Timer2->SetTime(dt);

	// UI업데이트
	pad->UIupdate();
	if (pad->m_KeyUp)
	{
		if (ObjectHero::getInstance()->m_Spr->getBoundingBox().intersectsRect(potalRect->getBoundingBox()))
		{
			this->unscheduleUpdate();
			BackScene();
			return;
		}
	}


	// 주인공 업데이트
	if (ObjectHero::getInstance()->m_Death == false)
	{
		if (ObjectHero::getInstance()->m_HoldPos == false)
			pad->m_dir.clear();

		ObjectHero::getInstance()->MoveCharacter(pad->m_dir, dt);
		ObjectHero::getInstance()->HeroUpdate();

		ObjectHero::getInstance()->GetUILayer(pad->GetLayer());
		ObjectHero::getInstance()->InitHP();

		if (m_UpdateFirst == false)
		{
			ObjectHero::getInstance()->SetHP(0);
			m_UpdateFirst = true;
		}
		m_CamControl->setViewPointCenter();
	}

	if (ObjectHero::getInstance()->m_Rect->getPositionY() > 29600)
		BackScene();

	m_Timer += dt;
	ObjectHero::getInstance()->GetTime(dt);

	CheckEvent();

	UpdateBarrier();

	// 카메라 세팅
	if (m_EventOn)
		m_CamControl->SettingCamera();

	pad->UISetposition();

	// 배경 업데이트
	UpdateBack();

	//Function::getInstance()->LookHeroPos();
}

void Stage2_2::MemoryArrange()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->MemoryArrange();

	SourceManager::getInstance()->ClearBoxVector();
	// 주인공 메모리해제
	ObjectHero::getInstance()->BulletDelete();
	this->removeChild(m_tmap);
	this->stopAllActions();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}

void Stage2_2::BackScene()
{
	MemoryArrange();
	Scene* s = Stage2_3Loading::createScene();
	Director::getInstance()->replaceScene(s);
}

//배경 그리기
void Stage2_2::CreateBack()
{
	//포탈 이벤트 체크박스
	m_PotalEvent = Sprite::create("Stage1_3/Wall2.png");
	m_PotalEvent->setVisible(ColiideRect);
	m_PotalEvent->setPosition(Vec2(m_ItemPos[0].x - 500, m_ItemPos[0].y + 60));
	this->addChild(m_PotalEvent, 5);

	//포탈
	m_Potal = Sprite::create("Stage2_2/InteractStone.png");
	m_Potal->setPosition(Vec2(m_ItemPos[0].x, m_ItemPos[0].y + 55));
	this->addChild(m_Potal, 5);

	// 맵
	Sprite* TowerMap1 = Sprite::create("Stage2_2/Tower1map.png");
	TowerMap1->setAnchorPoint(Vec2(0.0f, 0.0f));
	TowerMap1->setPosition(Vec2(0, 0));
	this->addChild(TowerMap1, 2);

	Sprite* TowerMap2 = Sprite::create("Stage2_2/Tower2map.png");
	TowerMap2->setAnchorPoint(Vec2(0.0f, 0.0f));
	TowerMap2->setPosition(Vec2(0, 28295));
	this->addChild(TowerMap2, 2);

	// 포탈
	potalRect = Sprite::create("Tutorial/PotalRect.png");
	potalRect->setPosition(Vec2(-500, -500));
	potalRect->setOpacity(120);
	this->addChild(potalRect, 11);

	backbase = Sprite::create("Stage2_2/BackBase.png");
	backbase->setAnchorPoint(Vec2(0.0f, 0.0f));
	backbase->setPosition(Vec2(0, 0));
	this->addChild(backbase, -10);

	Base[0] = Sprite::create("Stage2_2/Green1.png");
	Base[0]->setAnchorPoint(Vec2(0, 0));
	Base[0]->setPosition(Vec2(0, 0));
	this->addChild(Base[0], -8);

	Base[1] = Sprite::create("Stage2_2/Building1.png");
	Base[1]->setAnchorPoint(Vec2(0, 0));
	Base[1]->setPosition(Vec2(0, -500));
	this->addChild(Base[1], -9);

	Base[3] = Sprite::create("Stage2_2/Cloud.png");
	Base[3]->setAnchorPoint(Vec2(0, 0));
	Base[3]->setPosition(Vec2(0, 24362));
	this->addChild(Base[3], -9);

	//// 타워
	Tower[0] = Sprite::create("Stage2_2/Tower1.png");
	Tower[0]->setAnchorPoint(Vec2(0, 0));
	Tower[0]->setPosition(Vec2(0, 0));
	this->addChild(Tower[0], -5);

	Tower[1] = Sprite::create("Stage2_2/Tower2.png");
	Tower[1]->setAnchorPoint(Vec2(0, 0));
	Tower[1]->setPosition(Vec2(0, 2160));
	this->addChild(Tower[1], -5);

	Tower[2] = Sprite::create("Stage2_2/Tower3.png");
	Tower[2]->setAnchorPoint(Vec2(0, 0));
	Tower[2]->setPosition(Vec2(0, 8160));
	this->addChild(Tower[2], -5);

	Tower[3] = Sprite::create("Stage2_2/Tower4.png");
	Tower[3]->setAnchorPoint(Vec2(0, 0));
	Tower[3]->setPosition(Vec2(0, 14160));
	this->addChild(Tower[3], -5);

	Tower[4] = Sprite::create("Stage2_2/Tower5.png");
	Tower[4]->setAnchorPoint(Vec2(0, 0));
	Tower[4]->setPosition(Vec2(0, 20160));
	this->addChild(Tower[4], -5);

	Tower[5] = Sprite::create("Stage2_2/Tower6.png");
	Tower[5]->setAnchorPoint(Vec2(0, 0));
	Tower[5]->setPosition(Vec2(0, 26160));
	this->addChild(Tower[5], -5);

	//하단구름
	Cloud[0] = Sprite::create("Stage2_2/Cloud/Cloud (2).png");
	Cloud[0]->setAnchorPoint(Vec2(0, 0));
	Cloud[0]->setPosition(Vec2(0, 4358));
	this->addChild(Cloud[0], -4);

	Cloud[1] = Sprite::create("Stage2_2/Cloud/Cloud (1).png");
	Cloud[1]->setAnchorPoint(Vec2(0, 0));
	Cloud[1]->setPosition(Vec2(0, 9641));
	this->addChild(Cloud[1], -4);

	//중단구름
	Cloud[2] = Sprite::create("Stage2_2/Cloud2/Cloud (2).png");
	Cloud[2]->setAnchorPoint(Vec2(0, 0));
	Cloud[2]->setPosition(Vec2(0, 9898));
	this->addChild(Cloud[2], -3);

	Cloud[3] = Sprite::create("Stage2_2/Cloud2/Cloud (1).png");
	Cloud[3]->setAnchorPoint(Vec2(0, 0));
	Cloud[3]->setPosition(Vec2(0, 19796));
	this->addChild(Cloud[3], -3);

	//상단구름
	Cloud[4] = Sprite::create("Stage2_2/Cloud3/Cloud (2).png");
	Cloud[4]->setAnchorPoint(Vec2(0, 0));
	Cloud[4]->setPosition(Vec2(0, 9898));
	this->addChild(Cloud[4], -4);

	Cloud[5] = Sprite::create("Stage2_2/Cloud3/Cloud (1).png");
	Cloud[5]->setAnchorPoint(Vec2(0, 0));
	Cloud[5]->setPosition(Vec2(0, 19796));
	this->addChild(Cloud[5], -4);

	//움직이는  구름
	Cloud[6] = Sprite::create("Tutorial/Cloud/Cloud1.png");
	Cloud[6]->setAnchorPoint(Vec2(0, 0));
	Cloud[6]->setPosition(Vec2(0, 28000));
	this->addChild(Cloud[6], -4);

	Cloud[7] = Sprite::create("Tutorial/Cloud/Cloud4.png");
	Cloud[7]->setAnchorPoint(Vec2(0, 0));
	Cloud[7]->setPosition(Vec2(0, 28000));
	this->addChild(Cloud[7], -4);

	Cloud[8] = Sprite::create("Tutorial/Cloud/Cloud3.png");
	Cloud[8]->setAnchorPoint(Vec2(0, 0));
	Cloud[8]->setPosition(Vec2(0, 28000));
	this->addChild(Cloud[8], -4);
}

void Stage2_2::UpdateBack()
{
	Vec2 sample = m_CamControl->m_Camera->getPosition();
	sample.y -= 720;

	if (m_CamControl->m_Camera->getPositionY() > 720)
	{
		backbase->setPositionY(sample.y * 1.0f);
		Base[1]->setPositionY(sample.y * 0.97f-500);
	}


	if(Cloud[6]->getPositionX() <= 1920)
		Cloud[6]->setPositionX(Cloud[6]->getPositionX() + 2);
	else
		Cloud[6]->setPositionX(-4800);

	if (Cloud[7]->getPositionX() <= 1920)
		Cloud[7]->setPositionX(Cloud[7]->getPositionX() + 4);
	else
		Cloud[7]->setPositionX(-4800);

	if (Cloud[8]->getPositionX() <= 1920)
		Cloud[8]->setPositionX(Cloud[8]->getPositionX() + 3);
	else
		Cloud[8]->setPositionX(-4800);
}