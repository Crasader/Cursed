#ifndef __OBJECT_ITEM_H__
#define __OBJECT_ITEM_H__

USING_NS_CC;

#define ObjectEffectNum 3

enum ObjectEffect
{
	Death = 1, Saving = 2
};

enum Item
{
	Bat = 10, Gun = 11, SavePoint = 0, SkillScroll1 = 1, SkillScroll2 = 2, SkillScroll3 = 3,
	None = 4, Jar1 = 5, Jar2 = 6, Jar3 = 7, Jar4 = 8,
	Box1 = 21
};

enum Shield
{
	Head1 = 30,
	Top1 = 50, 
	Bottom1 = 70
};
class ObjectItem
{
public:
	Animation* effect[ObjectEffectNum];
	Sprite* m_Spr;
	Sprite* m_Item;
	Sprite* m_Rect;
	Sprite* m_Guide;
	int m_HP;
	int m_State;
	bool m_ItemExit;
	bool m_Recreate;

	//세이브 포인트용
	bool m_SaveObject;
	int m_SaveNum;

	void ChangeItemState();
	void ItemDelete();

	void CreateObject(float x, float y, int itemNum);
	void AnimationSwitch(int num);
	void CreateItem();
	void ReCreateItem(Sprite*);

	void ItemUpdate();
};

#endif 