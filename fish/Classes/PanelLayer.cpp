#include "PanelLayer.h"
#include "GameScene.h"
#include "ScheduleCountDown.h"
USING_NS_CC;
PanelLayer::PanelLayer(void)
{

}

PanelLayer::~PanelLayer(void)
{

}
bool PanelLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	_goldCounter = GoldCounterLayer::create(0);//创建积分器
	addChild(_goldCounter);
	_goldCounter->setPosition(ccp(1600, 25));//分数计数器的位置
	
	int maxTime =60;//送分倒计时
	ScheduleCountDown *countDown =ScheduleCountDown::create(this,maxTime,true);
	addChild(countDown,0, 99);
	_scheduleLabel=CCLabelAtlas::create(CCString::createWithFormat("%d",maxTime)->getCString(),"baoshiyu_shuzi_02-ipadhd.png",50,54,'0');//创计时器
	addChild(_scheduleLabel);
	_scheduleLabel->setPosition(ccp(1600, 1200));//倒计时位置


	CCSize winSize = CCDirector::sharedDirector()->getWinSize();//获取到应用程序的窗口大小
	
	CCMenuItemSprite* pause = CCMenuItemSprite::create(CCSprite::create("112913569on.png"),
		CCSprite::create("11291356off.png"),
		this, menu_selector(PanelLayer::pause));

	CCMenu* menu = CCMenu::create(pause, NULL);
	this->addChild(menu);
	CCSize pauseSize = pause->getContentSize();
	menu->setPosition(CCPointMake(100, winSize.height-60));//暂停键位置


    return true;
}
void PanelLayer::scheduleTimeUp()
{
	((GameScene *)getParent())->alterGold(200);
	ScheduleCountDown *countDown =(ScheduleCountDown *)getChildByTag(99);
	if(countDown->getLoop()==false)
	{
		_scheduleLabel->setVisible(false);
	}
}
void PanelLayer::setScheduleNumber(int number)
{
	//CCLabelAtlas *label =(CCLabelAtlas *)getChildByTag(99);
	_scheduleLabel->setString(CCString::createWithFormat("%d",number)->getCString());
}
void PanelLayer::pause(CCObject *sender)
{

		GameScene* gameScene = (GameScene*)this->getParent();
		gameScene->pause();
	
	
	
	
}