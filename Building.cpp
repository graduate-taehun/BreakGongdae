<<<<<<< HEAD
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
=======
//
//  Building.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#include "Building.h"

Building* Building::create(/*넣어야함*/)
{
    Building *pRet = new Building(/*넣어야함*/);
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
>>>>>>> 03a735b2bd71b7ff773cefb96ae1085319b33fc4
