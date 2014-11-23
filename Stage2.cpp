//
//  Stage2.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Stage2.h"

Scene* Stage2::createScene()
{
    auto scene=Stage::createScene();
    scene->removeChildByTag(Stage::THIS_TAG);
    
    auto layer = Stage2::create();
    layer->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    scene->addChild(layer);
    
    return scene;
}

bool Stage2::init() {
    if(!Stage::init()) return false;
    
    return true;
}