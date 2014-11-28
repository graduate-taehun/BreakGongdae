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
#include <queue>
#include <cstdlib>

class Stage : public LayerColor {
private:
    int cntofPosCharacter; //캐릭터가 현재 어디 있는지 posCharacter의 index로 나타냄. 처음은 중앙이므로 1
    void menuCloseCallback(Ref* pSender);
    
    Vec2 posTitle;
    Vec2 posStatus;
    Vec2 posClose;
    Vec2 posGauge;
    
    
    static const int GROUND_TAG = 0;
    //static const int EDGE_TAG=1;
protected:
    static const int GROUND_HEIGHT = 50;
    static const int THIS_TAG=2;
    
    virtual bool init();
   
    int wholeNumberOfBuilding;
    queue<string> fileBuilding;
    virtual void setNextBuilding() {}
    
    bool Game_Pause;
    static Size visibleSize;
	float posCharacter[3]; //캐릭터의 x좌표로 가능한 것들
    
    Menu* menuClose;
	MenuItemImage* btnClose;
    LabelBMFont *lbTitle;
    
    Status* status;
    Character* character;
    Building* building;
	Sprite* blade;
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {}
    virtual bool onContactBegin(PhysicsContact& contact) {return true;}
    
    void jump_scheduler(float time); //점프하면 반복적으로 호출되는 함수
	void blade_scheduler(float time);
    void gauge_up_scheduler(float time);
    
public:
	static cocos2d::Scene* createScene();

    CREATE_FUNC(Stage)
};

#endif /* defined(__BreakGongDae__Stage__) */