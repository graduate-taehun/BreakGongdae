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
    else
    {
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
const PhysicsMaterial Building::material=PhysicsMaterial(10000000.0f,0.0f,0.0f);
const map<string, const vector<int>> Building::durabilities
={
    {Stage1::fileBuilding[0],vector<int>{DURABS_MUEUNJAE}},
    {Stage1::fileBuilding[1],vector<int>{DURABS_JIGOK}},
    {Stage1::fileBuilding[2],vector<int>{DURABS_OLD_DORM_4}},
    {Stage1::fileBuilding[3],vector<int>{DURABS_OLD_DORM_3}},
    {Stage1::fileBuilding[4],vector<int>{DURABS_GYM}},
    {Stage1::fileBuilding[5],vector<int>{DURABS_DICE}},
    {Stage1::fileBuilding[6],vector<int>{DURABS_OLD_DORM_3}},
    {Stage1::fileBuilding[7],vector<int>{DURABS_RC}},
    {Stage1::fileBuilding[8],vector<int>{DURABS_OLD_DORM_4}},
    {Stage1::fileBuilding[9],vector<int>{DURABS_OLD_DORM_4}},
    {Stage1::fileBuilding[10],vector<int>{DURABS_78}}
};

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
        shapebox->setTag(i);
        
        body->addShape(shapebox);
        blocks->push(block);
        addChild(block);
    }
    
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
    if (pRet && pRet->init(filename))
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
            //크기 재설정
            
        }
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
