#ifndef __STAGE2_3_LOADING_H__
#define __STAGE2_3_LOADING_H__

#include "Default.h"

class Stage2_3Loading : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage2_3Loading);

	void loadingCallBack(Texture2D *texture);

	Label *_labelLoading;
	Label *_labelPercent;
	Sprite* LoadBarEmpty;

	float _numberOfSprites;
	float _numberOfLoadedSprites;

	void update(float dt);
};

#endif 