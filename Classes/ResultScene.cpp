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
#include "SimpleAudioEngine.h"
#include "GameUtils.h"

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
   
    TTFConfig menuTitle;
    menuTitle.fontFilePath = "yuweij.ttf";
    menuTitle.fontSize = 56;
    auto startLabel = Label::createWithTTF(menuTitle, "<重来>");
    startLabel->setColor(Color3B::BLACK);
    startLabel->setPosition(Vec2(ORIGIN_X + startLabel->getContentSize().width/2,
                                 ORIGIN_Y + HEIGHT/10));
    this->addChild(startLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(56);
    auto startItem = MenuItemFont::create("      ", CC_CALLBACK_1(ResultScene::menuStartCallback, this));
    
    auto startMenu = Menu::create(startItem, NULL);
    startMenu->setPosition(Vec2(ORIGIN_X + startLabel->getContentSize().width/2,
                           ORIGIN_Y + HEIGHT/10));
    this->addChild(startMenu, 1);
    
    auto stopLabel = Label::createWithTTF(menuTitle, "<返回>");
    stopLabel->setColor(Color3B::BLACK);
    stopLabel->setPosition(Vec2(ORIGIN_X + WIDTH - stopLabel->getContentSize().width/2,
                                 ORIGIN_Y + HEIGHT/10));
    this->addChild(stopLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(56);
    auto stopItem = MenuItemFont::create("      ", CC_CALLBACK_1(ResultScene::menuStopCallback, this));
    
    auto stopMenu = Menu::create(stopItem, NULL);
    stopMenu->setPosition(Vec2(ORIGIN_X + WIDTH - stopLabel->getContentSize().width/2,
                           ORIGIN_Y + HEIGHT/10));
    this->addChild(stopMenu, 1);
    
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
    title.fontSize = 90;
    
    auto resultLabel = Label::createWithTTF(title, "谁赢了？");
    switch (Banker::getInstance()->GameEnding()) {
        case GUY:
            resultLabel->setString("平民赢了！");
            break;
        case SPY:
            resultLabel->setString("卧底赢了！");
            break;
        case LUCKY:
            resultLabel->setString("白板赢了！");
            break;
        default:
            break;
    }
    resultLabel->setColor(Color3B::BLACK);
    resultLabel->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                            ORIGIN_Y + HEIGHT/1.2));
    
    // add the label as a child to this layer
    this->addChild(resultLabel, 1);
    
    // background image
    auto background = Sprite::create(BGSRC);
    
    // position it on the center of the screen
    background->setPosition(Vec2(WIDTH/2 + ORIGIN_X, HEIGHT/2 + ORIGIN_Y));
    this->addChild(background, 0);
    
    Banker::getInstance()->accounting(Banker::getInstance()->GameEnding());
    Banker::getInstance()->rankPlayers();
    
    std::string no1name = "無";
    std::string no2name = "無";
    std::string no3name = "無";
    std::string no4name = "無";
    std::string no5name = "無";
    
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

    TTFConfig rankTTF;
    rankTTF.fontFilePath = "yuweij.ttf";
    rankTTF.fontSize = 64;
    
    auto no1label = Label::createWithTTF(rankTTF, "一 " + no1name);
    auto no2label = Label::createWithTTF(rankTTF, "二 " + no2name);
    auto no3label = Label::createWithTTF(rankTTF, "三 " + no3name);
    auto no4label = Label::createWithTTF(rankTTF, "四 " + no4name);
    auto no5label = Label::createWithTTF(rankTTF, "五 " + no5name);
    
    auto originX = ORIGIN_X + WIDTH/4;
    auto originY = ORIGIN_Y + HEIGHT/1.7;
    auto marginX = WIDTH/2.5;
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
    
    no1label->setColor(Color3B::BLACK);
    no2label->setColor(Color3B::BLACK);
    no3label->setColor(Color3B::BLACK);
    no4label->setColor(Color3B::BLACK);
    no5label->setColor(Color3B::BLACK);
    
    this->addChild(no1label);
    this->addChild(no2label);
    this->addChild(no3label);
    this->addChild(no4label);
    this->addChild(no5label);
    
    auto no1scorelabel = Label::createWithTTF(rankTTF, no1score);
    auto no2scorelabel = Label::createWithTTF(rankTTF, no2score);
    auto no3scorelabel = Label::createWithTTF(rankTTF, no3score);
    auto no4scorelabel = Label::createWithTTF(rankTTF, no4score);
    auto no5scorelabel = Label::createWithTTF(rankTTF, no5score);
    
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
    
    no1scorelabel->setColor(Color3B::BLACK);
    no2scorelabel->setColor(Color3B::BLACK);
    no3scorelabel->setColor(Color3B::BLACK);
    no4scorelabel->setColor(Color3B::BLACK);
    no5scorelabel->setColor(Color3B::BLACK);
    
    this->addChild(no1scorelabel);
    this->addChild(no2scorelabel);
    this->addChild(no3scorelabel);
    this->addChild(no4scorelabel);
    this->addChild(no5scorelabel);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("ending.mp3");
    
    return true;
}


void ResultScene::menuStartCallback(Ref* pSender)
{
    //to do
    auto wordsScene = WordsScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, wordsScene));
}

void ResultScene::menuStopCallback(Ref* pSender)
{
    //reset banker(players) here
    Banker::getInstance()->resetGame();
    
    auto startScene = StartScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, startScene));
}