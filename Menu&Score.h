//
//  Menu&Score.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 11..
//
//

#ifndef __BreakGongDae__Menu_Score__
#define __BreakGongDae__Menu_Score__

#include "cocos2d.h"
USING_NS_CC;

class ScoreBoard : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
	virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(ScoreBoard);
};

class MenuStage : public Layer
{
public:
    static Scene* createScene(); 
    
	void menuCallbackforStage(Ref* pSender);
    void menuCallbackforScoreBoard(Ref* pSender);
    void menuCallbackforExit(Ref* pSender);

    virtual bool init();
    CREATE_FUNC(MenuStage);
};

class EndScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(EndScene);
};

#endif /* defined(__BreakGongDae__Menu_Score__) */
