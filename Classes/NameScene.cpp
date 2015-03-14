//
//  NameScene.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#include "NameScene.h"
#include "WordsScene.h"
#include "Banker.h"
#include "SimpleAudioEngine.h"
#include "GameUtils.h"

USING_NS_CC;

Scene* NameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (  !LayerColor::initWithColor(Color4B(36, 44, 60, 255))  )
    {
        return false;
    }
    
    TTFConfig title;
    title.fontFilePath = "yuweij.ttf";
    title.fontSize = 70;
    auto menuLabel = Label::createWithTTF(title, "<继续>");
    menuLabel->setColor(Color3B::BLACK);
    menuLabel->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                                 ORIGIN_Y + HEIGHT/5));
    this->addChild(menuLabel, 2);
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto startItem = MenuItemFont::create("      ", CC_CALLBACK_1(NameScene::menuStartCallback, this));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                           ORIGIN_Y + HEIGHT/5));
    this->addChild(menu, 1);
    
    title.fontSize = 90;
    auto label = Label::createWithTTF(title, "依次输入姓名");
    label->setColor(Color3B::BLACK);
    label->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                            ORIGIN_Y + HEIGHT/1.3));
    label->setTag(NO_TITLE);
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    TextFieldTTF* input = TextFieldTTF::textFieldWithPlaceHolder("{ 点击此处输入 }", "Menlo", 70);
    input->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                           ORIGIN_Y + HEIGHT/2));
    input->setColor(Color3B::BLACK);
    input->setColorSpaceHolder(Color3B::BLACK);
    input->setTag(NO_INPUT_AREA);
    input->setDelegate(this);
    this->addChild(input, 2);
    
    //an invisible menu for the textfield
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(80);
    auto blank = MenuItemFont::create("                          ", CC_CALLBACK_1(NameScene::textFieldPressed, this));
    auto blankMenu = Menu::create(blank, NULL);
    blankMenu->setPosition(Vec2(ORIGIN_X + WIDTH/2,
                                 ORIGIN_Y + HEIGHT/2));
    this->addChild(blankMenu);
    
    // background image
    auto background = Sprite::create(BGSRC);
    
    // position it on the center of the screen
    background->setPosition(Vec2(WIDTH/2 + ORIGIN_X, HEIGHT/2 + ORIGIN_Y));
    this->addChild(background, 0);
    
    scheduleUpdate();
    return true;
}


void NameScene::menuStartCallback(Ref* pSender)
{
    int remain = Banker::getInstance()->numSpy +
    Banker::getInstance()->numGuy +
    Banker::getInstance()->numLucky -
    Banker::getInstance()->playerCount();
    
    if (remain != 0) {
        return;
    }
    
    auto wordsScene = WordsScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-28.wav");
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(1.2, wordsScene));
}

bool NameScene::onTextFieldAttachWithIME(TextFieldTTF *sender)
{
    if (Banker::getInstance()->isPlayersFull()) {
        return true;
    }
    //move away from the virtula keyboard
    this->setPosition(Vec2(0, 150));
    return TextFieldDelegate::onTextFieldAttachWithIME(sender);
}

bool NameScene::onTextFieldDetachWithIME(TextFieldTTF* sender)
{
    //move back
    this->setPosition(Vec2(0, 0));
    
    auto text = (TextFieldTTF*)this->getChildByTag(NO_INPUT_AREA);
    if (text->getString().find(" ") != std::string::npos) {
        auto text = (Label*)this->getChildByTag(1);
        text->setString("输入错误，名字不能包含空格");
        return false;
    }
    if (text->getString() == "") {
        auto text = (Label*)this->getChildByTag(NO_TITLE);
        text->setString("输入错误，名字不能为空");
        return false;
    }
    Player* newPlayer = new Player(text->getString());
    Banker::getInstance()->addPlayer(newPlayer);
    
    text->setString("");
    return TextFieldDelegate::onTextFieldDetachWithIME(sender);
}

void NameScene::textFieldPressed(Ref* pSender)
{
    auto text = (TextFieldTTF*)this->getChildByTag(NO_INPUT_AREA);
    text->attachWithIME();
}

bool NameScene::onTextFieldInsertText(TextFieldTTF *sender, const char *text, size_t nLen) {
    return TextFieldDelegate::onTextFieldInsertText(sender, text, nLen);
}

bool NameScene::onTextFieldDeleteBackward(TextFieldTTF *sender, const char *delText, size_t nLen) {
    return TextFieldDelegate::onTextFieldDeleteBackward(sender, delText, nLen);
}

bool NameScene::onVisit(TextFieldTTF *sender, Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    return TextFieldDelegate::onVisit(sender, renderer, transform, flags);
}

void NameScene::update(float dt)
{
    int remain = Banker::getInstance()->numSpy +
    Banker::getInstance()->numGuy +
    Banker::getInstance()->numLucky -
    Banker::getInstance()->playerCount();
    
    auto label = (Label*)this->getChildByTag(NO_TITLE);
    auto input = (TextFieldTTF*)this->getChildByTag(NO_INPUT_AREA);
    if (remain && 0 != Banker::getInstance()->playerCount()) {
        if (label->getString() == "输入错误，名字不能包含空格" &&
            input->getString().find(" ") != std::string::npos)
        {
            return;
        }
        std::stringstream ss;
        ss<<"尚需输入 "<<remain<<" 个";
        label->setString(ss.str().c_str());
    }
    else if (remain == 0) {
        label->setString("输入完成");
        input->setString(" ");
    }
}