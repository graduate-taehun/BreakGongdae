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
bool Building::init(string filename, Size _blocksize, const vector<int>& currentDurabilities, int weight=0) {
    if(!Layer::init()) return false;
    blocksize=_blocksize;

    removeAllChildren();
    ignoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2(0.5,0.5));
    background=Sprite::create(filename);
    
    setContentSize(Size(blocksize.width, background->getContentSize().height));
    
    background->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    addChild(background);
    
    blocks=queue<Block *>();
    auto body = PhysicsBody::createBox(getContentSize(),material);
    body->setRotationEnable(false);
    body->removeAllShapes();
    
    //block들 생성
    for(unsigned long i=0; i<currentDurabilities.size(); i++) {
        auto block=Block::create((int)
                                    ((float)currentDurabilities.at(i)
                                        +( 1.0+(float)weight/16  )   ),filename,i);
        block->setContentSize(blocksize);
        block->setPosition(Vec2(0,((float)i+0.5)*blocksize.height-getContentSize().height/2));
        
        //블록 1개당 1개의 PhysicsShape
        auto shapebox = PhysicsShapeBox::create(block->getContentSize(),material,block->getPosition());
        
        body->addShape(shapebox);
        blocks.push(block);
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

Building* Building::createWithDurabilities(string filename, Size _blocksize, const vector<int>& currentDurabilities) {
    
    Building *pRet = new Building();
    if (pRet && pRet->init(filename, _blocksize, currentDurabilities)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Building* Building::createWithWeight(string filename, int weight) {
    if(filename==FILE_STAGE1+"78.png")
        return Stairs78::create();
    Building *pRet = new Building();
    if (pRet && pRet->init(filename, Block::SIZE_DEFAULT_BLOCK, durabilities.at(filename), weight)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void Building::restructure() {
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
}

bool Building::attack(bool isBlade) {
    auto bottom=blocks.front();
    if(!isBlade)
    bottom->attack();
    
    if(bottom->getDurability()<=0 || isBlade) {
        setPosition(Vec2(getPosition().x,getPosition().y+blocksize.height/2));

        removeChild(bottom);
        blocks.pop();
        
        if(blocks.size()==0) {
            removeAllChildren();
            return true;
        }
        restructure();
        getPhysicsBody()->setCategoryBitmask(0x03);
        getPhysicsBody()->setContactTestBitmask(0x08);
        getPhysicsBody()->setCollisionBitmask(0x03);
	}
    return false;
}

void Building::setPositionOfBottom(float bottom) {
    setPosition(getPosition().x,bottom+getContentSize().height/2);
}

float Building::getPositionOfTop() {   return getPosition().y+getContentSize().height/2;
}

float Building::getPositionOfBottom() {
    return getPosition().y-getContentSize().height/2;
}

bool Building::isEmpty() {
    return blocks.size()==0;
}

//
//Stairs78
//
bool Stairs78::init() {
    currentDurab=durabilities.at(FILE_78).cbegin();
    auto durabTemp=vector<int>(currentDurab,currentDurab+UNIT_NUM_78);
    
    if(!Building::init(FILE_78,Block::SIZE_78_BLOCK, durabTemp)) return false;
    
    currentDurab+=UNIT_NUM_78;
    nextBuilding=Sprite::create(FILE_78);
    nextBuilding->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2+nextBuilding->getContentSize().height/2+blocksize.height/2));
    addChild(nextBuilding);
    
    return true;
}

void Stairs78::restructure() {
    setContentSize(Size(blocksize.width,getContentSize().height-blocksize.height));
    
    //일단 Shape 모두 제거
    getPhysicsBody()->removeAllShapes();
    for(auto i=getChildren().begin(); i!=getChildren().end(); i++) {
        if(*i==background || *i==nextBuilding)
            continue;
        //블럭 위치 재설정
        (*i)->setPosition(Vec2((*i)->getPosition().x,
                               (*i)->getPosition().y-blocksize.height/2));
        
        //shape 재생성 및 추가
        auto shapebox = PhysicsShapeBox::create((*i)->getContentSize(),material,(*i)->getPosition());
        getPhysicsBody()->addShape(shapebox);
    }
    if(nextBuilding!=nullptr)
        nextBuilding->setPosition(Vec2(nextBuilding->getPosition().x, nextBuilding->getPosition().y-blocksize.height/2));
    
    auto shapeRoof=PhysicsShapeBox::create(Size(blocksize.width, blocksize.height/10),material,Vec2(0,getContentSize().height/2-blocksize.height/20));
    getPhysicsBody()->addShape(shapeRoof);
    
    background->setTextureRect(Rect(0,0,blocksize.width,getContentSize().height));
    background->setPosition(Vec2(background->getPosition().x,background->getPosition().y-blocksize.height/2));
}

bool Stairs78::attack(bool isBlade) {
    if(Building::attack(isBlade)) {
        if(currentDurab==durabilities.at(FILE_78).cend()) return true;
        
        vector<int> durabTemp;
        if(currentDurab+UNIT_NUM_78>durabilities.at(FILE_78).cend()) {
            durabTemp=vector<int>(currentDurab,durabilities.at(FILE_78).cend());
            Building::init(FILE_STAGE1+"78_final.png", Block::SIZE_78_BLOCK, durabTemp);
            nextBuilding=nullptr;
            currentDurab=durabilities.at(FILE_78).cend();
            removeChild(nextBuilding);
        }
        else {
            durabTemp=vector<int>(currentDurab,currentDurab+UNIT_NUM_78);
            Building::init(FILE_78, Block::SIZE_78_BLOCK, durabTemp);
            
            currentDurab+=UNIT_NUM_78;
            if(currentDurab+UNIT_NUM_78>durabilities.at(FILE_78).cend())
                nextBuilding=Sprite::create(FILE_STAGE1+"78_final.png");
            else
                nextBuilding=Sprite::create(FILE_78);
            nextBuilding->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2+nextBuilding->getContentSize().height/2+blocksize.height/2));
            addChild(nextBuilding);
        }
        
        setPosition(Vec2(getPosition().x,getPosition().y+getContentSize().height/2));
    }
    return false;
}