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

bool TouchLayer::init()//��ʼ������
{
	if(!CCLayer::init())
	{
		return false;
	}

	setTouchEnabled(true);

	return true;
}

bool TouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)//�ض��������麯�����ض��������麯��
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonAimAt(target);
	return true;
}

void TouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)//�������ƶ�ʱ�������¼�
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonAimAt(target);
}

void TouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)//��������ʱ�������¼�
{
	GameScene* gameScene = getGameScene();
	CCPoint target = pTouch->getLocation();
	gameScene->cannonShootTo(target);
}

GameScene* TouchLayer::getGameScene()//�����Ϸ������ָ��
{
	return (GameScene*)getParent();
}