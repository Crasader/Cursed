#include "Default.h"

bool EliteClear;
bool Boss1Clear;

Scene* Stage1_3::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage1_3::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Stage1_3::init()
{
	if (!Layer::init())
	{
		return false;
	}

	EliteClear = Stage1_3Elite ? true : false;
	Boss1Clear = false;

	CSoundManager::getInstance()->playBgm("Sound/Sound/cavebgm2.mp3", true, true, 1.0f);

	m_Lock = false;
	m_EventOn = true;

	SourceManager::getInstance()->LoadingSource(this);
	Function::getInstance()->GetLayer(this);

	m_winSize = Director::getInstance()->getWinSize();

	m_Timer = 0;
	m_GameSwitch = false;
	m_UpdateFirst = false;
	m_SceneStop = false;
	RoadTileMap();

	this->scheduleUpdate();

	m_CamControl = new CameraControl(m_winSize, Size(18240, 1840), this, ObjectHero::getInstance()->m_Rect->getPosition());
	m_CamControl->m_StageNum = 13;
	m_CamControl->FadeScene(ObjectHero::getInstance()->m_Rect->getPosition());

	CreateBack();

	//auto foract = Sprite::create();
	//foract->runAction(Sequence::create(
	//	CallFunc::create(CC_CALLBACK_0(Stage1_3::CameraAction1, this)),
	//	NULL));
	//this->addChild(foract);

	this->runAction(FadeOut::create(1.0f));

	for (int i = 0; i < 20; i++)
		m_Once[i] = false;

	for (int i = 0; i < 5; ++i)
		m_Event[i] = false;

	Function::getInstance()->MakeHeroPos();

	if (Stage1_3Elite == false)
	{
		m_Elite = new Boss();
		m_Elite->CreateElite(m_SavePoint[3]);
	}

	auto Node1 = Sprite::create("Stage1_3/Node1.png");
	Node1->setPosition(Vec2(3120, 920));
	this->addChild(Node1, 0);

	auto Node2 = Sprite::create("Stage1_3/Node2.png");
	Node2->setPosition(Vec2(9240, 920));
	this->addChild(Node2, 0);

	auto Node3 = Sprite::create("Stage1_3/Node3.png");
	Node3->setPosition(Vec2(15240, 920));
	this->addChild(Node3, 0);

	auto Map1 = Sprite::create("Stage1_3/Map1.png");
	Map1->setPosition(Vec2(3120, 920));
	this->addChild(Map1, 1);

	auto Map2 = Sprite::create("Stage1_3/Map2.png");
	Map2->setPosition(Vec2(9240, 920));
	this->addChild(Map2, 1);

	auto Map3 = Sprite::create("Stage1_3/Map3.png");
	Map3->setPosition(Vec2(15240, 920));
	this->addChild(Map3, 1);

	FatherCreate();

	return true;
}

void Stage1_3::RoadTileMap()
{
	m_SaveNum = 0;

	//타일맵 로드
	m_tmap = TMXTiledMap::create("Stage1_3/Stage1_3.tmx");
	this->addChild(m_tmap, 3, 11);

	m_background1 = m_tmap->getLayer("Left2");
	m_background1->setVisible(false);

	m_background2 = m_tmap->getLayer("Top2");
	m_background2->setVisible(false);

	m_background3 = m_tmap->getLayer("Basic2");
	m_background3->setVisible(false);

	m_background4 = m_tmap->getLayer("Right2");
	m_background4->setVisible(false);

	m_background5 = m_tmap->getLayer("Bottom2");
	m_background5->setVisible(false);

	m_Ground = m_tmap->getLayer("ColideRed");//충돌박스
	m_Ground->setVisible(false);

	m_Ground2 = m_tmap->getLayer("ColideRed2");//충돌박스
	m_Ground2->setVisible(false);

	m_MonsterCol = m_tmap->getLayer("MonsterColide");
	m_MonsterCol->setVisible(false);

	TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("Spawn");

	ValueMap& spawnPoint = Spawn_Pos->getObject(Stage1_3Elite ? "Boss1" : "Hero");

	//ValueMap& spawnPoint = Spawn_Pos->getObject("FatherEvent2");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	char str[100] = {};
	for (int i = 1; i <= 6; ++i)
	{
		sprintf(str, "LadyBug%d", i);
		spawnPoint = Spawn_Pos->getObject(str);
		m_EnemyPos[i].x = spawnPoint["x"].asFloat();
		m_EnemyPos[i].x = m_EnemyPos[i].x - ((int)m_EnemyPos[i].x % 80);
		m_EnemyPos[i].y = spawnPoint["y"].asFloat();
		m_EnemyPos[i].y = m_EnemyPos[i].y - ((int)m_EnemyPos[i].y % 80);
	}
	for (int i = 10; i < 15; ++i)// 7~11 보스가 소환하는 벌레
	{
		sprintf(str, "LadyBug%d", i - 3);
		spawnPoint = Spawn_Pos->getObject(str);
		m_EnemyPos[i].x = spawnPoint["x"].asFloat();
		m_EnemyPos[i].x = m_EnemyPos[i].x - ((int)m_EnemyPos[i].x % 80);
		m_EnemyPos[i].y = spawnPoint["y"].asFloat();
		m_EnemyPos[i].y = m_EnemyPos[i].y - ((int)m_EnemyPos[i].y % 80);
	}

	for (int i = 7; i <= 9; ++i)
	{
		sprintf(str, "BombBug%d", i - 6);
		spawnPoint = Spawn_Pos->getObject(str);
		m_EnemyPos[i].x = spawnPoint["x"].asFloat();
		m_EnemyPos[i].x = m_EnemyPos[i].x - ((int)m_EnemyPos[i].x % 80);
		m_EnemyPos[i].y = spawnPoint["y"].asFloat();
		m_EnemyPos[i].y = m_EnemyPos[i].y - ((int)m_EnemyPos[i].y % 80);
	}

	for (int i = 1; i <= 2; ++i)
	{
		sprintf(str, "Interact%d", i);
		spawnPoint = Spawn_Pos->getObject(str);
		m_SavePoint[i - 1].x = spawnPoint["x"].asFloat();
		m_SavePoint[i - 1].x = m_SavePoint[i - 1].x - ((int)m_SavePoint[i - 1].x % 80);
		m_SavePoint[i - 1].y = spawnPoint["y"].asFloat();
		m_SavePoint[i - 1].y = m_SavePoint[i - 1].y - ((int)m_SavePoint[i - 1].y % 80);
	}

	spawnPoint = Spawn_Pos->getObject("Door1");
	m_SavePoint[2].x = spawnPoint["x"].asFloat();
	m_SavePoint[2].x = m_SavePoint[2].x - ((int)m_SavePoint[2].x % 80);
	m_SavePoint[2].y = spawnPoint["y"].asFloat();
	m_SavePoint[2].y = m_SavePoint[2].y - ((int)m_SavePoint[2].y % 80);

	spawnPoint = Spawn_Pos->getObject("Boss1");
	m_SavePoint[3].x = spawnPoint["x"].asFloat();
	m_SavePoint[3].x = m_SavePoint[3].x - ((int)m_SavePoint[3].x % 80);
	m_SavePoint[3].y = spawnPoint["y"].asFloat();
	m_SavePoint[3].y = m_SavePoint[3].y - ((int)m_SavePoint[3].y % 80);

	spawnPoint = Spawn_Pos->getObject("Sphere1");
	m_SavePoint[4].x = spawnPoint["x"].asFloat();
	m_SavePoint[4].x = m_SavePoint[4].x - ((int)m_SavePoint[4].x % 80);
	m_SavePoint[4].y = spawnPoint["y"].asFloat();
	m_SavePoint[4].y = m_SavePoint[4].y - ((int)m_SavePoint[4].y % 80);

	spawnPoint = Spawn_Pos->getObject("Door2");
	m_SavePoint[5].x = spawnPoint["x"].asFloat();
	m_SavePoint[5].x = m_SavePoint[5].x - ((int)m_SavePoint[5].x % 80);
	m_SavePoint[5].y = spawnPoint["y"].asFloat();
	m_SavePoint[5].y = m_SavePoint[5].y - ((int)m_SavePoint[5].y % 80);

	spawnPoint = Spawn_Pos->getObject("Boss2");
	m_SavePoint[6].x = spawnPoint["x"].asFloat();
	m_SavePoint[6].x = m_SavePoint[6].x - ((int)m_SavePoint[5].x % 80);
	m_SavePoint[6].y = spawnPoint["y"].asFloat();
	m_SavePoint[6].y = m_SavePoint[6].y - ((int)m_SavePoint[5].y % 80);

	spawnPoint = Spawn_Pos->getObject("Father");
	m_SavePoint[7].x = spawnPoint["x"].asFloat();
	m_SavePoint[7].x = m_SavePoint[7].x - ((int)m_SavePoint[7].x % 80);
	m_SavePoint[7].y = spawnPoint["y"].asFloat();
	m_SavePoint[7].y = m_SavePoint[7].y - ((int)m_SavePoint[7].y % 80);

	spawnPoint = Spawn_Pos->getObject("Boss2Pos");
	m_SavePoint[8].x = spawnPoint["x"].asFloat();
	m_SavePoint[8].x = m_SavePoint[8].x - ((int)m_SavePoint[8].x % 80);
	m_SavePoint[8].y = spawnPoint["y"].asFloat();
	m_SavePoint[8].y = m_SavePoint[8].y - ((int)m_SavePoint[8].y % 80);

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
	ObjectHero::getInstance()->CreateObject(x + (Stage1_3Elite ? -900 : 0), y);
	ObjectHero::getInstance()->m_RebornPos = Vec2(x + (Stage1_3Elite ? 9600 : 0), y);

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
		}
	}

	Function::getInstance()->MakeColideWidth(MapRedXY, size, MetaNum::Red);
	Function::getInstance()->MakeColideHeight(MapRed2XY, size, MetaNum::Red);
	Function::getInstance()->MakeColideWidth(MapMonXY, size, MetaNum::MonsterOnly);

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

//적 생성 
void Stage1_3::CreateEnemy()
{
	extern EnemyManager* m_EnemyManager;
	m_EnemyManager->m_List.clear();
	m_EnemyManager->GetLayer(this);
	m_EnemyManager->GetSource(SourceManager::getInstance());

	//무당벌레 테스트
	std::list<MiniEnemy*> *m_list2 = &MemoryPool::getInstance()->m_LadyBugPool;
	std::list<MiniEnemy*>::iterator iter2 = m_list2->begin();
	for (int i = 1; i <= 6; ++i)
	{
		MiniEnemy* mini1 = *iter2;
		mini1->SetPosObject(m_EnemyPos[i].x, m_EnemyPos[i].y);
		iter2++;
	}
	for (int i = 0; i < 6; ++i)
		m_list2->remove(*m_list2->begin());

	//폭탄벌레 테스트
	std::list<MiniEnemy*> *m_list3 = &MemoryPool::getInstance()->m_BombBugPool;
	std::list<MiniEnemy*>::iterator iter3 = m_list3->begin();
	for (int i = 1; i < 3; ++i)
	{
		MiniEnemy* mini1 = *iter3;
		mini1->SetPosObject(m_EnemyPos[i + 7].x, m_EnemyPos[i + 7].y);
		iter3++;
	}
	for (int i = 0; i < 2; ++i)
		m_list3->remove(*m_list3->begin());

	//악령 테스트
	std::list<ObjectEnemy*> *m_list4 = &MemoryPool::getInstance()->m_Demon2Pool;
	std::list<ObjectEnemy*>::iterator iter4 = m_list4->begin();
	for (int i = 0; i < 1; ++i)
	{
		m_Demon = *iter4;
		m_Demon->SetPosObject(-1100, 800);
		m_Demon->AnimationSwitch(EnemyMotion::RightWalk);

		//치트 나중에 지워야함 ★
		m_Demon->m_Death = Stage1_3Elite;
		iter4++;
	}
	for (int i = 0; i < 1; ++i)
		m_list4->remove(*m_list4->begin());

	m_Enemy1 = new ObjectEnemy();
	m_Enemy1->CreateObject();
	m_Enemy1->m_Death = true;
}

//장애물 생성
void Stage1_3::CreateBarrier()
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierManager->m_List.clear();
	m_BarrierManager->GetLayer(this);
	m_BarrierManager->GetSource(SourceManager::getInstance());

	m_Interact[0] = Sprite::create("Object/InteractStone.png");
	m_Interact[0]->setPosition(Vec2(m_SavePoint[0].x, m_SavePoint[0].y + 160));
	this->addChild(m_Interact[0], 3);

	m_Guide[0] = Sprite::create("UI/Guide_X.png");
	m_Guide[0]->setPosition(Vec2(m_Interact[0]->getPositionX(), m_Interact[0]->getPositionY() + 200));
	m_Guide[0]->setVisible(false);
	m_Guide[0]->setScale(0.6f);
	this->addChild(m_Guide[0], 4);

	m_Interact[1] = Sprite::createWithSpriteFrame(m_Interact[0]->getSpriteFrame());
	m_Interact[1]->setPosition(Vec2(m_SavePoint[1].x, m_SavePoint[1].y + 160));
	this->addChild(m_Interact[1], 3);

	m_Guide[1] = Sprite::createWithSpriteFrame(m_Guide[0]->getSpriteFrame());
	m_Guide[1]->setPosition(Vec2(m_Interact[1]->getPositionX(), m_Interact[1]->getPositionY() + 200));
	m_Guide[1]->setVisible(false);
	m_Guide[1]->setScale(0.6f);
	this->addChild(m_Guide[1], 4);

	//엘리트보스 정문
	m_Interact[2] = Sprite::create("Barrier/Door/Door1.png");
	m_Interact[2]->setPosition(Vec2(m_SavePoint[2].x, m_SavePoint[2].y + 120));
	this->addChild(m_Interact[2], 2);

	m_Interact[3] = Sprite::create("Barrier/Door/Door2.png");
	m_Interact[3]->setPosition(Vec2(m_SavePoint[2].x, m_SavePoint[2].y - 120));
	this->addChild(m_Interact[3], 1);

	//엘리트보스 후문
	m_Interact[14] = Sprite::createWithSpriteFrame(m_Interact[2]->getSpriteFrame());
	m_Interact[14]->setScaleY(1.2f);
	m_Interact[14]->setPosition(Vec2(m_SavePoint[2].x + 2720, m_SavePoint[2].y + 150));
	this->addChild(m_Interact[14], 2);

	m_Interact[15] = Sprite::createWithSpriteFrame(m_Interact[3]->getSpriteFrame());
	m_Interact[15]->setScaleY(1.2f);
	m_Interact[15]->setPosition(Vec2(m_SavePoint[2].x + 2720, m_SavePoint[2].y + 150));
	m_Interact[15]->setTag(MetaNum::Red);
	SourceManager::getInstance()->m_metabox.pushBack(m_Interact[15]);
	this->addChild(m_Interact[15], 1);

	//보스몹 정문
	m_Interact[16] = Sprite::create("Stage1_3/Wall2.png");
	m_Interact[16]->setPosition(Vec2(m_SavePoint[5].x + 120, m_SavePoint[5].y - 120));
	m_Interact[16]->setVisible(ColiideRect);
	this->addChild(m_Interact[16], 2);

	m_Interact[17] = Sprite::create("Stage1_3/Wall1.png");
	m_Interact[17]->setPosition(Vec2(m_SavePoint[5].x + 120, m_SavePoint[5].y - 120));
	this->addChild(m_Interact[17], 1);

	//보스몹 후문
	m_Interact[18] = Sprite::createWithSpriteFrame(m_Interact[16]->getSpriteFrame());
	m_Interact[18]->setPosition(Vec2(m_SavePoint[5].x + 2040, m_SavePoint[5].y - 120));
	m_Interact[18]->setVisible(ColiideRect);
	this->addChild(m_Interact[18], 2);

	m_Interact[19] = Sprite::createWithSpriteFrame(m_Interact[17]->getSpriteFrame());
	m_Interact[19]->setPosition(Vec2(m_SavePoint[5].x + 2040, m_SavePoint[5].y - 120));
	this->addChild(m_Interact[19], 1);

	//창 장애물
	m_Interact[4] = Sprite::create("Barrier/FixSphere.png");
	m_Interact[4]->setPosition(Vec2(m_SavePoint[4].x + 130, m_SavePoint[4].y + 150));
	this->addChild(m_Interact[4], 1);

	m_Interact[5] = Sprite::create("Barrier/FixSphere2.png");
	m_Interact[5]->setPosition(Vec2(m_SavePoint[4].x + 350, m_SavePoint[4].y + 140));
	this->addChild(m_Interact[5], 1);

	m_Interact[6] = Sprite::create("Barrier/FixSphere.png");
	m_Interact[6]->setPosition(Vec2(m_SavePoint[4].x + 630, m_SavePoint[4].y + 150));
	this->addChild(m_Interact[6], 1);

	m_Interact[7] = Sprite::create("Barrier/FixSphere2.png");
	m_Interact[7]->setPosition(Vec2(m_SavePoint[4].x + 850, m_SavePoint[4].y + 140));
	this->addChild(m_Interact[7], 1);

	m_Interact[8] = Sprite::create("Barrier/FixSphere.png");
	m_Interact[8]->setPosition(Vec2(m_SavePoint[4].x + 1130, m_SavePoint[4].y + 150));
	this->addChild(m_Interact[8], 1);

	m_Interact[9] = Sprite::create("Barrier/FixSphere2.png");
	m_Interact[9]->setPosition(Vec2(m_SavePoint[4].x + 1350, m_SavePoint[4].y + 140));
	this->addChild(m_Interact[9], 1);

	m_Interact[10] = Sprite::create("Barrier/FixSphere.png");
	m_Interact[10]->setPosition(Vec2(m_SavePoint[4].x + 1630, m_SavePoint[4].y + 150));
	this->addChild(m_Interact[10], 1);

	m_Interact[11] = Sprite::create("Barrier/FixSphere2.png");
	m_Interact[11]->setPosition(Vec2(m_SavePoint[4].x + 1850, m_SavePoint[4].y + 140));
	this->addChild(m_Interact[11], 1);

	m_Interact[12] = Sprite::create("Barrier/FixSphere.png");
	m_Interact[12]->setPosition(Vec2(m_SavePoint[4].x + 2130, m_SavePoint[4].y + 150));
	this->addChild(m_Interact[12], 1);

	m_Interact[13] = Sprite::create("Barrier/FixSphere2.png");
	m_Interact[13]->setPosition(Vec2(m_SavePoint[4].x + 2350, m_SavePoint[4].y + 140));
	this->addChild(m_Interact[13], 1);
}

//아이템 생성
void Stage1_3::CreateItem()
{
	// 획득가능 아이템 박스
	extern ItemManager* m_ItemManager;
	m_ItemManager->m_List.clear();
	m_ItemManager->GetLayer(this);

}

//장애물 업데이트
void Stage1_3::UpdateBarrier()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern BarrierManager* m_BarrierManager;
		m_BarrierManager->BarrierUpdate();
	}
}

// 아이템 업데이트
void Stage1_3::CheckColide()
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
			//// 아이템 박스
			else if ((*iter)->m_ItemExit)// 상자를 부신상태라면
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

void Stage1_3::UpdateEnemy()
{
	// 이동 / 죽음 / 총알과 충돌체크
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern EnemyManager* m_EnemyManager;
		m_EnemyManager->Update();
	}

	if (EliteClear && m_Once[11] == false)
	{
		m_Once[11] = true;
		CSoundManager::getInstance()->playBgm("Sound/Sound/cavebgm2.mp3", true, true, 1.0f);
	}
	if (ObjectHero::getInstance()->m_Death == false && ObjectHero::getInstance()->m_Rect->getPositionX() > m_Interact[17]->getPositionX() + 100 && m_Once[13] == false)
	{
		CSoundManager::getInstance()->playEffect("Sound/MySound/Door_MysticalOpen3.mp3", false, 1.0f);
		m_Interact[17]->runAction(MoveTo::create(1.0f, Vec2(m_Interact[17]->getPositionX(), m_Interact[17]->getPositionY() + 250)));
		m_Interact[16]->runAction(MoveTo::create(1.0f, Vec2(m_Interact[16]->getPositionX(), m_Interact[16]->getPositionY() + 250)));
		m_Interact[16]->setTag(MetaNum::Red);
		SourceManager::getInstance()->m_metabox.pushBack(m_Interact[16]);

		m_Interact[19]->runAction(MoveTo::create(1.0f, Vec2(m_Interact[19]->getPositionX(), m_Interact[19]->getPositionY() + 250)));
		m_Interact[18]->runAction(MoveTo::create(1.0f, Vec2(m_Interact[18]->getPositionX(), m_Interact[18]->getPositionY() + 250)));
		m_Interact[18]->setTag(MetaNum::Red);
		SourceManager::getInstance()->m_metabox.pushBack(m_Interact[19]);

		m_Once[13] = true;
		m_CamControl->m_Event[1] = true;
	}

	//치트 나중에 지워야함★
	if (Stage1_3Elite)
		return;

	if (m_Demon->m_Death == false && ObjectHero::getInstance()->m_Death == false)
	{
		m_Demon->EnemyUpdate();
		if (m_Once[9])
		{
			if (m_Demon->m_Spr->getPositionX() < -30)
			{
				m_Demon->m_Spr->setPositionX(m_Demon->m_Spr->getPositionX() + 4);
				m_Demon->m_Spr->setPositionY(m_Demon->m_Spr->getPositionY() + 0.2f);
			}
			else
			{
				m_Once[1] = true;
			}
			if (m_Demon->m_Spr->getPositionX() > 200)
			{
				m_CamControl->m_Camera->setPosition(Vec2(m_Demon->m_Spr->getPositionX() + 800, m_CamControl->m_Camera->getPositionY()));
			}
			//악령소멸
			if (m_Demon->m_Weapon->getBoundingBox().intersectsRect(m_Interact[2]->getBoundingBox()) && m_Once[8] == false)
			{
				CSoundManager::getInstance()->playEffect("Sound/MySound/Ghost_walk2.mp3", false, 1.0f);
				m_Demon->m_Death = true;
				m_Demon->m_Spr->runAction(FadeOut::create(1.0f));
				m_Once[9] = false;
				m_Once[8] = true;
				m_Once[5] = false;
				m_EventOn = true;
			}
		}

		if (m_Demon->m_Spr->getPositionX() > 200 && m_Once[7] == false)
		{
			m_Once[7] = true;
			CSoundManager::getInstance()->playEffect("Sound/MySound/dragon_appear3.mp3", false, 1.0f);
		}
		if (ObjectHero::getInstance()->m_Rect->getPositionX() > m_Interact[2]->getPositionX() + 100 && m_Once[6] == false)
		{
			static bool once;
			if (once == false)
			{
				once = true;
				m_Interact[3]->setTag(MetaNum::Red);
				SourceManager::getInstance()->m_metabox.pushBack(m_Interact[3]);
			}
			CSoundManager::getInstance()->playEffect("Sound/MySound/Door_MysticalOpen3.mp3", false, 1.0f);
			m_Interact[3]->runAction(MoveTo::create(1.0f, Vec2(m_Interact[2]->getPositionX(), m_Interact[2]->getPositionY() + 10)));

			m_Once[6] = true;
		}
	}
	// 엘리트 관련체크
	else if (ObjectHero::getInstance()->m_Death == false && ObjectHero::getInstance()->m_Rect->getPositionX() > 10200 && m_Once[10] == false && Stage1_3Elite == false)
	{
		m_Once[10] = true;
		m_EventOn = false;
		CSoundManager::getInstance()->playBgm("Monster/Elite/bgm.mp3", true, true, 0.4f);

		m_Elite->AnimationSwitch(BossMotion::BossHowling);

		m_CamControl->m_Camera->runAction(Sequence::create(
			MoveTo::create(0.8f, Vec2(m_CamControl->m_Camera->getPositionX() + 600, m_CamControl->m_Camera->getPositionY())),
			DelayTime::create(2.7f),
			CallFunc::create(CC_CALLBACK_0(Stage1_3::Stg1_3Event2, this)),
			NULL));

		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->KeyClear();
		pad->m_KeyLock = true;
		pad->SetLetter();
		//pad->m_dir.push_back(PadDir::RightMove);
		pad->DirClear();

		RUN_WITH_DELAY(3.5f, CC_CALLBACK_0(Stage1_3::SetLetter2, this));
	}
}


void Stage1_3::Stage1_3EventCheck()
{
	if (Boss1Clear)
	{
		m_EventOn = true;
		if (m_Once[17] == false)
		{
			BossChat6();
			m_Once[17] = true;
			m_Interact[19]->runAction(MoveTo::create(1.0f, Vec2(m_Interact[19]->getPositionX(), m_Interact[19]->getPositionY() - 250)));
		}
		if (ObjectHero::getInstance()->m_Rect->getPositionX() > 18060)
		{
			this->unscheduleUpdate();
			BackScene();
			m_SceneStop = true;
			return;
			//스테이지 전환
		}
		return;
	}
	//보스가 생성된 상태이면
	if (m_Once[15] && m_Boss1->m_Death == false)
	{
		if (m_Boss1->m_Skill5On)
		{
			m_Boss1->m_Skill5On = false;
			extern EnemyManager* m_EnemyManager;
			std::list<MiniEnemy*>::iterator iter3 = m_EnemyManager->m_MiniList.begin();
			for (int i = 0; i < 5; ++i)
			{
				(*iter3)->m_SavePos.x = m_EnemyPos[10 + i].x;
				(*iter3)->m_SavePos.y = m_EnemyPos[10 + i].y + 80;
				(*iter3)->m_Death = true;
				(*iter3)->Recreate();
				iter3++;
			}
		}
		if (m_Spine->isVisible() && m_Spine->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
		{
			if (ObjectHero::getInstance()->m_HeroHit == false)
			{
				if (ObjectHero::getInstance()->m_Spr->getPositionX() > m_Spine->getPositionX())
					ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageRight);
				else
					ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDamageLeft);
				ObjectHero::getInstance()->SetHP(-10);
			}
		}
	}

	static bool once;
	if (ObjectHero::getInstance()->m_Rect->getPositionX() > 13500 && m_Once[16] == false && once == false)
	{
		ObjectHero::getInstance()->m_RebornPos = ObjectHero::getInstance()->m_Rect->getPosition();

		once = true;
		m_Once[16] = true;
		Boss2Idle(m_SavePoint[8]);
		m_Boss1 = new Boss();
		m_Boss1->CreateStage1Boss(Vec2(m_SavePoint[6].x - 100, m_SavePoint[6].y - 100), this);
		m_Boss1->m_Lock = true;
	}
	else if (once && ObjectHero::getInstance()->m_Rect->getPositionX() < 14500)
	{
		//16171819
		m_Interact[16]->setPosition(Vec2(m_SavePoint[5].x + 120, m_SavePoint[5].y - 120));
		m_Interact[17]->setPosition(Vec2(m_SavePoint[5].x + 120, m_SavePoint[5].y - 120));
	}
	else if (ObjectHero::getInstance()->m_Rect->getPositionX() > 15900 && ObjectHero::getInstance()->m_Death == false)
	{
		if (m_Once[15] == false)
		{
			m_Once[15] = true;
			m_Boss1->AnimationSwitch(0);
			m_EventOn = false;
			m_CamControl->m_Camera->setPosition(Vec2(16400, 1100));
			m_CamControl->m_Camera->stopAllActions();
			m_CamControl->m_Camera->runAction(Sequence::create(
				DelayTime::create(3.5f),
				CallFunc::create(CC_CALLBACK_0(Stage1_3::BossEvent1, this)), NULL));

			m_Spine = Sprite::create("Stage1_3/Spine.png");
			m_Spine->setAnchorPoint(Vec2(0.0f, 0.0f));
			m_Spine->setPosition(Vec2(m_SavePoint[5].x + 160 - 176, m_SavePoint[5].y));
			m_Spine->setVisible(false);
			m_Spine->runAction(Sequence::create(
				DelayTime::create(0.8f), Show::create(),
				MoveTo::create(0.5f, Vec2(m_Spine->getPositionX() + 176, m_Spine->getPositionY())),
				NULL));
			this->addChild(m_Spine, 2);

			GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
			pad->KeyClear();
			pad->m_KeyLock = true;
			pad->DirClear();
		}
	}

	//엘리트까지 업데이트 이벤트
	else if (ObjectHero::getInstance()->m_Rect->getPositionX() < 14500)
	{
		if (m_Once[11] && m_Once[12] == false)
		{
			CSoundManager::getInstance()->playEffect("Sound/MySound/Door_MysticalOpen3.mp3", false, 1.0f);
			m_Once[12] = true;
			m_Interact[15]->runAction(MoveTo::create(1.0f, Vec2(m_Interact[15]->getPositionX(), m_Interact[15]->getPositionY() - 340)));
		}
		//치트 나중에 지워야함★
		if (Stage1_3Elite)
			return;

		if (m_Once[5])
		{
			m_Demon->m_Spr->setPosition(Vec2(m_Demon->m_Spr->getPositionX() + 7, m_Demon->m_Spr->getPositionY() + 0.1f));
		}
		if (ObjectHero::getInstance()->m_Rect->getPositionX() > 1400 && m_Once[0] == false &&
			ObjectHero::getInstance()->m_Death == false)
		{
			GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
			pad->SetLetter();
			pad->m_KeyLock = true;
			pad->m_dir.push_back(PadDir::LeftMove);
			pad->DirClear();

			m_Once[0] = true;
			m_Once[9] = true;
			// 카메라기능 정지
			m_EventOn = false;
			this->runAction(ActionShake::create(4.0f, 50.0f, 50.0f));
			m_CamControl->m_Camera->runAction(Sequence::create(
				DelayTime::create(1.0f),
				EaseOut::create(MoveTo::create(1.0f, Vec2(960, m_CamControl->m_Camera->getPositionY())), 2.0f),
				NULL));
			CSoundManager::getInstance()->playEffect("Sound/MySound/Quake_Tunnel_Loop2.mp3", false, 0.7f);

			EmotionLabel = Label::createWithTTF("!", "fonts/210 아몬드R.ttf", 45);
			EmotionLabel->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 710));
			EmotionLabel->setVisible(false);
			this->addChild(EmotionLabel, 10);
			EmotionLabel->runAction(Sequence::create(DelayTime::create(0.5f), Show::create(),
				DelayTime::create(4.0f), Hide::create(), NULL));
		}
		else if (m_Once[0] && m_Once[1] == false)
		{
			//m_Once[1] = true;
		}
		else if (m_Once[1] && m_Once[2] == false)
		{
			m_Once[2] = true;
		}
		else if (m_Once[2] && m_Once[3] == false)
		{
			m_Once[3] = true;
			m_Demon->AnimationSwitch(EnemyMotion::Howling);
			RUN_WITH_DELAY(2.5f, CC_CALLBACK_0(Stage1_3::CheckCamEvent, this));
		}
		else if (m_Once[3] && m_Once[4] == false)
		{
			m_Once[4] = true;
			RUN_WITH_DELAY(4.0f, CC_CALLBACK_0(Stage1_3::SetLetter, this));
		}
		else if (m_Once[4] && m_Once[5] == false)
		{
			//m_Once[5] = true;
		}
	}
}

void Stage1_3::SetLetter()
{
	m_Once[5] = true;
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->SetLetter();
	pad->m_KeyLock = false;
}

void Stage1_3::SetLetter2()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->SetLetter();
	pad->m_KeyLock = false;
}

void Stage1_3::CheckCamEvent()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	if (ObjectHero::getInstance()->m_AniNum == 0)
	{
		pad->m_KeyClean = true;
		pad->m_KeySave = PadDir::Skill1;
		extern WeaponManager* m_WeaponManager;
		extern ShieldManager* m_ShieldManager;
		if (ObjectHero::getInstance()->m_AniNum == 0 && ObjectHero::getInstance()->m_CurMotionNum == MotionNum::Stand)
		{
			ObjectHero::getInstance()->m_AniNum = 8;
			ObjectHero::getInstance()->SettingItem(Item::Gun);
			m_WeaponManager->CloseWeapon->setVisible(false);
			pad->ChangeWeapon();
		}
	}
	pad->m_dir.push_back(PadDir::Att);
	pad->DirClear();

}

void Stage1_3::update(float dt)
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);

	Stage1_3EventCheck();


	if (m_SceneStop)
		return;

	//Vec2 ex = ObjectHero::getInstance()->m_Spr->getPosition();
	extern Timer2* m_Timer2;
	m_Timer2->SetTime(dt);

	// UI업데이트
	pad->UIupdate();

	if (pad->m_Boss1HP_On)
		pad->Boss1HPUpdate(m_Boss1->m_HP);
	else if (pad->m_EliteHP_On)
		pad->EliteHPUpdate(m_Elite->m_HP);

	if (pad->m_KeyUp)
	{
		if (ObjectHero::getInstance()->m_Spr->getBoundingBox().intersectsRect(potalRect->getBoundingBox()))
		{
			BackScene();
			this->unscheduleUpdate();
			return;
		}
	}

	/*if (m_Lock)
		pad->m_KeyLock = true;
	else if (m_Lock == false)
		pad->m_KeyLock = false;*/

		// 주인공 업데이트
	if (ObjectHero::getInstance()->m_Death == false)
	{
		m_Once[14] = false;

		if (EliteClear == false && ObjectHero::getInstance()->m_Rect->getPositionY() < 400)
			ObjectHero::getInstance()->SetHP(-1000);
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
	else if (m_Once[14] == false)
	{
		m_Once[5] = false;
		m_Once[14] = true;
		RUN_WITH_DELAY(6.4f, CC_CALLBACK_0(Stage1_3::GameOver, this));
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
	if (m_EventOn)
		m_CamControl->SettingCamera();

	// 1_3이벤트
	GuideCheck();
	if (Stage1_3Elite == false && m_Demon->m_Death == false)
	{
		if (m_Demon->m_Spr->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
		{
			m_Demon->AnimationSwitch(EnemyMotion::CloseAtk);
			if (ObjectHero::getInstance()->m_HP > 0)
				ObjectHero::getInstance()->SetHP(-10000);
		}
		if (m_Interact[0]->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()) &&
			ObjectHero::getInstance()->m_Interact && m_Event[0] == false)
		{
			m_Demon->AnimationSwitch(EnemyMotion::Hit);

			m_Event[0] = true;
			EffectManager::getInstance()->EffectSwitch(EffectName::Protect, m_Interact[0]->getPositionX(), m_Interact[0]->getPositionY(), false);
			CSoundManager::getInstance()->playEffect("Sound/MySound/Magic_Spell_Shield6.mp3", false, 1.0f);

			m_Once[5] = false;
			EffectManager::getInstance()->EffectSwitch(EffectName::Protect, m_Demon->m_Spr->getPositionX() + 200, m_Demon->m_Spr->getPositionY(), false);
			CSoundManager::getInstance()->playEffect("Sound/MySound/Ghost_attack.mp3", false, 1.0f);
			Sprite* foraction = Sprite::create();
			this->addChild(foraction);
			foraction->runAction(Sequence::create(
				DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(Stage1_3::Stg1_3Event, this)),
				NULL));
		}
		else if (m_Interact[1]->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()) &&
			ObjectHero::getInstance()->m_Interact && m_Event[1] == false)
		{
			m_Demon->AnimationSwitch(EnemyMotion::Hit);

			m_Event[1] = true;
			EffectManager::getInstance()->EffectSwitch(EffectName::Protect, m_Interact[1]->getPositionX(), m_Interact[1]->getPositionY(), false);
			CSoundManager::getInstance()->playEffect("Sound/MySound/Magic_Spell_Shield6.mp3", false, 1.0f);
			m_Once[5] = false;
			EffectManager::getInstance()->EffectSwitch(EffectName::Protect, m_Demon->m_Spr->getPositionX() + 200, m_Demon->m_Spr->getPositionY(), false);
			CSoundManager::getInstance()->playEffect("Sound/MySound/Ghost_attack.mp3", false, 1.0f);
			Sprite* foraction = Sprite::create();
			this->addChild(foraction);
			foraction->runAction(Sequence::create(
				DelayTime::create(2.0f), CallFunc::create(CC_CALLBACK_0(Stage1_3::Stg1_3Event, this)),
				NULL));
		}
	}
	pad->UISetposition();

	FatherEvent();

	//Function::getInstance()->LookHeroPos();
}

void Stage1_3::GameOver()
{
	if (ObjectHero::getInstance()->m_Death == false)
		return;
	for (int i = 0; i < 20; ++i)
	{
		m_Once[i] = false;
	}

	for (int i = 0; i < 5; ++i)
		m_Event[i] = false;

	m_Lock = false;
	m_EventOn = true;


	m_CamControl->m_Event[0] = true;
	m_CamControl->m_Event[1] = false;
	m_CamControl->m_Event[2] = false;

	m_CamControl->m_Camera->stopAllActions();
	m_CamControl->m_Camera->setPosition(Vec2(ObjectHero::getInstance()->m_RebornPos.x, ObjectHero::getInstance()->m_RebornPos.y - 150));

	CSoundManager::getInstance()->playBgm("Sound/Sound/cavebgm2.mp3", true, true, 1.0f);

	m_Interact[3]->setPosition(Vec2(m_SavePoint[2].x, m_SavePoint[2].y - 180));



	if (Stage1_3Elite == false)
	{
		m_Demon->m_Death = false;
		m_Demon->m_Spr->setOpacity(255);
		m_Demon->m_Spr->stopAllActions();
		m_Demon->SetPosObject(-1100, 800);
		m_Demon->AnimationSwitch(EnemyMotion::RightWalk);

		if (m_Elite->m_CurMotion != 999)
			m_Elite->CreateElite(m_SavePoint[3]);
	}

	if (EliteClear == false)
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		if (pad->m_EliteHP_On)
		{
			pad->m_EliteHP_On = false;
			pad->m_EliteHPBack->removeFromParent();
			pad->m_EliteHPBar->removeFromParent();
		}
		extern EnemyManager* m_EnemyManager;
		std::list<MiniEnemy*>::iterator iter3 = m_EnemyManager->m_MiniList.begin();
		for (iter3 = m_EnemyManager->m_MiniList.begin(); iter3 != m_EnemyManager->m_MiniList.end(); iter3++)
		{
			(*iter3)->Recreate();
		}
	}
	else
	{
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		if (pad->m_Boss1HP_On)
		{
			pad->m_Boss1HP_On = false;
			pad->m_Boss1HPBack->removeFromParent();
			pad->m_Boss1HPBar->removeFromParent();
		}

		extern EnemyManager* m_EnemyManager;
		std::list<MiniEnemy*>::iterator iter3 = m_EnemyManager->m_MiniList.begin();
		for (iter3 = m_EnemyManager->m_MiniList.begin(); iter3 != m_EnemyManager->m_MiniList.end(); iter3++)
		{
			(*iter3)->m_Spr->setVisible(false);
			(*iter3)->m_Death = true;
		}

		//보스
		m_Boss1->m_Spr->stopAllActions();
		m_Boss1->m_HP = 250;
		m_Boss1->m_Lock = true;

		m_Interact[16]->setPosition(Vec2(m_SavePoint[5].x + 120, m_SavePoint[5].y - 120));
		m_Interact[17]->setPosition(Vec2(m_SavePoint[5].x + 120, m_SavePoint[5].y - 120));
		m_Interact[18]->setPosition(Vec2(m_SavePoint[5].x + 2040, m_SavePoint[5].y - 120));
		m_Interact[19]->setPosition(Vec2(m_SavePoint[5].x + 2040, m_SavePoint[5].y - 120));

		m_Spine->setVisible(false);
	}
}

void Stage1_3::BackScene()
{
	MemoryArrange();
	Scene* s = Stage2_1Loading::createScene();
	Director::getInstance()->replaceScene(s);
}

void Stage1_3::MemoryArrange()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->MemoryArrange();

	extern EnemyManager* m_EnemyManager;

	std::list<MiniEnemy*>::iterator iter2 = m_EnemyManager->m_MiniList.begin();
	for (int i = 0; m_EnemyManager->m_MiniList.size() != 0; ++i)
	{
		(*iter2)->Delete();
		m_EnemyManager->m_MiniList.erase(iter2);
		iter2 = m_EnemyManager->m_MiniList.begin();
	}
	std::vector<ObjectEnemy*>::iterator iter = m_EnemyManager->m_List.begin();
	for (int i = 0; m_EnemyManager->m_List.size() != 0; ++i)
	{
		(*iter)->Delete();
		m_EnemyManager->m_List.erase(iter);
		iter = m_EnemyManager->m_List.begin();
	}
	if (Stage1_3Elite == false)
	{
		m_Demon->DemonDelete2();
		m_Elite->BossDelete();
	}

	if (Boss1Clear == false)
	{
		m_Boss1->BossDelete();
	}
	std::list<Boss*>::iterator iter_boss = m_EnemyManager->m_Boss.begin();
	for (int i = 0; m_EnemyManager->m_Boss.size() != 0; ++i)
	{
		m_EnemyManager->m_Boss.erase(iter_boss);
		iter_boss = m_EnemyManager->m_Boss.begin();
	}
	SourceManager::getInstance()->ClearBoxVector();
	// 주인공 메모리해제
	ObjectHero::getInstance()->BulletDelete();
	this->removeChild(m_tmap);
	this->stopAllActions();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}

//배경 그리기
void Stage1_3::CreateBack()
{
	// 포탈 충돌박스
	potalRect = Sprite::create("Tutorial/Potal.png");
	potalRect->setPosition(Vec2(Portal.x, Portal.y + 100));
	potalRect->setScale(0.3f);
	potalRect->setVisible(false);
	this->addChild(potalRect, 9);
}

void Stage1_3::FatherEvent()
{
	static float once;
	//13500
	if (ObjectHero::getInstance()->m_Rect->getPositionX() > 13800 && once == false)
	{
		m_Father->setVisible(true);
		once = true;
		m_EventOn = false;
	
		GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
		pad->KeyClear();
		pad->m_KeyLock = true;
		//pad->SetLetter();
		pad->DirClear();

		m_CamControl->m_Camera->runAction(
			MoveTo::create(1.0f, Vec2(ObjectHero::getInstance()->m_Rect->getPositionX() + 400,
				m_CamControl->m_Camera->getPositionY())));
		/*Camera::getDefaultCamera()->runAction(Sequence::create(
			EaseOut::create(ScaleTo::create(1.0f, 0.7f, 0.7f), 2.0f), NULL));*/
		Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 45);
		HeroChat1->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), 1000));
		HeroChat1->setVisible(true);
		this->addChild(HeroChat1, 10);
		LabelTypingEffect::typeMessage(HeroChat1, "아버지! ", 0.1f, Color3B::WHITE);

		HeroChat1->runAction(Sequence::create(DelayTime::create(1.5f), Hide::create(), NULL));

		m_ChatBox = Sprite::create("UI/Chat.png");
		m_ChatBox->setPosition(HeroChat1->getPosition());
		this->addChild(m_ChatBox, 9);
		m_ChatBox->runAction(Sequence::create(DelayTime::create(1.5f), Hide::create(), NULL));
		m_ChatBox->setScaleX(0.5f);
		RUN_WITH_DELAY(2.0f, CC_CALLBACK_0(Stage1_3::FatherChat1, this));
	}
}

void Stage1_3::UpdateBack()
{

}

void Stage1_3::setViewPointCenter()
{

}

void Stage1_3::GuideCheck()
{
	for (int i = 0; i < 2; ++i)
	{
		if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Interact[i]->getBoundingBox()) && m_Guide[i]->isVisible() == false)
		{
			m_Guide[i]->setVisible(true);
			m_Guide[i]->runAction(Repeat::create(
				Sequence::create(ScaleTo::create(0.8f, 0.5f),
					ScaleTo::create(0.8f, 0.6f), NULL), 20));
		}
		else if (!ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect(m_Interact[i]->getBoundingBox()))
		{
			m_Guide[i]->stopAllActions();
			m_Guide[i]->setScale(0.6f);
			m_Guide[i]->setVisible(false);
		}
	}
}

void Stage1_3::FatherCreate()
{
	char str[100] = { 0 };
	for (int i = 0; i < 2; i++)
	{
		m_FatherEffect[i] = Animation::create();
		m_FatherEffect[i]->setDelayPerUnit(i == 0 ? 0.1f : 0.05f);
	}

	for (int i = 1; i <= 21; i++)// Idle
	{
		sprintf(str, "Monster/Father/Idle/Idle (%d).png", i);
		m_FatherEffect[0]->addSpriteFrameWithFileName(str);
	}

	for (int i = 1; i <= 51; i++)// Hand
	{
		sprintf(str, "Monster/Father/Hand/Hand (%d).png", i);
		m_FatherEffect[1]->addSpriteFrameWithFileName(str);
	}
	for (int i = 51; i != 1; i--)
	{
		sprintf(str, "Monster/Father/Hand/Hand (%d).png", i);
		m_FatherEffect[1]->addSpriteFrameWithFileName(str);
	}
	CC_SAFE_RETAIN(m_FatherEffect[0]);
	CC_SAFE_RETAIN(m_FatherEffect[1]);

	m_Father = Sprite::create("Monster/Father/Idle/Idle (1).png");
	m_Father->setVisible(false);
	m_Father->setPosition(Vec2(m_SavePoint[7].x + 300, m_SavePoint[7].y-20));
	m_Father->runAction(RepeatForever::create(Animate::create(m_FatherEffect[0])));
	this->addChild(m_Father, 7);
}