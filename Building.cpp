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
    
    removeAllChildren();
    delete blocks;
    blocks=new queue<Block *>();
    
    for(int i=0; i<numbers; i++) {
        auto block=Block::createWithDurability(3);
        
        block->setTexture(filename);
        setContentSize(Size(block->getContentSize().width, block->getContentSize().height*numbers));
        block->setPosition(Vec2(0,(i-(numbers/2)+0.5)*block->getContentSize().height));
        
        blocks->push(block);
        addChild(block);
    }
    
    auto body = PhysicsBody::createBox(getContentSize());
    body->setCategoryBitmask(0x04);	// 0100
    body->setContactTestBitmask(0x08); // 1000
    body->setCollisionBitmask(0x06);	// 0110
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

void Building::attack() {
    auto bottom=blocks->front();
    bottom->attack();
    if(bottom->getDurability()<=0) {
        
        //getPhysicsBody()->setPositionOffset(Vec2(0,-blocks->back()->getContentSize().height/2));
        
        
        removeChild(bottom);
        blocks->pop();

        setPosition(Vec2(getPosition().x,getPosition().y+blocks->back()->getContentSize().height/2));

        for(int i=0; i<getChildren().size(); i++) {
            getChildren().at(i)->setPosition(Vec2(getChildren().at(i)->getPosition().x,getChildren().at(i)->getPosition().y-getChildren().at(i)->getContentSize().height/2));
        }
        setContentSize(Size(getContentSize().width,blocks->back()->getContentSize().height*blocks->size()));
        
        getPhysicsBody()->removeAllShapes();
        getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(getContentSize().width,getContentSize().height)));
    }
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