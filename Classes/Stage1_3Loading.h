#ifndef __STAGE1_3_LOADING_H__
#define __STAGE1_3_LOADING_H__

#include "Default.h"

class Stage1_3Loading : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage1_3Loading);

	void loadingCallBack(Texture2D *texture);

	Label *_labelLoading;
	Label *_labelPercent;
	Sprite* LoadBarEmpty;

	float _numberOfSprites;
	float _numberOfLoadedSprites;

	void update(float dt);
};

#endif 