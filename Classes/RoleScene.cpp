//
//  RoleScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "RoleScene.h"
#include "NameScene.h"
#include "SimpleAudioEngine.h"
#include "GameUtils.h"

USING_NS_CC;

Scene* RoleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RoleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RoleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(36, 44, 60, 255)) )
    {
        return false;
    }

    TTFConfig menuTitle;
    menuTitle.fontFilePath = "yuweij.ttf";
    menuTitle.fontSize = 70;
    auto menuLabel = Label::createWithTTF(menuTitle, "<继续>");
    menuLabel->setColor(Color3B::BLACK);
    menuLabel->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                                 ORIGIN_Y + HEIGHT/8));
    this->addChild(menuLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto startItem = MenuItemFont::create("      ", CC_CALLBACK_1(RoleScene::menuStartCallback, this));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                           ORIGIN_Y + HEIGHT/8));
    this->addChild(menu, 1);
    
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
    title.fontSize = 90;
    auto label = Label::createWithTTF(title, "选择角色及其人数");
    label->setColor(Color3B::BLACK);
    // position the label on the center of the screen
    label->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                            ORIGIN_Y + HEIGHT/1.2));
    
    // add the label as a child to this layer
    //label->setOpacity(0);
    this->addChild(label, 1);
    
    title.fontSize = 76;
    auto guy = Label::createWithTTF(title, "平民:   ");
    guy->setColor(Color3B::BLACK);
    guy->setPosition(Vec2(ORIGIN_X + WIDTH/2.7,
                             ORIGIN_Y + HEIGHT/1.6));
    this->addChild(guy, 1);
    
    auto spy = Label::createWithTTF(title, "卧底:   ");
    spy->setColor(Color3B::BLACK);
    spy->setPosition(Vec2(ORIGIN_X + WIDTH/2.7,
                          ORIGIN_Y + HEIGHT/2.1));
    this->addChild(spy, 1);
    
    auto lucky = Label::createWithTTF(title, "白板:   ");
    lucky->setColor(Color3B::BLACK);
    lucky->setPosition(Vec2(ORIGIN_X + WIDTH/2.7,
                              ORIGIN_Y + HEIGHT/3.1));
    this->addChild(lucky, 1);
    
    //平民 number selector
    MenuItemFont::setFontName("Chalkduster");
    MenuItemFont::setFontSize(80);
    auto c_minus = MenuItemFont::create("<< ", CC_CALLBACK_1(RoleScene::minus, this, GUY));
    c_minus->setColor(Color3B::BLACK);
    auto c_minus_menu = Menu::create(c_minus, NULL);
    c_minus_menu->setPosition(Vec2(guy->getPositionX() + guy->getContentSize().width/2, guy->getPositionY()));
    this->addChild(c_minus_menu, 1);
    
    //default number of 平民
    Banker::getInstance()->numGuy = 2;
    auto c_num = Label::createWithSystemFont("2", "Chalkduster", 80);
    c_num->setColor(Color3B::BLACK);
    c_num->setPosition(Vec2(c_minus_menu->getPositionX() + guy->getContentSize().width/3, guy->getPositionY()));
    c_num->setTag(GUY);
    this->addChild(c_num, 1);
    
    MenuItemFont::setFontName("Chalkduster");
    MenuItemFont::setFontSize(80);
    auto c_add = MenuItemFont::create(" >>", CC_CALLBACK_1(RoleScene::add, this, GUY));
    c_add->setColor(Color3B::BLACK);
    auto c_add_menu = Menu::create(c_add, NULL);
    c_add_menu->setPosition(Vec2(c_num->getPositionX() + guy->getContentSize().width/3, guy->getPositionY()));
    this->addChild(c_add_menu, 1);
    
    //卧底 number selector
    MenuItemFont::setFontName("Chalkduster");
    MenuItemFont::setFontSize(80);
    auto s_minus = MenuItemFont::create("<< ", CC_CALLBACK_1(RoleScene::minus, this, SPY));
    s_minus->setColor(Color3B::BLACK);
    auto s_minus_menu = Menu::create(s_minus, NULL);
    s_minus_menu->setPosition(Vec2(spy->getPositionX() + spy->getContentSize().width/2, spy->getPositionY()));
    this->addChild(s_minus_menu, 1);
    
    //default number of 卧底
    Banker::getInstance()->numSpy = 1;
    auto s_num = Label::createWithSystemFont("1", "Chalkduster", 80);
    s_num->setColor(Color3B::BLACK);
    s_num->setPosition(Vec2(s_minus_menu->getPositionX() + spy->getContentSize().width/3, spy->getPositionY()));
    s_num->setTag(SPY);
    this->addChild(s_num, 1);
    
    MenuItemFont::setFontName("Chalkduster");
    MenuItemFont::setFontSize(80);
    auto s_add = MenuItemFont::create(" >>", CC_CALLBACK_1(RoleScene::add, this, SPY));
    s_add->setColor(Color3B::BLACK);
    auto s_add_menu = Menu::create(s_add, NULL);
    s_add_menu->setPosition(Vec2(s_num->getPositionX() + spy->getContentSize().width/3, spy->getPositionY()));
    this->addChild(s_add_menu, 1);
    
    //白板 number selector
    MenuItemFont::setFontName("Chalkduster");
    MenuItemFont::setFontSize(80);
    auto n_minus = MenuItemFont::create("<< ", CC_CALLBACK_1(RoleScene::minus, this, LUCKY));
    n_minus->setColor(Color3B::BLACK);
    auto n_minus_menu = Menu::create(n_minus, NULL);
    n_minus_menu->setPosition(Vec2(lucky->getPositionX() + lucky->getContentSize().width/2, lucky->getPositionY()));
    this->addChild(n_minus_menu, 1);
    
    auto n_num = Label::createWithSystemFont("0", "Chalkduster", 80);
    n_num->setColor(Color3B::BLACK);
    n_num->setPosition(Vec2(n_minus_menu->getPositionX() + lucky->getContentSize().width/3, lucky->getPositionY()));
    n_num->setTag(LUCKY);
    this->addChild(n_num, 1);
    
    MenuItemFont::setFontName("Chalkduster");
    MenuItemFont::setFontSize(80);
    auto n_add = MenuItemFont::create(" >>", CC_CALLBACK_1(RoleScene::add, this, LUCKY));
    n_add->setColor(Color3B::BLACK);
    auto n_add_menu = Menu::create(n_add, NULL);
    n_add_menu->setPosition(Vec2(n_num->getPositionX() + lucky->getContentSize().width/3, lucky->getPositionY()));
    this->addChild(n_add_menu, 1);
    
    // background image
    auto background = Sprite::create(BGSRC);
    
    // position it on the center of the screen
    background->setPosition(Vec2(WIDTH/2 + ORIGIN_X, HEIGHT/2 + ORIGIN_Y));
    this->addChild(background, 0);
    
    return true;
}


void RoleScene::menuStartCallback(Ref* pSender)
{
    if (Banker::getInstance()->numGuy == 0 || Banker::getInstance()->numSpy == 0)
    {
        return;
    }
    auto nameScene = NameScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, nameScene));
}

void RoleScene::minus(Ref *pSender, ROLE t)
{
    if (t == GUY) {
        Banker::getInstance()->numGuy--;
        if (Banker::getInstance()->numGuy < 0) {
            Banker::getInstance()->numGuy = 0;
            return;
        }
        char number[2];
        sprintf(number, "%d", Banker::getInstance()->numGuy);
        auto num = (Label *)this->getChildByTag(GUY);
        num->setString(number);
    }
    else if (t == SPY) {
        Banker::getInstance()->numSpy--;
        if (Banker::getInstance()->numSpy < 0) {
            Banker::getInstance()->numSpy = 0;
            return;
        }
        char number[2];
        sprintf(number, "%d", Banker::getInstance()->numSpy);
        auto num = (Label *)this->getChildByTag(SPY);
        num->setString(number);
    }
    else {
        Banker::getInstance()->numLucky--;
        if (Banker::getInstance()->numLucky < 0) {
            Banker::getInstance()->numLucky = 0;
            return;
        }
        char number[2];
        sprintf(number, "%d", Banker::getInstance()->numLucky);
        auto num = (Label *)this->getChildByTag(LUCKY);
        num->setString(number);
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-30.mp3");
}

//suppose no more than 10 players
void RoleScene::add(Ref *pSender, ROLE t)
{
    if (t == GUY) {
        Banker::getInstance()->numGuy++;
        if (Banker::getInstance()->numGuy > 9) {
            Banker::getInstance()->numGuy = 9;
            return;
        }
        char number[2];
        sprintf(number, "%d", Banker::getInstance()->numGuy);
        auto num = (Label *)this->getChildByTag(GUY);
        num->setString(number);
    }
    else if (t == SPY) {
        Banker::getInstance()->numSpy++;
        if (Banker::getInstance()->numSpy > 9) {
            Banker::getInstance()->numSpy = 9;
            return;
        }
        char number[2];
        sprintf(number, "%d", Banker::getInstance()->numSpy);
        auto num = (Label *)this->getChildByTag(SPY);
        num->setString(number);
    }
    else {
        Banker::getInstance()->numLucky++;
        if (Banker::getInstance()->numLucky > 9) {
            Banker::getInstance()->numLucky = 9;
            return;
        }
        char number[2];
        sprintf(number, "%d", Banker::getInstance()->numLucky);
        auto num = (Label *)this->getChildByTag(LUCKY);
        num->setString(number);
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-30.mp3");
}