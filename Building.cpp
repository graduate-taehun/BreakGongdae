//
//  Building.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#include "Building.h"
#include "Stage2.h"

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
bool Building::initWithBlockSize(string filename, Size _blocksize) {
    if(!LayerColor::initWithColor(Color4B::GREEN)) return false;
    blocksize=_blocksize;
    const vector<int>& durabTemp=durabilities.at(filename);
    
    //초기화
    removeAllChildren();
    ignoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2(0.5,0.5));
    background=Sprite::create(filename);
    
    setContentSize(Size(blocksize.width, background->getContentSize().height));
    //background->setContentSize(getContentSize());
    background->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    addChild(background);
    
    blocks=new queue<Block *>();
    auto body = PhysicsBody::createBox(getContentSize(),material);
    body->setRotationEnable(false);
    body->removeAllShapes();
    
    //block들 생성
    for(int i=0; i<durabTemp.size(); i++) {
        auto block=Block::create(durabTemp.at(i),filename,i);
        block->setContentSize(blocksize);
        block->setPosition(Vec2(0,((float)i+0.5)*blocksize.height-getContentSize().height/2));
        
        //블록 1개당 1개의 PhysicsShape
        auto shapebox = PhysicsShapeBox::create(block->getContentSize(),material,block->getPosition());
        
        body->addShape(shapebox);
        blocks->push(block);
        addChild(block);
    }
    auto shapeRoof=PhysicsShapeBox::create(Size(blocksize.width, blocksize.height/10),material,Vec2(0,getContentSize().height/2-blocksize.height/20));
    body->addShape(shapeRoof);
    body->setVelocityLimit(BUILDING_VEL_LIMIT);
    
    body->setCategoryBitmask(0x03);
    body->setContactTestBitmask(0x08);
    body->setCollisionBitmask(0x03);
    setPhysicsBody(body);
    
    return true;
}
bool Building::init(string filename) {
    return initWithBlockSize(filename, SIZE_DEFAULT_BLOCK);
}

Building* Building::create(string filename) {
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

Building* Building::createWithBlockSize(string filename, Size _blocksize) {
    Building *pRet = new Building();
    if (pRet && pRet->initWithBlockSize(filename, _blocksize)){
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
        setPosition(Vec2(getPosition().x,getPosition().y+blocksize.height/2));
        
        //제거
        removeChild(bottom);
        blocks->pop();
        
        if(blocks->size()==0) {
            removeAllChildren();
            return true;
        }
        setContentSize(Size(blocksize.width,getContentSize().height-blocksize.height));

        //일단 Shape 모두 제거
        getPhysicsBody()->removeAllShapes();
        for(auto i=getChildren().begin(); i!=getChildren().end(); i++) {
            if(*i==background)
                continue;
            //블럭 위치 재설정
            (*i)->setPosition(Vec2((*i)->getPosition().x,
                                                  (*i)->getPosition().y-blocksize.height/2));
            
            //shape 재생성 및 추가
            auto shapebox = PhysicsShapeBox::create((*i)->getContentSize(),material,(*i)->getPosition());
            getPhysicsBody()->addShape(shapebox);
        }
        
        
        auto shapeRoof=PhysicsShapeBox::create(Size(blocksize.width, blocksize.height/10),material,Vec2(0,getContentSize().height/2-blocksize.height/20));
        getPhysicsBody()->addShape(shapeRoof);
        
        background->setTextureRect(Rect(0,0,blocksize.width,getContentSize().height));
        background->setPosition(Vec2(background->getPosition().x,background->getPosition().y-blocksize.height/2));
        getPhysicsBody()->setCategoryBitmask(0x03);
        getPhysicsBody()->setContactTestBitmask(0x08);
        getPhysicsBody()->setCollisionBitmask(0x03);
	}
    return false;
}

void Building::setPositionOfBottom(float bottom) {
    setPosition(getPosition().x,bottom+getContentSize().height/2);
}

float Building::getPositionOfTop() {
    return getPosition().y+getContentSize().height/2;
}

float Building::getPositionOfBottom() {
    return getPosition().y-getContentSize().height/2;
}

//
//Stairs78
//
bool Stairs78::init() {
    if(!Building::initWithBlockSize(FILE_STAGE1+"78.png",SIZE_78)) return false;
    /*numberOfBuilding=1;
    nextBuilding=Building::createWithBlockSize("78.png", SIZE_78);
    nextBuilding->setPosition(Vec2(0,getContentSize().height));
    nextBuilding->getPhysicsBody()->setDynamic(false);
    setContentSize(Size(getContentSize().width,getContentSize().height+nextBuilding->getContentSize().height));
    addChild(nextBuilding);*/
    return true;
}