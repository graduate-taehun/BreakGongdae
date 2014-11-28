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

protected:
	virtual bool init();
//	virtual void setNextBuilding();

//	virtual bool onContactBegin(PhysicsContact& contact);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BonusStage)
};

#endif /* defined(__BreakGongDae__BonusStage__) */
