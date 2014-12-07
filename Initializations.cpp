//
//  Initiallizations.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 30..
//
//

#include "Stage2.h"
#include "BonusStage.h"
#include "Character.h"
#include "Building.h"

//Stage
Size Stage::visibleSize = Director::getInstance()->getVisibleSize();

//Stage1
const vector<string> Stage1::fileBuilding={FILE_BUILDINGS_STAGE1};

//Bonus Stage
const vector<string> BonusStage::majors={FILE_MAJORS};
const map<string, vector<string>> BonusStage::courses_name
= {
    {BonusStage::majors[0],{"Circuit\nTheory","Digital\nSystem\nDesign","Signal\nand\nSystem"}},
    {BonusStage::majors[1],{"DS","Automata","OOP"}},
    {BonusStage::majors[2],{"Discrete\nMathematics","Set\nTheory","Differential\nGeometry"}},
    {BonusStage::majors[3],{"Organic\nChemistry","Chemical\nBiomolecular\nEngineering","Thermodynamics"}}
};

//Stage2
const vector<string> Stage2::fileBuilding={FILE_BUILDINGS_STAGE2};

//Character
const float Character::ATTACK_FRAME = 0.05f;
const float Character::CHARACTER_OFFSET=49;

//Block
const Size Block::SIZE_DEFAULT_BLOCK = Size(780,260);
const Size Block::SIZE_78_BLOCK      = Size(880,261);

//Building
const PhysicsMaterial Building::material=PhysicsMaterial(10000000.0f,0.0f,0.0f);
const map<string, const vector<int>> Building::durabilities
= {
    { Stage1::fileBuilding[0], vector<int>{DURABS_MUEUNJAE} },
    { Stage1::fileBuilding[1], vector<int>{DURABS_JIGOK} },
    { Stage1::fileBuilding[2], vector<int>{DURABS_OLD_DORM_4} },
    { Stage1::fileBuilding[3], vector<int>{DURABS_OLD_DORM_3} },
    { Stage1::fileBuilding[4], vector<int>{DURABS_GYM} },
    { Stage1::fileBuilding[5], vector<int>{DURABS_DICE} },
    { Stage1::fileBuilding[6], vector<int>{DURABS_OLD_DORM_3} },
    { Stage1::fileBuilding[7], vector<int>{DURABS_RC} },
    { Stage1::fileBuilding[8], vector<int>{DURABS_OLD_DORM_4} },
    { Stage1::fileBuilding[9], vector<int>{DURABS_OLD_DORM_4} },
    { Stage1::fileBuilding[10], vector<int>{DURABS_78} },
    
    { Stage2::fileBuilding[0], vector<int>{DURABS_ABC} },
    { Stage2::fileBuilding[1], vector<int>{DURABS_BASIC} },
    { Stage2::fileBuilding[2], vector<int>{DURABS_EE} },
    { Stage2::fileBuilding[3], vector<int>{DURABS_ENG} },
    { Stage2::fileBuilding[4], vector<int>{DURABS_MATH} }
};

//Stairs78
const string Stairs78::FILE_78= FILE_STAGE1+"78.png";