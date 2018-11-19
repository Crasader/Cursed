#ifndef __OBJECT_ITEM_H__
#define __OBJECT_BARRIER_H__

#include "Default.h"

enum BarrierType {
	Spine , Gate ,//��ư ȣ�� ����Ʈ, 
	Spine2 , Stone1 , Gate2 ,// Ʃ�丮�� �ٸ����� ����Ʈ
	Stage1Spine1 ,Stage1Spine2 ,
	Stage1Drop1 , Stage1Drop2 , Stage1Drop3,
	IronMace
};

#define BarrierEffectNum 5
class ObjectBarrier
{
public:
	int m_BarrierNum;//�踮�� ����

	// IronMace
	void CreateIronMace(float x, float y, float Angle);
	void IromMaceUpdate();

	// Spine
	Sprite* m_Spr;
	Sprite* m_SpineRect[10];
	float m_delay;
	Vec2 m_pos[3];
	bool Updown;
	void SpineAction();
	void SetRotation(float,float);

	// Drop
	Sprite* m_Save;
	float m_distance;
	float m_Speed;
	Animation *effect[BarrierEffectNum];
	void SetOption(float , float, float, float );
	void DropBallAction();
	void RepeatDrop();
	void SetTrigger()
	{
		if (Updown)
			Updown = false;
		else
			Updown = true;
	}

	void ColideBallAction()
	{
		Updown = false;
		m_Spr->stopAllActions();
		m_Spr->runAction(Sequence::create(
			//�浹 �ִϸ��̼�
			//Animate::create(effect[0]),
			FadeOut::create(0.0f),
			DelayTime::create(m_delay),
			CallFunc::create(CC_CALLBACK_0(ObjectBarrier::RepeatDrop, this)),
			NULL));
	}
	// Gate
	bool m_ButtonUse;
	Sprite* m_Button;
	void CreateButton(float, float);
	void GateAction();

	// Gate2 - Ʃ�丮���
	int m_FootHoldNum;
	Sprite* m_Guide;//�ȳ� Ű
	Sprite* m_Rect;//���� ��ȣ�ۿ��� �浹�ڽ�
	Sprite* m_FootHold[4]; // ����
	Sprite* m_FootRect[4]; // ���� �浹�ڽ�
	void CreateFoothold();//���� ����
	void CreateFoothold2();//���� ����


public:
	void CreateBarrier(float x, float y, int num);

};

#endif 