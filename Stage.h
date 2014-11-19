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
#include "Status.h"
#include "Building.h"

class Stage : public LayerColor
{
private:
    float posCharacter[3]; //캐릭터의 x좌표로 가능한 것들
    int cntofPosCharacter; //캐릭터가 현재 어디 있는지 posCharacter의 index로 나타냄. 처음은 중앙이므로 1
    void stopAttack();
    void menuCloseCallback(Ref* pSender);
    
    static Vec2 posScore;
    static Vec2 posTitle;
    static Vec2 posStatus;
	static Vec2 posCombo;
    
    int levelBuilding;
    //string fileBuilding[10]={"Mueunjae.png", "RC.png", "78.png", "Old_dormitory.png", "Jigok.png"};
	
protected:
    static const int GROUND_HEIGHT = 50;
    static const int EDGE_TAG = 0;
    static const int JUMP_TAG=22;
    
    Menu* menu;
	MenuItemImage* closeItem;
    
	LabelBMFont *Title;
	CCLabelTTF *Score;
	CCLabelTTF *Combo;
	CCLabelTTF *Label_Combo;
 
    Status* status;
    Character* character;
    Building* building;
   
    static Size visibleSize;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    void jump_scheduler(float time); //점프하면 반복적으로 호출되는 함수
    //void attack_scheduler(float time);
    void block_scheduler(float time);
    
	//void skill_blocking();
	bool onContactBegin(PhysicsContact& contact);
	bool Game_Pause;
    virtual bool init();
    virtual void setNextBuilding();
public:
	static cocos2d::Scene* createScene();
    
	//void setGamePause(bool p);
    CREATE_FUNC(Stage);
};

class PopLayer : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(PopLayer);

	cocos2d::CCSize winSize;

	CCLayerColor* backLayer;
	CCLayerColor* popUpLayer;

	void doClose(CCObject* pSender);
};

#endif /* defined(__BreakGongDae__Stage__) */