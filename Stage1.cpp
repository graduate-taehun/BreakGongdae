//
//  Stage1.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 28..
//
//

#include "Stage1.h"
#include "Stage2.h"
#include "BonusStage.h"
#include <climits>

//const vector<string> Stage1::fileBuilding={FILE_BUILDINGS_STAGE1};

Scene* Stage1::createScene(){
    auto scene=Stage::createScene();
    scene->removeChildByTag(Stage::THIS_TAG);
    
    auto layer = Stage1::create();
    layer->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    layer->setTag(THIS_TAG);
    scene->addChild(layer);
    
    return scene;
}
Stage1* Stage1::create() {
    Stage1 *pRet = new Stage1();
    if (pRet && pRet->init(nullptr)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool Stage1::init(Status* _status=nullptr) {
    if(!Stage::init(_status)) return false;
    level=fileBuilding.cbegin();
    building=nullptr;
    blade=nullptr;
	lbTitle->setString("Stage1");

	st_scene = Sprite::create(FILE_BACKGROUND+"stage1_start.png");
	st_scene->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	st_scene->setPosition(visibleSize.width / 2, visibleSize.height * 5);
	addChild(st_scene, MENU_Z_ORDER+5);
	schedule(schedule_selector(Stage1::scene_scheduler), 2, 1, 2);

	setNextBuilding();
    return true;
}
void Stage1::setNextBuilding() {
    float posRemoved = 2500;
    if(building!=nullptr)
        posRemoved=building->getPositionOfTop();
    removeChild(building);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FILE_BGM("main.mp3"), false);

    building = Building::create(*level++);
    building->setPosition(visibleSize.width / 2, GROUND_HEIGHT+building->getContentSize().height/2+posRemoved+BUILDING_START_HEIGHT);
    addChild(building,2);
}
void Stage1::decreaseCharacterHP() {
    status->decreaseHP();
    status->resetCombo();
    
	if (status->getHP() == 0){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene(EndScene::createSceneWithScore(*status));
	}
}

void Stage1::replaceNextScene() {
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->replaceScene(BonusStage::createScene(new Status(*status)));
}

bool Stage1::onContactBegin(PhysicsContact& contact) {
    if(!Stage::onContactBegin(contact)) return false;
    building->getPhysicsBody()->setVelocity(Vec2(0,0));
    building->getPhysicsBody()->setCategoryBitmask(0x03);
    building->getPhysicsBody()->setContactTestBitmask(0x08);
    building->getPhysicsBody()->setCollisionBitmask(0x03);
    
    decreaseCharacterHP();
    return true;
}

bool Stage1::isLevelEnd() {
    return level==fileBuilding.cend();
}

void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && Game_Pause == 1) {
		CCDirector::sharedDirector()->resume();
		removeChild(P_Label);
		removeChild(P_Layer);
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Game_Pause = 0;
        return;
    }
    if(Game_Pause==1) return;
    if(isScheduled(schedule_selector(Stage1::blade_scheduler))
       || isScheduled(schedule_selector(Stage1::blade_return_scheduler))) {
        Stage::onKeyPressed(keyCode, event);
        return;
    }
    switch (keyCode){
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        {
            if (character->getState() == sGround){
                character->setState(sAir);
                character->getPhysicsBody()->setVelocity(Vec2(0,CHARACTER_JUMP_VEL));
                
                if (!isScheduled(schedule_selector(Stage1::jump_scheduler)))
                    schedule(schedule_selector(Stage1::jump_scheduler));
                break;
            }
            break;
        }
		// 부수기
        case EventKeyboard::KeyCode::KEY_Z:
        {
            character->doAttackAction();
            
            if(   (0<=building->getPositionOfBottom()-character->getPositionOfTop()
                   && building->getPositionOfBottom()-character->getPositionOfTop()<ATTACK_RANGE)
               || (0<=character->getPositionOfTop()-building->getPositionOfBottom()
                   && character->getPositionOfTop()-building->getPositionOfBottom()<character->getHeight()/3)
               || abs(building->getPositionOfBottom()-GROUND_HEIGHT)<=5) {
                status->increaseScore(1 + status->getCombo() * 10);//콤보당 10점씩 추가
                status->increaseCombo(1, Vec2(character->getPosition().x,character->getPositionOfTop()));//하나 부실때마다 콤보 1씩 증가하게
                if(building->attack(false)) {
					if (isLevelEnd())
                        replaceNextScene();
					
                    setNextBuilding();
                    break;
                }
            }
            break;
        }
        // 막기
        case EventKeyboard::KeyCode::KEY_X:
        {
            character->setActionState(Blocking);
            schedule(schedule_selector(Stage1::block_scheduler));
            break;
        }
        case EventKeyboard::KeyCode::KEY_C:
        {
			if (status->getBlade() == status->getMAX_BLADE()){
				blade = Sprite::create(FILE_ETC+"Blade.png");
                character->setActionState(Blading);
                //setTexture("ch_lethal_move.png");
				auto body = PhysicsBody::createBox(blade->getContentSize(), PhysicsMaterial(0.f, 0.5f, 0.5f));
				body->setCollisionBitmask(0x00);
				body->setGravityEnable(false);
				body->setVelocity(Vec2(0, BLADE_VELOCITY));
				blade->setPhysicsBody(body);
				blade->setAnchorPoint(Vec2(0.5, 1));
				blade->setPosition(visibleSize.width / 2, character->getPositionOfTop());
				addChild(blade, MENU_Z_ORDER - 1);

				//if (!isScheduled(schedule_selector(Stage1::blade_scheduler)))
                schedule(schedule_selector(Stage1::blade_scheduler));
			
				status->setBlade(0);
			}
        }
        default: Stage::onKeyPressed(keyCode, event);
    }
}
void Stage1::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode){
        case EventKeyboard::KeyCode::KEY_X: {
            character->setActionState(None);
            
            status->setBlockingGaugeMode(false);
            unschedule(schedule_selector(Stage1::block_scheduler));
        }
    }
}

void Stage1::block_scheduler(float time) {
    status->setBlockingGaugeMode(true);
    if(status->blockingIsPossible() && abs(character->getPositionOfTop()-building->getPositionOfBottom())<5) {
        character->stopActionByTag(Character::ATTACK_TAG);
        
        if(character->getState()==sAir) {
            status->decreaseGauge(false);
            character->getPhysicsBody()->setVelocity(Vec2(0,-CHARACTER_VEL_AFTER_BLOCKING+building->getPhysicsBody()->getVelocity().y));
        }
        
        //땅에서 막기를 사용하면 콤보가 끊어진다.
        if (character->getState() == sGround) {
            status->decreaseGauge(true);
            status->resetCombo();
        }
        
        building->getPhysicsBody()->setVelocity(Vec2(0,BUILDING_VEL_AFTER_BLOCKING));
        //if(character->getState()==sGround) unschedule(schedule_selector(Stage::block_scheduler));
    }
}
void Stage1::blade_return_scheduler(float time) {
    blade->setOpacity(0);
    blade->getPhysicsBody()->setVelocity(Vec2(0,-BLADE_VELOCITY*3));

    schedule(schedule_selector(Stage1::blade_scheduler));
    unschedule(schedule_selector(Stage1::blade_return_scheduler));
}
void Stage1::blade_scheduler(float time){
    if(isScheduled(schedule_selector(Stage1::jump_scheduler)))
        unschedule(schedule_selector(Stage1::jump_scheduler));
 
	static bool breaking=true;
    setViewPoint(blade->getPosition().y);
    if(breaking) {
        if(building->getPositionOfBottom()<=blade->getPosition().y) {
            status->increaseScore(1 + status->getCombo() * 10);//콤보당 10점씩 추가
            status->increaseCombo(1, blade->getPosition() + Vec2(0, 400));
            if (building->attack(true)){
                breaking=false;
                
                character->setActionState(Blading);
                //setTexture("ch_base.png");
                unschedule(schedule_selector(Stage1::blade_scheduler));
                schedule(schedule_selector(Stage1::blade_return_scheduler),TIME_BLADE_STOP, 1, TIME_BLADE_STOP);
            }
        }
    }
    else if(blade->getPosition().y<=visibleSize.height/2 || blade->getPosition().y<=character->getPositionOfTop()) {
        breaking=true;
        unschedule(schedule_selector(Stage1::blade_scheduler));
        schedule(schedule_selector(Stage1::jump_scheduler));
        removeChild(blade);
        setNextBuilding();
    }
}