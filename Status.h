//
//  Status.h
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 15.
//
//

#ifndef __BreakGongDae__Status__
#define __BreakGongDae__Status__

#include "cocos2d.h"
#include "BalanceSetting.h"
#include <string>
USING_NS_CC;

class Status : public Layer {
private:
	int currentHP;
	static const int MAX_HP=30;
	int Combo;
	int score;
	//char coinScore[100];
	//char coinCombo[100];
    
    Sprite *bar_HP;
    CCLabelTTF *lbScore;
    CCLabelTTF *lbCombo;
    
    virtual bool init();
public:
    CREATE_FUNC(Status);

	int getCombo();
	int getWidth();
	int getHP();
	int getMAX_HP();
	void resetCombo();
    void increaseCombo(int i, const Vec2& posCharacter);
	void decreaseHP();
	int getScore();
	char* getcoinScore();
	char* getcoinCombo();
	void increaseScore(int i);
};

class BlockingGauge : public Sprite {
private:
    int gauge;
    static const int MAX_GAUGE=100;
    virtual bool init();
    
public:
    CREATE_FUNC(BlockingGauge)
    bool blockingIsPossible();
    void decreaseGauge(bool onGround);
};

#endif /* defined(__BreakGongDae__Status__) */
