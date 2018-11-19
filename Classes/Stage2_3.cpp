#include "Default.h"

bool Boss2Clear;

Scene* Stage2_3::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage2_3::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Stage2_3::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CSoundManager::getInstance()->playBgm("Monster/Boss2/lastboss.mp3", true, true, 0.25f);

	m_winSize = Director::getInstance()->getWinSize();

	SourceManager::getInstance()->LoadingSource(this);
	Function::getInstance()->GetLayer(this);
	Function::getInstance()->MakeHeroPos();
	Boss2Clear = false;
	m_PotalOn = false;
	this->scheduleUpdate();

	for (int i = 0; i < 20; i++)
		m_Once[i] = false;

	m_UpdateFirst = false;
	m_EventOn = true;
	m_UpdateStart = false;
	RoadTileMap();

	m_CamControl = new CameraControl(m_winSize, Size(1920, 1600), this, ObjectHero::getInstance()->m_Rect->getPosition());
	m_CamControl->m_StageNum = 23;
	Vec2 fpos = ObjectHero::getInstance()->m_Rect->getPosition();
	m_CamControl->FadeScene(Vec2(fpos.x, fpos.y - 350));
	
	CreateBack();

	//if (Stage2_3Boss)
	{
		auto foraction = Sprite::create();
		foraction->runAction(Sequence::create(DelayTime::create(0.2f),
			CallFunc::create(CC_CALLBACK_0(Stage2_3::BossAct1, this)), NULL));
		this->addChild(foraction);
		EffectManager::getInstance()->effect[9]->setDelayPerUnit(0.015f);
	}
	return true;
}

void Stage2_3::BossAct1()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->KeyClear();
	pad->DirClear();
	pad->SetMask();
	pad->m_KeyLock = true;
	pad->DoRain();
	pad->DoRain();

	m_EventOn = false;
	m_CamControl->m_Camera->runAction(Sequence::create(DelayTime::create(1.5f),
		MoveTo::create(1.5f, Vec2(m_winSize.width, 700)),
		CallFunc::create(CC_CALLBACK_0(Stage2_3::BossAct2,this)), NULL));
}

void Stage2_3::RoadTileMap()
{
	m_tmap = TMXTiledMap::create("Stage2_3/Stage2_3.tmx");
	this->addChild(m_tmap, 3);

	m_Ground = m_tmap->getLayer("ColideRed");//충돌박스
	m_Ground->setVisible(false);

	TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("Spawn");
	ValueMap& spawnPoint = Spawn_Pos->getObject("Hero");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Boss");
	m_EnemyPos[0].x = spawnPoint["x"].asFloat();
	m_EnemyPos[0].y = spawnPoint["y"].asFloat();

	char str[100] = {};

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
	ObjectHero::getInstance()->m_BossBullet = true;

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
		}
	}

	Function::getInstance()->MakeColideWidth(MapRedXY, size, MetaNum::Red);

	// 이펙트 생성
	EffectManager::getInstance()->GetLayer(this);
	EffectManager::getInstance()->CreateEffect();

	// 장애물 생성
	CreateBarrier();

	extern EnemyManager* m_EnemyManager;
	m_EnemyManager->m_List.clear();
	m_EnemyManager->GetLayer(this);
	m_EnemyManager->GetSource(SourceManager::getInstance());
}

void Stage2_3::CreateBarrier()
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierManager->m_List.clear();
	m_BarrierManager->GetLayer(this);
	m_BarrierManager->GetSource(SourceManager::getInstance());
}

void Stage2_3::UpdateBarrier()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern BarrierManager* m_BarrierManager;
		m_BarrierManager->BarrierUpdate();
	}
}

void Stage2_3::UpdateEnemy()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern EnemyManager* m_EnemyManager;
		m_EnemyManager->Update();
	}
}

void Stage2_3::update(float dt)
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	if (pad->m_BossHP_Exit)
		pad->BossHPUpdate(m_Boss->m_HP);
	extern Timer2* m_Timer2;
	m_Timer2->SetTime(dt);

	// UI업데이트
	pad->UIupdate();
	if (pad->m_KeyUp)
	{
		if (ObjectHero::getInstance()->m_Spr->getBoundingBox().intersectsRect(potalRect->getBoundingBox()))
		{
			EffectManager::getInstance()->EffectSwitch(EffectName::Teloport, potalRect->getPositionX(), potalRect->getPositionY(), false);
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

	m_Timer += dt;
	ObjectHero::getInstance()->GetTime(dt);

	UpdateBarrier();

	UpdateEnemy();

	// 카메라 세팅
	if (m_EventOn)
		m_CamControl->SettingCamera();

	pad->UISetposition();

	// 배경 업데이트
	if(m_UpdateStart)
		UpdateBack();

	if (Boss2Clear )
	{
		Boss2Clear = false;
		CreatePotal();
	}
	//Function::getInstance()->LookHeroPos();
}

void Stage2_3::CreatePotal()
{
	m_PotalOn = true;

	Sprite* potal = Sprite::create("Stage2_3/SavePoint.png");
	potal->setPosition(Vec2(960, 1000));
	this->addChild(potal, 2);

	Sprite* tile = Sprite::create("Stage2_3/TowerTileSet2.png");
	tile->setAnchorPoint(Vec2(0, 1));
	tile->setPosition(Vec2(850, 880));
	tile->setTag(MetaNum::Red);
	SourceManager::getInstance()->m_metabox.pushBack(tile);
	this->addChild(tile, 3);

	potalRect = Sprite::create("Stage1_3/Wall2.png");
	potalRect->setPosition(Vec2(960, 1000));
	potalRect->setVisible(false);
	this->addChild(potalRect, 3);
}

void Stage2_3::BackScene()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->KeyClear();
	pad->m_KeyLock = true;
	pad->CreateWhite();

	ObjectHero::getInstance()->m_Spr->runAction(FadeOut::create(1.5f));
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->CloseWeapon->runAction(FadeOut::create(1.5f));

	for (int i = 0; i < 8; ++i)
		m_MidTile[i]->stopAllActions();
}

void Stage2_3::UpdateBack()
{
	//중앙
	for(int i = 0; i < 8; ++i)
		m_MidRed[i]->setPosition(m_MidTile[i]->getPosition());

	//왼쪽
	for (int i = 0; i < 4; ++i)
		m_LeftRed[i]->setPosition(m_LeftTile[i]->getPosition());

	for (int i = 0; i < 4; ++i)
	{
		m_LeftTile[i]->setPositionY(m_LeftTile[i]->getPositionY()-2.5f);
		if (m_LeftTile[i]->getPositionY() <= 0)
			m_LeftTile[i]->setPositionY(1600);
	}

	//오른쪽
	for (int i = 0; i < 4; ++i)
		m_RightRed[i]->setPosition(m_RightTile[i]->getPosition());

	for (int i = 0; i < 4; ++i)
	{
		m_RightTile[i]->setPositionY(m_RightTile[i]->getPositionY() + 2.5f);
		if (m_RightTile[i]->getPositionY() >= 1600)
			m_RightTile[i]->setPositionY(0);
	}
}

void Stage2_3::MoveRedTile(Sprite* sender, int num)
{
	MoveTo* MAct[8];

	MAct[0] = MoveTo::create(1.5f, Vec2(1210, 1200));
	MAct[1] = MoveTo::create(1.5f, Vec2(1310, 920));
	MAct[2] = MoveTo::create(1.5f, Vec2(1210, 640));
	MAct[3] = MoveTo::create(1.5f, Vec2(880, 460));//1층으로
	MAct[4] = MoveTo::create(1.5f, Vec2(550, 640));
	MAct[5] = MoveTo::create(1.5f, Vec2(450, 920));
	MAct[6] = MoveTo::create(1.5f, Vec2(550, 1200));
	MAct[7] = MoveTo::create(1.5f, Vec2(880, 1380));//5층으로

	if (num == 0)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[0], MAct[1], MAct[2], MAct[3], MAct[4], MAct[5], MAct[6], MAct[7],NULL)));
	}
	else if (num == 1)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[1], MAct[2], MAct[3], MAct[4], MAct[5], MAct[6], MAct[7], MAct[0], NULL)));
	}
	else if (num == 2)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[2], MAct[3], MAct[4], MAct[5], MAct[6], MAct[7], MAct[0], MAct[1], NULL)));
	}
	else if (num == 3)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[3], MAct[4], MAct[5], MAct[6], MAct[7], MAct[0], MAct[1], MAct[2], NULL)));
	}
	else if (num == 4)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[4], MAct[5], MAct[6], MAct[7], MAct[0], MAct[1], MAct[2], MAct[3], NULL)));
	}
	else if (num == 5)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[5], MAct[6], MAct[7], MAct[0], MAct[1], MAct[2], MAct[3], MAct[4], NULL)));
	}
	else if (num == 6)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[6], MAct[7], MAct[0], MAct[1], MAct[2], MAct[3], MAct[4], MAct[5], NULL)));
	}
	else if (num == 7)
	{
		sender->runAction(RepeatForever::create(Sequence::create(
			MAct[7], MAct[0], MAct[1], MAct[2], MAct[3], MAct[4], MAct[5], MAct[6], NULL)));
	}
}

void Stage2_3::CreateBack()
{
	Sprite* back = Sprite::create("Stage2_3/Back/Tower.png");
	back->setAnchorPoint(Vec2(0, 0));
	back->setPosition(Vec2(0, 0));
	this->addChild(back, 0);

	Cloud[0] = Sprite::create("Stage2_3/Back/Cloud1.png");
	Cloud[0]->setAnchorPoint(Vec2(0, 0));
	Cloud[0]->setPosition(Vec2(0, 0));
	Cloud[0]->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(2.0f,Vec2(1920,0)),Place::create(Vec2(0,0)),NULL)));
	this->addChild(Cloud[0], -3);

	Cloud[1] = Sprite::createWithSpriteFrame(Cloud[0]->getSpriteFrame());
	Cloud[1]->setAnchorPoint(Vec2(0, 0));
	Cloud[1]->setPosition(Vec2(-1920, 0));
	Cloud[1]->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(2.0f, Vec2(0, 0)), Place::create(Vec2(-1920, 0)), NULL)));
	this->addChild(Cloud[1], -3);

	Cloud[2] = Sprite::create("Stage2_3/Back/Cloud2.png");
	Cloud[2]->setAnchorPoint(Vec2(0, 0));
	Cloud[2]->setPosition(Vec2(0, 0));
	Cloud[2]->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(5.0f, Vec2(1920, 0)), Place::create(Vec2(0, 0)), NULL)));
	this->addChild(Cloud[2], -2);

	Cloud[3] = Sprite::createWithSpriteFrame(Cloud[2]->getSpriteFrame());
	Cloud[3]->setAnchorPoint(Vec2(0, 0));
	Cloud[3]->setPosition(Vec2(0, 0));
	Cloud[3]->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(5.0f, Vec2(0, 0)), Place::create(Vec2(-1920, 0)), NULL)));
	this->addChild(Cloud[3], -2);

	Cloud[4] = Sprite::create("Stage2_3/Back/Cloud3.png");
	Cloud[4]->setAnchorPoint(Vec2(0, 0));
	Cloud[4]->setPosition(Vec2(0, 900));
	Cloud[4]->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(8.0f, Vec2(1920, 900)), Place::create(Vec2(0, 900)), NULL)));
	this->addChild(Cloud[4], -1);

	Cloud[5] = Sprite::createWithSpriteFrame(Cloud[4]->getSpriteFrame());
	Cloud[5]->setAnchorPoint(Vec2(0, 0));
	Cloud[5]->setPosition(Vec2(0, 900));
	Cloud[5]->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(8.0f, Vec2(0, 900)), Place::create(Vec2(-1920, 900)), NULL)));
	this->addChild(Cloud[5], -1);

	//5층
	m_MidTile[0] = Sprite::create("Stage2_2/TowerTile2.png");
	m_MidTile[0]->setAnchorPoint(Vec2(0, 1));
	m_MidTile[0]->setPosition(Vec2(880, 1380));
	this->addChild(m_MidTile[0], 3);

	m_MidRed[0] = Function::getInstance()->CreateRedBlock(Vec2(880, 1380), 2);
	//MoveRedTile(m_MidTile[0], 0);

	//4층
	for (int i = 1; i <= 2; i++)
	{
		m_MidTile[i] = Sprite::createWithSpriteFrame(m_MidTile[0]->getSpriteFrame());
		m_MidTile[i]->setAnchorPoint(Vec2(0, 1));
		m_MidTile[i]->setPosition(Vec2(i == 1 ? 550 : 1600 - 550 + 160, 1200));
		this->addChild(m_MidTile[i], 3);

		m_MidRed[i] = Function::getInstance()->CreateRedBlock(m_MidTile[i]->getPosition(), 2);
	}
	//MoveRedTile(m_MidTile[1], 1);
	//MoveRedTile(m_MidTile[2], 2);

	//3층
	for (int i = 3; i <= 4; i++)
	{
		m_MidTile[i] = Sprite::createWithSpriteFrame(m_MidTile[0]->getSpriteFrame());
		m_MidTile[i]->setAnchorPoint(Vec2(0, 1));
		m_MidTile[i]->setPosition(Vec2(i == 3 ? 450 : 1600 - 450 + 160, 920));
		this->addChild(m_MidTile[i], 3);

		m_MidRed[i] = Function::getInstance()->CreateRedBlock(m_MidTile[i]->getPosition(), 2);
	}
	//MoveRedTile(m_MidTile[3], 3);
	//MoveRedTile(m_MidTile[4], 4);

	//2층
	for (int i = 5; i <= 6; i++)
	{
		m_MidTile[i] = Sprite::createWithSpriteFrame(m_MidTile[0]->getSpriteFrame());
		m_MidTile[i]->setAnchorPoint(Vec2(0, 1));
		m_MidTile[i]->setPosition(Vec2(i == 5 ? 550 : 1600 - 550 + 160, 640));
		this->addChild(m_MidTile[i], 3);

		m_MidRed[i] = Function::getInstance()->CreateRedBlock(m_MidTile[i]->getPosition(), 2);
	}
	//MoveRedTile(m_MidTile[5], 5);
	//MoveRedTile(m_MidTile[6], 6);

	//1층
	m_MidTile[7] = Sprite::createWithSpriteFrame(m_MidTile[0]->getSpriteFrame());
	m_MidTile[7]->setAnchorPoint(Vec2(0, 1));
	m_MidTile[7]->setPosition(Vec2(880, 460));
	this->addChild(m_MidTile[7], 3);

	m_MidRed[7] = Function::getInstance()->CreateRedBlock(m_MidTile[7]->getPosition(), 2);
	//MoveRedTile(m_MidTile[7], 7);

	//왼쪽사이드
	m_LeftTile[0] = Sprite::create("Stage2_3/OneTile.png");
	m_LeftTile[0]->setAnchorPoint(Vec2(0, 1));
	m_LeftTile[0]->setPosition(Vec2(290, 360));
	this->addChild(m_LeftTile[0], 3);
	m_LeftRed[0] = Function::getInstance()->CreateRedBlock(m_LeftTile[0]->getPosition(), 1);

	m_LeftTile[1] = Sprite::createWithSpriteFrame(m_LeftTile[0]->getSpriteFrame());
	m_LeftTile[1]->setAnchorPoint(Vec2(0, 1));
	m_LeftTile[1]->setPosition(Vec2(290, 760));
	this->addChild(m_LeftTile[1], 3);
	m_LeftRed[1] = Function::getInstance()->CreateRedBlock(m_LeftTile[1]->getPosition(), 1);

	m_LeftTile[2] = Sprite::createWithSpriteFrame(m_LeftTile[0]->getSpriteFrame());
	m_LeftTile[2]->setAnchorPoint(Vec2(0, 1));
	m_LeftTile[2]->setPosition(Vec2(290, 1160));
	this->addChild(m_LeftTile[2], 3);
	m_LeftRed[2] = Function::getInstance()->CreateRedBlock(m_LeftTile[2]->getPosition(), 1);

	m_LeftTile[3] = Sprite::createWithSpriteFrame(m_LeftTile[0]->getSpriteFrame());
	m_LeftTile[3]->setAnchorPoint(Vec2(0, 1));
	m_LeftTile[3]->setPosition(Vec2(290, 1560));
	this->addChild(m_LeftTile[3], 3);
	m_LeftRed[3] = Function::getInstance()->CreateRedBlock(m_LeftTile[3]->getPosition(), 1);

	//오른쪽사이드
	m_RightTile[0] = Sprite::createWithSpriteFrame(m_LeftTile[0]->getSpriteFrame());
	m_RightTile[0]->setAnchorPoint(Vec2(0, 1));
	m_RightTile[0]->setPosition(Vec2(1540, 360));
	this->addChild(m_RightTile[0], 3);
	m_RightRed[0] = Function::getInstance()->CreateRedBlock(m_RightTile[0]->getPosition(), 1);

	m_RightTile[1] = Sprite::createWithSpriteFrame(m_RightTile[0]->getSpriteFrame());
	m_RightTile[1]->setAnchorPoint(Vec2(0, 1));
	m_RightTile[1]->setPosition(Vec2(1540, 760));
	this->addChild(m_RightTile[1], 3);
	m_RightRed[1] = Function::getInstance()->CreateRedBlock(m_RightTile[1]->getPosition(), 1);

	m_RightTile[2] = Sprite::createWithSpriteFrame(m_RightTile[0]->getSpriteFrame());
	m_RightTile[2]->setAnchorPoint(Vec2(0, 1));
	m_RightTile[2]->setPosition(Vec2(1540, 1160));
	this->addChild(m_RightTile[2], 3);
	m_RightRed[2] = Function::getInstance()->CreateRedBlock(m_RightTile[2]->getPosition(), 1);

	m_RightTile[3] = Sprite::createWithSpriteFrame(m_RightTile[0]->getSpriteFrame());
	m_RightTile[3]->setAnchorPoint(Vec2(0, 1));
	m_RightTile[3]->setPosition(Vec2(1540, 1560));
	this->addChild(m_RightTile[3], 3);
	m_RightRed[3] = Function::getInstance()->CreateRedBlock(m_RightTile[3]->getPosition(), 1);
}

void Stage2_3::Makethunder()
{
	if (m_PotalOn == false)
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->Makethunder();
		RUN_WITH_DELAY(7.0f, CC_CALLBACK_0(Stage2_3::Makethunder, this));
	}
}