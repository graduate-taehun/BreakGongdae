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
    virtual bool init(int _durability);
    
public:
    int getDurability();
    void attack();
    static Block* create(int _durability);
    const static Size SIZE_DEFAULT_BLOCK; //(780,260)
    const static Size SIZE_78_BLOCK; //(880,261)
};

class Building : public Layer {
protected:
    queue<Block *> blocks;
    Sprite* background;
    Size blocksize;
    
    const static PhysicsMaterial material; //(10000000.0f,0.0f,0.0f)
    
    // {Stage::fileBuilding , vector<int>{DURABS_XX}}
    const static map<string,const vector<int>> durabilities;
    
    virtual void restructure();
    
    bool init(string filename, Size _blocksize, const vector<int>& currentDurabilities, int weight);
public:
    static Building* createWithWeight(string filename, int weight);
    void setPositionOfBottom(float bottom);
    float getPositionOfTop();
    float getPositionOfBottom();
    virtual bool attack(bool isBlade); //다 없어지면 true 리턴
    bool isEmpty();
};

class Stairs78 : public Building {
private:
    const static string FILE_78; //=FILE_STAGE1+"78.png"
    const static int UNIT_NUM_78=9;
    
    Sprite* nextBuilding;
    vector<int>::const_iterator currentDurab;
    
    virtual bool init();
    virtual void restructure();
    
public:
    CREATE_FUNC(Stairs78)
    bool attack(bool isBlade); //다 없어지면 true 리턴
};

#endif /* defined(__BreakGongDae__Building__) */