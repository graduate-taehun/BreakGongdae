//
//  Status.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 15.
//
//

#include "Status.h"

bool Status::init() {
    if(!Layer::init())
        return false;
    
    
    
    bar_HP = Sprite::create("status_hp.png");
    float x=-bar_HP->getContentSize().width/2;
    bar_HP->setPosition(Vec2(x,bar_HP->getContentSize().height*3/2));
    bar_HP->setAnchorPoint(Vec2(0,0.5));
    addChild(bar_HP);
    
    lbScore = CCLabelTTF::create("score : 0", "futura-48.fnt", 32);
    lbScore->setPosition(Vec2(x,0));
    lbScore->setAnchorPoint(Vec2(0,0.5));
    lbScore->setColor(ccc3(0, 0, 0));
    addChild(lbScore);
    
    lbCombo = CCLabelTTF::create("combo : 0", "futura-48.fnt", 28);
    lbCombo->setPosition(Vec2(x,-lbCombo->getContentSize().height*3/2));
    lbCombo->setAnchorPoint(Vec2(0,0.5));
    lbCombo->setColor(ccc3(0, 0, 0));
    addChild(lbCombo);
    
    bar_HP->setContentSize(Size(lbCombo->getContentSize().width,bar_HP->getContentSize().height));
    bar_HP->setTextureRect(Rect(0, 0, lbCombo->getContentSize().width, bar_HP->getContentSize().height));
    
    setContentSize(Size(bar_HP->getContentSize().width,bar_HP->getContentSize().height*3));

	score = 0;
	currentHP = 30;
	MAX_HP = 30;
    Combo=0;

    return true;
}

using namespace std;

void Status::decreaseHP() {
    currentHP -= MAX_HP/3;
    bar_HP->setTextureRect(Rect(0, 0, getContentSize().width * currentHP /MAX_HP, bar_HP->getContentSize().height));
}

void Status::resetCombo() {
    Combo = 0;
    lbCombo->setString(string("combo : ") + to_string(Combo));
}

void Status::increaseCombo(int i, const Vec2& posCharacter) {
    Combo+=i;
    lbCombo->setString(string("combo : ") + to_string(Combo));
    auto *Label_Combo = CCLabelTTF::create(to_string(Combo)+" Combo!", "futura-48.fnt", 25);
    Label_Combo->setColor(ccc3(0, 0, 0));
    
    bool leftorright=rand() % 2;
    Label_Combo->setPosition(posCharacter.x + (leftorright?80:-80), posCharacter.y + 80);
    Label_Combo->setPhysicsBody(PhysicsBody::createBox(Label_Combo->getContentSize()));
    Label_Combo->getPhysicsBody()->setVelocity(Vec2((leftorright?100:-100),30));
    Label_Combo->getPhysicsBody()->setCollisionBitmask(0x00);
    getParent()->addChild(Label_Combo);
}
//char* Status::getcoinCombo(){ return coinCombo; }

void Status::increaseScore(int i) {
    score += i;
    lbScore->setString(string("score : ") + to_string(score));
}

int Status::getHP(){ return currentHP; }
int Status::getMAX_HP(){ return MAX_HP; }
int Status::getScore(){ return score; }
//char* Status::getcoinScore(){ return coinScore; }
int Status::getCombo(){ return Combo; }