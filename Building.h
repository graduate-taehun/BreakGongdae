//
//  Building.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 1..
//
//

#ifndef __BreakGongDae__Building__
#define __BreakGongDae__Building__

#include "BalanceSetting.h"
#include <map>
#include <vector>
#include <queue>

class Block : public Sprite {
private:
    int durability;
    virtual bool init(int _durability, string filename, int index);
    
public:
    int getDurability();
    void attack();
    static Block* create(int _durability, string filename, int index);
    
};

class Building : public LayerColor {
private:
    queue<Block *>* blocks;
    Sprite* background;
    Size blocksize;
    virtual bool init(string filename);
protected:
    const static PhysicsMaterial material;
    const static map<string,const vector<int>> durabilities;
    
    virtual bool initWithBlockSize(string filename, Size _blocksize);
    static Building* createWithBlockSize(string filename, Size _blocksize);
public:
    static Building* create(string filename);
    void setPositionOfBottom(float bottom);
    float getPositionOfTop();
    float getPositionOfBottom();
    bool attack(bool isBlade); //다 없어지면 true 리턴
    void destroyAll();
};

class Stairs78 : public Building {
private:
    Building* nextBuilding;
    int numberOfBuilding;
    virtual bool init();
public:
    CREATE_FUNC(Stairs78)
};

#endif /* defined(__BreakGongDae__Building__) */