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
enum ActionState{Attacking , None, Blocking };

class Character : public Sprite
{
    State state;
    ActionState action;
	int score;
public:
    virtual bool init();
    CREATE_FUNC(Character);
    State getState();
    void setState(State _state);
    ActionState getActionState();
    void setActionState(ActionState _action);
	int getScore();
	void increaseScore(int i);
};

#endif /* defined(__BreakGongDae__Character__) */
