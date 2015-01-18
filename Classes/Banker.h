//
//  Banker.h
//  HelloWorldDemo
//
//  Created by greatlzc on 12/17/14.
//
//

#ifndef __HelloWorldDemo__Banker__
#define __HelloWorldDemo__Banker__

#include <cocos2d.h>
#include "Player.h"
#include "WordsManager.h"

class Banker
{
private:
    
    static Banker* mBanker;
    Banker();
    std::vector<Player*> mPlayers;
    Words mWords;
public:
    
    friend class PlayingScene;
    friend class ResultScene;
    static Banker* getInstance();
    void shuffle();
    void addPlayer(Player* p);
    void removePlayer(std::string name);
    bool isPlayersFull();
    std::string getWordbyName(std::string name);
    ROLE getRolebyName(std::string name);
    void setWords(Words w);
    int numGuy;
    int numSpy;
    int numLucky;
    int playerCount();
    void rankPlayers();
    ROLE GameEnding();
    void accounting(ROLE winRole);
    void resetPlayers();
    void resetGame();
    Words getWords();
};

#endif /* defined(__HelloWorldDemo__Banker__) */
