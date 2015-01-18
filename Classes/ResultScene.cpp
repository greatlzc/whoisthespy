//
//  ResultScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "ResultScene.h"
#include "Banker.h"
#include "WordsScene.h"
#include "StartScene.h"

USING_NS_CC;

Scene* ResultScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResultScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ResultScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto startItem = MenuItemImage::create(
                                           "media-play.png",
                                           "media-play.png",
                                           CC_CALLBACK_1(ResultScene::menuStartCallback, this));
    //startItem->setScale(0.6);
    startItem->setPosition(Vec2(origin.x + visibleSize.width/3,
                                origin.y + visibleSize.height/7));
    
    // create menu, it's an autorelease object
    auto startmenu = Menu::create(startItem, NULL);
    startmenu->setPosition(Vec2::ZERO);
    this->addChild(startmenu, 1);
    
    auto stopItem = MenuItemImage::create(
                                           "media-stop.png",
                                           "media-stop.png",
                                           CC_CALLBACK_1(ResultScene::menuStopCallback, this));
    //startItem->setScale(0.6);
    stopItem->setPosition(Vec2(origin.x + visibleSize.width*2/3,
                                origin.y + visibleSize.height/7));
    
    // create menu, it's an autorelease object
    auto stopmenu = Menu::create(stopItem, NULL);
    stopmenu->setPosition(Vec2::ZERO);
    this->addChild(stopmenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
//    TTFConfig ttf;
//    ttf.fontFilePath = "Abberancy.ttf";
//    ttf.fontSize = 90;
//    auto label = Label::createWithTTF(ttf, "Rank:");
//    label->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    auto label = Label::create("谁赢了", "Arial", 90);
    switch (Banker::getInstance()->GameEnding()) {
        case GUY:
            label->setString("平民赢了！");
            break;
        case SPY:
            label->setString("卧底赢了！");
            break;
        case LUCKY:
            label->setString("白板赢了！");
            break;
        default:
            break;
    }
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.1));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "StartScene" splash screen"
    auto sprite = Sprite::create("mainbg.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.8);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    Banker::getInstance()->accounting(Banker::getInstance()->GameEnding());
    Banker::getInstance()->rankPlayers();
    
    std::string no1name = "NULL";
    std::string no2name = "NULL";
    std::string no3name = "NULL";
    std::string no4name = "NULL";
    std::string no5name = "NULL";
    
    std::string no1score = "0";
    std::string no2score = "0";
    std::string no3score = "0";
    std::string no4score = "0";
    std::string no5score = "0";
    
    int playerCount = Banker::getInstance()->playerCount();
    if (playerCount >= 5) {
        no5name = Banker::getInstance()->mPlayers.at(4)->mName;
        no5score = std::to_string(Banker::getInstance()->mPlayers.at(4)->mScore);
    }
    if (playerCount >= 4) {
        no4name = Banker::getInstance()->mPlayers.at(3)->mName;
        no4score = std::to_string(Banker::getInstance()->mPlayers.at(3)->mScore);
    }
    if (playerCount >= 3) {
        no3name = Banker::getInstance()->mPlayers.at(2)->mName;
        no3score = std::to_string(Banker::getInstance()->mPlayers.at(2)->mScore);
    }
    if (playerCount >= 2) {
        no2name = Banker::getInstance()->mPlayers.at(1)->mName;
        no2score = std::to_string(Banker::getInstance()->mPlayers.at(1)->mScore);
    }
    if (playerCount >= 1) {
        no1name = Banker::getInstance()->mPlayers.at(0)->mName;
        no1score = std::to_string(Banker::getInstance()->mPlayers.at(0)->mScore);
    }

    auto no1label = Label::create("1." + no1name, "Arial", 70);
    auto no2label = Label::create("2." + no2name, "Arial", 70);
    auto no3label = Label::create("3." + no3name, "Arial", 70);
    auto no4label = Label::create("4." + no4name, "Arial", 70);
    auto no5label = Label::create("5." + no5name, "Arial", 70);
    
    auto originX = origin.x + visibleSize.width/4;
    auto originY = origin.y + visibleSize.height/1.4;
    auto marginX = visibleSize.width/2.5;
    auto marginY = no1label->getContentSize().height;
    
    no1label->setAnchorPoint(Vec2(0, 0));
    no2label->setAnchorPoint(Vec2(0, 0));
    no3label->setAnchorPoint(Vec2(0, 0));
    no4label->setAnchorPoint(Vec2(0, 0));
    no5label->setAnchorPoint(Vec2(0, 0));
    
    no1label->setPosition(Vec2(originX, originY));
    no2label->setPosition(Vec2(originX, originY - marginY));
    no3label->setPosition(Vec2(originX, originY - 2*marginY));
    no4label->setPosition(Vec2(originX, originY - 3*marginY));
    no5label->setPosition(Vec2(originX, originY - 4*marginY));
    
    this->addChild(no1label);
    this->addChild(no2label);
    this->addChild(no3label);
    this->addChild(no4label);
    this->addChild(no5label);
    
    auto no1scorelabel = Label::create(no1score, "Arial", 70);
    auto no2scorelabel = Label::create(no2score, "Arial", 70);
    auto no3scorelabel = Label::create(no3score, "Arial", 70);
    auto no4scorelabel = Label::create(no4score, "Arial", 70);
    auto no5scorelabel = Label::create(no5score, "Arial", 70);
    
    no1scorelabel->setAnchorPoint(Vec2(0, 0));
    no2scorelabel->setAnchorPoint(Vec2(0, 0));
    no3scorelabel->setAnchorPoint(Vec2(0, 0));
    no4scorelabel->setAnchorPoint(Vec2(0, 0));
    no5scorelabel->setAnchorPoint(Vec2(0, 0));
    
    no1scorelabel->setPosition(Vec2(originX + marginX, originY));
    no2scorelabel->setPosition(Vec2(originX + marginX, originY - marginY));
    no3scorelabel->setPosition(Vec2(originX + marginX, originY - 2*marginY));
    no4scorelabel->setPosition(Vec2(originX + marginX, originY - 3*marginY));
    no5scorelabel->setPosition(Vec2(originX + marginX, originY - 4*marginY));
    
    this->addChild(no1scorelabel);
    this->addChild(no2scorelabel);
    this->addChild(no3scorelabel);
    this->addChild(no4scorelabel);
    this->addChild(no5scorelabel);
    
    return true;
}


void ResultScene::menuStartCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    //to do
    auto wordsScene = WordsScene::createScene();
    Director::getInstance()->replaceScene(wordsScene);
    //Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}

void ResultScene::menuStopCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    //reset banker(players) here
    Banker::getInstance()->resetGame();
    
    auto wordsScene = StartScene::createScene();
    Director::getInstance()->replaceScene(wordsScene);
    //Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
}