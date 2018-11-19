#include"Default.h"

SourceManager::SourceManager()
{
	//LoadingSource();
}
SourceManager::~SourceManager()
{
}

//Stage1 리소스로딩 -> 차후 스테이질 로딩 리소스 함수를 다르게 구현
//ㄴ해제도 스테이지 종료시 따로 구현해야 함
void SourceManager::LoadingSource(Layer* lay)
{
	static bool once;
	if (once == false)
	{
		once = true;
		//충돌박스 Red / Blue
		metaboxRed = Sprite::create("TileMap/MetaSet.png");
		metaboxRed->setVisible(false);
		CC_SAFE_RETAIN(metaboxRed);

		metaboxBlue = Sprite::create("TileMap/MetaSet2.png");
		metaboxBlue->setVisible(false);
		CC_SAFE_RETAIN(metaboxBlue);

		//주인공 탄환
		bullet1 = Sprite::create("Object/Bullet/Bullet1.png");
		bullet1->setVisible(false);
		CC_SAFE_RETAIN(bullet1);

		//적 탄환
		EnemyBullet = Sprite::create("Object/Bullet/EnemyBullet1.png");
		EnemyBullet->setVisible(false);
		CC_SAFE_RETAIN(EnemyBullet);

		//장애물
		spine = Sprite::create("Object/Tutorial/Spine1.png");
		spine->setVisible(false);
		CC_SAFE_RETAIN(spine);

		//장애물 충돌박스 7종
		char str[100] = { 0 };
		for (int i = 0; i < 7; ++i)
		{
			sprintf(str, "Object/Tutorial/Spine1Colide%d.png", i + 1);
			spineRect[i] = Sprite::create(str);
			spineRect[i]->setVisible(false);
			CC_SAFE_RETAIN(spineRect[i]);
		}

		// 가시2
		//장애물 충돌박스 9종
		for (int i = 0; i < 9; ++i)
		{
			sprintf(str, "Object/Tutorial/Spine2Colide%d.png", i + 1);
			spineRect2[i] = Sprite::create(str);
			spineRect2[i]->setVisible(false);
			CC_SAFE_RETAIN(spineRect2[i]);
		}

		// 가시2
		//장애물 충돌박스 9종
		for (int i = 0; i < 4; ++i)
		{
			sprintf(str, "Object/Tutorial/Stone1Colide%d.png", i + 1);
			stoneRect[i] = Sprite::create(str);
			stoneRect[i]->setVisible(false);
			CC_SAFE_RETAIN(stoneRect[i]);
		}

		//스테이지1 가시장애물1
		for (int i = 0; i < 3; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Fix_Col1_%d.png", i + 1);
			stg1Spine1[i] = Sprite::create(str);
			stg1Spine1[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Spine1[i]);
		}

		//스테이지1 가시장애물2
		for (int i = 0; i < 5; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Fix_Col2_%d.png", i + 1);
			stg1Spine2[i] = Sprite::create(str);
			stg1Spine2[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Spine2[i]);
		}

		//스테이지1 드롭장애물1
		for (int i = 0; i < 2; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Drop_Col1_%d.png", i + 1);
			stg1Drop1[i] = Sprite::create(str);
			stg1Drop1[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Drop1[i]);
		}

		//스테이지1 드롭장애물2
		for (int i = 0; i < 2; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Drop_Col2_%d.png", i + 1);
			stg1Drop2[i] = Sprite::create(str);
			stg1Drop2[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Drop2[i]);
		}

		//스테이지1 드롭장애물3
		for (int i = 0; i < 3; ++i)
		{
			if (i == 2)
				sprintf(str, "Barrier/ColideBox/Drop_Col3_2.png", i);
			else
				sprintf(str, "Barrier/ColideBox/Drop_Col3_%d.png", i + 1);
			stg1Drop3[i] = Sprite::create(str);
			stg1Drop3[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Drop3[i]);
		}
	}
}

void SourceManager::ClearBoxVector()
{
	int size = m_metabox.size();
	Vector<Sprite*>::iterator iter = m_metabox.begin();
	for (int i = 0; i < size; ++i)
	{
		iter = m_metabox.begin();
		m_metabox.erase(iter);
	}
}


