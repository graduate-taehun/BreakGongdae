//
//  Building.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#include "Building.h"

bool Building::init(int numbers) {
    if(!Layer::init()) return false;
    for(int i=0; i<numbers; ) {
        
    }
}

Building* Building::createWithNumbsersOfBlock(int numbers)
{
    Building *pRet = new Building();
    if (pRet && pRet->init(numbers))
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