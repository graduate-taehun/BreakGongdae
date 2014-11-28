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
    
protected:

    virtual bool init();
    virtual void setNextBuilding();
    
    virtual bool onContactBegin(PhysicsContact& contact);
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void decreaseCharacterHP();
    
    void block_scheduler(float time);
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(Stage1)
};

#endif /* defined(__BreakGongDae__Stage1__) */
