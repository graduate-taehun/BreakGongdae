//
//  Status.cpp
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 15.
//
//

#include "Status.h"
#include <cstdlib>

bool Status::init() {
    if(!Layer::init())
        return false;

	combo = 0;
    score = 0;
	MAX_COMBO = 0;
	currentHP = MAX_HP;
    currentGauge = 100;
    targetGauge = 100;
    
    bar_HP = Sprite::create("status_hp.png");
    float x = -bar_HP->getContentSize().width/2;
    bar_HP->setPosition(Vec2(x,bar_HP->getContentSize().height*1.5));
    bar_HP->setAnchorPoint(Vec2(0,0.5));
    addChild(bar_HP);
    
    bar_gauge = Sprite::create("status_hp.png");
    bar_gauge->setPosition(Vec2(x,bar_gauge->getContentSize().height/2));
    bar_gauge->setAnchorPoint(Vec2(0,0.5));
    addChild(bar_gauge);
    
    lbScore = CCLabelTTF::create("score : 0", "futura-48.fnt", 32);
    lbScore->setPosition(Vec2(x,-lbScore->getContentSize().height/2));
    lbScore->setAnchorPoint(Vec2(0,0.5));
    lbScore->setColor(ccc3(0, 0, 0));
    addChild(lbScore);
    
    lbCombo = CCLabelTTF::create("combo : 0", "futura-48.fnt", 28);
    lbCombo->setPosition(Vec2(x,-lbCombo->getContentSize().height*1.5));
    lbCombo->setAnchorPoint(Vec2(0,0.5));
    lbCombo->setColor(ccc3(0, 0, 0));
    addChild(lbCombo);
    
    bar_HP->setContentSize(Size(lbCombo->getContentSize().width,bar_HP->getContentSize().height));
    bar_HP->setTextureRect(Rect(0, 0, lbCombo->getContentSize().width, bar_HP->getContentSize().height));
    
    bar_gauge->setContentSize(bar_HP->getContentSize());
    bar_gauge->setTextureRect(Rect(0, 0, lbCombo->getContentSize().width, bar_gauge->getContentSize().height));
    
    setContentSize(Size(bar_HP->getContentSize().width,bar_HP->getContentSize().height*3));
        
    schedule(schedule_selector(Status::gauge_scheduler));

    return true;
}

Status::Status(const Status & st) {
    Layer::init();
    
    score = st.score;
    currentHP = st.currentHP;
    combo=st.combo;
	MAX_COMBO = st.MAX_COMBO;
	currentGauge=st.currentGauge;
    targetGauge=st.targetGauge;
    bar_HP=nullptr;
    bar_gauge=nullptr;
    lbScore=nullptr;
    lbCombo=nullptr;
}

using namespace std;

void Status::decreaseHP() {
    currentHP -= MAX_HP/3;
    bar_HP->setTextureRect(Rect(0, 0, getContentSize().width * currentHP /MAX_HP, bar_HP->getContentSize().height));
}

void Status::resetCombo() {
    combo = 0;
    lbCombo->setString(string("combo : ") + to_string(combo));
}

void Status::increaseCombo(int i, const Vec2& posCharacter) {
<<<<<<< HEAD

	combo += i;
	if (combo > MAX_COMBO)
		MAX_COMBO = combo;

    lbCombo->setString(string("combo : ") + to_string(combo));
    auto *Label_Combo = CCLabelTTF::create(to_string(combo)+" Combo!", "futura-48.fnt", 25);
    Label_Combo->setColor(ccc3(0, 0, 0));

	bool leftorright2 = rand() % 2;
    bool leftorright = rand() % 2;
    Label_Combo->setPosition(posCharacter.x + (leftorright?80:-80), posCharacter.y + 80);
    Label_Combo->setPhysicsBody(PhysicsBody::createBox(Label_Combo->getContentSize()));
    Label_Combo->getPhysicsBody()->setVelocity(Vec2((leftorright?100:-100),30));
    Label_Combo->getPhysicsBody()->setCollisionBitmask(0x00);
    getParent()->addChild(Label_Combo);

	int check = rand() % 100;
	int rand_block = rand() % 2;
	
	auto frag1 = Sprite::create("fragment_1.png");
	auto frag2 = Sprite::create("fragment_2.png");

	if (rand_block == 0){
		if (check % 2 == 1)
			frag1->setPosition(posCharacter.x + check * 2, posCharacter.y + 80);
		else
			frag1->setPosition(posCharacter.x - check * 2, posCharacter.y + 80);
		
		frag1->setPhysicsBody(PhysicsBody::createBox(frag1->getContentSize()));
		frag1->getPhysicsBody()->setVelocity(Vec2((leftorright2 ? 150 : -150), 40));
		frag1->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(frag1, 3);
	}
	else if (rand_block == 1){
		if (check % 2 == 1)
			frag2->setPosition(posCharacter.x + check * 2, posCharacter.y + 80);
		else
			frag2->setPosition(posCharacter.x - check * 2, posCharacter.y + 80);
		
		frag2->setPhysicsBody(PhysicsBody::createBox(frag2->getContentSize()));
		frag2->getPhysicsBody()->setVelocity(Vec2((leftorright2 ? 150 : -150), 40));
		frag2->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(frag2, 3);
=======
	Combo += i;
	lbCombo->setString(string("combo : ") + to_string(Combo));
	auto *Label_Combo = CCLabelTTF::create(to_string(Combo) + " Combo!", "futura-48.fnt", 35);
	Label_Combo->setColor(ccc3(0, 0, 0));

	bool leftorright2;
	bool leftorright = rand() % 2;
	Label_Combo->setPosition(posCharacter.x + (leftorright ? 80 : -80), posCharacter.y + 80);
	Label_Combo->setPhysicsBody(PhysicsBody::createBox(Label_Combo->getContentSize()));
	Label_Combo->getPhysicsBody()->setVelocity(Vec2((leftorright ? 100 : -100), 30));
	Label_Combo->getPhysicsBody()->setCollisionBitmask(0x00);
	getParent()->addChild(Label_Combo,4);
	int block_n = rand() % 3;
	int num = 0;
	int check[3];
	int block_select = rand() % 2;

	Sprite* frag;
	//반복문 {
	//    frag=Sprite::create
	//	asdsad
	//	addchild(frag);
	//}
	/*
	auto frag3 = Sprite::create("fragment_3.png");

	auto frag4 = Sprite::create("fragment_4.png");
	*/
	while (num <= block_n)
	{
		leftorright2 = rand() % 2;
		check[num] = rand() % 100;
		if (block_select == 0)
		{
			frag = Sprite::create("fragment_1.png");
			if (check[num]%2== 1)
			{
				frag->setPosition(posCharacter.x + check[num] * 2, posCharacter.y + 80);
			}
			else
			{
				frag->setPosition(posCharacter.x - check[num] * 2, posCharacter.y + 80);
			}
			frag->setPhysicsBody(PhysicsBody::createBox(frag->getContentSize()));
			frag->getPhysicsBody()->setVelocity(Vec2((leftorright2 ? 150 : -150), 40));
			frag->getPhysicsBody()->setCollisionBitmask(0x00);
			getParent()->addChild(frag, 3);
		}
		else if (block_select == 1)
		{
			frag = Sprite::create("fragment_2.png");
			if (check[num] % 2 == 1)
			{
				frag->setPosition(posCharacter.x + check[num] * 2, posCharacter.y + 80);
			}
			else
			{
				frag->setPosition(posCharacter.x - check[num] * 2, posCharacter.y + 80);
			}
			frag->setPhysicsBody(PhysicsBody::createBox(frag->getContentSize()));
			frag->getPhysicsBody()->setVelocity(Vec2((leftorright2 ? 150 : -150), 40));
			frag->getPhysicsBody()->setCollisionBitmask(0x00);
			getParent()->addChild(frag, 3);
		}
		num++;
	}/*
	 
	else if (rand_block == 2)
	{
		if (check % 2 == 1)
		{
			frag3->setPosition(posCharacter.x + check * 2, posCharacter.y + 80);
		}
		else
		{
			frag3->setPosition(posCharacter.x - check * 2, posCharacter.y + 80);
		}
		frag3->setPhysicsBody(PhysicsBody::createBox(frag3->getContentSize()));
		frag3->getPhysicsBody()->setVelocity(Vec2((leftorright2 ? 150 : -150), 40));
		frag3->getPhysicsBody()->setCollisionBitmask(0x00);
		getParent()->addChild(frag3, 3);
>>>>>>> origin/master
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
int Status::getMAX_COMBO(){ return MAX_COMBO; }
//char* Status::getcoinCombo(){ return coinCombo; }

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