//
//  Laser.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Laser.h"
#include "Stage2.h"
#include <cstdlib>

bool LaserWarning::init() {
	if (!LayerColor::initWithColor(Color4B::RED))
        return false;
    
    position =rand()%3;
    setOpacity(200);
    schedule(schedule_selector(LaserWarning::warning_scheduler));
    return true;
}



void LaserWarning::warning_scheduler(float time) {
    setOpacity(getOpacity()-3);
    if (getOpacity()<5) {
        setOpacity(0);
        //Sett Laser
        /*Laser=Sprite::create("laser.png");
        setContentSize(Laser->getContentSize());*/
        setContentSize(Size(getContentSize().width*0.2, getContentSize().height));
        schedule(schedule_selector(LaserWarning::laserlaunch_scheduler),INTERVAL_WARNING_AND_LASER,1,INTERVAL_WARNING_AND_LASER);
        unschedule(schedule_selector(LaserWarning::warning_scheduler));
    }
}

void LaserWarning::laserlaunch_scheduler(float time) {
    setOpacity(255);
    schedule(schedule_selector(LaserWarning::laser_scheduler),TIME_SHOWING_LASER,1,TIME_SHOWING_LASER);
    //unschedule(schedule_selector(LaserWarning::laserlaunch_scheduler));
}

void LaserWarning::laser_scheduler(float time) {
    setOpacity(0);
    dynamic_cast<Stage2 *>(getParent())->shotbyLaser();
    //unschedule(schedule_selector(LaserWarning::laser_scheduler));
}