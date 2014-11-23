//
//  Menu&Score.cpp
//  BreakGongDae
//
//  Created by 유정민 on 2014. 11. 11..
//
//

#include "Menu&Score.h"
#include "Stage.h"

Scene* MenuStage::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuStage::create();
    scene->addChild(layer);
    return scene;
}
bool MenuStage::init()
{
    if (!Layer::init())
        return false;
    
    auto item_1 = MenuItemFont::create("Start", CC_CALLBACK_1(MenuStage::menuCallbackforStage, this));
    auto item_2 = MenuItemFont::create("Score", CC_CALLBACK_1(MenuStage::menuCallbackforScoreBoard, this));
    auto item_3 = MenuItemFont::create("exit", CC_CALLBACK_1(MenuStage::menuCallbackforExit, this));
    
    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    
    return true;
}
void MenuStage::menuCallbackforStage(Ref* pSender){
    Director::getInstance()->replaceScene(Stage::createScene());
}
void MenuStage::menuCallbackforScoreBoard(Ref* pSender){
    Director::getInstance()->replaceScene(ScoreBoard::createScene());
}
void MenuStage::menuCallbackforExit(Ref* pSender){
    Director::getInstance()->end();
}

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
    
    auto label = LabelTTF::create("ScoreBoard", "Arial", 35);
    for(int i=1; i<=10; i++) {
        auto lbtemp=LabelTTF::create(to_string(i), "Arial", 24);
        lbtemp->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50*(5-i)));
        addChild(lbtemp);
    }
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
Scene* EndScene::createScene(){
	auto scene = Scene::create();
	auto layer = EndScene::create();
	scene->addChild(layer);
	return scene;
}

bool EndScene::init(){
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(EndScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	auto label = LabelTTF::create("Score : ", "Arial", 35);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 250));
	addChild(label);

//	auto temp = LabelTTF::create(to_string(Stage::status->getScore()), "Arial", 24);
//	temp->setPosition(Vec2(origin.x + visibleSize.width / 2 + 50, origin.y + visibleSize.height / 2 + 50 * 5));
//	addChild(temp);

//	auto background = Sprite::create("end.jpg");
//	background->setContentSize(Size(visibleSize.width, visibleSize.height * 10));
//	background->setPosition(visibleSize.width / 2, visibleSize.height * 5);
//	addChild(background);

	return true;
}

void EndScene::menuCloseCallback(Ref* pSender)
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

