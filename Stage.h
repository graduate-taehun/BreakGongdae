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

class Stage : public LayerColor
{
    
private:
    static float posCharacter[3]; //캐릭터의 x좌표로 가능한 것들
    static int cntofPosCharacter; //캐릭터가 현재 어디 있는지 posCharacter의 index로 나타냄. 처음은 중앙이므로 1
    void stopAttack();
    void menuCloseCallback(Ref* pSender);
    
protected:
    static const int GROUND_HEIGHT = 50;
    static const int CHARACTER_TAG = 11;
    static const int EDGE_TAG = 0;
    static const int BUILDING_TAG = 1;
	static const int TITLE_TAG = 2;
	static const int HP_BAR_TAG = 3;
	static const int STATUS_TAG = 4;

    static Size visibleSize;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void jump_scheduler(float time); //점프하면 반복적으로 호출되는 함수
	//void skill_blocking();
	bool onContactBegin(PhysicsContact& contact);

public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    CREATE_FUNC(Stage);
};

#endif /* defined(__BreakGongDae__Stage__) */