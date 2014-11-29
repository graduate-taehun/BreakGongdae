
//
//  BonusStage.h
//  BreakGongDae
//
//  Created by ¿ÃªÛ?Œ on 2014. 11. 28..
//
//

#ifndef __BreakGongDae__BonusStage__
#define __BreakGongDae__BonusStage__

#include "Stage.h"

class BonusStage : public Stage {
private:
    const static int HONEY_TAG=100;
    const static int NORMAL_TAG=101;
    const static int HARD_TAG=102;
    
	int cntMajor;
    string majors[4];
    
    Sprite* courses[3];
    
    virtual bool init(Status* _status);
    virtual bool onContactBegin(PhysicsContact& contact);
    virtual void replaceNextScene();
    void replace_scheduler(float time);
    void makeCourses();

public:
	static cocos2d::Scene* createScene(Status* _status);
    static BonusStage* create(Status* _status);

};
#endif /* defined(__BreakGongDae__BonusStage__) */
