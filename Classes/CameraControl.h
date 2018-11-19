#ifndef __CAMERA_CONTROL_H__
#define __CAMERA_CONTROL_H__

#include "Default.h"
#pragma once

class CameraControl
{
public:
	Size m_WinSize;
	Size m_MapSize;
	Sprite* m_Camera;
	Layer* m_layer;
public:
	CameraControl(Size wsize,Size msize, Layer* layer, Vec2 cpos);
	~CameraControl();

	float Stg13Ypos;
	bool m_Once[10];
	bool m_CamAct;
	bool m_Event[10];
	int m_StageNum;
	void FadeScene(Vec2 pos);
	void setViewPointCenter();
	void Stage1_2CameraCheck(Vec2 pos);
	Vec2 ReturnViewPos();
	void EndCameraAction()
	{
		m_CamAct = true;
	}

	//«¡∑π¿”30
	void setViewPointCenter2();
	void SettingCamera();

};


#endif