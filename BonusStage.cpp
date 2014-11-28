//
//  BonusStage.cpp
//  BreakGongDae
//
//  Created by �̻�� on 2014. 11. 28..
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

	for (int i = 0; i < 3; i++){
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
		// �μ���
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
								status->increaseScore(1 + status->getCombo() * 10);//�޺��� 10���� �߰�
								status->increaseCombo(1, character->getPosition());//�ϳ� �νǶ����� �޺� 1�� �����ϰ�
							}
							break;
		}
		*/
		default: Stage::onKeyPressed(keyCode, event);
	}
}
