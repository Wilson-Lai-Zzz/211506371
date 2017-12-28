#pragma once
#include "cocos2d.h"
USING_NS_CC;

class MenuLayer :
	public CCLayer
{
public:
	MenuLayer(void);
	CREATE_FUNC(MenuLayer)
	virtual bool init();
	virtual ~MenuLayer(void);
	void setSoundAndMusicVolume(float soundVolume, float musicVolume);//���ñ������ֺ���Ч��ť��Ӧ�˵���Ŀ���״̬��soundVolume����Ч������,musicVolume���������ֵ�������

private:
	
	void createMenu();//�����˵�
	void createBackground();//�������˵��ı�����

	void resume(cocos2d::CCObject* pSender);//�ָ���Ϸ
	void mainMenu(cocos2d::CCObject* pSender);//�л�����Ϸ���˵�����
	void sound(cocos2d::CCObject* pSender);//��Ч�ĹرպͿ���
	void music(cocos2d::CCObject* pSender);//�������ֵĹرպͿ���
	void reset(cocos2d::CCObject* pSender);//������Ϸ

	cocos2d::CCMenuItemToggle* _sound;
	cocos2d::CCMenuItemToggle* _music;
};

