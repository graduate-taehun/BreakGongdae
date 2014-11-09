//
//  Stage.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//

#ifndef __BreakGongDae__Stage__
#define __BreakGongDae__Stage__

#include "Character.h"
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
class Stage : public LayerColor
{
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	void menuCloseCallback(Ref* pSender);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    CREATE_FUNC(Stage);

	void stopAttack();
    
    //void setPhyWorld(PhysicsWorld* world){ m_world = world; }
    //~Stage();
    //virtual bool onTouchBegan(Touch *touch, Event * event);
    //virtual void onTouchEnded(Touch *touch, Event * event);
    

protected:
    static const int GROUND_HEIGHT = 50;
    static const int CHARACTER_TAG = 11;
    static const int EDGE_TAG = 0;
    static const int Building_TAG = 1;
	static const int TITLE_TAG = 2;
	static const int HP_BAR_TAG = 3;
	static const int STATUS_TAG = 4;

    static Size visibleSize;
    

	//PhysicsWorld* m_world;
    //Sprite *character;
    
    //onContact Listener
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void jump_scheduler(float time); //점프하면 반복적으로 호출되는 함수
	//void skill_blocking();
	bool onContactBegin(PhysicsContact& contact);

private:
    static float posCharacter[3]; //캐릭터의 x좌표로 가능한 것들
    static int cntofPosCharacter; //캐릭터가 현재 어디 있는지 posCharacter의 index로 나타냄. 처음은 중앙이므로 1
	
};

#endif /* defined(__BreakGongDae__Stage__) */