//
//  Building.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#include "Building.h"

bool Block::init() {
    if(!Sprite::init()) return false;
    
    return true;
}

bool Building::init(int numbers, string filename) {
    if(!Layer::init()) return false;
    
    removeAllChildren();
    blocks.~queue();
    
    for(int i=0; i<numbers; i++) {
        auto *block=Block::create();
        block->setPosition(Vec2(0,i*block->getContentSize().height));
        block->setTexture(filename);
        block->setScale(0.1,0.1);
        block->setContentSize(Size(block->getContentSize().width/10,block->getContentSize().height/10));
        block->durability=10;
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
    if(blocks.back()->durability<0) {
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