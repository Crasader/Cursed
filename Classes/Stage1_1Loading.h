#ifndef __STAGE1_1_LOADING_H__
#define __STAGE1_1_LOADING_H__

#include "Default.h"

class Stage1_1Loading : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage1_1Loading);

	void loadingCallBack(Texture2D *texture);

	Label *_labelLoading;
	Label *_labelPercent;

	int _numberOfSprites;
	int _numberOfLoadedSprites;

	bool LoadFinish;
	void update(float dt);
};

#endif 