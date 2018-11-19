#include "Default.h"

Scene* Stage1_2::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage1_2::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Stage1_2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	CSoundManager::getInstance()->playBgm("Sound/Sound/cavebgm2.mp3", true, true, 1.0f);
	//CSoundManager::getInstance()->preloadAudioFile("Sound/HeroAttack/Male_LS_L_AttackGrunt06.mp3");// 로딩
	//CSoundManager::getInstance()->preloadAudioFile("Sound/Hero/Male_Jump_Grunt01.mp3");// 로딩
	//CSoundManager::getInstance()->preloadAudioFile("Sound/Hero/Male_LS_H_Death02.mp3");// 로딩

	m_Lock = false;

	SourceManager::getInstance()->LoadingSource(this);
	Function::getInstance()->GetLayer(this);

	m_winSize = Director::getInstance()->getWinSize();

	m_Timer = 0;
	m_UpdateFirst = false;

	RoadTileMap();

	m_CamControl = new CameraControl(m_winSize, Size(7360, 5200), this, ObjectHero::getInstance()->m_Rect->getPosition());
	m_CamControl->m_StageNum = 12;
	Vec2 fpos = ObjectHero::getInstance()->m_Rect->getPosition();
	m_CamControl->FadeScene(Vec2(fpos.x,fpos.y-350));

	CreateBack();

	auto foract = Sprite::create();
	foract->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create(CC_CALLBACK_0(Stage1_2::CameraAction1, this)),
		NULL));
	this->addChild(foract);

	this->runAction(FadeOut::create(1.0f));

	for (int i = 0; i < 10; i++)
		m_Once[i] = false;

	this->scheduleUpdate();

	return true;
}
void Stage1_2::UpdateTirgger()
{
	this->scheduleUpdate();
}
void Stage1_2::CameraAction1()
{
	/*if (Camera::getDefaultCamera() != NULL && m_Once[0] == false)
	{
		m_Once[0] = true;
		Camera::getDefaultCamera()->runAction(Sequence::create(
			DelayTime::create(1.0f),
			EaseOut::create(ScaleTo::create(0.7f, 0.7f, 0.7f),2.0f),NULL));
	}
	else if(m_Once[0] && m_Once[1] == false)
	{
		m_Once[0] = false; m_Once[1] = true;
		Camera::getDefaultCamera()->runAction(Sequence::create(
			EaseOut::create(ScaleTo::create(1.0f, 1.0f, 1.0f), 2.0f), NULL));
	}
	else if (m_Once[3] && m_Once[4] == false)
	{
		Camera::getDefaultCamera()->runAction(Sequence::create(
			EaseOut::create(ScaleTo::create(0.7f, 0.7f, 0.7f), 2.0f), NULL));
	}
	else if (m_Once[4] && m_Once[5] == false)
	{
		Camera::getDefaultCamera()->runAction(Sequence::create(
			EaseOut::create(ScaleTo::create(0.7f, 0.7f, 0.7f), 2.0f),NULL));
	}
	else if (m_Once[5] && m_Once[6] == false)
	{
		Camera::getDefaultCamera()->runAction(Sequence::create(
			EaseOut::create(ScaleTo::create(1.5f, 1.5f, 1.5f), 2.0f),
			DelayTime::create(1.0f),
			EaseOut::create(ScaleTo::create(0.7f, 0.7f, 0.7f), 2.0f), NULL));
	}*/
}

void Stage1_2::RoadTileMap()
{
	//세이브 여부
	//m_SaveNum = UserDefault::getInstance()->getFloatForKey("Clear_Time", 0.0f);
	m_SaveNum = 0;

	//타일맵 로드
	m_tmap = TMXTiledMap::create("Stage1_2/Stage1_2.tmx");
	this->addChild(m_tmap, 3, 11);

	Sprite* turorialback = Sprite::create("Stage1_2/Stage1_2_2.png");
	turorialback->setPosition(Vec2(3680, 2600));
	this->addChild(turorialback, 2);

	m_background1 = m_tmap->getLayer("Left2");
	m_background1->setVisible(false);

	m_background2 = m_tmap->getLayer("Top2");
	m_background2->setVisible(false);

	m_background2 = m_tmap->getLayer("Top3");
	m_background2->setVisible(false);

	m_background2 = m_tmap->getLayer("BigTile");
	m_background2->setVisible(false);

	m_background3 = m_tmap->getLayer("Basic2");
	m_background3->setVisible(false);

	m_background4 = m_tmap->getLayer("Right2");
	m_background4->setVisible(false);

	m_background5 = m_tmap->getLayer("Bottom");
	m_background5->setVisible(false);

	m_background5 = m_tmap->getLayer("Bottom2");
	m_background5->setVisible(false);

	m_Ground = m_tmap->getLayer("ColideRed");		//충돌박스
	m_Ground->setVisible(false);
	
	m_Ground2 = m_tmap->getLayer("ColideRed2");		//충돌박스
	m_Ground2->setVisible(false);

	m_Jump = m_tmap->getLayer("ColideBlue2");
	m_Jump->setVisible(false);

	m_MonsterCol = m_tmap->getLayer("MonsterColide");
	m_MonsterCol->setVisible(false);

	m_Ladder = m_tmap->getLayer("ColideGreen");
	m_Ladder->setVisible(false);

	m_LadderEnd = m_tmap->getLayer("GreenEnd");
	m_LadderEnd->setVisible(false);

	TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("Spawn");
	ValueMap& spawnPoint = Spawn_Pos->getObject("Hero2");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	
	Animation* ani = Animation::create();
	ani->setDelayPerUnit(0.03f);

	char str2[100] = {};
	for (int i = 1; i <= 21; i++)// 걷기 
	{
		sprintf(str2, "Monster/Bat/idle/bat_run_%d.png", i);
		ani->addSpriteFrameWithFileName(str2);
	}

	Sprite* bat1 = Sprite::create("Monster/Bat/idle/bat_run_1.png");
	bat1->setScale(0.4);
	bat1->setPosition(Vec2(x + 1000, y + 700));
	this->addChild(bat1, 15);
	bat1->runAction(RepeatForever::create(Animate::create(ani)));
	
	// 무기 모션 생성
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->GetLayer(this);
	m_WeaponManager->CreateMotion();

	// 방어구 모션 생성
	extern ShieldManager* m_ShieldManager;
	m_ShieldManager->GetLayer(this);
	m_ShieldManager->CreateMotion();

	// 주인공 생성및 초기화
	ObjectHero::getInstance()->GetLayer(this);
	ObjectHero::getInstance()->CreateObject(x + 500, y+200);
	ObjectHero::getInstance()->m_RebornPos = Vec2(x+500, y);

	char str[100] = {};
	for (int i = 0; i < 14; ++i)
	{
		sprintf(str, "Monster%d", i+1);
		spawnPoint = Spawn_Pos->getObject(str);
		m_EnemyPos[i].x = spawnPoint["x"].asFloat();
		m_EnemyPos[i].y = spawnPoint["y"].asFloat();
	}

	for (int i = 1; i < 8; ++i)
	{
		sprintf(str, "LadyBug%d",i);
		spawnPoint = Spawn_Pos->getObject(str);
		m_EnemyPos[i+13].x = spawnPoint["x"].asFloat();
		m_EnemyPos[i+13].x = m_EnemyPos[i+13].x - ((int)m_EnemyPos[i+13].x % 80);
		m_EnemyPos[i+13].y = spawnPoint["y"].asFloat();
		m_EnemyPos[i+13].y = m_EnemyPos[i+13].y - ((int)m_EnemyPos[i+13].y % 80);
	}
	
	for (int i = 1; i <= 4; ++i)
	{
		sprintf(str, "BombBug%d", i);
		spawnPoint = Spawn_Pos->getObject(str);
		m_EnemyPos[i + 20].x = spawnPoint["x"].asFloat();
		m_EnemyPos[i + 20].x = m_EnemyPos[i + 20].x - ((int)m_EnemyPos[i + 20].x % 80);
		m_EnemyPos[i + 20].y = spawnPoint["y"].asFloat();
		m_EnemyPos[i + 20].y = m_EnemyPos[i + 20].y - ((int)m_EnemyPos[i + 20].y % 80);
	}

	//콜로니
	for (int i = 1; i <= 4; ++i)
	{
		sprintf(str, "Colony%d", i);
		spawnPoint = Spawn_Pos->getObject(str);
		m_EnemyPos[i + 24].x = spawnPoint["x"].asFloat();
		m_EnemyPos[i + 24].x = m_EnemyPos[i + 24].x - ((int)m_EnemyPos[i + 24].x % 80);
		m_EnemyPos[i + 24].y = spawnPoint["y"].asFloat();
		m_EnemyPos[i + 24].y = m_EnemyPos[i + 24].y - ((int)m_EnemyPos[i + 24].y % 80);
	}
	spawnPoint = Spawn_Pos->getObject("Barrier1");
	m_BarrierPos[0].x = spawnPoint["x"].asFloat();
	m_BarrierPos[0].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier2");
	m_BarrierPos[1].x = spawnPoint["x"].asFloat();
	m_BarrierPos[1].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier3");
	m_BarrierPos[2].x = spawnPoint["x"].asFloat();
	m_BarrierPos[2].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier4");
	m_BarrierPos[3].x = spawnPoint["x"].asFloat();
	m_BarrierPos[3].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier5");
	m_BarrierPos[4].x = spawnPoint["x"].asFloat();
	m_BarrierPos[4].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier6");
	m_BarrierPos[5].x = spawnPoint["x"].asFloat();
	m_BarrierPos[5].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier7");
	m_BarrierPos[6].x = spawnPoint["x"].asFloat();
	m_BarrierPos[6].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier8");
	m_BarrierPos[7].x = spawnPoint["x"].asFloat();
	m_BarrierPos[7].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Barrier9");
	m_BarrierPos[8].x = spawnPoint["x"].asFloat();
	m_BarrierPos[8].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Floor1");
	m_BarrierPos[9].x = spawnPoint["x"].asFloat();
	m_BarrierPos[9].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Floor2");
	m_BarrierPos[10].x = spawnPoint["x"].asFloat();
	m_BarrierPos[10].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Item1");
	m_ItemPos[0].x = spawnPoint["x"].asFloat();
	m_ItemPos[0].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Item2");
	m_ItemPos[1].x = spawnPoint["x"].asFloat();
	m_ItemPos[1].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Item3");
	m_ItemPos[2].x = spawnPoint["x"].asFloat();
	m_ItemPos[2].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Potal1");
	Portal.x = spawnPoint["x"].asFloat();
	Portal.y = spawnPoint["y"].asFloat();

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
			// 몬스터 콜라이더
			tileCoord.x = j;
			tileCoord.y = i;
			tileGid = m_MonsterCol->getTileGIDAt(tileCoord);
			if (tileGid)
			{
				Value property2 = m_tmap->getPropertiesForGID(tileGid);
				property2 = m_MonsterCol->getProperties();
				if (!property2.isNull())
				{
					std::string wall = property2.asValueMap()["Wall"].asString();
					if (wall == "YES")
					{
						MapMonXY[i][j] = -1;
					}
				}
			}
			if (MapMonXY[i][j] != -1)
				MapMonXY[i][j] = 0;
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
	
	Function::getInstance()->MakeColideWidth(MapRedXY, size, MetaNum::Red);
	Function::getInstance()->MakeColideHeight(MapRed2XY, size, MetaNum::Red);
	Function::getInstance()->MakeColideWidth(MapMonXY, size, MetaNum::MonsterOnly);

	// 사다리
	auto Ladder2 = Sprite::create("Stage1_2/MapLadder2.png");
	Ladder2->setFlipX(true);
	Ladder2->setAnchorPoint(Vec2(0.5f, 0.0f));
	Ladder2->setPosition(Vec2(ladderPos.x+20, ladderPos.y-15));
	this->addChild(Ladder2, 3);

	// 이펙트 생성
	EffectManager::getInstance()->GetLayer(this);
	EffectManager::getInstance()->CreateEffect();


	// 적생성
	CreateEnemy();

	// 아이템박스 생성
	CreateItem();

	// 장애물 생성
	CreateBarrier();
	return;
}

//장애물 생성
void Stage1_2::CreateBarrier()
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierManager->m_List.clear();
	m_BarrierManager->GetLayer(this);
	m_BarrierManager->GetSource(SourceManager::getInstance());

	for (int i = 0; i < 11; ++i)
	{
		Sprite* Sphere1 = Sprite::create("Barrier/FixSphere.png");
		Sphere1->setAnchorPoint(Vec2(0, 0));
		Sphere1->setPosition(Vec2(m_BarrierPos[7].x - 160 + (i*200), m_BarrierPos[7].y - 83));
		this->addChild(Sphere1, 2);

		Sprite* Sphere2 = Sprite::create("Barrier/FixSphere2.png");
		Sphere2->setAnchorPoint(Vec2(0, 0));
		Sphere2->setPosition(Vec2(m_BarrierPos[7].x - 160 + 116 + (i*200), m_BarrierPos[7].y - 83));
		this->addChild(Sphere2, 1);
	}

	SphereRect = Sprite::create("Barrier/SphereRect.png");
	SphereRect->setPosition(Vec2(m_BarrierPos[7].x - 40, m_BarrierPos[7].y));
	SphereRect->setAnchorPoint(Vec2(0, 0));
	SphereRect->setScaleX(22.0f);
	SphereRect->setVisible(ColiideRect);
	this->addChild(SphereRect, 2);

	ObjectBarrier* sp1 = new ObjectBarrier;
	sp1->CreateBarrier(m_BarrierPos[0].x, m_BarrierPos[0].y + 80 , BarrierType::Stage1Drop1);
	sp1->SetOption(-320, 2.0f, 0.0f, 0.3f);

	ObjectBarrier* sp2 = new ObjectBarrier;
	sp2->CreateBarrier(m_BarrierPos[1].x, m_BarrierPos[1].y + 80, BarrierType::Stage1Drop1);
	sp2->SetOption(-320, 2.0f, 1.0f, 0.3f);

	ObjectBarrier* sp3 = new ObjectBarrier;
	sp3->CreateBarrier(m_BarrierPos[2].x, m_BarrierPos[2].y + 80, BarrierType::Stage1Drop2);
	sp3->SetOption(-550, 2.0f, 0.5f, 0.5f);

	ObjectBarrier* sp4 = new ObjectBarrier;
	sp4->CreateBarrier(m_BarrierPos[3].x, m_BarrierPos[3].y + 80, BarrierType::Stage1Drop2);
	sp4->SetOption(-550, 2.0f, 0.5f, 0.5f);

	ObjectBarrier* sp5 = new ObjectBarrier;
	sp5->CreateBarrier(m_BarrierPos[4].x, m_BarrierPos[4].y + 80 , BarrierType::Stage1Spine1);

	ObjectBarrier* sp6 = new ObjectBarrier;
	sp6->CreateBarrier(m_BarrierPos[5].x + 40, m_BarrierPos[5].y + 80, BarrierType::Stage1Drop3);
	sp6->SetOption(-380, 2.0f, 0.0f, 0.3f);

	ObjectBarrier* sp7 = new ObjectBarrier;
	sp7->CreateBarrier(m_BarrierPos[6].x + 40, m_BarrierPos[6].y + 80, BarrierType::Stage1Drop3);
	sp7->SetOption(-380, 2.0f, 1.0f, 0.3f);

	ObjectBarrier* sp8 = new ObjectBarrier;
	sp8->CreateBarrier(m_BarrierPos[8].x, m_BarrierPos[8].y + 80, BarrierType::Stage1Drop1);
	sp8->SetOption(-320, 2.0f, 0.0f, 0.3f);

	ObjectBarrier* sp9 = new ObjectBarrier;
	sp9->CreateBarrier(m_BarrierPos[8].x + 640, m_BarrierPos[8].y + 80, BarrierType::Stage1Drop1);
	sp9->SetOption(-320, 2.0f, 0.0f, 0.3f);

	ObjectBarrier* sp10 = new ObjectBarrier;
	sp10->CreateBarrier(m_BarrierPos[8].x + 720, m_BarrierPos[8].y + 80, BarrierType::Stage1Drop1);
	sp10->SetOption(-320, 3.0f, 0.0f, 0.3f);

	/////////////////////////////////////////////////////////
	
	Sprite* Floor1R1 = Function::getInstance()->CreateRedBlock(Vec2(m_BarrierPos[9].x + 15, m_BarrierPos[9].y + 25));
	Floor1R1->runAction(RepeatForever::create(Sequence::create(
			MoveTo::create(1.0f, Vec2(Floor1R1->getPositionX(), Floor1R1->getPositionY() + 400)),
			DelayTime::create(0.5f),
			MoveTo::create(1.0f, Vec2(Floor1R1->getPositionX(), Floor1R1->getPositionY() )),
			NULL)));

	Sprite* Floor1R2 = Function::getInstance()->CreateRedBlock(Vec2(m_BarrierPos[9].x + 95, m_BarrierPos[9].y + 25));

	Floor1R2->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor1R2->getPositionX(), Floor1R2->getPositionY() + 400)),
		DelayTime::create(0.5f),
		MoveTo::create(1.0f, Vec2(Floor1R2->getPositionX(), Floor1R2->getPositionY())),
		NULL)));

	Sprite* Floor1 = Sprite::create("Stage1_2/Floor1.png");
	Floor1->setAnchorPoint(Vec2(0.0f, 0.0f));
	Floor1->setPosition(Vec2(m_BarrierPos[9].x, m_BarrierPos[9].y-80));
	this->addChild(Floor1, 1);

	Floor1->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor1->getPositionX(), Floor1->getPositionY() + 400)),
		DelayTime::create(0.5f),
		MoveTo::create(1.0f, Vec2(Floor1->getPositionX(), Floor1->getPositionY())),
		NULL)));

	//////////////////////////////////////////////////////////////
	Sprite* Floor2 = Sprite::create("Stage1_2/Floor2.png");
	Floor2->setAnchorPoint(Vec2(0.0f, 0.0f));
	Floor2->setPosition(Vec2(m_BarrierPos[9].x + 240, m_BarrierPos[9].y + 400));
	this->addChild(Floor2, 1);

	Floor2->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor2->getPositionX() + 100, Floor2->getPositionY())),
		DelayTime::create(0.1f),
		MoveTo::create(1.0f, Vec2(Floor2->getPositionX(), Floor2->getPositionY())),
		NULL)));

	Sprite* Floor2R1 = Function::getInstance()->CreateRedBlock(Vec2(m_BarrierPos[9].x + 255, m_BarrierPos[9].y + 505));

	Floor2R1->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor2R1->getPositionX()+100, Floor2R1->getPositionY())),
		DelayTime::create(0.1f),
		MoveTo::create(1.0f, Vec2(Floor2R1->getPositionX(), Floor2R1->getPositionY())),
		NULL)));

	//////////////////////////////////////////////////////////////
	Sprite* Floor3R1 = Function::getInstance()->CreateRedBlock(Vec2(m_BarrierPos[10].x + 15, m_BarrierPos[10].y -175));
	Floor3R1->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor3R1->getPositionX(), Floor3R1->getPositionY() + 320)),
		DelayTime::create(0.5f),
		MoveTo::create(1.0f, Vec2(Floor3R1->getPositionX(), Floor3R1->getPositionY())),
		NULL)));


	Sprite* Floor3R2 = Function::getInstance()->CreateRedBlock(Vec2(m_BarrierPos[10].x + 95, m_BarrierPos[10].y - 175));
	Floor3R2->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor3R2->getPositionX(), Floor3R2->getPositionY() + 320)),
		DelayTime::create(0.5f),
		MoveTo::create(1.0f, Vec2(Floor3R2->getPositionX(), Floor3R2->getPositionY())),
		NULL)));

	Sprite* Floor3 = Sprite::create("Stage1_2/Floor2.png");
	Floor3->setAnchorPoint(Vec2(0.0f, 0.0f));
	Floor3->setPosition(Vec2(m_BarrierPos[10].x , m_BarrierPos[10].y - 280));
	this->addChild(Floor3, 1);

	Floor3->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor3->getPositionX(), Floor3->getPositionY() + 320)),
		DelayTime::create(0.5f),
		MoveTo::create(1.0f, Vec2(Floor3->getPositionX(), Floor3->getPositionY())),
		NULL)));

	/////////////////////////////////////////////////////////////////
	Sprite* Floor4 = Sprite::create("Stage1_2/Floor2.png");
	Floor4->setAnchorPoint(Vec2(0.0f, 0.0f));
	Floor4->setPosition(Vec2(m_BarrierPos[10].x + 240, m_BarrierPos[10].y + 200));
	this->addChild(Floor4, 1);

	Floor4->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor4->getPositionX() + 100, Floor4->getPositionY())),
		DelayTime::create(0.1f),
		MoveTo::create(1.0f, Vec2(Floor4->getPositionX(), Floor4->getPositionY())),
		NULL)));

	Sprite* Floor4R1 = Function::getInstance()->CreateRedBlock(Vec2(m_BarrierPos[10].x + 255, m_BarrierPos[10].y + 305));

	Floor4R1->runAction(RepeatForever::create(Sequence::create(
		MoveTo::create(1.0f, Vec2(Floor4R1->getPositionX() + 100, Floor4R1->getPositionY())),
		DelayTime::create(0.1f),
		MoveTo::create(1.0f, Vec2(Floor4R1->getPositionX(), Floor4R1->getPositionY())),
		NULL)));
}

//아이템 생성
void Stage1_2::CreateItem()
{
	// 획득가능 아이템 박스
	extern ItemManager* m_ItemManager;
	m_ItemManager->m_List.clear();
	m_ItemManager->GetLayer(this);

	ObjectItem* Item0 = new ObjectItem;
	Item0->CreateObject(m_ItemPos[0].x, m_ItemPos[0].y - 20, Item::Box1);

	ObjectItem* Item1 = new ObjectItem;
	Item1->CreateObject(m_ItemPos[1].x + 30, m_ItemPos[1].y - 80, Item::Box1);

	ObjectItem* Item2 = new ObjectItem;
	Item2->CreateObject(m_ItemPos[2].x + 30, m_ItemPos[2].y - 15, Item::Box1);

	/*extern BulletManager* m_BulletManager;
	m_BulletManager->m_BulletList.clear();
	m_BulletManager->GetLayer(this);*/
	//BulletManager->AddBullet();

}

//적 생성 
void Stage1_2::CreateEnemy()
{
	extern EnemyManager* m_EnemyManager;
	m_EnemyManager->m_List.clear();
	m_EnemyManager->GetLayer(this);
	m_EnemyManager->GetSource(SourceManager::getInstance());

	//몬스터1
	std::list<ObjectEnemy*> *m_list = &MemoryPool::getInstance()->m_Enemy1Pool;
	std::list<ObjectEnemy*>::iterator iter = m_list->begin();

	for (int i = 0; i < 11; ++i)
	{
		if (m_list->size() != 15)
			return;
		ObjectEnemy* enemy1 = *iter;
		enemy1->SetPosObject(m_EnemyPos[i].x, m_EnemyPos[i].y);
		iter++;
	}

	for (int i = 0; i < 11; ++i)
	{
		m_list->remove(*m_list->begin());
	}

	//몬스터2
	m_list = &MemoryPool::getInstance()->m_Enemy2Pool;
	iter = m_list->begin();
	for (int i = 11; i < 14; ++i)
	{
		ObjectEnemy* enemy1 = *iter;
		enemy1->SetPosObject(m_EnemyPos[i].x, m_EnemyPos[i].y);
		iter++;
	}
	for (int i = 0; i < 3; ++i)
		m_list->remove(*m_list->begin());

	//무당벌레 테스트
	std::list<MiniEnemy*> *m_list2 = &MemoryPool::getInstance()->m_LadyBugPool;
	std::list<MiniEnemy*>::iterator iter2 = m_list2->begin();
	for (int i = 1; i < 8; ++i)
	{
		MiniEnemy* mini1 = *iter2;
		mini1->SetPosObject(m_EnemyPos[i + 13].x, m_EnemyPos[i + 13].y);
		iter2++;
	}
	for (int i = 0; i < 7; ++i)
		m_list2->remove(*m_list2->begin());

	//폭탄벌레 테스트
	std::list<MiniEnemy*> *m_list3 = &MemoryPool::getInstance()->m_BombBugPool;
	std::list<MiniEnemy*>::iterator iter3 = m_list3->begin();
	for (int i = 0; i < 4; ++i)
	{
		MiniEnemy* mini1 = *iter3;
		mini1->SetPosObject(m_EnemyPos[21 + i].x, m_EnemyPos[21 + i].y);
		iter3++;
	}
	for (int i = 0; i < 4; ++i)
		m_list3->remove(*m_list3->begin());

	//박쥐 테스트
	std::list<MiniEnemy*> *m_list4 = &MemoryPool::getInstance()->m_BatPool;
	std::list<MiniEnemy*>::iterator iter4 = m_list4->begin();
	for (int i = 0; i < 4; ++i)
	{
		MiniEnemy* mini1 = *iter4;
		mini1->SetPosObject(m_EnemyPos[21 + i].x + 200, m_EnemyPos[21 + i].y);
		iter4++;
	}
	for (int i = 0; i < 4; ++i)
		m_list4->remove(*m_list4->begin());

	//콜로니 테스트
	std::list<MiniEnemy*> *m_list5 = &MemoryPool::getInstance()->m_Colony;
	std::list<MiniEnemy*>::iterator iter5 = m_list5->begin();
	for (int i = 0; i < 4; ++i)
	{
		MiniEnemy* mini2 = *iter5;
		mini2->SetPosObject(m_EnemyPos[25 + i].x, m_EnemyPos[25 + i].y);
		if (i == 0 || i == 2)
			mini2->SetColony(true, 0);
		iter5++;
	}
	for (int i = 0; i < 4; ++i)
		m_list5->remove(*m_list5->begin());
}

//장애물 업데이트
void Stage1_2::UpdateBarrier()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern BarrierManager* m_BarrierManager;
		m_BarrierManager->BarrierUpdate();
	}
}

// 아이템 업데이트
void Stage1_2::CheckColide()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern ItemManager* m_ItemManager;
		std::vector<ObjectItem*>::iterator iter = m_ItemManager->m_List.begin();

		for (iter; iter != m_ItemManager->m_List.end(); ++iter)
		{
			//// 세이브 박스
			//if ((*iter)->m_SaveObject && (*iter)->m_Spr->getName() == "ItemSave")//세이브 포인트라면
			//{
			//	if ((*iter)->m_Rect->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
			//	{
			//		for (ObjectItem* iter2 : m_ItemManager->m_List)
			//		{
			//			if (iter2->m_SaveObject == false && iter2->m_Spr->getName() == "ItemSave")//기존 비활성화하게한 세이브포인트 다시 활성화
			//				iter2->m_SaveObject = true;
			//		}
			//		(*iter)->AnimationSwitch(ObjectEffect::Saving);
			//		m_SaveNum = (*iter)->m_SaveNum;
			//		UserDefault::getInstance()->setFloatForKey("Clear_Time", m_SaveNum);
			//		return;
			//	}
			//}
			//// 아이템 박스
			if ((*iter)->m_ItemExit)// 상자를 부신상태라면
			{
				if (ObjectHero::getInstance()->m_GetOn)
				{
					if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect((*iter)->m_Item->getBoundingBox()))
					{
						if (ObjectHero::getInstance()->GetItem((*iter)))// 무기, 방어구인 경우
						{
							(*iter)->ItemDelete();
							m_ItemManager->m_List.erase(iter);
							return;
						}
						else// 스킬 스크롤인경우
						{
							(*iter)->ItemDelete();
							m_ItemManager->m_List.erase(iter);
							return;
						}
					}
				}
			}
		}
	}
}

void Stage1_2::UpdateEnemy()
{
	// 이동 / 죽음 / 총알과 충돌체크
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern EnemyManager* m_EnemyManager;
		m_EnemyManager->Update();
	}
}

void Stage1_2::CheckCamEvent()
{
	if (ObjectHero::getInstance()->m_Death)
	{
		for (int i = 0; i < 6; ++i)
			m_Once[i] = false;
		return;
	}
	else
	{
		/*if (Camera::getDefaultCamera() != NULL && m_Once[0] == false)
		{
			m_Once[0] = true;
			Camera::getDefaultCamera()->runAction(Sequence::create(
				DelayTime::create(1.0f),
				EaseOut::create(ScaleTo::create(0.7f, 0.7f, 0.7f), 2.0f), NULL));
		}
		else if (ObjectHero::getInstance()->m_Rect->getPositionX() > 3780 && ObjectHero::getInstance()->m_Rect->getPositionY() < 3245 && m_Once[2] == false)
		{
			m_Once[2] = true;
			CameraAction1();
		}
		else if (ObjectHero::getInstance()->m_Rect->getPositionX() < 3220 && m_Once[2] && m_Once[3] == false)
		{
			m_Once[3] = true;
			CameraAction1();
		}
		else if (ObjectHero::getInstance()->m_Spr->getPositionX() > 2400 && ObjectHero::getInstance()->m_Spr->getPositionY() < 500 && m_Once[3] && m_Once[4] == false)
		{
			m_Once[4] = true;
			CameraAction1();
		}
		else if (ObjectHero::getInstance()->m_Spr->getPositionX() > 4680 && m_Once[4] && m_Once[5] == false)
		{
			m_Once[5] = true;
			CameraAction1();
		}*/
	}
}

void Stage1_2::update(float dt)
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);

	UpdateBack();//배경 업뎃
	Vec2 ex = ObjectHero::getInstance()->m_Spr->getPosition();
	extern Timer2* m_Timer2;
	m_Timer2->SetTime(dt);

	// 카메라 이벤트 체크
	CheckCamEvent();

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

		if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(SphereRect->getBoundingBox()))
		{
			ObjectHero::getInstance()->SetHP(-1000);
		}
		ObjectHero::getInstance()->MoveCharacter(pad->m_dir,dt);
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

	//적 업데이트
	UpdateEnemy();

	// 아이템, 적 충돌체크
	CheckColide();

	// 장애물 업데이트
	UpdateBarrier();

	// 카메라 세팅
	m_CamControl->SettingCamera();

	pad->UISetposition();
}

void Stage1_2::GameOver()
{
	Scene* s = TransitionFade::create(2.0f, Stage1_2::createScene());
	Director::getInstance()->replaceScene(s);
}

void Stage1_2::BackScene()
{
	MemoryArrange();
	Scene* s = Stage1_3Loading::createScene();
	Director::getInstance()->replaceScene(s);
}

void Stage1_2::MemoryArrange()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->MemoryArrange();

	extern EnemyManager* m_EnemyManager;
	std::vector<ObjectEnemy*>::iterator iter = m_EnemyManager->m_List.begin();
	for (int i = 0; m_EnemyManager->m_List.size() != 0; ++i)
	{
		(*iter)->Delete();
		m_EnemyManager->m_List.erase(iter);
		iter = m_EnemyManager->m_List.begin();
	}
	
	std::list<MiniEnemy*>::iterator iter2 = m_EnemyManager->m_MiniList.begin();
	for (int i = 0; m_EnemyManager->m_MiniList.size() != 0; ++i)
	{
		(*iter2)->Delete();
		m_EnemyManager->m_MiniList.erase(iter2);
		iter2 = m_EnemyManager->m_MiniList.begin();
	}

	std::list<MiniEnemy*>::iterator iter3 = m_EnemyManager->m_ColideMini.begin();
	for (int i = 0; m_EnemyManager->m_ColideMini.size() != 0; ++i)
	{
		(*iter3)->Delete();
		m_EnemyManager->m_ColideMini.erase(iter3);
		iter3 = m_EnemyManager->m_ColideMini.begin();
	}

	//extern BulletManager* m_BulletManager;
	//std::list<BulletClass*>::iterator bullet = m_BulletManager->m_BulletList.begin();
	////총알 메모리해제
	//for (int i = 0; m_BulletManager->m_BulletList.size() != 0; ++i)
	//{
	//	(*bullet)->Delete();
	//	m_BulletManager->m_BulletList.erase(bullet);
	//	bullet = m_BulletManager->m_BulletList.begin();
	//}

	//std::list<BulletClass*>::iterator bullet2 = MemoryPool::getInstance()->m_BulletPool.begin();
	//for (int i = 0; MemoryPool::getInstance()->m_BulletPool.size() != 0; ++i)
	//{
	//	(*bullet2)->Delete();
	//	//Me
	//}

	SourceManager::getInstance()->ClearBoxVector();

	// 주인공 메모리해제
	ObjectHero::getInstance()->BulletDelete();

	this->removeChild(m_tmap);
	this->stopAllActions();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}

//배경 그리기
void Stage1_2::CreateBack()
{
	// 기본 베이스
	backbase = Sprite::create("Stage1_2/Basic.png");
	//backbase->setScaleY(1.1f);
	backbase->setAnchorPoint(Vec2(0.0f, 0.0f));
	backbase->setPosition(Vec2(0, 0));
	this->addChild(backbase, -10);

	// 포탈 충돌박스
	potalRect = Sprite::create("Tutorial/Potal.png");
	potalRect->setPosition(Vec2(Portal.x, Portal.y+100));
	potalRect->setScale(0.3f);
	potalRect->setVisible(false);
	this->addChild(potalRect, 9);
}

void Stage1_2::UpdateBack()
{

}
