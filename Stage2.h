//
//  Stage2.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#ifndef __BreakGongDae__Stage2__
#define __BreakGongDae__Stage2__

#include "Stage1.h"
#include "Laser.h"

class Stage2 : public Stage1 {
private:
	LaserWarning *laserwarning;
    
    void makeLaser_scheduler(float time);
    void removeLaser_scheduler(float time);
    virtual bool isLevelEnd();
    int laserposition;
    virtual void replaceNextScene();
    
    virtual bool init(Status* _status);

public:
    ~Stage2();
    static const vector<string> fileBuilding;
    
	static cocos2d::Scene* createScene(Status* _status);
    static Stage2* create(Status* status);
    
    void shotbyLaser();
};

#endif /* defined(__BreakGongDae__Stage2__) */
