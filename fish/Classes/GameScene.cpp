#include "GameScene.h"
//#include "FishJoyData.h"
GameScene::GameScene()
{
}

bool GameScene::init()//添加各个层
{
	do
	{
		CC_BREAK_IF(!CCScene::init());
		preloadResources();
		//因为~GameScene()中需要CC_SAFE_RELEASE(_menuLayer)， 如果其它层创建失败，_menuLayer将不创建，
		//所以_menuLayer要先于其他层创建， 否则将报 "reference count greater than 0" 错误
		_menuLayer = MenuLayer::create(); 
		CC_BREAK_IF(!_menuLayer);
		CC_SAFE_RETAIN(_menuLayer); 


		_backgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(!_backgroundLayer);
		this->addChild(_backgroundLayer);


		_fishLayer = FishLayer::create();
		CC_BREAK_IF(!_fishLayer);
		this->addChild(_fishLayer);


		_cannonLayer = CannonLayer::create();
		CC_BREAK_IF(!_cannonLayer);
		this->addChild(_cannonLayer);


		_touchLayer = TouchLayer::create();
		CC_BREAK_IF(!_touchLayer);
		this->addChild(_touchLayer);


		_paneLayer = PanelLayer::create();
		CC_BREAK_IF(!_paneLayer);
		this->addChild(_paneLayer);

		_paneLayer->getGoldCounter()->setNumber(FishJoyData::getInstance()->getGold());
		this->scheduleUpdate();
		return true;
	} while (0);
	return false;
}

void GameScene::preloadResources(void)
{
	PersonalAudioEngine::getInstance();
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	//修改以下plist文件， 删除key中的中文， 否则spriteFrameByName函数无法找到Frame，将返回NULL
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Large-ipadhd.plist");		//修改metadata->realTextureFileName->FishActor-Large-ipadhdhd.png, textureFileName->FishActor-Large-ipadhd.png
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Marlin-ipadhd.plist");		//修改metadata->realTextureFileName->FishActor-Marlin-ipadhdhd.png, textureFileName->FishActor-Marlin-ipadhd.png
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Shark-ipadhd.plist");		//同上
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Small-ipadhd.plist");		//同上
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Mid-ipadhd.plist");			//同上
	spriteFrameCache->addSpriteFramesWithFile("cannon-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("Item-chaojiwuqi-ipadhd.plist");

	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	textureCache->addImage("ui_button_63-ipadhd.png");
	textureCache->addImage("ui_button_65-ipadhd.png");

	char str[][50] = { "SmallFish", "Croaker", "AngelFish", "Amphiprion", "PufferS", 
		"Bream", "Porgy", "Chelonian", "Lantern", "Ray", "Shark", "GoldenTrout", "GShark", 
		"GMarlinsFish", "GrouperFish", "JadePerch", "MarlinsFish", "PufferB" };
	for (int i = 0; i < 18; i++)
	{
		CCArray* array = CCArray::createWithCapacity(10);
		for (int j = 0; j < 10; j++)
		{
			CCString* spriteFrameName = CCString::createWithFormat("%s_actor_%03d.png", str[i], j + 1);
			CCSpriteFrame* spriteFrame = spriteFrameCache->spriteFrameByName(spriteFrameName->getCString());
			CC_BREAK_IF(!spriteFrame);
			array->addObject(spriteFrame);
		}
		if (array->count() == 0)
		{
			continue;
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 0.15f);
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", i + 1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, animationName->getCString());

		
		PersonalAudioEngine::sharedEngine();//音效资源的预加载
	}
	
}

GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_menuLayer);
}

void GameScene::cannonAimAt(CCPoint target)
{
	_cannonLayer->aimAt(target);
}

void GameScene::cannonShootTo(CCPoint target)
{
	int cost = _cannonLayer->getWeapon()->getCannonType() + 1;
	if (FishJoyData::getInstance()->getGold() >= cost)
	{
		_cannonLayer->shootTo(target);
		alterGold(-cost);
	}

	//_cannonLayer->shootTo(target);
}

bool GameScene::checkOutCollisionBetweenFishesAndBullet(Bullet* bullet)
{
	CCPoint bulletPos = bullet->getCollosionPoint();
	CCArray* fishArray = _fishLayer->getFishArray();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(fishArray, obj)
	{
		Fish* fish =(Fish*)obj;
		if(fish->isRunning() && fish->getCollisionArea().containsPoint(bulletPos))
		{
			bullet->end();
			return true;
		}
	}
	return false;
}

void GameScene::checkOutCollision()
{
	CCArray* bullets = _cannonLayer->getWeapon()->getBullets();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(bullets, obj)
	{
		Bullet* bullet = (Bullet*)obj;
		if(bullet->isVisible())
		{
			if(checkOutCollisionBetweenFishesAndBullet(bullet))
			{
				checkOutCollisionBetweenFishesAndFishingNet(bullet);
			}
		}
	}	
}

void GameScene::update(float delta)
{
	checkOutCollision();
}

void GameScene::fishWillBeCaught(Fish* fish)
{
	float weaponPercents[k_Cannon_Count] = { 0.3, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
	float fishPercents[	k_Fish_Type_Count] = { 1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4 };
	int _cannonType = _cannonLayer->getWeapon()->getCannonType();
	int _fishType = fish->getType();
	float percentage =(float)_cannonType * _fishType;
	if(CCRANDOM_0_1() < percentage)//1.1
	{
		fish->beCaught();
		//
		int reward = STATIC_DATA_INT(CCString::createWithFormat(STATIC_DATA_STRING("reward_format"),_fishType)->getCString());
		alterGold(reward);
		//
	}
	
}

void GameScene::checkOutCollisionBetweenFishesAndFishingNet(Bullet* bullet)
{
	Weapon* weapon = _cannonLayer->getWeapon();
	CCRect rect = weapon->getCollisionArea(bullet);
	CCArray* fishArray = _fishLayer->getFishArray();
	CCObject* obj = NULL;
	CCARRAY_FOREACH(fishArray, obj)
	{
		Fish* fish = (Fish*)obj;
		if(fish->isRunning() && rect.intersectsRect(fish->getCollisionArea()))
		{
			fishWillBeCaught(fish);
		}
	}
}
void GameScene::alterGold(int delta)
{
	FishJoyData* _fishJoyData = FishJoyData::getInstance();
	_fishJoyData->alterGold(delta);
	_paneLayer->getGoldCounter()->setNumber(_fishJoyData->getGold());
}
void GameScene::onEnter()
{
	CCScene::onEnter();
	PersonalAudioEngine::getInstance()->playBackgroundMusic(3);
}
void GameScene::pause()//暂停
{
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	PersonalAudioEngine::sharedEngine()->playEffect("bgm_button.aif");
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);
	_touchLayer->setTouchEnabled(false);
	this->addChild(_menuLayer);
}
void GameScene::operateAllSchedulerAndActions(CCNode* node, OperateFlag flag)
{
	if (node->isRunning()){
		switch (flag) {
		case k_Operate_Pause:
			node->pauseSchedulerAndActions();
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;
		}
		CCArray* array = node->getChildren();
		if (array != NULL && array->count()>0){
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

void GameScene::Resume()//重新开始
{
	this->operateAllSchedulerAndActions(this, k_Operate_Resume);
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->removeChild(_menuLayer, false);
	_touchLayer->setTouchEnabled(true);
}