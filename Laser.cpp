//
//  Laser.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Laser.h"

bool LaserWarning::initRandomlyWithVisibleSize(float* threePosition) {
    if(!Layer::init())
        return false;
    //1,2,3 중에 랜덤
    
    return true;
}

LaserWarning* LaserWarning::createWithVisibleSize(float* threePosition)
{
    LaserWarning *pRet = new LaserWarning();
    if (pRet && pRet->initRandomlyWithVisibleSize(threePosition))
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