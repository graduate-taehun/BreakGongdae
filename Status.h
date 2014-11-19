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
USING_NS_CC;

class Status : public Sprite
{
private:
	float width;
	int currentHP;
	int MAX_HP;
	int score;
	int Combo;
	char coinScore[100];
	char coinCombo[100];

public:
    virtual bool init();
    CREATE_FUNC(Status);

	int getCombo();
	int getWidth();
	int getHP();
	int getMAX_HP();
	void setCombo(int C);
	void decreaseHP(int _HP);
	int getScore();
	char* getcoinScore();
	char* getcoinCombo();
	void increaseScore(int i);
};

#endif /* defined(__BreakGongDae__Status__) */
