#include "Default.h"

CameraControl::CameraControl(Size wsize, Size msize, Layer* layer, Vec2 cpos)
{
	m_CamAct = false;
	Stg13Ypos = 800;
	m_WinSize = wsize;
	m_MapSize = msize;
	m_layer = layer;
	m_Camera = Sprite::create("Camera.png");
	m_Camera->setPosition(Vec2(cpos.x, cpos.y - 150));
	m_Camera->setVisible(CameraVisible);
	m_layer->addChild(m_Camera, 15);

	for (int i = 0; i < 10; ++i)
		m_Once[i] = false;

	for (int i = 0; i < 10; ++i)
		m_Event[i] = false;
}

CameraControl::~CameraControl()
{
	m_Camera->runAction(RemoveSelf::create());
}

//초반 카메라 고정버그 해결위한 꼼수함수
void CameraControl::FadeScene(Vec2 pos)
{
	Sprite* FadeAct = Sprite::create("Stage1_2/Base3.png");
	FadeAct->setScaleX(9.0f);
	FadeAct->setScaleY(8.0f);
	pos.x += 400;
	FadeAct->setPosition(pos);
	FadeAct->runAction(Sequence::create(
		DelayTime::create(0.5f), FadeOut::create(0.5f), RemoveSelf::create(),
		NULL));
	m_layer->addChild(FadeAct, 30);

	Sprite* FadeAct2 = Sprite::createWithTexture(FadeAct->getTexture());
	FadeAct2->setScaleX(7.0f);
	FadeAct2->setScaleY(5.0f);
	FadeAct2->setPosition(Vec2(m_WinSize.width*0.5f, m_WinSize.height*0.5f));
	FadeAct2->runAction(Sequence::create(
		DelayTime::create(0.5f), RemoveSelf::create(), NULL));
	m_layer->addChild(FadeAct2, 30);
}

void CameraControl::setViewPointCenter()
{
	Vec2 pos = m_Camera->getPosition();
	if (pos.x <= m_WinSize.width*0.5f)
		pos.x = m_WinSize.width*0.5f;
	else if (pos.x >= m_MapSize.width - m_WinSize.width*0.5f)
		pos.x = m_MapSize.width - m_WinSize.width*0.5f;

	if (pos.y <= m_WinSize.height*0.5f)
		pos.y = m_WinSize.height*0.5f;
	else if (pos.y >= m_MapSize.height - m_WinSize.height*0.5f)
		pos.y = m_MapSize.height - m_WinSize.height*0.5f;

	if (m_StageNum == 13)
	{
		if (pos.x >= 10100)
		{
			m_Event[2] = true;
			Stg13Ypos = 1100;
		}
		if (pos.x >= 8400 && ObjectHero::getInstance()->m_Rect->getPositionX() < 9280)
		{
			if (Stg13Ypos != 1100)
				Stg13Ypos += 5;
		}
		else if (m_Event[1] == false && m_Event[2])
		{
			if (pos.x <= 10100)
				pos.x = 10100;
		}
		else if (m_Event[1])
		{
			if (pos.x <= 16000 && pos.x >= 15350)
				pos.x = 16400;
		}

		if (m_Event[0] )
		{
			Stg13Ypos = 800;
			m_Event[0] = false;
		}

		pos.y = Stg13Ypos;
		if (Stage1_3Elite)
			pos.y = 1100;
		Camera::getDefaultCamera()->setPosition(pos);
	}
	else if (m_StageNum == 23)
	{
		static bool once;
		float y = pos.y;
		if (pos.y >= 700 && once == false)
			once = true;

		if (once)
		{
			if (pos.y < 700)
				pos.y = 700;
		}
		Camera::getDefaultCamera()->setPosition(pos);
	}
	/*else if (m_StageNum == 21)
	{
		if(pos.x)
	}*/
	else
		Camera::getDefaultCamera()->setPosition(pos);
}

void CameraControl::Stage1_2CameraCheck(Vec2 pos)
{
	Vec2 Cpos = pos;
	int check = 0;
	if (Camera::getDefaultCamera() != NULL)
	{
		if (Cpos.x > 3800.0f && Cpos.y > 2200.0f)
		{
			if (Cpos.x > 4000.0f && Cpos.x < 4380.0f)
				Cpos.x = 4000.0f;
		}

		if (Cpos.y < 3300 && Cpos.y > 2750 && Cpos.x > 1530 && Cpos.x < 3325)
		{
			if(Cpos.y > 2958)
				Cpos.y = 2958.0f;
		}
	}

	if(!m_CamAct)
		Camera::getDefaultCamera()->setPosition(Cpos);
}

Vec2 CameraControl::ReturnViewPos()
{
	Vec2 pos = m_Camera->getPosition();
	if (pos.x <= m_WinSize.width*0.5f)
		pos.x = m_WinSize.width*0.5f;
	else if (pos.x >= m_MapSize.width - m_WinSize.width*0.5f)
		pos.x = m_MapSize.width - m_WinSize.width*0.5f;

	if (pos.y <= m_WinSize.height*0.5f)
		pos.y = m_WinSize.height*0.5f;
	else if (pos.y >= m_MapSize.height - m_WinSize.height*0.5f)
		pos.y = m_MapSize.height - m_WinSize.height*0.5f;

	return pos;
}

void CameraControl::SettingCamera()
{
	if (ObjectHero::getInstance()->m_Death)
	{
		m_Camera->setPosition(ObjectHero::getInstance()->m_RebornPos);
		return;
	}

	static bool ActionCheck[3];
	static int ActNum;

	float PosY = (!ObjectHero::getInstance()->m_BeforePos.empty() ? ObjectHero::getInstance()->m_SavePos.y : ObjectHero::getInstance()->m_Rect->getPositionY());

	auto flipMove1 = EaseOut::create(MoveTo::create(0.3f, Vec2(ObjectHero::getInstance()->m_Rect->getPositionX() + 160, PosY)), 1.0f);
	flipMove1->setTag(501);
	auto flipMove2 = EaseOut::create(MoveTo::create(0.3f, Vec2(ObjectHero::getInstance()->m_Rect->getPositionX() - 160, PosY)), 1.0f);
	flipMove2->setTag(502);

	auto flipMove3 = EaseOut::create(MoveTo::create(0.3f, Vec2(ObjectHero::getInstance()->m_Rect->getPositionX() + 200, PosY)), 1.0f);
	flipMove3->setTag(503);
	auto flipMove4 = EaseOut::create(MoveTo::create(0.3f, Vec2(ObjectHero::getInstance()->m_Rect->getPositionX() - 200, PosY)), 1.0f);
	flipMove4->setTag(504);

	auto flipMove5 = EaseIn::create(MoveTo::create(0.2f, Vec2(ObjectHero::getInstance()->m_Rect->getPositionX() + 300, PosY)), 2.0f);
	flipMove3->setTag(505);
	auto flipMove6 = EaseIn::create(MoveTo::create(0.2f, Vec2(ObjectHero::getInstance()->m_Rect->getPositionX() - 300, PosY)), 2.0f);
	flipMove4->setTag(506);

	
	if (ObjectHero::getInstance()->DashCheck)// 대쉬체크
	{
		if (ObjectHero::getInstance()->m_Spr->isFlipX() && ActNum != flipMove5->getTag())
		{
			ActNum = flipMove5->getTag();
			m_Camera->stopAllActions();
			m_Camera->runAction(flipMove5);
		}
		else if (!ObjectHero::getInstance()->m_Spr->isFlipX() && ActNum != flipMove6->getTag())
		{
			ActNum = flipMove6->getTag();
			m_Camera->stopAllActions();
			m_Camera->runAction(flipMove6);
		}
		m_Camera->setPositionY(PosY);
		return;
	}
	if (ObjectHero::getInstance()->m_NoChangePos)//주인공 위치가 부동이면
	{
		if (ObjectHero::getInstance()->m_Spr->isFlipX())
		{
			if (ObjectHero::getInstance()->m_Spr->getBoundingBox().intersectsRect(m_Camera->getBoundingBox()) && ActNum != flipMove1->getTag())
			{
				ActNum = flipMove1->getTag();
				m_Camera->stopAllActions();
				m_Camera->runAction(flipMove1);
			}
			else if (ActNum != flipMove1->getTag())//실행하려는 행동과 같지않으면
			{
				ActNum = flipMove1->getTag();
				m_Camera->stopAllActions();
				m_Camera->runAction(flipMove1);
			}
		}
		else if (!ObjectHero::getInstance()->m_Spr->isFlipX())
		{
			if (ObjectHero::getInstance()->m_Spr->getBoundingBox().intersectsRect(m_Camera->getBoundingBox()) && ActNum != flipMove2->getTag())
			{
				ActNum = flipMove2->getTag();
				m_Camera->stopAllActions();
				m_Camera->runAction(flipMove2);
			}
			else if (ActNum != flipMove2->getTag())//실행하려는 행동과 같지않으면
			{
				ActNum = flipMove2->getTag();
				m_Camera->stopAllActions();
				m_Camera->runAction(flipMove2);
			}
		}
		m_Camera->setPositionY(PosY);
	}
	else if (ObjectHero::getInstance()->m_NoChangePos == false)//주인공이 움직이고 있으면
	{
		if (ObjectHero::getInstance()->m_Spr->isFlipX())
		{
			if (abs(m_Camera->getPositionX() - ObjectHero::getInstance()->m_Rect->getPositionX()) < 10)
			{
				ActNum = NULL;
				m_Camera->stopAllActions();
				m_Camera->setPositionX(ObjectHero::getInstance()->m_Rect->getPositionX());
			}
			else if (m_Camera->getPositionX() < ObjectHero::getInstance()->m_Rect->getPositionX())
			{
				if (ActNum != flipMove3->getTag())
				{
					ActNum = flipMove3->getTag();
					m_Camera->stopAllActions();
					m_Camera->runAction(flipMove3);
				}
			}
		}
		else if (!ObjectHero::getInstance()->m_Spr->isFlipX())
		{
			if (abs(m_Camera->getPositionX() - ObjectHero::getInstance()->m_Rect->getPositionX()) < 10)
			{
				ActNum = NULL;
				m_Camera->stopAllActions();
				m_Camera->setPositionX(ObjectHero::getInstance()->m_Rect->getPositionX());
			}
			else if (m_Camera->getPositionX() > ObjectHero::getInstance()->m_Rect->getPositionX())
			{
				if (ActNum != flipMove4->getTag())
				{
					ActNum = flipMove4->getTag();
					m_Camera->stopAllActions();
					m_Camera->runAction(flipMove4);
				}
			}
		}
		m_Camera->setPositionY(PosY);
	}
}
