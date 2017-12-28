#include "PersonalAudioEngine.h"
#include "FishJoyData.h"
USING_NS_CC;
static PersonalAudioEngine *_sharedEngine=NULL;
PersonalAudioEngine* PersonalAudioEngine::getInstance()
{
	if(_sharedEngine==NULL)
	{
		_sharedEngine=new PersonalAudioEngine;
		_sharedEngine->init();

	}
	return _sharedEngine;
}
void PersonalAudioEngine::destoryIntance()
{
	//delete _sharedEngine;
	//_sharedEngine=NULL;
	CC_SAFE_DELETE(_sharedEngine);
}
PersonalAudioEngine::PersonalAudioEngine()
{
}
PersonalAudioEngine::~PersonalAudioEngine()
{
}
bool PersonalAudioEngine::init()
{
	this->preloadBackgroundMusic("music_1.mp3");
	this->preloadBackgroundMusic("music_2.mp3");
	this->preloadBackgroundMusic("music_3.mp3");
	this->preloadEffect("bgm_button.aif");
	this->preloadEffect("bgm_fire.aif");
	this->preloadEffect("bgm_net.mp3");
	

	this->setBackgroundMusicVolume(FishJoyData::getInstance()->getIsMusic());
	this->setEffectsVolume(FishJoyData::getInstance()->getIsSound());

	return true;
}
void PersonalAudioEngine::playBackgroundMusic(int type)
{
	CCString *fileName =CCString::createWithFormat("music_%d.mp3",type);
	SimpleAudioEngine::playBackgroundMusic(fileName->getCString());
}
void PersonalAudioEngine::playEffect(EffectType type)
{
	switch(type)
	{
	case kEffectFishNet:
		SimpleAudioEngine::playEffect("bgm_net.mp3");
		break;
	case kEffectShoot:
		SimpleAudioEngine::playEffect("bgm_fire.aif");
		break;
	case kEffectSwichCannon: 
		SimpleAudioEngine::playEffect("bgm_button.aif");
		break;
	}
}

void PersonalAudioEngine::setBackgroundMusicVolume(float volume){

	SimpleAudioEngine::setBackgroundMusicVolume(volume);//调整音量大小
	FishJoyData::getInstance()->setIsMusic(volume);//写入文档记住
}
void PersonalAudioEngine::setEffectsVolume(float volume){
	SimpleAudioEngine::setEffectsVolume(volume);//调整音量大小
	FishJoyData::getInstance()->setIsSound(volume);//写入文档记住
}