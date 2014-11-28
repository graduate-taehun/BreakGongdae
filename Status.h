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
	//int bonus_score[4];
	int B_Score;
	static const int MAX_HP = 30;
    
    float currentGauge;
    float targetGauge;
    static const int MAX_GAUGE=100;
    
    void gauge_scheduler(float time);
    
    Sprite* bar_gauge;
    Sprite *bar_HP;
    CCLabelTTF *lbScore;
    CCLabelTTF *lbCombo;
    
    virtual bool init();
public:
	Status() { B_Score = 0; }
    Status(const Status & st);
    CREATE_FUNC(Status);

	int getWidth();

	void increaseBScore(int i);
	int getBScore();
	void resetCombo();
	int getCombo();
	int getMAX_COMBO();
	char* getcoinCombo();
	void increaseCombo(int i, const Vec2& posCharacter);
	//void setBonusScore(int s, int i);
	//int getBonusScore(int i);
	int getHP();
	int getMAX_HP();
	void decreaseHP();

	int getScore();
	char* getcoinScore();
	void increaseScore(int i);

	bool blockingIsPossible();
    void decreaseGauge(bool onGround);
    void setBlockingGaugeMode(bool decrease);
};
#endif /* defined(__BreakGongDae__Status__) */
