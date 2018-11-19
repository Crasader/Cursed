#ifndef __STAGE1_1_H__
#define __STAGE1_1_H__

#include "Default.h"

class Stage1_1 : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage1_1);

	//Default
	CameraControl* m_CamControl;
	bool m_EndAction;
	void ChangeCameraState()
	{
		//if (m_EndAction)
		//	m_EndAction = false;
		//else
			m_EndAction = true;
	}
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

	//업데이트
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//타일맵
	void RoadTileMap();
	TMXTiledMap* m_tmap;
	TMXLayer* m_background1;
	TMXLayer* m_background2;
	TMXLayer* m_background3;
	TMXLayer* m_background4;
	TMXLayer* m_background5;
	TMXLayer* m_background6;

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

	//터치
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

	//배경오브젝트
	Sprite *backbase, *back1, *back2, *back3, *backTop1, *backTop2;
	Sprite *pil1, *pil2, *Top1, *Top2, *Front1, *Front2;
	void CreateBack();
};

#endif 
