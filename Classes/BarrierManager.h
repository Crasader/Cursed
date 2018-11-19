#ifndef __BARRIER_MANAGER_H__
#define __BARRIER_MANAGER_H__

#include "Default.h"

USING_NS_CC;

class BarrierManager
{
public:

	std::vector<ObjectBarrier*> m_List;
	Layer* m_layer;
	SourceManager* m_Source;
public:
	void GetLayer(Layer* layer);
	void BarrierUpdate();
	void GetSource(SourceManager*);
};

#endif 