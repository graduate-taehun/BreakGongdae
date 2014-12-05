//
//  Stage.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//

#ifndef __BreakGongDae__Stage__
#define __BreakGongDae__Stage__

#include "Character.h"
#include "Status.h"
#include "Building.h"
#include "Menu&Score.h"

class Stage : public Layer {
private:
    void menuCloseCallback(Ref* pSender);
    
    Vec2 posTitle;
    Vec2 posStatus;
    Vec2 posClose;
    Vec2 posGauge;
     
    static const int GROUND_TAG = 0;
protected:
    static const int THIS_TAG = 2;
    static const int MENU_Z_ORDER = 255;
    static const int THIS_HEIGHT = 5500;
    
    virtual bool init(Status* _status);
    static cocos2d::Scene* createScene();
    static Stage* create();
    
    //캐릭터가 현재 어디 있는지 posCharacter의 index로 나타냄. 처음은 중앙이므로 1
    int cntofPosCharacter;
    
    void setViewPoint(float threshold);
    
    bool Game_Pause;
    static Size visibleSize;
	float posCharacter[3]; //캐릭터의 x좌표로 가능한 것들
    
	Sprite* pauseCover;
    Menu* menuClose;
	MenuItemImage* btnClose;
    Label *lbTitle;
    Label *lbPause;
    Status* status;
	Sprite* groundNode;
    Character* character;
	Sprite* splashScreen;

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {}
    virtual bool onContactBegin(PhysicsContact& contact) { return true; }
    
	void scene_scheduler(float time);
	void gauge_up_scheduler(float time);
    
    virtual void replaceNextScene();
public:
    static const int GROUND_HEIGHT = 50;
    static const int THIS_BACKGROUND_HEIGHT=3192;
};

#endif /* defined(__BreakGongDae__Stage__) */