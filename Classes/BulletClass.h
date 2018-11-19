#ifndef __BULLET_CLASS_H__
#define __BULLET_CLASS_H__

#include "Default.h"

#define BulletEffectNum 3

#define BulletDifY 40

enum BulletKind
{
	HeroBullet1, HeroBullet2,
	EnemyBullet1,
	BarrierBuller1
};

class BulletClass
{
public:
	Sprite* m_Bullet;
	Sprite* m_Rect;
	int m_KindNum;
	bool m_FirstAdd;
	Animation* m_BulletEffect[BulletEffectNum];

	void CreateBullet(int KindNum);
	void RunBullet(Vec2 pos, bool flip, Layer* m_lay);
	void SetBullet();
	bool CheckColide(Sprite*);
	void DeleteList();
	void Delete();
};

#endif 