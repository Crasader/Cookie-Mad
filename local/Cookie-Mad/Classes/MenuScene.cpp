#include "MenuScene.h"
#include "GameSceneMap3.h"
#include "GameSceneMap4.h"
#include "GameSceneMap5.h"

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	layer->setKeypadEnabled(true);
#endif
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	SceneManager::Instance()->setInfoDb();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////
	// menu bg
	/////
	auto bgSprite = Sprite::create("normal/tableclothes_menu.jpg");

	// position the sprite on the center of the screen
	bgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bgSprite->setScaleX(SceneManager::Instance()->getXScale());
	bgSprite->setScaleY(SceneManager::Instance()->getYScale());

	// add the sprite as a child to this layer
	this->addChild(bgSprite, 0);
	/////
	// end menu bg
	/////



	float scaleMap = 1;
	/// 
	/// button map 3
	///
	auto map3Button = cocos2d::ui::Button::create();
	map3Button->setTouchEnabled(true);
	map3Button->loadTextures("normal/coki_3.png", "normal/coki_3_click.png", "");

	if (map3Button->getContentSize().height * SceneManager::Instance()->getYScale() > visibleSize.height * 0.3)
	{
		scaleMap = visibleSize.height * 0.3 / map3Button->getContentSize().height;
	}
	else
	{
		scaleMap = SceneManager::Instance()->getYScale();
	}
	map3Button->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.833));
	map3Button->addTouchEventListener(CC_CALLBACK_2(MenuScene::touchMap3Event, this));
	map3Button->setScale(scaleMap, scaleMap);
	this->addChild(map3Button, 1);
	if (SceneManager::Instance()->getScoreMapOrLock(MAP_3) > 0)
	{
		char szScore[20] = { 0 };
		sprintf(szScore, " x %d", SceneManager::Instance()->getScoreMapOrLock(MAP_3));
		auto lblScore3 = Label::createWithTTF(szScore, "fonts/SAF.otf", 48 * SceneManager::Instance()->getYScale());
		lblScore3->setColor(Color3B::BLACK);
		lblScore3->setPosition(Vec2(
			map3Button->getPositionX() - map3Button->getContentSize().width * 0.38 * SceneManager::Instance()->getXScale() + 0.5 * lblScore3->getContentSize().width
			,
			map3Button->getPositionY() - map3Button->getContentSize().height * 0.45 * SceneManager::Instance()->getYScale() + 0.5 * lblScore3->getContentSize().height));
		this->addChild(lblScore3, 2);
	}

    /// sound-music button -> 1 : music 2: sound -> no : 0
    // 0 : no music no sound ; 1 : music ; 2 : sound ; 3 : music + sound
    
    musicBtt = cocos2d::ui::Button::create();
    musicBtt->setTouchEnabled(true);
    if(SceneManager::Instance()->isGoodMusic())
        musicBtt->loadTextures("normal/music_btt.png", "normal/music_btt_click.png", "");
    else
        musicBtt->loadTextures("normal/no_music_btt.png", "normal/no_music_btt_click.png", "");
    
    musicBtt->setScale(scaleMap, scaleMap);
    float posSoundY = map3Button->getPositionY() + map3Button->getContentSize().height * 0.5 * SceneManager::Instance()->getYScale() - musicBtt->getContentSize().height * 0.5 * SceneManager::Instance()->getYScale();
    float posBienSoundX = map3Button->getPositionX() + map3Button->getContentSize().height * 0.5 * SceneManager::Instance()->getYScale();
    float deltaSoundX = 0.333 * ( visibleSize.width - posBienSoundX );
    float posSoundX = visibleSize.width - deltaSoundX - musicBtt->getContentSize().width * 0.5 * SceneManager::Instance()->getXScale();
    musicBtt->setPosition(Point(posSoundX,posSoundY));
    musicBtt->addTouchEventListener(CC_CALLBACK_2(MenuScene::musicEvent  , this));
    this->addChild(musicBtt, 71);
    
    
//    musicBtt = cocos2d::ui::Button::create();
//    musicBtt->setTouchEnabled(true);
//    musicBtt->loadTextures("normal/music_btt.png", "normal/music_btt_click.png", "");
//    musicBtt->setScale(scaleMap, scaleMap);
//    float posMusicY = posSoundY - soundBtt->getContentSize().height * SceneManager::Instance()->getYScale();
//    musicBtt->setPosition(Point(posSoundX,posMusicY));
//    musicBtt->addTouchEventListener(CC_CALLBACK_2(MenuScene::musicEvent , this));
//    this->addChild(musicBtt, 72);
    
    ///
    
	/// 
	/// button map 4
	///
	auto map4Button = cocos2d::ui::Button::create();
	map4Button->setTouchEnabled(true);
	if (SceneManager::Instance()->getScoreMapOrLock(MAP_4) == -1)
	{
		map4Button->loadTextures("normal/coki_4_lock.png", "", "");
	}
	else
	{
		map4Button->loadTextures("normal/coki_4.png", "normal/coki_4_click.png", "");	
		map4Button->addTouchEventListener(CC_CALLBACK_2(MenuScene::touchMap4Event, this));
	}
	map4Button->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.5));
	map4Button->setScale(scaleMap, scaleMap);
	this->addChild(map4Button, 3);
	if (SceneManager::Instance()->getScoreMapOrLock(MAP_4) > 0)
	{
		char szScore[20] = { 0 };
		sprintf(szScore, " x %d", SceneManager::Instance()->getScoreMapOrLock(MAP_4));
		auto lblScore4 = Label::createWithTTF(szScore, "fonts/SAF.otf", 48 * SceneManager::Instance()->getYScale());
		lblScore4->setColor(Color3B::BLACK);
		lblScore4->setPosition(Vec2(
			map4Button->getPositionX() - map4Button->getContentSize().width * 0.38 * SceneManager::Instance()->getXScale() 
			+ 0.5 * lblScore4->getContentSize().width
			,
			map4Button->getPositionY() - map4Button->getContentSize().height * 0.45 * SceneManager::Instance()->getYScale()
			+ 0.5 * lblScore4->getContentSize().height));
		this->addChild(lblScore4 , 4);
	}
	/// 
	/// button map 5
	///
	auto map5Button = cocos2d::ui::Button::create();
	map5Button->setTouchEnabled(true);
	if (SceneManager::Instance()->getScoreMapOrLock(MAP_5) == -1)
	{
		map5Button->loadTextures("normal/coki_5_lock.png", "", "");
	}
	else
	{
		map5Button->loadTextures("normal/coki_5.png", "normal/coki_5_click.png", "");
		map5Button->addTouchEventListener(CC_CALLBACK_2(MenuScene::touchMap5Event, this));
	}
	map5Button->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.166));
	map5Button->setScale(scaleMap, scaleMap);
	this->addChild(map5Button, 5);
	if (SceneManager::Instance()->getScoreMapOrLock(MAP_5) > 0)
	{
		char szScore[20] = { 0 };
		sprintf(szScore, " x %d", SceneManager::Instance()->getScoreMapOrLock(MAP_5));
		auto lblScore5 = Label::createWithTTF(szScore, "fonts/SAF.otf", 48 * SceneManager::Instance()->getYScale());
		lblScore5->setColor(Color3B::BLACK);
		lblScore5->setPosition(Vec2(
			map5Button->getPositionX() - map5Button->getContentSize().width * 0.38 * SceneManager::Instance()->getXScale() 
			+ 0.5 * lblScore5->getContentSize().width
			,
			map5Button->getPositionY() - map5Button->getContentSize().height * 0.45 * SceneManager::Instance()->getYScale()
			+ 0.5 * lblScore5->getContentSize().height));
		this->addChild(lblScore5, 6);
	}

	_testLbl = Label::createWithTTF("", "fonts/Marker Felt.ttf", 16 * SceneManager::Instance()->getYScale());
	_testLbl->setColor(Color3B::BLACK);
	_testLbl->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(_testLbl, 18);

	return true;
}

void MenuScene::touchMap3Event(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		SceneManager::Instance()->setAdvAvaiable();
		auto scene = GameSceneMap3::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
	}
}

void MenuScene::touchMap4Event(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		SceneManager::Instance()->setAdvAvaiable();
		auto scene = GameSceneMap4::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
	}
}

void MenuScene::touchMap5Event(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
	if (eEventType == ui::Widget::TouchEventType::ENDED)
	{
		SceneManager::Instance()->setAdvAvaiable();
		auto scene = GameSceneMap5::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
	}
}

void MenuScene::musicEvent(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        if(SceneManager::Instance()->isGoodMusic())
        {
            musicBtt->loadTextures("normal/no_music_btt.png","normal/no_music_btt_click.png","");
            SceneManager::Instance()->setMusic(false);
        }
        else{
            musicBtt->loadTextures("normal/music_btt.png","normal/music_btt_click.png","");
            SceneManager::Instance()->setMusic(true);
        }
    }
}

//void MenuScene::soundEvent(Ref* pSender, ui::Widget::TouchEventType eEventType)
//{
//    if (eEventType == ui::Widget::TouchEventType::ENDED)
//    {
//        if(SceneManager::Instance()->isGoodSound())
//        {
//            soundBtt->loadTextures("normal/no_sound_btt.png","normal/no_sound_btt_click.png","");
//            SceneManager::Instance()->setSound(false);
//        }
//        else{
//            soundBtt->loadTextures("normal/sound_btt.png","normal/sound_btt_click.png","");
//            SceneManager::Instance()->setSound(true);
//        }
//    }
//}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	Director::getInstance()->end(); 
}
#endif