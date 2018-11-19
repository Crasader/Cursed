#include "AppDelegate.h"
#include "Default.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() 
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		// 창모드
		glview = GLViewImpl::createWithRect("Cursed", cocos2d::Rect(0, 0, 1920, 1080));
		// 전체화면모드
		//glview = GLViewImpl::createWithFullScreen("Cursed"); // 전체화면 모드
#else
		glview = GLViewImpl::create("Prototype");
#endif
		director->setOpenGLView(glview);
	}

	director->setAnimationInterval(1.0 / 60);
	glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::EXACT_FIT);
	director->setDisplayStats(false);
	register_all_packages();

	director->runWithScene(LogoScene::createScene());

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

}
