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

bool Building::init(int numbers, string filename) {
    if(!Layer::init()) return false;
    
    removeAllChildren();
    blocks.~queue();
    
    for(int i=0; i<numbers; i++) {
        auto *block=Block::createWithDurability(10);
        
        block->setTexture(filename);
        //block->setScale(0.1,0.1);
        //block->setContentSize(Size(block->getContentSize().width/10,block->getContentSize().height/10));
        setContentSize(Size(block->getContentSize().width,block->getContentSize().height*numbers));
        block->setPosition(Vec2(0,(i-(numbers/2)+0.5)*block->getContentSize().height));
        blocks.push(block);
        addChild(block);
    }
    
     return true;
}

void Block::attack() {
    durability--;
}

void Building::attack() {
    blocks.back()->attack();
    if(blocks.back()->getDurability()<0) {
        setContentSize(Size(getContentSize().width,getContentSize().height-blocks.back()->getContentSize().height));
        removeChild(blocks.back());
        blocks.pop();
    }
}

Building* Building::createWithNumbsersOfBlockAndImage(int numbers, string filename)
{
    Building *pRet = new Building();
    if (pRet && pRet->init(numbers,filename))
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