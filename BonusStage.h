//
//  BonusStage.h
//  BreakGongDae
//
//  Created by �̻�� on 2014. 11. 28..
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
protected:
	virtual bool init();
//	virtual void setNextBuilding();

//	virtual bool onContactBegin(PhysicsContact& contact);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	Sprite* course1;
	Sprite* course2;
	Sprite* course3;
public:
	static cocos2d::Scene* createScene();
	bool onContactBegin(PhysicsContact& contact);
	void block_scheduler(float time);
	void makesubject();
	CREATE_FUNC(BonusStage)
};

#endif /* defined(__BreakGongDae__BonusStage__) */
