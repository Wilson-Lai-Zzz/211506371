#include "TouchLayer.h"
#include "GameScene.h"

TouchLayer::TouchLayer(void)
{
}

TouchLayer::~TouchLayer(void)
{
}

void TouchLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector() -> getTouchDispatcher() -> addTargetedDelegate(this, 0, true);

}

bool TouchLayer::init()//初始化操作
{
	if(!CCLayer::init())
	{
		return false;
	}

	setTouchEnabled(true);

	return true;
}

bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)//重定义基类的虚函数，重定义基类的虚函数
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonAimAt(target);
	return true;
}

void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)//当触摸移动时触发的事件
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonAimAt(target);
}

void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)//触摸结束时触发的事件
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonShootTo(target);
}

GameScene* TouchLayer::getGameScene()//获得游戏场景的指针
{
	return (GameScene*)getParent();
}