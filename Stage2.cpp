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
    scene->addChild(layer);
    
    return scene;
}

bool Stage2::init() {
    if(!Stage1::init()) return false;
    schedule(schedule_selector(Stage2::makeLaser_scheduler),1,INT_MAX,1);
	
	/*auto back = Sprite::create("laserlayer.png");
	back->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	back->setPosition(visibleSize.width / 2, visibleSize.height*5);
	*/
	//addChild(back);
	//removeChild(Stage::character);
	//laser->setOpacity(laser->getOpacity() - 100);
    return true;
}

void Stage2::makeLaser_scheduler(float time) {
    if(rand()%10<2 && laserwarning==nullptr) {
        laserwarning = LaserWarning::createWithVisibleSize(posCharacter,visibleSize);
        addChild(laserwarning);
    }
}
