//
//  BonusStage.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 28..
//
//
#include "BonusStage.h"
#include "Stage2.h"

Scene* BonusStage::createScene(Status* _status=nullptr)
{
	auto scene = Stage::createScene();
	scene->removeChildByTag(Stage::THIS_TAG);

	auto layer = BonusStage::create(_status);
	layer->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	layer->setTag(THIS_TAG);
	scene->addChild(layer);

	return scene;
}

BonusStage* BonusStage::create(Status *_status) {
    BonusStage *pRet = new BonusStage();
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

bool BonusStage::init(Status* _status) {
	if (!Stage::init(_status)) return false;

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FILE_BGM("bonus.mp3"), false);

	lbTitle->setString("Bonus");
	st_scene = Sprite::create(FILE_BACKGROUND+"bonus_stage_start.png");
	st_scene->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	st_scene->setPosition(visibleSize.width / 2, visibleSize.height * 5);
	addChild(st_scene, MENU_Z_ORDER + 2);
	schedule(schedule_selector(BonusStage::scene_scheduler), 2, 1, 2);

	cntMajor = majors.cbegin();
	makeCourses();
	
	return true;
}

void BonusStage::replace_scheduler(float time) {
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(Stage2::createScene(new Status(*status)));
}

void BonusStage::replaceNextScene() {
    schedule(schedule_selector(BonusStage::replace_scheduler),INTERVAL_REPLACE_BONUS_TO_STAGE2,1,INTERVAL_REPLACE_BONUS_TO_STAGE2);
}

bool BonusStage::onContactBegin(PhysicsContact& contact) {
	if (!Stage::onContactBegin(contact)) return false;

    auto Label = CCLabelTTF::create("", "Arial Rounded MT Bold", 30);
    bool leftorright = rand() % 2;
    Label->setPosition(character->getPosition().x + (leftorright ? 80 : -80), character->getPositionOfTop() + 80);
    Label->setPhysicsBody(PhysicsBody::createBox(Label->getContentSize()));
    Label->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
    Label->getPhysicsBody()->setCollisionBitmask(0x00);
    
	if(contact.getShapeA()->getBody()->getNode()==nullptr
       || contact.getShapeB()->getBody()->getNode()==nullptr) return true;
    
	auto course=(HONEY_TAG <= contact.getShapeA()->getBody()->getNode()->getTag()
                 && contact.getShapeA()->getBody()->getNode()->getTag() <= HARD_TAG)
                ?(contact.getShapeA()->getBody()->getNode())
                :(contact.getShapeB()->getBody()->getNode());
    string strForLabel;
    
    if(course->getTag()==HONEY_TAG) {
        Label->setColor(ccc3(0, 255, 0));
        strForLabel=" Perfect!";
        status->increaseBScore(HONEY_BSCORE);
    }
    else if(course->getTag()==NORMAL_TAG) {
        Label->setColor(ccc3(0, 0, 255));
        strForLabel=" SoSo~";
        status->increaseBScore(NORMAL_BSCORE);
    }
    else {
        Label->setColor(ccc3(255, 0, 0));
        strForLabel="Uh....Bad";
        status->increaseBScore(HARD_BSCORE);
    }
    
    status->increaseScore(status->getBScore());
    
    Label->setString(strForLabel);
    addChild(Label, MENU_Z_ORDER-1);
    
    for(int i=0; i<3; i++)
        removeChild(courses[i]);

	if (cntMajor == majors.cend())
		replaceNextScene();
	else
		makeCourses();

	return true;
}
void BonusStage::makeCourses() {
	PhysicsMaterial	material = PhysicsMaterial(10000000.0f, 0.0f, 0.0f);
	int k=0, course_select[3];

	while (k < 3) {
		int check = 0;
		course_select[k] = rand() % 3;
		int j = k;
		while (j >0) {
			j--;
			if (course_select[k] == course_select[j])
				check = 1;
		}
		if (check == 0)
			k++;
	}

    for(int i=0; i<3; i++) {
        courses[i]=Sprite::create(FILE_BOUNS_STAGE+*cntMajor + "_" + to_string(i+1) + ".png");
        courses[i]->setPosition(Vec2(posCharacter[course_select[i]], BUILDING_START_HEIGHT));
    
		auto body = PhysicsBody::createBox(courses[i]->getContentSize(), material);
        body->setCategoryBitmask(0x03);
        body->setContactTestBitmask(0x08);
        body->setCollisionBitmask(0x03);
        body->setRotationEnable(false);
        body->setVelocityLimit(BUILDING_VEL_LIMIT);
        courses[i]->setTag(HONEY_TAG+i);
        courses[i]->setPhysicsBody(body);
        addChild(courses[i]);
    }
    if(cntMajor!=majors.end())
        cntMajor++;
}