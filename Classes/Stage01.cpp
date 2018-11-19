#include "Default.h"

Scene* Stage01::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage01::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Stage01::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_Soucre = new SourceManager();
	m_Soucre->LoadingSource(this);

	m_winSize = Director::getInstance()->getWinSize();

	m_Timer = 0;
	m_GameSwitch = false;
	m_UpdateFirst = false;

	CreateBack();
	RoadTileMap();

	this->scheduleUpdate();

	return true;
}

//배경 그리기
void Stage01::CreateBack()
{
	auto back1 = Sprite::create("Tutorial/TutorialBack.png");
	back1->setPosition(Vec2(1600, 1520));
	this->addChild(back1, -2);
}

// 맵로딩
void Stage01::RoadTileMap()
{
	//세이브 여부
	//m_SaveNum = UserDefault::getInstance()->getFloatForKey("Clear_Time", 0.0f);
	m_SaveNum = 0;

	//타일맵 로드
	m_tmap = TMXTiledMap::create("TileMap/Dummy/ProtoStage01.tmx");
	m_background = m_tmap->getLayer("back2");

	m_Ground = m_tmap->getLayer("ColideMeta1");
	m_Ground->setVisible(false);

	m_Jump = m_tmap->getLayer("ColideJumpTile");
	m_Jump->setVisible(false);

	m_MonsterCol = m_tmap->getLayer("MonsterColide");
	m_MonsterCol->setVisible(false);

	m_Ladder = m_tmap->getLayer("Ladder");
	m_Ladder->setVisible(false);
	this->addChild(m_tmap, 1, 11);

	TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("Spawn");
	ValueMap& spawnPoint = Spawn_Pos->getObject("SpawnHero");
	float x = 0;
	float y = 0;

	if (m_SaveNum == 0)
	{
		x = spawnPoint["x"].asFloat();
		y = spawnPoint["y"].asFloat();
	}
	else if (m_SaveNum == 1)
	{
		Spawn_Pos = m_tmap->getObjectGroup("ItemBox1");
		spawnPoint = Spawn_Pos->getObject("SavePoint1");
		x = spawnPoint["x"].asFloat();
		y = spawnPoint["y"].asFloat();
	}
	else if (m_SaveNum == 2)
	{
		Spawn_Pos = m_tmap->getObjectGroup("ItemBox1");
		spawnPoint = Spawn_Pos->getObject("SavePoint2");
		x = spawnPoint["x"].asFloat();
		y = spawnPoint["y"].asFloat();
	}

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
	ObjectHero::getInstance()->GetSoucre(m_Soucre);
	ObjectHero::getInstance()->CreateObject(x, y + 300);
	setViewPointCenter(ObjectHero::getInstance()->m_Rect->getPosition());

	////박스1 생성포인트
	Spawn_Pos = m_tmap->getObjectGroup("ItemBox");
	spawnPoint = Spawn_Pos->getObject("Box3");
	m_ItemPos[0].x = spawnPoint["x"].asFloat();
	m_ItemPos[0].y = spawnPoint["y"].asFloat();

	////박스2 생성포인트
	spawnPoint = Spawn_Pos->getObject("Box4");
	m_ItemPos[1].x = spawnPoint["x"].asFloat();
	m_ItemPos[1].y = spawnPoint["y"].asFloat();

	////박스3 생성포인트
	spawnPoint = Spawn_Pos->getObject("Box5");
	m_ItemPos[2].x = spawnPoint["x"].asFloat();
	m_ItemPos[2].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Box7");
	m_ItemPos[3].x = spawnPoint["x"].asFloat();
	m_ItemPos[3].y = spawnPoint["y"].asFloat();

	////세이브 포인트1
	//spawnPoint = Spawn_Pos->getObject("SavePoint1");
	//m_SavePoint[0].x = spawnPoint["x"].asFloat();
	//m_SavePoint[0].y = spawnPoint["y"].asFloat();

	////세이브 포인트2
	//spawnPoint = Spawn_Pos->getObject("SavePoint2");
	//m_SavePoint[1].x = spawnPoint["x"].asFloat();
	//m_SavePoint[1].y = spawnPoint["y"].asFloat();

	////장애물1 생성포인트
	Spawn_Pos = m_tmap->getObjectGroup("Barrier");
	spawnPoint = Spawn_Pos->getObject("Trap1");
	m_BarrierPos[0].x = spawnPoint["x"].asFloat();
	m_BarrierPos[0].y = spawnPoint["y"].asFloat();

	spawnPoint = Spawn_Pos->getObject("Trap1_1");
	m_BarrierPos[1].x = spawnPoint["x"].asFloat();
	m_BarrierPos[1].y = spawnPoint["y"].asFloat();

	////적생성 포인트1
	Spawn_Pos = m_tmap->getObjectGroup("Spawn");
	spawnPoint = Spawn_Pos->getObject("Enemy3");
	m_EnemyPos[0].x = spawnPoint["x"].asFloat();
	m_EnemyPos[0].y = spawnPoint["y"].asFloat();

	////적생성 포인트2
	//spawnPoint = Spawn_Pos->getObject("Enemy2");
	//m_EnemyPos[0].x = spawnPoint["x"].asFloat();
	//m_EnemyPos[0].y = spawnPoint["y"].asFloat();

	auto meta4 = Sprite::create("TileMap/Dummy/MetaSet4.png");
	auto ladder = Sprite::create("TileMap/Dummy/Ladder1.png");

	Vec2 tileCoord;
	int tileGid;
	//충돌박스 Vector에 삽입
	for (int i = 0; i <= 33; ++i)
	{
		for (int j = 0; j <= 93; ++j)
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
						int x = tileCoord.x * m_tmap->getTileSize().width;
						int y = 2720 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(m_Soucre->metaboxRed->getSpriteFrame());
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y - 20);
						this->addChild(spr, 5);
						m_Soucre->m_metabox.pushBack(spr);
					}
				}
			}
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
						int x = tileCoord.x * m_tmap->getTileSize().width;
						int y = 2720 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(m_Soucre->metaboxBlue->getSpriteFrame());
						spr->setVisible(ColiideRect);
						spr->setTag(MetaNum::MonsterOnly);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y - 20);
						this->addChild(spr, 5);
						m_Soucre->m_metabox.pushBack(spr);
					}
				}
			}
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
						int y = 2720 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(m_Soucre->metaboxBlue->getSpriteFrame());
						spr->setTag(MetaNum::Blue);
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y - 20);
						this->addChild(spr, 5);
						m_Soucre->m_metabox.pushBack(spr);
					}
				}
			}
			//사다리
			tileGid = m_Ladder->getTileGIDAt(tileCoord);
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
						int y = 2720 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(meta4->getSpriteFrame());
						spr->setTag(MetaNum::GreenL);
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.5f, 1.0f));
						spr->setPosition(x + 40, y);
						this->addChild(spr, 5);
						m_Soucre->m_metabox.pushBack(spr);

						auto lad = Sprite::createWithSpriteFrame(ladder->getSpriteFrame());
						lad->setAnchorPoint(Vec2(0.5f, 1.0f));
						lad->setPosition(x + 40, y - 20);
						this->addChild(lad, 6);
					}
				}
			}
		}
	}
	// 이펙트 생성


	// 적생성
	CreateEnemy();

	// 아이템박스 생성
	CreateItem();

	// 장애물 생성
	CreateBarrier();
	return;
}

//장애물 생성
void Stage01::CreateBarrier()
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierManager->m_List.clear();
	m_BarrierManager->GetLayer(this);
	m_BarrierManager->GetSource(m_Soucre);

	ObjectBarrier* spine1 = new ObjectBarrier;
	spine1->CreateBarrier(m_BarrierPos[0].x + 5, m_BarrierPos[0].y - 110, BarrierType::Spine);
	spine1->SetRotation(0, 0.7f);

	ObjectBarrier* spine2 = new ObjectBarrier;
	spine2->CreateBarrier(m_BarrierPos[0].x + 5, m_BarrierPos[0].y - 240, BarrierType::Spine);
	spine2->SetRotation(-90, 0.7f);

	ObjectBarrier* spine3 = new ObjectBarrier;
	spine3->CreateBarrier(m_EnemyPos[0].x - 320, m_EnemyPos[0].y + 660, BarrierType::Spine);
	spine3->SetRotation(90, 0.7f);

	ObjectBarrier* spine4 = new ObjectBarrier;
	spine4->CreateBarrier(m_EnemyPos[0].x - 320, m_EnemyPos[0].y + 960, BarrierType::Spine);
	spine4->SetRotation(90, 0.7f);


	for (int i = 0; i < 6; ++i)
	{
		ObjectBarrier* spine5 = new ObjectBarrier;
		spine5->CreateBarrier(m_BarrierPos[1].x - i * 300, m_BarrierPos[1].y - 110, BarrierType::Spine);
		spine5->SetRotation(0, 0.5f);
	}

	ObjectBarrier* gate1 = new ObjectBarrier;
	gate1->CreateBarrier(m_BarrierPos[1].x + 1320, m_BarrierPos[1].y, BarrierType::Gate);
	gate1->CreateButton(m_BarrierPos[1].x - 1900, m_BarrierPos[1].y - 10);
}

//아이템 생성
void Stage01::CreateItem()
{
	// 획득가능 아이템 박스
	extern ItemManager* m_ItemManager;
	m_ItemManager->m_List.clear();
	m_ItemManager->GetLayer(this);

	ObjectItem* Item0 = new ObjectItem;
	Item0->CreateObject(m_ItemPos[0].x-160, m_ItemPos[0].y, Shield::Head1);

	ObjectItem* Item1 = new ObjectItem;
	Item1->CreateObject(m_ItemPos[0].x, m_ItemPos[0].y, Shield::Head1);

	ObjectItem* Item2 = new ObjectItem;
	Item2->CreateObject(m_ItemPos[1].x, m_ItemPos[1].y, Shield::Top1);

	ObjectItem* Item3 = new ObjectItem;
	Item3->CreateObject(m_ItemPos[2].x, m_ItemPos[2].y, Shield::Bottom1);

	ObjectItem* Item4 = new ObjectItem;
	Item4->CreateObject(m_ItemPos[2].x + 160, m_ItemPos[2].y, Item::Gun);

	ObjectItem* Item5 = new ObjectItem;
	Item5->CreateObject(m_ItemPos[2].x + 320, m_ItemPos[2].y, Item::Gun);

	ObjectItem* Item6 = new ObjectItem;
	Item6->CreateObject(m_ItemPos[3].x + 320, m_ItemPos[3].y, Shield::Top1);

	ObjectItem* Item7 = new ObjectItem;
	Item7->CreateObject(m_ItemPos[2].x + 480, m_ItemPos[2].y, Item::SkillScroll1);

	ObjectItem* Item8 = new ObjectItem;
	Item8->CreateObject(m_ItemPos[2].x + 560, m_ItemPos[2].y, Item::SkillScroll2);

	ObjectItem* Item9 = new ObjectItem;
	Item9->CreateObject(m_ItemPos[2].x + 640, m_ItemPos[2].y, Item::SkillScroll3);

	//// 세이브 포인트1
	//ObjectItem* Save1 = new ObjectItem;
	//Save1->CreateObject(m_SavePoint[0].x, m_SavePoint[0].y, Item::SavePoint);
	//Save1->m_SaveNum = 1;

	//// 세이브 포인트2
	//ObjectItem* Save2 = new ObjectItem;
	//Save2->CreateObject(m_SavePoint[1].x, m_SavePoint[1].y, Item::SavePoint);
	//Save2->m_SaveNum = 2;
}

//적 생성 
void Stage01::CreateEnemy()
{
	extern EnemyManager* m_EnemyManager;
	m_EnemyManager->m_List.clear();
	m_EnemyManager->GetLayer(this);
	m_EnemyManager->GetSource(m_Soucre);

	ObjectEnemy* enemy1 = *MemoryPool::getInstance()->m_Enemy2Pool.begin();
	MemoryPool::getInstance()->m_Enemy2Pool.erase(MemoryPool::getInstance()->m_Enemy2Pool.begin());
	enemy1->SetPosObject(m_BarrierPos[1].x - 400, m_BarrierPos[1].y + 50);

	ObjectEnemy* enemy2 = *MemoryPool::getInstance()->m_Enemy1Pool.begin();
	MemoryPool::getInstance()->m_Enemy1Pool.erase(MemoryPool::getInstance()->m_Enemy1Pool.begin());
	enemy2->SetPosObject(m_BarrierPos[1].x - 400, m_BarrierPos[1].y + 50);

	ObjectEnemy* enemy3 = *MemoryPool::getInstance()->m_Enemy1Pool.begin();
	MemoryPool::getInstance()->m_Enemy1Pool.erase(MemoryPool::getInstance()->m_Enemy1Pool.begin());
	enemy3->SetPosObject(m_BarrierPos[1].x - 400, m_BarrierPos[1].y + 50);

	ObjectEnemy* enemy4 = *MemoryPool::getInstance()->m_Enemy1Pool.begin();
	MemoryPool::getInstance()->m_Enemy1Pool.erase(MemoryPool::getInstance()->m_Enemy1Pool.begin());
	enemy4->SetPosObject(m_BarrierPos[1].x - 400, m_BarrierPos[1].y + 50);
}

//장애물 업데이트
void Stage01::UpdateBarrier()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern BarrierManager* m_BarrierManager;
		m_BarrierManager->BarrierUpdate();
	}
}

// 아이템 업데이트
void Stage01::CheckColide()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern ItemManager* m_ItemManager;
		std::vector<ObjectItem*>::iterator iter = m_ItemManager->m_List.begin();

		for (iter; iter != m_ItemManager->m_List.end(); ++iter)
		{
			//// 세이브 박스
			if ((*iter)->m_SaveObject && (*iter)->m_Spr->getName() == "ItemSave")//세이브 포인트라면
			{
				if ((*iter)->m_Rect->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
				{
					for (ObjectItem* iter2 : m_ItemManager->m_List)
					{
						if (iter2->m_SaveObject == false && iter2->m_Spr->getName() == "ItemSave")//기존 비활성화하게한 세이브포인트 다시 활성화
							iter2->m_SaveObject = true;
					}
					(*iter)->AnimationSwitch(ObjectEffect::Saving);
					m_SaveNum = (*iter)->m_SaveNum;
					UserDefault::getInstance()->setFloatForKey("Clear_Time", m_SaveNum);
					return;
				}
			}
			else if ((*iter)->m_ItemExit)// 상자를 부신상태가 아니라면
			{
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect((*iter)->m_Item->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_GetOn)
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

void Stage01::UpdateEnemy()
{
	// 이동 / 죽음 / 총알과 충돌체크
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern EnemyManager* m_EnemyManager;
		std::vector<ObjectEnemy*>::iterator iter = m_EnemyManager->m_List.begin();
		for (iter; iter != m_EnemyManager->m_List.end(); ++iter)
		{
			if ((*iter)->m_Death)
			{
				(*iter)->AnimationSwitch(EnemyMotion::Die);
				m_EnemyManager->m_List.erase(iter);
				return;
			}
			else
			{
				(*iter)->SetMoveDir();
				(*iter)->MoveCharacter();
				(*iter)->EnemyUpdate();//적 총알 이동
			}
		}
	}
}

void Stage01::update(float dt)
{
	extern Timer2* m_Timer2;
	m_Timer2->SetTime(dt);

	// UI업데이트
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->UIupdate();

	// 주인공 업데이트
	if (ObjectHero::getInstance()->m_Death == false)
	{
		ObjectHero::getInstance()->MoveCharacter(pad->m_dir,dt);
		ObjectHero::getInstance()->HeroUpdate();

		ObjectHero::getInstance()->GetUILayer(pad->GetLayer());
		ObjectHero::getInstance()->InitHP();
		//m_UpdateFirst = true;
		if (m_UpdateFirst == false)
		{
			ObjectHero::getInstance()->SetHP(0);
			m_UpdateFirst = true;
		}
		//RUN_WITH_DELAY(1.0f, CC_CALLBACK_0(Stage01::setViewPointCenter, this));

		setViewPointCenter(ObjectHero::getInstance()->m_SavePos);
	}
	else
	{
		if (m_GameSwitch == false)
		{
			ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDeath);
			RUN_WITH_DELAY(2.5f, CC_CALLBACK_0(Stage01::GameOver, this));
			m_GameSwitch = true;
		}
	}

	m_Timer += dt;
	ObjectHero::getInstance()->GetTime(dt);

	//적 업데이트
	UpdateEnemy();

	// 아이템, 적 충돌체크
	CheckColide();

	// 장애물 업데이트
	UpdateBarrier();
}

void Stage01::GameOver()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	auto label2 = Label::createWithTTF("Game Over", "fonts/arial.ttf", 75.0f, Size(800.0f, 200.0f), TextHAlignment::RIGHT, TextVAlignment::BOTTOM);
	label2->setTextColor(Color4B(255, 0, 0, 255));
	label2->setPosition(440, 500);
	label2->runAction(Sequence::create(
		FadeOut::create(2.5f), CallFunc::create(CC_CALLBACK_0(Stage01::BackScene, this)), NULL));
	pad->GetLayer()->addChild(label2, 10);
}

void Stage01::BackScene()
{
	MemoryArrange();
	Scene* s = TransitionFade::create(2.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(s);
}

void Stage01::MemoryArrange()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->MemoryArrange();

	extern EnemyManager* m_EnemyManager;
	std::vector<ObjectEnemy*>::iterator iter = m_EnemyManager->m_List.begin();
	for (int i = 0; m_EnemyManager->m_List.size() != 0; ++i)
	{
		(*iter)->EnemyDelete();
		m_EnemyManager->m_List.erase(iter);
		iter = m_EnemyManager->m_List.begin();
	}
	this->removeChild(m_tmap);
	m_metabox.clear();
	this->unscheduleUpdate();
	this->stopAllActions();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}

void Stage01::setViewPointCenter(Vec2 pos)
{
	if (pos.x == -500 && pos.y == -500)
		return;
	float x = MAX(pos.x, m_winSize.width * 0.5f);
	float y = MAX(pos.y, m_winSize.height * 0.5f);

	x = MIN(x, (m_tmap->getMapSize().width * m_tmap->getTileSize().width) - m_winSize.width * 0.5f);
	y = MIN(y, (m_tmap->getMapSize().height * m_tmap->getTileSize().height) - m_winSize.height * 0.5f);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(m_winSize.width * 0.5f, m_winSize.height * 0.5f);
	Vec2 viewPoint = centerOfView - actualPosition;
	
	static Vec2 saveViewPos;
	/*if (viewPoint != saveViewPos)
	{
		if (Camera::getDefaultCamera() != NULL)
		{
			Camera::getDefaultCamera()->stopAllActions();
			Camera::getDefaultCamera()->runAction(MoveTo::create(
				0.3f, viewPoint));
		}
		saveViewPos = viewPoint;
	}*/
	
	this->setPosition(viewPoint);
}

void Stage01::setCamera(float dt)
{
	Vec2 mapPos = m_tmap->getMapSize();
}