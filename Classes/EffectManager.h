#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__

#include "Default.h"
#define EffectIndex 20

enum EffectName {
	HeroJump1, HeroJump2, HeroLand, GetScroll,
	MonsterHit1, MonsterHit2, LadyBugBoom, Protect, HeroWalk, Flame1,GreenE, RedE, BlackE,
	Teloport
};
class EffectManager : public CSingletonBase<EffectManager>
{
public:
	EffectManager();
	~EffectManager();

	Animation *effect[EffectIndex];
	Layer* m_layer;
	void GetLayer(Layer* layer);
	void CreateEffect();
	void EffectSwitch(int num, float x, float y, bool Flip);
	void EffectSwitch(int num, float x, float y, bool Flip, float delay);
};

#endif 