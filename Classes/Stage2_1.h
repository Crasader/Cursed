#ifndef __STAGE2_1_H__
#define __STAGE2_1_H__

#include "Default.h"

class Stage2_1 : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage2_1);

	//Default
	CameraControl* m_CamControl;
	void CameraAction1();
	Size m_winSize;
	SourceManager* m_Soucre;
	void MemoryArrange();
	bool m_GameSwitch;
	float m_SaveNum;
	bool m_UpdateFirst;
	void setViewPointCenter();

	//�����̺�Ʈ(���ӿ���)
	Label* EmotionLabel;
	ObjectEnemy* m_Demon;
	Boss* m_Elite;
	Boss* m_Boss1;
	void Stage1_3EventCheck();
	bool m_Lock;
	Sprite* m_Spine;
	Sprite* potalRect;
	void BackScene();//�޴�ȭ������ ���ư���
	void GameOver();

	//������Ʈ
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//Ÿ�ϸ�
	Vec2 Portal;
	int MapRedXY[13][48];
	int MapMonXY[13][48];
	int MapRed2XY[13][48];

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

	//��ֹ�
	void UpdateBarrier();
	Vec2 m_BarrierPos[12];
	void CreateBarrier();

	//������Ʈ ( ������ ), ( ���̺�����Ʈ )
	Vec2 m_SavePoint[10];
	Vec2 m_ItemPos[10];
	void CreateItem();

	//��ü(Block),(Enemy)
	Vec2 m_EnemyPos[20];
	void CreateEnemy();
	void CheckColide();
	void UpdateEnemy();

	Sprite* m_Interact[20];

	//ī�޶�
	bool m_EventOn;
	void CheckCamEvent();
	bool m_Once[20];
	void SetLetter();
	void SetLetter2();


	//��ġ
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

	//��������Ʈ
	Sprite *backbase;
	Sprite* Left[10];
	Sprite* Mid[10];
	Sprite* Right[10];
	Sprite* Smoke[10];

	void CreateBack();

};


#endif 
