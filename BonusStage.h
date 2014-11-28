
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
	int honeyposcheck;
	int normalposcheck;
	int stage_num;
    
    virtual bool init(Status* _status);
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual bool onContactBegin(PhysicsContact& contact);
protected:
	//virtual bool init();
//	virtual void setNextBuilding();

//	virtual bool onContactBegin(PhysicsContact& contact);
	//virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	Sprite* course1;
	Sprite* course2;
	Sprite* course3;
public:
	static cocos2d::Scene* createScene(Status* _status);
    static BonusStage* create(Status* _status);
	//static cocos2d::Scene* createScene();
	//bool onContactBegin(PhysicsContact& contact);
	//void block_scheduler(float time);
	void makesubject();
	//CREATE_FUNC(BonusStage)
};
#endif /* defined(__BreakGongDae__BonusStage__) */
