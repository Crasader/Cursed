#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "Default.h"

class Function : public CSingletonBase<Function>
{
public:
	Function();
	~Function();
	
	//타일맵 블록생성 구간
	// 1_2 
	void MakeColideWidth(int MapXY[][92], Vec2 size, int tag);
	void MakeColideHeight(int MapXY[][92], Vec2 size, int tag);

	// 1_3
	void MakeColideWidth(int MapXY[][228], Vec2 size, int tag);
	void MakeColideHeight(int MapXY[][228], Vec2 size, int tag);

	// 2_1
	void MakeColideWidth(int MapXY[][48], Vec2 size, int tag);
	void MakeColideHeight(int MapXY[][48], Vec2 size, int tag);

	// 2_2 | 2_3
	void MakeColideWidth(int MapXY[][24], Vec2 size, int tag);
	void MakeColideHeight(int MapXY[][24], Vec2 size, int tag);

	void MakeBlockWidth(Vec2 pos, float width, int tag);
	void MakeBlockHeight(Vec2 pos, float height, int tag);

	Sprite* CreateRedBlock(Vec2);
	Sprite* CreateRedBlock(Vec2, float);
	// 주인공 옵션
	Label* m_HeroPos;
	void MakeHeroPos();
	void LookHeroPos();

	//레이어 획득구간
	Layer* m_Layer;
	void GetLayer(Layer*);
};

#endif 