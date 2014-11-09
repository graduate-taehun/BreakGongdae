//
//  Stage.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 10. 24..
//
//

#include "Stage.h"
#include "Building.h"

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
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Stage::menuCloseCallback, this));

	closeItem->setPosition(Vec2(visibleSize.width - closeItem->getContentSize().width / 2,
		closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    //visibleSize=Director::getInstance()->getVisibleSize();
    auto *keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

    auto *background=Sprite::create("stage_background.png");
    background->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    background->setPosition(visibleSize.width/2,visibleSize.height*5);
    addChild(background);
    
    auto *character=Character::create();
	character->setTag(CHARACTER_TAG);
    character->setPosition(visibleSize.width / 2, GROUND_HEIGHT + character->getContentSize().height / 2);
    addChild(character);
    
    auto *pLabel_Title = LabelBMFont::create("BreakGongDae", "futura-48.fnt");
	pLabel_Title->setTag(TITLE_TAG);
	pLabel_Title->setPosition(visibleSize.width *3 / 4, visibleSize.height *19 / 20);
	addChild(pLabel_Title);

	auto *pLabel = CCLabelTTF::create("HP BAR", "Arial", 30);
	pLabel->setTag(STATUS_TAG);
	pLabel->setPosition(visibleSize.width / 8, visibleSize.height *18/20);
	addChild(pLabel);

	//	pLabel->setFontFillColor(Color3B::RED);
	//	pLabel->enableShadow(Size(10, 10), 255, 3.0);    // 그림자 떨어진 크기, 투명도, 두께
	//	pLabel->enableStroke(Color3B::RED, 2.0); // 외곽선 색상, 두께
	//	pLabel->setFontFillColor(Color3B(0, 0, 0));   // pLabel->setColor(Color3B::RED);

	auto *status_bar = Sprite::create("Hp.jpg");
	status_bar->setScale(0.5, 0.125);
	status_bar->setTag(HP_BAR_TAG);
	status_bar->setPosition(visibleSize.width / 8, visibleSize.height*19/20);
	
	addChild(status_bar);

	//body->setAngularVelocityLimit(0);
	//body->setCategoryBitmask(0x01); // 0001
	//body->setContactTestBitmask(0x04); // 0100
	//body->setCollisionBitmask(0x03); // 0011

	auto *Building = Building::createWithNumbsersOfBlockAndImage(10,"block.png");
    
    
    //block->setContentSize(Size(block->getContentSize().width*0.6,block->getContentSize().height*0.15));
    
	auto *Building_body = PhysicsBody::createBox(Building->getContentSize(), PhysicsMaterial(0., 0., 0.), Vec2(0,0));
    
	Building_body->setAngularVelocityLimit(0);
    //Building_body->setPositionOffset(Vec2(0,Building->getContentSize().height/2));

	// 郊韓拭 薗顕
	Building_body->setCategoryBitmask(0x04);	// 0100
	Building_body->setContactTestBitmask(0x08); // 1000
	Building_body->setCollisionBitmask(0x06);	// 0110

	Building->setPhysicsBody(Building_body);
    
	Building->setPosition(visibleSize.width / 2, GROUND_HEIGHT+1000);
    Building->setTag(Building_TAG);
	addChild(Building);
	
	auto *contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Stage::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
    return true;
}

void Stage::jump_scheduler(float time) {
    auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));
	auto pLabel_Title = dynamic_cast<LabelBMFont *>(getChildByTag(TITLE_TAG));
	auto pLabel = dynamic_cast<CCLabelTTF *>(getChildByTag(STATUS_TAG));
	auto status_bar = dynamic_cast<Sprite *>(getChildByTag(HP_BAR_TAG));

    if(character->getPosition().y >=visibleSize.height/2) {
        //배경을 내림
		status_bar->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 9 / 20);
		pLabel->setPosition(visibleSize.width / 8, character->getPosition().y + visibleSize.height * 8 / 20);
		pLabel_Title->setPosition(visibleSize.width * 3 / 4, character->getPosition().y+visibleSize.height * 9 / 20);
	
        this->setPosition(Vec2(this->getPosition().x,-character->getPosition().y+visibleSize.height/2));
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(Vec2(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,visibleSize.height*5+GROUND_HEIGHT/2+(visibleSize.height/2-character->getPosition().y)));
    }
    else if(character->getPosition().y<=GROUND_HEIGHT+character->getContentSize().height/2+1) {
        //캐릭터 안흔들리게
        character->getPhysicsBody()->setAngularVelocity(0.);
        character->getPhysicsBody()->setVelocity(Vec2(0.,0.));
        character->setRotation(0);
        character->setPosition(Vec2(posCharacter[cntofPosCharacter],GROUND_HEIGHT+character->getContentSize().height/2));
        
        //점프 중지
        character->setState(sGround);
        unschedule(schedule_selector(Stage::jump_scheduler));
    }
    else {
        //배경 안움직임
		status_bar->setPosition(visibleSize.width / 8, visibleSize.height * 19 / 20);
		pLabel->setPosition(visibleSize.width / 8, visibleSize.height * 18 / 20);
		pLabel_Title->setPosition(visibleSize.width * 3 / 4, visibleSize.height * 19 / 20);
        this->setPosition(this->getPosition().x,0);
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,visibleSize.height*5+GROUND_HEIGHT/2);
        
		//안흔들리게
        character->setRotation(0);
        character->getPhysicsBody()->setAngularVelocity(0.);
    }
}
/*
void Stage::skill_blocking(){
	

}*/
void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
    auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));
    
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
				auto jump = JumpBy::create(1, Vec2(0, 1000), 1000, 1);
				character->runAction(jump);

				//점프동작
				if (!isScheduled(schedule_selector(Stage::jump_scheduler)))
					schedule(schedule_selector(Stage::jump_scheduler));
					break;
				}
				break;
        }
		// 採呪奄
		case EventKeyboard::KeyCode::KEY_Z:
		{ 
											  character->stopActionByTag(21);
											  character->setAttack(N);
			if (character->getAttack() == N)
			{
                character->setAttack(Y);
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
				pSequence->setTag(21);
				character->runAction(pSequence);


				character->getPhysicsBody()->setCategoryBitmask(0x08);// 0010
				character->getPhysicsBody()->setContactTestBitmask(0x04); // 1000
				character->getPhysicsBody()->setCollisionBitmask(0x06);	// 0001

			}

			break;
		}
		// 厳奄
		case EventKeyboard::KeyCode::KEY_X:
		{
			character->getPhysicsBody()->setCategoryBitmask(0x04);// 0010
			character->getPhysicsBody()->setContactTestBitmask(0x01); // 1000
			character->getPhysicsBody()->setCollisionBitmask(0x06);	// 0001
			break;
		}
        default:
            break;
    }
}

void Stage::stopAttack()
{
	auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));
	character->setAttack(N);
}


void Stage::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));
	
	switch (keyCode){
		case EventKeyboard::KeyCode::KEY_Z:{

			character->getPhysicsBody()->setCategoryBitmask(0x01);// 0010
			character->getPhysicsBody()->setContactTestBitmask(0x04); // 1000
			character->getPhysicsBody()->setCollisionBitmask(0x03);	// 0001
			//character->setAttack(N);
		}
	}
}

bool Stage::onContactBegin(PhysicsContact& contact)
{
	//auto character = dynamic_cast<Character *>(getChildByTag(CHARACTER_TAG));

	auto sp1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto sp2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
    auto character=dynamic_cast<Character *>((sp1->getTag()==Building_TAG)?sp2:sp1);
    auto Building=/*dynamic_cast<Building *>*/((sp1->getTag()==Building_TAG)?sp1:sp2);
    
    switch (character->getAttack()) {
        case Y:
            removeChild(Building, true);
            break;
        case B:
            Building->getPhysicsBody()->setVelocity(Vec2(0,0));
            break;
        case N:
            break;
    }
	return true;
}

Scene* MenuStage::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuStage::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool MenuStage::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto item_1 = MenuItemFont::create("Start", CC_CALLBACK_1(MenuStage::menuCallback1, this));
	auto item_2 = MenuItemFont::create("Score", CC_CALLBACK_1(MenuStage::menuCallback2, this));
	auto item_3 = MenuItemFont::create("exit", CC_CALLBACK_1(MenuStage::menuCallback3, this));

	auto menu = Menu::create(item_1, item_2, item_3, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}

void MenuStage::menuCallback1(Ref* pSender)
{
	Director::getInstance()->replaceScene(Stage::createScene());
}
void MenuStage::menuCallback2(Ref* pSender)
{
	Director::getInstance()->replaceScene(ScoreBoard::createScene());
}
void MenuStage::menuCallback3(Ref* pSender)
{
	Director::getInstance()->end();
}
Scene* ScoreBoard::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ScoreBoard::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool ScoreBoard::init()
{
	//////////////////////////////
	// 1. super init first
	int num[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int i = 0;
	char str[10][10];
	while (i < 10)
	{
		sprintf(str[i], "%d", num[i]);
		i++;
	}
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ScoreBoard::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("ScoreBoard", "Arial", 35);
	auto label0 = LabelTTF::create(str[0], "Arial", 24);
	auto label1 = LabelTTF::create(str[1], "Arial", 24);
	auto label2 = LabelTTF::create(str[2], "Arial", 24);
	auto label3 = LabelTTF::create(str[3], "Arial", 24);
	auto label4 = LabelTTF::create(str[4], "Arial", 24);
	auto label5 = LabelTTF::create(str[5], "Arial", 24);
	auto label6 = LabelTTF::create(str[6], "Arial", 24);
	auto label7 = LabelTTF::create(str[7], "Arial", 24);
	auto label8 = LabelTTF::create(str[8], "Arial", 24);
	auto label9 = LabelTTF::create(str[9], "Arial", 24);
	// position the label on the center of the screen

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	label0->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 200));
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 150));
	label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 100));
	label3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 50));
	label4->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	label5->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 50));
	label6->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 100));
	label7->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 150));
	label8->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 200));
	label9->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 250));

	// add the label as a child to this layer
	this->addChild(label, 1);
	this->addChild(label0, 1);
	this->addChild(label1, 1);
	this->addChild(label2, 1);
	this->addChild(label3, 1);
	this->addChild(label4, 1);
	this->addChild(label5, 1);
	this->addChild(label6, 1);
	this->addChild(label7, 1);
	this->addChild(label8, 1);
	this->addChild(label9, 1);

	// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);

	return true;
}
void ScoreBoard::menuCloseCallback(Ref* pSender)
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