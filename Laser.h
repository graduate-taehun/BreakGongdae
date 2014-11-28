//
//  Laser.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#ifndef __BreakGongDae__Laser__
#define __BreakGongDae__Laser__

#include "cocos2d.h"
#include "BalanceSetting.h"
USING_NS_CC;

class LaserWarning : public LayerColor {
private:
    Sprite *Laser;
    virtual bool initRandomlyWithVisibleSize(float* threePosition, Size visibleSize);
    void warning_scheduler(float time);
    void laserlaunch_scheduler(float time);
    void laser_scheduler(float time);
public:
    static LaserWarning* createWithVisibleSize(float* threePosition, Size visibleSize);
};

#endif /* defined(__BreakGongDae__Laser__) */
