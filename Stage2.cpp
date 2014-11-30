//
//  Stage2.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Stage2.h"
#include <climits>

//const vector<string> Stage2::fileBuilding={FILE_BUILDINGS_STAGE2};

Scene* Stage2::createScene(Status* _status)
{
    auto scene=Stage1::createScene();
    scene->removeChildByTag(Stage1::THIS_TAG);
    
    auto layer = Stage2::create(_status);
    layer->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    layer->setTag(THIS_TAG);
    scene->addChild(layer);
    
    return scene;
}

Stage2* Stage2::create(Status* _status) {
    Stage2 *pRet = new Stage2();
    if (pRet && pRet->init(_status)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Stage2::init(Status *_status) {
    if(!Stage1::init(_status)) return false;
    schedule(schedule_selector(Stage2::makeLaser_scheduler),1,INT_MAX,1);
    laserwarning=nullptr;
    level=Stage2::fileBuilding.cbegin();
	lbTitle->setString("Stage2");
    building->setPositionOfBottom(-building->getContentSize().height);
    setNextBuilding();
	return true;
}

Stage2::~Stage2() {
    unschedule(schedule_selector(Stage2::makeLaser_scheduler));
}

void Stage2::replaceNextScene() {
    
}

bool Stage2::isLevelEnd() {
    return level==fileBuilding.cend();
}

void Stage2::makeLaser_scheduler(float time) {
    if(rand()%10<3 && laserwarning==nullptr) {
        laserposition=rand()%3;
        laserwarning = LaserWarning::create();
        laserwarning->ignoreAnchorPointForPosition(false);
        laserwarning->setAnchorPoint(Vec2(0.5,0));
        laserwarning->setContentSize(Size(getContentSize().width/3,getContentSize().height));
        laserwarning->setPosition(Vec2(posCharacter[laserposition],0));
        
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
