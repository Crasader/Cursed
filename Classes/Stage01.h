#ifndef __STAGE01_SCENE_H__
#define __STAGE01_SCENE_H__

#include "Default.h"

class Stage01 : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage01);

	//Default
	Size m_winSize;
	SourceManager* m_Soucre;
	void MemoryArrange();
	bool m_GameSwitch;
	float m_SaveNum;
	bool m_UpdateFirst;

	//게임이벤트(게임오버)
	void BackScene();//메뉴화면으로 돌아가기
	void GameOver();

	//업데이트
	float m_Timer;
	void update(float dt);

	//배경오브젝트
	void CreateBack();

	//타일맵
	void RoadTileMap();
	TMXTiledMap* m_tmap;
	TMXLayer* m_background;
	TMXLayer* m_MonsterCol;
	TMXLayer* m_Ground;
	TMXLayer* m_Jump;
	TMXLayer* m_Ladder;
	Vector<Sprite*> m_metabox;

	//장애물
	void UpdateBarrier();
	Vec2 m_BarrierPos[10];
	void CreateBarrier();

	//오브젝트 ( 아이템 ), ( 세이브포인트 )
	Vec2 m_SavePoint[10];
	Vec2 m_ItemPos[10];
	void CreateItem();

	//객체(Block),(Enemy)
	Vec2 m_EnemyPos[10];
	void CreateEnemy();
	void CheckColide();
	void UpdateEnemy();

	//카메라
	void setViewPointCenter(Vec2 pos);
	void setCamera(float dt);

	//터치
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

};

#endif 
