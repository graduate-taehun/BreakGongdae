//
//  Status.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 15.
//
//

#include "Status.h"

bool Status::initWithHeight(float height) {
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
    
    
	state = Sprite::create(FILE_ETC + "gauge.png");
	state->setPosition(Vec2(0, state->getContentSize().height/2));
	state->setAnchorPoint(Vec2(0, 0.5));
	addChild(state);
    
    STATUS_WIDTH=state->getContentSize().width;
    setContentSize(Size(STATUS_WIDTH,height));
    ignoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2(0.5,0.5));

    bar_HP = Sprite::create(FILE_ETC+"life.png");
	bar_HP->setPosition(Vec2(0, state->getContentSize().height+bar_HP->getContentSize().height/2));
    bar_HP->setAnchorPoint(Vec2(0,0.5));
    addChild(bar_HP);
    
    bar_gauge = Sprite::create(FILE_ETC + "gauge_bar.png");
    bar_gauge->setPosition(Vec2(BAR_X,BAR_GAUGE_Y));
    bar_gauge->setAnchorPoint(Vec2(0,0.5));
    addChild(bar_gauge);
    
    GAUGE_WIDTH=bar_gauge->getContentSize().width;
	
	bar_blade = Sprite::create(FILE_ETC+"gauge_bar.png");
	bar_blade->setPosition(Vec2(BAR_X, BAR_BLADE_Y));
	bar_blade->setAnchorPoint(Vec2(0, 0.5));
	addChild(bar_blade);

	lbScore = LabelTTF::create("Score : 0", "Arial Rounded MT Bold", 30);
    lbScore->setPosition(Vec2(LABEL_X, height-lbScore->getContentSize().height/2-LABEL_INTERVAL_Y));
    lbScore->setAnchorPoint(Vec2(0,0.5));
    lbScore->setColor(Color3B(0, 0, 0));
    addChild(lbScore);
    
	lbCombo = LabelTTF::create("Combo : 0", "Arial Rounded MT Bold", 25);
    lbCombo->setPosition(Vec2(LABEL_X, height-lbScore->getContentSize().height-lbCombo->getContentSize().height/2-LABEL_INTERVAL_Y));
    lbCombo->setAnchorPoint(Vec2(0,0.5));
    lbCombo->setColor(Color3B(0, 0, 0));
    addChild(lbCombo);
    
	bar_blade->setTextureRect(Rect(0, 0, currentblade, bar_gauge->getContentSize().height));
        
    schedule(schedule_selector(Status::gauge_scheduler));

    return true;
}

Status* Status::createWithHeight(float height) {
    Status *pRet = new Status();
    if (pRet && pRet->initWithHeight(height)) {
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Status::Status(const Status & st) {
    Status::initWithHeight(st.getContentSize().height);
    
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
    bar_HP->setTextureRect(Rect(0, 0, GAUGE_WIDTH * currentHP /MAX_HP, bar_HP->getContentSize().height));
}

void Status::resetCombo() {
    combo = 0;
    lbCombo->setString(string("Combo : ") + to_string(combo));
}

void Status::increaseCombo(int i, const Vec2& posCharacter, bool isBlade) {

	if (currentblade<MAX_BLADE && !isBlade)
        increaseBlade(i);

	combo += i;
	if (combo > MAX_COMBO) MAX_COMBO = combo;

	lbCombo->setString(string("Combo : ") + to_string(combo));
	auto *Label_Combo = CCLabelTTF::create(to_string(combo) + " Combo!", "Arial Rounded MT Bold", 30);
	Label_Combo->setColor(Color3B(0, 0, 0));

	bool leftorright = rand() % 2;
	Label_Combo->setPosition(posCharacter.x + (leftorright ? 80 : -80), posCharacter.y + 80);
	Label_Combo->setPhysicsBody(PhysicsBody::createBox(Label_Combo->getContentSize()));
	Label_Combo->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
	Label_Combo->getPhysicsBody()->setCollisionBitmask(0x00);
	getParent()->addChild(Label_Combo, 4);

	int block_n = rand() % 3;
	int block_select = rand() % 2;

	Sprite* frag;
    for(int i=0; i<=block_n; i++) {
		leftorright = rand() % 2;
		int check = rand() % 100;

        frag = Sprite::create(FILE_ETC+"fragment_"+to_string(block_select+1)+".png");
        if (check % 2 == 1)
            frag->setPosition(posCharacter.x + check * 2, posCharacter.y + 80);
        else
            frag->setPosition(posCharacter.x - check * 2, posCharacter.y + 80);
        
        frag->setPhysicsBody(PhysicsBody::createBox(frag->getContentSize()));
        frag->getPhysicsBody()->setVelocity(Vec2((leftorright ? 150 : -150), 40));
        frag->getPhysicsBody()->setCollisionBitmask(0x00);
        getParent()->addChild(frag, 3);
		i++;
	}
}

void Status::increaseBlade(int _blade) {
    currentblade += BLADE_GAUGE_UNIT*_blade;
    if(currentblade>MAX_BLADE) currentblade=MAX_BLADE;
    bar_blade->setTextureRect(Rect(0, 0, GAUGE_WIDTH * currentblade / MAX_BLADE, bar_gauge->getContentSize().height));
}

void Status::resetBlade() {
    currentblade=0;
    bar_blade->setTextureRect(Rect(0, 0, GAUGE_WIDTH * currentblade / MAX_BLADE, bar_gauge->getContentSize().height));
}

void Status::gauge_scheduler(float time) {
    if(currentGauge>targetGauge) currentGauge-=BLOCKING_GAUGE_VELOCITY;
    else if(currentGauge<targetGauge) currentGauge+=BLOCKING_GAUGE_VELOCITY;

    bar_gauge->setTextureRect(Rect(0, 0, GAUGE_WIDTH * currentGauge /MAX_GAUGE, bar_gauge->getContentSize().height));
}

bool Status::blockingIsPossible() {
    if(currentGauge>=MIN_COST_BLOCKING) return true;
    return false;
}
void Status::decreaseGauge(bool onGround) {
    if(onGround || currentGauge-COST_BLOCKING<0) currentGauge=0;
    else currentGauge-=COST_BLOCKING;
    bar_gauge->setTextureRect(Rect(0, 0, GAUGE_WIDTH * currentGauge /MAX_GAUGE, bar_gauge->getContentSize().height));
}
void Status::setBlockingGaugeMode(bool decrease) {
    if(decrease) targetGauge=0;
    else targetGauge=MAX_GAUGE;
}

void Status::increaseScore(int i) {
    score += i;
    lbScore->setString(string("Score : ") + to_string(score));
}

int Status::getHP(){ return currentHP; }
int Status::getMAX_HP(){ return MAX_HP; }
int Status::getScore(){ return score; }
int Status::getCombo(){ return combo; }
bool Status::bladeIsPossible(){ return currentblade==MAX_BLADE; }
int Status::getMAX_COMBO(){ return MAX_COMBO; }
int Status::getMAX_BLADE(){ return MAX_BLADE; }
void Status::increaseBScore(int i) { B_Score = B_Score + i; }
int Status::getBScore() { return B_Score; }

