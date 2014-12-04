//
//  Stage.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//

#include "Stage.h"

Scene* Stage::createScene()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    
    Vect gravity = Vect(0.0f, -GRAVITY);
    
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(DEBUG_MODE);
    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setSubsteps(3);
    
    auto body = PhysicsBody::createBox(Size(visibleSize.width,GROUND_HEIGHT),PhysicsMaterial(0.0f,0.0f,0.0f));
    body->setDynamic(false);
    body->setCategoryBitmask(0x09);
    body->setContactTestBitmask(0x03);
    body->setCollisionBitmask(0x05);
 
    body=PhysicsBody::createEdgeBox(Size(visibleSize.width,Stage::THIS_HEIGHT));
    auto edgeBox = Node::create();
    edgeBox->setPosition(Point(visibleSize.width/2, Stage::THIS_HEIGHT/2));
    edgeBox->setContentSize(Size(visibleSize.width,Stage::THIS_HEIGHT));
    edgeBox->setPhysicsBody(body);
    scene->addChild(edgeBox);
    
    auto layer = Stage::create();
    layer->setContentSize(Size(visibleSize.width,Stage::THIS_HEIGHT));
    layer->setTag(2);
    scene->addChild(layer);
    
    return scene;
}
Stage* Stage::create() {
    Stage *pRet = new Stage();
    if (pRet && pRet->init(nullptr)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool Stage::init(Status* _status=nullptr)
{
    if (!Layer::init())
        return false;
    
	Director::getInstance()->resume();
	
    setContentSize(Size(visibleSize.width,Stage::THIS_HEIGHT));
    
    
    posTitle=Vec2(visibleSize.width * 7 / 8, visibleSize.height * 19 / 20);
    posCharacter[0]=Stage::visibleSize.width / 2 - Stage::visibleSize.width / 3;
    posCharacter[1]=Stage::visibleSize.width / 2;
    posCharacter[2]=Stage::visibleSize.width / 2 + Stage::visibleSize.width / 3;
    cntofPosCharacter = 1;
    
	auto body = PhysicsBody::createBox(Size(visibleSize.width, GROUND_HEIGHT), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	body->setDynamic(false);
	body->setCategoryBitmask(0x09);
	body->setContactTestBitmask(0x03);
	body->setCollisionBitmask(0x05);

	groundNode = Sprite::create(FILE_BACKGROUND+"ground.png");
	groundNode->setContentSize(Size(visibleSize.width, GROUND_HEIGHT));
	groundNode->setPosition(visibleSize.width / 2, GROUND_HEIGHT / 2);
	groundNode->setTag(GROUND_TAG);
	groundNode->setPhysicsBody(body);
	addChild(groundNode, MENU_Z_ORDER-1);

	Game_Pause = false;
	btnClose = MenuItemImage::create(FILE_ETC+"CloseNormal.png", FILE_ETC+"CloseSelected.png", CC_CALLBACK_1(Stage::menuCloseCallback, this));
    posClose=Vec2(visibleSize.width - btnClose->getContentSize().width / 2, btnClose->getContentSize().height / 2);
	btnClose->setPosition(posClose);

	menuClose = Menu::create(btnClose, NULL);
	menuClose->setPosition(Vec2::ZERO);
	addChild(menuClose,MENU_Z_ORDER+2);

	auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Stage::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto background=Sprite::create(FILE_BACKGROUND+"background.png");
    background->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    background->setPosition(visibleSize.width/2,visibleSize.height*5);
    addChild(background);
    
    character = Character::create();
    character->setPosition(visibleSize.width / 2, GROUND_HEIGHT+character->getContentSize().height/2);
	addChild(character);
    
    if(_status==nullptr)
        status=Status::createWithHeight(visibleSize.height);
    else
        status=_status;
    posStatus=Vec2(status->getContentSize().width/2, visibleSize.height / 2);
    status->setPosition(posStatus);
    addChild(status, MENU_Z_ORDER);

    lbTitle = Label::createWithBMFont(FILE_FONT+"futura-48.fnt","Stage");
    lbTitle->setPosition(posTitle);
    addChild(lbTitle, MENU_Z_ORDER);
    
    lbPause = Label::createWithSystemFont("Pause", "Arial Rounded MT Bold", 45);
    lbPause->setColor(Color3B(0, 0, 0));
    lbPause->setVisible(false);
    addChild(lbPause, MENU_Z_ORDER);

    pauseCover = Sprite::create(FILE_BACKGROUND + "pause_cover.png");
    pauseCover->setOpacity(100);
    
    pauseCover->setVisible(false);
    addChild(pauseCover, MENU_Z_ORDER-1);
    return true;
}

void Stage::replaceNextScene() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Stage::setViewPoint(float threshold) {
    if(threshold>=visibleSize.height/2) {
        status->setPosition(posStatus.x, threshold + posStatus.y-visibleSize.height/2);
        lbTitle->setPosition(posTitle.x, threshold + posTitle.y-visibleSize.height/2);
        btnClose->setPosition(posClose.x, threshold + posClose.y-visibleSize.height/2);
        this->setPosition(Vec2(this->getPosition().x,-threshold+visibleSize.height/2));
        this->getChildByTag(GROUND_TAG)->setPosition(
                    Vec2(this->getChildByTag(GROUND_TAG)->getPosition().x, GROUND_HEIGHT/2+(visibleSize.height/2-threshold)));
    }
    else {
        status->setPosition(posStatus);
        lbTitle->setPosition(posTitle);
        btnClose->setPosition(posClose);
        
        this->setPosition(this->getPosition().x,0);
        this->getChildByTag(GROUND_TAG)->setPosition(Vec2(this->getChildByTag(GROUND_TAG)->getPosition().x, GROUND_HEIGHT/2));
    }
}
void Stage::scene_scheduler(float time) {
	removeChild(splashScreen);
    splashScreen=nullptr;
}

void Stage::jump_scheduler(float time) {
    setViewPoint(character->getPositionOfBottom()+character->getHeight()/2);
    if(character->getPositionOfBottom()<=GROUND_HEIGHT+10) {
        character->getPhysicsBody()->setVelocity(Vec2(0.,0.));
        character->setPosition(Vec2(character->getPosition().x,GROUND_HEIGHT+character->getContentSize().height/2));
		character->setState(sGround);
        unschedule(schedule_selector(Stage::jump_scheduler));
    }
}

void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && Game_Pause) {
		Director::getInstance()->resume();
        pauseCover->setVisible(false);
        lbPause->setVisible(false);
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Game_Pause = false;
        return;
	}
    if(Game_Pause) return;
    
    switch (keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
            if(cntofPosCharacter!=0)
                character->setPosition(posCharacter[--cntofPosCharacter],character->getPosition().y);
            break;	
        }
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
            if(cntofPosCharacter!=2)
                character->setPosition(posCharacter[++cntofPosCharacter],character->getPosition().y);
            break;
        }
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            if (!Game_Pause) {
				CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				Director::getInstance()->pause();
                lbPause->setPosition(Vec2(Status::LABEL_X, max(visibleSize.height / 2, character->getPosition().y) + 200));
                lbPause->setAnchorPoint(Vec2(0,0.5));
                pauseCover->setPosition(Vec2(visibleSize.width / 2, max(visibleSize.height / 2, character->getPosition().y)));
                pauseCover->setVisible(true);
                lbPause->setVisible(true);

				Game_Pause = true;
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

	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(MenuStage::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}