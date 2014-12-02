//
//  Laser.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#ifndef __BreakGongDae__Laser__
#define __BreakGongDae__Laser__

#include "BalanceSetting.h"

class LaserWarning : public LayerColor {
private:
    Sprite *Laser;
    int position;
    virtual bool init();
    void warning_scheduler(float time);
    void laserlaunch_scheduler(float time);
    void laser_scheduler(float time);
public:
    CREATE_FUNC(LaserWarning)
};

#endif /* defined(__BreakGongDae__Laser__) */
