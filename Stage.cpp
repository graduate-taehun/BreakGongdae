//
//  Stage.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//ㅁㄴㅇㄹ

#include "Stage.h"
#include <SimpleAudioEngine.h>

Size Stage::visibleSize = Director::getInstance()->getVisibleSize();
/*
	캐릭터 및 빌딩 비트마스크 처리 (순서는 category,contact,collision)
	1. 캐릭터가 땅에 있을 때	
	0100
	0010
	0001

	2. 캐릭터가 점프했을 때
	0001
	0100
	0011

	3. 빌딩
	0011
	1000
	0011

	4. 바닥
	1001
	0011
	0101
*/
Scene* Stage::createScene()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    
    //origin=Director::getInstance()->getVisibleOrigin();
    
    Vect gravity = Vect(0.0f, -GRAVITY);
    
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setSubsteps(3);
    
    auto body = PhysicsBody::createBox(Size(visibleSize.width,GROUND_HEIGHT),PhysicsMaterial(0.0f,0.0f,0.0f));
    body->setDynamic(false);
    body->setCategoryBitmask(0x09);
    body->setContactTestBitmask(0x03);
    body->setCollisionBitmask(0x05);
    
    auto groundNode = Node::create();
    groundNode->setPosition(Point(visibleSize.width / 2, GROUND_HEIGHT/2));
    groundNode->setTag(GROUND_TAG);
    groundNode->setPhysicsBody(body);
    scene->addChild(groundNode);
    
    body=PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height*10));
    auto edgeBox = Node::create();
    edgeBox->setPosition(Point(visibleSize.width/2, visibleSize.height*5));
    edgeBox->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    //edgeBox->setTag(EDGE_TAG);
    edgeBox->setPhysicsBody(body);
    scene->addChild(edgeBox);
    
    auto layer = Stage::create();
    layer->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    layer->setTag(2);
    scene->addChild(layer);
    
    return scene;
}

bool Stage::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    CCDirector::sharedDirector()->resume();
    
    setContentSize(Size(visibleSize.width,visibleSize.height*10));
    
    posStatus=Vec2(visibleSize.width / 8, visibleSize.height * 18 / 20);
    posTitle=Vec2(visibleSize.width *3 / 4, visibleSize.height *19 / 20);
    posCharacter[0]=Stage::visibleSize.width / 2 - Stage::visibleSize.width / 3;
    posCharacter[1]=Stage::visibleSize.width / 2;
    posCharacter[2]=Stage::visibleSize.width / 2 + Stage::visibleSize.width / 3;
    cntofPosCharacter = 1;
    
	Game_Pause = 0;
	btnClose = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Stage::menuCloseCallback, this));
    posClose=Vec2(visibleSize.width - btnClose->getContentSize().width / 2, btnClose->getContentSize().height / 2);
	btnClose->setPosition(posClose);

	menuClose = Menu::create(btnClose, NULL);
	menuClose->setPosition(Vec2::ZERO);
	addChild(menuClose,1);
   
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Track 01.mp3", false);
	
	auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Stage::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto background=Sprite::create("stage_background.png");
    background->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    background->setPosition(visibleSize.width/2,visibleSize.height*5);
    addChild(background);
    
    character = Character::create();
    character->setPosition(visibleSize.width / 2, GROUND_HEIGHT + character->getContentSize().height / 2);
	addChild(character);
    
    setNextBuilding();
    
    status=Status::create();
    status->setPosition(posStatus);
    addChild(status);
    
    /*gaugeBlocking=BlockingGauge::create();
    posGauge=Vec2(visibleSize.width*19/20-gaugeBlocking->getContentSize().width,visibleSize.height *1 / 20);
    gaugeBlocking->setPosition(posGauge);
    addChild(gaugeBlocking);*/

    lbTitle = LabelBMFont::create("BreakGongDae", "futura-48.fnt");
    //Title->setPosition(posTitle);
    addChild(lbTitle);
   
    return true;
}

void Stage::jump_scheduler(float time) {
    if(character->getPosition().y >=visibleSize.height/2) {
        //배경을 내림
		status->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 8 / 20);
		lbTitle->setPosition(visibleSize.width * 3 / 4, character->getPosition().y+visibleSize.height * 9 / 20);
		btnClose->setPosition(Vec2(visibleSize.width - btnClose->getContentSize().width / 2, character->getPosition().y - visibleSize.height/2 + btnClose->getContentSize().height / 2));

		this->setPosition(Vec2(this->getPosition().x,-character->getPosition().y+visibleSize.height/2));
        this->getScene()->getChildByTag(GROUND_TAG)->setPosition(Vec2(this->getScene()->getChildByTag(GROUND_TAG)->getPosition().x,GROUND_HEIGHT/2+(visibleSize.height/2-character->getPosition().y)));
    }
    else if(character->getPositionOfTop()-character->getContentSize().height<=GROUND_HEIGHT+10) {
        character->getPhysicsBody()->setVelocity(Vec2(0.,0.));
        character->setPosition(Vec2(character->getPosition().x,GROUND_HEIGHT+character->getContentSize().height/2));
        
        //점프 중지
		character->setState(sGround);
        unschedule(schedule_selector(Stage::jump_scheduler));
    }
    else {
        //배경 안움직임
		status->setPosition(posStatus);
		lbTitle->setPosition(posTitle);
		btnClose->setPosition(posClose);

		this->setPosition(this->getPosition().x,0);
        this->getScene()->getChildByTag(GROUND_TAG)->setPosition(this->getScene()->getChildByTag(GROUND_TAG)->getPosition().x,GROUND_HEIGHT/2);
    }
}



void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	
    if(Game_Pause==1) return;
    
    switch (keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
            if(cntofPosCharacter!=0)
                character->setPosition(posCharacter[--cntofPosCharacter],character->getPosition().y);
            break;
        }
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
            if(cntofPosCharacter!=2)
                character->setPosition(posCharacter[++cntofPosCharacter],character->getPosition().y);
            break;
        }
        case EventKeyboard::KeyCode::KEY_ESCAPE:
        {
            if (Game_Pause == 0)
            {
                CCDirector::sharedDirector()->pause();
                Game_Pause = 1;
                //CCScene* pScene = PopLayer::scene(); //팝업레이어는 일단 미완성이라 주석처리함
                //this->addChild(pScene, 2000, 2000);
            }
            else if (Game_Pause == 1 )
            {
               CCDirector::sharedDirector()->resume();
               Game_Pause = 0;
               //CCString* popParam = CCString::create("1");
               //CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기

               //팝업창 제거
            }
        }
        default:
            break;
    }
}

void Stage::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->replaceScene(MenuStage::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
/*void Stage::setGamePause(bool p)
{
	Game_Pause = p;
}*/