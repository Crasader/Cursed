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

	//충돌 박스
	Vector<Sprite*> m_metabox;
	Vector<Sprite*> m_Stg1_2MBox;

	Sprite* metaboxRed;
	Sprite* metaboxBlue;

	//메모리 해제
	void ClearBoxVector();

	//주인공 탄환
	Sprite* bullet1;

	//적 탄환
	Sprite* EnemyBullet;

	//장애물
	Sprite* spine;
	Sprite* spineRect[7];
	Sprite* spineRect2[10];
	Sprite* stoneRect[4];
	Sprite* stg1Spine1[3];//스테이지1 가시장애물1
	Sprite* stg1Spine2[5];//스테이지1 가시장애물2
	Sprite* stg1Drop1[2];//스테이지1 드롭장애물1
	Sprite* stg1Drop2[2];//스테이지1 드롭장애물2
	Sprite* stg1Drop3[3];//스테이지1 드롭장애물3


};

#endif 