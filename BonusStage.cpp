//
//  BonusStage.cpp
//  BreakGongDae
//
//  Created by ¬ø√É¬™√õ?≈í on 2014. 11. 28..
//
//
#include "BonusStage.h"
#include "Stage2.h"

Scene* BonusStage::createScene(Status* _status)
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
	
	//status->blockingIsPossible.
	cntMajor = -1;
    majors[0]="EECE";
    majors[1]="CSE1";
    majors[2]="MATH";
    majors[3]="CSE2";
    
	makeCourses();

	return true;
}

void BonusStage::replace_scheduler(float time) {
    Director::getInstance()->replaceScene(Stage2::createScene(new Status(*status)));
}

void BonusStage::replaceNextScene() {
    schedule(schedule_selector(BonusStage::replace_scheduler),INTERVAL_REPLACE_BONUS_TO_STAGE2,1,INTERVAL_REPLACE_BONUS_TO_STAGE2);
}

bool BonusStage::onContactBegin(PhysicsContact& contact) {
	if (!Stage::onContactBegin(contact)) return false;
	/*
	building->getPhysicsBody()->setCategoryBitmask(0x03);
	building->getPhysicsBody()->setContactTestBitmask(0x08);
	building->getPhysicsBody()->setCollisionBitmask(0x03);
	*/
    
    auto Label = CCLabelTTF::create("", "Arial Rounded MT Bold", 30);
    bool leftorright = rand() % 2;
    Label->setPosition(character->getPosition().x + (leftorright ? 80 : -80), character->getPosition().y + 80);
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
    
	/*if (cntofPosCharacter == honeyposcheck)
	{
		// if (status->getBonusScore(stage_num) != 1)//¬ø√É?´≈í‚à´?ì¬ø‚à´ ¬ø¬∑Œ©??¬ª√Ü¬ø≈í√∏√é¬ø?è‚àë≈í ?•√∑√¶√ì‚â•ƒ±¬ø?´‚àû?à‚àÇ√õ¬∫??¬°¬∂¬ø??∏≈ì‚àë¬∑¬µ¬´?è√?¬™√ã¬°¬∂¬´√ø√¶Ô¨Ç¬µ¬?
		// status->increaseScore(stage_num);//¬ø√É?´≈í‚à´?ì¬ø‚à´ ¬ø¬∑Œ©??¬ª√Ü¬ø≈í√∏√é¬ø?è‚àë≈í ?•√∑√¶√ì‚â•ƒ±¬ø?´‚àû?à‚àÇ√õ¬∫??¬°¬∂¬ø??∏≈ì‚àë¬∑¬µ¬´?è√?¬™√ã¬°¬∂¬´√ø√¶Ô¨Ç¬µ¬?
		// status->setBonusScore(2, stage_num);
		status->increaseBScore(2);//?§‚Äπ‚àû??è√í¬ø¬??•√∑¬ø‚àè?è√?score?√ã√∏?†√∏¬?1¬ø¬™ ?•√∑‚àû√å √¶?Ü¬•≈ì‚àè√à 0¬ø¬™ ?•√∑¬•¬?•≈? ?•‚Ñ¢¬°Ô¨Ç√∏¬?¬ø¬∏?´≈?¬•ƒ±¬´√ø√¶Ô¨Ç¬´‚Äú¬µ√?
		status->increaseScore(status->getBScore());

		auto *Label = CCLabelTTF::create(" Perfect!", "Arial Rounded MT Bold", 30);
		Label->setColor(ccc3(0, 255, 0));

		bool leftorright = rand() % 2;
		Label->setPosition(character->getPosition().x + (leftorright ? 80 : -80), character->getPosition().y + 80);
		Label->setPhysicsBody(PhysicsBody::createBox(Label->getContentSize()));
		Label->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
		Label->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(Label, 4);
	}
	else if (cntofPosCharacter == normalposcheck)
	{
		//status->setBonusScore(1, stage_num);
		status->increaseBScore(1);//?§‚Äπ‚àû??è√í¬ø¬??•√∑¬ø‚àè?è√?score?√ã√∏?†√∏¬?1¬ø¬™ ?•√∑‚àû√å √¶?Ü¬•≈ì‚àè√à 0¬ø¬™ ?•√∑¬•¬?•≈? ?•‚Ñ¢¬°Ô¨Ç√∏¬?¬ø¬∏?´≈?¬•ƒ±¬´√ø√¶Ô¨Ç¬´‚Äú¬µ√?
		status->increaseScore(status->getBScore());
		auto *Label = CCLabelTTF::create(" SoSo~", "Arial Rounded MT Bold", 30);
		Label->setColor(ccc3(0, 0, 255));

		bool leftorright2, leftorright = rand() % 2;
		Label->setPosition(character->getPosition().x + (leftorright ? 80 : -80), character->getPosition().y + 80);
		Label->setPhysicsBody(PhysicsBody::createBox(Label->getContentSize()));
		Label->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
		Label->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(Label, 4);
	}
	else{
		auto *Label = CCLabelTTF::create("Uh....Bad", "Arial Rounded MT Bold", 30);
		Label->setColor(ccc3(255, 0, 0));

		bool leftorright2, leftorright = rand() % 2;
		Label->setPosition(character->getPosition().x + (leftorright ? 80 : -80), character->getPosition().y + 80);
		Label->setPhysicsBody(PhysicsBody::createBox(Label->getContentSize()));
		Label->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
		Label->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(Label, 4);
	}*/
    for(int i=0; i<3; i++) {
        removeChild(courses[i]);
    }
    if(cntMajor==3) replaceNextScene();
    makeCourses();
	return true;
}

void BonusStage::makeCourses() {
	PhysicsMaterial	material = PhysicsMaterial(10000000.0f, 0.0f, 0.0f);
	int course_select[3];
	int k=0;

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
    cntMajor++;
    for(int i=0; i<3; i++) {
        courses[i]=Sprite::create(string()+(char)(i+'b')+".png");
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
	/*if (stage_num == 0){
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0){
				course1 = Sprite::create("b.png");
				course1->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course1->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x08);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course1->setTag(100 + stage_num);
				course1->setPhysicsBody(body);
				this->addChild(course1);
				honeyposcheck = i;
			}
			else if (course_select[i] == 1){
				course2 = Sprite::create("c.png");//?û¬¢‚àû¬¢ ¬•≈∏?è‚Ä¢¬™√Å¬°¬?ø¬??•√∑√¶√ì¬°√∑‚àè√à ¬µ?¶¬µ√?
				course2->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course2->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course2->setTag(100 + stage_num);
				course2->setPhysicsBody(body);
				this->addChild(course2);
				normalposcheck = i;
			}
			else{
				course3 = Sprite::create("d.png");
				course3->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course3->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course3->setTag(100 + stage_num);
				course3->setPhysicsBody(body);
				this->addChild(course3);
			}
		}
	}
	else if (stage_num == 1){
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0){
				course1 = Sprite::create("b.png");
				course1->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course1->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x08);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course1->setTag(100 + stage_num);
				course1->setPhysicsBody(body);
				this->addChild(course1);
				honeyposcheck = i;
			}
			else if (course_select[i] == 1)
			{
				course2 = Sprite::create("c.png");//?û¬¢‚àû¬¢ ¬•≈∏?è‚Ä¢¬™√Å¬°¬?ø¬??•√∑√¶√ì¬°√∑‚àè√à ¬µ?¶¬µ√?
				course2->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course2->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course2->setTag(100 + stage_num);
				course2->setPhysicsBody(body);
				this->addChild(course2);
				normalposcheck = i;
			}
			else{
				course3 = Sprite::create("d.png");
				course3->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course3->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course3->setTag(100 + stage_num);
				course3->setPhysicsBody(body);
				this->addChild(course3);
			}
		}
	}
	else if (stage_num == 2){
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0){
				course1 = Sprite::create("b.png");
				course1->setPosition(posCharacter[i], 1000);
			
				auto body = PhysicsBody::createBox(course1->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x08);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course1->setTag(100 + stage_num);
				course1->setPhysicsBody(body);
				this->addChild(course1);
				honeyposcheck = i;
			}
			else if (course_select[i] == 1){
				course2 = Sprite::create("c.png");//?û¬¢‚àû¬¢ ¬•≈∏?è‚Ä¢¬™√Å¬°¬?ø¬??•√∑√¶√ì¬°√∑‚àè√à ¬µ?¶¬µ√?
				course2->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course2->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course2->setTag(100 + stage_num);
				course2->setPhysicsBody(body);
				this->addChild(course2);
				normalposcheck = i;
			}
			else{
				course3 = Sprite::create("d.png");
				course3->setPosition(posCharacter[i], 1000);
				
				auto body = PhysicsBody::createBox(course3->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course3->setTag(100 + stage_num);
				course3->setPhysicsBody(body);
				this->addChild(course3);
			}
		}
	}
	else if (stage_num == 3){
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0){
				course1 = Sprite::create("b.png");
				course1->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course1->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x08);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course1->setTag(100 + stage_num);
				course1->setPhysicsBody(body);
				this->addChild(course1);
				honeyposcheck = i;
			}
			else if (course_select[i] == 1)
			{
				course2 = Sprite::create("c.png");//?û¬¢‚àû¬¢ ¬•≈∏?è‚Ä¢¬™√Å¬°¬?ø¬??•√∑√¶√ì¬°√∑‚àè√à ¬µ?¶¬µ√?
				course2->setPosition(posCharacter[i], 1000);

				auto body = PhysicsBody::createBox(course2->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course2->setTag(100 + stage_num);
				course2->setPhysicsBody(body);
				this->addChild(course2);
				normalposcheck = i;
			}
			else{
				course3 = Sprite::create("d.png");
				course3->setPosition(posCharacter[i], 1000);
				
				auto body = PhysicsBody::createBox(course3->getContentSize(), material);
				body->setCategoryBitmask(0x03);
				body->setContactTestBitmask(0x00);
				body->setCollisionBitmask(0x03);
				body->setRotationEnable(false);
				body->setVelocityLimit(BUILDING_VEL_LIMIT);
				course3->setTag(100 + stage_num);
				course3->setPhysicsBody(body);
				this->addChild(course3);
			}
		}
	}*/
}