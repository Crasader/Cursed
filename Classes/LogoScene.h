#ifndef __LOGO_SCENE_h__
#define __LOGO_SCENE_h__

#include "Default.h"

class LogoScene : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LogoScene);
	void loadingCallBack(Texture2D *texture);
	Sprite* logo;
	float _numberOfSprites;
	float _numberOfLoadedSprites;

	bool m_once;
	void update(float dt);
	void ChangeScene();
};

#endif