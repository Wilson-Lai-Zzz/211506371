#include "CannonLayer.h"

CannonLayer::CannonLayer(void)
{
}

CannonLayer::~CannonLayer(void)
{
}

bool CannonLayer::init()//初始化操作，用来显示炮台和相应的菜单项
{
	if(!CCLayer::init())
	{
		return false;
	}
	_weapon = Weapon::create((CannonType)0);
	addChild(_weapon,1);
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	_weapon->setPosition(ccp(winSize.width/2 - 18, 0));

	_addMenuItem = CCMenuItemImage::create(
		"ui_button_65-ipadhd.png",
		"ui_button_65-ipadhd.png",
		this,menu_selector(CannonLayer::switchCannonCallback));

	_subMenuItem = CCMenuItemImage::create(
		"ui_button_63-ipadhd.png",
		"ui_button_63-ipadhd.png",
		this,menu_selector(CannonLayer::switchCannonCallback));

	CCMenu* menu = CCMenu::create(_subMenuItem, _addMenuItem, NULL);
	menu->alignItemsHorizontallyWithPadding(120);
	addChild(menu,0);
	menu->setPosition(ccp(winSize.width/2-20, _addMenuItem->getContentSize().height/2));
	return true;
}

void CannonLayer::switchCannonCallback(cocos2d::CCObject* sender)//切换当前的炮台类型
{
	CannonOperate operate = k_Cannon_Operate_Up;
	if((CCMenuItemImage*)sender == _subMenuItem)//如果sender是_subMenuItem,表示类型减一
	{
		operate = k_Cannon_Operate_Down;
	}
	_weapon->changeCannon(operate);

}

void CannonLayer::aimAt(CCPoint target)//让炮口对准targe的方向
{
	_weapon->aimAt(target);//旋转炮台
}

void CannonLayer::shootTo(CCPoint target)//子弹对准targe的方向
{
	_weapon->shootTo(target);//发射子弹
}
