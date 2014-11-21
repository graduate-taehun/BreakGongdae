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
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuStage::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool MenuStage::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto item_1 = MenuItemFont::create("Start", CC_CALLBACK_1(MenuStage::menuCallbackforStage, this));
    auto item_2 = MenuItemFont::create("Score", CC_CALLBACK_1(MenuStage::menuCallbackforScoreBoard, this));
    auto item_3 = MenuItemFont::create("exit", CC_CALLBACK_1(MenuStage::menuCallbackforExit, this));
    
    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    
    return true;
}
void MenuStage::menuCallbackforStage(Ref* pSender)
{
    Director::getInstance()->replaceScene(Stage::createScene());
}
void MenuStage::menuCallbackforScoreBoard(Ref* pSender)
{
    Director::getInstance()->replaceScene(ScoreBoard::createScene());
}
void MenuStage::menuCallbackforExit(Ref* pSender)
{
    Director::getInstance()->end();
}


Scene* ScoreBoard::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ScoreBoard::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool ScoreBoard::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(ScoreBoard::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
    
    // create menu, it's an autorelease object
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