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
#include "SimpleAudioEngine.h"
#include "GameUtils.h"

USING_NS_CC;

Scene* PlayingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayingScene::create();
    layer->setTag(1);
    auto forgot = ForgotDialog::create();
    forgot->setTag(2);
    auto kill = KillDialog::create();
    kill->setTag(3);
    // add layer as a child to scene
    scene->addChild(layer, 1);
    scene->addChild(forgot, 2);
    scene->addChild(kill, 3);
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
    
    // background image
    auto sprite = Sprite::create("background.png");
    
    // position it on the center of the screen
    sprite->setPosition(Vec2(WIDTH/2 + ORIGIN_X, HEIGHT/2 + ORIGIN_Y));
    sprite->setTag(-4);
    this->addChild(sprite, 0);
    
    TTFConfig menu_title;
    menu_title.fontFilePath = "yuweij.ttf";
    menu_title.fontSize = 60;
    auto forgot_label = Label::createWithTTF(menu_title, "<看词>");
    forgot_label->setColor(Color3B::BLACK);
    forgot_label->setPosition(Vec2(ORIGIN_X + WIDTH/3,
                                  ORIGIN_Y + HEIGHT/7));
    this->addChild(forgot_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(70);
    auto forgotItem = MenuItemFont::create("       ", CC_CALLBACK_1(PlayingScene::OnForgotWord, this));
    
    auto forgot_menu = Menu::create(forgotItem, NULL);
    forgot_menu->setPosition(Vec2(ORIGIN_X + WIDTH/3,
                                 ORIGIN_Y + HEIGHT/7));
    forgot_menu->setTag(-2);
    this->addChild(forgot_menu, 1);
    
    auto kill_label = Label::createWithTTF(menu_title, "<投之>");
    kill_label->setColor(Color3B::BLACK);
    kill_label->setPosition(Vec2(ORIGIN_X + WIDTH*2/3,
                                 ORIGIN_Y + HEIGHT/7));
    this->addChild(kill_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(60);
    auto killItem = MenuItemFont::create("       ", CC_CALLBACK_1(PlayingScene::OnKillPlayer, this));
    
    auto kill_menu = Menu::create(killItem, NULL);
    kill_menu->setPosition(Vec2(ORIGIN_X + WIDTH*2/3,
                                ORIGIN_Y + HEIGHT/7));
    kill_menu->setTag(-3);
    this->addChild(kill_menu, 1);
    
    //relive all players and dispatch role
    Banker::getInstance()->resetPlayers();
    Banker::getInstance()->shuffle();
    
    auto sample = Label::create("sample", "Arial", 60);
    auto originX = ORIGIN_X + WIDTH/6;
    auto originY = ORIGIN_Y + HEIGHT/1.4;
    auto marginX = WIDTH/3;
    auto marginY = sample->getContentSize().height*2;
    
    //add players name on screen, 3 colums at most considering the name length
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
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
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(66);
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
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Super Mario Bros.mp3");
    
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
    for (Node* n : this->getChildren()) {
        if (n->getTag() < 10) {
            n->setOpacity(150);
        }
    }
    
    auto dialog = (ForgotDialog*)this->getParent()->getChildByTag(2);
    dialog->OnForgotWord(this);
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
    auto name = (Label*)this->getChildByTag(mPlayerSelected);
    name->setColor(Color3B::BLACK);
    auto menu = (Menu*)this->getChildByTag(mPlayerSelected + 10);
    menu->setEnabled(false);
    dead->setPosition(name->getPosition());
    dead->setScale(0.3);
    this->addChild(dead, 3);
    
    for (Node* n : this->getChildren()) {
        if (n->getTag() < 10) {
            n->setOpacity(150);
        }
    }
    
    auto dialog = (KillDialog*)this->getParent()->getChildByTag(3);
    dialog->OnKillPlayer(this);
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
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Super Mario Bros.mp3");
        Director::getInstance()->replaceScene(resultScene);
    }
}

bool ForgotDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    forgot = Sprite::create("forgot.png");
    forgot->setScale(1.5);
    forgot->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    this->addChild(forgot, 1);
    forgot->setVisible(false);
    
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
    title.fontSize = 50;
    
    word = Label::createWithTTF(title, "");
    word->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    word->setColor(Color3B::BLACK);
    this->addChild(word, 2);
    word->setVisible(false);
    
    TTFConfig menu_title;
    menu_title.fontFilePath = "yuweij.ttf";
    menu_title.fontSize = 60;
    info = Label::createWithTTF(menu_title, "你的关键词是：");
    info->setColor(Color3B::BLACK);
    info->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/1.1));
    this->addChild(info, 2);
    info->setVisible(false);
    
    //forgotten word will show, touch to return
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        Vec2 locationInNode = forgot->convertToNodeSpace(touch->getLocation());
        Size s = forgot->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        word->setVisible(false);
        forgot->setVisible(false);
        info->setVisible(false);
        auto layer = this->getParent()->getChildByTag(1);
        for (Node* n : layer->getChildren())
        {
            if (n->getTag() < 10)
            {
                n->setOpacity(255);
            }
        }
        this->_eventDispatcher->removeEventListenersForTarget(this);
        doModal = false;
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    doModal = false;
    
    return true;
}

void ForgotDialog::OnForgotWord(Ref* pSender)
{
    forgot->setVisible(true);
    word->setVisible(true);
    info->setVisible(true);
    auto layer = (PlayingScene*)pSender;
    auto pName = Banker::getInstance()->mPlayers.at(layer->mPlayerSelected)->mName;
    std::string pWord = Banker::getInstance()->getWordbyName(pName);
    word->setString(pWord);
    doModal = true;
    //forgotten word will show, touch to return
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        Vec2 locationInNode = forgot->convertToNodeSpace(touch->getLocation());
        Size s = forgot->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        word->setVisible(false);
        forgot->setVisible(false);
        info->setVisible(false);
        auto layer = this->getParent()->getChildByTag(1);
        for (Node* n : layer->getChildren())
        {
            if (n->getTag() < 10)
            {
                n->setOpacity(255);
            }
        }
        this->_eventDispatcher->removeEventListenersForTarget(this);
        doModal = false;
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool KillDialog::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //a banner, information about living guys
    int livingGuy = Banker::getInstance()->livingGuyCount();
    int livingSpy = Banker::getInstance()->livingSpyCount();
    int livingLucky = Banker::getInstance()->livingLuckyCount();
    std::string guy = std::to_string(livingGuy);
    std::string spy = std::to_string(livingSpy);
    std::string lucky = std::to_string(livingLucky);
    
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
    title.fontSize = 48;
    info = Label::createWithTTF(title, "当前：平民 " + guy + " 人" +
                                     "    " +
                                     "卧底 " + spy + " 人" +
                                     "    " +
                                     "白板 " + lucky + " 人");
    info->setColor(Color3B::BLACK);
    info->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/1.1));
    this->addChild(info, 2);
    info->setVisible(false);
    
    kill = Sprite::create("rank.png");
    kill->setScale(1.5);
    kill->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    this->addChild(kill, 1);
    kill->setVisible(false);
    
    title.fontSize = 50;
    
    result = Label::createWithTTF(title, "");
    
    result->setColor(Color3B::BLACK);
    result->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    this->addChild(result, 2);
    result->setVisible(false);
    
    //voting result will show, touch to return, this may lead to next scene
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        Vec2 locationInNode = kill->convertToNodeSpace(touch->getLocation());
        Size s = kill->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        result->setVisible(false);
        kill->setVisible(false);
        info->setVisible(false);
        auto layer = (PlayingScene*)this->getParent()->getChildByTag(1);
        for (Node* n : layer->getChildren())
        {
            if (n->getTag() < 10)
            {
                n->setOpacity(255);
            }
        }
        doModal = false;
        if (Banker::getInstance()->GameEnding() != UNDEFINED) {
            layer->isGameEnded = true;
        }
        this->_eventDispatcher->removeEventListenersForTarget(this);
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    doModal = false;
    
    return true;
}

void KillDialog::OnKillPlayer(Ref* pSender)
{
    kill->setVisible(true);
    result->setVisible(true);
    info->setVisible(true);
    
    auto layer = (PlayingScene*)pSender;
    
    auto pName = Banker::getInstance()->mPlayers.at(layer->mPlayerSelected)->mName;
    auto pRole = Banker::getInstance()->getRolebyName(pName);
    
    if (pRole == GUY) {
        result->setString("平民冤死");
    }
    else if (pRole == SPY) {
        result->setString("果然是卧底");
    }
    else if (pRole == LUCKY) {
        result->setString("白板再见");
    }
    doModal = true;
    
    int livingGuy = Banker::getInstance()->livingGuyCount();
    int livingSpy = Banker::getInstance()->livingSpyCount();
    int livingLucky = Banker::getInstance()->livingLuckyCount();
    std::string guy = std::to_string(livingGuy);
    std::string spy = std::to_string(livingSpy);
    std::string lucky = std::to_string(livingLucky);
    
    info->setString("当前：平民 " + guy + " 人" +
                    "    " +
                    "卧底 " + spy + " 人" +
                    "    " +
                    "白板 " + lucky + " 人");
    
    //voting result will show, touch to return, this may lead to next scene
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        Vec2 locationInNode = kill->convertToNodeSpace(touch->getLocation());
        Size s = kill->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        result->setVisible(false);
        kill->setVisible(false);
        info->setVisible(false);
        auto layer = (PlayingScene*)this->getParent()->getChildByTag(1);
        for (Node* n : layer->getChildren())
        {
            if (n->getTag() < 10)
            {
                n->setOpacity(255);
            }
        }
        doModal = false;
        if (Banker::getInstance()->GameEnding() != UNDEFINED) {
            layer->isGameEnded = true;
        }
        this->_eventDispatcher->removeEventListenersForTarget(this);
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
