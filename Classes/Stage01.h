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

	//�����̺�Ʈ(���ӿ���)
	void BackScene();//�޴�ȭ������ ���ư���
	void GameOver();

	//������Ʈ
	float m_Timer;
	void update(float dt);

	//��������Ʈ
	void CreateBack();

	//Ÿ�ϸ�
	void RoadTileMap();
	TMXTiledMap* m_tmap;
	TMXLayer* m_background;
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

	//ī�޶�
	void setViewPointCenter(Vec2 pos);
	void setCamera(float dt);

	//��ġ
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

};

#endif 
