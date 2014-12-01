//
//  Menu&Score.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 11..
//
//

#include "Menu&Score.h"
#include "Stage2.h"
#include "BonusStage.h"
#include <SimpleAudioEngine.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

bool comp(int i, int j){ return (i > j); }
//
//ScoreBoard
//
Scene* ScoreBoard::createScene()
{
    auto scene = Scene::create();
    auto layer = ScoreBoard::create();
    scene->addChild(layer);
    return scene;
}

bool ScoreBoard::init()
{
    if (!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(ScoreBoard::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
	auto background = Sprite::create("rank.png");
	background->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	background->setPosition(visibleSize.width / 2, visibleSize.height * 5);
	addChild(background);

	auto label = LabelTTF::create("** Ranking **", "Arial Rounded MT Bold", 60);
    label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 200);
    this->addChild(label);
    
    // string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Score.txt");
    // "C:/Users/LeeSangmin/AppData/Local/GongDae/Score.txt"
    string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "Score.txt";
    ifstream in;
    in.open(filePath.c_str());
    
	vector<int> temp_score(0);

	while (!in.eof()){
		string score;
		getline(in,score);
		if (score == "") break;
		int a = stoi(score);
		temp_score.push_back(a);
	}
	LabelTTF* lbtemp;
	sort(temp_score.begin(), temp_score.end(), comp);

	for (int i = 1; i <= 5; i++){	
		if (i > temp_score.size())
			break;

		if (i == 1)
			lbtemp = LabelTTF::create(to_string(i) + "st        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);
		else if (i == 2)
			lbtemp = LabelTTF::create(to_string(i) + "nd        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);
		else if (i == 3)
			lbtemp = LabelTTF::create(to_string(i) + "rd        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);
		else
			lbtemp = LabelTTF::create(to_string(i) + "th        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);

		lbtemp->setPosition(Vec2(origin.x + visibleSize.width *9 / 24, origin.y + visibleSize.height / 2 + 100 - 50 * i));
		lbtemp->setAnchorPoint(Vec2(0, 0.5));
		addChild(lbtemp);
	}
    in.close();
    
    return true;
}

void ScoreBoard::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif
    
    Director::getInstance()->replaceScene(MenuStage::createScene());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//
//MenuStage
//
Scene* MenuStage::createScene(){
    srand(time(NULL));
    auto scene = Scene::create();
    auto layer = MenuStage::create();
    scene->addChild(layer);
    return scene;
}

bool MenuStage::init(){
    if (!Layer::init())
        return false;
    
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("start_scecne.png");
	background->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	background->setPosition(visibleSize.width / 2, visibleSize.height * 5);
	addChild(background);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("opening.mp3", false);

	auto item1 = LabelBMFont::create("START", "bitmapFontTest3.fnt");
	auto item_1 = MenuItemLabel::create(item1, CC_CALLBACK_1(MenuStage::menuCallbackforStage, this));
	item_1->setScale(2, 2);

	auto item2 = LabelBMFont::create("SCORE", "bitmapFontTest3.fnt");
	auto item_2 = MenuItemLabel::create(item2, CC_CALLBACK_1(MenuStage::menuCallbackforScoreBoard, this));
	item_2->setScale(2, 2);
		
	auto item3 = LabelBMFont::create("EXIT", "bitmapFontTest3.fnt");
	auto item_3 = MenuItemLabel::create(item3, CC_CALLBACK_1(MenuStage::menuCallbackforExit, this));
	item_3->setScale(2, 2);

	auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    
    return true;
}

void MenuStage::menuCallbackforStage(Ref* pSender){
    Director::getInstance()->replaceScene(START_SCENE);
}
void MenuStage::menuCallbackforScoreBoard(Ref* pSender){
    Director::getInstance()->replaceScene(ScoreBoard::createScene());
}
void MenuStage::menuCallbackforExit(Ref* pSender){
    Director::getInstance()->end();
}

//
//EndScene
//
Scene* EndScene::createSceneWithScore(Status status) {
	auto scene = Scene::create();
	auto layer = EndScene::createWithScore(status);
	scene->addChild(layer);
	return scene;
}
EndScene* EndScene::createWithScore(Status& status){
    EndScene *pRet = new EndScene();
    
    if (pRet && pRet->initWithScore(status)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool EndScene::initWithScore(Status& status) {
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(EndScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));

	auto background = Sprite::create("end.png");
	background->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	background->setPosition(visibleSize.width / 2, visibleSize.height * 5);
	addChild(background);

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	
	auto score = LabelTTF::create("Score : " + to_string(status.getScore()), "Arial Rounded MT Bold", 45);
	score->setColor(ccc3(0, 0, 0));
	score->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 240));
	addChild(score);

	auto combo = LabelTTF::create("MAX Combo : " + to_string(status.getMAX_COMBO()), "Arial Rounded MT Bold", 45);
	combo->setColor(ccc3(0, 0, 0));
	combo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 180));
	addChild(combo);

	// string filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Score.txt");
	// "C:/Users/LeeSangmin/AppData/Local/GongDae/Score.txt"
	string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "Score.txt";
	ofstream out;
	out.open(filePath.c_str(), ios::app);

	out << status.getScore() << endl;

	out.close();

	return true;
}

void EndScene::menuCloseCallback(Ref* pSender){	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->replaceScene(MenuStage::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
