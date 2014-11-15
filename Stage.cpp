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
float Stage::posCharacter[3] = { Stage::visibleSize.width / 2 - Stage::visibleSize.width / 3, Stage::visibleSize.width / 2, Stage::visibleSize.width / 2 + Stage::visibleSize.width / 3 };
int Stage::cntofPosCharacter = 1;

Scene* Stage::createScene()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    //origin=Director::getInstance()->getVisibleOrigin();
    posCharacter[0]=Stage::visibleSize.width/2-Stage::visibleSize.width/3;
    posCharacter[1]=Stage::visibleSize.width/2;
    posCharacter[2]=Stage::visibleSize.width/2+Stage::visibleSize.width/3;
    
    Vect gravity = Vect(0.0f, -400.0f);
    
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(gravity);
    
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height*10-GROUND_HEIGHT), PhysicsMaterial(0.,0.,0.),1);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height*5+GROUND_HEIGHT/2));
    edgeNode->setTag(EDGE_TAG);
    edgeNode->setPhysicsBody(body);
    scene->addChild(edgeNode);
    
    auto layer = Stage::create();
    //layer->setPhyWorld(scene->getPhysicsWorld());
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
	// create menu, it's an autorelease object
	closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(Stage::menuCloseCallback, this));
	Game_Pause = 0;
	CCDirector::sharedDirector()->resume();
	closeItem->setPosition(Vec2(visibleSize.width - closeItem->getContentSize().width / 2, closeItem->getContentSize().height / 2));

	menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
    
    //visibleSize=Director::getInstance()->getVisibleSize();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Track 01.mp3", false);
	
	auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

    auto background=Sprite::create("stage_background.png");
    background->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    background->setPosition(visibleSize.width/2,visibleSize.height*5);
    addChild(background);
    
    character=Character::create();
    character->setPosition(visibleSize.width / 2, GROUND_HEIGHT + character->getContentSize().height / 2);
	addChild(character);

	status = Status::create();
	status->setPosition(visibleSize.width / 8, visibleSize.height * 19 / 20);
	addChild(status);

	Title = LabelBMFont::create("BreakGongDae", "futura-48.fnt");
	Title->setPosition(visibleSize.width *3 / 4, visibleSize.height *19 / 20);
	addChild(Title);

	Score = CCLabelTTF::create("score : 0", "futura-48.fnt", 32);
	Score->setPosition(visibleSize.width / 8, visibleSize.height * 18 / 20);
	Score->setColor(ccc3(0, 0, 0));
	addChild(Score, 12);
	
	/*
    building = Building::createWithNumbsersAndImage(10, "block.png");
	building->setPosition(visibleSize.width / 2, GROUND_HEIGHT+2000);
    //building->setTag(BUILDING_TAG);
	addChild(building);
	*/

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Stage::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
    return true;
}
void Stage::jump_scheduler(float time) {
    if(character->getPosition().y >=visibleSize.height/2) {
        //배경을 내림
		status->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 9 / 20);
		Title->setPosition(visibleSize.width * 3 / 4, character->getPosition().y+visibleSize.height * 9 / 20);
		Score->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 8 / 20);
 
		this->setPosition(Vec2(this->getPosition().x,-character->getPosition().y+visibleSize.height/2));
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(Vec2(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,visibleSize.height*5+GROUND_HEIGHT/2+(visibleSize.height/2-character->getPosition().y)));
    }
    else if(character->getPosition().y<=GROUND_HEIGHT+character->getContentSize().height/2+1) {
        //캐릭터 안흔들리게
        //character->getPhysicsBody()->setAngularVelocity(0.);
        character->getPhysicsBody()->setVelocity(Vec2(0.,0.));
        character->setPosition(Vec2(posCharacter[cntofPosCharacter],GROUND_HEIGHT+character->getContentSize().height/2));
        
        //점프 중지
        character->setState(sGround);
        unschedule(schedule_selector(Stage::jump_scheduler));
    }
    else {
        //배경 안움직임
		status->setPosition(visibleSize.width / 8, visibleSize.height * 19 / 20);
		Title->setPosition(visibleSize.width * 3 / 4, visibleSize.height * 19 / 20);
		Score->setPosition(visibleSize.width / 8,  visibleSize.height * 18 / 20);

		this->setPosition(this->getPosition().x,0);
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,visibleSize.height*5+GROUND_HEIGHT/2);
    }
}
/*
void Stage::skill_blocking(){

}*/
void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
    //auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));
//	int i = 0;
    switch (keyCode){
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
            if(cntofPosCharacter!=0&&Game_Pause==0)
                character->setPosition(posCharacter[--cntofPosCharacter],character->getPosition().y);
            break;
        }
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
            if(cntofPosCharacter!=2&&Game_Pause==0)
                character->setPosition(posCharacter[++cntofPosCharacter],character->getPosition().y);
            break;
        }
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        {
            if (character->getState() == sGround&&Game_Pause==0) {
                character->setState(sAir);
                auto jump = JumpBy::create(1, Vec2(0, 1000), 1000, 1);
                jump->setTag(JUMP_TAG);
                character->runAction(jump);
                
                //점프동작
                if (!isScheduled(schedule_selector(Stage::jump_scheduler)))
                    schedule(schedule_selector(Stage::jump_scheduler));
                break;
            }
            break;
        }
        // 부수기
		/*
		case EventKeyboard::KeyCode::KEY_Z:
        {
            //auto building=dynamic_cast<Building *>(getChildByTag(BUILDING_TAG));
            character->stopActionByTag(ATTACK_TAG);
            if(abs(character->getPosition().y+character->getContentSize().height/2+building->getContentSize().height/2-building->getPosition().y)<5) {
                building->attack();
				character->increaseScore(1);
				sprintf(coinScore, "score: %d", character->getScore());
				pLabel2->setString(coinScore);
            }
            //character->setAttack(N);
            if (character->getActionState() == None) {
                character->setActionState(Attacking);
                Vector<SpriteFrame*> animFrames(15);
                char str[100] = { 0 };
                for (int i = 1; i < 15; i++){
                    sprintf(str, "grossini_dance_%02d.png", i);
                    auto frame = SpriteFrame::create(str, Rect(0, 0, 80, 115));
                    animFrames.pushBack(frame);
                }
                auto frame = SpriteFrame::create("grossini_dance_05.png", Rect(0, 0, 80, 115));
                animFrames.pushBack(frame);
                auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
				auto animate = Animate::create(animation);

				auto pCallback = CallFunc::create(CC_CALLBACK_0(Stage::stopAttack, this));
				auto pSequence = Sequence::create(animate, pCallback, nullptr);
				pSequence->setTag(ATTACK_TAG);
				character->runAction(pSequence);

				character->getPhysicsBody()->setCategoryBitmask(0x08);// 0010
				character->getPhysicsBody()->setContactTestBitmask(0x04); // 1000
				character->getPhysicsBody()->setCollisionBitmask(0x06);	// 0001

			}
			break;
		}*/
		// 막기
		case EventKeyboard::KeyCode::KEY_X:
		{
            character->setActionState(Blocking);
			character->getPhysicsBody()->setCategoryBitmask(0x04);// 0010
			character->getPhysicsBody()->setContactTestBitmask(0x01); // 1000
			character->getPhysicsBody()->setCollisionBitmask(0x06);	// 0001
			//z가 작동하지 않아서 일단 막기를 눌렀을떄 점수가 상승하는것으로 표현한다
			/*character->increaseScore(1);
			sprintf(coinScore, "score : %d", character->getScore());
			pLabel2->setString(coinScore);//*/
			break;
		}
		// 나중에 막기 X로 옮길 것
		case EventKeyboard::KeyCode::KEY_C:
		{
			status->increaseScore(10);
			sprintf(status->getcoinScore(), "score : %d", status->getScore());
			Score->setString(status->getcoinScore());
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

void Stage::stopAttack()
{
	//auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));
	character->setActionState(None);
}

void Stage::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));
	
	switch (keyCode){
        case EventKeyboard::KeyCode::KEY_X: {
            character->setActionState(None);
        }
		case EventKeyboard::KeyCode::KEY_Z: {
			character->getPhysicsBody()->setCategoryBitmask(0x01);// 0010
			character->getPhysicsBody()->setContactTestBitmask(0x04); // 1000
			character->getPhysicsBody()->setCollisionBitmask(0x03);	// 0001
            character->setActionState(None);
		}
	}
}

bool Stage::onContactBegin(PhysicsContact& contact)
{
    character->stopActionByTag(JUMP_TAG);
    switch (character->getActionState()) {
        case Attacking:
            //building->attack();
            break;
        case Blocking:
            character->getPhysicsBody()->setVelocity(building->getPhysicsBody()->getVelocity());
            building->getPhysicsBody()->setVelocity(Vec2(0,0));
            break;
        case None:
            character->getPhysicsBody()->setVelocity(building->getPhysicsBody()->getVelocity());
            break;
    }
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