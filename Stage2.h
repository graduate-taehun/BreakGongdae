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
    virtual bool init(Status* _status);
    void makeLaser_scheduler(float time);
    void removeLaser_scheduler(float time);
    int laserposition;
    virtual void replaceNextScene();
public:
    ~Stage2();
    void shotbyLaser();
	static cocos2d::Scene* createScene(Status* _status);
    static Stage2* create(Status* status);
};

#endif /* defined(__BreakGongDae__Stage2__) */
