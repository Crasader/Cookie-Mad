#ifndef __GAME_SCENE_MAP4_H__
#define __GAME_SCENE_MAP4_H__

#include "SceneManager.h"

class GameSceneMap4 : public cocos2d::Layer
{
public:
	~GameSceneMap4();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	bool init();
	void update(float dt);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void reloadEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	void backEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
	CREATE_FUNC(GameSceneMap4);
private:
	cocos2d::Label *_clickLabel, *_scoreLabel;
	cocos2d::__String *_clickNumberStr, *_scoreStr;

	cocos2d::Sprite *_cookie1, *_cookie2, *_cookie3, *_cookie4;
	cocos2d::Sprite *shadow1, *shadow2, *shadow3, *shadow4;

	cocos2d::Point cook1_start, cook1_end;
	cocos2d::Point cook2_start, cook2_end;
	cocos2d::Point cook3_start, cook3_end;
	cocos2d::Point cook4_start, cook4_end;

	cocos2d::Label *_labelScore1, *_labelScore2, *_labelScore3, *_labelScore4;

	bool _isClicked, _isWon;
	cocos2d::ui::Button *clickBackBtt, *clickReloadBtt;

	int _numberOfClick;

	float _correctPointDis, _shortPointDis, _bigPointDis;
	float _currentDis;
	int _score;

	int _pixelPerUpdateC1, _pixelPerUpdateC2, _pixelPerUpdateC3, _pixelPerUpdateC4;
};

#endif