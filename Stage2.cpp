//
//  Stage2.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Stage2.h"
#include <climits>

Scene* Stage2::createScene()
{
    auto scene=Stage1::createScene();
    scene->removeChildByTag(Stage1::THIS_TAG);
    
    auto layer = Stage2::create();
    layer->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    layer->setTag(THIS_TAG);
    scene->addChild(layer);
    
    return scene;
}

bool Stage2::init() {
    if(!Stage1::init()) return false;
    schedule(schedule_selector(Stage2::makeLaser_scheduler),1,INT_MAX,1);

    return true;
}

Stage2::~Stage2() {
    unschedule(schedule_selector(Stage2::makeLaser_scheduler));
}

void Stage2::makeLaser_scheduler(float time) {
    if(rand()%10<3 && laserwarning==nullptr) {
        laserposition=rand()%3;
        laserwarning = LaserWarning::create();
        
        setAnchorPoint(Vec2(0.5,0));
        laserwarning->setContentSize(Size(getContentSize().width/3,getContentSize().height));
        laserwarning->setPosition(Vec2(posCharacter[cntofPosCharacter],0));
        
        addChild(laserwarning,256);
    }
}

void Stage2::removeLaser_scheduler(float time) {
    laserwarning=nullptr;
}

void Stage2::shotbyLaser() {
    if(laserposition==cntofPosCharacter)
        decreaseCharacterHP();
    removeChild(laserwarning);
    schedule(schedule_selector(Stage2::removeLaser_scheduler),MIN_INTERVAL_OF_REGENERATE_LASER,1,MIN_INTERVAL_OF_REGENERATE_LASER);
}
