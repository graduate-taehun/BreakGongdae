//
//  Building.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#include "Building.h"

Block* Block::createWithDurability(int _durability) {
    Block *pRet = new Block();
    if (pRet && pRet->init(_durability)) {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Block::init(int _durability) {
    if(!Sprite::init()) return false;
    durability=_durability;
    return true;
}

int Block::getDurability() {
    return durability;
}

bool Building::initWithNumbersAndImage(int numbers, string filename) {
    if(!Layer::init()) return false;
    
    //초기화
    material=PhysicsMaterial(1000000000.0f,0.0f,0.0f);
    removeAllChildren();
    //delete blocks;
    
    blocks=new queue<Block *>();
    auto body = PhysicsBody::createBox(getContentSize(),material);
    body->setRotationEnable(false);
    body->removeAllShapes();
    
    //block들 생성
    for(int i=0; i<numbers; i++) {
        auto block=Block::createWithDurability(1);
        block->setTexture(filename);
        setContentSize(Size(block->getContentSize().width, block->getContentSize().height*numbers));
        block->setPosition(Vec2(0,(i-(numbers/2)+0.5)*block->getContentSize().height));
        
        //블록 1개당 1개의 PhysicsShape
        auto shapebox = PhysicsShapeBox::create(block->getContentSize(),material,block->getPosition());
        shapebox->setTag(i);
        
        body->addShape(shapebox);
        blocks->push(block);
        addChild(block);
    }
    
    body->setCategoryBitmask(0x02);
    body->setContactTestBitmask(0x08);
    body->setCollisionBitmask(0x01);
    body->setVelocityLimit(500);
    //body->setGravityEnable(false);
    setPhysicsBody(body);

    return true;
}

Building::~Building() {
    delete blocks;
}

void Block::attack() {
    durability--;
}

bool Building::attack() {
    auto bottom=blocks->front();
    bottom->attack();
    if(bottom->getDurability()<=0) {
        //제거
        getPhysicsBody()->removeShape(blocks->size()-1);
        removeChild(bottom,true);
        
        blocks->pop();
        
        if(blocks->size()==0) return true;

        //크기를 줄여야하므로(가운데를 기준으로 줄어듬) 위치를 block의 반만큼 올려야함
        setPosition(Vec2(getPosition().x,getPosition().y+blocks->back()->getContentSize().height/2));
        
        //일단 Shape 모두 제거
        getPhysicsBody()->removeAllShapes();
        for(int i=0; i<getChildren().size(); i++) {
            //블럭 위치 재설정
            getChildren().at(i)->setPosition(Vec2(getChildren().at(i)->getPosition().x,
                                                  getChildren().at(i)->getPosition().y-getChildren().at(i)->getContentSize().height/2));
            
            //shape 재생성 및 추가
            auto shapebox = PhysicsShapeBox::create(getChildren().at(i)->getContentSize(),material,getChildren().at(i)->getPosition());
            shapebox->setTag(i);
            getPhysicsBody()->addShape(shapebox);
        }
        //크기 재설정
        setContentSize(Size(getContentSize().width,blocks->back()->getContentSize().height*blocks->size()));
    }
    return false;
}

void Building::setPositionOfBottom(float bottom) {
    setPosition(getPosition().x,bottom+getContentSize().height/2);
}

float Building::getPositionOfTop() {
    return getPosition().y+getContentSize().height/2;
}

Building* Building::createWithNumbsersAndImage(int numbers, string filename)
{
    Building *pRet = new Building();
    if (pRet && pRet->initWithNumbersAndImage(numbers,filename))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}