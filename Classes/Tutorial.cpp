#include "Default.h"

Scene* Tutorial::createScene()
{
	auto scene = Scene::create();

	auto layer = Tutorial::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Tutorial::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_winSize = Director::getInstance()->getWinSize();

	Fade = Sprite::create("TileMap/Fade.png");
	Fade->setOpacity(0);
	this->addChild(Fade, 50);

	auto tutorial = Sprite::create("Tutorial/Tutorial.png");
	tutorial->setPosition(Vec2(m_winSize.width*0.5f + 200, m_winSize.height * 0.5f + m_winSize.height * 0.1f));
	tutorial->setOpacity(0);
	this->addChild(tutorial, 20);

	tutorial->runAction(Sequence::create(
		FadeIn::create(1.0f),DelayTime::create(2.0f),FadeOut::create(1.0f),RemoveSelf::create(), NULL));
	CSoundManager::getInstance()->playBgm("Sound/Nevada_City.mp3", true, true, 1.0f);

	for (int i = 0; i < 10; ++i)
		m_event2[i] = false;

	//��ٸ�üũ�� ���� �ӽ� true
	m_Lock = false;
	m_Message = Sprite::create();
	this->addChild(m_Message, 13);

	SourceManager::getInstance()->LoadingSource(this);
	Function::getInstance()->GetLayer(this);


	m_Timer = 0;
	m_GameSwitch = false;
	m_UpdateFirst = false;

	CreateBack();
	RoadTileMap();

	m_CamControl = new CameraControl(m_winSize, Size(4800, 1680), this, ObjectHero::getInstance()->m_Rect->getPosition());
	m_CamControl->m_StageNum = 10;
	Vec2 fpos = ObjectHero::getInstance()->m_Rect->getPosition();
	m_CamControl->FadeScene(Vec2(fpos.x, fpos.y - 350));

	this->scheduleUpdate();

	return true;
}


// �ʷε�
void Tutorial::RoadTileMap()
{
	//���̺� ����
	//m_SaveNum = UserDefault::getInstance()->getFloatForKey("Clear_Time", 0.0f);
	m_SaveNum = 0;

	//Ÿ�ϸ� �ε�
	m_tmap = TMXTiledMap::create("Tutorial/prologue.tmx");
	this->addChild(m_tmap, 1, 11);

	Sprite* floorLine = Sprite::create("Tutorial/FloorLine.png");
	floorLine->setPosition(Vec2(2400, -40));
	this->addChild(floorLine, 1);

	Sprite* turorialback = Sprite::create("Tutorial/prologue.png");
	turorialback->setPosition(Vec2(2400, 840));
	this->addChild(turorialback, 1);

	m_background1 = m_tmap->getLayer("RBlack2");
	m_background1->setVisible(false);

	m_background2 = m_tmap->getLayer("RTop");
	m_background2->setVisible(false);

	m_background3 = m_tmap->getLayer("RLeft");
	m_background3->setVisible(false);

	m_background4 = m_tmap->getLayer("RRight");
	m_background4->setVisible(false);

	m_background5 = m_tmap->getLayer("RBottom");
	m_background5->setVisible(false);

	auto Ladder2 = Sprite::create("Tutorial/MapLadder.png");
	Ladder2->setAnchorPoint(Vec2(0.5f, 0.0f));
	Ladder2->setPosition(Vec2(1787, 160));
	this->addChild(Ladder2, 3);

	m_Ground = m_tmap->getLayer("ColideRed");//�浹�ڽ�
	m_Ground->setVisible(false);

	m_Jump = m_tmap->getLayer("ColideBlue");
	m_Jump->setVisible(false);

	//m_MonsterCol = m_tmap->getLayer("MonsterColide");
	//m_MonsterCol->setVisible(false);

	m_Ladder = m_tmap->getLayer("ColideGreen");
	m_Ladder->setVisible(false);

	m_LadderEnd = m_tmap->getLayer("GreenEnd");
	m_LadderEnd->setVisible(false);

	TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("SpawnHero");
	ValueMap& spawnPoint = Spawn_Pos->getObject("HeroPos");
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

	// ���� ��� ����
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->GetLayer(this);
	m_WeaponManager->CreateMotion();

	// �� ��� ����
	extern ShieldManager* m_ShieldManager;
	m_ShieldManager->GetLayer(this);
	m_ShieldManager->CreateMotion();

	//���ΰ� ������ �ʱ�ȭ
	ObjectHero::getInstance()->GetLayer(this);
	ObjectHero::getInstance()->CreateObject(x + 300, y + 00);
	ObjectHero::getInstance()->m_RebornPos = Vec2(x + 300, y + 00);

	//setViewPointCenter(ObjectHero::getInstance()->m_Rect->getPosition());

	auto meta4 = Sprite::create("TileMap/Dummy/MetaSet4.png");
	auto ladder = Sprite::create("TileMap/Dummy/Ladder1.png");

	Vec2 tileCoord;
	int tileGid;
	Vec2 size = m_tmap->getMapSize();
	//�浹�ڽ� Vector�� ����
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
						int x = tileCoord.x * m_tmap->getTileSize().width;
						int y = (size.y - 1) * 80 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxRed->getSpriteFrame());
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y + 80);
						spr->setTag(MetaNum::Red);
						this->addChild(spr, 5);
						SourceManager::getInstance()->m_metabox.pushBack(spr);
					}
				}
			}
			//���ڽ�
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
			//��ٸ�
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

						auto spr = Sprite::createWithSpriteFrame(meta4->getSpriteFrame());
						spr->setTag(MetaNum::GreenL);
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y + 80);
						this->addChild(spr, 5);
						SourceManager::getInstance()->m_metabox.pushBack(spr);
					}
				}
			}
			//��ٸ� ��(��ǹ� �������� üũ��)
			tileGid = m_LadderEnd->getTileGIDAt(tileCoord);
			if (tileGid)
			{
				Value property2 = m_tmap->getPropertiesForGID(tileGid);
				property2 = m_LadderEnd->getProperties();
				if (!property2.isNull())
				{
					std::string wall = property2.asValueMap()["Flip"].asString();
					if (wall == "YES")
					{
						int x = tileCoord.x * m_tmap->getTileSize().width;
						int y = (size.y - 1) * 80 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(meta4->getSpriteFrame());
						spr->setTag(MetaNum::GreenEnd);
						spr->setFlipX(true);
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

	// ����Ʈ ����
	EffectManager::getInstance()->GetLayer(this);
	//Tutorial �� ���ս� ���� �ϰ� �ڿ����� �ּ�ó�� �ؾ� ��
	EffectManager::getInstance()->CreateEffect();

	// ������
	CreateEnemy();

	// �����۹ڽ� ����
	CreateItem();

	// ��ֹ� ����
	CreateBarrier();
	return;
}

void Tutorial::setViewPointCenter(Vec2 pos)
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

	this->setPosition(viewPoint);
}

//��ֹ� ����
void Tutorial::CreateBarrier()
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierManager->m_List.clear();
	m_BarrierManager->GetLayer(this);
	m_BarrierManager->GetSource(SourceManager::getInstance());

	ObjectBarrier* spine1 = new ObjectBarrier;
	spine1->CreateBarrier(600, 200, BarrierType::Spine);
	spine1->SetRotation(-1, 0.3f);

	ObjectBarrier* spine2 = new ObjectBarrier;
	spine2->CreateBarrier(1140, 260, BarrierType::Spine2);
	spine2->SetRotation(-1, 0.4f);

	ObjectBarrier* stone = new ObjectBarrier;
	stone->CreateBarrier(2278, 887, BarrierType::Stone1);
	stone->SetRotation(0, 0.5f);

	ObjectBarrier* Interact = new ObjectBarrier;
	Interact->CreateBarrier(3278, 807, BarrierType::Gate2);
}

//������ ����
void Tutorial::CreateItem()
{
	// ȹ�氡�� ������ �ڽ�
	extern ItemManager* m_ItemManager;
	m_ItemManager->m_List.clear();
	m_ItemManager->GetLayer(this);

	/*ObjectItem* Item0 = new ObjectItem;
	Item0->CreateObject(2900, 850, Item::None);*/

	ObjectItem* Item0 = new ObjectItem;
	Item0->CreateObject(2900, 810, Item::Box1);
}

//�� ���� 
void Tutorial::CreateEnemy()
{
	extern EnemyManager* m_EnemyManager;
	m_EnemyManager->m_List.clear();
	m_EnemyManager->GetLayer(this);
	m_EnemyManager->GetSource(SourceManager::getInstance());
}

//��ֹ� ������Ʈ
void Tutorial::UpdateBarrier()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern BarrierManager* m_BarrierManager;
		m_BarrierManager->BarrierUpdate();
	}
}

// ������ ������Ʈ
void Tutorial::CheckColide()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern ItemManager* m_ItemManager;
		std::vector<ObjectItem*>::iterator iter = m_ItemManager->m_List.begin();

		for (iter; iter != m_ItemManager->m_List.end(); ++iter)
		{
			//// ���̺� �ڽ�
			if ((*iter)->m_SaveObject && (*iter)->m_Spr->getName() == "ItemSave")//���̺� ����Ʈ���
			{
				if ((*iter)->m_Rect->getBoundingBox().intersectsRect(ObjectHero::getInstance()->m_Rect->getBoundingBox()))
				{
					for (ObjectItem* iter2 : m_ItemManager->m_List)
					{
						if (iter2->m_SaveObject == false && iter2->m_Spr->getName() == "ItemSave")//���� ��Ȱ��ȭ�ϰ��� ���̺�����Ʈ �ٽ� Ȱ��ȭ
							iter2->m_SaveObject = true;
					}
					(*iter)->AnimationSwitch(ObjectEffect::Saving);
					m_SaveNum = (*iter)->m_SaveNum;
					UserDefault::getInstance()->setFloatForKey("Clear_Time", m_SaveNum);
					return;
				}
			}
			//// ������ �ڽ�
			else if ((*iter)->m_ItemExit)// ���ڸ� �νŻ��°� �ƴ϶��
			{
				(*iter)->ItemUpdate();
				if (ObjectHero::getInstance()->m_Rect->getBoundingBox().intersectsRect((*iter)->m_Item->getBoundingBox()))
				{
					if (ObjectHero::getInstance()->m_GetOn)
					{
						if (ObjectHero::getInstance()->GetItem((*iter)))// ����, ���� ���
						{
							(*iter)->ItemDelete();
							m_ItemManager->m_List.erase(iter);
							return;
						}
						else// ��ų ��ũ���ΰ��
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

void Tutorial::UpdateEnemy()
{
	// �̵� / ���� / �Ѿ˰� �浹üũ
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
				(*iter)->EnemyUpdate();//�� �Ѿ� �̵�
			}
		}
	}
}

void Tutorial::update(float dt)
{
	UpdateBack();//��� ����
	TutorialEvent();//Ʃ�丮�� �̺�Ʈ üũ
	Vec2 ex = ObjectHero::getInstance()->m_Spr->getPosition();
	extern Timer2* m_Timer2;
	m_Timer2->SetTime(dt);

	// UI������Ʈ
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->UIupdate();
	if (pad->m_KeyUp)
	{
		if (ObjectHero::getInstance()->m_Spr->getBoundingBox().intersectsRect(potalRect->getBoundingBox()))
		{
			this->unscheduleUpdate();
			extern WeaponManager* m_WeaponManager;
			m_WeaponManager->CloseWeapon->runAction(FadeOut::create(1.0f));
			ObjectHero::getInstance()->m_Spr->runAction(Sequence::create(
				FadeOut::create(1.0f),
				CallFunc::create(CC_CALLBACK_0(Tutorial::BackScene, this)),
				NULL));
			return;
		}
	}
	// ���ΰ� ������Ʈ
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

		if (ObjectHero::getInstance()->m_Rect->getPositionY() < 0)
		{
			ObjectHero::getInstance()->m_Rect->setPosition(ObjectHero::getInstance()->m_RebornPos);
			ObjectHero::getInstance()->m_Spr->setPosition(Vec2(ObjectHero::getInstance()->m_Rect->getPositionX(), ObjectHero::getInstance()->m_Rect->getPositionY() + SpineDif_Y));
			Vec2 sample = ObjectHero::getInstance()->m_Spr->getPosition();
			Vec2 sample2 = sample;
			sample2.x -= 900;
			leftFrontGround->setPosition(Vec2(-80 + sample2.x*0.05f, 80));
			leftFrontGround2->setPosition(Vec2(-80 + sample2.x*0.04f, 80));
			leftFrontGround3->setPosition(Vec2(-80 + sample2.x*0.03f, 80));
			leftstone1->setPosition(Vec2(-80 + sample2.x*0.04f, 80));
			leftTree->setPosition(Vec2(-80 + sample2.x*0.02f, 80));
		}
	}

	m_Timer += dt;
	ObjectHero::getInstance()->GetTime(dt);

	//�� ������Ʈ
	UpdateEnemy();

	// ������, �� �浹üũ
	CheckColide();

	// ��ֹ� ������Ʈ
	UpdateBarrier();

	// ī�޶� ����
	m_CamControl->SettingCamera();

	pad->UISetposition();
}

void Tutorial::GameOver()
{
	Scene* s = TransitionFade::create(1.0f, Tutorial::createScene());
	Director::getInstance()->replaceScene(s);
}

void Tutorial::BackScene()
{
	MemoryArrange();
	Scene* s = Stage1_2Loading::createScene();
	Director::getInstance()->replaceScene(s);
}

void Tutorial::MemoryArrange()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->MemoryArrange();

	this->removeChild(m_background1);
	this->removeChild(m_background2);
	this->removeChild(m_background3);
	this->removeChild(m_background4);
	this->removeChild(m_background5);
	this->removeChild(m_background6);
	this->removeChild(m_MonsterCol);
	this->removeChild(m_Ground);
	this->removeChild(m_Jump);
	this->removeChild(m_Ladder);
	this->removeChild(m_LadderEnd);

	//this->removeChild(m_tmap);
	this->stopAllActions();
	// ���ΰ� �޸�����
	ObjectHero::getInstance()->BulletDelete();
	SourceManager::getInstance()->ClearBoxVector();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}
void Tutorial::ChangeEventState()
{
	m_Lock = false;
}
void Tutorial::ChangeEventState2()
{
	auto msg = dynamic_cast<Sprite*>(this->getChildByName("Event1"));
	if (msg->getName() == "Event1")
		m_event2[0] = true;
}
void Tutorial::TutorialEvent()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);

	char str[100] = { "fonts/gabia_napjakBlock.ttf" };
	static bool m_event1[20];
	//����Ű �޼���
	if (ObjectHero::getInstance()->m_Spr->getPositionX() > 300 && ObjectHero::getInstance()->m_Spr->getPositionX() < 400 && m_event1[0] == false)
	{
		m_event1[0] = true;
		m_Lock = true;

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(250, 700));
		txtLabel->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel, "��Ӱ� �Ⱬ�� ���Դϴ�.", 0.05f);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));
		auto txtLabel2 = Label::createWithTTF("", str, 35);
		txtLabel2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel2->setPosition(Vec2(250, 660));
		txtLabel2->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel2, "����Ű�� ����� ������ �̵��ϼ���", 0.05f);
		this->addChild(txtLabel2, 15);
		txtLabel2->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));
		auto foraction = Sprite::create();
		foraction->setName("Event1");
		foraction->runAction(Sequence::create(
			DelayTime::create(3.0f),
			CallFunc::create(CC_CALLBACK_0(Tutorial::ChangeEventState2, this)),
			NULL));
		this->addChild(foraction);
	}
	else if (m_event2[0] && m_event1[0])
	{
		m_event2[0] = false;

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(450, 350));
		txtLabel->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel, "AltŰ�� ���� ������ ��ֹ��� ���ϼ���", 0.05f);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));

		auto foraction = Sprite::create();
		foraction->runAction(Sequence::create(
			DelayTime::create(3.0f),
			CallFunc::create(CC_CALLBACK_0(Tutorial::ChangeEventState, this)),
			NULL));
		this->addChild(foraction);
	}
	else if (m_event2[0] == false && ObjectHero::getInstance()->m_Spr->getPositionX() > 810 && m_event2[1] == false)
	{
		m_event2[1] = true;

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(840, 450));
		txtLabel->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel, "�������¿��� AltŰ�� �ѹ� �� ������", 0.05f);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));

		auto txtLabel2 = Label::createWithTTF("", str, 35);
		txtLabel2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel2->setPosition(Vec2(840, 410));
		txtLabel2->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel2, "2�� ������ �����ϴ�", 0.05f);
		this->addChild(txtLabel2, 15);
		txtLabel2->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));
	}
	else if (ObjectHero::getInstance()->m_Spr->getPositionX() > 1570 && m_event2[1] && m_event2[2] == false)
	{
		m_event2[2] = true;

		auto txtLabel3 = Label::createWithTTF("", "fonts/210 �Ƹ��R.ttf", 35);
		txtLabel3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel3->setPosition(Vec2(1500, 450));
		txtLabel3->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel3, "��", 0.05f);
		this->addChild(txtLabel3, 15);
		txtLabel3->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(1500, 450));
		txtLabel->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel, "    Ű�� ���� ��ٸ��� Ÿ����", 0.05f);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));
	}
	else if (ObjectHero::getInstance()->m_Spr->getPositionX() > 1890 && m_event2[2] == true && m_event2[3] == false)
	{
		m_event2[3] = true;

		auto txtLabel3 = Label::createWithTTF("", "fonts/210 �Ƹ��R.ttf", 35);
		txtLabel3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel3->setPosition(Vec2(2000, 1050));
		txtLabel3->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel3, "��", 0.05f);
		this->addChild(txtLabel3, 15);
		txtLabel3->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(2000, 1050));
		txtLabel->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel, "    Ű�� �������� ���� �뽬��", 0.05f);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));

		auto txtLabel2 = Label::createWithTTF("", str, 35);
		txtLabel2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel2->setPosition(Vec2(2000, 1010));
		txtLabel2->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel2, "��ֹ��� ȸ���ϼ���", 0.05f);
		this->addChild(txtLabel2, 15);
		txtLabel2->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));
	}
	else if (ObjectHero::getInstance()->m_Spr->getPositionX() > 2650 && m_event2[3] && m_event2[4] == false)
	{
		m_event2[4] = true;

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(2500, 1050));
		txtLabel->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel, "Ctrl Ű�� ������ �׾Ƹ��� �ı��ϼ���", 0.05f);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));
	}
	else if (ObjectHero::getInstance()->m_Spr->getPositionX() > 3100 && m_event2[4] && m_event2[5] == false)
	{
		m_event2[5] = true;

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(2940, 1160));
		txtLabel->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel, "���¼��� XŰ�� ���� ��ȣ�ۿ��ϼ���", 0.05f);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));
	}
	else if (ObjectHero::getInstance()->m_Spr->getPositionX() > 4400 && m_event2[5] && m_event2[6] == false)
	{
		m_event2[6] = true;

		auto txtLabel3 = Label::createWithTTF("", "fonts/210 �Ƹ��R.ttf", 35);
		txtLabel3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel3->setPosition(Vec2(4250, 1200));
		txtLabel3->setColor(Color3B::WHITE);
		LabelTypingEffect::typeMessage(txtLabel3, "��", 0.05f, Color3B::RED);
		this->addChild(txtLabel3, 15);
		txtLabel3->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));

		auto txtLabel = Label::createWithTTF("", str, 35);
		txtLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		txtLabel->setPosition(Vec2(4250, 1200));
		LabelTypingEffect::typeMessage(txtLabel, "    Ű�� ���� �����ȿ� �����ϼ���", 0.05f, Color3B::RED);
		this->addChild(txtLabel, 15);
		txtLabel->runAction(Sequence::create(
			DelayTime::create(2.5f), FadeOut::create(1.0f), RemoveSelf::create(),
			NULL));

	}
}

//��� �׸���
void Tutorial::CreateBack()
{
	//��Ż �浹�ڽ�
	potalRect = Sprite::create("Tutorial/PotalRect.png");
	potalRect->setPosition(Vec2(4500, 1030));
	potalRect->setVisible(false);
	this->addChild(potalRect, 9);

	// ������Ż
	Sprite* potal = Sprite::create("Tutorial/Right/Cage_Potal.png");
	potal->setAnchorPoint(Vec2(0.0f, 0.0f));
	potal->setPosition(Vec2(160, 0));
	this->addChild(potal, 8);

	// �⺻ ���̽�
	backbase = Sprite::create("Tutorial/TutorialBack.png");
	backbase->setScaleY(1.1f);
	backbase->setAnchorPoint(Vec2(0.0f, 0.0f));
	backbase->setPosition(Vec2(0, -80));
	this->addChild(backbase, -10);

	///////////////////////���� ������///////////////////////////////////////////
	// ���� �ٰ�
	leftShadow = Sprite::create("Tutorial/CloseBack.png");
	leftShadow->setAnchorPoint(Vec2(0.0f, 0.0f));
	leftShadow->setPosition(Vec2(0, 80));
	this->addChild(leftShadow, 10);
	//���� �� ����2
	leftFrontGround2 = Sprite::create("Tutorial/Left/Front_Left_Ground2.png");
	leftFrontGround2->setAnchorPoint(Vec2(0.0f, 0.0f));
	leftFrontGround2->setPosition(Vec2(-80, 80));
	this->addChild(leftFrontGround2, -3);
	//���� �� ����1
	leftFrontGround = Sprite::create("Tutorial/Left/Front_Left_Ground.png");
	leftFrontGround->setAnchorPoint(Vec2(0.0f, 0.0f));
	leftFrontGround->setPosition(Vec2(-80, 80));
	this->addChild(leftFrontGround, -2);
	//���� �� �����µ�
	leftstone1 = Sprite::create("Tutorial/Left/Stone1.png");
	leftstone1->setAnchorPoint(Vec2(0.0f, 0.0f));
	leftstone1->setPosition(Vec2(-80, 80));
	this->addChild(leftstone1, -3);
	//���� �� �����µ�2
	leftstone2 = Sprite::create("Tutorial/Left/Stone2.png");
	leftstone2->setAnchorPoint(Vec2(0.0f, 0.0f));
	leftstone2->setPosition(Vec2(-80, 80));
	this->addChild(leftstone2, -2);
	//���� �� ����3
	leftFrontGround3 = Sprite::create("Tutorial/Left/Front_Left_Ground3.png");
	leftFrontGround3->setAnchorPoint(Vec2(0.0f, 0.0f));
	leftFrontGround3->setPosition(Vec2(-80, 80));
	this->addChild(leftFrontGround3, -4);
	//���� �� ����3
	leftTree = Sprite::create("Tutorial/Left/LeftTree.png");
	leftTree->setAnchorPoint(Vec2(0.0f, 0.0f));
	leftTree->setPosition(Vec2(-80, 80));
	this->addChild(leftTree, -5);

	//////////////////////�߾� ������//////////////////////////////////////////
	//�߾� ���Ͼ� ��
	Mid_Back = Sprite::create("Tutorial/Mid/Mid_Back.png");
	Mid_Back->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid_Back->setPosition(Vec2(0, 00));
	this->addChild(Mid_Back, -2);
	//�߾� ���Ͼ� �� �ϳ� ��
	Mid_Back2 = Sprite::create("Tutorial/Mid/Mid_Back2.png");
	Mid_Back2->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid_Back2->setPosition(Vec2(0, 00));
	this->addChild(Mid_Back2, -3);
	//�߾� ���Ͼ� �� �ϳ� ��2
	Mid_Back3 = Sprite::create("Tutorial/Mid/Mid_Back3.png");
	Mid_Back3->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid_Back3->setPosition(Vec2(0, 00));
	this->addChild(Mid_Back3, -5);
	//�߾� ��
	Mid_Moutain = Sprite::create("Tutorial/Mid/Mid_Mountain.png");
	Mid_Moutain->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid_Moutain->setPosition(Vec2(0, 80));
	this->addChild(Mid_Moutain, -8);
	//�߾� ����
	Mid_Grand = Sprite::create("Tutorial/Mid/Mid_Grand.png");
	Mid_Grand->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid_Grand->setPosition(Vec2(0, 80));
	this->addChild(Mid_Grand, -7);
	//�߾� ����
	Mid_Tree1 = Sprite::create("Tutorial/Mid/Mid_Tree.png");
	Mid_Tree1->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid_Tree1->setPosition(Vec2(0, 80));
	this->addChild(Mid_Tree1, -6);
	//�߾� ���ٱ�
	Mid_Plant1 = Sprite::create("Tutorial/Mid/Mid_Plant1.png");
	Mid_Plant1->setAnchorPoint(Vec2(0.0f, 0.0f));
	Mid_Plant1->setPosition(Vec2(0, 80));
	this->addChild(Mid_Plant1, -2);

	//////////////////////������ ������
	//������ �ٰ�
	/*RightShadow = Sprite::create("Tutorial/Right/RightShadow.png");
	RightShadow->setAnchorPoint(Vec2(0.0f, 0.0f));
	RightShadow->setPosition(Vec2(3874, 80));
	this->addChild(RightShadow, 10);*/
	//���� �޹��
	CageBack = Sprite::create("Tutorial/Right/CageBack.png");
	CageBack->setAnchorPoint(Vec2(0.0f, 0.0f));
	CageBack->setScaleY(1.2f);
	CageBack->setPosition(Vec2(0, 80));
	this->addChild(CageBack, -4);
	//���� + ��������Ʈ
	CageEffect = Sprite::create("Tutorial/Right/Cage_Effect.png");
	CageEffect->setAnchorPoint(Vec2(0.0f, 0.0f));
	CageEffect->setPosition(Vec2(80, 80));
	this->addChild(CageEffect, -3);

	/////////////////// ����������
	//����1
	Cloud1 = Sprite::create("Tutorial/Cloud/Cloud1.png");
	Cloud1->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud1->setPosition(Vec2(0, 00));
	this->addChild(Cloud1, -4);
	//����2
	Cloud2 = Sprite::create("Tutorial/Cloud/Cloud2.png");
	Cloud2->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud2->setPosition(Vec2(0, 00));
	this->addChild(Cloud2, -4);
	//����3
	Cloud3 = Sprite::create("Tutorial/Cloud/Cloud3.png");
	Cloud3->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud3->setPosition(Vec2(0, 00));
	this->addChild(Cloud3, -4);
	//����4
	Cloud4 = Sprite::create("Tutorial/Cloud/Cloud4.png");
	Cloud4->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud4->setPosition(Vec2(-100, 250));
	this->addChild(Cloud4, -3);
	//����5
	Cloud5 = Sprite::create("Tutorial/Cloud/Cloud4.png");
	Cloud5->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud5->setPosition(Vec2(-300, 00));
	this->addChild(Cloud5, -2);
	//����6
	Cloud6 = Sprite::create("Tutorial/Cloud/Cloud6.png");
	Cloud6->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud6->setPosition(Vec2(0, 00));
	this->addChild(Cloud6, 9);
	//����7
	Cloud7 = Sprite::create("Tutorial/Cloud/Cloud7.png");
	Cloud7->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud7->setPosition(Vec2(0, 00));
	this->addChild(Cloud7, -2);
	//����8
	Cloud8 = Sprite::create("Tutorial/Cloud/Cloud8.png");
	Cloud8->setAnchorPoint(Vec2(0.0f, 0.0f));
	Cloud8->setPosition(Vec2(-50, -50));
	this->addChild(Cloud8, -2);
}

void Tutorial::UpdateBack()
{
	Vec2 sample = ObjectHero::getInstance()->m_Spr->getPosition();
	Vec2 sample2 = sample;
	sample2.x -= 900;
	// �⺻ ���̽�
	//backbase->setPosition(Vec2(0 + sample.x*0.015f, 00));

	// ����������
	if (ObjectHero::getInstance()->m_Spr->getPositionX() > 900)
	{
		leftFrontGround->setPosition(Vec2(-80 + sample2.x*0.05f, 80));
		leftFrontGround2->setPosition(Vec2(-80 + sample2.x*0.04f, 80));
		leftFrontGround3->setPosition(Vec2(-80 + sample2.x*0.03f, 80));
		leftstone1->setPosition(Vec2(-80 + sample2.x*0.04f, 80));
		leftTree->setPosition(Vec2(-80 + sample2.x*0.02f, 80));
	}

	// �߾�������
	//if (Hero->m_Spr->getPositionX() > 900)
	{
		Mid_Back->setPosition(Vec2(0 + sample.x*0.04f, 0));
		Mid_Back2->setPosition(Vec2(0 + sample.x*0.03f, 0));
		Mid_Back3->setPosition(Vec2(0 + sample.x*0.03f, 0));
		Mid_Moutain->setPosition(Vec2(0 + sample.x*0.02f, 80));
		Mid_Grand->setPosition(Vec2(0 + sample.x*0.03f, 80));
		Mid_Tree1->setPosition(Vec2(0 + sample.x*0.02f, 80));
		Mid_Plant1->setPosition(Vec2(0 + sample.x*0.02f, 80));
	}
	// ������������
	if (ObjectHero::getInstance()->m_Spr->getPositionX() < 3840)
	{
		CageBack->setPosition(Vec2(-150 + sample.x*0.03f, 80));
		CageEffect->setPosition(Vec2(-150 + 80 + sample.x*0.04f, 80));
	}

	// ������
	if (Cloud1->getPositionX() < 4800)
		Cloud1->setPosition(Vec2(Cloud1->getPositionX() + 1, Cloud1->getPositionY()));
	else
		Cloud1->setPosition(Vec2(-4800, 0));

	if (Cloud2->getPositionX() < 4800)
		Cloud2->setPosition(Vec2(Cloud2->getPositionX() + 3, Cloud2->getPositionY()));
	else
		Cloud2->setPosition(Vec2(-4800, 0));

	if (Cloud3->getPositionX() < 4800)
		Cloud3->setPosition(Vec2(Cloud3->getPositionX() + 4, Cloud3->getPositionY()));
	else
		Cloud3->setPosition(Vec2(-4800, 0));

	if (Cloud4->getPositionX() < 4800)
		Cloud4->setPosition(Vec2(Cloud4->getPositionX() + 0.5f, Cloud4->getPositionY()));
	else
		Cloud4->setPosition(Vec2(-4800, 0));

	if (Cloud5->getPositionX() < 4800)
		Cloud5->setPosition(Vec2(Cloud5->getPositionX() + 0.3f, Cloud5->getPositionY()));
	else
		Cloud5->setPosition(Vec2(-4800, 0));

	if (Cloud6->getPositionX() < 4800)
		Cloud6->setPosition(Vec2(Cloud6->getPositionX() + 1.0f, Cloud6->getPositionY()));
	else
		Cloud6->setPosition(Vec2(-4800, 0));

	if (Cloud7->getPositionX() < 4800)
		Cloud7->setPosition(Vec2(Cloud7->getPositionX() + 4.0f, Cloud7->getPositionY()));
	else
		Cloud7->setPosition(Vec2(-4800, 0));

	if (Cloud8->getPositionX() < 4800)
		Cloud8->setPosition(Vec2(Cloud8->getPositionX() + 2.0f, Cloud8->getPositionY()));
	else
		Cloud8->setPosition(Vec2(-4800, 0));
}