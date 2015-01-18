//
//  Words.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/18/14.
//
//

#include "WordsManager.h"

WordsManager* WordsManager::wm = NULL;

WordsManager::WordsManager()
{
    
}

WordsManager* WordsManager::getInstance()
{
    if (wm == NULL) {
        wm = new WordsManager();
    }
    return wm;
}

Words WordsManager::getWordsbyRandom()
{
    int it = rand() % mWordsList.size();
    return mWordsList[it];
}

//defined word is put at the last
Words WordsManager::getWordsbySelect()
{
    //auto it = --mWordsList.end();
    auto it = mWordsList.end() - 1;
    return *it;
}

void WordsManager::init()
{
    srand(unsigned(time(0)));
    addWord("周总理", "周恩来");
    addWord("王菲", "那英");
    addWord("元芳", "展昭");
    addWord("古龙", "金庸");
    addWord("若曦", "晴川");
    addWord("保安", "保镖");
    addWord("生菜", "白菜");
    addWord("赵敏", "黄蓉");
    addWord("海狮", "海豚");
    addWord("人妖", "太监");
    addWord("橘子", "橙子");
    addWord("油条", "麻花");
    addWord("魔术师", "魔法师");
    addWord("高富帅", "富二代");
    addWord("双胞胎", "龙凤胎");
    addWord("泡泡糖", "棒棒糖");
    addWord("两小无猜", "青梅竹马");
    addWord("果粒橙", "鲜橙多");
    addWord("刘诗诗", "刘亦菲");
    addWord("森马", "以纯");
    addWord("格格", "公主");
    addWord("松岛枫", "苍井空");
    addWord("飞行员", "宇航员");
    addWord("高富帅", "白富美");
    addWord("香皂", "肥皂");
    addWord("仙人球", "仙人掌");
    addWord("百度", "腾讯");
    addWord("包子", "饺子");
    addWord("班主任", "辅导员");
    addWord("成吉思汗", "努尔哈赤");
    addWord("维多利亚", "伊丽莎白");
    addWord("虫洞", "黑洞");
    addWord("杜牧", "杜甫");
    addWord("天猫", "淘宝");
    addWord("春联", "对联");
    addWord("贝斯", "吉他");
    addWord("双飞", "3P");
    addWord("季风", "信风");
    addWord("火炉", "火炕");
    addWord("潮水", "洪水");
    addWord("华南", "江南");
    addWord("塞外", "塞北");
    addWord("蝙蝠侠", "钢铁侠");
    addWord("跳槽", "辞职");
    addWord("玄武", "朱雀");
    addWord("摩卡", "拿铁");
    addWord("七喜", "雪碧");
    addWord("竹笋", "竹子");
    addWord("一起又看流星雨", "一起来看流星雨");
    addWord("工藤新一", "江户川柯南");
    addWord("丧尸", "僵尸");
    addWord("2B", "SB");
    addWord("汉奸", "内奸");
    addWord("人人网", "校内网");
    addWord("威士忌", "白兰地");
    addWord("松下", "索尼");
}

void WordsManager::addWord(std::string g, std::string s)
{
    Words w(g, s);
    mWordsList.push_back(w);
}

void WordsManager::removeWord(Words word)
{
    for (auto it = mWordsList.begin(); it != mWordsList.end(); it++) {
        if (it->gWord == word.gWord && it->sWord == word.sWord) {
            mWordsList.erase(it);
        }
    }
}