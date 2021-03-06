//
//  Stage2.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 19..
//
//

#include "Stage2.h"
#include <climits>

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
    status->setBladeGaugeUnit(STAGE2_BLADE_GAUGE_UNIT);
	lbTitle->setString("Stage2");

    splashScreen->setTexture(FILE_BACKGROUND+"stage2_start.png");

	building->setPositionOfBottom(-building->getContentSize().height);
    setNextBuilding(status->getBonusScore());
	return true;
}

Stage2::~Stage2() {
    unschedule(schedule_selector(Stage2::makeLaser_scheduler));
}

void Stage2::replaceNextScene() {
    Director::getInstance()->replaceScene(EndScene::createScene(*status,true));
}

bool Stage2::isLevelEnd() {
    return level==fileBuilding.cend();
}

void Stage2::makeLaser_scheduler(float time) {
    if(splashScreen !=nullptr || laserwarning!=nullptr) return;
    
    if(rand()%10<3) {
        laserposition=rand()%3;
        laserwarning = LaserWarning::create();
        laserwarning->ignoreAnchorPointForPosition(false);
        laserwarning->setAnchorPoint(Vec2(0.5,0));
        laserwarning->setContentSize(Size(getContentSize().width/3,getContentSize().height));
        laserwarning->setPosition(Vec2(posCharacter[laserposition],0));
        
        addChild(laserwarning,256);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.15);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FILE_BGM("warning.wav"));
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