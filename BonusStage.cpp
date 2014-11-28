//
//  BonusStage.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 28..
//
//
#include "BonusStage.h"

Scene* BonusStage::createScene()
{
	auto scene = Stage::createScene();
	scene->removeChildByTag(Stage::THIS_TAG);

	auto layer = BonusStage::create();
	layer->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	layer->setTag(THIS_TAG);
	scene->addChild(layer);

	return scene;
}
bool BonusStage::init() {
	if (!Stage::init()) return false;
	
	PhysicsMaterial	material = PhysicsMaterial(10000000.0f, 0.0f, 0.0f);
	//status->blockingIsPossible.
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
		//if (status->getBonusScore(stage_num) != 1)//이부분은 잠시 확인용으로 넣어놓은거라서 제작완료되면 삭제해야됨
		//	status->increaseScore(stage_num);//이부분은 잠시 확인용으로 넣어놓은거라서 제작완료되면 삭제해야됨
		//status->setBonusScore(2, stage_num);
		status->increaseBScore(2);//꿀과목을 넣으면 score배열에 1을 넣고 아니면 0을 넣는다. 나중에 전부 더해야할듯
		status->increaseScore(status->getBScore());
	}
	else if (cntofPosCharacter == normalposcheck)
	{
		//status->setBonusScore(1, stage_num);
		status->increaseBScore(1);//꿀과목을 넣으면 score배열에 1을 넣고 아니면 0을 넣는다. 나중에 전부 더해야할듯
		status->increaseScore(status->getBScore());
	}
	else
	{
		//아무것도 안함 ㅎㅎ
	}
	removeChild(course1);
	removeChild(course2);
	removeChild(course3);
	if (stage_num < 3)
	{
		stage_num++;
		makesubject();
	}
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
				course2 = Sprite::create("c.png");//각각 다른사진을 넣어주면 될듯
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
				course2 = Sprite::create("c.png");//각각 다른사진을 넣어주면 될듯
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
				course2 = Sprite::create("c.png");//각각 다른사진을 넣어주면 될듯
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
				course2 = Sprite::create("c.png");//각각 다른사진을 넣어주면 될듯
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

	//첫번째끝
}