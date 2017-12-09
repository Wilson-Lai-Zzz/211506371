#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define _CANNON_H
//枚举炮塔种类
typedef enum{
	k_Cannon_Type_1 = 0,
	k_Cannon_Type_2,
	k_Cannon_Type_3,
	k_Cannon_Type_4,
	k_Cannon_Type_5,
	k_Cannon_Type_6,
	k_Cannon_Type_7,
	k_Cannon_Count,
	k_Cannon_Invalid,
}CannonType;

typedef enum{
	k_Cannon_Operate_Up = 1,
	k_Cannon_Operate_Down = -1
}CannonOperate;

class Cannon :
	public CCNode
{
public:
	Cannon(void);
	static Cannon* create(CannonType type = k_Cannon_Type_1);//创建炮台
	bool init(CannonType type = k_Cannon_Type_1);//设定炮台的类型，并将各种炮台的精灵加入数组中
	CCSize getSize();//得到炮塔台大小
	float getFireRange();//炮台的攻击范围
	CC_PROPERTY(CannonType, _type, Type);
	virtual ~Cannon(void);
	void aimAt(CCPoint target);//瞄准，炮台随着鼠标位置瞄准
protected:
	CCArray* _cannonSprites;
};
