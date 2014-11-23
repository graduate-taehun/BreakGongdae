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
	laser = LaserWarning::createWithVisibleSize(posCharacter,visibleSize);
	addChild(laser);
	if (!isScheduled(schedule_selector(Stage2::laser_scheduler)))
		schedule(schedule_selector(Stage2::laser_scheduler));
	/*auto back = Sprite::create("laserlayer.png");
	back->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	back->setPosition(visibleSize.width / 2, visibleSize.height*5);
	*/
	//addChild(back);
	//removeChild(Stage::character);
	//laser->setOpacity(laser->getOpacity() - 100);
    return true;
}
void Stage2::laser_scheduler(float time)
{
	laser->setOpacity(laser->getOpacity()-1);
	if (laser->getOpacity() < 50)
	{
		unschedule(schedule_selector(Stage2::laser_scheduler));
		removeChild(laser);
	}
}