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
#include "Status.h"
USING_NS_CC;

class ScoreBoard : public cocos2d::Layer{
private:
    virtual bool init();

public:
    static cocos2d::Scene* createScene();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(ScoreBoard)
};

class MenuStage : public Layer{
private:
    virtual bool init();

public:
    static Scene* createScene();
    
    void menuCallbackforStage(Ref* pSender);
    void menuCallbackforScoreBoard(Ref* pSender);
    void menuCallbackforExit(Ref* pSender);
    
    CREATE_FUNC(MenuStage)
};

class EndScene : public cocos2d::Layer{
private:
    virtual bool initWithScore(Status& status);
    static EndScene* createWithScore(Status& status);
    
public:
    static cocos2d::Scene* createSceneWithScore(Status status);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif /* defined(__BreakGongDae__Menu_Score__) */
