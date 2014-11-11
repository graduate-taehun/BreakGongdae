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
    
    auto item_1 = MenuItemFont::create("Start", CC_CALLBACK_1(MenuStage::menuCallback1, this));
    auto item_2 = MenuItemFont::create("Score", CC_CALLBACK_1(MenuStage::menuCallback2, this));
    auto item_3 = MenuItemFont::create("exit", CC_CALLBACK_1(MenuStage::menuCallback3, this));
    
    auto menu = Menu::create(item_1, item_2, item_3, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    
    return true;
}

void MenuStage::menuCallback1(Ref* pSender)
{
    Director::getInstance()->replaceScene(Stage::createScene());
}
void MenuStage::menuCallback2(Ref* pSender)
{
    Director::getInstance()->replaceScene(ScoreBoard::createScene());
}
void MenuStage::menuCallback3(Ref* pSender)
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
    //////////////////////////////
    // 1. super init first
    int num[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int i = 0;
    char str[10][10];
    while (i < 10)
    {
        sprintf(str[i], "%d", num[i]);
        i++;
    }
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ScoreBoard::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                origin.y + closeItem->getContentSize().height / 2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("ScoreBoard", "Arial", 35);
    auto label0 = LabelTTF::create(str[0], "Arial", 24);
    auto label1 = LabelTTF::create(str[1], "Arial", 24);
    auto label2 = LabelTTF::create(str[2], "Arial", 24);
    auto label3 = LabelTTF::create(str[3], "Arial", 24);
    auto label4 = LabelTTF::create(str[4], "Arial", 24);
    auto label5 = LabelTTF::create(str[5], "Arial", 24);
    auto label6 = LabelTTF::create(str[6], "Arial", 24);
    auto label7 = LabelTTF::create(str[7], "Arial", 24);
    auto label8 = LabelTTF::create(str[8], "Arial", 24);
    auto label9 = LabelTTF::create(str[9], "Arial", 24);
    // position the label on the center of the screen
    
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    label0->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 + 200));
    label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 + 150));
    label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 + 100));
    label3->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 + 50));
    label4->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2));
    label5->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 - 50));
    label6->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 - 100));
    label7->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 - 150));
    label8->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 - 200));
    label9->setPosition(Vec2(origin.x + visibleSize.width / 2,
                             origin.y + visibleSize.height / 2 - 250));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    this->addChild(label0, 1);
    this->addChild(label1, 1);
    this->addChild(label2, 1);
    this->addChild(label3, 1);
    this->addChild(label4, 1);
    this->addChild(label5, 1);
    this->addChild(label6, 1);
    this->addChild(label7, 1);
    this->addChild(label8, 1);
    this->addChild(label9, 1);
    
    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
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