#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "Default.h"

class LoadingScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadingScene);

	void loadingCallBack(Texture2D *texture);

	Sprite* LoadBarEmpty;
	Label *_labelLoading;
	Label *_labelPercent;

	float _numberOfSprites;
	float _numberOfLoadedSprites;

	void ChangeScene();
	void update(float dt);
};

#endif 