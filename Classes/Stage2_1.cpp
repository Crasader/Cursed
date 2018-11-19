#include "Default.h"

Scene* Stage2_1::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage2_1::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Stage2_1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	CSoundManager::getInstance()->playBgm("Stage2_1/darkforest1.mp3", true, true, 0.25f);

	m_winSize = Director::getInstance()->getWinSize();

	SourceManager::getInstance()->LoadingSource(this);
	Function::getInstance()->GetLayer(this);

	this->scheduleUpdate();

	m_UpdateFirst = false;

	RoadTileMap();

	m_CamControl = new CameraControl(m_winSize, Size(3840, 1080), this, ObjectHero::getInstance()->m_Rect->getPosition());
	m_CamControl->m_StageNum = 21;
	Vec2 fpos = ObjectHero::getInstance()->m_Rect->getPosition();
	m_CamControl->FadeScene(Vec2(fpos.x, fpos.y - 350));

	CreateBack();

	return true;
}

void Stage2_1::RoadTileMap()
{
	m_tmap = TMXTiledMap::create("Stage2_1/Stage2_1.tmx");
	this->addChild(m_tmap, 3);

	Sprite* turorialback = Sprite::create("Stage2_1/Stage2_1map.png");
	turorialback->setPosition(Vec2(1920, 640));
	this->addChild(turorialback, 2);

	Sprite* turorialbac2 = Sprite::create("Stage2_1/Stage2_1map2.png");
	turorialbac2->setPosition(Vec2(1920, 540));
	this->addChild(turorialbac2, 2);

	m_background1 = m_tmap->getLayer("Top");
	m_background1->setVisible(false);

	m_background2 = m_tmap->getLayer("Basic");
	m_background2->setVisible(false);

	m_Ground = m_tmap->getLayer("ColideRed");//충돌박스
	m_Ground->setVisible(false);

	TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("Spawn");
	ValueMap& spawnPoint = Spawn_Pos->getObject("Hero");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

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
		}
	}

	Function::getInstance()->MakeColideWidth(MapRedXY, size, MetaNum::Red);
	//Function::getInstance()->MakeColideHeight(MapRed2XY, size, MetaNum::Red);
	//Function::getInstance()->MakeColideWidth(MapMonXY, size, MetaNum::MonsterOnly);

	// 이펙트 생성
	EffectManager::getInstance()->GetLayer(this);
	EffectManager::getInstance()->CreateEffect();

}

void Stage2_1::update(float dt)
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);

	extern Timer2* m_Timer2;
	m_Timer2->SetTime(dt);

	// UI업데이트
	pad->UIupdate();
	if (ObjectHero::getInstance()->m_Spr->getBoundingBox().intersectsRect(potalRect->getBoundingBox()))
	{
		this->unscheduleUpdate();
		BackScene();
		return;
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

	// 카메라 세팅
	m_CamControl->SettingCamera();

	pad->UISetposition();

	// 배경 업데이트
	UpdateBack();
}

void Stage2_1::MemoryArrange()
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

void Stage2_1::BackScene()
{
	MemoryArrange();
	Scene* s = Stage2_2Loading::createScene();
	Director::getInstance()->replaceScene(s);
}

//배경 그리기
void Stage2_1::CreateBack()
{
	backbase = Sprite::create("Stage2_1/BackBase.png");
	backbase->setAnchorPoint(Vec2(0.0f, 0.0f));
	backbase->setPosition(Vec2(0, 0));
	this->addChild(backbase, -10);

	potalRect = Sprite::create("Tutorial/PotalRect.png");
	potalRect->setPosition(Vec2(3770, 300));
	potalRect->setOpacity(120);
	potalRect->setVisible(ColiideRect);
	this->addChild(potalRect, 11);

	//// Left
	Left[0] = Sprite::create("Stage2_1/Left1.png");
	Left[0]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Left[0]->setPosition(Vec2(0, 0));
	this->addChild(Left[0], -4);

	Left[1] = Sprite::create("Stage2_1/Left2.png");
	Left[1]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Left[1]->setPosition(Vec2(0, 0));
	this->addChild(Left[1], 10);

	//// Mid
	Mid[0] = Sprite::create("Stage2_1/Mid1.png");
	Mid[0]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid[0]->setPosition(Vec2(0, 0));
	this->addChild(Mid[0], -6);

	Mid[1] = Sprite::create("Stage2_1/Mid2.png");
	Mid[1]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid[1]->setPosition(Vec2(0, 0));
	this->addChild(Mid[1], -5);

	Mid[2] = Sprite::create("Stage2_1/Mid3.png");
	Mid[2]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid[2]->setPosition(Vec2(0, 0));
	this->addChild(Mid[2], 3);

	//// Right
	Right[0] = Sprite::create("Stage2_1/Right1.png");
	Right[0]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Right[0]->setPosition(Vec2(0, 0));
	this->addChild(Right[0], 0);

	//// Smoke
	Smoke[0] = Sprite::create("Stage2_1/Smoke1.png");
	Smoke[0]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Smoke[0]->setPosition(Vec2(0, 0));
	this->addChild(Smoke[0], 11);

	Smoke[1] = Sprite::create("Stage2_1/Smoke2.png");
	Smoke[1]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Smoke[1]->setPosition(Vec2(0, 0));
	this->addChild(Smoke[1], 11);

	Smoke[2] = Sprite::create("Stage2_1/Smoke3.png");
	Smoke[2]->setAnchorPoint(Vec2(0.0f, 0.0f));
	Smoke[2]->setPosition(Vec2(0, 0));
	this->addChild(Smoke[2], 11);
}

void Stage2_1::UpdateBack()
{
	Vec2 sample = ObjectHero::getInstance()->m_Rect->getPosition();
	sample.x -= 900;

	if (ObjectHero::getInstance()->m_Rect->getPositionX() > 900)
	{
		Mid[0]->setPositionX(sample.x*0.02f);
		Mid[1]->setPositionX(sample.x*0.035f);
		Mid[2]->setPositionX(sample.x*0.06f);
	}

	if (Smoke[0]->getPositionX() < 3840)
		Smoke[0]->setPositionX(Smoke[0]->getPositionX() + 1);
	else
		Smoke[0]->setPosition(Vec2(-3840, 0));

	if (Smoke[1]->getPositionX() < 3840)
		Smoke[1]->setPositionX(Smoke[1]->getPositionX() + 2);
	else
		Smoke[1]->setPosition(Vec2(-3840, 0));

	if (Smoke[2]->getPositionX() < 3840)
		Smoke[2]->setPositionX(Smoke[2]->getPositionX() + 1.5f);
	else
		Smoke[2]->setPosition(Vec2(-3840, 0));
}