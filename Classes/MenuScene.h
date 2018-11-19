#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

class MenuScene : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

	//Default
	bool m_twice;
	Sprite* BackGround;
	Animation* m_TitleAni;
	bool m_once;
	Size m_winSize;
	void GameMenu1(Object* pSender);
	void update(float dt);
	void RunTitle();

	Sprite* m_Effect[3];

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif 