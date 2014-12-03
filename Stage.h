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
    //static const int EDGE_TAG=1;
protected:
    static const int GROUND_HEIGHT = 50;
    static const int THIS_TAG = 2;
    static const int MENU_Z_ORDER = 255;
    static const int THIS_HEIGHT = 5500;
    static const int THIS_BACKGROUND_HEIGHT=3192;
    
    int cntofPosCharacter; //캐릭터가 현재 어디 있는지 posCharacter의 index로 나타냄. 처음은 중앙이므로 1
    
    virtual bool init(Status* _status);
   
    void setViewPoint(float threshold);
    
    bool Game_Pause;
    static Size visibleSize;
	float posCharacter[3]; //캐릭터의 x좌표로 가능한 것들
    
	Sprite* P_Layer;
    Menu* menuClose;
	MenuItemImage* btnClose;
    LabelBMFont *lbTitle;
	LabelTTF *P_Label;
    Status* status;
	Sprite* groundNode;
    Character* character;
	Sprite* st_scene;

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {}
    virtual bool onContactBegin(PhysicsContact& contact) { return true; }
    
	void scene_scheduler(float time);
    void jump_scheduler(float time); //점프하면 반복적으로 호출되는 함수
	void gauge_up_scheduler(float time);
    
    virtual void replaceNextScene() {}
    
public:
	static cocos2d::Scene* createScene();

    static Stage* create();
};

#endif /* defined(__BreakGongDae__Stage__) */