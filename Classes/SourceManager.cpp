#include"Default.h"

SourceManager::SourceManager()
{
	//LoadingSource();
}
SourceManager::~SourceManager()
{
}

//Stage1 ���ҽ��ε� -> ���� �������� �ε� ���ҽ� �Լ��� �ٸ��� ����
//�������� �������� ����� ���� �����ؾ� ��
void SourceManager::LoadingSource(Layer* lay)
{
	static bool once;
	if (once == false)
	{
		once = true;
		//�浹�ڽ� Red / Blue
		metaboxRed = Sprite::create("TileMap/MetaSet.png");
		metaboxRed->setVisible(false);
		CC_SAFE_RETAIN(metaboxRed);

		metaboxBlue = Sprite::create("TileMap/MetaSet2.png");
		metaboxBlue->setVisible(false);
		CC_SAFE_RETAIN(metaboxBlue);

		//���ΰ� źȯ
		bullet1 = Sprite::create("Object/Bullet/Bullet1.png");
		bullet1->setVisible(false);
		CC_SAFE_RETAIN(bullet1);

		//�� źȯ
		EnemyBullet = Sprite::create("Object/Bullet/EnemyBullet1.png");
		EnemyBullet->setVisible(false);
		CC_SAFE_RETAIN(EnemyBullet);

		//��ֹ�
		spine = Sprite::create("Object/Tutorial/Spine1.png");
		spine->setVisible(false);
		CC_SAFE_RETAIN(spine);

		//��ֹ� �浹�ڽ� 7��
		char str[100] = { 0 };
		for (int i = 0; i < 7; ++i)
		{
			sprintf(str, "Object/Tutorial/Spine1Colide%d.png", i + 1);
			spineRect[i] = Sprite::create(str);
			spineRect[i]->setVisible(false);
			CC_SAFE_RETAIN(spineRect[i]);
		}

		// ����2
		//��ֹ� �浹�ڽ� 9��
		for (int i = 0; i < 9; ++i)
		{
			sprintf(str, "Object/Tutorial/Spine2Colide%d.png", i + 1);
			spineRect2[i] = Sprite::create(str);
			spineRect2[i]->setVisible(false);
			CC_SAFE_RETAIN(spineRect2[i]);
		}

		// ����2
		//��ֹ� �浹�ڽ� 9��
		for (int i = 0; i < 4; ++i)
		{
			sprintf(str, "Object/Tutorial/Stone1Colide%d.png", i + 1);
			stoneRect[i] = Sprite::create(str);
			stoneRect[i]->setVisible(false);
			CC_SAFE_RETAIN(stoneRect[i]);
		}

		//��������1 ������ֹ�1
		for (int i = 0; i < 3; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Fix_Col1_%d.png", i + 1);
			stg1Spine1[i] = Sprite::create(str);
			stg1Spine1[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Spine1[i]);
		}

		//��������1 ������ֹ�2
		for (int i = 0; i < 5; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Fix_Col2_%d.png", i + 1);
			stg1Spine2[i] = Sprite::create(str);
			stg1Spine2[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Spine2[i]);
		}

		//��������1 �����ֹ�1
		for (int i = 0; i < 2; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Drop_Col1_%d.png", i + 1);
			stg1Drop1[i] = Sprite::create(str);
			stg1Drop1[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Drop1[i]);
		}

		//��������1 �����ֹ�2
		for (int i = 0; i < 2; ++i)
		{
			sprintf(str, "Barrier/ColideBox/Drop_Col2_%d.png", i + 1);
			stg1Drop2[i] = Sprite::create(str);
			stg1Drop2[i]->setVisible(false);
			CC_SAFE_RETAIN(stg1Drop2[i]);
		}

		//��������1 �����ֹ�3
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


