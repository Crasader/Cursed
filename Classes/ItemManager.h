#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "Default.h"

class ItemManager
{
public:
	std::vector<ObjectItem*> m_List;
	Layer* m_layer;
	void GetLayer(Layer* layer);
};

#endif 