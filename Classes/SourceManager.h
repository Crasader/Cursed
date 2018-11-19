#ifndef __SOURCE_MANAGER_H__
#define __SOURCE_MANAGER_H__

#include "Default.h"

#pragma once

USING_NS_CC;

class SourceManager : public CSingletonBase<SourceManager>
{
public:
	SourceManager();
	~SourceManager();

	
	void LoadingSource(Layer*);

	//�浹 �ڽ�
	Vector<Sprite*> m_metabox;
	Vector<Sprite*> m_Stg1_2MBox;

	Sprite* metaboxRed;
	Sprite* metaboxBlue;

	//�޸� ����
	void ClearBoxVector();

	//���ΰ� źȯ
	Sprite* bullet1;

	//�� źȯ
	Sprite* EnemyBullet;

	//��ֹ�
	Sprite* spine;
	Sprite* spineRect[7];
	Sprite* spineRect2[10];
	Sprite* stoneRect[4];
	Sprite* stg1Spine1[3];//��������1 ������ֹ�1
	Sprite* stg1Spine2[5];//��������1 ������ֹ�2
	Sprite* stg1Drop1[2];//��������1 �����ֹ�1
	Sprite* stg1Drop2[2];//��������1 �����ֹ�2
	Sprite* stg1Drop3[3];//��������1 �����ֹ�3


};

#endif 