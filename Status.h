//
//  Status.h
//  BreakGongDae
//
//  Created by 이상민 on 2014. 11. 15.
//
//

#ifndef __BreakGongDae__Status__
#define __BreakGongDae__Status__

#include "BalanceSetting.h"

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
    void increaseBlade(int _blade);
    
	Sprite* state;
    Sprite* bar_gauge;
    Sprite* bar_HP;
	Sprite* bar_blade;
    Label* lbScore;
    Label* lbCombo;
    
    const static int BAR_BLADE_Y=65;
    const static int BAR_GAUGE_Y=28;
    const static int BAR_X=78;
    const static int LABEL_X=20;
    const static int LABEL_INTERVAL_Y=5;
    
    virtual bool initWithHeight(float height);

public:
    Status() {}
    Status(const Status & st);
    static Status* createWithHeight(float height);

    float STATUS_WIDTH;
    float GAUGE_WIDTH;
    
	int getWidth();

	int getBScore();
    void increaseBScore(int i);
    
    int getCombo();
	void resetCombo();
    void increaseCombo(int i, const Vec2& posCharacter, bool isBlade);
    
	bool bladeIsPossible();
    void resetBlade();
	
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
