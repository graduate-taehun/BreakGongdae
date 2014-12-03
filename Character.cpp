//
//  Character.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 4..
//
//

#include "Character.h"

bool Character::init() {
    if(!Sprite::initWithFile(FILE_CHARACTER+"ch_base.png"))
        return false;
    
    auto body = PhysicsBody::createBox(Size(getContentSize().width,getContentSize().height-CHARACTER_OFFSET),PhysicsMaterial(10.0f,0.0f,0.0f),Vec2(0,-CHARACTER_OFFSET/2));

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
    if(getActionByTag(ATTACK_TAG)!=nullptr) return;
    //stopActionByTag(ATTACK_TAG);
    //if (getActionState() == None) {
    setActionState(Attacking);
    Vector<SpriteFrame*> animFrames(6);
    string str;
    for (int i = 1; i <= 6; i++){
        str=FILE_CHARACTER+"ch_attack_"+to_string(i)+".png";
        auto frame = SpriteFrame::create(str, getTextureRect());
        animFrames.pushBack(frame);
    }
    auto frame = SpriteFrame::create(FILE_CHARACTER+"ch_base.png", getTextureRect());
    animFrames.pushBack(frame);
    auto animation = Animation::createWithSpriteFrames(animFrames, ATTACK_FRAME);
    auto animate = Animate::create(animation);
        
    auto pCallback = CallFunc::create(CC_CALLBACK_0(Character::stopAttackAction, this));
    auto pSequence = Sequence::create(animate, pCallback, nullptr);
    pSequence->setTag(ATTACK_TAG);
    runAction(pSequence);
}

void Character::pre_jump_scheduler(float time) {
    setActionState(getActionState());
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
        setTexture(FILE_CHARACTER+"ch_jump_start.png");
        schedule(schedule_selector(Character::pre_jump_scheduler),TIME_PRE_JUMP,1,TIME_PRE_JUMP);
        
        
	}
}
void Character::setActionState(ActionState _action){
    action = _action;
    if(action!=Attacking) stopActionByTag(ATTACK_TAG);
    if(action==Blocking)
        setTexture(FILE_CHARACTER+"ch_blocking.png");
    if(action==Blading)
        setTexture(FILE_CHARACTER+"ch_lethal_move.png");
    else if(action==None)
        setTexture(FILE_CHARACTER+"ch_base.png");
}

float Character::getPositionOfTop() { return getPosition().y + getContentSize().height/2-CHARACTER_OFFSET; }
float Character::getPositionOfBottom() { return getPosition().y-getContentSize().height/2; }
float Character::getHeight() { return getContentSize().height-CHARACTER_OFFSET; }
State Character::getState(){ return state; }
ActionState Character::getActionState(){ return action; }
