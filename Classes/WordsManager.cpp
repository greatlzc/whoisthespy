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
    mWordsList.pop_back();
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
    addWord("汉奸", "内奸");
    addWord("人人网", "校内网");
    addWord("威士忌", "白兰地");
    addWord("松下", "索尼");
    addWord("西域", "西部");
    addWord("卧底", "间谍");
    addWord("宁夏", "甘肃");
    addWord("红烧牛肉面", "香辣牛肉面");
    addWord("纸巾", "手帕");
    addWord("唇膏", "口红");
    addWord("联通", "移动");
    addWord("大白兔", "金丝猴");
    addWord("水泡", "气泡");
    addWord("欧元", "美元");
    addWord("护发素", "洗发露");
    addWord("竹笋", "竹子");
    addWord("十面埋伏", "四面楚歌");
    addWord("电动车", "摩托车");
    addWord("轻轨", "地铁");
    addWord("零花钱", "生活费");
    addWord("情人节", "光棍节");
    addWord("鼠目寸光", "井底之蛙");
    addWord("神雕侠侣", "天龙八部");
    addWord("圆珠笔", "中性笔");
    addWord("裸婚", "闪婚");
    addWord("电梯", "扶梯");
    addWord("草莓", "蓝莓");
    addWord("滑雪", "滑冰");
    addWord("离婚", "失恋");
    addWord("家乡", "故乡");
    addWord("金山毒霸", "卡巴斯基");
    addWord("杭州", "苏州");
    addWord("小品", "话剧");
    addWord("警察", "捕快");
    addWord("老师", "教师");
    addWord("抓狂", "发狂");
    addWord("音乐", "歌曲");
    addWord("结婚", "成亲");
    addWord("荷花", "莲花");
    addWord("五颜六色", "五光十色");
    addWord("薯条", "薯片");
    addWord("百年好合", "白头偕老");
    addWord("学姐", "师姐");
    addWord("矿泉水", "纯净水");
    addWord("桂林米粉", "过桥米线");
    addWord("游泳圈", "救生衣");
    addWord("照相机", "摄影机");
    addWord("快乐大本营", "百变大咖秀");
    addWord("葵花宝典", "辟邪剑谱");
    addWord("冰激凌", "冰淇淋");
    addWord("李秋水", "李莫愁");
    addWord("命中注定", "青梅竹马");
    addWord("手臂", "胳膊");
    addWord("58同城", "赶集网");
    addWord("核桃", "榛子");
    addWord("耳机", "耳麦");
    addWord("健身", "锻炼");
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
            //in case "it" is the last
            break;
        }
    }
}