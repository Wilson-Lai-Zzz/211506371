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
	void setSoundAndMusicVolume(float soundVolume, float musicVolume);//设置背景音乐和音效按钮对应菜单项的开关状态。soundVolume：音效的音量,musicVolume：背景音乐的音量。

private:
	
	void createMenu();//创建菜单
	void createBackground();//创建出菜单的背景层

	void resume(cocos2d::CCObject* pSender);//恢复游戏
	void mainMenu(cocos2d::CCObject* pSender);//切换到游戏主菜单场景
	void sound(cocos2d::CCObject* pSender);//音效的关闭和开启
	void music(cocos2d::CCObject* pSender);//背景音乐的关闭和开启
	void reset(cocos2d::CCObject* pSender);//重设游戏

	cocos2d::CCMenuItemToggle* _sound;
	cocos2d::CCMenuItemToggle* _music;
};

