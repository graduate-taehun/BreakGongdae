//
//  BonusStage.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 28..
//
//
#include "BonusStage.h"

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

BonusStage* BonusStage::create(Status* _status) {
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
	int course_select[3];
	int k, j;
	int check;
	stage_num = -1;
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
	for (int i = 0; i < 3; i++){
		if (course_select[i] == 0)
		{
			auto course = Sprite::create("b.png");
			course->setPosition(posCharacter[i], 1000);
			auto body = PhysicsBody::createBox(course->getContentSize(), material);
			body->setCategoryBitmask(0x03);
			body->setContactTestBitmask(0x08);
			body->setCollisionBitmask(0x03);
			body->setRotationEnable(false);
			body->setVelocityLimit(BUILDING_VEL_LIMIT);
			course->setPhysicsBody(body);
			this->addChild(course);
			poscheck = i;
		}
		else if (course_select[i] == 1)
		{
			auto course = Sprite::create("c.png");//각각 다른사진을 넣어주면 될듯
			course->setPosition(posCharacter[i], 1000);
			auto body = PhysicsBody::createBox(course->getContentSize(), material);
			body->setCategoryBitmask(0x03);
			body->setContactTestBitmask(0x00);
			body->setCollisionBitmask(0x03);
			body->setRotationEnable(false);
			body->setVelocityLimit(BUILDING_VEL_LIMIT);
			course->setPhysicsBody(body);
			this->addChild(course);
		}
		else
		{
			auto course = Sprite::create("d.png");
			course->setPosition(posCharacter[i], 1000);
			auto body = PhysicsBody::createBox(course->getContentSize(), material);
			body->setCategoryBitmask(0x03);
			body->setContactTestBitmask(0x00);
			body->setCollisionBitmask(0x03);
			body->setRotationEnable(false);
			body->setVelocityLimit(BUILDING_VEL_LIMIT);
			course->setPhysicsBody(body);
			this->addChild(course);
		}
	}
	stage_num++;

	return true;
}
bool BonusStage::onContactBegin(PhysicsContact& contact) {
	if (!Stage::onContactBegin(contact)) return false;
	/*
	building->getPhysicsBody()->setCategoryBitmask(0x03);
	building->getPhysicsBody()->setContactTestBitmask(0x08);
	building->getPhysicsBody()->setCollisionBitmask(0x03);
	*/
	if (cntofPosCharacter == poscheck)
	{
		if (score[stage_num] != 1)
			status->increaseScore(100);
		score[stage_num] = 1;//꿀과목을 넣으면 score배열에 1을 넣고 아니면 0을 넣는다. 나중에 전부 더해야할듯
	}
	else
	{
		score[stage_num] = 0;
	}
	removeChild(this);
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
		// 부수기
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
								status->increaseScore(1 + status->getCombo() * 10);//콤보당 10점씩 추가
								status->increaseCombo(1, character->getPosition());//하나 부실때마다 콤보 1씩 증가하게
							}
							break;
		}
		*/
		default: Stage::onKeyPressed(keyCode, event);
	}
}
