//
//  Character.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 4..
//
//

#include "Character.h"

float Character::ATTACK_FRAME = 0.1f;
bool Character::init() {
    if(!Sprite::initWithFile("grossini.png"))
        return false;
    
    auto body = PhysicsBody::createBox(Sprite::getContentSize(),PhysicsMaterial(10.0f,0.0f,0.0f));
    //body->setMass(100);
    body->setRotationEnable(false);
	setPhysicsBody(body);
    
    setState(sGround);
    action = None;
	
    return true;
}
void Character::stopAttackAction(){
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
void Character::setState(State _state){
	state = _state;
	if (state == sGround) {
		getPhysicsBody()->setCategoryBitmask(0x04);
		getPhysicsBody()->setContactTestBitmask(0x02);
		getPhysicsBody()->setCollisionBitmask(0x01);
	}
	else {
		getPhysicsBody()->setCategoryBitmask(0x01);
		getPhysicsBody()->setContactTestBitmask(0x04);
		getPhysicsBody()->setCollisionBitmask(0x03);
	}
}
float Character::getPositionOfTop() { return getPosition().y + getContentSize().height / 2; }
State Character::getState(){ return state; }
ActionState Character::getActionState(){ return action; }
void Character::setActionState(ActionState _action){ action = _action; }