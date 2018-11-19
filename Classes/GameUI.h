#ifndef __GAMEUI_SCENE_H__
#define __GAMEUI_SCENE_H__

#include "Default.h"
#pragma once

enum PadDir
{
	LeftMove = 201, RightMove = 202, JUMP = 203, JUMP2 = 204, Att = 205, UpMove = 206,
	Skill1 = 210, Skill2 = 211, Skill3 = 212,
	DownMove = 207,
	LeftDash = 208, RightDash = 209
};

class GameUI : public Layer
{
public:
	CREATE_FUNC(GameUI);
	virtual bool init();

	//Default
	Size m_winSize;
	void DoRain();
	void UIupdate();
	Layer* GetLayer();
	void MemoryArrange();
	void InitStageScene();
	void GameClear();

	// 인게임 UI
	Sprite* m_Chatbox;
	void EndEvent1();
	void EndEvent2();

	bool m_WhiteNull;
	Sprite* white;
	Sprite* m_Mask;
	void Makethunder();
	void SetMask();
	void CreateWhite();
	void DrawUI();
	void DrawInfo(Object* pSender);
	void DrawSkill(Object* pSender);
	void SetUIVisible(bool);
	void UISetposition();
	void SetLetter();
	void DirClear();
	void KeyClear()
	{
		m_dir.clear();
		//m_dir.push_back(Pad)
	}
	Sprite* m_Letter;
	Sprite* m_Eye;
	Sprite* m_SkillGageBar;
	Sprite* m_Bar;
	Animation* m_EyeAni;

	//HP
	Sprite* m_HPback[3];
	Sprite* m_Health[3];
	Sprite* m_HPtexture[4];

	//파이널 보스 HP
	bool m_BossHP_Exit;
	float m_MaxHP;
	float m_NumHP;
	Sprite* m_BossHPBack;
	Sprite* m_BossHPBar;
	void BossHPCreate(float);
	void BossHPUpdate(float);

	//코끼리 보스 HP
	bool m_Boss1HP_On;
	void Boss1HPCreate(float);
	void Boss1HPUpdate(float);
	Sprite* m_Boss1HPBack;
	Sprite* m_Boss1HPBar;

	//엘리트 보스 HP
	bool m_EliteHP_On;
	void EliteHPCreate(float);
	void EliteHPUpdate(float);
	Sprite* m_EliteHPBack;
	Sprite* m_EliteHPBar;

	//무기교체
	Sprite* m_WeaponSwap[5];
	void ChangeWeapon();

	void BeepSound()
	{
		CSoundManager::getInstance()->playEffect("Sound/Beep.mp3", false, 1.0f);
	}
	void UpdateHP();

	bool m_UILayer[3];
	bool m_TurnOnInfo;
	Sprite* m_Scroll[3];
	Sprite* m_WeaponSlot;
	Sprite* m_Weapon;
	Sprite* m_Shield[3];
	Sprite* m_ShieldSlot[3];

	//터치
	std::vector<int> m_dir;
	Vec2 m_TouchPos;
	bool m_TouchCheck;
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);


	// PC판/////////////////////////////////////////////////////////////
	// 키보드
	bool m_KeyUp;
	bool m_KeyLock;
	bool m_KeyClean;
	bool m_KeyStack;
	int m_KeySave;
	void MakeKeyListener();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	// 마우스
	Sprite* m_Cursor;
	EventListenerMouse* _mouseListener;
	void onMouseDown(Event* event);
	void onMouseUp(Event* event);
	void onMouseMove(Event* event);
	void onMouseScroll(Event* event);
	Vec2 m_MousePos;
	Vec2 GetCursorPos();
};

#endif 
