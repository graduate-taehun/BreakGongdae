//
//  Building.cpp
//  BreakGongDae
//
//  Created by ������ on 2014. 11. 1..
//
//

#include "Building.h"

Building* Building::create(/*�־����*/)
{
    Building *pRet = new Building(/*�־����*/);
    if (pRet && pRet->init())
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