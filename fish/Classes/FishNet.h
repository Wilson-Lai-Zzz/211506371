#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define _FishNet_H

class FishNet :
	public CCNode
{
public:
	FishNet(void);
	virtual ~FishNet(void);
	CREATE_FUNC(FishNet);
	bool init();
	void showAt(CCPoint pos,int type = 0);//展开渔网的面积
	CCRect getCollisionArea();
protected:
	float getSpeed(int type);//设置速度
	CCSprite* _fishNetSprite;//渔网的图片精灵
};
