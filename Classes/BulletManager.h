#ifndef __BULLET_MANAGER_H__
#define __BULLET_MANAGER_H__

#include "cocos2d.h"
#include "Default.h"

USING_NS_CC;

class BulletManager
{
public:
	std::list<BulletClass*> m_BulletList;
	Layer* m_layer;
	void GetLayer(Layer* layer);
	void AddBullet();

	void GetSource(SourceManager*);
	void Update();
};

#endif 