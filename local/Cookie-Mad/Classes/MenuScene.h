#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "SceneManager.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);

	void touchMap3Event(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

	void touchMap4Event(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

	void touchMap5Event(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    
    void musicEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    //void soundEvent(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
#endif
private:
	Label* _testLbl;
    cocos2d::ui::Button *musicBtt;
};

#endif // __HELLOWORLD_SCENE_H__
