#include "Default.h"

ObjectHero::ObjectHero()
{}

ObjectHero::~ObjectHero()
{}

bool ObjectHero::CreateObject(float x, float y)
{
	static bool once = false;
	if (once == false)
	{
		m_BossBullet = false;
		m_UpdateLock = false;
		m_OnGround = false;
		m_TargetIn = false;
		m_EliteClear = false;
		once = true;
		MotionSwap = false;
		DashCheck = false;
		m_NoChangePos = false;
		m_LadderEnd = true;
		m_JumpTime = 0;
		m_Energy = 3000;
		m_SavePos.x = -500;
		m_SavePos.y = -500;
		m_GroundPos.x = 0;
		m_GroundPos.y = 0;
		m_accel = 0;

		//�뽬 �浹�ڽ�
		m_DashRect = Sprite::create("Hero/DashRect.png");
		m_DashRect->setPosition(Vec2(x, y));
		m_DashRect->setVisible(ColiideRect);
		//m_layer->addChild(m_DashRect, 8);
		CC_SAFE_RETAIN(m_DashRect);

		//���� ���ΰ� �浹�ڽ�
		m_Rect = Sprite::create("Hero/HeroRect2.png");
		m_Rect->setPosition(Vec2(x, y));
		m_Rect->setVisible(ColiideRect);
		m_Rect->setScaleX(0.9f);
		//m_layer->addChild(m_Rect, 7);
		CC_SAFE_RETAIN(m_Rect);

		//��Ʈ ��� üũ�ڽ�
		m_HitRect = Sprite::createWithSpriteFrame(m_Rect->getSpriteFrame());
		m_HitRect->setPosition(Vec2(x, y));
		m_HitRect->setScaleX(2.0f);
		m_HitRect->setVisible(ColiideRect);
		m_HitRect->setOpacity(50);
		CC_SAFE_RETAIN(m_HitRect);

		//��� Ȱ
		m_Bow = Sprite::create("Hero/Bow2.png");
		m_Bow->setPosition(Vec2(x, y));
		m_Bow->setVisible(true);
		CC_SAFE_RETAIN(m_Bow);

		m_CheckPos = m_Rect->getPosition();

		for (int i = 0; i < 10; ++i)
			m_SoundEnd[i] = false;
		// ��ų �ʱ�ȭ
		for (int i = 0; i < 3; ++i)
			m_Skill[i] = false;

		//�� ����
		for (int i = 0; i < 3; ++i)
		{
			m_Shield[i] = false;
			m_Hard[i] = 0;
		}

		//���ΰ� ĳ����
		m_Spr = Sprite::create("Hero/HeroIdle/idle1.png");
		m_Spr->setPosition(Vec2(x, y));
		m_Spr->setVisible(true);
		CC_SAFE_RETAIN(m_Spr);

		//���� (��,����� ���� �浹�ڽ�)
		m_ItemRect = Sprite::create("Hero/HeroNoWeapon.png");
		m_ItemRect->setPosition(Vec2(x + 100, y));
		m_ItemRect->setVisible(ColiideRect);
		CC_SAFE_RETAIN(m_ItemRect);

		JumpPower = PhysicNum::JumpPower;

		m_BossSkill1 = false;
		m_Interact = false;
		m_GetOn = false;
		CanJump = false;
		m_HeroDash = false;
		m_FirstGround = false;
		m_WeaponHave = false;
		m_SetLadder = false;
		m_HeroHit = false;
		m_FrameCheck = false;

		for (int i = 0; i < 3; ++i)
			m_AttackEnd[i] = true;
		JumpCount = 0;
		m_Timer = 0;
		m_ATimer = 0;
		m_CurMotionNum = 0;
		m_AniNum = 0;//�⺻����(����)
		m_HP = 3060;//HP
		m_damage = 10;
		m_HoldPos = false;
		m_Death = false;
		State = 0;
		for (int i = 0; i < 3; ++i)
			AttackNum[i] = NULL;
		m_ItemChange = false;

		//�ִϸ��̼�
		char str[100] = { 0 };
		///// ������
		Death = Animation::create();
		Death->setDelayPerUnit(DeathDelay);
		for (int i = 1; i <= 11; i++)// ������
		{
			sprintf(str, "Hero/HeroDeath/Death%d.png", i);
			Death->addSpriteFrameWithFileName(str);
		}
		//////////// �⺻ ĳ����
		for (int i = 0; i < HeroEffectNum; i++)
		{
			effect[i] = Animation::create();
			if (i == 0)//�޸���
				effect[i]->setDelayPerUnit(RunDelay);
			else if (i == 1 || i == 18)//����
				effect[i]->setDelayPerUnit(BasicAttackDelay);
			else if (i == 2)// ���ֱ�
				effect[i]->setDelayPerUnit(IdleDelay);
			else if (i == 3)//����
				effect[i]->setDelayPerUnit(JumpDelay);
			else if (i == 13 || i == 17)//��ٸ�
				effect[i]->setDelayPerUnit(LadderDelay);
			else if (i == 15)//�ȱ�
				effect[i]->setDelayPerUnit(WalkDelay);
			else if (i == 14)//�߶�
				effect[i]->setDelayPerUnit(FallDelay);
			else if (i == 16)//�뽬
				effect[i]->setDelayPerUnit(DashDelay);
			else if (i == 19 || i == 20)//��ٸ� ���� ���
				effect[i]->setDelayPerUnit(LadderEndDelay);
			else if (i == 5) // Ȱ����
				effect[i]->setDelayPerUnit(BowAtkDelay);
			else if(i == 21)
				effect[i]->setDelayPerUnit(0.05f);
		}
		for (int i = 1; i <= 16; i++)// �޸���
		{
			sprintf(str, "Hero/HeroRun/Run/run (%d).png", i);
			if (i == 2)
			{
				Sprite* forsave = Sprite::create();
				forsave->initWithFile(str);
				effect[0]->addSpriteFrame(forsave->getSpriteFrame());
				m_SoundNum[1] = forsave->getSpriteFrame()->getTexture()->getName();
			}
			else if (i == 10)
			{
				Sprite* forsave = Sprite::create();
				forsave->initWithFile(str);
				effect[0]->addSpriteFrame(forsave->getSpriteFrame());
				m_SoundNum[2] = forsave->getSpriteFrame()->getTexture()->getName();
			}
			else
				effect[0]->addSpriteFrameWithFileName(str);
		}

		for (int i = 1; i <= 3; i++)// �ȱ� 
		{
			sprintf(str, "Hero/HeroRun/Run%d.png", i);
			effect[15]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 7; i++)// ���� 1Ÿ
		{
			sprintf(str, "Hero/HeroAttack/Attack1_%d.png", i);
			effect[1]->addSpriteFrameWithFileName(str);
		}
		effect[1]->setRestoreOriginalFrame(true);//�ִϸ��̼� ����� ���� ��������Ʈ�� ����
		for (int i = 1; i <= 7; i++)// ���� 2Ÿ
		{
			sprintf(str, "Hero/HeroAttack/Attack2_%d.png", i);
			if (i == 3)
			{
				Sprite* forsave = Sprite::create();
				forsave->initWithFile(str);
				effect[18]->addSpriteFrame(forsave->getSpriteFrame());
				m_SoundNum[0] = forsave->getSpriteFrame()->getTexture()->getName();
			}
			else
				effect[18]->addSpriteFrameWithFileName(str);
		}
		effect[18]->setRestoreOriginalFrame(true);//�ִϸ��̼� ����� ���� ��������Ʈ�� ����
		for (int i = 1; i <= 25; i++)// ���ֱ�
		{
			sprintf(str, "Hero/HeroIdle/idle%d.png", i);
			effect[2]->addSpriteFrameWithFileName(str);
		}
		effect[2]->setRestoreOriginalFrame(true);//�ִϸ��̼� ����� ���� ��������Ʈ�� ����
		for (int i = 1; i <= 14; i++)// ����
		{
			sprintf(str, "Hero/HeroJump/Jump%d.png", i);
			effect[3]->addSpriteFrameWithFileName(str);
		}
		//for (int i = 1; i < 2; i++)// �˹�
		//{
		//	sprintf(str, "Hero/HeroHit1.png", i);
		//	effect[12]->addSpriteFrameWithFileName(str);
		//}
		//effect[12]->setRestoreOriginalFrame(true);//�ִϸ��̼� ����� ���� ��������Ʈ�� ����
		for (int i = 1; i <= 5; i++)// ��ٸ�1
		{
			sprintf(str, "Hero/HeroLadder/Tick1/Ladder%d.png", i);
			effect[13]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 5; i++)// ��ٸ�2
		{
			sprintf(str, "Hero/HeroLadder/Tick2/Ladder%d.png", i);
			effect[17]->addSpriteFrameWithFileName(str);
		}
		for (int i = 1; i <= 9; i++)// ��ٸ� ���� ��� ��
		{
			sprintf(str, "Hero/climb_fixed/climb%d.png", i);
			effect[19]->addSpriteFrameWithFileName(str);
		}
		for (int i = 9; i != 1; i--)// ��ٸ� ���� ��� �ٿ�
		{
			sprintf(str, "Hero/climb/climb%d.png", i);
			effect[20]->addSpriteFrameWithFileName(str);
		}
		for (int i = 8; i <= 14; i++)// �߶�
		{
			sprintf(str, "Hero/HeroJump/Jump%d.png", i);
			effect[14]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i <= 4; i++)// �뽬
		{
			sprintf(str, "Hero/HeroDash/dash_0%d.png", i);
			effect[16]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i <= 4; i++)// Hit
		{
			sprintf(str, "Hero/HeroHit.png", i);
			effect[21]->addSpriteFrameWithFileName(str);
		}
		/////////// ���Ÿ� ���ݸ��
		for (int i = 1; i <= 24; i++)// ����
		{
			sprintf(str, "Hero/bow/bowAttack%d.png", i);
			if (i == 15)
			{
				Sprite* forsave = Sprite::create();
				forsave->initWithFile(str);
				effect[5]->addSpriteFrame(forsave->getSpriteFrame());
				m_BowAtk = forsave->getSpriteFrame()->getTexture()->getName();
			}
			else
				effect[5]->addSpriteFrameWithFileName(str);
		}
		effect[5]->setRestoreOriginalFrame(true);//�ִϸ��̼� ����� ���� ��������Ʈ�� ����
												 //������ �޸����� -> addchild �� �������� ������ ������� ����

		CC_SAFE_RETAIN(Death);
		for (int i = 0; i < HeroEffectNum; i++)
			CC_SAFE_RETAIN(effect[i]);

		return true;
	}
	else
	{
		if (m_layer != NULL)
		{
			m_HoldPos = false;
			m_RebornPos = Vec2(x, y);
			m_Rect->setFlipX(true);
			m_Spr->setFlipX(true);
			m_Spr->setOpacity(1000);
			m_Rect->setPosition(Vec2(x, y));

			m_Rect->removeFromParent();
			m_Spr->removeFromParent();
			m_DashRect->removeFromParent();
			m_ItemRect->removeFromParent();
			m_HitRect->removeFromParent();
			m_Bow->removeFromParent();

			m_layer->addChild(m_DashRect, 8);
			m_layer->addChild(m_Rect, 7);
			m_layer->addChild(m_Spr, 8);
			m_layer->addChild(m_ItemRect, 8);
			m_layer->addChild(m_HitRect, 6);
			m_layer->addChild(m_Bow, 7);

			SettingItem(BasicWeapon);

			auto Foract = Sprite::create();
			Foract->runAction(Sequence::create(
				DelayTime::create(0.5f),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::HoldPos, this))
				, NULL));
			m_layer->addChild(Foract);
		}
		return true;
	}
}

void ObjectHero::SettingItem(int tagNum)
{
	static bool ifgun;

	if (tagNum == BasicWeapon)
	{
		extern WeaponManager* m_WeaponManager;
		m_WeaponManager->m_MotionNum = BasicWeapon;
		m_WeaponManager->SettingWeapon(BasicWeapon);
		m_WeaponHave = false;
		m_AniNum = 0;
	}
	else if (tagNum == Item::Bat)
	{
		extern WeaponManager* m_WeaponManager;
		m_WeaponManager->m_MotionNum = 1;
		m_WeaponManager->SettingWeapon(Item::Bat);
		m_WeaponHave = true;
		m_AniNum = 4;
	}
	else if (tagNum == Item::Gun)
	{
		extern WeaponManager* m_WeaponManager;
		m_WeaponManager->m_MotionNum = 2;
		m_WeaponManager->SettingWeapon(Item::Gun);
		m_WeaponHave = true;
		m_AniNum = 8;
		ifgun = true;
	}
	else if (tagNum == Shield::Head1)
	{
		extern ShieldManager* m_ShieldManager;
		m_ShieldManager->SettingShield(tagNum);
		m_Shield[0] = true;
	}
	else if (tagNum == Shield::Top1)
	{
		extern ShieldManager* m_ShieldManager;
		m_ShieldManager->SettingShield(tagNum);
		m_Shield[1] = true;
	}
	else if (tagNum == Shield::Bottom1)
	{
		extern ShieldManager* m_ShieldManager;
		m_ShieldManager->SettingShield(tagNum);
		m_Shield[2] = true;
	}
}

void ObjectHero::AnimationSwitch(int num)
{
	static float DashTime;
	extern Timer2* m_Timer2;
	extern WeaponManager* m_WeaponManager;
	extern ShieldManager* m_ShieldManager;

	/*if (m_Death)
		return;*/
	if (num != MotionNum::HeroDeath && (m_HoldPos == false || m_Death))
		return;
	if (DashCheck)
	{
		if (m_Death == false && num == MotionNum::HeroDeath)
		{
			DashCheck = false;
			if (State != num || m_ItemChange)
			{
				m_Death = true;
				CSoundManager::getInstance()->playEffect("Sound/Sound/player_death2.mp3", false, 1.0f);
				m_CurMotionNum = num;
				State = MotionNum::HeroDeath;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(Death),
					CallFunc::create(CC_CALLBACK_0(ObjectHero::HeroDeath, this)),
					NULL));
				m_WeaponManager->AtkMotionSwitch(MotionNum::HeroDeath);
				m_ShieldManager->MotionSwitch(num);
				m_Spr->setZOrder(15);
				Camera::getDefaultCamera()->stopAllActions();
				//if(m_Stage)
				Camera::getDefaultCamera()->runAction(Spawn::create(
					Place::create(m_Rect->getPosition()),
					EaseOut::create(ScaleTo::create(0.5f, 0.5f, 0.5f), 2.0f),
					NULL));
			}
			return;
		}
		if (m_Timer2->GetTime() - DashTime >= 0.33f)
		{
			DashTime = 0;
			DashCheck = false;
		}
		// �뽬�� ���ݻ��°� ������츦 üũ
		if (num == MotionNum::Attack)// ����
		{
			if (m_AniNum == 0)// �⺻���� ����
			{
				DashCheck = false;
				CSoundManager::getInstance()->playEffect("Sound/Sound/player_attack3.mp3", false, 1.0f);
				m_CurMotionNum = num;
				State = MotionNum::Attack;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[1]),
					CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeState, this)),
					Animate::create(effect[18]),
					CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeState, this)),
					NULL));
				m_WeaponManager->AtkMotionSwitch(MotionNum::Attack);
				m_ShieldManager->MotionSwitch(num);
			}
			else if (m_AniNum == 8)// ���Ÿ� ���� ����
			{
				DashCheck = false;
				m_CurMotionNum = num;
				State = MotionNum::Attack;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					Animate::create(effect[5]),
					CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeState, this)),
					NULL));
			}
		}
		else if (num == MotionNum::LongAtk)
		{

		}
		return;
	}
	if (num == MotionNum::Dash)// ���� �뽬
	{
		if (State != num || m_ItemChange)
		{
			CSoundManager::getInstance()->playEffect("Sound/MySound/Pickup_Speed01.mp3", false, 0.2f);

			DashCheck = true;
			DashTime = m_Timer2->GetTime();
			m_CurMotionNum = num;
			State = MotionNum::Dash;
			m_Spr->stopAllActions();
			m_Spr->runAction((Animate::create(effect[16])));
			m_WeaponManager->AtkMotionSwitch(MotionNum::Dash);
			m_ShieldManager->MotionSwitch(num);
		}
	}
	else if (num == MotionNum::Fall)//�߶�
	{
		if (m_OnGround == false)
		{
			if (State != num || m_ItemChange)
			{
				/*Animation* one = Animation::create();
				one->addSpriteFrame(m_Spr->getSpriteFrame());
				one->addSpriteFrame(m_Spr->getSpriteFrame());
				one->setDelayPerUnit(FallDelay);*/
				m_CurMotionNum = num;
				State = MotionNum::Fall;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					DelayTime::create(0.1f),
					//Animate::create(one),
					Animate::create(effect[14]),
					NULL));
				m_WeaponManager->AtkMotionSwitch(MotionNum::Fall);
				m_ShieldManager->MotionSwitch(num);
			}
		}
	}
	else if (num == MotionNum::HeroLadderUp)//��ٸ�Ÿ�� Up
	{
		if (m_LadderEnd)
		{
			Animation* ptr = NULL;
			ptr = effect[MotionSwap ? 17 : 13];
			MotionSwap = MotionSwap ? false : true;
			m_LadderEnd = false;
			m_CurMotionNum = num;
			State = MotionNum::HeroLadderUp;
			m_Spr->stopAllActions();
			m_Rect->stopAllActions();
			m_Spr->runAction(Animate::create(ptr));
			m_Rect->runAction(Sequence::create(
				MoveTo::create(0.3f, Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 80)),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeLadderState, this)),
				NULL));
			m_WeaponManager->AtkMotionSwitch(MotionSwap ? MotionNum::HeroLadderUp : MotionNum::HeroLadderDown);
			m_ShieldManager->MotionSwitch(num);
		}
	}
	else if (num == MotionNum::HeroLadderDown)//��ٸ�Ÿ�� Down
	{
		if (m_LadderEnd)
		{
			Animation* ptr = NULL;
			ptr = effect[MotionSwap ? 17 : 13];
			MotionSwap = MotionSwap ? false : true;
			m_LadderEnd = false;
			m_CurMotionNum = num;
			State = MotionNum::HeroLadderDown;
			m_Spr->stopAllActions();
			m_Rect->stopAllActions();
			m_Spr->runAction(Animate::create(ptr));
			m_Rect->runAction(Sequence::create(
				MoveTo::create(0.3f, Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() - 80)),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeLadderState, this)),
				NULL));
			m_WeaponManager->AtkMotionSwitch(MotionSwap ? MotionNum::HeroLadderUp : MotionNum::HeroLadderDown);
			m_ShieldManager->MotionSwitch(num);
		}
	}
	else if (num == MotionNum::HeroLadderEndUp)//��ٸ�Ÿ�� Down
	{
		if (m_LadderEnd)
		{
			Animation* ptr = NULL;
			ptr = effect[MotionSwap ? 17 : 13];
			MotionSwap = MotionSwap ? false : true;
			m_LadderEnd = false;
			m_CurMotionNum = num;
			State = MotionNum::HeroLadderEndUp;
			m_Spr->stopAllActions();
			m_Rect->stopAllActions();
			m_Spr->runAction(Sequence::create(
				Animate::create(ptr),
				Animate::create(effect[19]), NULL));
			m_Rect->runAction(Sequence::create(
				MoveTo::create(0.8f, Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 230)),
				DelayTime::create(0.2f),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeLadderState, this)),
				NULL));
			m_WeaponManager->AtkMotionSwitch(MotionNum::HeroLadderEndUp);
			m_ShieldManager->MotionSwitch(num);
		}
	}
	else if (num == MotionNum::HeroLadderEndDown)//��ٸ�Ÿ�� Down
	{
		if (m_LadderEnd)
		{
			Animation* ptr = NULL;
			ptr = effect[MotionSwap ? 17 : 13];
			MotionSwap = MotionSwap ? false : true;
			m_LadderEnd = false;
			m_CurMotionNum = num;
			State = MotionNum::HeroLadderEndDown;
			m_Spr->stopAllActions();
			m_Rect->stopAllActions();
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[20]),
				Animate::create(ptr),
				NULL));
			m_Rect->runAction(Sequence::create(
				MoveTo::create(0.8f, Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() - 230)),
				DelayTime::create(0.2f),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeLadderState, this)),
				NULL));
			m_WeaponManager->AtkMotionSwitch(MotionNum::HeroLadderEndDown);
			m_ShieldManager->MotionSwitch(num);
		}
	}
	else if (num == MotionNum::HeroJump)//���� 
	{
		if (State != num || m_ItemChange)
		{
			m_FirstGround = true;
			m_CurMotionNum = num;
			State = MotionNum::HeroJump;
			m_Spr->stopAllActions();
			m_Spr->runAction(Animate::create(effect[3]));
			m_WeaponManager->AtkMotionSwitch(MotionNum::HeroJump);
			m_ShieldManager->MotionSwitch(num);
			if (JumpCount == 0)
				EffectManager::getInstance()->EffectSwitch(EffectName::HeroJump1, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());
			else if (JumpCount == 1)
			{
				CSoundManager::getInstance()->playEffect("Sound/MySound/Male_Jump_Grunt06.mp3", false, 0.3f);
				EffectManager::getInstance()->EffectSwitch(EffectName::HeroJump2, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());
			}
		}
	}
	else if (num == MotionNum::Attack)// ����
	{
		if (m_AniNum == 0)// �⺻���� ����
		{
			bool atkcheck = false;
			extern EnemyManager* m_EnemyManager;
			for (ObjectEnemy* iter : m_EnemyManager->m_List)
			{
				if (iter->m_Death == false)
				{
					if (iter->m_Rect->getBoundingBox().intersectsRect(m_ItemRect->getBoundingBox()))
					{
						atkcheck = true;
						m_TargetIn = true;
						break;
					}
				}
			}
			if (atkcheck == false)
			{
				m_TargetIn = false;
				CSoundManager::getInstance()->playEffect("Sound/Sound/player_attack1.mp3", false, 1.0f);
			}
			else if (m_TargetIn)
				CSoundManager::getInstance()->playEffect("Sound/Sound/player_attack3.mp3", false, 1.0f);

			m_CurMotionNum = num;
			State = MotionNum::Attack;
			m_Spr->stopAllActions();
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[1]),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeState, this)),
				Animate::create(effect[18]),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeState, this)),
				NULL));
			m_WeaponManager->AtkMotionSwitch(MotionNum::Attack);
			m_ShieldManager->MotionSwitch(num);
		}
		else if (m_AniNum == 4)// �������� ����
		{
			m_CurMotionNum = num;
			State = MotionNum::Attack;
			m_Spr->stopAllActions();
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[4]),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeState, this)),
				NULL));
			m_WeaponManager->AtkMotionSwitch(MotionNum::Attack);
			m_ShieldManager->MotionSwitch(num);
		}
		else if (m_AniNum == 8)// ���Ÿ� ���� ����
		{
			CSoundManager::getInstance()->playEffect("Sound/Sound/bowfullback.mp3", false, 1.0f);

			m_CurMotionNum = num;
			State = MotionNum::Attack;
			m_Spr->stopAllActions();
			m_Spr->runAction(Sequence::create(
				Animate::create(effect[5]),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ChangeState, this)),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::ShootArrowSound, this)),
				NULL));
		}
	}
	else if (num == MotionNum::Stand)// ���ĵ�
	{
		if (State != num || m_ItemChange)
		{
			//CSoundManager::getInstance()->playEffect("Sound/Sound/player_Idle.mp3", false, 1.0f);
			m_CurMotionNum = num;
			State = MotionNum::Stand;
			m_Spr->stopAllActions();
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[2])));
			m_WeaponManager->AtkMotionSwitch(MotionNum::Stand);
			m_ShieldManager->MotionSwitch(num);
			if (m_FirstGround)
			{
				m_FirstGround = false;
				EffectManager::getInstance()->EffectSwitch(EffectName::HeroLand, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());
			}
		}
	}
	else if (num == MotionNum::Move)// �޸���
	{
		if (State != num || m_ItemChange)
		{
			//CSoundManager::getInstance()->playEffect("Sound/Sound/player_walk.mp3", true, 1.0f);

			m_CurMotionNum = num;
			State = MotionNum::Move;
			m_Spr->stopAllActions();
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
			//EffectManager::getInstance()->EffectSwitch(EffectName::HeroLand, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());

			//m_Spr->runAction(Sequence::create(
			//	RepeatForever::create(Animate::create(effect[0])),
			//	//Animate::create(effect[15]),
			//	//CallFunc::create(CC_CALLBACK_0(ObjectHero::HeroRun, this)),
			//	NULL));
			m_WeaponManager->AtkMotionSwitch(MotionNum::Move);
			m_ShieldManager->MotionSwitch(num);
			if (m_FirstGround)
			{
				m_FirstGround = false;
				EffectManager::getInstance()->EffectSwitch(EffectName::HeroLand, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());
			}
		}
	}
	else if (num == MotionNum::HeroDamageLeft || num == MotionNum::HeroDamageRight)// Ÿ��
	{
		if (m_HeroHit == false)
		{
			if (State != num || m_ItemChange)
			{
				CSoundManager::getInstance()->playEffect("Sound/MySound/Hurt.mp3", false, 0.3f);

				m_HeroHit = true;
				m_CurMotionNum = num;
				State = num;
				m_Spr->stopAllActions();
				m_Spr->runAction(Sequence::create(
					TintTo::create(0.1f, Color3B::RED),
					TintTo::create(0.1f, Color3B(255, 255, 255)),
					NULL));
				m_Spr->runAction(RepeatForever::create(Animate::create(effect[21])));
				
				bool Colide = false;
				for (Sprite* box : SourceManager::getInstance()->m_metabox)
				{
					if (m_HitRect->getBoundingBox().intersectsRect(box->getBoundingBox()) && box->getTag() == MetaNum::Red)
					{
						Colide = true;
						break;
					}
				}
				if (Colide == false)
				{
					if (num == MotionNum::HeroDamageRight)
					{
						m_Rect->runAction(Sequence::create(
							JumpTo::create(0.2f, Vec2(m_Rect->getPositionX() + 55, m_Rect->getPositionY() + 35), 50, 1),
							CallFunc::create(CC_CALLBACK_0(ObjectHero::DirClear,this)), NULL));
					}
					else if (num == MotionNum::HeroDamageLeft)
					{
						m_Rect->runAction(Sequence::create(
							JumpTo::create(0.2f, Vec2(m_Rect->getPositionX() - 55, m_Rect->getPositionY() + 35), 50, 1),
							CallFunc::create(CC_CALLBACK_0(ObjectHero::DirClear, this)), NULL));
					}
				}
				m_WeaponManager->AtkMotionSwitch(MotionNum::Stand);
				m_ShieldManager->MotionSwitch(MotionNum::Stand);
			}
		}
	}
	else if (num == MotionNum::HeroDeath)// ����
	{
		if (State != num || m_ItemChange)
		{
			m_Death = true;
			CSoundManager::getInstance()->playEffect("Sound/Sound/player_death2.mp3", false, 1.0f);
			m_CurMotionNum = num;
			State = MotionNum::HeroDeath;
			m_Spr->stopAllActions();
			m_Spr->setColor(Color3B(255, 255, 255));
			m_Spr->runAction(Sequence::create(
				Animate::create(Death),
				CallFunc::create(CC_CALLBACK_0(ObjectHero::HeroDeath, this)),
				NULL));
			m_WeaponManager->AtkMotionSwitch(MotionNum::HeroDeath);
			m_ShieldManager->MotionSwitch(num);
			m_Spr->setZOrder(15);
			Camera::getDefaultCamera()->stopAllActions();
			//if(m_Stage)
			Camera::getDefaultCamera()->runAction(Spawn::create(
				Place::create(m_Rect->getPosition()),
				EaseOut::create(ScaleTo::create(0.5f, 0.5f, 0.5f), 2.0f),
				NULL));
		}
	}
	else if (num == MotionNum::Nothing)
	{
		if (State != num || m_ItemChange)
		{
			m_CurMotionNum = num;
			State = MotionNum::Nothing;
			m_Spr->stopAllActions();
			m_WeaponManager->AtkMotionSwitch(MotionNum::Nothing);
		}
	}


	if (m_ItemChange)
		m_ItemChange = false;
}

void ObjectHero::HeroDeath()
{
	m_HoldPos = true;
	//m_HP = 10;

	Vec2 pos = Camera::getDefaultCamera()->getPosition();

	Sprite* FadeBack = Sprite::create("Stage1_2/Base3.png");
	FadeBack->setScaleX(11.0f);
	FadeBack->setScaleY(8.0f);
	FadeBack->setPosition(pos);
	FadeBack->setOpacity(0);
	FadeBack->runAction(Sequence::create(
		FadeIn::create(1.5f), DelayTime::create(3.5f),
		Place::create(m_RebornPos),
		FadeOut::create(1.0f),
		RemoveSelf::create(), NULL));
	m_layer->addChild(FadeBack, 14);


	auto txtLabel = Label::createWithTTF("YOU DIED", "fonts/gabia_napjakBlock.ttf", 50);
	txtLabel->setColor(Color3B::RED);
	txtLabel->setOpacity(0);
	txtLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	txtLabel->setPosition(Vec2(pos.x, pos.y + 150));
	m_layer->addChild(txtLabel, 15);

	txtLabel->runAction(Sequence::create(
		DelayTime::create(1.5f),
		FadeIn::create(0.5f),
		DelayTime::create(3.0f),
		RemoveSelf::create(),
		NULL));

	auto foraction = Sprite::create();
	foraction->runAction(Sequence::create(
		DelayTime::create(5.0f),
		CallFunc::create(CC_CALLBACK_0(ObjectHero::SetRectPos, this)),
		CallFunc::create(CC_CALLBACK_0(ObjectHero::HoldPos, this)),
		CallFunc::create(CC_CALLBACK_0(ObjectHero::MakeLife, this)),
		NULL));
	m_layer->addChild(foraction);


	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->CloseWeapon->setVisible(false);

	//�Ѿ� �޸�����
	/*std::vector<BulletClass*>::iterator bullet = m_bullet.begin();
	int bulletSize = m_bullet.size();
	for (int i = 0; !m_bullet.empty(); ++i)
	{
		m_bullet.erase(bullet);
		(*bullet)->Delete();
		bullet = m_bullet.begin();
	}*/
}

void ObjectHero::HeroUpdate()
{
	//����üũ
	AniSoundCheck();

	extern WeaponManager* m_WeaponManager;
	if (m_WeaponManager->m_Durability == 0)
	{
		SettingItem(BasicWeapon);
		return;
	}

	//���� �����Ѱ�� �Ѿ˾�����Ʈ üũ
	if (m_AniNum == 8 && !m_bullet.empty())
	{
		std::list<BulletClass*>::iterator bullet = m_bullet.begin();
		extern EnemyManager* m_EnemyManager;

		for (bullet; bullet != m_bullet.end(); ++bullet)
		{
			// ������ �浹üũ
			for (Boss* boss : m_EnemyManager->m_Boss)
			{
				if (boss->m_Lock == false && boss->m_Death == false)
				{
					if ((*bullet)->CheckColide(boss->m_Rect))
					{
						CSoundManager::getInstance()->playEffect("Sound/Sound/arrowattacked.mp3", false, 1.0f);
						m_bullet.erase(bullet);
						boss->m_HP -= BowDamage;
						boss->BossHit();
						if (boss->m_HP <= 0)
						{
							boss->m_Death = true;
							boss->AnimationSwitch(BossMotion::BossDeath);
						}
						return;
					}
				}
			}

			// ������ �浹üũ
			for (ObjectEnemy* enemy : m_EnemyManager->m_List)
			{
				if ((*bullet)->CheckColide(enemy->m_Rect))
				{
					CSoundManager::getInstance()->playEffect("Sound/Sound/arrowattacked.mp3", false, 1.0f);
					m_bullet.erase(bullet);
					enemy->SetHP(-BowDamage);
					enemy->AnimationSwitch(EnemyMotion::Hit);
					return;
				}
			}
			// ������ �浹üũ
			if (m_BossBullet == false)
			{
				for (Sprite* box : SourceManager::getInstance()->m_metabox)
				{
					if ((*bullet)->CheckColide(box))
					{
						m_bullet.erase(bullet);
						return;
					} 
				}
			}
			else
			{
				for (Sprite* box : SourceManager::getInstance()->m_metabox)
				{
					if ((*bullet)->m_Rect->getPositionX() < 0 || (*bullet)->m_Rect->getPositionX() > 1920 ||
						(*bullet)->m_Rect->getPositionY() < 0 || (*bullet)->m_Rect->getPositionY() > 1600)
					{
						(*bullet)->DeleteList();
						m_bullet.erase(bullet);
						return;
					}
				}
			}
			// ������ �ڽ��� �浹üũ
			extern ItemManager* m_ItemManager;
			std::vector<ObjectItem*>::iterator iter = m_ItemManager->m_List.begin();
			for (iter; iter != m_ItemManager->m_List.end(); ++iter)
			{
				if ((*iter)->m_Recreate == false)
				{
					if ((*iter)->m_ItemExit == false && (*iter)->m_HP > 0 && (*iter)->m_Spr->getName() != "ItemSave")
					{
						if ((*bullet)->CheckColide((*iter)->m_Rect))
						{
							(*iter)->m_HP -= BowDamage;
							if ((*iter)->m_HP <= 0)
								(*iter)->AnimationSwitch(ObjectEffect::Death);

							m_ItemManager->m_List.erase(iter);
							m_bullet.erase(bullet);

							return;
						}
					}
				}
			}
			for (ObjectItem* iter : m_ItemManager->m_List)
			{
				if (iter->m_Recreate == false)
				{
					if (iter->m_ItemExit == false && iter->m_HP > 0 && iter->m_Spr->getName() != "ItemSave")
					{
						if ((*bullet)->CheckColide(iter->m_Rect))
						{
							iter->m_HP -= BowDamage;
							if (iter->m_HP <= 0)
								iter->AnimationSwitch(ObjectEffect::Death);

							//m_ItemManager->m_List.erase
							m_bullet.erase(bullet);

							return;
						}
					}
				}
			}
		}
	}
}

void ObjectHero::HeroAttack()
{
	extern Timer2* m_Timer2;
	static float m_AtTime;

	if (m_AtTime == 0)
		m_AtTime = m_Timer2->GetTime();

	extern WeaponManager* m_WeaponManager;
	if (m_AniNum == 0)// �⺻ ������ ���
	{
		if (m_FrameCheck && m_Timer2->GetTime() - m_AtTime > BasicAttackDelay)
		{
			m_AtTime = m_Timer2->GetTime();
			m_FrameCheck = false;
		}
		if (m_WeaponManager->CloseWeapon->getTexture()->getName() ==
			m_WeaponManager->m_Att[2] && m_FrameCheck == false)
		{
			m_AtTime = m_Timer2->GetTime();
			AttackCheck();
			m_FrameCheck = true;
		}
		else if (m_WeaponManager->CloseWeapon->getTexture()->getName() ==
			m_WeaponManager->m_Att[3] && m_FrameCheck == false)
		{
			m_AtTime = m_Timer2->GetTime();
			AttackCheck();
			m_FrameCheck = true;
		}
	}
	else if (m_AniNum == 4)// ���ݰ�ü Bat�� ���
	{
		extern WeaponManager* m_WeaponManager;
		if (m_WeaponManager->CloseWeapon->getTexture()->getName() ==
			m_WeaponManager->m_Att[0] && m_FrameCheck == false)
		{
			AttackCheck();
			m_FrameCheck = true;
		}
		else if (m_WeaponManager->CloseWeapon->getTexture()->getName() !=
			m_WeaponManager->m_Att[0] && m_FrameCheck)
			m_FrameCheck = false;
	}
	else if (m_AniNum == 8)// ���ݰ�ü Gun�� ���
	{
		extern WeaponManager* m_WeaponManager;
		if (m_Spr->getTexture()->getName() == m_BowAtk &&
			m_FrameCheck == false)
		{
			CreateBullet();
			m_FrameCheck = true;
		}
		else if (m_Spr->getTexture()->getName() != m_BowAtk &&
			m_FrameCheck)
			m_FrameCheck = false;
	}
}

void ObjectHero::MoveCharacter(std::vector<int> dir, float dt)
{
	if (m_HoldPos == false)
		return;
	
	//���� ��ų
	if (m_BossSkill1)
	{
		m_Rect->setPositionX(m_Rect->getPositionX() - 5);
		for (Sprite* box : SourceManager::getInstance()->m_metabox)
		{
			if (box->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
			{
				m_Rect->setPositionX(m_Rect->getPositionX() + 5);
				break;
			}
		}
	}

	// �뽬 �ܻ�ȿ��
	if (m_HeroDash)
	{
		Sprite* shadow = Sprite::createWithTexture(m_Spr->getTexture());
		shadow->setFlipX(m_Spr->isFlipX() ? true : false);
		shadow->setPosition(m_Spr->getPosition());
		shadow->setColor(m_Spr->getColor());
		shadow->setOpacity(85);
		m_Spr->getParent()->addChild(shadow,8);
		shadow->runAction(Sequence::create(
			FadeOut::create(0.7f), RemoveSelf::create(), NULL));
	}

	//ȭ��� ������ ����
	if (m_Rect->getPositionX() < 0)
		m_Rect->setPositionX(0.0f);

	// ī�޶�� Pos����
	extern Timer2* m_Timer2;
	static float m_SavePosTime;
	m_BeforePos.push_back(m_Rect->getPosition());

	if (m_Timer2->GetTime() - m_SavePosTime > 0.12f)
	{
		m_SavePos = *(m_BeforePos.begin());
		m_BeforePos.pop_front();
	}
	// �浹�ڽ��� ���ΰ� �߷�üũ
	//static bool CanJump;
	static bool JumpCheck;
	static bool col;
	static bool canJump2;
	static bool Jump2Check;
	static bool BlockJump;
	static bool ReJump;
	static bool gravity;

	int AniNum = 0;
	if (m_Death)
	{
		return;
	}
	if (m_Death == false)
	{
		if (m_SetLadder)// ��ٸ� ź���� on
		{
			for (Sprite* box : SourceManager::getInstance()->m_metabox)
			{
				if (box->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()) &&
					(box->getTag() == MetaNum::GreenL || box->getTag() == MetaNum::GreenR || box->getTag() == MetaNum::GreenEnd))
				{
					m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));

					if (box->getTag() == MetaNum::GreenL || box->getTag() == MetaNum::GreenR)
					{
						m_Spr->setFlipX(box->getTag() == MetaNum::GreenL ? true : false);
						m_Rect->setFlipX(box->getTag() == MetaNum::GreenL ? true : false);
					}
					else if (box->getTag() == MetaNum::GreenEnd)
					{
						m_Spr->setFlipX(box->isFlipX() ? true : false);
						m_Rect->setFlipX(box->isFlipX() ? true : false);
					}
					for (int iter : dir)
					{
						if (iter == PadDir::UpMove)
						{
							if (box->getTag() == MetaNum::GreenL || box->getTag() == MetaNum::GreenR || box->getTag() == MetaNum::GreenEnd)
							{
								FollowBox();
								if (box->getTag() == MetaNum::GreenEnd)
									AnimationSwitch(MotionNum::HeroLadderEndUp);
								else
									AnimationSwitch(MotionNum::HeroLadderUp);

								return;
							}
						}
						else if (iter == PadDir::DownMove)
						{
							for (Sprite* box : SourceManager::getInstance()->m_metabox)
							{
								if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()) && box->getTag() != MetaNum::Blue
									&& box->getTag() != MetaNum::MonsterOnly  && box->getTag() != MetaNum::GreenL && box->getTag() != MetaNum::GreenR && box->getTag() != MetaNum::GreenEnd)
								{
									m_SetLadder = false;
									return;
								}
							}
							if (box->getTag() == MetaNum::GreenL || box->getTag() == MetaNum::GreenR || box->getTag() == MetaNum::GreenEnd)
							{
								FollowBox();
								if (box->getTag() == MetaNum::GreenEnd)
									AnimationSwitch(MotionNum::HeroLadderEndDown);
								else
									AnimationSwitch(MotionNum::HeroLadderDown);
								return;
							}
						}
						else if (iter == PadDir::JUMP || iter == PadDir::JUMP2)
						{
							m_SetLadder = false;
							return;
						}
					}
					m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));

					FollowBox();
					return;
				}
			}
			//���⿡ ��������� ���
			m_SetLadder = false;
			m_LadderEnd = true;
			return;
		}
		///////////////////////////////////////////////////////////////////////////////
		// �߷� ����
		m_Rect->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() - PhysicNum::Gravity  - m_accel));
		CanJump = true;
		m_accel += 0.2f;
		AniNum = MotionNum::Fall;

		m_OnGround = false;
		// ���� �浹�ڽ�
		for (Sprite* box : SourceManager::getInstance()->m_metabox)
		{
			// �ڽ�üũ : �߷����� ���� �϶�üũ�̱� ������ �ڽ�Y�� ���ΰ�Y ���ϰ� �̿��� ��
			if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()) && box->getPositionY() < m_Rect->getPositionY()
				&& (box->getTag() == MetaNum::Red || box->getTag() == MetaNum::Blue))
			{
				m_OnGround = true;
				m_GroundPos = box->getPosition();
				m_accel = 0;
				gravity = true;
				Jump2Check = false;
				CanJump = false; // ���鿡 ������� CanJump = false�� �����Ѵ�
				m_Rect->setPosition(Vec2(m_Rect->getPositionX(), box->getPositionY() + 78));//�߷����� ���� ������ ����ŭ �ٽ� �����ش�
				AniNum = MotionNum::Stand;
				JumpCount = 0;
				ReJump = true;
				break;
			}
		}

		// ��ٸ�Ÿ��
		for (int iter : dir)
		{
			if (iter == PadDir::UpMove)
			{
				for (Sprite* box : SourceManager::getInstance()->m_metabox)//���ڽ� �� �浹üũ
				{
					if (box->getTag() == MetaNum::GreenL || box->getTag() == MetaNum::GreenR)
					{
						if (sqrt((m_Rect->getPositionX() - box->getPositionX())*(m_Rect->getPositionX() - box->getPositionX()) +
							(m_Rect->getPositionY() - box->getPositionY())*(m_Rect->getPositionY() - box->getPositionY())) < 40)
						{
							gravity = false;
							m_SetLadder = true;
							m_Rect->setPosition(Vec2(box->getPositionX() + (box->getTag() == MetaNum::GreenL ? 0 : 50), box->getPositionY() + 16));
							AniNum = MotionNum::HeroLadderUp;
							m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
							AnimationSwitch(AniNum);
							FollowBox();
							return;
						}
					}
				}
			}
			else if (iter == PadDir::DownMove)
			{
				for (Sprite* box : SourceManager::getInstance()->m_metabox)//���ڽ� �� �浹üũ
				{
					if (box->getTag() == MetaNum::GreenL || box->getTag() == MetaNum::GreenR || box->getTag() == MetaNum::GreenEnd)
					{
						if (sqrt((m_Rect->getPositionX() - box->getPositionX())*(m_Rect->getPositionX() - box->getPositionX()) +
							(m_Rect->getPositionY() - 80 - box->getPositionY())*(m_Rect->getPositionY() - 80 - box->getPositionY())) < 50)
						{
							gravity = false;
							m_SetLadder = true;
							AniNum = MotionNum::HeroLadderDown;

							if (box->getTag() != MetaNum::GreenEnd)
								m_Rect->setPosition(Vec2(box->getPositionX() + (box->getTag() == MetaNum::GreenL ? 0 : 50), box->getPositionY() + 16));
							else if (box->getTag() == MetaNum::GreenEnd)
								m_Rect->setPosition(Vec2(box->getPositionX() + (box->isFlipX() ? 0 : 50), box->getPositionY() + 16));

							m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));

							if (box->getTag() == MetaNum::GreenEnd)
								AnimationSwitch(HeroLadderEndDown);
							else
								AnimationSwitch(AniNum);
							FollowBox();
							return;

						}
					}
				}
			}
		}
		///// ���� üũ ////////////////////////
		if (JumpCheck && JumpPower != 5)
		{
			m_accel = 0;
			gravity = false;
			if (JumpCount > 1)
			{
				JumpPower = PhysicNum::JumpPower;
				col = true;
				JumpCheck = false;
			}
			Rect sample = m_Rect->getBoundingBox();
			sample.origin.y += JumpPower;
			for (Sprite* box : SourceManager::getInstance()->m_metabox)//���ڽ� �� �浹üũ
			{
				if (sample.intersectsRect(box->getBoundingBox()) && box->getTag() != MetaNum::Blue && box->getTag() != MetaNum::MonsterOnly
					&& box->getTag() != MetaNum::GreenL && box->getTag() != MetaNum::GreenR)
				{
					m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
					JumpCheck = false;
					JumpPower = PhysicNum::JumpPower;
					col = true;
					FollowBox();
					return;
				}
			}
			if (col == false)
			{
				AniNum = MotionNum::HeroJump;
				float t = dt;
				if (dt > 0.03f)
				{
					m_Rect->setPositionY(m_Rect->getPositionY() + JumpPower * 1.4f);
					m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
					--JumpPower;
				}
				else
				{
					m_Rect->setPositionY(m_Rect->getPositionY() + JumpPower);
					m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
					--JumpPower;
				}
			}
		}
		else//��������
		{
			JumpPower = PhysicNum::JumpPower;
			JumpCheck = false;
		}
		if (m_HeroHit)
		{
			static float hittime;
			if (hittime > 0.5)
			{
				hittime = 0;
				m_HeroHit = false;
				for (int i = 0; i < 3; ++i)
					m_AttackEnd[i] = true;
			}
			else
				hittime += dt;
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			FollowBox();
			//dir.clear();
			return;
		}

		//����1Ÿ �������
		if (m_AttackEnd[0] == false || m_AttackEnd[1] == false)
		{
			dir.clear();
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			HeroAttack();
			FollowBox();
			return;
		}
		//���� ��ư üũ - ������ �ٸ�Ű�� ���ý����� ���� ��������
		for (int iter : dir)
		{
			if (iter == PadDir::Att)
			{
				m_AttackEnd[0] = false;
				AniNum = MotionNum::Attack;
				AnimationSwitch(MotionNum::Attack);
				dir.clear();
				bool ACheck = true;
				for (Sprite* box : SourceManager::getInstance()->m_metabox)
				{
					if (m_DashRect->getBoundingBox().intersectsRect(box->getBoundingBox()) && box->getTag() == MetaNum::Red)
						ACheck = false;
				}
				if (ACheck && m_AniNum == 0)
					m_Rect->runAction(MoveTo::create(0.2f, Vec2(m_Rect->getPositionX() + (m_Rect->isFlipX() ? 10 : -10), m_Rect->getPositionY())));
				m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
				FollowBox();
				return;
			}
		}
		int num = 0;
		////////// �̵� üũ ////////////////////////////////////////////////////
		for (int iter : dir)
		{
			if (CanJump == false)
			{
				BlockJump = true;
				canJump2 = false;
			}
			if (BlockJump)
			{
				if (iter == PadDir::JUMP && JumpCheck == false && canJump2 == false)
				{
					//accel = 0;
					++JumpCount;
					canJump2 = true;
					col = false;
					JumpCheck = true; // ����, JumpCheck(�ߺ���������) ������ true
				}// ���� �����Ŀ� �̻� �Ҹ��ϰ� ��� �����ϵ��� JumpPower < 8 �� �����ص�
				else if (iter == PadDir::JUMP && CanJump && canJump2 && (JumpPower < 8 || JumpCheck == false))
				{
					//accel = 0;
					++JumpCount;
					JumpPower = PhysicNum::JumpPower;
					JumpCheck = true;
					col = false;
					canJump2 = false;
					BlockJump = false;
				}
			}
			// �뽬
			if ((iter == PadDir::LeftDash || iter == PadDir::RightDash) && CanJump == false && SetEnergy(-10))// <--
			{
				EffectManager::getInstance()->EffectSwitch(EffectName::HeroLand, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());
				m_HeroDash = true;
				if (CanJump == false)
					AniNum = MotionNum::Dash;
				Vec2 pos = m_Rect->getPosition();
				m_Rect->runAction(
					MoveTo::create(0.3f, Vec2(iter == PadDir::LeftDash ? pos.x - PhysicNum::DashSpeed : pos.x + PhysicNum::DashSpeed, pos.y)));
				m_Spr->setFlipX(iter == PadDir::LeftDash ? false : true);
				m_Rect->setFlipX(iter == PadDir::LeftDash ? false : true);
			}
			// �̵�
			if (iter == PadDir::LeftMove || iter == PadDir::RightMove)// <--
			{
				m_HeroDash = false;
				if (CanJump == false && AniNum != MotionNum::Dash)
					AniNum = MotionNum::Move;
				if (m_Rect->getNumberOfRunningActions() == 0 && iter == PadDir::LeftMove)
					m_Rect->setPositionX(m_Rect->getPositionX() - PhysicNum::MovePower*dt);
				else if (m_Rect->getNumberOfRunningActions() == 0 && iter == PadDir::RightMove)
					m_Rect->setPositionX(m_Rect->getPositionX() + PhysicNum::MovePower*dt);
				m_Spr->setFlipX(iter == PadDir::LeftMove ? false : true);
				m_Rect->setFlipX(iter == PadDir::LeftMove ? false : true);
			}
			for (Sprite* box : SourceManager::getInstance()->m_metabox)
			{
				if (m_Rect->getNumberOfRunningActions() != 0)
				{
					if (m_DashRect->getBoundingBox().intersectsRect(box->getBoundingBox()) && box->getTag() == MetaNum::Red)
					{
						m_Rect->stopAllActions();
						m_Rect->setPositionX(m_Rect->getPositionX() + (m_Spr->isFlipX() ? -10 : 10));
					}
				}
				if (m_Rect->getBoundingBox().intersectsRect(box->getBoundingBox()) && box->getTag() == MetaNum::Red)
				{
					if (iter == PadDir::LeftMove || iter == PadDir::RightMove)
						m_Rect->setPositionX(m_Rect->getPositionX() + (iter == PadDir::LeftMove ? PhysicNum::MovePower*dt : -PhysicNum::MovePower*dt));
					if (JumpCount == 1 && ReJump)//���� 2���������ؾ� ���µǴ� 1ȸ ���µǴ� ���
					{
						ReJump = JumpCheck = canJump2 = false;
						JumpCount -= 1;
					}
				}
			}
		}
		switch (AniNum)
		{
		case MotionNum::Dash:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::Dash);
			break;
		case MotionNum::Fall:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::Fall);
			break;
		case MotionNum::Move:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX() + (m_Spr->isFlipX() ? -30 : 30), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::Move);
			break;
		case MotionNum::Stand:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::Stand);
			break;
		case MotionNum::Attack:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::Attack);
			break;
		case MotionNum::HeroJump:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::HeroJump);
			break;
		case MotionNum::HeroLadderDown:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::HeroLadderDown);
			break;
		case MotionNum::HeroLadderUp:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::HeroLadderUp);
			break;
		/*case MotionNum::Nothing:
			m_Spr->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + SpineDif_Y));
			AnimationSwitch(MotionNum::Nothing);
			break;*/
		}
		FollowBox();
	}
}

//������,�� �ڽ� ĳ���� ��������ϱ�
void ObjectHero::FollowBox()
{
	// Ȱ
	if (m_AniNum == 8)
		m_Bow->setVisible(true);
	else
		m_Bow->setVisible(false);

	if (m_AniNum == 8)
	{
		if (m_CurMotionNum == MotionNum::Stand)
		{
			m_Bow->setRotation(0);
			m_Bow->setFlipX(m_Rect->isFlipX() ? true : false);
			m_Bow->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 50));
		}
		else if (m_CurMotionNum == MotionNum::Move)
		{
			m_Bow->setRotation(m_Rect->isFlipX() ? 30 : -30);
			m_Bow->setFlipX(m_Rect->isFlipX() ? true : false);
			m_Bow->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 40));
		}
		else if (m_CurMotionNum == MotionNum::HeroLadderDown || m_CurMotionNum == MotionNum::HeroLadderUp ||
			m_CurMotionNum == MotionNum::HeroLadderEndUp || m_CurMotionNum == MotionNum::HeroLadderEndDown)
		{
			m_Bow->setRotation(0);
			m_Bow->setFlipX(m_Rect->isFlipX() ? true : false);
			m_Bow->setPosition(Vec2(m_Rect->getPositionX() + (m_Rect->isFlipX() ? -20 : 20), m_Rect->getPositionY() + 40));
		}
		else if (m_CurMotionNum == MotionNum::Dash)
		{
			m_Bow->setRotation(0);
			m_Bow->setFlipX(m_Rect->isFlipX() ? true : false);
			m_Bow->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 30));
		}
		else if (m_CurMotionNum == MotionNum::Attack)
		{
			m_Bow->setVisible(false);
		}
		else
		{
			m_Bow->setRotation(0);
			m_Bow->setFlipX(m_Rect->isFlipX() ? true : false);
			m_Bow->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY() + 50));
		}
	}
	// ��Ʈ��� �ڽ�
	m_HitRect->setFlipX(m_Rect->isFlipX() ? true : false);
	m_HitRect->setPosition(Vec2(m_Rect->getPositionX(), m_Rect->getPositionY()));

	// �뽬 �ڽ�
	m_DashRect->setFlipX(m_Rect->isFlipX() ? true : false);
	m_DashRect->setPosition(Vec2(m_Rect->getPositionX() + (m_Rect->isFlipX() ? 80 : -80), m_Rect->getPositionY()));

	// �� ������ �̵�
	extern ShieldManager* m_ShieldManager;
	m_ShieldManager->FollowHero();

	// ���� ������ �̵�
	extern WeaponManager* m_WeaponManager;
	m_WeaponManager->FollowHero();

	//������ ���º�ȯ üũ
	static int CheckAniNum;
	if (m_AniNum == 0)//�Ǽ�
	{
		CheckAniNum = m_AniNum;
		m_ItemRect->setPosition(Vec2(m_Rect->getPositionX() + (m_Rect->isFlipX() ? 80 : -80), m_Rect->getPositionY()));
	}
	else if (m_AniNum == 4)// Bat(�����)
	{
		if (CheckAniNum != m_AniNum)
		{
			m_damage = 50;
			m_ItemRect->removeFromParentAndCleanup(true);
			m_ItemRect = Sprite::create("Hero/HeroBatRect.png");
			m_ItemRect->setVisible(ColiideRect);
			m_layer->addChild(m_ItemRect, 6);
			CheckAniNum = m_AniNum;
		}
		m_ItemRect->setPosition(Vec2(m_Rect->getPositionX() + (m_Rect->isFlipX() ? 50 : -50), m_Rect->getPositionY()));
	}
	else if (m_AniNum == 8)// Gun(��)
	{
		if (CheckAniNum != m_AniNum)
		{
			m_damage = 30;
			/*Sprite* fortex = Sprite::create("Hero")
			m_ItemRect->removeFromParentAndCleanup(true);
			m_ItemRect = Sprite::create("Hero/HeroRect.png");
			m_ItemRect->setVisible(ColiideRect);
			m_layer->addChild(m_ItemRect, 6);*/
			CheckAniNum = m_AniNum;
		}
		m_ItemRect->setPosition(m_Rect->getPosition());
	}
}

void ObjectHero::GetTime(float dt)
{
	m_Timer += dt;
}

//��������üũ
void ObjectHero::AttackCheck()
{
	m_layer->runAction(Sequence::create(
		MoveTo::create(0.05f, Vec2(m_layer->getPositionX() + 10, m_layer->getPositionY())),
		MoveTo::create(0.05f, Vec2(m_layer->getPositionX(), m_layer->getPositionY())),
		NULL));

	extern EnemyManager* m_EnemyManager;
	bool oneByOne = true;

	// Boss üũ
	for (Boss* iter : m_EnemyManager->m_Boss)
	{
		if (iter->m_Death == false && iter->m_Lock == false)
		{
			if (iter->m_Rect->getBoundingBox().intersectsRect(m_ItemRect->getBoundingBox()))
			{
				if (iter->m_HP < 0)
					return;
				oneByOne = false;
				iter->m_HP -= m_damage;
				iter->BossHit();
				iter->m_HitCheck = false;
				if (iter->m_HP <= 0)
				{
					iter->m_Death = true;
					iter->AnimationSwitch(BossMotion::BossDeath);
				}
				return;
			}
		}
	}
	// Enemy üũ
	for (ObjectEnemy* iter : m_EnemyManager->m_List)
	{
		if (iter->m_Death == false)
		{
			if (iter->m_Rect->getBoundingBox().intersectsRect(m_ItemRect->getBoundingBox()))
			{
				if (iter->m_HP < 0)
					return;
				oneByOne = false;
				iter->m_HP -= m_damage;
				iter->m_HitCheck = false;
				iter->AnimationSwitch(EnemyMotion::Hit);
				if (iter->m_HP <= 0)
					iter->m_Death = true;
				//return �ؾ��ϴ��� Ȯ��
			}
		}
	}

	for (MiniEnemy* iter : m_EnemyManager->m_ColideMini)
	{
		if (iter->m_Death == false)
		{
			if (iter->m_Rect->getBoundingBox().intersectsRect(m_ItemRect->getBoundingBox()))
			{ 
				if (iter->m_HP < 0 || iter->m_Hit )
					return;
				oneByOne = false;
				iter->m_HP -= m_damage;
				iter->AnimationSwitch(MiniMotion::MiniHit);
				if (iter->m_HP <= 0)
				{
					iter->m_Death = true;
					iter->AnimationSwitch(MiniMotion::MiniDeath);
				}
			}
		}
	}
	
	//������ ����üũ�� �켱 -> ���� ������ ����üũ�� ������쿡�� ������ üũ�ϰ� ����
	if (oneByOne)
	{
		extern ItemManager* m_ItemManager;
		std::vector<ObjectItem*>::iterator iter = m_ItemManager->m_List.begin();

		for (iter; iter != m_ItemManager->m_List.end(); ++iter)
		{
			if ((*iter)->m_Recreate == false)
			{
				if ((*iter)->m_ItemExit == false && (*iter)->m_HP > 0 && (*iter)->m_Spr->getName() != "ItemSave")
				{
					if ((*iter)->m_Rect->getBoundingBox().intersectsRect(m_ItemRect->getBoundingBox()))
					{
						if ((*iter)->m_Spr->getName() == "Nothing")
						{
							(*iter)->m_HP -= m_damage;
							(*iter)->AnimationSwitch(ObjectEffect::Death);
							m_ItemManager->m_List.erase(iter);
							return;
						}
						(*iter)->m_HP -= m_damage;
						if ((*iter)->m_HP <= 0)
							(*iter)->AnimationSwitch(ObjectEffect::Death);
					}
				}
			}
		}
	}

}

bool ObjectHero::GetItem(ObjectItem* iter)
{
	bool get = false;
	bool weapon = false;

	//�ڽ�1 - ����1
	if (iter->m_Item->getTag() == Item::Box1)
	{
		EffectManager::getInstance()->EffectSwitch(EffectName::GetScroll, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());
		return true;
	}

	if (iter->m_Item->getTag() / 10 >= 3)//�� ������
	{
		if (iter->m_Item->getTag() / 10 == 3)//�������� = 3
		{
			if (m_Shield[0] == false)
				get = true;
			else
			{
				get = true;
				extern ItemManager* m_ItemManager;
				ObjectItem* item = new ObjectItem;
				extern ShieldManager* m_ShieldManager;
				item->ReCreateItem(m_ShieldManager->m_Shield[0]);
			}
		}
		else if (iter->m_Item->getTag() / 10 == 5)//�������� = 4
		{
			if (m_Shield[1] == false)
				get = true;
			else
			{
				get = true;
				extern ItemManager* m_ItemManager;
				ObjectItem* item = new ObjectItem;
				extern ShieldManager* m_ShieldManager;
				item->ReCreateItem(m_ShieldManager->m_Shield[1]);
			}
		}
		else if (iter->m_Item->getTag() / 10 == 7)//�������� = 5
		{
			if (m_Shield[2] == false)
				get = true;
			else
			{
				get = true;
				extern ItemManager* m_ItemManager;
				ObjectItem* item = new ObjectItem;
				extern ShieldManager* m_ShieldManager;
				item->ReCreateItem(m_ShieldManager->m_Shield[2]);
			}
		}
	}
	else if (iter->m_Item->getTag() < 30 && iter->m_Item->getTag() >= 10)//����� ��ũ�� ������
	{
		if (m_WeaponHave)// ���������
		{
			extern ItemManager* m_ItemManager;
			ObjectItem* item = new ObjectItem;
			item->ReCreateItem(m_SaveWeapon);
		}
		get = true;
		weapon = true;
	}
	if (get && iter->m_Item->getTag() >= 10)// ���⳪ ���ִ� �ּ� 10�̻���
	{
		iter->m_Item->setVisible(false);
		iter->m_ItemExit = false;
		SettingItem(iter->m_Item->getTag());
		float tag = iter->m_Item->getTag();
		m_ItemChange = true;
		if (weapon)
		{
			weapon = false;
			m_SaveWeapon = Sprite::createWithSpriteFrame(iter->m_Item->getSpriteFrame());
			m_SaveWeapon->setTag(iter->m_Item->getTag());
			m_SaveWeapon->setVisible(false);
			m_layer->addChild(m_SaveWeapon, -1);
		}
		return true;
	}
	else if (get == false && iter->m_Item->getTag() < 10 && iter->m_Item->getTag() >= 1)
	{
		if (iter->m_Item->getTag() == Item::SkillScroll1)
		{
			if (m_Skill[0] == false)
			{
				m_Skill[0] = true;
			}
		}
		else if (iter->m_Item->getTag() == Item::SkillScroll2)
		{
			if (m_Skill[1] == false && m_Skill[0] == true)
			{
				m_Skill[1] = true;
			}
		}
		else if (iter->m_Item->getTag() == Item::SkillScroll3)
		{
			if (m_Skill[2] == false && m_Skill[0] == true && m_Skill[1] == true)
			{
				m_Skill[2] = true;
			}
		}
		EffectManager::getInstance()->EffectSwitch(EffectName::GetScroll, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());
		return true;
	}
	//�Ա� �����Ѱ�� false
	return true;
}

void ObjectHero::CreateBullet()
{
	BulletClass* bullet = *MemoryPool::getInstance()->m_BulletPool.begin();
	bullet->RunBullet(m_Spr->getPosition(), m_Spr->isFlipX(), m_layer);
	m_bullet.push_back(bullet);
	MemoryPool::getInstance()->m_BulletPool.erase(MemoryPool::getInstance()->m_BulletPool.begin());
}

void ObjectHero::GetLayer(Layer* layer)
{
	m_layer = layer;
}

void ObjectHero::GetSoucre(SourceManager* source)
{
	m_Soucre = source;
}

void ObjectHero::InitHP()
{
	auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 50.0f);
	label->setAnchorPoint(Vec2(0.0f, 1.0f));
	label->setPosition(Vec2(330.0f, 700.0f));
	label->setName("HERO_HP");
	label->setVisible(false);
	m_UIlayer->addChild(label, 9);
}

void ObjectHero::SetHP(int num)
{
	extern ShieldManager* m_ShieldManager;
	for (int i = 0; i < 3; ++i)
	{
		if (m_Shield[i])
		{
			m_ShieldManager->m_Hard[i] += num;
			if (m_ShieldManager->m_Hard[i] < 0)
			{
				m_Shield[i] = false;
				m_ShieldManager->m_Shield[i]->setVisible(false);
				m_ShieldManager->m_Hard[i] = 0;
				return;
			}
			return;
		}
	}
	if (m_HP > 0)
	{
		if (num == 90)
			m_HP = 90;
		else
			m_HP += num;
		if (m_HP < 0)
			m_HP = 0;
		GameUI* pad = (GameUI*)m_layer->getParent()->getChildByTag(100);
		pad->UpdateHP();
		auto label = dynamic_cast<Label*>(m_UIlayer->getChildByName("HERO_HP"));
		label->setString(StringUtils::format("HP : %d", m_HP));
		if (m_HP <= 0)
		{
			AnimationSwitch(MotionNum::HeroDeath);
			return;
		}
	}
	else
	{
		m_Death = true;
	}
}

void ObjectHero::GetUILayer(Layer* layer)
{
	m_UIlayer = layer;
}

void ObjectHero::SetShieldHP(int tagNum)
{
	if (tagNum == Shield::Head1)
		m_Hard[0] = 100;
	else if (tagNum == Shield::Top1)
		m_Hard[1] = 100;
	else if (tagNum == Shield::Bottom1)
		m_Hard[2] = 100;
}

bool ObjectHero::SetEnergy(int value)
{
	if (m_Energy + value >= 0)
	{
		m_Energy += value;
		return true;
	}
	return false;
}

void ObjectHero::BulletDelete()
{

}

void ObjectHero::DirClear()
{
	GameUI* pad = (GameUI*)m_layer->getParent()->getChildByTag(100);
	pad->m_dir.clear();
}
