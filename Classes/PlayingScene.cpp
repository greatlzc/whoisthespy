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
    auto playingScene = PlayingScene::create();
    playingScene->setTag(NO_PLAYING_SCENE);
    auto forgotScene = ForgotDialog::create();
    forgotScene->setTag(NO_FORGOT_DIALOG);
    auto killScene = KillDialog::create();
    killScene->setTag(NO_KILL_DIALOG);
    
    // add layer as a child to scene
    scene->addChild(playingScene, 1);
    scene->addChild(forgotScene, 2);
    scene->addChild(killScene, 3);
    
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
    auto background = Sprite::create(BGSRC);
    
    // position it on the center of the screen
    background->setPosition(Vec2(WIDTH/2 + ORIGIN_X, HEIGHT/2 + ORIGIN_Y));
    background->setTag(-4);
    this->addChild(background, 0);
    
    TTFConfig menuTitle;
    menuTitle.fontFilePath = "yuweij.ttf";
    menuTitle.fontSize = 60;
    
    auto forgotLabel = Label::createWithTTF(menuTitle, "<看词>");
    forgotLabel->setColor(Color3B::BLACK);
    forgotLabel->setPosition(Vec2(ORIGIN_X + WIDTH/3,
                                  ORIGIN_Y + HEIGHT/7));
    this->addChild(forgotLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(70);
    auto forgotItem = MenuItemFont::create("       ", CC_CALLBACK_1(PlayingScene::OnForgotWord, this));
    
    auto forgotMenu = Menu::create(forgotItem, NULL);
    forgotMenu->setPosition(Vec2(ORIGIN_X + WIDTH/3,
                                 ORIGIN_Y + HEIGHT/7));
    forgotMenu->setTag(-2);
    this->addChild(forgotMenu, 1);
    
    auto killLable = Label::createWithTTF(menuTitle, "<投之>");
    killLable->setColor(Color3B::BLACK);
    killLable->setPosition(Vec2(ORIGIN_X + WIDTH*2/3,
                                 ORIGIN_Y + HEIGHT/7));
    this->addChild(killLable, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(60);
    auto killItem = MenuItemFont::create("       ", CC_CALLBACK_1(PlayingScene::OnKillPlayer, this));
    
    auto killMenu = Menu::create(killItem, NULL);
    killMenu->setPosition(Vec2(ORIGIN_X + WIDTH*2/3,
                                ORIGIN_Y + HEIGHT/7));
    killMenu->setTag(-3);
    this->addChild(killMenu, 1);
    
    //relive all players and dispatch role
    Banker::getInstance()->resetPlayers();
    Banker::getInstance()->shuffle();
    
    auto sample = Label::createWithSystemFont("sample", "Arial", 60);
    auto originX = ORIGIN_X + WIDTH/6;
    auto originY = ORIGIN_Y + HEIGHT/1.4;
    auto marginX = WIDTH/3;
    auto marginY = sample->getContentSize().height*2;
    
    //add players name on screen, 3 colums at most considering the name length
    TTFConfig nameTitle;
    nameTitle.fontFilePath = "yuweij.ttf";
    nameTitle.fontSize = 60;
    int nPlayers = Banker::getInstance()->playerCount();
    for (int i = 0; i < nPlayers; i++)
    {
        auto pName = Banker::getInstance()->mPlayers.at(i)->mName;
        auto pLabel = Label::createWithTTF(nameTitle, pName);
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
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Falcom Sound Team jdk - TRINITY.mp3");
    
    scheduleUpdate();
    return true;
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
    for (Node* node : this->getChildren()) {
        if (node->getTag() < 10) {
            node->setOpacity(150);
        }
    }
    
    auto forgotDialog = (ForgotDialog*)this->getParent()->getChildByTag(NO_FORGOT_DIALOG);
    forgotDialog->OnForgotWord(this);
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
    
    auto killDialog = (KillDialog*)this->getParent()->getChildByTag(NO_KILL_DIALOG);
    killDialog->OnKillPlayer(this);
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
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("Falcom Sound Team jdk - TRINITY.mp3");
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
    forgotLabel = Sprite::create("label.png");
    forgotLabel->setScale(1.5);
    forgotLabel->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    this->addChild(forgotLabel, 1);
    forgotLabel->setVisible(false);
    
    TTFConfig wordTTF;
    wordTTF.fontFilePath = "yuweij.ttf";
    wordTTF.fontSize = 50;
    
    word = Label::createWithTTF(wordTTF, "");
    word->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    word->setColor(Color3B::BLACK);
    this->addChild(word, 2);
    word->setVisible(false);
    
    TTFConfig menuTitle;
    menuTitle.fontFilePath = "yuweij.ttf";
    menuTitle.fontSize = 60;
    info = Label::createWithTTF(menuTitle, "你的关键词是：");
    info->setColor(Color3B::BLACK);
    info->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/1.1));
    this->addChild(info, 2);
    info->setVisible(false);
    
    //forgotten word will show, touch to return
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        Vec2 locationInNode = forgotLabel->convertToNodeSpace(touch->getLocation());
        Size s = forgotLabel->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        word->setVisible(false);
        forgotLabel->setVisible(false);
        info->setVisible(false);
        
        //get the playing scene
        auto playingScene = this->getParent()->getChildByTag(NO_PLAYING_SCENE);
        
        //set opacity back
        for (Node* node : playingScene->getChildren())
        {
            if (node->getTag() < 10)
            {
                node->setOpacity(255);
            }
        }
        
        //remove touch eventlistener when this dialog disappear
        this->_eventDispatcher->removeEventListenersForTarget(this);
        doModal = false;
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    doModal = false;
    
    return true;
}

void ForgotDialog::OnForgotWord(Ref* pSender)
{
    forgotLabel->setVisible(true);
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
        Vec2 locationInNode = forgotLabel->convertToNodeSpace(touch->getLocation());
        Size s = forgotLabel->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        word->setVisible(false);
        forgotLabel->setVisible(false);
        info->setVisible(false);
        
        //get the playing scene
        auto playingScene = this->getParent()->getChildByTag(NO_PLAYING_SCENE);
        
        //set opacity back
        for (Node* node : playingScene->getChildren())
        {
            if (node->getTag() < 10)
            {
                node->setOpacity(255);
            }
        }
        
        //remove touch eventlistener when this dialog disappear
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
    
    TTFConfig infoTTF;
    infoTTF.fontFilePath = "yuweij.ttf";
    infoTTF.fontSize = 48;
    info = Label::createWithTTF(infoTTF, "当前：平民 " + guy + " 人" +
                                     "    " +
                                     "卧底 " + spy + " 人" +
                                     "    " +
                                     "白板 " + lucky + " 人");
    info->setColor(Color3B::BLACK);
    info->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/1.1));
    this->addChild(info, 2);
    info->setVisible(false);
    
    killLabel = Sprite::create("label.png");
    killLabel->setScale(1.5);
    killLabel->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    this->addChild(killLabel, 1);
    killLabel->setVisible(false);
    
    TTFConfig resultTTF;
    resultTTF.fontFilePath = "yuweij.ttf";
    resultTTF.fontSize = 50;
    result = Label::createWithTTF(resultTTF, "");
    
    result->setColor(Color3B::BLACK);
    result->setPosition(Vec2(ORIGIN_X + WIDTH/2, ORIGIN_Y + HEIGHT/2));
    this->addChild(result, 2);
    result->setVisible(false);
    
    //voting result will show, touch to return, this may lead to next scene
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        Vec2 locationInNode = killLabel->convertToNodeSpace(touch->getLocation());
        Size s = killLabel->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        result->setVisible(false);
        killLabel->setVisible(false);
        info->setVisible(false);
        
        //get the playing scene
        auto playing_scene = (PlayingScene*)this->getParent()->getChildByTag(NO_PLAYING_SCENE);
        
        //set opacity back
        for (Node* node : playing_scene->getChildren())
        {
            if (node->getTag() < 10)
            {
                node->setOpacity(255);
            }
        }
        doModal = false;
        if (Banker::getInstance()->GameEnding() != UNDEFINED) {
            playing_scene->isGameEnded = true;
        }
        
        //remove touch eventlistener when this dialog disappear
        this->_eventDispatcher->removeEventListenersForTarget(this);
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    doModal = false;
    
    return true;
}

void KillDialog::OnKillPlayer(Ref* pSender)
{
    killLabel->setVisible(true);
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
        Vec2 locationInNode = killLabel->convertToNodeSpace(touch->getLocation());
        Size s = killLabel->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode) && doModal)
        {
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event * event) {
        result->setVisible(false);
        killLabel->setVisible(false);
        info->setVisible(false);
        
        //get the playing scene
        auto playingScene = this->getParent()->getChildByTag(NO_PLAYING_SCENE);
        
        //set opacity back
        for (Node* node : playingScene->getChildren())
        {
            if (node->getTag() < 10)
            {
                node->setOpacity(255);
            }
        }
        
        doModal = false;
        if (Banker::getInstance()->GameEnding() != UNDEFINED) {
            layer->isGameEnded = true;
        }
        
        //remove touch eventlistener when this dialog disappear
        this->_eventDispatcher->removeEventListenersForTarget(this);
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
