//
//  RoleScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "RoleScene.h"
#include "NameScene.h"

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto startItem = MenuItemImage::create(
                                           "play 2.png",
                                           "play2 2.png",
                                           CC_CALLBACK_1(RoleScene::menuStartCallback, this));
    startItem->setScale(0.6);
    startItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height/6));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    TTFConfig title;
    title.fontFilePath = "Abberancy.ttf";
    title.fontSize = 90;
    auto label = Label::createWithTTF(title, "Number the Roles:");
    label->setColor(Color3B::YELLOW);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.2));
    
    // add the label as a child to this layer
    //label->setOpacity(0);
    this->addChild(label, 1);
    
    // add "StartScene" splash screen"
//    auto sprite = Sprite::create("sky.jpg");
//    
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    auto guy = Label::create("平民：", "Arial", 70);
    guy->setPosition(Vec2(origin.x + visibleSize.width/2.5,
                             origin.y + visibleSize.height/1.5));
    this->addChild(guy, 1);
    
    auto spy = Label::create("卧底：", "Arial", 70);
    spy->setPosition(Vec2(origin.x + visibleSize.width/2.5,
                          origin.y + visibleSize.height/2));
    this->addChild(spy, 1);
    
    auto lucky = Label::create("白板：", "Arial", 70);
    lucky->setPosition(Vec2(origin.x + visibleSize.width/2.5,
                              origin.y + visibleSize.height/3));
    this->addChild(lucky, 1);
    
    //平民 number selector
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto c_minus = MenuItemFont::create("<", CC_CALLBACK_1(RoleScene::minus, this, GUY));
    auto c_minus_menu = Menu::create(c_minus, NULL);
    c_minus_menu->setPosition(Vec2(guy->getPositionX() + guy->getContentSize().width/2, guy->getPositionY()));
    this->addChild(c_minus_menu, 1);
    
    auto c_num = Label::create("0", "Arial", 80);
    c_num->setPosition(Vec2(c_minus_menu->getPositionX() + guy->getContentSize().width/3, guy->getPositionY()));
    c_num->setTag(GUY);
    this->addChild(c_num, 1);
    
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto c_add = MenuItemFont::create(">", CC_CALLBACK_1(RoleScene::add, this, GUY));
    auto c_add_menu = Menu::create(c_add, NULL);
    c_add_menu->setPosition(Vec2(c_num->getPositionX() + guy->getContentSize().width/3, guy->getPositionY()));
    this->addChild(c_add_menu, 1);
    
    //卧底 number selector
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto s_minus = MenuItemFont::create("<", CC_CALLBACK_1(RoleScene::minus, this, SPY));
    auto s_minus_menu = Menu::create(s_minus, NULL);
    s_minus_menu->setPosition(Vec2(spy->getPositionX() + spy->getContentSize().width/2, spy->getPositionY()));
    this->addChild(s_minus_menu, 1);
    
    auto s_num = Label::create("0", "Arial", 80);
    s_num->setPosition(Vec2(s_minus_menu->getPositionX() + spy->getContentSize().width/3, spy->getPositionY()));
    s_num->setTag(SPY);
    this->addChild(s_num, 1);
    
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto s_add = MenuItemFont::create(">", CC_CALLBACK_1(RoleScene::add, this, SPY));
    auto s_add_menu = Menu::create(s_add, NULL);
    s_add_menu->setPosition(Vec2(s_num->getPositionX() + spy->getContentSize().width/3, spy->getPositionY()));
    this->addChild(s_add_menu, 1);
    
    //白板 number selector
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto n_minus = MenuItemFont::create("<", CC_CALLBACK_1(RoleScene::minus, this, LUCKY));
    auto n_minus_menu = Menu::create(n_minus, NULL);
    n_minus_menu->setPosition(Vec2(lucky->getPositionX() + lucky->getContentSize().width/2, lucky->getPositionY()));
    this->addChild(n_minus_menu, 1);
    
    auto n_num = Label::create("0", "Arial", 80);
    n_num->setPosition(Vec2(n_minus_menu->getPositionX() + lucky->getContentSize().width/3, lucky->getPositionY()));
    n_num->setTag(LUCKY);
    this->addChild(n_num, 1);
    
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto n_add = MenuItemFont::create(">", CC_CALLBACK_1(RoleScene::add, this, LUCKY));
    auto n_add_menu = Menu::create(n_add, NULL);
    n_add_menu->setPosition(Vec2(n_num->getPositionX() + lucky->getContentSize().width/3, lucky->getPositionY()));
    this->addChild(n_add_menu, 1);
    
    return true;
}


void RoleScene::menuStartCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    if (Banker::getInstance()->numGuy == 0 || Banker::getInstance()->numSpy == 0)
    {
        return;
    }
    auto nameScene = NameScene::createScene();
    Director::getInstance()->replaceScene(nameScene);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //exit(0);
#endif
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
}