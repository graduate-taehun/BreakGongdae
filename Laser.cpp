//
//  Laser.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Laser.h"
#include <cmath>

bool LaserWarning::initRandomlyWithVisibleSize(float* threePosition, Size visibleSize) {
	if (!LayerColor::initWithColor(Color4B::RED))
        return false;
    srand(time(NULL));
    int position =rand()%3;
    setPosition(Vec2(threePosition[position],visibleSize.height/2));
    setOpacity(128);
    
    setContentSize(Size(visibleSize.width/3,visibleSize.height));
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