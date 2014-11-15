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
    material=PhysicsMaterial(10.0f,0.0f,10.0f);
    removeAllChildren();
    delete blocks;
    blocks=new queue<Block *>();
    auto body = PhysicsBody::createBox(getContentSize(),material);
    
    
    
    body->removeAllShapes();
    for(int i=0; i<numbers; i++) {
        auto block=Block::createWithDurability(3);
        
        block->setTexture(filename);
        setContentSize(Size(block->getContentSize().width, block->getContentSize().height*numbers));
        block->setPosition(Vec2(0,(i-(numbers/2)+0.5)*block->getContentSize().height));
        
        auto shapebox = PhysicsShapeBox::create(block->getContentSize(),material,block->getPosition());
        
        //shapebox->setMass(10000.0f);
        shapebox->setTag(i);
        body->addShape(shapebox);
        
        blocks->push(block);
        addChild(block);
    }
    //body->setCategoryBitmask(0x04);	// 0100
    body->setContactTestBitmask(0x01); // 0001
    //body->setCollisionBitmask(0x06);	// 0110
    body->setRotationEnable(false);
    
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
        getPhysicsBody()->removeShape(blocks->size()-1);
        
        removeChild(bottom);
        blocks->pop();
        
        if(blocks->size()==0) return true;

        setPosition(Vec2(getPosition().x,getPosition().y+blocks->back()->getContentSize().height/2));
        
        getPhysicsBody()->removeAllShapes();
        
        for(int i=0; i<getChildren().size(); i++) {
            getChildren().at(i)->setPosition(Vec2(getChildren().at(i)->getPosition().x,getChildren().at(i)->getPosition().y-getChildren().at(i)->getContentSize().height/2));
            auto shapebox = PhysicsShapeBox::create(getChildren().at(i)->getContentSize(),material,getChildren().at(i)->getPosition());
            shapebox->setTag(i);
            getPhysicsBody()->addShape(shapebox);
        }
        setContentSize(Size(getContentSize().width,blocks->back()->getContentSize().height*blocks->size()));
        
        //getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(getContentSize().width,getContentSize().height)));
    }
    return false;
}

void Building::setPositionOfBottom(Point p) {
    
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