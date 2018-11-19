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

	//�����̺�Ʈ(���ӿ���)
	bool m_Lock;
	Sprite* potalRect;
	void BackScene();//�޴�ȭ������ ���ư���
	void GameOver();

	//������Ʈ
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//Ÿ�ϸ�
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

	//��ֹ�
	void UpdateBarrier();
	Vec2 m_BarrierPos[10];
	void CreateBarrier();

	//������Ʈ ( ������ ), ( ���̺�����Ʈ )
	Vec2 m_SavePoint[10];
	Vec2 m_ItemPos[10];
	void CreateItem();

	//��ü(Block),(Enemy)
	Vec2 m_EnemyPos[10];
	void CreateEnemy();
	void CheckColide();
	void UpdateEnemy();

	//��ġ
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

	//��������Ʈ
	Sprite *backbase, *back1, *back2, *back3, *backTop1, *backTop2;
	Sprite *pil1, *pil2, *Top1, *Top2, *Front1, *Front2;
	void CreateBack();
};

#endif 
