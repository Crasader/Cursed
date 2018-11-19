#ifndef __ENEMY_MANAGER_H__
#define __ENEMY_MANAGER_H__

#include "cocos2d.h"
#include "Default.h"

USING_NS_CC;

class EnemyManager
{
public:
	std::vector<ObjectEnemy*> m_List;
	std::list<MiniEnemy*> m_MiniList;
	std::list<MiniEnemy*> m_ColideMini;
	std::list<Boss*> m_Boss;

	Layer* m_layer;
	void GetLayer(Layer* layer);
	SourceManager* m_Source;

	void GetSource(SourceManager*);
	void Update();
};

#endif 