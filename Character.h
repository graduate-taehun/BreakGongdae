//
//  Character.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 4..
//
//

#ifndef __BreakGongDae__Character__
#define __BreakGongDae__Character__

#include "cocos2d.h"
USING_NS_CC;

enum State{ sGround, sAir };
enum Attack{ Y, N, B };

class Character : public Sprite
{
    State state;
    Attack attack;
public:
    virtual bool init();
    CREATE_FUNC(Character);
    State getState();
    void setState(State _state);
    Attack getAttack();
    void setAttack(Attack _attack);
};

#endif /* defined(__BreakGongDae__Character__) */
