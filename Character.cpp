//
//  Character.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 4..
//
//

#include "Character.h"


bool Character::init() {
    if(!Sprite::initWithFile("grossini.png"))
        return false;
    state = sGround;
    action = None;
    
    auto body = PhysicsBody::createBox(Sprite::getContentSize(),PhysicsMaterial(1.0f,0.0f,0.0f));
    //body->setMass(10.0f);
    body->setRotationEnable(false);
    
    //body->setCategoryBitmask(0x01); // 0001
    body->setContactTestBitmask(0x01); // 0001
    //body->setCollisionBitmask(0x03); // 0011
    setPhysicsBody(body);
    return true;
}

State Character::getState(){ return state; }
void Character::setState(State _state){ state = _state; }
ActionState Character::getActionState(){ return action; }
void Character::setActionState(ActionState _action){ action = _action; }
