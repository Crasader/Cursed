#include "Default.h"

Scene* Stage1_1::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage1_1::create();
	scene->addChild(layer, 1);

	auto GamePad = GameUI::create();
	GamePad->setTag(100);
	GamePad->InitStageScene();
	scene->addChild(GamePad, 5);

	return scene;
}

bool Stage1_1::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CSoundManager::getInstance()->playBgm("Sound/Nevada_City.mp3", true, true, 1.0f);
	CSoundManager::getInstance()->preloadAudioFile("Sound/HeroAttack/Male_LS_L_AttackGrunt06.mp3");// �ε�
	CSoundManager::getInstance()->preloadAudioFile("Sound/Hero/Male_Jump_Grunt01.mp3");// �ε�
	CSoundManager::getInstance()->preloadAudioFile("Sound/Hero/Male_LS_H_Death02.mp3");// �ε�

	m_Lock = false;
	m_EndAction = false;

	SourceManager::getInstance()->LoadingSource(this);
	Function::getInstance()->GetLayer(this);

	m_winSize = Director::getInstance()->getWinSize();

	m_Timer = 0;
	m_GameSwitch = false;
	m_UpdateFirst = false;

	CreateBack();
	RoadTileMap();

	m_CamControl = new CameraControl(m_winSize, Size(10320, 2160), this, ObjectHero::getInstance()->m_Rect->getPosition());
	m_CamControl->m_StageNum = 11;
	Vec2 fpos = ObjectHero::getInstance()->m_Rect->getPosition();
	//m_CamControl->FadeScene(Vec2(fpos.x, fpos.y - 350));

	this->scheduleUpdate();

	return true;
}

void Stage1_1::RoadTileMap()
{
	//���̺� ����
	//m_SaveNum = UserDefault::getInstance()->getFloatForKey("Clear_Time", 0.0f);
	m_SaveNum = 0;

	//Ÿ�ϸ� �ε�
	m_tmap = TMXTiledMap::create("Stage1_1/Stage1_1.tmx");
	this->addChild(m_tmap, 1, 11);

	Sprite* turorialback = Sprite::create("Stage1_1/Stage1_1.png");
	turorialback->setPosition(Vec2(5160, 1080));
	this->addChild(turorialback, 2);

	m_background1 = m_tmap->getLayer("Basic");
	m_background1->setVisible(false);

	m_background1 = m_tmap->getLayer("Right");
	m_background1->setVisible(false);

	m_background1 = m_tmap->getLayer("Left");
	m_background1->setVisible(false);

	m_background1 = m_tmap->getLayer("Top");
	m_background1->setVisible(false);

	m_background1 = m_tmap->getLayer("Bottom");
	m_background1->setVisible(false);

	m_Ground = m_tmap->getLayer("ColideRed");//�浹�ڽ�
	m_Ground->setVisible(false);


	//TMXObjectGroup* Spawn_Pos = m_tmap->getObjectGroup("SpawnHero");
	//ValueMap& spawnPoint = Spawn_Pos->getObject("Hero");
	float x = 0;
	float y = 0;


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
	ObjectHero::getInstance()->CreateObject(300, 1200);

	auto meta4 = Sprite::create("TileMap/Dummy/MetaSet4.png");

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
						int y = (size.y-1)*80 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(SourceManager::getInstance()->metaboxRed->getSpriteFrame());
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y + 80);
						this->addChild(spr, 5);
						SourceManager::getInstance()->m_metabox.pushBack(spr);
					}
				}
			}
			//���ڽ�
			/*tileGid = m_Jump->getTileGIDAt(tileCoord);
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
						int y = 2080 - tileCoord.y * m_tmap->getTileSize().height;

						auto spr = Sprite::createWithSpriteFrame(m_Soucre->metaboxBlue->getSpriteFrame());
						spr->setTag(MetaNum::Blue);
						spr->setVisible(ColiideRect);
						spr->setAnchorPoint(Vec2(0.0f, 1.0f));
						spr->setPosition(x, y + 80);
						this->addChild(spr, 5);
						m_Soucre->m_metabox.pushBack(spr);
					}
				}
			}*/
			//��ٸ�
			//tileGid = m_Ladder->getTileGIDAt(tileCoord);
			//if (tileGid)
			//{
			//	Value property2 = m_tmap->getPropertiesForGID(tileGid);
			//	property2 = m_Jump->getProperties();
			//	if (!property2.isNull())
			//	{
			//		std::string wall = property2.asValueMap()["Wall"].asString();
			//		if (wall == "YES")
			//		{
			//			int x = tileCoord.x * m_tmap->getTileSize().width;
			//			int y = 2080 - tileCoord.y * m_tmap->getTileSize().height;

			//			auto spr = Sprite::createWithSpriteFrame(meta4->getSpriteFrame());
			//			spr->setTag(MetaNum::GreenL);
			//			spr->setVisible(ColiideRect);
			//			spr->setAnchorPoint(Vec2(0.0f, 1.0f));
			//			spr->setPosition(x, y + 80);
			//			this->addChild(spr, 5);
			//			m_Soucre->m_metabox.pushBack(spr);
			//		}
			//	}
			//}
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

//��ֹ� ����
void Stage1_1::CreateBarrier()
{
	extern BarrierManager* m_BarrierManager;
	m_BarrierManager->m_List.clear();
	m_BarrierManager->GetLayer(this);
	m_BarrierManager->GetSource(SourceManager::getInstance());
}

//������ ����
void Stage1_1::CreateItem()
{
	// ȹ�氡�� ������ �ڽ�
	extern ItemManager* m_ItemManager;
	m_ItemManager->m_List.clear();
	m_ItemManager->GetLayer(this);
}

//�� ���� 
void Stage1_1::CreateEnemy()
{
	extern EnemyManager* m_EnemyManager;
	m_EnemyManager->m_List.clear();
	m_EnemyManager->GetLayer(this);
	m_EnemyManager->GetSource(SourceManager::getInstance());
}

//��ֹ� ������Ʈ
void Stage1_1::UpdateBarrier()
{
	if (ObjectHero::getInstance()->m_Death == false)
	{
		extern BarrierManager* m_BarrierManager;
		m_BarrierManager->BarrierUpdate();
	}
}

// ������ ������Ʈ
void Stage1_1::CheckColide()
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

void Stage1_1::UpdateEnemy()
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

void Stage1_1::update(float dt)
{
	UpdateBack();//��� ����
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
			BackScene();
			return;
		}
	}
	if (m_Lock)
		pad->m_KeyLock = true;
	else if (m_Lock == false)
		pad->m_KeyLock = false;

	// ���ΰ� ������Ʈ
	if (ObjectHero::getInstance()->m_Death == false)
	{
		if (ObjectHero::getInstance()->m_HoldPos == false)
			pad->m_dir.clear();

		ObjectHero::getInstance()->MoveCharacter(pad->m_dir, dt);
		ObjectHero::getInstance()->HeroUpdate();

		ObjectHero::getInstance()->GetUILayer(pad->GetLayer());
		ObjectHero::getInstance()->InitHP();
		//m_UpdateFirst = true;
		if (m_UpdateFirst == false)
		{
			ObjectHero::getInstance()->SetHP(0);
			m_UpdateFirst = true;
		}
		m_CamControl->setViewPointCenter();
	}
	else
	{
		if (m_GameSwitch == false)
		{
			this->unscheduleUpdate();
			ObjectHero::getInstance()->AnimationSwitch(MotionNum::HeroDeath);
			RUN_WITH_DELAY(2.5f, CC_CALLBACK_0(Stage1_1::GameOver, this));
			m_GameSwitch = true;
			return;
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

void Stage1_1::GameOver()
{
	Scene* s = TransitionFade::create(2.0f, Stage1_1::createScene());
	Director::getInstance()->replaceScene(s);
}

void Stage1_1::BackScene()
{
	MemoryArrange();
	Scene* s = Stage1_2Loading::createScene();
	Director::getInstance()->replaceScene(s);
}

void Stage1_1::MemoryArrange()
{
	GameUI* pad = (GameUI*)this->getParent()->getChildByTag(100);
	pad->MemoryArrange();

	this->removeChild(m_tmap);
	this->stopAllActions();

	SourceManager::getInstance()->ClearBoxVector();
	SpriteFrameCache::getInstance()->removeSpriteFrames();
}

//��� �׸���
void Stage1_1::CreateBack()
{
	// �⺻ ���̽�
	backbase = Sprite::create("Stage1_1/Back/Base.png");
	backbase->setAnchorPoint(Vec2(0.0f, 0.0f));
	backbase->setPosition(Vec2(0, 0));
	this->addChild(backbase, -15);

	//// ���ϵ� ����
	back3 = Sprite::create("Stage1_1/Back/Back3.png");
	back3->setAnchorPoint(Vec2(0.0f, 0.0f));
	back3->setPosition(Vec2(0, 0));
	this->addChild(back3, -14);

	backTop1 = Sprite::create("Stage1_1/Back/BackTop1.png");
	backTop1->setAnchorPoint(Vec2(0.0f, 0.0f));
	backTop1->setPosition(Vec2(0, 0));
	this->addChild(backTop1, -13);

	backTop2 = Sprite::create("Stage1_1/Back/BackTop2.png");
	backTop2->setAnchorPoint(Vec2(0.0f, 0.0f));
	backTop2->setPosition(Vec2(0, 0));
	this->addChild(backTop2, -12);

	back1 = Sprite::create("Stage1_1/Back/Back1.png");
	back1->setAnchorPoint(Vec2(0.0f, 0.0f));
	back1->setPosition(Vec2(0, 0));
	this->addChild(back1, -11);

	back2 = Sprite::create("Stage1_1/Back/Back2.png");
	back2->setAnchorPoint(Vec2(0.0f, 0.0f));
	back2->setPosition(Vec2(0, 0));
	this->addChild(back2, -10);

	pil1 = Sprite::create("Stage1_1/Back/pillar1.png");
	pil1->setAnchorPoint(Vec2(0.0f, 0.0f));
	pil1->setPosition(Vec2(0, 0));
	this->addChild(pil1, -9);

	pil2 = Sprite::create("Stage1_1/Back/pillar2.png");
	pil2->setAnchorPoint(Vec2(0.0f, 0.0f));
	pil2->setPosition(Vec2(0, 0));
	this->addChild(pil2, -9);

	Top2 = Sprite::create("Stage1_1/Back/Top2.png");
	Top2->setAnchorPoint(Vec2(0.0f, 0.0f));
	Top2->setPosition(Vec2(0, 0));
	this->addChild(Top2, -8);

	Top1 = Sprite::create("Stage1_1/Back/Top1.png");
	Top1->setAnchorPoint(Vec2(0.0f, 0.0f));
	Top1->setPosition(Vec2(0, 0));
	this->addChild(Top1, -7);

	Front1 = Sprite::create("Stage1_1/Back/Front1.png");
	Front1->setAnchorPoint(Vec2(0.0f, 0.0f));
	Front1->setPosition(Vec2(0, 0));
	this->addChild(Front1, -6);

	Front2 = Sprite::create("Stage1_1/Back/Front2.png");
	Front2->setAnchorPoint(Vec2(0.0f, 0.0f));
	Front2->setPosition(Vec2(0, 0));
	this->addChild(Front2, -5);

	//��Ż �浹�ڽ�
	potalRect = Sprite::create("Tutorial/PotalRect.png");
	potalRect->setPosition(Vec2(7500, 630));
	potalRect->setVisible(true);
	this->addChild(potalRect, 9);
}

void Stage1_1::UpdateBack()
{
	Vec2 sample = ObjectHero::getInstance()->m_Spr->getPosition();
	Vec2 sample2 = sample;
	sample2.x -= 900;

	if (ObjectHero::getInstance()->m_Spr->getPositionX() > 900 && ObjectHero::getInstance()->m_Spr->getPositionX() < 9150)
	{
		back1->setPosition(Vec2(sample2.x*0.08f, 0));
		back2->setPosition(Vec2(sample2.x*0.11f, 0));
		back3->setPosition(Vec2(sample2.x*0.08f, 0));

		backTop1->setPosition(Vec2(sample2.x*0.035f, 0));
		backTop1->setPosition(Vec2(sample2.x*0.035f, 0));

		pil1->setPosition(Vec2(sample2.x*0.045f, 0));
		pil2->setPosition(Vec2(sample2.x*0.045f, 0));

		Top1->setPosition(Vec2(sample2.x*0.065f, 0));
		Top2->setPosition(Vec2(sample2.x*0.065f, 0));

		Front1->setPosition(Vec2(sample2.x*0.065f, 0));
		Front2->setPosition(Vec2(sample2.x*0.065f, 0));

	}
}