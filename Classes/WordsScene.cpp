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
#include "SimpleAudioEngine.h"
#include "GameUtils.h"

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
    
    TTFConfig ttf;
    ttf.fontFilePath = "yuweij.ttf";
    ttf.fontSize = 90;
    auto label = Label::createWithTTF(ttf, "选词模式");
    label->setColor(Color3B::BLACK);
    // position the label on the center of the screen
    label->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                            ORIGIN_Y + HEIGHT/1.5));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    ttf.fontSize = 80;
    auto defineLabel = Label::createWithTTF(ttf, "|自定义|");
    defineLabel->setColor(Color3B::BLACK);
    defineLabel->setPosition(Vec2(label->getPositionX()/2, label->getPositionY()/2));
    this->addChild(defineLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(90);
    auto defineItem = MenuItemFont::create("          ", CC_CALLBACK_1(WordsScene::defineCallback, this));
    
    // create menu, it's an autorelease object
    auto defineMenu = Menu::create(defineItem, NULL);
    defineMenu->setPosition(Vec2(label->getPositionX()/2, label->getPositionY()/2));
    this->addChild(defineMenu, 1);
    
    auto defaultLabel = Label::createWithTTF(ttf, "|随机|");
    defaultLabel->setColor(Color3B::BLACK);
    defaultLabel->setPosition(Vec2(label->getPositionX()/0.66, label->getPositionY()/2));
    this->addChild(defaultLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(90);
    auto defaultItem = MenuItemFont::create("        ", CC_CALLBACK_1(WordsScene::defaultCallback, this));
    
    // create menu, it's an autorelease object
    auto defaultMenu = Menu::create(defaultItem, NULL);
    defaultMenu->setPosition(Vec2(label->getPositionX()/0.66, label->getPositionY()/2));
    this->addChild(defaultMenu, 1);
    
    // background image
    auto background = Sprite::create(BGSRC);
    
    // position it on the center of the screen
    background->setPosition(Vec2(WIDTH/2 + ORIGIN_X, HEIGHT/2 + ORIGIN_Y));
    this->addChild(background, 0);
    
    return true;
}


void WordsScene::defineCallback(Ref* pSender)
{
    auto defineScene = WordsSceneDefine::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, defineScene));
}

void WordsScene::defaultCallback(Ref* pSender)
{
    //remove last played words
    WordsManager::getInstance()->removeWord(Banker::getInstance()->getWords());
    
    Banker::getInstance()->setWords(WordsManager::getInstance()->getWordsbyRandom());
    auto playingScene = PlayingScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, playingScene));
}