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
	if(cannon && cannon->init(type))//cannon->init(type),�����̨����Ķ�����ʼ��
	{
		cannon->autorelease();//����̨��������ڴ���У������渺�����
		return cannon;
	}
	else//û�����ɹ��ͷ��ؿ�
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
	_cannonSprites = CCArray::createWithCapacity(k_Cannon_Count);//������һ������Ϊk_Cannon_Count��������󣬷�װ��̨��7�У�
	for(int i = k_Cannon_Type_1; i < k_Cannon_Count; i++)//�洢��̨
	{	
		CCString* fileName = CCString::createWithFormat("actor_cannon1_%d1.png", i+1);//����Դ�ļ����ҵ���̨�������ͼƬ����ȡ��̨ͼƬ��
		CCSprite* cannonSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());//��ͼƬ����Ϊ������󣬲�����ê��
		_cannonSprites->addObject(cannonSprite);//�������������
		cannonSprite->setAnchorPoint(ccp(0.5,0.18));//������̨��ê������
	}
	CC_SAFE_RETAIN(_cannonSprites);//����װ��̨�����鱣����������Ȼ�ᱻ���ճظ����յ�
	setType(type);//�����ͱ��浽���ݳ�Ա��
	return true;
}

CannonType Cannon::getType()
{
	return _type;
}

void Cannon::setType(CannonType var)//���ݴ������type������̨����
{
	if(_type == var)
	{
		return;
	}
	if(var < k_Cannon_Type_1)//��������С��0�ǣ��±����������ѭ������һ��
	{
		var = (CannonType)(k_Cannon_Count-1);
	}else if(var >= k_Cannon_Count)//�������ʹ��ڵ���7���Ľ���ѭ��
	{
		var = k_Cannon_Type_1;
	}
	removeChildByTag(_type);
	CCSprite* sprite = (CCSprite*) _cannonSprites->objectAtIndex(var);
	addChild(sprite,0,var);//���µ���̨�ڵ�ӵ����ڵ���
	_type = var;
}

CCSize Cannon::getSize()
{
	CCSprite* cannonSprite = (CCSprite*) _cannonSprites->objectAtIndex(_type);
	return cannonSprite->getContentSize();
}
float Cannon::getFireRange()//������̨�����ͼ������̨�����
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	double temp = pow(winSize.width/2, 2) + pow(winSize.height, 2);
	double result = sqrt(temp);
	return result/7*(_type+1);
}

void Cannon::aimAt(CCPoint target)//���ڿڶ�׼������ķ���
{

	//target���û�����Ļ������λ��
	if(target.y < 0)//��ֹ��ת360��
	{
		target.y = 0.0f;
	}
	CCPoint location = getParent()->convertToWorldSpace(getPosition());
	float angle = ccpAngleSigned(ccpSub(target, location), CCPointMake(0, 1));
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
}
