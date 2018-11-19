#ifndef __STAGE1_2_LOADING_H__
#define __STAGE1_2_LOADING_H__

#include "Default.h"

class Stage1_2Loading : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage1_2Loading);

	void loadingCallBack(Texture2D *texture);
	Label *_labelLoading;
	Label *_labelPercent;
	Sprite* LoadBarEmpty;

	float _numberOfSprites;
	float _numberOfLoadedSprites;

	void ChangeScene();

	void update(float dt);
};

#endif 