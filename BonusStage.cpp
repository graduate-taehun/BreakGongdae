
//
//  BonusStage.cpp
//  BreakGongDae
//
//  Created by ¿ÃªÛ?Œ on 2014. 11. 28..
//
//
#include "BonusStage.h"
#include "Stage2.h"
//status ?�기??�?
//Director::getInstance()->replaceScene(Stage2::createScene(new Status(*status)));
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
    if (pRet && pRet->init(_status))
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

bool BonusStage::init(Status* _status) {
	if (!Stage::init(_status)) return false;
	PhysicsMaterial	material = PhysicsMaterial(10000000.0f, 0.0f, 0.0f);
	//status->blockingIsPossible.
	status->setBScore(0);
	stage_num = 0;
	makesubject();
	


	return true;
}
bool BonusStage::onContactBegin(PhysicsContact& contact) {
	if (!Stage::onContactBegin(contact)) return false;
	/*
	building->getPhysicsBody()->setCategoryBitmask(0x03);
	building->getPhysicsBody()->setContactTestBitmask(0x08);
	building->getPhysicsBody()->setCollisionBitmask(0x03);
	*/
	if (cntofPosCharacter == honeyposcheck)
	{
		//if (status->getBonusScore(stage_num) != 1)//¿Ã?�Œ∫?�¿∫ ¿·Ω??»Æ¿ŒøÎ¿?�∑Œ ?�÷æÓ≥ı¿?�∞?�∂Ûº??¡¶¿??�œ∑·µ«?��?ªË¡¶«ÿæﬂµ�?
		//	status->increaseScore(stage_num);//¿Ã?�Œ∫?�¿∫ ¿·Ω??»Æ¿ŒøÎ¿?�∑Œ ?�÷æÓ≥ı¿?�∞?�∂Ûº??¡¶¿??�œ∑·µ«?��?ªË¡¶«ÿæﬂµ�?
		//status->setBonusScore(2, stage_num);
		status->increaseBScore(2);//?�‹∞??�Ò¿�??�÷¿∏?��?score?Ëø?�ø�?1¿ª ?�÷∞Ì æ?�¥œ∏È 0¿ª ?�÷¥�?��? ?�™¡ﬂø�?¿¸?��?¥ı«ÿæﬂ«“µ�?
		status->increaseScore(status->getBScore());

		auto *Label = CCLabelTTF::create( " Perfect!", "Arial Rounded MT Bold", 30);
		Label->setColor(ccc3(0, 255, 0));

		bool leftorright2, leftorright = rand() % 2;
		Label->setPosition(character->getPosition().x + (leftorright ? 80 : -80), character->getPosition().y + 80);
		Label->setPhysicsBody(PhysicsBody::createBox(Label->getContentSize()));
		Label->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
		Label->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(Label, 4);
	}
	else if (cntofPosCharacter == normalposcheck)
	{
		//status->setBonusScore(1, stage_num);
		status->increaseBScore(1);//?�‹∞??�Ò¿�??�÷¿∏?��?score?Ëø?�ø�?1¿ª ?�÷∞Ì æ?�¥œ∏È 0¿ª ?�÷¥�?��? ?�™¡ﬂø�?¿¸?��?¥ı«ÿæﬂ«“µ�?
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
	else
	{
		auto *Label = CCLabelTTF::create("Uh....Bad", "Arial Rounded MT Bold", 30);
		Label->setColor(ccc3(255, 0, 0));

		bool leftorright2, leftorright = rand() % 2;
		Label->setPosition(character->getPosition().x + (leftorright ? 80 : -80), character->getPosition().y + 80);
		Label->setPhysicsBody(PhysicsBody::createBox(Label->getContentSize()));
		Label->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
		Label->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(Label, 4);
	}
	removeChild(course1);
	removeChild(course2);
	removeChild(course3);
	if (stage_num < 3)
	{
		stage_num++;
		makesubject();
	}
	else if (stage_num==3)
		Director::getInstance()->replaceScene(Stage2::createScene(new Status(*status)));
	return true;
}
/*
void BonusStage::setNextBuilding() {
	building = Building::create(10, "block.png", wholeNumberOfBuilding);
	building->setPosition(visibleSize.width / 2, GROUND_HEIGHT + building->getContentSize().height / 2 + BUILDING_START_HEIGHT);
	addChild(building, 2);
}

bool BonusStage::onContactBegin(PhysicsContact& contact) {
	if (!Stage::onContactBegin(contact)) return false;
	building->getPhysicsBody()->setCategoryBitmask(0x03);
	building->getPhysicsBody()->setContactTestBitmask(0x08);
	building->getPhysicsBody()->setCollisionBitmask(0x03);

	status->decreaseHP();
	status->resetCombo();

	if (status->getHP() == 0)
		Director::getInstance()->replaceScene(EndScene::createSceneWithScore(*status));

	return true;
}
*/
void BonusStage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	if (Game_Pause == 1) return;

	switch (keyCode){
		/*
		// ?�Œºˆ±�?
		case EventKeyboard::KeyCode::KEY_Z:
		{
			character->doAttackAction();

			if ((0 <= building->getPositionOfBottom() - character->getPositionOfTop()
				&& building->getPositionOfBottom() - character->getPositionOfTop()<ATTACK_RANGE)
					|| (0 <= character->getPositionOfTop() - building->getPositionOfBottom()
						&& character->getPositionOfTop() - building->getPositionOfBottom()<character->getContentSize().height / 3)
							|| abs(building->getPositionOfBottom() - GROUND_HEIGHT) <= 5) {
								if (building->attack()) {
									setNextBuilding();
									break;
								}
								status->increaseScore(1 + status->getCombo() * 10);//?ﬁ∫?�¥�?10¡°æø ?�ﬂ?��?
								status->increaseCombo(1, character->getPosition());//«œ?�™ ?�ŒΩ«∂ß?�∂¥Ÿ ?ﬁ∫??1æø ¡ı?�°«œ∞??
							}
							break;
		}
		*/
		default: Stage::onKeyPressed(keyCode, event);
	}
}
void BonusStage::makesubject()
{
	PhysicsMaterial	material = PhysicsMaterial(10000000.0f, 0.0f, 0.0f);
	int course_select[3];
	int check;
	int k, j;
	k = 0;
	while (k < 3)
	{
		check = 0;
		course_select[k] = rand() % 3;
		j = k;
		while (j >0)
		{
			j--;
			if (course_select[k] == course_select[j])
				check = 1;
		}
		if (check == 0)
			k++;
	}
	if (stage_num == 0)
	{
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0)
			{
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
				course2 = Sprite::create("c.png");//?�¢∞¢ ¥Ÿ?�•ªÁ¡�?��??�÷æÓ¡÷∏È µ?�µ�?
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
			else
			{
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
	else if (stage_num == 1)
	{
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0)
			{
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
				course2 = Sprite::create("c.png");//?�¢∞¢ ¥Ÿ?�•ªÁ¡�?��??�÷æÓ¡÷∏È µ?�µ�?
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
			else
			{
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
	else if (stage_num == 2)
	{
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0)
			{
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
				course2 = Sprite::create("c.png");//?�¢∞¢ ¥Ÿ?�•ªÁ¡�?��??�÷æÓ¡÷∏È µ?�µ�?
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
			else
			{
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
	else if (stage_num == 3)
	{
		for (int i = 0; i < 3; i++){
			if (course_select[i] == 0)
			{
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
				course2 = Sprite::create("c.png");//?�¢∞¢ ¥Ÿ?�•ªÁ¡�?��??�÷æÓ¡÷∏È µ?�µ�?
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
			else
			{
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

	//?�π?¯¬?�≥°
}