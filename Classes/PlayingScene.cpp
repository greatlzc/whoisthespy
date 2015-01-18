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
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
//    auto startItem = MenuItemImage::create(
//                                           "play 2.png",
//                                           "play2 2.png",
//                                           CC_CALLBACK_1(PlayingScene::menuStartCallback, this));
//    startItem->setScale(0.6);
//    startItem->setPosition(Vec2(origin.x + visibleSize.width/2,
//                                origin.y + visibleSize.height/3));
//    
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(startItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = LabelTTF::create("游戏中...", "Abduction.ttf", 80);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height/1.5));
//    
//    // add the label as a child to this layer
//    this->addChild(label, 1);
    
    // add "StartScene" splash screen"
    auto sprite = Sprite::create("mainbg.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1.8);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(60);
    auto forgot = MenuItemFont::create("看词", CC_CALLBACK_1(PlayingScene::OnForgotWord, this));
    auto forgot_menu = Menu::create(forgot, NULL);
    forgot_menu->setPosition(Vec2(origin.x + visibleSize.width/3, origin.y + visibleSize.height/7));
    forgot_menu->setTag(-2);    //notice the tag id
    this->addChild(forgot_menu);
    
    auto kill = MenuItemFont::create("投TA", CC_CALLBACK_1(PlayingScene::OnKillPlayer, this));
    auto kill_menu = Menu::create(kill, NULL);
    kill_menu->setPosition(Vec2(origin.x + visibleSize.width*2/3, origin.y + visibleSize.height/7));
    kill_menu->setTag(-3);      //notice the tag id
    this->addChild(kill_menu);
    
    //relive all players and dispatch role
    Banker::getInstance()->resetPlayers();
    Banker::getInstance()->shuffle();
    
    int nGuy = Banker::getInstance()->numGuy;
    int nSpy = Banker::getInstance()->numSpy;
    int nLucky = Banker::getInstance()->numLucky;
    std::string guy = std::to_string(nGuy);
    std::string spy = std::to_string(nSpy);
    std::string lucky = std::to_string(nLucky);
    
    //a banner, information about living guys
    auto info = Label::create("平民（" + guy + "/" + guy + "）" +
                              "    " +
                              "卧底（" + spy + "/" + spy + "）" +
                              "    " +
                              "白板（" + lucky + "/" + lucky + "）", "Arial", 40);
    info->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/1.1));
    info->setTag(-4);
    info->setVisible(false);
    this->addChild(info);
    
    //auto sample = Label::create("sample", "Arial", 60);
    auto originX = origin.x + visibleSize.width/6;
    auto originY = origin.y + visibleSize.height/1.4;
    auto marginX = visibleSize.width/3;
    auto marginY = info->getContentSize().height*2;
    
    int nPlayers = Banker::getInstance()->playerCount();
    //std::vector<Label*> playerLabels;
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(60);
    
    //add players name on screen, 3 colums at most considering the name length
    for (int i = 0; i < nPlayers; i++)
    {
        auto pName = Banker::getInstance()->mPlayers.at(i)->mName;
        auto pLabel = MenuItemFont::create(pName, CC_CALLBACK_1(PlayingScene::OnNameTouched, this, i));
        auto pMenu = Menu::create(pLabel, NULL);
        pMenu->setPosition(Vec2(originX + (i%3)*marginX, originY - (i/3)*marginY));
        pMenu->setTag(i);
        this->addChild(pMenu);
    }
    
    scheduleUpdate();
    return true;
}


void PlayingScene::menuStartCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    auto resultScene = ResultScene::createScene();
    Director::getInstance()->replaceScene(resultScene);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
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
    for (Node* child : this->getChildren())
    {
        child->setOpacity(128);
    }
    
    auto forgot_menu = (Menu*)this->getChildByTag(-2);
    forgot_menu->setEnabled(false);
    auto kill_menu = (Menu*)this->getChildByTag(-3);
    kill_menu->setEnabled(false);
    auto banner = (Label*)this->getChildByTag(-4);
    banner->setOpacity(255);
    banner->setVisible(true);
    
    auto forgotten = Sprite::create("forgot.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    forgotten->setScale(1.5);
    forgotten->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    
    auto pName = Banker::getInstance()->mPlayers.at(mPlayerSelected)->mName;
    std::string pWord = Banker::getInstance()->getWordbyName(pName);
    auto word = Label::create(pWord, "Arial", 50);
    word->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    word->setColor(Color3B::RED);
    this->addChild(word, 2);
    this->addChild(forgotten, 1);

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
                for (Node* child : this->getChildren())
                {
                    child->setOpacity(255);
                }
                banner->setVisible(false);
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
    
    Banker::getInstance()->mPlayers.at(mPlayerSelected)->isDead = true;
    
    auto dead = Sprite::create("dead.png");
    auto name = (Menu*)this->getChildByTag(mPlayerSelected);
    name->setColor(Color3B::WHITE);
    name->setEnabled(false);
    dead->setPosition(name->getPosition());
    dead->setScale(0.75);
    this->addChild(dead);
    
    auto pName = Banker::getInstance()->mPlayers.at(mPlayerSelected)->mName;
    auto pRole = Banker::getInstance()->getRolebyName(pName);
    
    for (Node* child : this->getChildren())
    {
        child->setOpacity(128);
    }
    
    auto forgot_menu = (Menu*)this->getChildByTag(-2);
    forgot_menu->setEnabled(false);
    auto kill_menu = (Menu*)this->getChildByTag(-3);
    kill_menu->setEnabled(false);
    auto banner = (Label*)this->getChildByTag(-4);
    banner->setOpacity(255);
    banner->setVisible(true);
    
    auto resultbg = Sprite::create("rank.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    resultbg->setScale(1.5);
    resultbg->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(resultbg);
    
    auto result = Label::create("死者身份是……", "Arial", 36);
    result->setColor(Color3B::BLACK);
    result->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(result);
    
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
                for (Node* child : this->getChildren())
                {
                    child->setOpacity(255);
                }
                banner->setVisible(false);
                forgot_menu->setEnabled(true);
                kill_menu->setEnabled(true);
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
        result->setString("冤啊~平民死了");
    }
    else if (pRole == SPY) {
        result->setString("果然是卧底！");
    }
    else if (pRole == LUCKY) {
        result->setString("早死早超生……");
    }
}

void PlayingScene::OnNameTouched(Ref* pSender, int seq)
{
    mPlayerSelected = seq;
    int nPlayers = Banker::getInstance()->playerCount();
    
    //keep at most one green name
    for (int i = 0; i < nPlayers; i++) {
        auto menu = (Menu *)this->getChildByTag(i);
        menu->setColor(Color3B::WHITE);
    }
    auto menu = (Menu *)this->getChildByTag(seq);
    menu->setColor(Color3B::GREEN);
}

void PlayingScene::update(float dt)
{
    //check if game is ending every second
    if (isGameEnded) {
        auto resultScene = ResultScene::createScene();
        Director::getInstance()->replaceScene(resultScene);
    }
}