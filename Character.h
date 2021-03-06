//
//  Character.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 4..
//
//

#ifndef __BreakGongDae__Character__
#define __BreakGongDae__Character__

#include "BalanceSetting.h"

enum State{ sGround, sAir };
enum ActionState{Attacking , None, Blocking, Blading };

class Character : public Sprite{
private:
    State state;
    ActionState action;
    void stopAttackAction();
    void pre_jump_scheduler(float time);
public:
    const static float ATTACK_FRAME; //=0.05f
    const static int ATTACK_TAG = 21;
    const static float CHARACTER_OFFSET; //=49
    virtual bool init();
    
    virtual void setPosition(const Vec2& _pos);
    virtual void setPosition(float x, float y);
    
    CREATE_FUNC(Character)
    
    State getState();
    void setState(State _state);
    ActionState getActionState();
    void setActionState(ActionState _action);
    float getPositionOfTop();
    float getPositionOfBottom();
    float getHeight();
    
    void doAttackAction();
};

#endif /* defined(__BreakGongDae__Character__) */
