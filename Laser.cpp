//
//  Laser.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Laser.h"
#include <cstdlib>

bool LaserWarning::initRandomlyWithVisibleSize(float* threePosition, Size visibleSize) {
	if (!LayerColor::initWithColor(Color4B::RED))
        return false;
    
    int position =rand()%3;
	setPosition(Vec2(threePosition[position]-160,visibleSize.height/2-350));
    setOpacity(200);
    setContentSize(Size(visibleSize.width/3,visibleSize.height*4));
    if (!isScheduled(schedule_selector(LaserWarning::warning_scheduler)))
        schedule(schedule_selector(LaserWarning::warning_scheduler));
    return true;
}

LaserWarning* LaserWarning::createWithVisibleSize(float* threePosition, Size visibleSize)
{
    LaserWarning *pRet = new LaserWarning();
	
    if (pRet && pRet->initRandomlyWithVisibleSize(threePosition, visibleSize))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void LaserWarning::warning_scheduler(float time) {
    setOpacity(getOpacity()-1);
    if (getOpacity() < 50) {
        //Sett Laser
        /*Laser=Sprite::create("laser.png");
        setContentSize(Laser->getContentSize());*/
        schedule(schedule_selector(LaserWarning::laserlaunch_scheduler),INTERVAL_WARNING_AND_LASER,1,INTERVAL_WARNING_AND_LASER);
    }
}

void LaserWarning::laserlaunch_scheduler(float time) {
    setOpacity(255);
    schedule(schedule_selector(LaserWarning::laser_scheduler),TIME_SHOWING_LASER,1,TIME_SHOWING_LASER);
}

void LaserWarning::laser_scheduler(float time) {
    setOpacity(0);
    removeFromParent();
}