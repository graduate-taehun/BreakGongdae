//
//  Character.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 4..
//
//

#include "Character.h"

float Character::ATTACK_FRAME = 0.1f;
/*
 1. 캐릭터가 땅에 있을 때
 0011
 0100
 0001
 
 2. 캐릭터가 점프했을 때
 0001
 0100
 0011
 
 3. 빌딩
 0011
 1000
 0001
 
 4. 바닥
 1001
 0011
 0011
 */
bool Character::init() {
    if(!Sprite::initWithFile("grossini.png"))
        return false;
    state = sGround;
    action = None;
    
    auto body = PhysicsBody::createBox(Sprite::getContentSize(),PhysicsMaterial(1.0f,0.0f,0.0f));
    
    body->setRotationEnable(false);
	body->setCategoryBitmask(0x02);
	body->setContactTestBitmask(0x02);
	body->setCollisionBitmask(0x01);

	setPhysicsBody(body);
    return true;
}
void Character::stopAttackAction()
{
    setActionState(None);
}

void Character::doAttackAction() {
    stopActionByTag(ATTACK_TAG);
    //if (getActionState() == None) {
    setActionState(Attacking);
    Vector<SpriteFrame*> animFrames(3);
    char str[100] = { 0 };
    for (int i = 1; i < 4; i++){
        sprintf(str, "grossini_dance_%02d.png", i);
        auto frame = SpriteFrame::create(str, Rect(0, 0, 80, 115));
        animFrames.pushBack(frame);
    }
    auto frame = SpriteFrame::create("grossini_dance_05.png", Rect(0, 0, 80, 115));
    animFrames.pushBack(frame);
    auto animation = Animation::createWithSpriteFrames(animFrames, ATTACK_FRAME);
    auto animate = Animate::create(animation);
    
    
    auto pCallback = CallFunc::create(CC_CALLBACK_0(Character::stopAttackAction, this));
    auto pSequence = Sequence::create(animate, pCallback, nullptr);
    pSequence->setTag(ATTACK_TAG);
    runAction(pSequence);
        
}

float Character::getPositionOfTop() {
    return getPosition().y+getContentSize().height/2;
}

State Character::getState(){ return state; }
void Character::setState(State _state){
    state = _state;
    if(state==sGround) {
        getPhysicsBody()->setCategoryBitmask(0x03);
        getPhysicsBody()->setContactTestBitmask(0x04);
        getPhysicsBody()->setCollisionBitmask(0x01);
    }
    else {
        getPhysicsBody()->setCategoryBitmask(0x01);
        getPhysicsBody()->setContactTestBitmask(0x04);
        getPhysicsBody()->setCollisionBitmask(0x03);
    }
}
ActionState Character::getActionState(){ return action; }
void Character::setActionState(ActionState _action){ action = _action; }

