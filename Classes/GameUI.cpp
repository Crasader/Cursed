#include "Default.h"

bool GameUI::init()
{
	if (!Layer::init())
		return false;

	m_BossHP_Exit = false;
	m_Boss1HP_On = false;
	m_EliteHP_On = false;

	m_KeyLock = false;
	m_winSize = Director::getInstance()->getWinSize();
	m_KeyUp = false;
	m_WhiteNull = false;
	// UI
	m_TurnOnInfo = false;
	DrawUI();
	m_KeyClean = false;

	// 커서
	Sprite* mouse = Sprite::create("UI/Cursor2.png");
	mouse->setName("Mouse");
	mouse->setPosition(GetCursorPos());
	this->addChild(mouse, 20);
	m_dir.clear();

	m_Letter = Sprite::create("UI/LetterBox.png");
	m_Letter->setVisible(false);
	this->addChild(m_Letter, 25);

	// 터치 이벤트 등록
	m_TouchCheck = NULL;
	//auto listener = EventListenerTouchOneByOne::create(); // 싱글터치용


	//마우스이벤트 등록
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(GameUI::onMouseMove, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(GameUI::onMouseUp, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(GameUI::onMouseDown, this);
	_mouseListener->onMouseScroll = CC_CALLBACK_1(GameUI::onMouseScroll, this);
	Director::getInstance()->getOpenGLView()->setCursorVisible(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	return true;
}

void GameUI::InitStageScene()
{
	//DoRain();
	//DrawDir();
	//auto listener = EventListenerTouchAllAtOnce::create();// 멀티터치용 - touch->touches로 비긴,무브,앤드 함수 수정해야함
	//listener->onTouchesBegan = CC_CALLBACK_2(GameUI::onTouchesBegan, this);
	//listener->onTouchesMoved = CC_CALLBACK_2(GameUI::onTouchesMoved, this);
	//listener->onTouchesEnded = CC_CALLBACK_2(GameUI::onTouchesEnded, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	MakeKeyListener();
}

void GameUI::GameClear()
{
	auto lab = Label::createWithTTF("Game Clear", "fonts/Assassin$.ttf", 200);
	lab->setPosition(Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f));
	lab->runAction(Sequence::create(
		DelayTime::create(0.5f),FadeOut::create(0.5f),
		NULL));

	this->addChild(lab, 55);
}

Vec2 GameUI::GetCursorPos()
{
	return m_MousePos;
}

void GameUI::DoRain()
{
	/*extern ObjectHero* Hero;
	auto particle = ParticleSystemQuad::create("test.plist");
	particle->setPosition(Vec2(1000, 900));
	this->addChild(particle,10);*/

	ParticleSystem* rain = ParticleRain::create();
	rain->retain();
	
	Vec2 p = rain->getPosition();
	rain->setPosition(Vec2(p.x, p.y));
	rain->setLife(8);

	auto texture = Director::getInstance()->getTextureCache()->addImage("particle.png");
	rain->setTexture(texture);
	rain->setScale(1.3f);
	rain->setScaleY(5);

	if (rain != NULL)
	{
		rain->setPosition(Vec2(960, 1100));
		this->addChild(rain, 7);
	}
}

void GameUI::UpdateHP()
{
	int num = ObjectHero::getInstance()->m_HP / 10;
	switch (num)
	{
	case 6:
		m_Health[0]->setTexture(m_HPtexture[3]->getTexture());
		break;
	case 5:
		m_Health[0]->setTexture(m_HPtexture[3]->getTexture());
		break;
	case 4:
		m_Health[0]->setTexture(m_HPtexture[2]->getTexture());
		break;
	case 3:
		m_Health[0]->setTexture(m_HPtexture[2]->getTexture());
		break;
	case 2:
		m_Health[0]->setTexture(m_HPtexture[1]->getTexture());
		break;
	case 1:
		m_Health[0]->setTexture(m_HPtexture[1]->getTexture());
		break;
	case 0:
		m_Health[0]->setTexture(m_HPtexture[0]->getTexture());
		break;
	}
	if (num > 6)
	{
		m_Health[0]->setTexture(m_HPtexture[3]->getTexture());
	}
}

void GameUI::ChangeWeapon()
{
	if (ObjectHero::getInstance()->m_AniNum == 8)
		m_WeaponSwap[0]->setTexture(m_WeaponSwap[1]->getTexture());
	else
		m_WeaponSwap[0]->setTexture(m_WeaponSwap[2]->getTexture());
	CSoundManager::getInstance()->playEffect("Sound/Sound/Swap.mp3", false, 1.0f);
}

void GameUI::DrawUI()
{
	/*auto InfoBack = Sprite::create("UI/Info/InfoBack.png");
	InfoBack->setName("InfoBack");
	InfoBack->setPosition(Vec2(m_winSize.width*0.5f, m_winSize.height*0.5f));
	InfoBack->setVisible(false);
	this->addChild(InfoBack, 30);*/

	// HP
	for (int i = 0; i < 1; ++i)
	{
		m_HPback[i] = i == 0 ? Sprite::create("UI/Health/HPback.png") : Sprite::createWithSpriteFrame(m_HPback[0]->getSpriteFrame());
		m_HPback[i]->setPosition(Vec2(m_winSize.width*0.1f + i * 250, m_winSize.height*0.8f + 100));
		this->addChild(m_HPback[i], 20);

		m_Health[i] = i == 0 ? Sprite::create("UI/Health/HP3.png") : Sprite::createWithSpriteFrame(m_Health[0]->getSpriteFrame());
		m_Health[i]->setPosition(Vec2(m_HPback[i]->getPositionX() - 20, m_HPback[i]->getPositionY() + 60));
		this->addChild(m_Health[i], 21);
	}

	m_HPtexture[0] = Sprite::create("UI/Health/HP0.png");
	m_HPtexture[0]->setVisible(false);
	m_HPtexture[0]->setPosition(Vec2(-500, -500));
	this->addChild(m_HPtexture[0]);

	m_HPtexture[1] = Sprite::create("UI/Health/HP1.png");
	m_HPtexture[1]->setVisible(false);
	m_HPtexture[1]->setPosition(Vec2(-500, -500));
	this->addChild(m_HPtexture[1]);

	m_HPtexture[2] = Sprite::create("UI/Health/HP2.png");
	m_HPtexture[2]->setVisible(false);
	m_HPtexture[2]->setPosition(Vec2(-500, -500));
	this->addChild(m_HPtexture[2]);

	m_HPtexture[3] = Sprite::create("UI/Health/HP3.png");
	m_HPtexture[3]->setVisible(false);
	m_HPtexture[3]->setPosition(Vec2(-500, -500));
	this->addChild(m_HPtexture[3]);

	// 무기교체
	m_WeaponSwap[0] = Sprite::create("UI/Health/Sword.png");
	m_WeaponSwap[0]->setPosition(Vec2(m_Health[0]->getPositionX() - 10, m_Health[0]->getPositionY() - 80));
	this->addChild(m_WeaponSwap[0], 22);

	m_WeaponSwap[1] = Sprite::create("UI/Health/Bow.png");
	m_WeaponSwap[1]->setVisible(false);
	m_WeaponSwap[1]->setPosition(Vec2(-500, -500));
	this->addChild(m_WeaponSwap[1]);

	m_WeaponSwap[2] = Sprite::create("UI/Health/Sword.png");
	m_WeaponSwap[2]->setVisible(false);
	m_WeaponSwap[2]->setPosition(Vec2(-500, -500));
	this->addChild(m_WeaponSwap[2]);

	/*m_WeaponSwap[3] = Sprite::create("UI/Health/Skill.png");
	m_WeaponSwap[3]->setPosition(Vec2(m_Health[1]->getPositionX() - 10, m_Health[1]->getPositionY() - 80));
	this->addChild(m_WeaponSwap[3],22);*/

	//게이지틀
	//m_SkillGageBar = Sprite::create("UI/GageBar/SkillBar.png");
	//m_SkillGageBar->setPosition(Vec2(m_winSize.width*0.5f-500, m_winSize.height*0.5f + 450));
	//m_SkillGageBar->setOpacity(0);
	//this->addChild(m_SkillGageBar, 15);

	////눈깔
	//m_Eye = Sprite::create("UI/GageBar/eye1.png");
	//m_Eye->setPosition(Vec2(m_winSize.width*0.5f - 866, m_winSize.height*0.5f + 450));
	//m_Eye->setOpacity(0);
	//this->addChild(m_Eye, 16);

	////게이지바
	//m_Bar = Sprite::create("UI/GageBar/Bar.png");
	//m_Bar->setPosition(Vec2(m_winSize.width*0.5f - 457, m_winSize.height*0.5f + 450));
	//m_Bar->runAction(FadeOut::create(0.0f));
	//m_Bar->setOpacity(0);
	//this->addChild(m_Bar, 14);

	//m_EyeAni = Animation::create();
	//m_EyeAni->setDelayPerUnit(0.05f);
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye6.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye5.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye4.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye3.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye2.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye1.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye2.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye3.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye4.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye5.png");
	//m_EyeAni->addSpriteFrameWithFileName("UI/GageBar/eye6.png");

	//m_Eye->runAction(RepeatForever::create(
	//	Sequence::create(
	//		Animate::create(m_EyeAni), DelayTime::create(2.5f), 
	//		Animate::create(m_EyeAni),Animate::create(m_EyeAni),
	//		DelayTime::create(4.5f),
	//		NULL
	//	)));

	//메뉴목록
	{
		//시작
		MenuItemSprite* Info = MenuItemSprite::create(Sprite::create("UI/Info/InfoButton.png"), Sprite::create("UI/Info/InfoButton.png"), Sprite::create("UI/Info/InfoButton.png"), this, menu_selector(GameUI::DrawInfo));
		Info->setPosition(Vec2(-310, 270));

		MenuItemSprite* Info2 = MenuItemSprite::create(Sprite::create("UI/Info/SkillButton.png"), Sprite::create("UI/Info/SkillButton.png"), Sprite::create("UI/Info/SkillButton.png"), this, menu_selector(GameUI::DrawSkill));
		Info2->setPosition(Vec2(-160, 270));

		auto storeKindMenu = Menu::create(Info, Info2, NULL);
		storeKindMenu->setVisible(false);
		storeKindMenu->setName("UIInfo");
		this->addChild(storeKindMenu, 9);
	}
	//// Info
	/*for (int i = 0; i < 3; ++i)
	{
		if (m_ShieldSlot[i] == NULL)
		{
			m_ShieldSlot[i] = Sprite::create("UI/Info/ItemSlot.png");
			m_ShieldSlot[i]->setPosition(Vec2(760 + i * 120, 640));
			m_ShieldSlot[i]->setVisible(false);
			this->addChild(m_ShieldSlot[i], 10);

			m_Shield[i] = Sprite::create("UI/Info/ItemSlot.png");
			m_Shield[i]->setPosition(Vec2(760 + i * 120, 640));
			m_Shield[i]->setVisible(false);
			this->addChild(m_Shield[i], 10);
		}
	}*/
	//// Skill

}

void GameUI::DrawInfo(Object* pSender)
{
	if (m_TurnOnInfo)
	{
		// 스킬창 off
		
	}
}

void GameUI::DrawSkill(Object* pSender)
{
	if (m_TurnOnInfo)
	{
		// 정보창 off
		/*for (int i = 0; i < 3; ++i)
		{
			m_ShieldSlot[i]->setVisible(false);
			m_Shield[i]->setVisible(false);
		}*/

		// 스킬창 On
		m_WeaponSlot->setVisible(true);
		extern WeaponManager* m_WeaponManager;
		if (m_WeaponManager->m_WeaponNum == BasicWeapon)
		{
			m_Weapon->setTexture(m_WeaponManager->CloseWeapon->getTexture());
		}
		else if (m_WeaponManager->m_WeaponNum == Item::Bat)
		{
			m_Weapon->setTexture(m_WeaponManager->CloseWeapon->getTexture());
		}
		else if (m_WeaponManager->m_WeaponNum == Item::Gun)
		{
			m_Weapon->setTexture(m_WeaponManager->CloseWeapon->getTexture());
		}
		m_Weapon->setVisible(true);

		char str[100] = { 0 };
		for (int i = 0; i < 3; ++i)
		{
			if (ObjectHero::getInstance()->m_Skill[i])
			{
				sprintf(str, "UI/Info/SkillRock%d_1.png", i);
				m_Scroll[i]->initWithFile(str);
				m_Scroll[i]->setVisible(true);
			}
			else if (ObjectHero::getInstance()->m_Skill[i] == false)
			{
				sprintf(str, "UI/Info/SkillRock0_2.png", i);
				m_Scroll[i]->initWithFile(str);
				m_Scroll[i]->setVisible(true);
			}
		}
	}
}

void GameUI::SetUIVisible(bool On)
{
	if (On)
	{
		m_TurnOnInfo = true;
		/*auto InfoBack = dynamic_cast<Sprite*>(this->getChildByName("InfoBack"));
		InfoBack->setVisible(On);
		auto Info1 = dynamic_cast<Menu*>(this->getChildByName("UIInfo"));
		Info1->setVisible(On);*/
	}
	else
	{
		/*for (int i = 0; i < 3; ++i)
		{
			m_ShieldSlot[i]->setVisible(false);
			m_Shield[i]->setVisible(false);
			m_Scroll[i]->setVisible(false);
		}*/
		m_WeaponSlot->setVisible(false);
		m_Weapon->setVisible(false);

		m_TurnOnInfo = false;
		auto InfoBack = dynamic_cast<Sprite*>(this->getChildByName("InfoBack"));
		InfoBack->setVisible(On);
		auto Info1 = dynamic_cast<Menu*>(this->getChildByName("UIInfo"));
		Info1->setVisible(On);
	}
}

void GameUI::UISetposition()
{
	Vec2 pos = Camera::getDefaultCamera()->getPosition();
	pos.x -= m_winSize.width*0.5f;
	pos.y -= m_winSize.height*0.5f;
	this->setPosition(pos);
}

void GameUI::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	
}

void GameUI::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{

}

void GameUI::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	m_dir.clear();
	m_TouchCheck = false;
	m_TouchPos.x = NULL;
	m_TouchPos.y = NULL;
}

void GameUI::MakeKeyListener()
{
	//키보드 리스너
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameUI::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameUI::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void GameUI::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	extern Timer2* m_Timer2;
	static float dashTime;
	static bool IfDash;
	std::vector<int>::const_iterator iter = m_dir.begin();

	if (m_KeyLock)
	{
		m_dir.clear();
		return;
	}
	//if (m_KeyLock)
	//{
	//	//ObjectHero::getInstance()->AnimationSwitch(MotionNum::Stand);
	//	m_dir.clear();
	//	return;
	//}
	// 애니 테스트
	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
	{
		m_dir.clear();
		ObjectHero::getInstance()->m_Spr->stopAllActions();
		ObjectHero::getInstance()->BugFix();
	}

	// 상호작용 키 X
	if (keyCode == EventKeyboard::KeyCode::KEY_X)
	{
		ObjectHero::getInstance()->m_Interact = true;
	}

	// 스킬 - 상태 확인
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
	{
		m_KeyClean = true;
		if (m_TurnOnInfo == false)
		{
			SetUIVisible(true);
			DrawInfo(NULL);
		}
		else
			SetUIVisible(false);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_KeyUp = true;
		m_KeyClean = true;
		m_KeySave = PadDir::UpMove;
		m_dir.push_back(PadDir::UpMove);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_KeyClean = true;
		m_KeySave = PadDir::DownMove;
		m_dir.push_back(PadDir::DownMove);
	}

	if (m_Timer2->GetTime() - dashTime > 2.5f)
		IfDash = false;
	//왼쪽 이동 및 대쉬
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_dir.clear();
		m_KeyClean = true;
		if (IfDash == false && ObjectHero::getInstance()->CanJump == false && !ObjectHero::getInstance()->m_SetLadder && m_KeySave == PadDir::LeftMove && m_Timer2->GetTime() - dashTime < 0.3f
			&&  ObjectHero::getInstance()->m_CurMotionNum != MotionNum::Attack)
		{
			m_dir.push_back(PadDir::LeftDash);
			dashTime = m_Timer2->GetTime();
			IfDash = true;
			return;
		}
		if (IfDash == false)
			dashTime = m_Timer2->GetTime();
		m_KeySave = PadDir::LeftMove;
		m_dir.push_back(PadDir::LeftMove);
	}
	//오른쪽 이동 및 대쉬
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_dir.clear();
		m_KeyClean = true;
		if (IfDash == false && ObjectHero::getInstance()->CanJump == false && !ObjectHero::getInstance()->m_SetLadder && m_KeySave == PadDir::RightMove && m_Timer2->GetTime() - dashTime < 0.3f
			&&  ObjectHero::getInstance()->m_CurMotionNum != MotionNum::Attack)
		{
			m_dir.push_back(PadDir::RightDash);
			dashTime = m_Timer2->GetTime();
			IfDash = true;
			return;
		}
		if (IfDash == false)
			dashTime = m_Timer2->GetTime();
		m_KeySave = PadDir::RightMove;
		m_dir.push_back(PadDir::RightMove);
	}

	// 점프
	if (keyCode == EventKeyboard::KeyCode::KEY_ALT)
	{
		//if (Hero->m_SetLadder == false)
		{
			m_KeyClean = true;
			m_KeySave = PadDir::JUMP;
			m_dir.push_back(PadDir::JUMP);
		}
	}
	// 기본공격
	if (keyCode == EventKeyboard::KeyCode::KEY_CTRL)
	{
		m_dir.clear();
		m_KeyClean = true;
		m_KeySave = PadDir::Att;
		m_dir.push_back(PadDir::Att);
		//if (m_Timer2->GetTime() - dashTime > 0.3f)
		//{
		//	//m_dir.clear();
		//	m_KeyClean = true;
		//	m_KeySave = PadDir::Att;
		//	m_dir.push_back(PadDir::Att);
		//}
	}
	// 스킬1
	if (keyCode == EventKeyboard::KeyCode::KEY_SHIFT)
	{
		m_KeyClean = true;
		m_KeySave = PadDir::Skill1;
		extern WeaponManager* m_WeaponManager;
		extern ShieldManager* m_ShieldManager;
		if (ObjectHero::getInstance()->m_AniNum == 0 && ObjectHero::getInstance()->m_CurMotionNum == MotionNum::Stand)
		{
			ObjectHero::getInstance()->m_AniNum = 8;
			ObjectHero::getInstance()->SettingItem(Item::Gun);
			m_WeaponManager->CloseWeapon->setVisible(false);
			ChangeWeapon();
		}
		else if (ObjectHero::getInstance()->m_AniNum == 8 && ObjectHero::getInstance()->m_CurMotionNum == MotionNum::Stand)
		{
			ObjectHero::getInstance()->m_AniNum = 0;
			ObjectHero::getInstance()->SettingItem(BasicWeapon);
			m_WeaponManager->CloseWeapon->setVisible(true);
			ChangeWeapon();
		}
	}
	// 아이템 줍기
	if (keyCode == EventKeyboard::KeyCode::KEY_Z)
	{
		m_KeyClean = true;
		ObjectHero::getInstance()->m_GetOn = true;
	}
}

void GameUI::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (m_KeyLock)
	{
		return;
	}

	std::vector<int>::const_iterator iter = m_dir.begin();

	//if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		//m_KeyUp = false;

	// 상호작용 키 X
	if (keyCode == EventKeyboard::KeyCode::KEY_X)
	{
		ObjectHero::getInstance()->m_Interact = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::DownMove)
			{
				m_dir.erase(iter);
				return;
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		m_KeyUp = false;
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::UpMove)
			{
				m_dir.erase(iter);
				return;
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::LeftMove)
			{
				m_dir.erase(iter);
				return;
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::RightMove)
			{
				m_dir.erase(iter);
				return;
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_ALT)
	{
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::JUMP)
			{
				m_dir.erase(iter);
				return;
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_CTRL)
	{
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::Att)
			{
				m_dir.erase(iter);
				return;
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_SHIFT)
	{
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::Skill1)
			{
				m_dir.erase(iter);
				return;
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_Z)
	{
		ObjectHero::getInstance()->m_GetOn = false;
		return;
	}

	if (m_KeyClean == false)
		m_dir.clear();
}


void GameUI::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	e->getCursorX();
}

void GameUI::onMouseUp(Event *event)
{

}

void GameUI::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	m_MousePos.x = e->getCursorX();
	m_MousePos.y = e->getCursorY();
}

void GameUI::onMouseScroll(Event *event)
{
}

void GameUI::UIupdate()
{
	//마우스 위치 세팅
	auto mouse = dynamic_cast<Sprite*>(this->getChildByName("Mouse"));
	mouse->setPosition(GetCursorPos());
	std::vector<int>::const_iterator iter = m_dir.begin();

	// 좌우 카메라 확대를 위한 위치 고정확인
	if (ObjectHero::getInstance()->m_CheckPos == ObjectHero::getInstance()->m_Rect->getPosition())
		ObjectHero::getInstance()->m_NoChangePos = true;
	else
		ObjectHero::getInstance()->m_NoChangePos = false;
	ObjectHero::getInstance()->m_CheckPos = ObjectHero::getInstance()->m_Rect->getPosition();

	// 주인공 대쉬체크
	if (ObjectHero::getInstance()->m_HeroDash)
	{
		for (iter; iter != m_dir.end(); ++iter)
		{
			if (*iter == PadDir::LeftDash)
			{
				m_dir.erase(iter);
				m_dir.push_back(PadDir::LeftMove);
				return;
			}
			else if (*iter == PadDir::RightDash)
			{
				m_dir.erase(iter);
				m_dir.push_back(PadDir::RightMove);
				return;
			}
		}
	}
}

void GameUI::SetLetter()
{
	if (m_Letter->isVisible() == false)
	{
		m_Letter->setPosition(Vec2(m_winSize.width*0.5f, 1200));
		m_Letter->setVisible(true);
		m_Letter->runAction(MoveTo::create(1.0f, Vec2(m_winSize.width*0.5f, 1080)));
	}
	else
	{
		m_Letter->runAction(Sequence::create(
			MoveTo::create(2.0f, Vec2(m_winSize.width*0.5f, 1500)),
			Hide::create(),NULL));
	}
}

void GameUI::DirClear()
{
	Sprite* foraction = Sprite::create();
	foraction->runAction(Sequence::create(
		DelayTime::create(0.1f),
		CallFunc::create(CC_CALLBACK_0(GameUI::KeyClear, this)), NULL));
	this->addChild(foraction);
}

Layer * GameUI::GetLayer()
{
	return this;
}

void GameUI::MemoryArrange()
{
	this->stopAllActions();
}

void GameUI::EliteHPCreate(float HP)
{
	m_EliteHP_On = true;
	m_MaxHP = HP;

	m_EliteHPBack = Sprite::create("UI/EliteBack.png");
	m_EliteHPBack->setAnchorPoint(Vec2(0, 0));
	m_EliteHPBack->setPosition(Vec2(520, 800));
	this->addChild(m_EliteHPBack, 3);

	m_EliteHPBar = Sprite::create("UI/EliteBar.png");
	m_EliteHPBar->setAnchorPoint(Vec2(0, 0));
	m_EliteHPBar->setPosition(Vec2(520, 800));
	this->addChild(m_EliteHPBar, 2);
}

void GameUI::EliteHPUpdate(float CurHP)
{
	Rect BarRect = m_EliteHPBack->getTextureRect();
	float per = CurHP / m_MaxHP;
	per = 1000 * per;
	BarRect.size.width = per;
	m_EliteHPBar->setTextureRect(BarRect);

	if (CurHP <= 0)
	{
		m_EliteHP_On = false;
		m_EliteHPBack->runAction(Sequence::create(
			FadeOut::create(1.5f), RemoveSelf::create(), NULL));
		m_EliteHPBar->removeFromParent();
	}
}

void GameUI::Boss1HPCreate(float HP)
{
	m_Boss1HP_On = true;
	m_MaxHP = HP;
	
	m_Boss1HPBack = Sprite::create("UI/BossHPBack.png");
	m_Boss1HPBack->setAnchorPoint(Vec2(0, 0));
	m_Boss1HPBack->setPosition(Vec2(520, 950));
	this->addChild(m_Boss1HPBack, 3);

	m_Boss1HPBar = Sprite::create("UI/BossHPBar.png");
	m_Boss1HPBar->setAnchorPoint(Vec2(0, 0));
	m_Boss1HPBar->setPosition(Vec2(520, 950));
	this->addChild(m_Boss1HPBar, 2);
}

void GameUI::Boss1HPUpdate(float CurHP)
{
	Rect BarRect = m_Boss1HPBack->getTextureRect();
	float per = CurHP / m_MaxHP;
	per = 935 * per;
	BarRect.size.width = per;
	m_Boss1HPBar->setTextureRect(BarRect);

	if (CurHP <= 0)
	{
		m_Boss1HP_On = false;
		m_Boss1HPBack->runAction(Sequence::create(
			FadeOut::create(1.5f), RemoveSelf::create(), NULL));
		m_Boss1HPBar->removeFromParent();
	}
}

void GameUI::BossHPCreate(float HP)
{
	m_BossHP_Exit = true;
	m_MaxHP = HP;
	m_NumHP = HP;
	m_BossHPBack = Sprite::create("UI/Boss2Back.png");
	m_BossHPBack->setAnchorPoint(Vec2(0, 0));
	m_BossHPBack->setPosition(Vec2(420, 950));
	this->addChild(m_BossHPBack, 3);

	m_BossHPBar = Sprite::create("UI/Boss2Bar.png");
	m_BossHPBar->setAnchorPoint(Vec2(0, 0));
	m_BossHPBar->setPosition(Vec2(420, 950));
	this->addChild(m_BossHPBar, 2);
}

void GameUI::BossHPUpdate(float CurHP)
{
	Rect BarRect = m_BossHPBack->getTextureRect();
	float per = CurHP / m_MaxHP;
	per = 1250 * per;
	BarRect.size.width = per;
	m_BossHPBar->setTextureRect(BarRect);
	
	if (CurHP <= 0)
	{
		m_BossHP_Exit = false;
		m_BossHPBack->runAction(FadeOut::create(1.5f));
	}
}

void GameUI::CreateWhite()
{
	Sprite* white2 = Sprite::create("UI/White.png");
	white2->setPosition(Vec2(960, 540));
	white2->setOpacity(0);
	this->addChild(white2, 15);

	white2->runAction(Sequence::create(DelayTime::create(2.0f),
		FadeIn::create(1.0f), CallFunc::create(CC_CALLBACK_0(GameUI::BeepSound, this)),FadeOut::create(1.0f), FadeIn::create(1.0f), CallFunc::create(CC_CALLBACK_0(GameUI::BeepSound, this)),
		FadeOut::create(1.0f),FadeIn::create(1.0f), CallFunc::create(CC_CALLBACK_0(GameUI::BeepSound, this)),
		CallFunc::create(CC_CALLBACK_0(GameUI::EndEvent1,this)),
		NULL));

	m_Health[0]->setVisible(false);
	m_HPback[0]->setVisible(false);
	m_Health[0]->setVisible(false);
	m_WeaponSwap[0]->setVisible(false);
}

void GameUI::EndEvent1()
{
	Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 100);
	HeroChat1->setPosition(Vec2(960, 540));
	HeroChat1->setVisible(true);
	this->addChild(HeroChat1, 17);
	LabelTypingEffect::typeMessage(HeroChat1, "기다려.. 내가 지금 구하러 갈께", 0.1f, Color3B::BLACK);
	HeroChat1->runAction(Sequence::create(DelayTime::create(3.0f), Hide::create(), RemoveSelf::create(), NULL));

	RUN_WITH_DELAY(3.5f, CC_CALLBACK_0(GameUI::EndEvent2, this));
}

void GameUI::EndEvent2()
{
	Label* HeroChat1 = Label::createWithTTF("", "fonts/210 아몬드R.ttf", 120);
	HeroChat1->setPosition(Vec2(960, 540));
	HeroChat1->setVisible(true);
	this->addChild(HeroChat1, 17);
	LabelTypingEffect::typeMessage(HeroChat1, "Chapter1  END", 0.1f, Color3B::BLACK);
	HeroChat1->runAction(Sequence::create(DelayTime::create(3.0f),  NULL));
}
void GameUI::SetMask()
{
	m_Mask = Sprite::create("Stage2_3/Alpha_Mask.png");
	m_Mask->setPosition(Vec2(960, 540));
	this->addChild(m_Mask, 16);
}

void GameUI::Makethunder()
{
	int num = random(1, 2);
	if(num == 1)
		CSoundManager::getInstance()->playEffect("Sound/thunder2.mp3", false, 1.0f);
	else
		CSoundManager::getInstance()->playEffect("Sound/thunder1.mp3", false, 1.0f);

	if (m_WhiteNull == false)
	{
		m_WhiteNull = true;
		white = Sprite::create("UI/White.png");
		white->setPosition(Vec2(960, 540));
		white->setOpacity(0);
		this->addChild(white, 15);
	}
	white->runAction(Sequence::create(
		FadeIn::create(0.15f),FadeOut::create(0.15f), NULL));

	//white = Sprite::create("")
}