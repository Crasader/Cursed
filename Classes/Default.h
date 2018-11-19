#pragma once

#include"cocosMacro.h"

// ī�޶� On/Off
#define CameraVisible false

// �浹�ڽ� On/Off
#define ColiideRect false

// �ִϸ��̼� ������
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

// �̱��� ���̽�
#include "singletonBase.h"

// ���� ���̽�
#include "ShadowLayer.h"

// STL Header ����
#include <vector>
#include <string>

// ���ҽ�, Ÿ�̸�, ����, ī�޶�, ��Ÿ��� ���
#include "LabelTypingEffect.h"
#include "Function.h"
#include "CameraControl.h"
#include "SourceManager.h"
#include "Timer.h"
#include "soundManager.h"
#include "ActionShake.h"

// ��ֹ� ������Ʈ
#include "ObjectBarrier.h"
#include "BarrierManager.h"

// źȯ Ŭ����
#include "BulletClass.h" // -> ��� ź�������� �̳༮�� �����
#include "BulletManager.h"

// ����Ʈ �Ŵ���
#include "EffectManager.h"

// ���� �Ŵ��� ( ��� ���� )
#include "Weapon.h"
#include "WeaponManager.h"

// �� �Ŵ��� ( �� ��� ���� )
#include "ShieldManager.h"

// �ƾ��� + �����۸Ŵ���
#include "ObjectItem.h"
#include "ItemManager.h"

// �� + �� �Ŵ��� + ������
#include "Boss.h"
#include "ObjectEnemy.h"
#include "MiniEnemy.h"
#include "EnemyManager.h"

// �޸�Ǯ
#include "MemoryPool.h"

// ���� UI
#include "GameUI.h"

// ���ΰ�
#include "ObjectHero.h"

// Ʃ�丮�� ��������
#include "Tutorial.h"

// �������� 1_1
#include "Stage1_1Loading.h"
#include "Stage1_1.h"

// �������� 1_2
#include "Stage1_2Loading.h"
#include "Stage1_2.h"

//�������� 1_3
#include "Stage1_3Loading.h"
#include "Stage1_3.h"

//�������� 2_1
#include "Stage2_1Loading.h"
#include "Stage2_1.h"

//�������� 2_2
#include "Stage2_2Loading.h"
#include "Stage2_2.h"

//�������� 2_3
#include "Stage2_3Loading.h"
#include "Stage2_3.h"

// �������� 1(������Ÿ��)
#include "Stage01.h"

// �޴� ��
#include "MenuScene.h"

// �ΰ� ��
#include "LogoScene.h"

// �ε���
#include "LoadingScene.h"
#pragma once
