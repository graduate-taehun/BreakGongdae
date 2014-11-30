//
//  BalanceSetting.h
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 21..
//
//

#ifndef BreakGongDae_BalanceSetting_h
#define BreakGongDae_BalanceSetting_h

#define CHARACTER_VEL_AFTER_BLOCKING 700
#define BUILDING_VEL_AFTER_BLOCKING 100
#define BLOCKING_TIME_LIMIT 3000
#define COST_BLOCKING 50
#define MIN_COST_BLOCKING 15

#define BUILDING_VEL_LIMIT 600
#define GRAVITY 400
#define BUILDING_START_HEIGHT 500

#define CHARACTER_JUMP_VEL 1200

#define ATTACK_RANGE 100

#define TIME_WARNING 0.1
#define INTERVAL_WARNING_AND_LASER 0.3
#define TIME_SHOWING_LASER 0.2
#define MIN_INTERVAL_OF_REGENERATE_LASER 1
#define INTERVAL_REPLACE_BONUS_TO_STAGE2 1

#define BLADE_VELOCITY 1000
#define TIME_BLADE_STOP 0.5

#define HONEY_BSCORE 2
#define NORMAL_BSCORE 1
#define HARD_BSCORE 0

#define WIDTH_BLOCK 780
#define HEIGHT_BLOCK 260

#define FILE_BUILDINGS_STAGE1 \
    "Mueunjae.png", \
    "Jigok.png", \
    "Old_dormitory_9101112.png", \
    "Old_dormitory_131415.png", \
    "Gym.png", \
    "Old_dormitory_dice.png", \
    "Old_dormitory_171819.png", \
    "RC.png", \
    "Old_dormitory_1234.png", \
    "Old_dormitory_5678.png", \
    "78.png"

#define DURABS_MUEUNJAE 1,1,2
#define DURABS_JIGOK 5
#define DURABS_OLD_DORM_4 1,2,1,2,1,3,1,4
#define DURABS_OLD_DORM_3 1,2,1,3,1,4
#define DURABS_GYM 4,4,4
#define DURABS_DICE 5,6
#define DURABS_RC 1,1,2,3,5
#define DURABS_78 4,1,1,1,1,1,1,1,1,1,1,\
                  4,1,1,1,1,1,1,1,1,1,1,\
                  4,1,1,1,1,1,1,1,1,1,1,\
                  5,2,2,2,2,2,2,2,2,2,2,\
                  5,2,2,2,2,2,2,2,2,2,2,\
                  7,3,3,3,3,3,3,3,3,3,3,\
                  9,4,4,4,4,4,5,5,5,6,6,\
                  10

#define FILE_BUILDINGS_STAGE2 ""

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
/*
 "Mueunjae.png", "Jigok.png", "Old_dormitory_9101112.png", "Old_dormitory_131415.png", "Old_dormitory_dice.png", "Old_dormitory_171819.png", "RC.png", "Old_dormitory_1234.png", "Old_dormitory_5678.png", "78.png"
*/
