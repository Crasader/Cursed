#pragma once

#include "cocos2d.h"
#pragma execution_character_set("utf-8")
USING_NS_CC;

#define TRUE true
#define FALSE false

// DelayTime + Sequence 매크로함수
#define RUN_WITH_DELAY(delay, func) Director::getInstance()->getRunningScene()->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create(func), nullptr))

//씬전환
#define replaceSceneTransitionFadeOut(classType)\
do {\
stopAllActions();\
unscheduleAllSelectors();\
Scene *scene = Scene::create();\
classType *layer = classType::create();\
scene->addChild(layer);\
Director::sharedDirector()->replaceScene(TransitionFade::create(1.0, scene, ccc3(0, 0, 0)));\
}\
while(false)

//스테이지1_3 엘리트보스 치트
#define Stage1_3Elite false

//주인공 무기 Damage
#define BowDamage 15
#define KnifeDamage 10

//적 애니메이션 Delay
#define M1RunDly 0.05f
#define M1AttackDly 0.03f
#define M1IdleDly 0.05f
#define M1DieDly 0.05f
#define M1HitDly 0.05f

#define M2RunDly 0.05f
#define M2AttackDly 0.05f
#define M2IdleDly 0.05f
#define M2DieDly 0.05f
#define M2HitDly 0.05f

//무당벌레
#define BugRunDly 0.025f
#define BugUnburrowDly 0.04f
#define BugAttackDly 0.025f

//폭탄벌레
#define BombMoveDly 0.05f

//엘리트보스
#define EliteIdleDly 0.05f
#define EliteRunDly 0.01f
#define EliteHowlingDly 0.05f
#define EliteAttack2Dly 0.04f
#define EliteAttack1Dly 0.05f
#define EliteAttack3Dly 0.02f
#define EliteHitDly 0.05f
#define EliteSkillDly 0.05f
#define EliteDeadDly 0.05f


//스테이지1 보스
#define Boss1IdleDly 0.05f
#define Boss1Atk1Dly 0.05f
#define Boss1Atk2Dly 0.05f
#define Boss1Atk3Dly 0.04f
#define Boss1Atk4Dly 0.05f
#define Boss1Atk5Dly 0.05f
#define Boss1HowlingDly 0.035f
#define Boss1Death 0.05f
#define Boss1Skill1 0.075f