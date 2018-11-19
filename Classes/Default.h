#pragma once

#include"cocosMacro.h"

// 카메라 On/Off
#define CameraVisible false

// 충돌박스 On/Off
#define ColiideRect false

// 애니메이션 딜레이
#define DeathDelay 0.15f
#define RunDelay 0.04f
#define BasicAttackDelay 0.05f
#define IdleDelay 0.07f
#define JumpDelay 0.05f
#define LadderDelay 0.075f
#define WalkDelay 0.04f
#define FallDelay 0.05f
#define DashDelay 0.05f
#define LadderEndDelay 0.05f
#define BowAtkDelay 0.025f

enum MetaNum { Blue = 55, GreenL,GreenR, GreenEnd, Red, MonsterOnly };

// 싱글톤 베이스
#include "singletonBase.h"

// 조명 베이스
#include "ShadowLayer.h"

// STL Header 모음
#include <vector>
#include <string>

// 리소스, 타이머, 사운드, 카메라, 기타기능 등등
#include "LabelTypingEffect.h"
#include "Function.h"
#include "CameraControl.h"
#include "SourceManager.h"
#include "Timer.h"
#include "soundManager.h"
#include "ActionShake.h"

// 장애물 오브젝트
#include "ObjectBarrier.h"
#include "BarrierManager.h"

// 탄환 클래스
#include "BulletClass.h" // -> 모든 탄막생성은 이녀석이 담당함
#include "BulletManager.h"

// 이펙트 매니저
#include "EffectManager.h"

// 무기 매니저 ( 모션 관리 )
#include "Weapon.h"
#include "WeaponManager.h"

// 방어구 매니저 ( 방어구 모션 관리 )
#include "ShieldManager.h"

// 아아템 + 아이템매니저
#include "ObjectItem.h"
#include "ItemManager.h"

// 적 + 적 매니저 + 보스몹
#include "Boss.h"
#include "ObjectEnemy.h"
#include "MiniEnemy.h"
#include "EnemyManager.h"

// 메모리풀
#include "MemoryPool.h"

// 게임 UI
#include "GameUI.h"

// 주인공
#include "ObjectHero.h"

// 튜토리얼 스테이지
#include "Tutorial.h"

// 스테이지 1_1
#include "Stage1_1Loading.h"
#include "Stage1_1.h"

// 스테이지 1_2
#include "Stage1_2Loading.h"
#include "Stage1_2.h"

//스테이지 1_3
#include "Stage1_3Loading.h"
#include "Stage1_3.h"

//스테이지 2_1
#include "Stage2_1Loading.h"
#include "Stage2_1.h"

//스테이지 2_2
#include "Stage2_2Loading.h"
#include "Stage2_2.h"

//스테이지 2_3
#include "Stage2_3Loading.h"
#include "Stage2_3.h"

// 스테이지 1(프로토타입)
#include "Stage01.h"

// 메뉴 씬
#include "MenuScene.h"

// 로고 씬
#include "LogoScene.h"

// 로딩씬
#include "LoadingScene.h"
#pragma once
