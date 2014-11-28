//
//  BonusStage.h
//  BreakGongDae
//
//  Created by ¿ÃªÛπŒ on 2014. 11. 28..
//
//

#ifndef __BreakGongDae__BonusStage__
#define __BreakGongDae__BonusStage__

#include "Stage.h"

class BonusStage : public Stage {
private:
	int poscheck;
	int score[10];
	int stage_num;
    
    virtual bool init(Status* _status);
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual bool onContactBegin(PhysicsContact& contact);
public:
	static cocos2d::Scene* createScene(Status* _status);
    static BonusStage* create(Status* _status);
};

#endif /* defined(__BreakGongDae__BonusStage__) */
