//
//  Stage2.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#ifndef __BreakGongDae__Stage2__
#define __BreakGongDae__Stage2__

#include "Stage.h"
#include "Laser.h"

class Stage2 : public Stage {
private:
    LaserWarning *laserwarning;
    virtual bool init();
public:
    Scene* createScene();
    CREATE_FUNC(Stage2)
};

#endif /* defined(__BreakGongDae__Stage2__) */
