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
    attack = N;
    
    auto body = PhysicsBody::createBox(Sprite::getContentSize(), PhysicsMaterial(1., 0., 0.), Vec2(0, 0));
    body->setAngularVelocityLimit(0);
    body->setCategoryBitmask(0x01); // 0001
    body->setContactTestBitmask(0x04); // 0100
    body->setCollisionBitmask(0x03); // 0011
    Sprite::setPhysicsBody(body);
    return true;
}

State Character::getState(){ return state; }
void Character::setState(State _state){ state = _state; }
Attack Character::getAttack(){ return attack; }
void Character::setAttack(Attack _attack){ attack = _attack; }