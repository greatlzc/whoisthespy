//
//  Words.h
//  HelloWorldDemo
//
//  Created by greatlzc on 12/18/14.
//
//

#ifndef __HelloWorldDemo__Words__
#define __HelloWorldDemo__Words__

#include <cocos2d.h>

struct Words
{
    Words() {}
    Words(std::string g, std::string s) : gWord(g), sWord(s) {}
    std::string gWord;
    std::string sWord;
};

class WordsManager
{
private:
    WordsManager();
    std::vector<Words> mWordsList;
    static WordsManager* wm;
public:
    static WordsManager* getInstance();
    Words getWordsbyRandom();
    Words getWordsbySelect();
    void init();
    void addWord(std::string g, std::string s);
    void removeWord(Words word);
};

#endif /* defined(__HelloWorldDemo__Words__) */
