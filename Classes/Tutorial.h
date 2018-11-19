#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

#include "Default.h"


class Tutorial : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Tutorial);

	//Default
	Size m_winSize;
	void MemoryArrange();
	bool m_GameSwitch;
	float m_SaveNum;
	bool m_UpdateFirst;

	//�����̺�Ʈ(���ӿ���)
	Sprite* potalRect;
	void BackScene();//�޴�ȭ������ ���ư���
	void GameOver();
	bool m_Lock;
	bool m_event2[10];
	Sprite* m_Message;//�̺�Ʈ�� �޼��� spr
	void TutorialEvent();
	void ChangeEventState();
	void ChangeEventState2();
	//������Ʈ
	void UpdateBack();
	float m_Timer;
	void update(float dt);

	//��������Ʈ
	void CreateBack();
	Sprite *Cloud1, *Cloud2, *Cloud3, *Cloud4, *Cloud5, *Cloud6, *Cloud7, *Cloud8;
	Sprite *backbase;
	Sprite *leftShadow, *leftFrontGround, *leftFrontGround2, *leftstone1, *leftstone2, *leftFrontGround3, *leftTree;//���� ��� ������Ʈ
	Sprite *Mid_Back, *Mid_Back2, *Mid_Back3, *Mid_Moutain, *Mid_Grand, *Mid_Tree1, *Mid_Plant1;//�߾� ��� ������Ʈ
	Sprite *RightShadow, *CageBack, *CageEffect;

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
	TMXLayer* m_LadderEnd;

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
	CameraControl* m_CamControl;
	Sprite* Fade;
	void setViewPointCenter(Vec2 pos);

	//��ġ
	Vec2 m_SaveViewPos;
	Vec2 m_TouchPos;
	bool m_TouchCheck;

};

#endif 
