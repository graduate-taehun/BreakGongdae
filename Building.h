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
    const static Size SIZE_DEFAULT_BLOCK;
    const static Size SIZE_78_BLOCK;
};

class Building : public LayerColor {
protected:
    queue<Block *>* blocks;
    Sprite* background;
    Size blocksize;
    //virtual bool init(string filename);
    

    const static PhysicsMaterial material;
    const static map<string,const vector<int>> durabilities;
    
    virtual void restructure();
    
    bool initWithDurabilities(string filename, Size _blocksize, const vector<int>& currentDurabilities);
    static Building* createWithDurabilities(string filename, Size _blocksize, const vector<int>& currentDurabilities);
public:
    static Building* create(string filename);
    void setPositionOfBottom(float bottom);
    float getPositionOfTop();
    float getPositionOfBottom();
    virtual bool attack(bool isBlade); //다 없어지면 true 리턴
    bool isEmpty();
};

class Stairs78 : public Building {
private:
    const static string FILE_78;
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