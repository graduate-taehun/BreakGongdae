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
class Stage1 : public Stage {
private:
    void blade_scheduler(float time);
    void blade_return_scheduler(float time);    
    void block_scheduler(float time);

protected:
    Building* building;
    Sprite* blade;
    
    virtual bool init(Status* _status);
    int wholeNumberOfBuilding;
    queue<string> fileBuilding;
    virtual void setNextBuilding();
    
    virtual bool onContactBegin(PhysicsContact& contact);
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void decreaseCharacterHP();
    
    virtual void replaceNextScene();

public:
    static cocos2d::Scene* createScene();
    static Stage1* create();
};

#endif /* defined(__BreakGongDae__Stage1__) */
