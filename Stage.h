//
//  Stage.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//

#ifndef __BreakGongDae__Stage__
#define __BreakGongDae__Stage__

#include "cocos2d.h"
USING_NS_CC;

enum state{ G, AIR };
enum attack{ Y, N, B };

class Grosss :	public Sprite
{
	Sprite *gros;
	state s;
	attack a;
public:
	Sprite* getgros();
	Grosss();
	void grosinit();
	state getstate();
	void setstate(state);
	attack getattack();
	void setattack(attack);
};

class Stage : public LayerColor
{
public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    CREATE_FUNC(Stage);
    
    //void setPhyWorld(PhysicsWorld* world){ m_world = world; }
    //~Stage();
    //virtual bool onTouchBegan(Touch *touch, Event * event);
    //virtual void onTouchEnded(Touch *touch, Event * event);
    

protected:
    static const int GROUND = 50;
    static const int CHARACTER_TAG = 11;
    static const int EDGE_TAG = 0;
    
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
	friend class Grosss;
	Grosss g;
};

#endif /* defined(__BreakGongDae__Stage__) */