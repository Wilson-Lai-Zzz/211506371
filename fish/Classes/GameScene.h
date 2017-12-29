#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "FishLayer.h"
#include "MenuLayer.h"
#include "CannonLayer.h"
#include "TouchLayer.h"
#include "Fish.h"
#include "PanelLayer.h"
#include "FishJoyData.h"
#include "GoldCounterLayer.h"
#include "PersonalAudioEngine.h"
USING_NS_CC;
typedef enum{
	k_Operate_Pause = 0,
	k_Operate_Resume
}OperateFlag;
class GameScene :
	public CCScene
{
public:
	GameScene(void);
	CREATE_FUNC(GameScene)
	virtual bool init();
	virtual ~GameScene();
	void cannonAimAt(CCPoint target);
	void cannonShootTo(CCPoint target);
	void alterGold(int delta);
	void onEnter();
	void pause();
	void operateAllSchedulerAndActions(CCNode* node, OperateFlag flag);
	void Resume();
	void transToMainMenu();
protected:
	BackgroundLayer* _backgroundLayer;
	FishLayer* _fishLayer;
	MenuLayer* _menuLayer;
	CannonLayer* _cannonLayer;
	TouchLayer* _touchLayer;
	PanelLayer* _paneLayer;
	int i = 0;
	//GoldCounterLayer* alterGold;

	void preloadResources(void);
	bool checkOutCollisionBetweenFishesAndBullet(Bullet* bullet);
	void checkOutCollision();
	virtual void update(float delta);
	void fishWillBeCaught(Fish* fish);
	void checkOutCollisionBetweenFishesAndFishingNet(Bullet* bulet);
};

