#include "Default.h"

void BulletClass::CreateBullet(int KindNum)
{
	extern BulletManager* m_BulletManager;

	if (KindNum == BulletKind::HeroBullet1)
	{
		m_FirstAdd = false;

		m_KindNum = KindNum;
		//애니메이션
		char str[100] = { 0 };
		for (int i = 0; i < BulletEffectNum; i++)
		{
			m_BulletEffect[i] = Animation::create();
			m_BulletEffect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)// 총알 소멸
		{
			sprintf(str, "Object/Bullet/Bullet1_Death%d.png", i);
			m_BulletEffect[0]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i < BulletEffectNum; ++i)
			CC_SAFE_RETAIN(m_BulletEffect[i]);

		m_Bullet = Sprite::create("Object/Bullet/Arrow1.png");
		m_Rect = Sprite::create("Object/Bullet/Bullet1_Rect.png");
		m_Bullet->setVisible(false);
		m_Rect->setVisible(ColiideRect);
		//m_BulletManager->m_layer->addChild(m_Rect, 7);
		//m_BulletManager->m_layer->addChild(m_Bullet, 8);
		CC_SAFE_RETAIN(m_Bullet);
		CC_SAFE_RETAIN(m_Rect);
	}
	else if (KindNum == BulletKind::EnemyBullet1)
	{
		m_FirstAdd = false;

		m_KindNum = KindNum;
		//애니메이션
		char str[100] = { 0 };
		for (int i = 0; i < BulletEffectNum; i++)
		{
			m_BulletEffect[i] = Animation::create();
			m_BulletEffect[i]->setDelayPerUnit(0.1f);
		}
		for (int i = 1; i <= 3; i++)// 총알 소멸
		{
			sprintf(str, "Object/Bullet/Bullet1_Death%d.png", i);
			m_BulletEffect[0]->addSpriteFrameWithFileName(str);
		}
		for (int i = 0; i < BulletEffectNum; ++i)
			CC_SAFE_RETAIN(m_BulletEffect[i]);

		m_Bullet = Sprite::create("Object/Bullet/Bullet1.png");
		m_Rect = Sprite::create("Object/Bullet/Bullet1_Rect.png");
		CC_SAFE_RETAIN(m_Bullet);
		CC_SAFE_RETAIN(m_Rect);
	}
}

void BulletClass::SetBullet()
{
	extern BulletManager* m_BulletManager;

	if (m_FirstAdd == false)
	{
		m_FirstAdd = true;
		//나중에 true->ColideRect로 수정해야함
		
		//m_BulletManager->m_BulletList.push_back(this);
	}
	else
	{
		//m_BulletManager->m_BulletList.push_back(this);

	}
}
void BulletClass::RunBullet(Vec2 pos, bool flip, Layer* m_lay )
{
	if (m_KindNum == BulletKind::HeroBullet1)
	{
		m_Bullet->setPosition(Vec2(pos.x, pos.y+25));
		m_Bullet->setVisible(true);

		if (m_FirstAdd == false)
		{
			m_FirstAdd = true;
			ObjectHero::getInstance()->m_layer->addChild(m_Bullet, 8);
			ObjectHero::getInstance()->m_layer->addChild(m_Rect, 9);
		}
		float Speed = 15000.0f;
		float time = 15.0f;
		if (flip)
		{
			m_Rect->setPosition(Vec2(m_Bullet->getPositionX() + BulletDifY, m_Bullet->getPositionY()));
			m_Rect->runAction(MoveTo::create(time, Vec2(m_Rect->getPositionX() + Speed, m_Rect->getPositionY())));
			m_Bullet->setFlipX(true);
			m_Bullet->runAction(MoveTo::create(time, Vec2(m_Bullet->getPositionX() + Speed, m_Bullet->getPositionY())));
		}
		else
		{
			m_Rect->setPosition(Vec2(m_Bullet->getPositionX() - BulletDifY, m_Bullet->getPositionY()));
			m_Rect->runAction(MoveTo::create(time, Vec2(m_Rect->getPositionX() - Speed, m_Rect->getPositionY())));
			m_Bullet->setFlipX(false);
			m_Bullet->runAction(MoveTo::create(time, Vec2(m_Bullet->getPositionX() - Speed, m_Bullet->getPositionY())));
		}
	}
}

bool BulletClass::CheckColide(Sprite* object)
{
	if (object->getBoundingBox().intersectsRect(m_Rect->getBoundingBox()))
	{
		m_Rect->stopAllActions();
		m_Bullet->stopAllActions();
		m_Bullet->setVisible(false);
		MemoryPool::getInstance()->m_BulletPool.push_back(this);
		return true;
	}
	else
		return false;
}

void BulletClass::DeleteList()
{
	m_Rect->stopAllActions();
	m_Bullet->stopAllActions();
	m_Bullet->setVisible(false);
	MemoryPool::getInstance()->m_BulletPool.push_back(this);
}

void BulletClass::Delete()
{
	//m_Rect->removeFromParent();
	//m_Bullet->removeFromParent();
	CC_SAFE_RELEASE(m_Rect);
	CC_SAFE_RELEASE(m_Bullet);

	for(int i = 0;  i < BulletEffectNum; ++i)
		CC_SAFE_RELEASE(m_BulletEffect[i]);
}
