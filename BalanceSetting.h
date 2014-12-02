//
//  BalanceSetting.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 21..
//
//

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <string>
#include <cstdlib>
USING_NS_CC;
using namespace std;

#ifndef BreakGongDae_BalanceSetting_h
#define BreakGongDae_BalanceSetting_h

//For_Debug
#define START_SCENE     Stage1::createScene()
#define DEBUG_MODE      PhysicsWorld::DEBUGDRAW_ALL

//Blocking
#define CHARACTER_VEL_AFTER_BLOCKING 700
#define BUILDING_VEL_AFTER_BLOCKING 100
#define COST_BLOCKING 50
#define MIN_COST_BLOCKING 15
#define BLOCKING_GAUGE_VELOCITY 0.5

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
#define BLADE_VELOCITY 1000
#define TIME_BLADE_STOP 0.5

//Bonus Score
#define HONEY_BSCORE 2
#define NORMAL_BSCORE 1
#define HARD_BSCORE 0

//Blocks
#define SIZE_DEFAULT_BLOCK Size(780,260)
#define SIZE_78 Size(880,260)

//Files
//Seperator
#if (CC_TARGET_PLATFORM==CC_PLATFORM_MAC) \
 || (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    #define DIR_SEPERATOR "/"
#else
    #define DIR_SEPERATOR "\\"
#endif

//Folders
#define ROOT_RESOURCES      string("Resources")+DIR_SEPERATOR
#define FILE_BACKGROUND     ROOT_RESOURCES+"0. Background"+DIR_SEPERATOR
#define FILE_CHARACTER      ROOT_RESOURCES+"1. Character"+DIR_SEPERATOR
#define FILE_STAGE1         ROOT_RESOURCES+"2. Stage 1"+DIR_SEPERATOR
#define FILE_BOUNS_STAGE    ROOT_RESOURCES+"3. Bonus Stage"+DIR_SEPERATOR
#define FILE_STAGE2         ROOT_RESOURCES+"4. Stage 2"+DIR_SEPERATOR
#define FILE_BGM(__mp3__)   (ROOT_RESOURCES+"5. BGM"+DIR_SEPERATOR+__mp3__).data()
#define FILE_FONT           ROOT_RESOURCES"6. FONT"+DIR_SEPERATOR
#define FILE_ETC            ROOT_RESOURCES+"7. etc"+DIR_SEPERATOR

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

#define DURABS_78           4,1,1,1,1,1,1,1,1/*,1,1,\
                            4,1,1,1,1,1,1,1,1,1,1,\
                            4,1,1,1,1,1,1,1,1,1,1,\
                            5,2,2,2,2,2,2,2,2,2,2,\
                            5,2,2,2,2,2,2,2,2,2,2,\
                            7,3,3,3,3,3,3,3,3,3,3,\
                            9,4,4,4,4,4,5,5,5,6,6,\
                            10*/

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


#endif
/*
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
