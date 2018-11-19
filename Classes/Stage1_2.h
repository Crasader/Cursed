#ifndef __STAGE1_2_H__
#define __STAGE1_2_H__

#include "Default.h"

class Stage1_2 : public Layer
{
public:
	ShadowLayer* _shadowLayer;
	float _timer;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage1_2);

	//Default
	CameraControl* m_CamControl;
	void CameraAction1();
	Size m_winSize;
	SourceManager* m_Soucre;
	void MemoryArrange();
	bool m_GameSwitch;
	float m_SaveNum;
	bool m_UpdateFirst;

	//게임이벤트(게임오버)
	bool m_Lock;
	Sprite* potalRect;
	void BackScene();//메뉴화면으로 돌아가기
	void GameOver();
	Sprite* SphereRect;//창살

	//업데이트
	void UpdateTirgger();
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//타일맵
	Vec2 Portal;
	int MapRedXY[65][92];
	int MapMonXY[65][92];
	int MapRed2XY[65][92];

	void RoadTileMap();
	TMXTiledMap* m_tmap;
	TMXLayer* m_background1;
	TMXLayer* m_background2;
	TMXLayer* m_background3;
	TMXLayer* m_background4;
	TMXLayer* m_background5;
	TMXLayer* m_background6;

	TMXLayer* m_Test;
	TMXLayer* m_MonsterCol;
	TMXLayer* m_Ground;
	TMXLayer* m_Ground2;
	TMXLayer* m_Jump;
	TMXLayer* m_Ladder;
	TMXLayer* m_LadderEnd;
	Vector<Sprite*> m_metabox;

	//장애물
	void UpdateBarrier();
	Vec2 m_BarrierPos[12];
	void CreateBarrier();

	//오브젝트 ( 아이템 ), ( 세이브포인트 )
	Vec2 m_SavePoint[10];
	Vec2 m_ItemPos[10];
	void CreateItem();

	//객체(Block),(Enemy)
	Vec2 m_EnemyPos[30];
	void CreateEnemy();
	void CheckColide();
	void UpdateEnemy();

	//카메라
	void CheckCamEvent();
	bool m_Once[10];

	//터치
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

	//배경오브젝트
	Sprite *backbase;
	void CreateBack();
};

#endif 
