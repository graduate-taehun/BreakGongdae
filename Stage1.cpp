//
//  Stage1.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 28..
//
//

#include "Stage1.h"
#include "Stage2.h"
Scene* Stage1::createScene()
{
    auto scene=Stage::createScene();
    scene->removeChildByTag(Stage::THIS_TAG);
    
    auto layer = Stage1::create();
    layer->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    layer->setTag(THIS_TAG);
    scene->addChild(layer);
    
    return scene;
}

bool Stage1::init() {
    if(!Stage::init()) return false;
    //fileBuilding=queue<string>("Mueunjae.png", "RC.png", "78.png", "Old_dormitory.png", "Jigok.png");
    //fileBuilding[10]={};
    building=nullptr;
    setNextBuilding();
    return true;
}

void Stage1::setNextBuilding() {
    Vec2 posRemoved(0,0);
    if(building!=nullptr)
        posRemoved=building->getPosition();
    removeChild(building);
    building = Building::create(10, "block.png",wholeNumberOfBuilding);
    building->setPosition(visibleSize.width / 2, GROUND_HEIGHT+building->getContentSize().height/2+posRemoved.y+BUILDING_START_HEIGHT);
    addChild(building,2);
}

void Stage1::decreaseCharacterHP() {
    status->decreaseHP();
    status->resetCombo();
    
    if (status->getHP() == 0)
        Director::getInstance()->replaceScene(EndScene::createSceneWithScore(*status));
}

bool Stage1::onContactBegin(PhysicsContact& contact) {
    if(!Stage::onContactBegin(contact)) return false;
    building->getPhysicsBody()->setCategoryBitmask(0x03);
    building->getPhysicsBody()->setContactTestBitmask(0x08);
    building->getPhysicsBody()->setCollisionBitmask(0x03);
    
    decreaseCharacterHP();
    return true;
}

void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
    if(Game_Pause==1) return;
    switch (keyCode){
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        {
            if (character->getState() == sGround){
                character->setState(sAir);
                character->getPhysicsBody()->setVelocity(Vec2(0,CHARACTER_JUMP_VEL));
                
                //점프동작
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
                   && character->getPositionOfTop()-building->getPositionOfBottom()<character->getContentSize().height/3)
               || abs(building->getPositionOfBottom()-GROUND_HEIGHT)<=5) {
                if(building->attack()) {
					if (1)//이거 대신에 stage전환인자확인을 해줘야됨)
					{
						Director::getInstance()->replaceScene(Stage2::createScene());
					}
                    setNextBuilding();
                    break;
                }
                status->increaseScore(1 + status->getCombo() * 10);//콤보당 10점씩 추가
                status->increaseCombo(1, character->getPosition());//하나 부실때마다 콤보 1씩 증가하게
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
            blade = Sprite::create("Blade.png");
            auto material = PhysicsMaterial(0.1f, 1.0f, 0.5f);
            auto body = PhysicsBody::createBox(blade->getContentSize(), material);
            blade->setPhysicsBody(body);
            blade->setPosition(visibleSize.width / 2, character->getPosition().y);
            blade->getPhysicsBody()->setCollisionBitmask(0x00);
            addChild(blade);
            if (!isScheduled(schedule_selector(Stage1::blade_scheduler)))
                schedule(schedule_selector(Stage1::blade_scheduler));
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
    if(status->blockingIsPossible() && abs(character->getPositionOfTop()-building->getPositionOfBottom())<10) {
        character->stopActionByTag(Character::ATTACK_TAG);
        
        if(character->getState()==sAir) {
            status->decreaseGauge(false);
            character->getPhysicsBody()->setVelocity(Vec2(0,-CHARACTER_VEL_AFTER_BLOCKING+building->getPhysicsBody()->getVelocity().y));
        }
        if (character->getState() == sGround) {
            status->decreaseGauge(true);
            status->resetCombo();
        }
        //땅에서 막기를 사용하면 콤보가 끊어진다. 나중에 죽었을때도 콤보가 끊어지도록 수정해야함
        
        building->getPhysicsBody()->setVelocity(Vec2(0,BUILDING_VEL_AFTER_BLOCKING));
        //if(character->getState()==sGround) unschedule(schedule_selector(Stage::block_scheduler));
    }
}

void Stage1::blade_scheduler(float time)
{
    //
    if (blade->getPosition().y >= visibleSize.height / 2) {
        //배경을 내림
        status->setPosition(visibleSize.width / 8, blade->getPosition().y + visibleSize.height * 8 / 20);
        lbTitle->setPosition(visibleSize.width * 3 / 4, blade->getPosition().y + visibleSize.height * 9 / 20);
        btnClose->setPosition(Vec2(visibleSize.width - btnClose->getContentSize().width / 2, blade->getPosition().y - visibleSize.height / 2 + btnClose->getContentSize().height / 2));
        
        this->setPosition(Vec2(this->getPosition().x, -blade->getPosition().y + visibleSize.height / 2));
        //this->getScene()->getChildByTag(GROUND_TAG)->setPosition(Vec2(this->getScene()->getChildByTag(GROUND_TAG)->getPosition().x, GROUND_HEIGHT / 2 + (visibleSize.height / 2 - character->getPosition().y)));
    }
    else if (blade->getPosition().y - blade->getContentSize().height <= GROUND_HEIGHT + 10) {
        blade->getPhysicsBody()->setVelocity(Vec2(0., 0.));
        blade->setPosition(Vec2(blade->getPosition().x, GROUND_HEIGHT + blade->getContentSize().height / 2));
        
    }
    else {
        //배경 안움직임
        //status->setPosition(posStatus);
        //lbTitle->setPosition(posTitle);
        //btnClose->setPosition(posClose);
        
        this->setPosition(this->getPosition().x, 0);
        //this->getScene()->getChildByTag(GROUND_TAG)->setPosition(this->getScene()->getChildByTag(GROUND_TAG)->getPosition().x, GROUND_HEIGHT / 2);
    }
    
    //
    Vec2 Pos;
    Pos = blade->getPosition();
    if (building->attack())
    {
        setNextBuilding();
        unschedule(schedule_selector(Stage1::blade_scheduler));
        removeChild(blade);
    }
    status->increaseScore(1 + status->getCombo() * 10);//콤보당 10점씩 추가
    status->increaseCombo(1, Pos + Vec2(0, 400));
}