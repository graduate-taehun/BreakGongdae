//
//  Stage1.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 28..
//
//

#ifndef __BreakGongDae__Stage1__
#define __BreakGongDae__Stage1__

#include "Stage.h"
#include <vector>

class Stage1 : public Stage {
private:
    void blade_scheduler(float time);
    void blade_return_scheduler(float time);    
    void block_scheduler(float time);
    void jump_scheduler(float time); //점프하면 반복적으로 호출되는 함수

protected:
    vector<string>::const_iterator level;
    Building* building;
    Sprite* blade;
	Sprite* bladeText;
    virtual bool isLevelEnd();
    
    virtual void setNextBuilding(int weight=0);
    
    void decreaseCharacterHP();
    
    virtual void replaceNextScene();
    
    virtual bool onContactBegin(PhysicsContact& contact);
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    virtual bool init(Status* _status);
    
public:
    static const vector<string> fileBuilding; //FILE_BUILDINGS_STAGE1 in BalanceSettings.h
    static cocos2d::Scene* createScene();
    static Stage1* create();
};

#endif /* defined(__BreakGongDae__Stage1__) */
