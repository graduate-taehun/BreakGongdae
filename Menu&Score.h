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
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ScoreBoard);
};

class MenuStage : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    
    void menuCallback1(Ref* pSender);
    void menuCallback2(Ref* pSender);
    void menuCallback3(Ref* pSender);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuStage);
};

#endif /* defined(__BreakGongDae__Menu_Score__) */
