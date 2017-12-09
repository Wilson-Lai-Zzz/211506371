#include "Weapon.h"

#define BULLET_COUNT 10

Weapon* Weapon::create(CannonType type)
{
	Weapon* weapon = new Weapon();
	if(weapon && weapon->init(type))
	{
		weapon->autorelease();//)将对象加入对象池中
		return weapon;
	}
	else
	{
		CC_SAFE_DELETE(weapon); 
		return NULL;
	}
}

bool Weapon::init(CannonType type)
{
	do
	{
		CC_BREAK_IF(!CCNode::init());
		_cannon = Cannon::create(type);
		CC_BREAK_IF(!_cannon);
		addChild(_cannon, 1);
		
		_bullets = CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_bullets);
		CC_SAFE_RETAIN(_bullets);
		
		_fishNets=CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_fishNets);
		CC_SAFE_RETAIN(_fishNets);

		_particils = CCArray::createWithCapacity(BULLET_COUNT);
		CC_BREAK_IF(!_particils);
		CC_SAFE_RETAIN(_particils);
		
		for(int i = 0; i < BULLET_COUNT; i++)
		{
			Bullet* bullet = Bullet::create();
			_bullets->addObject(bullet);
			addChild(bullet);
			bullet->setVisible(false);
			
			FishNet* fishNet = FishNet::create();
			_fishNets->addObject(fishNet);
			addChild(fishNet);
			fishNet->setVisible(false);
			bullet->setUserObject(fishNet);

			CCParticleSystemQuad* particle = CCParticleSystemQuad::create("yuwanglizi.plist");
			particle->stopSystem();
			addChild(particle);
			_particils->addObject(particle);
			fishNet->setUserObject(particle);
		}
		return true;
	}while(0);

	return false;
}

CCSize Weapon::getCannonSize()
{
	return _cannon->getSize();
}

CannonType Weapon::getCannonType()
{
	return _cannon->getType();
}

void Weapon::changeCannon(CannonOperate operate)//变换炮台
{
	int type = (int) _cannon->getType();
	type += operate;
	_cannon->setType((CannonType)type);
}

Weapon::~Weapon(void)
{
	CC_SAFE_RELEASE(_bullets);
	CC_SAFE_RELEASE(_fishNets);
	CC_SAFE_RELEASE(_particils);
}

void Weapon::aimAt(CCPoint target)//旋转炮台，让炮口对准targe的方向
{
	_cannon->aimAt(target);
}

void Weapon::shootTo(CCPoint target)//子弹对准targe的方向
{

	//tget：用户在屏幕触摸的位置
	Bullet* bullet= getBulletToShoot();
	if(!bullet) return;
	CCPoint pointWorldSpace = getParent()->convertToWorldSpace(getPosition());
	float distance = ccpDistance(target, pointWorldSpace);
	if(distance > _cannon->getFireRange())
	{
		CCPoint normal = ccpNormalize(ccpSub(target, pointWorldSpace));
		CCPoint mult = ccpMult(normal, _cannon->getFireRange());
		target = ccpAdd(pointWorldSpace, mult);
	}
	bullet->flyTo(target, _cannon->getType());//发射子弹
}

Bullet* Weapon::getBulletToShoot()
{
	CCObject* obj;
	CCARRAY_FOREACH(_bullets, obj)
	{
		Bullet* bullet = (Bullet*)obj;
		if(!bullet->isVisible())
		{
			return bullet;
		}
	}
	return NULL;
}

CCRect Weapon::getCollisionArea(Bullet* bullet)
{
	FishNet* _fishNets = (FishNet*)bullet->getUserObject();
	if(_fishNets->isVisible())
	{
		return _fishNets->getCollisionArea();
	}
	return CCRectZero;
}
