//
//  WordsScene.h
//  HelloWorldDemo
//
//  Created by greatlzc on 12/16/14.
//
//

#ifndef __HelloWorldDemo__WordsSceneDefine__
#define __HelloWorldDemo__WordsSceneDefine__

#include <cocos2d.h>

class WordsSceneDefine : public cocos2d::LayerColor, public cocos2d::TextFieldDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuStartCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WordsSceneDefine);
    
    virtual bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF *sender) override;
    
    virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF *sender) override;
    
    virtual bool onTextFieldInsertText(cocos2d::TextFieldTTF *sender, const char *text, size_t nLen) override;
    
    virtual bool onTextFieldDeleteBackward(cocos2d::TextFieldTTF *sender, const char *delText, size_t nLen)
    override;
    
    virtual bool onVisit(cocos2d::TextFieldTTF *sender, cocos2d::Renderer *renderer,
                         cocos2d::Mat4 const &transform, uint32_t flags) override;
    
    void textFieldPressed(Ref* pSender, int index);
};

#define NO_GUY_INPUT 1
#define NO_SPY_INPUT 2

#endif /* defined(__HelloWorldDemo__WordsScene__) */
