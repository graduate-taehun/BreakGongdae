//
//  Status.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 15.
//
//

#include "Status.h"
#include <cstdlib>
using namespace std;

bool Status::init() {
    if(!Layer::init())
        return false;
	
    score = 0;
    combo = 0;
	MAX_COMBO = 0;
    currentHP = MAX_HP;
    B_Score=0;
	currentblade = 0;
    currentGauge = MAX_GAUGE;
    targetGauge = MAX_GAUGE;
    
    bar_HP = Sprite::create("status_hp.png");
    float x = -bar_HP->getContentSize().width/2;
    bar_HP->setPosition(Vec2(x,bar_HP->getContentSize().height*1.5));
    bar_HP->setAnchorPoint(Vec2(0,0.5));
    addChild(bar_HP);
    
    bar_gauge = Sprite::create("status_hp.png");
    bar_gauge->setPosition(Vec2(x,bar_gauge->getContentSize().height/2));
    bar_gauge->setAnchorPoint(Vec2(0,0.5));
    addChild(bar_gauge);
	
	bar_blade = Sprite::create("status_hp.png");
	bar_blade->setPosition(Vec2(x, -bar_blade->getContentSize().height / 2));
	bar_blade->setAnchorPoint(Vec2(0, 0.5));
	addChild(bar_blade);
	
    lbScore = CCLabelTTF::create("score : 0", "futura-48.fnt", 32);
    lbScore->setPosition(Vec2(x,-lbScore->getContentSize().height*1.5));
    lbScore->setAnchorPoint(Vec2(0,0.5));
    lbScore->setColor(ccc3(0, 0, 0));
    addChild(lbScore);
    
    lbCombo = CCLabelTTF::create("combo : 0", "futura-48.fnt", 28);
    lbCombo->setPosition(Vec2(x,-lbCombo->getContentSize().height*2.5));
    lbCombo->setAnchorPoint(Vec2(0,0.5));
    lbCombo->setColor(ccc3(0, 0, 0));
    addChild(lbCombo);
    
    bar_HP->setContentSize(Size(lbCombo->getContentSize().width,bar_HP->getContentSize().height));
    bar_HP->setTextureRect(Rect(0, 0, lbCombo->getContentSize().width, bar_HP->getContentSize().height));
    
    bar_gauge->setContentSize(bar_HP->getContentSize());
    bar_gauge->setTextureRect(Rect(0, 0, lbCombo->getContentSize().width, bar_gauge->getContentSize().height));
    
	bar_blade->setContentSize(bar_blade->getContentSize());
	bar_blade->setTextureRect(Rect(0, 0, 0, bar_blade->getContentSize().height));

    setContentSize(Size(bar_HP->getContentSize().width,bar_HP->getContentSize().height*3));
        
    schedule(schedule_selector(Status::gauge_scheduler));

    return true;
}
Status::Status(const Status & st) {
    Status::init();
    
    score = st.score;
    lbScore->setString(st.lbScore->getString());
    
    combo=st.combo;
    lbCombo->setString(st.lbCombo->getString());
    
    currentHP = st.currentHP;
    bar_HP->setTextureRect(st.bar_HP->getTextureRect());
    
    B_Score=st.B_Score;
	
    MAX_COMBO = st.MAX_COMBO;
    
    currentblade=st.currentblade;
    
    currentGauge=st.currentGauge;
    
    targetGauge=st.targetGauge;
    
    bar_blade->setTextureRect(st.bar_blade->getTextureRect());
}
void Status::decreaseHP() {
    currentHP -= MAX_HP/3;
    bar_HP->setTextureRect(Rect(0, 0, getContentSize().width * currentHP /MAX_HP, bar_HP->getContentSize().height));
}

void Status::resetCombo() {
    combo = 0;
    lbCombo->setString(string("combo : ") + to_string(combo));
}

void Status::increaseCombo(int i, const Vec2& posCharacter) {

	if (currentblade<MAX_BLADE)
		currentblade += 2*i;
	bar_blade->setTextureRect(Rect(0, 0, getContentSize().width * currentblade / MAX_BLADE, bar_HP->getContentSize().height));

	combo += i;
	if (combo > MAX_COMBO)
		MAX_COMBO = combo;

	lbCombo->setString(string("combo : ") + to_string(combo));
	auto *Label_Combo = CCLabelTTF::create(to_string(combo) + " Combo!", "Arial Rounded MT Bold", 30);
	Label_Combo->setColor(ccc3(0, 0, 0));

	bool leftorright2, leftorright = rand() % 2;
	Label_Combo->setPosition(posCharacter.x + (leftorright ? 80 : -80), posCharacter.y + 80);
	Label_Combo->setPhysicsBody(PhysicsBody::createBox(Label_Combo->getContentSize()));
	Label_Combo->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
	Label_Combo->getPhysicsBody()->setCollisionBitmask(0x00);
	getParent()->addChild(Label_Combo, 4);

	int num = 0, check[3];
	int block_n = rand() % 3;
	int block_select = rand() % 2;

	auto frag1 = Sprite::create("fragment_1.png");
	auto frag2 = Sprite::create("fragment_2.png");

	Sprite* frag;
	while (num <= block_n){
		leftorright2 = rand() % 2;
		check[num] = rand() % 100;
		
		if (block_select == 0){
			frag = Sprite::create("fragment_1.png");
			if (check[num] % 2 == 1)
				frag->setPosition(posCharacter.x + check[num] * 2, posCharacter.y + 80);
			else
				frag->setPosition(posCharacter.x - check[num] * 2, posCharacter.y + 80);
			
			frag->setPhysicsBody(PhysicsBody::createBox(frag->getContentSize()));
			frag->getPhysicsBody()->setVelocity(Vec2((leftorright2 ? 150 : -150), 40));
			frag->getPhysicsBody()->setCollisionBitmask(0x00);
			getParent()->addChild(frag, 3);
		}
		else if (block_select == 1){
			frag = Sprite::create("fragment_2.png");
			if (check[num] % 2 == 1)
				frag->setPosition(posCharacter.x + check[num] * 2, posCharacter.y + 80);
			else
				frag->setPosition(posCharacter.x - check[num] * 2, posCharacter.y + 80);
			
			frag->setPhysicsBody(PhysicsBody::createBox(frag->getContentSize()));
			frag->getPhysicsBody()->setVelocity(Vec2((leftorright2 ? 150 : -150), 40));
			frag->getPhysicsBody()->setCollisionBitmask(0x00);
			getParent()->addChild(frag, 3);
		}
		num++;
	}
}
void Status::increaseScore(int i) {
    score += i;
    lbScore->setString(string("score : ") + to_string(score));
}

int Status::getHP(){ return currentHP; }
int Status::getMAX_HP(){ return MAX_HP; }
int Status::getScore(){ return score; }
int Status::getCombo(){ return combo; }
int Status::getBlade(){ return currentblade; }
int Status::getMAX_COMBO(){ return MAX_COMBO; }
int Status::getMAX_BLADE(){ return MAX_BLADE; }
void Status::setBlade(int b){ currentblade = b; }
void Status::increaseBScore(int i) { B_Score = B_Score + i; }
int Status::getBScore() { return B_Score; }

void Status::gauge_scheduler(float time) {
    if(currentGauge>targetGauge) currentGauge-=0.5;
    else if(currentGauge<targetGauge) currentGauge+=0.5;
    //else targetGauge=MAX_GAUGE;
    bar_gauge->setTextureRect(Rect(0, 0, getContentSize().width * currentGauge /MAX_GAUGE, bar_gauge->getContentSize().height));
}

bool Status::blockingIsPossible() {
    if(currentGauge>=MIN_COST_BLOCKING) return true;
    return false;
}
void Status::decreaseGauge(bool onGround) {
    if(onGround || currentGauge-COST_BLOCKING<0) currentGauge=0;
    else currentGauge-=COST_BLOCKING;
    bar_gauge->setTextureRect(Rect(0, 0, getContentSize().width * currentGauge /MAX_GAUGE, bar_gauge->getContentSize().height));
}
void Status::setBlockingGaugeMode(bool decrease) {
    if(decrease && blockingIsPossible()) targetGauge=0;
    else targetGauge=MAX_GAUGE;
}