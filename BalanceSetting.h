//
//  BalanceSetting.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 21..
//
//

#ifndef BreakGongDae_BalanceSetting_h
#define BreakGongDae_BalanceSetting_h

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <string>
#include <cstdlib>
USING_NS_CC;
using namespace std;

//For_Debug
#define START_SCENE     BonusStage::createScene(nullptr)
#define DEBUG_MODE      PhysicsWorld::DEBUGDRAW_NONE

//Blocking
#define CHARACTER_VEL_AFTER_BLOCKING 700
#define BUILDING_VEL_AFTER_BLOCKING 100
#define COST_BLOCKING 50
#define MIN_COST_BLOCKING 15
#define BLOCKING_GAUGE_CHARGE_VELOCITY 0.5
#define BLOCKING_GAUGE_REDUCE_VELOCITY 0.6

//Building
#define BUILDING_VEL_LIMIT 600
#define GRAVITY 400
#define BUILDING_START_HEIGHT 1500

//Character
#define CHARACTER_JUMP_VEL 1200
#define TIME_PRE_JUMP 0.2
#define ATTACK_RANGE 150

//Laser & Warning
#define TIME_WARNING 0.1
#define INTERVAL_WARNING_AND_LASER 0.3
#define TIME_SHOWING_LASER 0.2
#define MIN_INTERVAL_OF_REGENERATE_LASER 1
#define INTERVAL_REPLACE_BONUS_TO_STAGE2 1

//Blade(Lethal Move)
#define BLADE_GAUGE_UNIT 1.7
#define BLADE_VELOCITY 1000
#define TIME_BLADE_STOP 0.3

//Bonus Score
#define HONEY_BSCORE 1
#define NORMAL_BSCORE 2
#define HARD_BSCORE 3

//Folders
#define ROOT_RESOURCES      string("Resources/")
#define FILE_BACKGROUND     ROOT_RESOURCES+"0. Background/"
#define FILE_CHARACTER      ROOT_RESOURCES+"1. Character/"
#define FILE_STAGE1         ROOT_RESOURCES+"2. Stage 1/"
#define FILE_BOUNS_STAGE    ROOT_RESOURCES+"3. Bonus Stage/"
#define FILE_STAGE2         ROOT_RESOURCES+"4. Stage 2/"
#define FILE_BGM(__mp3__)   (ROOT_RESOURCES+"5. BGM/"+__mp3__).data()
#define FILE_FONT           ROOT_RESOURCES+"6. FONT/"
#define FILE_ETC            ROOT_RESOURCES+"7. etc/"

//Files_Stage1
#define FILE_BUILDINGS_STAGE1 \
    FILE_STAGE1+"Mueunjae.png", \
    FILE_STAGE1+"Jigok.png", \
    FILE_STAGE1+"Old_dormitory_9101112.png", \
    FILE_STAGE1+"Old_dormitory_131415.png", \
    FILE_STAGE1+"Gym.png", \
    FILE_STAGE1+"Old_dormitory_dice.png", \
    FILE_STAGE1+"Old_dormitory_171819.png", \
    FILE_STAGE1+"RC.png", \
    FILE_STAGE1+"Old_dormitory_1234.png", \
    FILE_STAGE1+"Old_dormitory_5678.png", \
    FILE_STAGE1+"78.png"

#define DURABS_MUEUNJAE     1,1,2
#define DURABS_JIGOK        5
#define DURABS_OLD_DORM_4   1,2,1,2,1,3
#define DURABS_OLD_DORM_3   1,2,1,3,1
#define DURABS_GYM          4,4,4
#define DURABS_DICE         2,3
#define DURABS_RC           2,3,5

#define DURABS_78           1,1,1,1,1,1,1,1,4,\
                            1,1,1,1,1,1,1,1,4,\
                            1,1,1,1,1,1,1,1,4,\
                            2,2,2,2,2,2,2,2,5,\
                            2,2,2,2,2,2,2,2,5,\
                            3,3,3,3,3,3,3,3,6,\
                            3,3,3,3,3,3,3,3,7,\
                            4,4,4,4,4,5,5,5,8,\
                            5,5,5,6,8,10

//Files_BonusStage
#define FILE_MAJORS \
    "eece", \
    "csed", \
    "math", \
    "cheb"

//Files_Stage2
#define FILE_BUILDINGS_STAGE2 \
    FILE_STAGE2+"ABC.png", \
    FILE_STAGE2+"basic.png", \
    FILE_STAGE2+"electronic.png", \
    FILE_STAGE2+"english.png", \
    FILE_STAGE2+"math.png"

#define DURABS_ABC 1,1,1,2,4
#define DURABS_BASIC \
    2,1, \
    3,2,2, \
    2,5,2, \
    2,3,2, \
    3,2,3, \
    2,5,2
#define DURABS_EE \
    3,2,4, \
    2,2, \
    2,8,8,8, \
    3,8,10
#define DURABS_ENG \
    2, \
    5, \
    1,1, \
    1,3, \
    3,4,4, \
    2,3,3,3
#define DURABS_MATH \
    2,2,2, \
    3,4, \
    2,2, \
    3,7,7,8 \

#endif
/*
 Default Fonts
	"American Typewriter"
	"Arial"
	"Arial Rounded MT Bold"
	"Courier New"
	"Georgia"
	"Helvetica"
	"Marker Felt"
	"Times New Roman"
	"Trebuchet MS"
	"Verdana"
	"Zapfino"
*/
/*
	캐릭터 및 빌딩 비트마스크 처리 (순서는 category,contact,collision)
	1. 캐릭터가 땅에 있을 때
	0100
	0010
	0001

	2. 캐릭터가 점프했을 때
	0001
	0100
	0011

	3. 빌딩
	0011
	1000
	0011

	4. 바닥
	1001
	0011
	0101
*/