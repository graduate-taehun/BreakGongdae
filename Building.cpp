//
//  Building.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#include "Building.h"
#include "Stage2.h"
#include <cstdlib>

//
//Block
//
bool Block::init(int _durability, string filename, int index) {
    if(!Sprite::init()) return false;
    
    durability=_durability;
    
    return true;
}

Block* Block::create(int _durability, string filename, int index) {
    Block *pRet = new Block();
    if (pRet && pRet->init(_durability, filename, index)) {
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

int Block::getDurability() {
    return durability;
}

void Block::attack() {
    durability--;
}

//
//Building
//
bool Building::init(string filename) {
    if(!Layer::init()) return false;
    
    const vector<int>& durabTemp=durabilities.at(filename);
    
    //초기화
    removeAllChildren();
    ignoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2(0.5,0));
    setContentSize(Size(WIDTH_BLOCK, HEIGHT_BLOCK*durabTemp.size()));
    
    background=Sprite::create(filename);
    background->setContentSize(getContentSize());
    background->setPosition(Vec2(getContentSize().width/2,getContentSize().height));
    addChild(background);
    
    blocks=new queue<Block *>();
    auto body = PhysicsBody::createBox(getContentSize(),material);
    body->setRotationEnable(false);
    body->removeAllShapes();

    //block들 생성
    for(int i=0; i<durabTemp.size(); i++) {
        auto block=Block::create(durabTemp.at(i),filename,i);
        block->setContentSize(Size(WIDTH_BLOCK,HEIGHT_BLOCK));
        block->setPosition(Vec2(0,(i+0.5)*HEIGHT_BLOCK));
        
        //블록 1개당 1개의 PhysicsShape
        auto shapebox = PhysicsShapeBox::create(block->getContentSize(),material,block->getPosition());
        
        body->addShape(shapebox);
        blocks->push(block);
        addChild(block);
    }
    auto shapeRoof=PhysicsShapeBox::create(Size(WIDTH_BLOCK, HEIGHT_BLOCK/10),material,Vec2(0,(durabTemp.size()-1/20)*HEIGHT_BLOCK));
    body->addShape(shapeRoof);
    body->setVelocityLimit(BUILDING_VEL_LIMIT);
    
    body->setCategoryBitmask(0x03);
    body->setContactTestBitmask(0x08);
    body->setCollisionBitmask(0x03);
    setPhysicsBody(body);

    return true;
}

Building* Building::create(string filename)
{
    Building *pRet = new Building();
    if (pRet && pRet->init(filename)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Building::attack(bool isBlade) {
    auto bottom=blocks->front();
    if(!isBlade)
    bottom->attack();
        
    if(bottom->getDurability()<=0 || isBlade) {
        setPosition(Vec2(getPosition().x,getPosition().y+HEIGHT_BLOCK));
        
        //제거
        removeChild(bottom);
        blocks->pop();
        
        if(blocks->size()==0) {
            removeAllChildren();
            return true;
        }
        //일단 Shape 모두 제거
        getPhysicsBody()->removeAllShapes();
        for(auto i=getChildren().begin(); i!=getChildren().end(); i++) {
            if(*i==background)
                continue;
            //블럭 위치 재설정
            (*i)->setPosition(Vec2((*i)->getPosition().x,
                                                  (*i)->getPosition().y-(*i)->getContentSize().height));
            
            //shape 재생성 및 추가
            auto shapebox = PhysicsShapeBox::create((*i)->getContentSize(),material,(*i)->getPosition());
            getPhysicsBody()->addShape(shapebox);
        }
        auto shapeRoof=PhysicsShapeBox::create(Size(WIDTH_BLOCK, HEIGHT_BLOCK/10),material,Vec2(0,(blocks->size()-1/20)*HEIGHT_BLOCK));
        getPhysicsBody()->addShape(shapeRoof);
        setContentSize(Size(WIDTH_BLOCK,HEIGHT_BLOCK*blocks->size()));
        background->setTextureRect(Rect(0,0,WIDTH_BLOCK,HEIGHT_BLOCK*blocks->size()));
        background->setContentSize(getContentSize());
        background->setPosition(Vec2(getContentSize().width/2,getContentSize().height));
        getPhysicsBody()->setCategoryBitmask(0x03);
        getPhysicsBody()->setContactTestBitmask(0x08);
        getPhysicsBody()->setCollisionBitmask(0x03);
	}
    return false;
}

void Building::setPositionOfBottom(float bottom) {
    setPosition(getPosition().x,bottom);
}

float Building::getPositionOfTop() {
    return getPosition().y+getContentSize().height;
}

float Building::getPositionOfBottom() {
    return getPosition().y;
}
