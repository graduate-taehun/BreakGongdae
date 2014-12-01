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
	int score;
	int combo;
	int MAX_COMBO;
    int currentHP;
    static const int MAX_HP = 30;
	
	int B_Score;
    
	int currentblade;
	static const int MAX_BLADE = 30;
    
    float currentGauge;
    float targetGauge;
    static const int MAX_GAUGE = 100;
    
    void gauge_scheduler(float time);
    
    Sprite* bar_gauge;
    Sprite* bar_HP;
	Sprite* bar_blade;
    CCLabelTTF* lbScore;
    CCLabelTTF* lbCombo;
    
    virtual bool init();

public:
    Status() {}
    Status(const Status & st);
    CREATE_FUNC(Status);

	int getWidth();

	int getBScore();
    void increaseBScore(int i);
    
    int getCombo();
	void resetCombo();
    void increaseCombo(int i, const Vec2& posCharacter);
    
	int getBlade();
	void setBlade(int);
	
    int getMAX_BLADE();
	int getMAX_COMBO();

	int getHP();
	int getMAX_HP();
	void decreaseHP();

	int getScore();
	void increaseScore(int i);
	
    bool blockingIsPossible();
    void decreaseGauge(bool onGround);
    void setBlockingGaugeMode(bool decrease);
};
#endif /* defined(__BreakGongDae__Status__) */
