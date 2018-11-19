#ifndef __WEAPON_MANAGER_H__
#define __WEAPON_MANAGER_H__

#include "Default.h"
#define WeaponEffectNum 30
#define AttFrame 10
#define BasicWeapon -10
#define BasicEffectNum 12

enum WeaponEffect {
	CloseStand, CloseWalk, CloseLadder, CloseJump, CloseHit, // 1
	LongStand, LongWalk, LongLadder, LongJump, LongHit // 2
};
class WeaponManager
{
public:
	Animation *effect[WeaponEffectNum];
	Animation *beffect[BasicEffectNum];
	void AnimationInit();

	int m_Att[AttFrame];

	Sprite* ForChange;
	Sprite* CloseWeapon;
	Sprite* LongWeapon;

	int m_WeaponNum;
	int m_Durability; // ³»±¸µµ
	int m_MotionNum;
	Layer* m_layer;
	void GetLayer(Layer* layer);
	void CreateMotion();
	void SettingWeapon(int tagNum);
	void AtkMotionSwitch(int num);
	void FollowHero();
	void WeaponRun();
};

#endif 