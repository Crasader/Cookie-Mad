#include "GameSceneMap4.h"
#include "MenuScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) 
#include "SonarFrameworks.h"
#endif
#define SPEED_BACIC_C1 31
#define SPEED_BACIC_C2 32
#define SPEED_BACIC_C3 38
#define SPEED_BACIC_C4 40



inline void SwapInt(int &a, int &b) {
	if (&a != &b) {
		a ^= b;
		b ^= a;
		a ^= b;
	}
}

Scene* GameSceneMap4::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameSceneMap4::create();
	//layer->SetPhysicsWorld(scene->getPhysicsWorld());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	layer->setKeypadEnabled(true);
#endif
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

inline float distance2Point(cocos2d::Point p1, cocos2d::Point p2)
{
	//float returnD = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// on "init" you need to initialize your instance
bool GameSceneMap4::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	_isWon = false;
	float xspeed = 1;
	if (SceneManager::Instance()->getXScale() > 1.5)
		xspeed = SceneManager::Instance()->getXScale() * 1.5;
	else if (SceneManager::Instance()->getXScale() > 1.2)
		xspeed = SceneManager::Instance()->getXScale() * 1.2;
	else
		xspeed = SceneManager::Instance()->getXScale();

	_pixelPerUpdateC1 = SPEED_BACIC_C1 * xspeed;
	_pixelPerUpdateC2 = SPEED_BACIC_C2 * xspeed;
	_pixelPerUpdateC3 = SPEED_BACIC_C3 * xspeed;
	_pixelPerUpdateC4 = SPEED_BACIC_C4 * xspeed;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////
	// menu bg
	/////
	auto bgSprite = Sprite::create("normal/tableclothes_game.jpg");

	// position the sprite on the center of the screen
	bgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bgSprite->setScaleX(SceneManager::Instance()->getXScale());
	bgSprite->setScaleY(SceneManager::Instance()->getYScale());

	// add the sprite as a child to this layer
	this->addChild(bgSprite, 0);
	/////
	// end menu bg
	///// hand_click.png

	//
	// click image
	//

	auto clickSprite = Sprite::create("normal/hand_click.png");

	// position the sprite on the center of the screen
	clickSprite->setPosition(Vec2(visibleSize.width  * 0.1 + origin.x,
		visibleSize.height + origin.y - clickSprite->getContentSize().height * 0.6 * SceneManager::Instance()->getYScale()));
	clickSprite->setScaleX(SceneManager::Instance()->getXScale());
	clickSprite->setScaleY(SceneManager::Instance()->getYScale());

	// add the sprite as a child to this layer
	this->addChild(clickSprite, 100);

	clickBackBtt = cocos2d::ui::Button::create();
	clickBackBtt->setTouchEnabled(true);
	clickBackBtt->loadTextures("normal/back.png", "normal/back_click.png", "");
	clickBackBtt->setPosition(Vec2(origin.x + visibleSize.width * 0.98 - clickBackBtt->getContentSize().width * 0.5 * SceneManager::Instance()->getXScale(),
		clickSprite->getPositionY()));
	clickBackBtt->addTouchEventListener(CC_CALLBACK_2(GameSceneMap4::backEvent, this));
	clickBackBtt->setScaleX(SceneManager::Instance()->getXScale());
	clickBackBtt->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(clickBackBtt, 101);

	clickReloadBtt = cocos2d::ui::Button::create();
	clickReloadBtt->setTouchEnabled(true);
	clickReloadBtt->loadTextures("normal/reload.png", "normal/reload_click.png", "");
	clickReloadBtt->setPosition(Vec2(clickBackBtt->getPositionX()
		- clickBackBtt->getContentSize().width * 0.5 *  SceneManager::Instance()->getXScale()
		- clickReloadBtt->getContentSize().width * 0.5  * SceneManager::Instance()->getXScale()
		- visibleSize.width * 0.01,
		clickSprite->getPositionY()));
	clickReloadBtt->addTouchEventListener(CC_CALLBACK_2(GameSceneMap4::reloadEvent, this));
	clickReloadBtt->setScaleX(SceneManager::Instance()->getXScale());
	clickReloadBtt->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(clickReloadBtt, 102);


	//
	// label click
	//
	_numberOfClick = 0;
	//float fontSizeClick = 50 * SceneManager::Instance()->getYScale();
	_clickNumberStr = __String::createWithFormat(" x %i", _numberOfClick);
	_clickLabel = Label::createWithTTF(_clickNumberStr->getCString(), "fonts/SAF.otf", FONT_SIZE_TEXT * SceneManager::Instance()->getYScale());
	//float scaleLbl = 1;// clickReloadBtt->getContentSize().height / _clickLabel->getContentSize().height;
	//_clickLabel->setScale(scaleLbl, scaleLbl);
	_clickLabel->setColor(Color3B::BLACK);
	_clickLabel->setPosition(Vec2(clickSprite->getPositionX()
		+ clickSprite->getContentSize().width * 0.5 * SceneManager::Instance()->getXScale()
		+ _clickLabel->getContentSize().width * 0.5
		+ 0.01 * visibleSize.width
		,
		clickSprite->getPositionY()));

	this->addChild(_clickLabel, 2);

	//
	// label score
	//
	// float fontSizeScore = 50 * SceneManager::Instance()->getYScale();
	_score = 10;
	_scoreStr = __String::createWithFormat(" %i / %i", _score, FINISH_SCORE_80);
	_scoreLabel = Label::createWithTTF(_scoreStr->getCString(), "fonts/SF Cosmic Age.ttf", FONT_SIZE_SCORE * SceneManager::Instance()->getYScale());
	//_scoreLabel->setScale(scaleLbl, scaleLbl);
	_scoreLabel->setColor(Color3B::BLACK);
	_scoreLabel->setPosition(Vec2(
		clickReloadBtt->getPositionX()
		- clickReloadBtt->getContentSize().width * 0.5  * SceneManager::Instance()->getXScale()
		- _scoreLabel->getContentSize().width * 0.5
		- 0.05 * visibleSize.width,
		clickSprite->getPositionY()));

	this->addChild(_scoreLabel, 3);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	/// game !!! getSizeOfSquare
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	
	
	float x1 = 0.166 * SceneManager::Instance()->getSizeOfSquare() + origin.x;
	float x2 = 0.5 * SceneManager::Instance()->getSizeOfSquare() + origin.x;
	float x3 = 0.833 * SceneManager::Instance()->getSizeOfSquare() + origin.x;

	float y1 = visibleSize.height - clickSprite->getContentSize().height * SceneManager::Instance()->getYScale()
		- 0.833 * SceneManager::Instance()->getSizeOfSquare() + origin.y;
	float y2 = visibleSize.height - clickSprite->getContentSize().height * SceneManager::Instance()->getYScale()
		- 0.5 * SceneManager::Instance()->getSizeOfSquare() + origin.y;
	float y3 = visibleSize.height - clickSprite->getContentSize().height * SceneManager::Instance()->getYScale()
		- 0.166 * SceneManager::Instance()->getSizeOfSquare() + origin.y;


	shadow1 = Sprite::create("normal/coki_shadow.png");
	shadow1->setPosition(Vec2(x2, y3));
	shadow1->setScaleX(SceneManager::Instance()->getXScale());
	shadow1->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(shadow1, 5);
	_labelScore1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", FONT_SIZE_TEXT * SceneManager::Instance()->getYScale());
	//_scoreLabel->setScale(scaleLbl, scaleLbl);
	_labelScore1->setColor(Color3B::GREEN);
	_labelScore1->setPosition(Vec2(shadow1->getPositionX() + shadow1->getContentSize().width * SceneManager::Instance()->getXScale() * 0.5,
		shadow1->getPositionY() + shadow1->getContentSize().height * SceneManager::Instance()->getYScale() * 0.5));
	this->addChild(_labelScore1, 50);


	shadow2 = Sprite::create("normal/coki_shadow.png");
	shadow2->setPosition(Vec2(x1, y2));
	shadow2->setScaleX(SceneManager::Instance()->getXScale());
	shadow2->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(shadow2, 6);
	_labelScore2 = Label::createWithTTF("", "fonts/Marker Felt.ttf", FONT_SIZE_TEXT * SceneManager::Instance()->getYScale());
	//_scoreLabel->setScale(scaleLbl, scaleLbl);
	_labelScore2->setColor(Color3B::GREEN);
	_labelScore2->setPosition(Vec2(shadow2->getPositionX() + shadow2->getContentSize().width * SceneManager::Instance()->getXScale() * 0.5,
		shadow2->getPositionY() + shadow2->getContentSize().height * SceneManager::Instance()->getYScale() * 0.5));
	this->addChild(_labelScore2, 60);

	shadow3 = Sprite::create("normal/coki_shadow.png");
	shadow3->setPosition(Vec2(x2, y1));
	shadow3->setScaleX(SceneManager::Instance()->getXScale());
	shadow3->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(shadow3, 7);
	_labelScore3 = Label::createWithTTF("", "fonts/Marker Felt.ttf", FONT_SIZE_TEXT * SceneManager::Instance()->getYScale());
	//_scoreLabel->setScale(scaleLbl, scaleLbl);
	_labelScore3->setColor(Color3B::GREEN);
	_labelScore3->setPosition(Vec2(shadow3->getPositionX() + shadow3->getContentSize().width * SceneManager::Instance()->getXScale() * 0.5,
		shadow3->getPositionY() + shadow3->getContentSize().height * SceneManager::Instance()->getYScale() * 0.5));
	this->addChild(_labelScore3, 70);

	shadow4 = Sprite::create("normal/coki_shadow.png");
	shadow4->setPosition(Vec2(x3, y2));
	shadow4->setScaleX(SceneManager::Instance()->getXScale());
	shadow4->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(shadow4, 8);
	_labelScore4 = Label::createWithTTF("", "fonts/Marker Felt.ttf", FONT_SIZE_TEXT * SceneManager::Instance()->getYScale());
	//_scoreLabel->setScale(scaleLbl, scaleLbl);
	_labelScore4->setColor(Color3B::GREEN);
	_labelScore4->setPosition(Vec2(shadow4->getPositionX() + shadow4->getContentSize().width * SceneManager::Instance()->getXScale() * 0.5,
		shadow4->getPositionY() + shadow4->getContentSize().height * SceneManager::Instance()->getYScale() * 0.5));
	this->addChild(_labelScore4, 80);

	float far_dis = SceneManager::Instance()->getXScale() * shadow1->getContentSize().width + 0.02 * SceneManager::Instance()->getSizeOfSquare();
	
	
	//////////////////////////////////////////////////////////////////////////
	////////////////// COOKIES
	//////////////////////////////////////////////////////////////////////////
	
	
	cook1_start = Vec2(x3 + far_dis, y3);
	cook1_end = Vec2(-far_dis, y3);
	_cookie1 = Sprite::create("normal/cokie.png");
	_cookie1->setPosition(cook1_start);
	_cookie1->setScaleX(SceneManager::Instance()->getXScale());
	_cookie1->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(_cookie1, 30);

	cook2_start = Vec2(x1, y3 + far_dis);
	cook2_end = Vec2(x1, y1 - far_dis);
	_cookie2 = Sprite::create("normal/cokie.png");
	_cookie2->setPosition(cook2_start);
	_cookie2->setScaleX(SceneManager::Instance()->getXScale());
	_cookie2->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(_cookie2, 31);

	cook3_start = Vec2(x1 - far_dis, y1);
	cook3_end = Vec2(x3 + far_dis, y1);
	_cookie3 = Sprite::create("normal/cokie.png");
	_cookie3->setPosition(cook3_start);
	_cookie3->setScaleX(SceneManager::Instance()->getXScale());
	_cookie3->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(_cookie3, 32);

	cook4_start = Vec2(x3, y1- far_dis);
	cook4_end = Vec2(x3, y3+far_dis);
	_cookie4 = Sprite::create("normal/cokie.png");
	_cookie4->setPosition(cook4_start);
	_cookie4->setScaleX(SceneManager::Instance()->getXScale());
	_cookie4->setScaleY(SceneManager::Instance()->getYScale());
	this->addChild(_cookie4, 33);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameSceneMap4::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	_isClicked = false;
	_correctPointDis = shadow1->getContentSize().width * SceneManager::Instance()->getXScale() * 0.05;
	_shortPointDis = shadow1->getContentSize().width * SceneManager::Instance()->getXScale() *0.4;
	_bigPointDis = shadow1->getContentSize().width * SceneManager::Instance()->getXScale() * 0.95;

	if (SceneManager::Instance()->isAdvAvaiable())
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SonarCocosHelper::AdMob::showBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
#endif
	}
	this->scheduleUpdate();
}

bool GameSceneMap4::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (_isWon)
		return _isWon;
	_isClicked = !_isClicked;
	if (_isClicked)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
			"sound/touch.wav", false);
		if (_numberOfClick % 7 == 0)
			SwapInt(_pixelPerUpdateC4, _pixelPerUpdateC3);
		else if (_numberOfClick % 5 == 0)
			SwapInt(_pixelPerUpdateC1, _pixelPerUpdateC3);
		else if (_numberOfClick % 3 == 0)
			SwapInt(_pixelPerUpdateC2, _pixelPerUpdateC4);
		else if (_numberOfClick % 2 == 0)
			SwapInt(_pixelPerUpdateC2, _pixelPerUpdateC1);


		_clickNumberStr = __String::createWithFormat(" x %i", ++_numberOfClick);
		_clickLabel->setString(_clickNumberStr->getCString());
		// distance 1,2,3 !!
		_currentDis = distance2Point(_cookie1->getPosition(), shadow1->getPosition());
		if (_currentDis > _bigPointDis){
			_score--;
			_labelScore1->setString("-1");
			_labelScore1->setColor(Color3B::RED);
		}
		else if (_currentDis < _correctPointDis){
			_score += 3;
			_labelScore1->setString("+3");
			_labelScore1->setColor(Color3B::BLUE);
		}
		else if (_currentDis < _shortPointDis){
			_score += 2;
			_labelScore1->setString("+2");
			_labelScore1->setColor(Color3B::GREEN);
		}
		else{
			_score++;
			_labelScore1->setString("+1");
			_labelScore1->setColor(Color3B::GREEN);
		}


		///
		///2
		///
		_currentDis = distance2Point(_cookie2->getPosition(), shadow2->getPosition());
		if (_currentDis > _bigPointDis){
			_score--;
			_labelScore2->setString("-1");
			_labelScore2->setColor(Color3B::RED);
		}
		else if (_currentDis < _correctPointDis){
			_score += 3;
			_labelScore2->setString("+3");
			_labelScore2->setColor(Color3B::BLUE);
		}
		else if (_currentDis < _shortPointDis){
			_score += 2;
			_labelScore2->setString("+2");
			_labelScore2->setColor(Color3B::GREEN);
		}
		else{
			_score++;
			_labelScore2->setString("+1");
			_labelScore2->setColor(Color3B::GREEN);
		}

		///
		///3
		///
		_currentDis = distance2Point(_cookie3->getPosition(), shadow3->getPosition());
		if (_currentDis > _bigPointDis){
			_score--;
			_labelScore3->setString("-1");
			_labelScore3->setColor(Color3B::RED);
		}
		else if (_currentDis < _correctPointDis){
			_score += 3;
			_labelScore3->setString("+3");
			_labelScore3->setColor(Color3B::BLUE);
		}
		else if (_currentDis < _shortPointDis){
			_score += 2;
			_labelScore3->setString("+2");
			_labelScore3->setColor(Color3B::GREEN);
		}
		else{
			_score++; 
			_labelScore3->setString("+1");
			_labelScore3->setColor(Color3B::GREEN);
		}

		///
		///4
		///
		_currentDis = distance2Point(_cookie4->getPosition(), shadow4->getPosition());
		if (_currentDis > _bigPointDis){
			_score--;
			_labelScore4->setString("-1");
			_labelScore4->setColor(Color3B::RED);
		}
		else if (_currentDis < _correctPointDis){
			_score += 3;
			_labelScore4->setString("+3");
			_labelScore4->setColor(Color3B::BLUE);
		}
		else if (_currentDis < _shortPointDis){
			_score += 2;
			_labelScore4->setString("+2");
			_labelScore4->setColor(Color3B::GREEN);
		}
		else{
			_score++;
			_labelScore4->setString("+1");
			_labelScore4->setColor(Color3B::GREEN);
		}


		if (_score >= FINISH_SCORE_80)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
				"sound/win.mp3", false);
			_isWon = true;
			clickBackBtt->setEnabled(false);
			clickReloadBtt->setEnabled(false);
			// win - show dialog
			auto black_bg = Sprite::create("normal/black_bg.jpg");
			black_bg->setPosition(Point(Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2,
				Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height / 2));
			float scaleX = Director::getInstance()->getVisibleSize().width / black_bg->getContentSize().width;
			float scaleY = Director::getInstance()->getVisibleSize().height / black_bg->getContentSize().height;
			black_bg->setScale(scaleX, scaleY);
			black_bg->setOpacity(222);
			this->addChild(black_bg, 577);

			auto congraSprite = Sprite::create("normal/congra_bg.png");
			congraSprite->setPosition(Point(Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2,
				Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height * 0.6));
			congraSprite->setScaleX(SceneManager::Instance()->getXScale());
			congraSprite->setScaleY(SceneManager::Instance()->getYScale());
			this->addChild(congraSprite, 578);

			auto congraText = Sprite::create("normal/congra_text.png");
			congraText->setPosition(Point(Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2,
				congraSprite->getPositionY()
				+ congraSprite->getContentSize().height * SceneManager::Instance()->getYScale() * 0.25));
			congraText->setScaleX(SceneManager::Instance()->getXScale());
			congraText->setScaleY(SceneManager::Instance()->getYScale());
			this->addChild(congraText, 578);


			auto clickSprite = Sprite::create("normal/hand_click.png");
			clickSprite->setScaleX(SceneManager::Instance()->getXScale());
			clickSprite->setScaleY(SceneManager::Instance()->getYScale());


			auto lblScore = Label::createWithTTF(_clickNumberStr->getCString(),
				"fonts/SAF.otf", FONT_SIZE_TEXT * SceneManager::Instance()->getYScale());
			lblScore->setColor(Color3B::BLACK);

			float x1 = Director::getInstance()->getVisibleSize().width * 0.5
				+ 0.25 * (clickSprite->getContentSize().width * SceneManager::Instance()->getXScale()
				+ lblScore->getContentSize().width * SceneManager::Instance()->getXScale());
			float x2 = 2 * Director::getInstance()->getVisibleSize().width * 0.5 - x1;
			//float wi_screen_mid = Director::getInstance()->getVisibleSize().width * 0.5;
			float hi_screen = congraSprite->getPositionY() - congraSprite->getContentSize().height * SceneManager::Instance()->getYScale() * 0.25;

			float position_img = lblScore->getContentSize().width + clickSprite->getContentSize().width * SceneManager::Instance()->getXScale();


			clickSprite->setPosition(Point(x2, hi_screen));
			lblScore->setPosition(Point(x1, hi_screen));

			this->addChild(clickSprite, 579);
			this->addChild(lblScore, 580);


			auto clickBackNotiBtt = cocos2d::ui::Button::create();
			clickBackNotiBtt->setTouchEnabled(true);
			clickBackNotiBtt->loadTextures("normal/back_noti.png", "normal/back_noti_click.png", "");
			clickBackNotiBtt->setPosition(Vec2(
				Director::getInstance()->getVisibleSize().width * 0.5
				- congraSprite->getContentSize().width  * SceneManager::Instance()->getXScale() * 0.4
				, hi_screen));
			clickBackNotiBtt->addTouchEventListener(CC_CALLBACK_2(GameSceneMap4::reloadEvent, this));
			clickBackNotiBtt->setScaleX(SceneManager::Instance()->getXScale());
			clickBackNotiBtt->setScaleY(SceneManager::Instance()->getYScale());
			this->addChild(clickBackNotiBtt, 581);

			auto clickNextNotiBtt = cocos2d::ui::Button::create();
			clickNextNotiBtt->setTouchEnabled(true);
			clickNextNotiBtt->loadTextures("normal/next_noti.png", "normal/next_noti_click.png", "");
			clickNextNotiBtt->setPosition(Vec2(
				Director::getInstance()->getVisibleSize().width * 0.5
				+ congraSprite->getContentSize().width  * SceneManager::Instance()->getXScale() * 0.4
				, hi_screen));
			clickNextNotiBtt->addTouchEventListener(CC_CALLBACK_2(GameSceneMap4::backEvent, this));
			clickNextNotiBtt->setScaleX(SceneManager::Instance()->getXScale());
			clickNextNotiBtt->setScaleY(SceneManager::Instance()->getYScale());
			this->addChild(clickNextNotiBtt, 582);

			SceneManager::Instance()->writeScoreToMap4(_numberOfClick);

			// write st here
		}
		else if (_score > MINIMUM_SCORE){
			_scoreStr = __String::createWithFormat(" %i / %i", _score, FINISH_SCORE_80);
			_scoreLabel->setString(_scoreStr->getCString());
		}
		else{ // -999 is min
			_score = MINIMUM_SCORE;
			_scoreLabel->setString("HAHA!!!");
		}
		_labelScore1->stopAllActions();
		_labelScore2->stopAllActions();
		_labelScore3->stopAllActions();
		_labelScore4->stopAllActions();

		_labelScore1->setOpacity(255);
		_labelScore2->setOpacity(255);
		_labelScore3->setOpacity(255);
		_labelScore4->setOpacity(255);

		auto actionFade1 = FadeOut::create(3);
		auto actionFade2 = FadeOut::create(3);
		auto actionFade3 = FadeOut::create(3);
		auto actionFade4 = FadeOut::create(3);

		_labelScore1->runAction(actionFade1);
		_labelScore2->runAction(actionFade2);
		_labelScore3->runAction(actionFade3);
		_labelScore4->runAction(actionFade4);
	}
	return _isClicked;
}

void GameSceneMap4::update(float dt)
{
	if (!_isClicked)
	{
		if (_cookie1->getPositionX() < cook1_end.x)
			_cookie1->setPosition(cook1_start);
		else
			_cookie1->setPositionX(_cookie1->getPositionX() - _pixelPerUpdateC1);

		if (_cookie2->getPositionY() < cook2_end.y)
			_cookie2->setPosition(cook2_start);
		else{
			_cookie2->setPositionY(_cookie2->getPositionY() - _pixelPerUpdateC2);
		}

		if (_cookie3->getPositionX() > cook3_end.x)
			_cookie3->setPosition(cook3_start);
		else{
			_cookie3->setPositionX(_cookie3->getPositionX() + _pixelPerUpdateC3);
		}

		if (_cookie4->getPositionY() > cook4_end.y)
			_cookie4->setPosition(cook4_start);
		else{
			_cookie4->setPositionY(_cookie4->getPositionY() + _pixelPerUpdateC4);
		}
	}
}
void GameSceneMap4::reloadEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	SceneManager::Instance()->setAdvAvaiable();
	this->unscheduleUpdate();
	auto scene = GameSceneMap4::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}

void GameSceneMap4::backEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
	if (SceneManager::Instance()->isAdvAvaiable())
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SonarCocosHelper::AdMob::hideBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
#endif
	}
	this->unscheduleUpdate();
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}

GameSceneMap4::~GameSceneMap4()
{

}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void GameSceneMap4::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (SceneManager::Instance()->isAdvAvaiable())
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SonarCocosHelper::AdMob::hideBannerAd(SonarCocosHelper::AdBannerPosition::eBottom);
#endif
	}
	this->unscheduleUpdate();
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
	// return to main menu
}
#endif