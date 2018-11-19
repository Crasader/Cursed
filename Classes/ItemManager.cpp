#include "Default.h"

ItemManager* m_ItemManager = new ItemManager;

void ItemManager::GetLayer(Layer* layer)
{
	m_layer = layer;
}