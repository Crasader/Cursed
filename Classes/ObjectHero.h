#ifndef __OBJECT_HERO_H__
#define __OBJECT_HERO_H__

#include "cocos2d.h"
#include "Default.h"

USING_NS_CC;
//400
enum PhysicNum
{
	Gravity = 7, JumpPower = 25, MovePower = 400, DashSpeed = 200
};

typedef enum 
{
	Move = 30, Attack = 31, Stand = 32, Fall = 33, HeroDeath = 34, HeroJump = 35, 
	HeroDamageLeft = 36, HeroDamageRight = 37,
	HeroLadderUp, HeroLadderDown, HeroLadderEndUp, HeroLadderEndDown, Nothing, Dash,
	LongAtk,
	HeroSkill1 
}MotionNum;

#define HeroEffectNum 25
#define SpineDif_Y 40

class ObjectHero : public CSingletonBase<ObjectHero>
{
public:
	ObjectHero();
	~ObjectHero();
	
	Animation *effect[HeroEffectNum];
	Animation *Death;
	Sprite* m_Spr;//ĳ����
	Sprite* m_ItemSpr;//������ ���� ĳ����
	Sprite* m_Rect;//���� ĳ���� ���ݹ޾����� �������� �ڽ�
	Sprite* m_DashRect;//�뽬 �浹 ������ �ڽ�
	Sprite* m_HitRect;
	Sprite* m_Bow;//��� Ȱ

	MotionStreak* m_Streak;

	// ��ų �ý���
	bool m_Skill[3];
	
	// Ű�Է� ( ������ �ݱ� )
	bool m_UpdateLock;
	bool m_Interact;//��ȣ�ۿ�Ű
	bool m_GetOn;

	//�� �ý���
	Sprite* m_ShieldSpr[3];
	bool m_Shield[3];

	//����(��üHP����)
	int m_Hard[3];
	void SetShieldHP(int tagNum);

	//���
	int m_Energy;
	bool SetEnergy(int);

	// HP
	int m_HP;
	void InitHP();
	void SetHP(int num);
	float m_damage;
	bool m_Death;
	
	// �������� �ý���
	bool m_EliteClear;
	bool m_BossSkill1;

	bool m_BossBullet;

	float m_accel;
	float m_JumpTime;
	float m_Timer;
	float m_ATimer;
	int m_CurMotionNum;
	std::vector<int> m_dir;
	int JumpPower;
	int AttackNum[3];
	int m_AniNum;
	SourceManager* m_Soucre;

	//���̾�޾ƿ��� / �ҽ��ޱ�
	void GetLayer(Layer*);
	Layer* m_layer;
	void GetSoucre(SourceManager*);
	void GetUILayer(Layer*);
	Layer* m_UIlayer;

	// ���� �������� ���� �迭 Index
	Sprite* m_SaveWeapon;
	bool m_WeaponHave;
	Sprite* m_ItemRect;
	bool m_ItemChange;//������ ������ �˷��ִº���
	bool GetItem(ObjectItem*);//������ȹ���Լ�
	void CreateBullet();//�Ѿ˻���
	std::list<BulletClass*> m_bullet;
	void BulletDelete();
	void DirClear();
	//Vector<Sprite*> m_bullet;
	void FollowBox();//�浹�ڽ� ���󰡱�
	void HeroDeath();

	bool CreateObject(float x, float y);
	void SettingItem(int tagNum);
	void GetTime(float dt);

	// �����Ӽ���
	Vec2 m_RebornPos;
	bool m_HoldPos;
	void MakeLife()
	{
		m_HP = 3010;
		for (int i = 0; i < 3; ++i)
			m_AttackEnd[i] = true;
		m_Death = false;
		m_Spr->setColor(Color3B(255, 255, 255));
		m_Spr->setZOrder(8);
		ObjectHero::getInstance()->m_AniNum = 0;
		ObjectHero::getInstance()->SettingItem(BasicWeapon);
		extern WeaponManager* m_WeaponManager;
		m_WeaponManager->CloseWeapon->setVisible(true);
		Camera::getDefaultCamera()->runAction(ScaleTo::create(1.0f, 1.0f, 1.0f));

		GameUI* pad = (GameUI*)m_layer->getParent()->getChildByTag(100);
		pad->ChangeWeapon();

		SetHP(50);
	}
	void HoldPos()
	{
		m_HoldPos = true;
	}
	void SetRectPos()
	{
		m_Rect->setPosition(m_RebornPos);
	}
	bool m_OnGround;//����Ȯ��
	Vec2 m_GroundPos;//����ο� �浹���� �� Pos
	bool MotionSwap;
	bool DashCheck;
	std::list<Vec2> m_BeforePos;
	Vec2 m_SavePos;//ī�޶� ����� ����� Pos
	Vec2 m_CheckPos;//ī�޶� ����� ����� Pos2
	bool m_NoChangePos;//������ ��������

	void HeroRun()//����� �޸���
	{
		if(m_CurMotionNum == MotionNum::Move)
			m_Spr->runAction(RepeatForever::create(Animate::create(effect[0])));
	}

	int JumpCount;
	bool m_SetLadder;
	void MoveCharacter(std::vector<int> dir, float dt);
	void AnimationSwitch(int num);
	void ChangeHit()
	{
		m_HeroHit = false;
	}
	bool m_FrameCheck;
	bool m_HeroHit;
	bool m_HeroDash;
	bool CanJump;

	int m_BowAtk;
	bool m_AttackEnd[3];//����1Ÿ ������ üũ
	void ChangeState()
	{
		if (m_AttackEnd[0] == false)
		{
			if (m_AniNum != 8)
			{
				GameUI* pad = (GameUI*)m_layer->getParent()->getChildByTag(100);
				for (int iter : pad->m_dir)
				{
					if (iter == PadDir::Att)
					{
						m_SoundEnd[0] = false;
						m_AttackEnd[0] = true;
						m_AttackEnd[1] = false;
						return;
					}
				}
			}
			m_AttackEnd[0] = true;
			return;
		}
		else if (m_AttackEnd[1] == false && m_AttackEnd[0])
		{
			//CSoundManager::getInstance()->playEffect("Sound/Sound/player_attack4.mp3", false, 1.0f);
			m_AttackEnd[1] = true;
		}
	}

	bool m_LadderEnd;//��ٸ� Ÿ�� ������ üũ
	void ChangeLadderState()
	{
		m_LadderEnd = true;
	}

	//����� źȯ�˻縦 �����Ѵ�
	void HeroUpdate();

	//���� ������ ��ü��
	Weapon* m_Basic;
	void HeroAttack();
	void AttackCheck();

	// ����Ʈ
	bool m_FirstGround;

	// Spine
	int State;

	// Sound
	bool m_TargetIn;
	int m_SoundNum[10];
	bool m_SoundEnd[10];
	void AniSoundCheck()
	{
		// �÷��̾� �⺻����
		if (m_CurMotionNum == MotionNum::Attack)
		{
			if (m_Spr->getTexture()->getName() == m_SoundNum[0] && m_SoundEnd[0] == false)
			{
				m_SoundEnd[0] = true;
				if (m_TargetIn == false)
					CSoundManager::getInstance()->playEffect("Sound/Sound/player_attack2.mp3", false, 1.0f, CC_CALLBACK_0(ObjectHero::SoundEnd1, this));
				else if (m_TargetIn)
					CSoundManager::getInstance()->playEffect("Sound/Sound/player_attack4.mp3", false, 1.0f,
						CC_CALLBACK_0(ObjectHero::SoundEnd1, this));
			}
		}
	
		// �÷��̾� �޸���
		if (m_CurMotionNum == MotionNum::Move)
		{
			if (m_Spr->getTexture()->getName() == m_SoundNum[1] && m_SoundEnd[1] == false)
			{
				EffectManager::getInstance()->EffectSwitch(EffectName::HeroWalk, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());

				m_SoundEnd[1] = true;
				CSoundManager::getInstance()->playEffect("Sound/Sound/player_walk.mp3", false, 1.0f);
				Sprite* foraction = Sprite::create();
				foraction->runAction(Sequence::create(
					DelayTime::create(0.05f),
					CallFunc::create(CC_CALLBACK_0(ObjectHero::SoundEnd2, this)),
					RemoveSelf::create(), NULL));
				m_layer->addChild(foraction);
			}
			else if (m_Spr->getTexture()->getName() == m_SoundNum[2] && m_SoundEnd[2] == false)
			{
				EffectManager::getInstance()->EffectSwitch(EffectName::HeroWalk, m_Spr->getPositionX(), m_Spr->getPositionY(), m_Spr->isFlipX());

				m_SoundEnd[2] = true;
				CSoundManager::getInstance()->playEffect("Sound/Sound/player_walk.mp3", false, 1.0f);
				Sprite* foraction = Sprite::create();
				foraction->runAction(Sequence::create(
					DelayTime::create(0.05f),
					CallFunc::create(CC_CALLBACK_0(ObjectHero::SoundEnd3, this)),
					RemoveSelf::create(), NULL));
				m_layer->addChild(foraction);
			}
		}
	}

	void SoundEnd1()
	{
		m_SoundEnd[0] = false;
	}

	void SoundEnd2()
	{
		m_SoundEnd[1] = false;
	}

	void SoundEnd3()
	{
		m_SoundEnd[2] = false;
	}

	void ShootArrowSound()
	{
		CSoundManager::getInstance()->playEffect("Sound/Sound/arrowpass.mp3", false, 1.0f);

	}

	void BugFix()
	{
		char str[100] = { 0 };
		effect[0]->setDelayPerUnit(RunDelay);
		effect[2]->setDelayPerUnit(IdleDelay);

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

		for (int i = 1; i <= 25; i++)// ���ֱ�
		{
			sprintf(str, "Hero/HeroIdle/idle%d.png", i);
			effect[2]->addSpriteFrameWithFileName(str);
		}
		effect[2]->setRestoreOriginalFrame(true);//�ִϸ��̼� ����� ���� ��������Ʈ�� ����

	}
};

#endif