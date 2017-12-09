#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define _BULLET_H

class Bullet :
	public CCNode
{
public:
	Bullet(void);
	virtual ~Bullet(void);
	CREATE_FUNC(Bullet);
	bool init();
	void end();
	void flyTo(CCPoint targetInWorldSpace, int type/* =0 */);
	CCPoint getCollosionPoint();//得到碰撞点
protected:
	float getSpeed(int type);//得到速度，不同炮台有不同速度
	CCSprite* _bulletSprite;//子弹精灵
};
