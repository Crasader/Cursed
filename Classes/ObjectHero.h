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
	Sprite* m_Spr;//캐릭터
	Sprite* m_ItemSpr;//아이템 상태 캐릭터
	Sprite* m_Rect;//실제 캐릭터 공격받았을시 판정해줄 박스
	Sprite* m_DashRect;//대쉬 충돌 측정용 박스
	Sprite* m_HitRect;
	Sprite* m_Bow;//등뒤 활

	MotionStreak* m_Streak;

	// 스킬 시스템
	bool m_Skill[3];
	
	// 키입력 ( 아이템 줍기 )
	bool m_UpdateLock;
	bool m_Interact;//상호작용키
	bool m_GetOn;

	//방어구 시스템
	Sprite* m_ShieldSpr[3];
	bool m_Shield[3];

	//방어력(대체HP감소)
	int m_Hard[3];
	void SetShieldHP(int tagNum);

	//기력
	int m_Energy;
	bool SetEnergy(int);

	// HP
	int m_HP;
	void InitHP();
	void SetHP(int num);
	float m_damage;
	bool m_Death;
	
	// 보스관련 시스템
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

	//레이어받아오기 / 소스받기
	void GetLayer(Layer*);
	Layer* m_layer;
	void GetSoucre(SourceManager*);
	void GetUILayer(Layer*);
	Layer* m_UIlayer;

	// 현재 착용중인 장비와 배열 Index
	Sprite* m_SaveWeapon;
	bool m_WeaponHave;
	Sprite* m_ItemRect;
	bool m_ItemChange;//아이템 착용을 알려주는변수
	bool GetItem(ObjectItem*);//아이템획득함수
	void CreateBullet();//총알생성
	std::list<BulletClass*> m_bullet;
	void BulletDelete();
	void DirClear();
	//Vector<Sprite*> m_bullet;
	void FollowBox();//충돌박스 따라가기
	void HeroDeath();

	bool CreateObject(float x, float y);
	void SettingItem(int tagNum);
	void GetTime(float dt);

	// 움직임셋팅
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
	bool m_OnGround;//지면확인
	Vec2 m_GroundPos;//히어로와 충돌중인 땅 Pos
	bool MotionSwap;
	bool DashCheck;
	std::list<Vec2> m_BeforePos;
	Vec2 m_SavePos;//카메라 연출용 저장된 Pos
	Vec2 m_CheckPos;//카메라 연출용 저장된 Pos2
	bool m_NoChangePos;//포지션 고정상태

	void HeroRun()//히어로 달리기
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
	bool m_AttackEnd[3];//공격1타 끝나기 체크
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

	bool m_LadderEnd;//사다리 타기 끝나기 체크
	void ChangeLadderState()
	{
		m_LadderEnd = true;
	}

	//현재는 탄환검사를 수행한다
	void HeroUpdate();

	//적과 아이템 객체용
	Weapon* m_Basic;
	void HeroAttack();
	void AttackCheck();

	// 이펙트
	bool m_FirstGround;

	// Spine
	int State;

	// Sound
	bool m_TargetIn;
	int m_SoundNum[10];
	bool m_SoundEnd[10];
	void AniSoundCheck()
	{
		// 플레이어 기본공격
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
	
		// 플레이어 달리기
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

		for (int i = 1; i <= 16; i++)// 달리기
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

		for (int i = 1; i <= 25; i++)// 서있기
		{
			sprintf(str, "Hero/HeroIdle/idle%d.png", i);
			effect[2]->addSpriteFrameWithFileName(str);
		}
		effect[2]->setRestoreOriginalFrame(true);//애니메이션 종료시 원래 스프라이트로 복귀

	}
};

#endif