//
//  WordsScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "WordsScene.h"
#include "PlayingScene.h"
#include "WordsSceneDefine.h"
#include "Banker.h"

USING_NS_CC;

Scene* WordsScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WordsScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WordsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (  !LayerColor::initWithColor(Color4B(36, 44, 60, 255))  )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    TTFConfig ttf;
    ttf.fontFilePath = "yuweij.ttf";
    ttf.fontSize = 90;
    auto label = Label::createWithTTF(ttf, "选词模式");
    label->setColor(Color3B::BLACK);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/1.5));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    
    TTFConfig menu_title;
    menu_title.fontFilePath = "yuweij.ttf";
    menu_title.fontSize = 80;
    auto define_label = Label::createWithTTF(menu_title, "|自定义|");
    define_label->setColor(Color3B::BLACK);
    define_label->setPosition(Vec2(label->getPositionX()/2, label->getPositionY()/2));
    this->addChild(define_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto defineItem = MenuItemFont::create("          ", CC_CALLBACK_1(WordsScene::defineCallback, this));
    
    // create menu, it's an autorelease object
    auto define_menu = Menu::create(defineItem, NULL);
    define_menu->setPosition(Vec2(label->getPositionX()/2, label->getPositionY()/2));
    this->addChild(define_menu, 1);
    
    auto default_label = Label::createWithTTF(menu_title, "|随机|");
    default_label->setColor(Color3B::BLACK);
    default_label->setPosition(Vec2(label->getPositionX()/0.66, label->getPositionY()/2));
    this->addChild(default_label, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto defaultItem = MenuItemFont::create("        ", CC_CALLBACK_1(WordsScene::defaultCallback, this));
    
    // create menu, it's an autorelease object
    auto default_menu = Menu::create(defaultItem, NULL);
    default_menu->setPosition(Vec2(label->getPositionX()/0.66, label->getPositionY()/2));
    this->addChild(default_menu, 1);
    
    // background image
    auto sprite = Sprite::create("background.png");
    
    // position it on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}


void WordsScene::defineCallback(Ref* pSender)
{
    auto defineScene = WordsSceneDefine::createScene();
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, defineScene));
}

void WordsScene::defaultCallback(Ref* pSender)
{
    //remove last played words
    WordsManager::getInstance()->removeWord(Banker::getInstance()->getWords());
    
    Banker::getInstance()->setWords(WordsManager::getInstance()->getWordsbyRandom());
    auto playingScene = PlayingScene::createScene();
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, playingScene));
}