//
//  PlayingScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "PlayingScene.h"
#include "ResultScene.h"
#include "Banker.h"

USING_NS_CC;

Scene* PlayingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // background image
    auto sprite = Sprite::create("background.png");
    
    // position it on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setTag(-4);
    this->addChild(sprite, 0);
    
    TTFConfig menu_title;
    menu_title.fontFilePath = "yuweij.ttf";
    menu_title.fontSize = 60;
    auto forgot_label = Label::createWithTTF(menu_title, "<看词>");
    forgot_label->setColor(Color3B::BLACK);
    forgot_label->setPosition(Vec2(origin.x + visibleSize.width/3,
                                  origin.y + visibleSize.height/7));
    this->addChild(forgot_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(60);
    auto forgotItem = MenuItemFont::create("       ", CC_CALLBACK_1(PlayingScene::OnForgotWord, this));
    
    auto forgot_menu = Menu::create(forgotItem, NULL);
    forgot_menu->setPosition(Vec2(origin.x + visibleSize.width/3,
                                 origin.y + visibleSize.height/7));
    forgot_menu->setTag(-2);
    this->addChild(forgot_menu, 1);
    
    auto kill_label = Label::createWithTTF(menu_title, "<投之>");
    kill_label->setColor(Color3B::BLACK);
    kill_label->setPosition(Vec2(origin.x + visibleSize.width*2/3,
                                 origin.y + visibleSize.height/7));
    this->addChild(kill_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(60);
    auto killItem = MenuItemFont::create("       ", CC_CALLBACK_1(PlayingScene::OnKillPlayer, this));
    
    auto kill_menu = Menu::create(killItem, NULL);
    kill_menu->setPosition(Vec2(origin.x + visibleSize.width*2/3,
                                origin.y + visibleSize.height/7));
    kill_menu->setTag(-3);
    this->addChild(kill_menu, 1);
    
    //relive all players and dispatch role
    Banker::getInstance()->resetPlayers();
    Banker::getInstance()->shuffle();
    
    auto sample = Label::create("sample", "Arial", 60);
    auto originX = origin.x + visibleSize.width/6;
    auto originY = origin.y + visibleSize.height/1.4;
    auto marginX = visibleSize.width/3;
    auto marginY = sample->getContentSize().height*2;
    
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(60);
    
    //add players name on screen, 3 colums at most considering the name length
    TTFConfig title;
    title.fontFilePath = "FZJingLeiS-R-GB.ttf";
    title.fontSize = 60;
    int nPlayers = Banker::getInstance()->playerCount();
    for (int i = 0; i < nPlayers; i++)
    {
        auto pName = Banker::getInstance()->mPlayers.at(i)->mName;
        auto pLabel = Label::createWithTTF(title, pName);
        pLabel->setColor(Color3B::BLACK);
        pLabel->setPosition(Vec2(originX + (i%3)*marginX, originY - (i/3)*marginY));
        pLabel->setTag(i);
        this->addChild(pLabel, 2);
    }
    for (int i = 0; i < nPlayers; i++)
    {
        auto pName = Banker::getInstance()->mPlayers.at(i)->mName;
        auto pLabel = MenuItemFont::create(pName, CC_CALLBACK_1(PlayingScene::OnNameTouched, this, i));
        auto pMenu = Menu::create(pLabel, NULL);
        //pMenu->setColor(Color3B::WHITE);
        pMenu->setPosition(Vec2(originX + (i%3)*marginX, originY - (i/3)*marginY));
        pMenu->setOpacity(0);
        pMenu->setTag(i + 10);
        this->addChild(pMenu, 1);
    }
    
    scheduleUpdate();
    return true;
}


void PlayingScene::menuStartCallback(Ref* pSender)
{
    auto resultScene = ResultScene::createScene();
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, resultScene));
}

void PlayingScene::OnForgotWord(Ref* pSender)
{
    if (mPlayerSelected < 0) {
        return;
    }
    
    if (Banker::getInstance()->mPlayers.at(mPlayerSelected)->isDead == true) {
        return;
    }
    
    //make background grey
    for (int i = 0; i < Banker::getInstance()->playerCount(); i++)
    {
        auto name = (Label *)this->getChildByTag(i);
        name->setOpacity(128);
    }
    auto forgot_menu = (Menu *)this->getChildByTag(-2);
    auto kill_menu = (Menu *)this->getChildByTag(-3);
    auto background = (Sprite *)this->getChildByTag(-4);
    forgot_menu->setOpacity(128);
    kill_menu->setOpacity(128);
    background->setOpacity(128);
    
    forgot_menu->setEnabled(false);
    kill_menu->setEnabled(false);
    
    auto forgotten = Sprite::create("forgot.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    forgotten->setScale(1.5);
    forgotten->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    
    auto pName = Banker::getInstance()->mPlayers.at(mPlayerSelected)->mName;
    std::string pWord = Banker::getInstance()->getWordbyName(pName);
    
    TTFConfig title;
    title.fontFilePath = "FZJingLeiS-R-GB.ttf";
    title.fontSize = 50;
    
    auto word = Label::createWithTTF(title, pWord);
    word->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    word->setColor(Color3B::BLACK);
    this->addChild(word, 4);
    this->addChild(forgotten, 3);

    //forgotten word will show, touch to return
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) -> bool {
        try {
            Vec2 locationInNode = forgotten->convertToNodeSpace(touch->getLocation());
            Size s = forgotten->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            if (rect.containsPoint(locationInNode)) {
                this->removeChild(word);
                this->removeChild(forgotten);
                for (int i = 0; i < Banker::getInstance()->playerCount(); i++)
                {
                    auto name = (Label *)this->getChildByTag(i);
                    name->setOpacity(255);
                }
                auto forgot_menu = (Menu *)this->getChildByTag(-2);
                auto kill_menu = (Menu *)this->getChildByTag(-3);
                auto background = (Sprite *)this->getChildByTag(-4);
                forgot_menu->setOpacity(255);
                kill_menu->setOpacity(255);
                background->setOpacity(255);
                forgot_menu->setEnabled(true);
                kill_menu->setEnabled(true);
            }
            return true;
        }
        catch(std::bad_cast & err){
            return true;
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, forgotten);
}

void PlayingScene::OnKillPlayer(Ref* pSender)
{
    if (mPlayerSelected < 0) {
        return;
    }
    
    if ( Banker::getInstance()->mPlayers.at(mPlayerSelected)->isDead == true)
        return;
    
    Banker::getInstance()->mPlayers.at(mPlayerSelected)->isDead = true;
    
    auto dead = Sprite::create("dead.png");
    auto name = (Label *)this->getChildByTag(mPlayerSelected);
    name->setColor(Color3B::BLACK);
    auto menu = (Menu *)this->getChildByTag(mPlayerSelected + 10);
    menu->setEnabled(false);
    dead->setPosition(name->getPosition());
    dead->setScale(0.75);
    this->addChild(dead);
    
    auto pName = Banker::getInstance()->mPlayers.at(mPlayerSelected)->mName;
    auto pRole = Banker::getInstance()->getRolebyName(pName);
    
    for (int i = 0; i < Banker::getInstance()->playerCount(); i++)
    {
        auto name = (Label *)this->getChildByTag(i);
        name->setOpacity(128);
    }
    auto forgot_menu = (Menu *)this->getChildByTag(-2);
    auto kill_menu = (Menu *)this->getChildByTag(-3);
    auto background = (Sprite *)this->getChildByTag(-4);
    forgot_menu->setOpacity(128);
    kill_menu->setOpacity(128);
    background->setOpacity(128);
    
    forgot_menu->setEnabled(false);
    kill_menu->setEnabled(false);
    
    //a banner, information about living guys
    int nGuy = Banker::getInstance()->numGuy;
    int nSpy = Banker::getInstance()->numSpy;
    int nLucky = Banker::getInstance()->numLucky;
    std::string guy = std::to_string(nGuy);
    std::string spy = std::to_string(nSpy);
    std::string lucky = std::to_string(nLucky);
    int livingGuy = Banker::getInstance()->livingGuyCount();
    int livingSpy = Banker::getInstance()->livingSpyCount();
    int livingLucky = Banker::getInstance()->livingLuckyCount();
    std::string lguy = std::to_string(livingGuy);
    std::string lspy = std::to_string(livingSpy);
    std::string llucky = std::to_string(livingLucky);
    
    TTFConfig title;
    title.fontFilePath = "FZJingLeiS-R-GB.ttf";
    title.fontSize = 40;
    auto info = Label::createWithTTF(title, "平民（" + lguy + "/" + guy + "）" +
                                     "    " +
                                     "卧底（" + lspy + "/" + spy + "）" +
                                     "    " +
                                     "白板（" + llucky + "/" + lucky + "）");
    info->setColor(Color3B::BLACK);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    info->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/1.1));
    this->addChild(info);
    
    auto resultbg = Sprite::create("rank.png");
    resultbg->setScale(1.5);
    resultbg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(resultbg, 3);
    
    auto result = Label::createWithTTF(title, "死者身份是……");
    result->setColor(Color3B::BLACK);
    result->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(result, 4);
    
    //voting result will show, touch to return, this may lead to next scene
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) -> bool {
        try {
            Vec2 locationInNode = resultbg->convertToNodeSpace(touch->getLocation());
            Size s = resultbg->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            if (rect.containsPoint(locationInNode)) {
                this->removeChild(result);
                this->removeChild(resultbg);
                for (int i = 0; i < Banker::getInstance()->playerCount(); i++)
                {
                    auto name = (Label *)this->getChildByTag(i);
                    name->setOpacity(255);
                }
                auto forgot_menu = (Menu *)this->getChildByTag(-2);
                auto kill_menu = (Menu *)this->getChildByTag(-3);
                auto background = (Sprite *)this->getChildByTag(-4);
                forgot_menu->setOpacity(255);
                kill_menu->setOpacity(255);
                background->setOpacity(255);
                forgot_menu->setEnabled(true);
                kill_menu->setEnabled(true);
                this->removeChild(info);
                if (Banker::getInstance()->GameEnding() != UNDEFINED) {
                    isGameEnded = true;
                }
            }
            return true;
        }
        catch(std::bad_cast & err){
            return true;
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, resultbg);
    
    if (pRole == GUY) {
        result->setString("平民冤死");
    }
    else if (pRole == SPY) {
        result->setString("果然是卧底");
    }
    else if (pRole == LUCKY) {
        result->setString("白板走了");
    }
}

void PlayingScene::OnNameTouched(Ref* pSender, int seq)
{
    mPlayerSelected = seq;
    int nPlayers = Banker::getInstance()->playerCount();
    
    //keep at most one green name
    for (int i = 0; i < nPlayers; i++) {
        auto menu = (Label *)this->getChildByTag(i);
        menu->setColor(Color3B::BLACK);
    }
    auto menu = (Label *)this->getChildByTag(seq);
    menu->setColor(Color3B::RED);
    
}

void PlayingScene::update(float dt)
{
    //check if game is ending per second
    if (isGameEnded) {
        auto resultScene = ResultScene::createScene();
        Director::getInstance()->replaceScene(resultScene);
    }
}