//
//  Status.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 15.
//
//

#include "Status.h"

bool Status::init() {
    if(!Sprite::initWithFile("status_hp.png"))
        return false;

	width = this->getContentSize().width;
	score = 0;
	currentHP = 100;
	MAX_HP = 100;

    return true;
}
int Status::getWidth(){ return width; }
int Status::getHP(){ return currentHP; }
int Status::getMAX_HP(){ return MAX_HP; }
void Status::decreaseHP(int i){ currentHP -= i; }
int Status::getScore(){ return score; }
char* Status::getcoinScore(){ return coinScore; }
void Status::increaseScore(int i){ score += i; }