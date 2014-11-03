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

Grosss::Grosss()
{
	grosinit();
	s = G;
	a = N;
}

void Grosss::grosinit() {
	gros = Sprite::create("grossini.png");
	gros->setPosition(Stage::visibleSize.width / 2, Stage::GROUND + gros->getContentSize().height / 2);
	auto body = PhysicsBody::createBox(gros->getContentSize(), PhysicsMaterial(1., 0., 0.), Vec2(0, 0));
	body->setAngularVelocityLimit(0);
	body->setCategoryBitmask(0x01); // 0001
	body->setContactTestBitmask(0x04); // 0100
	body->setCollisionBitmask(0x03); // 0011
	gros->setPhysicsBody(body);
}

Sprite* Grosss::getgros(){ return gros; }
state Grosss::getstate(){ return s; }
void Grosss::setstate(state ss){ s = ss; }
attack Grosss::getattack(){ return a; }
void Grosss::setattack(attack aa){ a = aa; }


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
    
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width,visibleSize.height*10-GROUND), PhysicsMaterial(0.,0.,0.),1);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height*5+GROUND/2));
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
    //visibleSize=Director::getInstance()->getVisibleSize();
    auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

    auto *background=Sprite::create("stage_background.png");
    background->setContentSize(Size(visibleSize.width,visibleSize.height*10));
    background->setPosition(visibleSize.width/2,visibleSize.height*5);
    addChild(background);
    

	addChild(g.getgros());
	g.setTag(CHARACTER_TAG);

	auto *block = Sprite::create("block.png");
	block->setScale(0.1, 0.1);
	auto block_body = PhysicsBody::createBox(block->getContentSize() / 10, PhysicsMaterial(0., 0., 0.), Vec2(0, 0));
	block_body->setAngularVelocityLimit(0);

	// 郊韓拭 薗顕
	block_body->setCategoryBitmask(0x04);	// 0100
	block_body->setContactTestBitmask(0x08); // 1000
	block_body->setCollisionBitmask(0x06);	// 0110

	block->setPhysicsBody(block_body);
	block->setPosition(visibleSize.width / 2, GROUND + block->getContentSize().height);
	addChild(block);
	block->setTag(1);
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Stage::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
    return true;
}
/*Stage::~Stage() {
    
}*/

void Stage::jump_scheduler(float time) {
    auto character = g.getgros();
    if(character->getPosition().y >=visibleSize.height/2) {
        //배경을 내림
        this->setPosition(Vec2(this->getPosition().x,-character->getPosition().y+visibleSize.height/2));
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(Vec2(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,visibleSize.height*5+GROUND/2+(visibleSize.height/2-character->getPosition().y)));
    }
    else if(character->getPosition().y<=GROUND+character->getContentSize().height/2+1) {
        //캐릭터 안흔들리게
        character->getPhysicsBody()->setAngularVelocity(0.);
        character->getPhysicsBody()->setVelocity(Vec2(0.,0.));
        character->setRotation(0);
        character->setPosition(Vec2(posCharacter[cntofPosCharacter],GROUND+character->getContentSize().height/2));
        
        //점프 중지
        unschedule(schedule_selector(Stage::jump_scheduler));
    }
    else {
        //배경 안움직임
        this->setPosition(this->getPosition().x,0);
        
        this->getScene()->getChildByTag(EDGE_TAG)->setPosition(this->getScene()->getChildByTag(EDGE_TAG)->getPosition().x,visibleSize.height*5+GROUND/2);
        //안흔들리게
        character->setRotation(0);
        character->getPhysicsBody()->setAngularVelocity(0.);
    }
}
/*
void Stage::skill_blocking(){
	

}*/
void Stage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event){
    auto character = g.getgros();
    
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
			if (g.getstate() == G){
				g.setstate(AIR);
				auto act = JumpBy::create(1, Vec2(0, 1000), 1000, 1);
				character->runAction(act);

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
			if (g.getattack() == N)
			{
				g.setattack(Y);
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

				character->runAction(animate);

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

void Stage::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto character = g.getgros();
	
	switch (keyCode){
		case EventKeyboard::KeyCode::KEY_Z:{

			character->getPhysicsBody()->setCategoryBitmask(0x01);// 0010
			character->getPhysicsBody()->setContactTestBitmask(0x04); // 1000
			character->getPhysicsBody()->setCollisionBitmask(0x03);	// 0001
			g.setattack(N);
		}
	}
}

bool Stage::onContactBegin(PhysicsContact& contact)
{
	auto character = g.getgros();

	auto sp1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int tag1 = sp1->getTag();

	auto sp2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tag2 = sp2->getTag();
	
	removeChild(sp1, true);
	
	return true;
}