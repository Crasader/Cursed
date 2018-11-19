#include "Default.h"

BarrierManager* m_BarrierManager = new BarrierManager;

void BarrierManager::GetLayer(Layer * layer)
{
	m_layer = layer;
}

void BarrierManager::BarrierUpdate()
{
	for (ObjectBarrier* iter : m_List)
	{
		if (iter->m_BarrierNum == BarrierType::Spine || iter->m_BarrierNum == BarrierType::Spine2 ||
			iter->m_BarrierNum == BarrierType::Stone1 || iter->m_BarrierNum == BarrierType::Stage1Spine1 ||
			iter->m_BarrierNum == BarrierType::Stage1Spine2)
			iter->SpineAction();
		else if (iter->m_BarrierNum == BarrierType::Stage1Drop1 || iter->m_BarrierNum == BarrierType::Stage1Drop2 ||
			iter->m_BarrierNum == BarrierType::Stage1Drop3)
			iter->DropBallAction();
		else if (iter->m_BarrierNum == BarrierType::Gate || iter->m_BarrierNum == BarrierType::Gate2)
			iter->GateAction();
		else if (iter->m_BarrierNum == BarrierType::IronMace)
			iter->IromMaceUpdate();
	}
}

void BarrierManager::GetSource(SourceManager* Source)
{
	m_Source = Source;
}

