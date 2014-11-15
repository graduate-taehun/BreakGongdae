//
//  Building.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#ifndef __BreakGongDae__Building__
#define __BreakGongDae__Building__

#include "cocos2d.h"
#include <queue>
USING_NS_CC;

class Block : public Sprite {
    int durability;
public:
    //Block(int _durability=10) : durability(_durability) {}
    int getDurability();
    void attack();
    virtual bool init(int _durability);
    static Block* createWithDurability(int _durability);
};

using namespace std;
class Building : public Layer {
private:
    queue<Block *>* blocks;
    PhysicsMaterial material;
public:
    ~Building();
    virtual bool initWithNumbersAndImage(int numbers, string filename);
    static Building* createWithNumbsersAndImage(int numbers, string filename);
    void setPositionOfBottom(Vec2 p);
    float getPositionOfTop();
    bool attack(); //다 없어지면 true 리턴
    void destroyAll();
};

#endif /* defined(__BreakGongDae__Building__) */