#ifndef __GAME_SCENE_MAP3_H__
#define __GAME_SCENE_MAP3_H__

#include "SceneManager.h"

class GameSceneMap3 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	~GameSceneMap3();
	static cocos2d::Scene* createScene();
	bool init();
	void update( float dt );
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void reloadEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void backEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
	CREATE_FUNC(GameSceneMap3);
private:
	cocos2d::Label *_clickLabel, *_scoreLabel;
	cocos2d::__String *_clickNumberStr, *_scoreStr;

	cocos2d::Sprite *_cookie1, *_cookie2, *_cookie3; 
	cocos2d::Sprite *shadow1, *shadow2, *shadow3;

	cocos2d::Point cook1_start, cook1_end;
	cocos2d::Point cook2_start, cook2_end;
	cocos2d::Point cook3_start, cook3_end;

	cocos2d::Label *_labelScore1, *_labelScore2, *_labelScore3;

	bool _isClicked,_isWon;
	cocos2d::ui::Button *clickBackBtt, *clickReloadBtt;

	int _numberOfClick;

	float _correctPointDis, _shortPointDis, _bigPointDis;
	float _currentDis;
	int _score;

	int _pixelPerUpdateC1, _pixelPerUpdateC2, _pixelPerUpdateC3;
};

#endif