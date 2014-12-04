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
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>

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

bool comp(int i, int j){ return (i > j); }

bool ScoreBoard::init()
{
    if (!Layer::init())
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(FILE_ETC+"CloseNormal.png", FILE_ETC+"CloseSelected.png", CC_CALLBACK_1(ScoreBoard::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
	auto background = Sprite::create(FILE_BACKGROUND+"rank.png");
	background->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	background->setPosition(visibleSize.width / 2, visibleSize.height * 5);
	addChild(background);

	auto label = Label::createWithSystemFont("** Ranking **", "Arial Rounded MT Bold", 60);
    label->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 200);
    this->addChild(label);
    
    // string filePath = CCFileUtils::getInstance()->fullPathForFilename("Score.txt");
    // "C:/Users/LeeSangmin/AppData/Local/GongDae/Score.txt"
    string filePath = FileUtils::getInstance()->getWritablePath() + "Score.txt";
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
	Label* lbtemp;
	sort(temp_score.begin(), temp_score.end(), comp);

	for (unsigned long i = 1; i <= 5; i++){
		if (i > temp_score.size())
			break;

		if (i == 1)
			lbtemp = Label::createWithSystemFont(to_string(i) + "st        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);
		else if (i == 2)
			lbtemp = Label::createWithSystemFont(to_string(i) + "nd        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);
		else if (i == 3)
			lbtemp = Label::createWithSystemFont(to_string(i) + "rd        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);
		else
			lbtemp = Label::createWithSystemFont(to_string(i) + "th        " + to_string(temp_score[i-1]), "Arial Rounded MT Bold", 35);

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

	auto background = Sprite::create(FILE_BACKGROUND+"start_scene.png");
	background->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
	background->setPosition(visibleSize.width / 2, visibleSize.height * 5);
	addChild(background);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.6);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FILE_BGM("opening.mp3"), true);

	auto item1 = LabelBMFont::create("START", FILE_FONT+"bitmapFontTest3.fnt");
	auto item_1 = MenuItemLabel::create(item1, CC_CALLBACK_1(MenuStage::menuCallbackforStage, this));
	item_1->setScale(2, 2);

	auto item2 = LabelBMFont::create("SCORE", FILE_FONT+"bitmapFontTest3.fnt");
	auto item_2 = MenuItemLabel::create(item2, CC_CALLBACK_1(MenuStage::menuCallbackforScoreBoard, this));
	item_2->setScale(2, 2);
		
	auto item3 = Label::createWithBMFont(FILE_FONT+"bitmapFontTest3.fnt","EXIT");
	auto item_3 = MenuItemLabel::create(item3, CC_CALLBACK_1(MenuStage::menuCallbackforExit, this));
	item_3->setScale(2, 2);

	auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-30));
    this->addChild(menu);
    
    return true;
}

void MenuStage::menuCallbackforStage(Ref* pSender){
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
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
Scene* EndScene::createScene(Status& status, bool _allClear) {
	auto scene = Scene::create();
	auto layer = EndScene::create(status, _allClear);
	scene->addChild(layer);
	return scene;
}
EndScene* EndScene::create(Status& status, bool _allClear){
    EndScene *pRet = new EndScene();
    
    if (pRet && pRet->init(status, _allClear)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool EndScene::init(Status& status, bool _allClear) {
	if (!Layer::init())
		return false;
    allClear=_allClear;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create(FILE_BACKGROUND+(allClear?"allclear.png":"end.png"));
    background->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
    background->setPosition(visibleSize.width / 2, visibleSize.height * 5);
    addChild(background);
    
	auto closeItem = MenuItemImage::create(FILE_ETC+"CloseNormal.png", FILE_ETC+"CloseSelected.png", CC_CALLBACK_1(EndScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
	
	auto score = Label::createWithSystemFont("Score : " + to_string(status.getScore()), "Arial Rounded MT Bold", 45);
	score->setColor(Color3B(0, 0, 0));
    score->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + (allClear?-120:240)));
	addChild(score);

	auto combo = Label::createWithSystemFont("MAX Combo : " + to_string(status.getMAX_COMBO()), "Arial Rounded MT Bold", 45);
	combo->setColor(Color3B(0, 0, 0));
	combo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + (allClear?-40:180)));
	addChild(combo);

	// "C:/Users/LeeSangmin/AppData/Local/GongDae/Score.txt"
	string filePath = FileUtils::getInstance()->getWritablePath() + "Score.txt";
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
