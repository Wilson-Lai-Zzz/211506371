#include "Cannon.h"
#include <cmath>
USING_NS_CC;
using namespace std;

Cannon::Cannon(void)
{
}

Cannon::~Cannon(void)
{
}

Cannon* Cannon::create(CannonType type)
{
	Cannon* cannon = new Cannon();
	if(cannon && cannon->init(type))//cannon->init(type),完成炮台对象的动作初始化
	{
		cannon->autorelease();//将炮台对象加入内存池中，由引擎负责回收
		return cannon;
	}
	else//没创建成功就返回空
	{
		CC_SAFE_DELETE(cannon);
		return NULL;
	}
}

bool Cannon::init(CannonType type)
{
	if(!CCNode::init()){
		return false;
	}
	_cannonSprites = CCArray::createWithCapacity(k_Cannon_Count);//创建出一个容量为k_Cannon_Count的数组对象，封装炮台（7中）
	for(int i = k_Cannon_Type_1; i < k_Cannon_Count; i++)//存储炮台
	{	
		CCString* fileName = CCString::createWithFormat("actor_cannon1_%d1.png", i+1);//在资源文件中找到炮台的种类的图片（读取炮台图片）
		CCSprite* cannonSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());//将图片设置为精灵对象，并设置锚点
		_cannonSprites->addObject(cannonSprite);//将精灵存入数组
		cannonSprite->setAnchorPoint(ccp(0.5,0.18));//设置炮台的锚点坐标
	}
	CC_SAFE_RETAIN(_cannonSprites);//将封装派台的数组保存下来，不然会被回收池给回收掉
	setType(type);//将类型保存到数据成员中
	return true;
}

CannonType Cannon::getType()
{
	return _type;
}

void Cannon::setType(CannonType var)//根据传入参数type设置炮台类型
{
	if(_type == var)
	{
		return;
	}
	if(var < k_Cannon_Type_1)//对于类型小鱼0是，下标溢出，进行循环回下一种
	{
		var = (CannonType)(k_Cannon_Count-1);
	}else if(var >= k_Cannon_Count)//对于类型大于等于7，的进行循环
	{
		var = k_Cannon_Type_1;
	}
	removeChildByTag(_type);
	CCSprite* sprite = (CCSprite*) _cannonSprites->objectAtIndex(var);
	addChild(sprite,0,var);//将新的炮台节点加到本节点中
	_type = var;
}

CCSize Cannon::getSize()
{
	CCSprite* cannonSprite = (CCSprite*) _cannonSprites->objectAtIndex(_type);
	return cannonSprite->getContentSize();
}
float Cannon::getFireRange()//根据炮台的类型计算出炮台的射程
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	double temp = pow(winSize.width/2, 2) + pow(winSize.height, 2);
	double result = sqrt(temp);
	return result/7*(_type+1);
}

void Cannon::aimAt(CCPoint target)//让炮口对准鼠标点击的方向
{

	//target：用户在屏幕触摸的位置
	if(target.y < 0)//防止旋转360度
	{
		target.y = 0.0f;
	}
	CCPoint location = getParent()->convertToWorldSpace(getPosition());
	float angle = ccpAngleSigned(ccpSub(target, location), CCPointMake(0, 1));
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
}
