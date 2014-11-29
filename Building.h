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
#include "BalanceSetting.h"
#include <string>
#include <map>
#include <vector>
USING_NS_CC;
using namespace std;

class Block : public Sprite {
private:
    int durability;
    virtual bool init(int _durability, string filename, int index);
    
public:
    //Block(int _durability=10) : durability(_durability) {}
    int getDurability();
    void attack();
    static Block* create(int _durability, string filename, int index);
    
};

class Building : public Layer {
private:
    queue<Block *>* blocks;
    Sprite* background;
    const static PhysicsMaterial material;
    const static map<string,const vector<int>> durabilities;
    
    virtual bool init(string filename);
    
public:
    static Building* create(string filename);
    void setPositionOfBottom(float bottom);
    float getPositionOfTop();
    float getPositionOfBottom();
    bool attack(bool isBlade); //다 없어지면 true 리턴
    void destroyAll();
};

#endif /* defined(__BreakGongDae__Building__) */