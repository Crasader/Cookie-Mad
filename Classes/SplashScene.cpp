#include "SplashScene.h"
#include "MenuScene.h"

Scene* SplashScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SplashScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	///
	/// background
	///
	auto slashSprite = Sprite::create("normal/tableclothes_game.jpg");
	float iw = slashSprite->getContentSize().width;
	float ih = slashSprite->getContentSize().height;

	float sw = Director::getInstance()->getVisibleSize().width;
	float sh = Director::getInstance()->getVisibleSize().height;

	float kx = Director::getInstance()->getVisibleSize().width / slashSprite->getContentSize().width;
	float ky = Director::getInstance()->getVisibleSize().height / slashSprite->getContentSize().height;
	SceneManager::Instance()->setScale(kx,ky);
	
	slashSprite->setScaleX(kx);
	slashSprite->setScaleY(ky);

	slashSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(slashSprite, 0);
	///
	/// end background
	///

	/// 
	// logo
	///
	auto logoSprite = Sprite::create("normal/splash_icon.png");
	logoSprite->setScaleX(kx);
	logoSprite->setScaleY(ky);
	logoSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.65 + origin.y));
	this->addChild(logoSprite, 1);
	/// 
	// end logo
	///

	/// 
	//  gameNameSprite
	///
	auto gameNameSprite = Sprite::create("normal/cokies_mad.png");
	gameNameSprite->setScaleX(kx);
	gameNameSprite->setScaleY(ky);
	gameNameSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.4 + origin.y));
	this->addChild(gameNameSprite, 2);
	/// 
	// end gameNameSprite
	///

	this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), 0);
	return true;
}

void SplashScene::GoToMainMenuScene(float dt)
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/sound_bg.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/touch.wav");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sound_bg.mp3", true);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"sound/sound_bg.mp3", true);

	// check st here
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}



