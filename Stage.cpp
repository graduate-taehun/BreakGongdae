//
//  Stage.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//ㅁㄴㅇㄹ

#include "Stage.h"
#include "Menu&Score.h"
#include <cstdlib>
#include <SimpleAudioEngine.h>

Size Stage::visibleSize = Director::getInstance()->getVisibleSize();
Vec2 Stage::posStatus=Vec2(visibleSize.width / 8, visibleSize.height * 18 / 20);
Vec2 Stage::posTitle=Vec2(visibleSize.width *3 / 4, visibleSize.height *19 / 20);

string Stage::fileBuilding[10]={"Mueunjae.png", "RC.png", "78.png", "Old_dormitory.png", "Jigok.png"};

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

	srand(time(NULL));
    visibleSize=Director::getInstance()->getVisibleSize();
    posStatus=Vec2(visibleSize.width / 8, visibleSize.height * 18 / 20);
    posTitle=Vec2(visibleSize.width *3 / 4, visibleSize.height *19 / 20);
    
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
    edgeBox->setTag(EDGE_TAG);
    edgeBox->setPhysicsBody(body);
    scene->addChild(edgeBox);
    
    auto layer = Stage::create();
    layer->setContentSize(Size(visibleSize.width,visibleSize.height*10));
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
    
    levelBuilding=-1;
    setContentSize(Size(visibleSize.width,visibleSize.height*10));
    
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

    lbTitle = LabelBMFont::create("BreakGongDae", "futura-48.fnt");
    //Title->setPosition(posTitle);
    addChild(lbTitle);
   
    return true;
}

void Stage::setNextBuilding() {
    levelBuilding++;
    building = Building::create(10, "block.png",levelBuilding);
    building->setPosition(visibleSize.width / 2, GROUND_HEIGHT+building->getContentSize().height/2+BUILDING_START_HEIGHT);
    addChild(building);
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

void Stage::block_scheduler(float time) {
    if(time>=BLOCKING_TIME_LIMIT) {
        unschedule(schedule_selector(Stage::block_scheduler));
    }
    if(abs(character->getPositionOfTop()-building->getPositionOfBottom())<10) {
        //float charactervel=character->getPhysicsBody()->getVelocity().y;
        character->stopActionByTag(Character::ATTACK_TAG);
        if(character->getState()==sAir)
            character->getPhysicsBody()->setVelocity(Vec2(0,-CHARACTER_VEL_AFTER_BLOCKING+building->getPhysicsBody()->getVelocity().y));
		if (character->getState() == sGround)
			status->resetCombo();
		//땅에서 막기를 사용하면 콤보가 끊어진다. 나중에 죽었을때도 콤보가 끊어지도록 수정해야함

        building->getPhysicsBody()->setVelocity(Vec2(0,BUILDING_VEL_AFTER_BLOCKING));
        //if(character->getState()==sGround) unschedule(schedule_selector(Stage::block_scheduler));
    }
}

void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	
	if(Game_Pause==0) {
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
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            {
				if (character->getState() == sGround){
					character->setState(sAir);
					character->getPhysicsBody()->setVelocity(Vec2(0,CHARACTER_JUMP_VEL));
                    
                    //점프동작
                    if (!isScheduled(schedule_selector(Stage::jump_scheduler)))
                        schedule(schedule_selector(Stage::jump_scheduler));
                    break;
                }
                break;
            }
            // 부수기
            case EventKeyboard::KeyCode::KEY_Z:
            {
                
                
				character->doAttackAction();
            
				if(   (0<=building->getPositionOfBottom()-character->getPositionOfTop()
                       && building->getPositionOfBottom()-character->getPositionOfTop()<ATTACK_RANGE)
                   || (0<=character->getPositionOfTop()-building->getPositionOfBottom()
                       && character->getPositionOfTop()-building->getPositionOfBottom()<character->getContentSize().height/3)
                   || abs(building->getPositionOfBottom()-GROUND_HEIGHT)<=5) {
                    if(building->attack()) {
                        setNextBuilding();
                        break;
                    }
					status->increaseScore(1 + status->getCombo() * 10);//콤보당 10점씩 추가
					status->increaseCombo(1, character->getPosition());//하나 부실때마다 콤보 1씩 증가하게
                }
                break;
            }
            // 막기
            case EventKeyboard::KeyCode::KEY_X:
            {
                character->setActionState(Blocking);
                schedule(schedule_selector(Stage::block_scheduler));
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
}

void Stage::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode){
        case EventKeyboard::KeyCode::KEY_X: {
            character->setActionState(None);
            unschedule(schedule_selector(Stage::block_scheduler));
        }
	}
}

bool Stage::onContactBegin(PhysicsContact& contact)
{
	building->getPhysicsBody()->setCategoryBitmask(0x03);
	building->getPhysicsBody()->setContactTestBitmask(0x08);
	building->getPhysicsBody()->setCollisionBitmask(0x03);

    status->decreaseHP();
    status->resetCombo();
	return true;
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