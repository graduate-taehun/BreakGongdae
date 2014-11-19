//
//  Stage.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//

#include "Stage.h"
#include "Menu&Score.h"
#include <cstdlib>
#include <SimpleAudioEngine.h>

Size Stage::visibleSize = Director::getInstance()->getVisibleSize();
Vec2 Stage::posStatus=Vec2(visibleSize.width / 8, visibleSize.height * 19 / 20);
Vec2 Stage::posScore=Vec2(visibleSize.width / 8, visibleSize.height * 18 / 20);
Vec2 Stage::posTitle=Vec2(visibleSize.width *3 / 4, visibleSize.height *19 / 20);
Vec2 Stage::posCombo = Vec2(visibleSize.width / 8, visibleSize.height * 17 / 20);
/*
	캐릭터 및 빌딩 비트마스크 처리 (순서는 category,contact,collision)
	1. 캐릭터가 땅에 있을 때
	0010
	0010
	0001

	2. 캐릭터가 점프했을 때
	0001
	0100
	0011

	3. 빌딩
	0010
	0010
	0001
*/
Scene* Stage::createScene()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    posStatus=Vec2(visibleSize.width / 8, visibleSize.height * 19 / 20);
    posScore=Vec2(visibleSize.width / 8, visibleSize.height * 18 / 20);
    posTitle=Vec2(visibleSize.width *3 / 4, visibleSize.height *19 / 20);
	posCombo = Vec2(visibleSize.width / 8, visibleSize.height * 17 / 20);
    //origin=Director::getInstance()->getVisibleOrigin();
    
    Vect gravity = Vect(0.0f, -400.0f);
    
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setSubsteps(3);
    
    auto body = PhysicsBody::createBox(Size(visibleSize.width*2,GROUND_HEIGHT),PhysicsMaterial(0.0f,0.0f,0.0f));
    body->setDynamic(false);
    body->setCategoryBitmask(0x09);
    body->setContactTestBitmask(0x03);
    body->setCollisionBitmask(0x03);
    
    auto groundNode = Node::create();
    groundNode->setPosition(Point(visibleSize.width / 2, GROUND_HEIGHT/2));
    groundNode->setTag(EDGE_TAG);
    groundNode->setPhysicsBody(body);
    scene->addChild(groundNode);
    
    auto layer = Stage::create();

    scene->addChild(layer);
    
    return scene;
}

bool Stage::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    levelBuilding=0;
    setContentSize(Size(visibleSize.width,visibleSize.height*10));
    
    posCharacter[0]=Stage::visibleSize.width / 2 - Stage::visibleSize.width / 3;
    posCharacter[1]=Stage::visibleSize.width / 2;
    posCharacter[2]=Stage::visibleSize.width / 2 + Stage::visibleSize.width / 3;
    cntofPosCharacter = 1;
    
	Game_Pause = 0;
	closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Stage::menuCloseCallback, this));
	CCDirector::sharedDirector()->resume();
	closeItem->setPosition(Vec2(visibleSize.width - closeItem->getContentSize().width / 2, closeItem->getContentSize().height / 2));

	menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
   
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
    
    building = Building::createWithNumbsersAndImage(10, "block.png");
    building->setPosition(visibleSize.width / 2, GROUND_HEIGHT+building->getContentSize().height/2+2000);
    //building->getPhysicsBody()->setVelocity(Vec2(0,-300));
    addChild(building);

	status = Status::create();
	status->setPosition(posStatus);
	status->setCombo(0);
	addChild(status);

	Title = LabelBMFont::create("BreakGongDae", "futura-48.fnt");
	Title->setPosition(posTitle);
	addChild(Title);

	Score = CCLabelTTF::create("score : 0", "futura-48.fnt", 32);
	Score->setPosition(posScore);
	Score->setColor(ccc3(0, 0, 0));
	addChild(Score);

	Combo = CCLabelTTF::create("combo : 0", "futura-48.fnt", 28);
	Combo->setPosition(posCombo);
	Combo->setColor(ccc3(0, 0, 0));
	addChild(Combo);
   
    return true;
}

void Stage::setNextBuilding() {
    levelBuilding++;
    building = Building::create(10, "block.png",levelBuilding);
    building->setPosition(visibleSize.width / 2, GROUND_HEIGHT+building->getContentSize().height/2+2000);
    addChild(building);
}

void Stage::jump_scheduler(float time) {
    if(character->getPosition().y >=visibleSize.height/2) {
        //배경을 내림
		status->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 9 / 20);
		Title->setPosition(visibleSize.width * 3 / 4, character->getPosition().y+visibleSize.height * 9 / 20);
		Score->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 8 / 20);
		Combo->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 7 / 20);
		closeItem->setPosition(Vec2(visibleSize.width - closeItem->getContentSize().width / 2, character->getPosition().y - visibleSize.height/2 + closeItem->getContentSize().height / 2));

		this->setPosition(Vec2(this->getPosition().x,-character->getPosition().y+visibleSize.height/2));
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(Vec2(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,GROUND_HEIGHT/2+(visibleSize.height/2-character->getPosition().y)));
    }
    else if(character->getPosition().y<=GROUND_HEIGHT+character->getContentSize().height/2+1) {
        character->getPhysicsBody()->setVelocity(Vec2(0.,0.));
        character->setPosition(Vec2(character->getPosition().x,GROUND_HEIGHT+character->getContentSize().height/2));
        
        //점프 중지
		character->getPhysicsBody()->setCategoryBitmask(0x02);
		character->getPhysicsBody()->setContactTestBitmask(0x08);
		character->getPhysicsBody()->setCollisionBitmask(0x01);
		character->setState(sGround);
        unschedule(schedule_selector(Stage::jump_scheduler));
    }
    else {
        //배경 안움직임
		status->setPosition(posStatus);
		Title->setPosition(posTitle);
		Score->setPosition(posScore);
		Combo->setPosition(posCombo);
		closeItem->setPosition(Vec2(visibleSize.width - closeItem->getContentSize().width / 2, closeItem->getContentSize().height / 2));

        //building->getPhysicsBody()->setGravityEnable(false);
        //building->setPositionOfBottom(GROUND_HEIGHT+2000);
		this->setPosition(this->getPosition().x,0);
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,GROUND_HEIGHT/2);
    }
}

/*void Stage::attack_scheduler(float time) {
    if(character->getActionState()==None) {
        unschedule(schedule_selector(Stage::attack_scheduler));
        return;
    }
    
}*/

void Stage::block_scheduler(float time) {
    if(time>=3.0f) {
        unschedule(schedule_selector(Stage::block_scheduler));
    }
    if(abs(character->getPositionOfTop()-building->getPositionOfBottom())<10) {
        //float charactervel=character->getPhysicsBody()->getVelocity().y;
        character->stopActionByTag(Character::ATTACK_TAG);
        character->getPhysicsBody()->setVelocity(Vec2(0,-500+building->getPhysicsBody()->getVelocity().y));
		if (character->getState() == sGround)
		{
			status->setCombo(0);
			sprintf(status->getcoinCombo(), "combo : %d", status->getCombo());
			Combo->setString(status->getcoinCombo());
		}//땅에서 막기를 사용하면 콤보가 끊어진다. 나중에 죽었을때도 콤보가 끊어지도록 수정해야함

		//auto jump = JumpBy::create(1, Vec2(0,30), 30, 1);
        //building->runAction(jump);
        building->getPhysicsBody()->setVelocity(Vec2(0,10));
        if(character->getState()==sGround) unschedule(schedule_selector(Stage::block_scheduler));
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
                if (character->getState() == sGround) {
					character->getPhysicsBody()->setCategoryBitmask(0x01);
					character->getPhysicsBody()->setContactTestBitmask(0x04);
					character->getPhysicsBody()->setCollisionBitmask(0x03);
					character->setState(sAir);
                    /*auto jump = JumpTo::create(3, Vec2(character->getPosition().x,building->getPositionOfTop()/3), building->getPositionOfTop(), 1);
                    //auto jump = JumpTo::create(2, Vec2(character->getPosition().x,1000), 1000, 1);
                    jump->setTag(JUMP_TAG);
                    character->runAction(jump);*/
                    character->getPhysicsBody()->setVelocity(Vec2(0,2000));
                    
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
                if((0<=character->getPositionOfTop()-building->getPositionOfBottom()
                   && character->getPositionOfTop()-building->getPositionOfBottom()<100)
                   || character->getPositionOfTop()>building->getPositionOfBottom()) {
                    if(building->attack()) {
                        setNextBuilding();
                        break;
                    }
					status->increaseScore(1 + status->getCombo() * 10);//콤보당 10점씩 추가
					status->setCombo(status->getCombo() + 1);//하나 부실때마다 콤보 1씩 증가하게
					sprintf(status->getcoinScore(), "score : %d", status->getScore());
					Score->setString(status->getcoinScore());
					sprintf(status->getcoinCombo(), "combo : %d", status->getCombo());
					Combo->setString(status->getcoinCombo());
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
            case EventKeyboard::KeyCode::KEY_V:
            {
                status->decreaseHP(status->getMAX_HP()/10);
                status->setTextureRect(Rect(0, 0, status->getWidth() * status->getHP() / status->getMAX_HP(), status->getContentSize().height));
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
    status->decreaseHP(status->getMAX_HP() / 3);
    status->setTextureRect(Rect(0, 0, status->getWidth() * status->getHP() / status->getMAX_HP(), status->getContentSize().height));
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
/* 아랫부분은 팝업레이어구현해놓은 부분인데 아직 미완성이라 주석처리함 by 재엽*/

CCScene* PopLayer::scene()
{
	CCScene *scene = CCScene::create();
	PopLayer *layer = PopLayer::create();
	scene->addChild(layer);

	return scene;
}

bool PopLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
	{
		return false;
	}
	
	CCString* popParam = CCString::create("0");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기

	winSize = CCDirector::sharedDirector()->getWinSize();

	//메뉴추가
	CCMenuItemFont* pMenuItem = CCMenuItemFont::create("Resume", this, menu_selector(PopLayer::doClose));
	pMenuItem->setColor(ccc3(0, 0, 0));
	CCMenu* pMenu2 = CCMenu::create(pMenuItem, NULL);
	pMenu2->setPosition(ccp(450,300));
	this->addChild(pMenu2, 10);

	//backLayer추가
	backLayer = CCLayerColor::create(ccc4(0, 0, 0, 50), winSize.width, winSize.height);
	backLayer->setAnchorPoint(ccp(0, 0));
	backLayer->setPosition(ccp(0, 0));
	this->addChild(backLayer);

	//popUpLayer추가
	popUpLayer = CCLayerColor::create(ccc4(255, 0, 0, 255), 250, 150);
	popUpLayer->setAnchorPoint(ccp(0, 0));
	popUpLayer->setPosition(ccp((winSize.width - popUpLayer->getContentSize().width) / 2,
		(winSize.height - popUpLayer->getContentSize().height) / 2 ));
	this->addChild(popUpLayer);

	return true;
}

void PopLayer::doClose(CCObject* pSender)
{
	CCString* popParam = CCString::create("1");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기
	//팝업창 제거
	this->removeFromParentAndCleanup(true);
}
