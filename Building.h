//
//  Building.h
//  BreakGongDae
//
//  Created by ������ on 2014. 11. 1..
//
//

#ifndef __BreakGongDae__Building__
#define __BreakGongDae__Building__

#include "cocos2d.h"
#include <queue>
USING_NS_CC;

class Block : Sprite {
private:
    int durability;
public:
    Block(int _durability=10) : durability(_durability) {}
    void attack();
    virtual bool init();
    CREATE_FUNC(Block);
};

using namespace std;
class Building : Layer {
private:
    queue<Block> blocks;
public:
    //Constructor(���� Layer::init ȣ��)
    static Building* create(/*�־����*/);
    void setPositionOfBottom();
    Point getPositionOfTop();
    void attack();
    void destroyAll();
};



#endif /* defined(__BreakGongDae__Building__) */