//
//  Banker.cpp
//  HelloWorldDemo
//
//  Created by greatlzc on 12/17/14.
//
//

#include "Banker.h"
//#include <math.h>

Banker* Banker::mBanker = NULL;

Banker::Banker()
{
    numGuy = 0;
    numLucky = 0;
    numSpy = 0;
    srand(unsigned(time(0)));
}

Banker* Banker::getInstance()
{
    if (mBanker == NULL) {
        mBanker = new Banker();
    }
    return mBanker;
}

//dispatch role to each player
void Banker::shuffle()
{
    int nSpy = numSpy, nGuy = numGuy, nLucky = numLucky;
    int nPlayers = nSpy + nLucky + nGuy;
    int num = nPlayers;
    std::vector<int> array;
    
    for (int i = 0; i < nPlayers; i++) {
        array.push_back(i);
    }
    
    for (int i = 0; i < num; i++, nPlayers--) {
        int r = rand()%nPlayers;
        if (nLucky-- > 0) {
            mPlayers.at(array[r])->mRole = LUCKY;
        }
        else if (nSpy-- > 0) {
            mPlayers.at(array[r])->mRole = SPY;
        }
        else {
            mPlayers.at(array[r])->mRole = GUY;
        }
        array.erase(array.begin() + r);
    }
}

// return UNDEFINED means not ended else return winning role
ROLE Banker::GameEnding()
{
    ROLE ret = UNDEFINED;
    int livingGuy = 0;
    int livingSpy = 0;
    int livingLucky = 0;
    int livingPlayer = 0;
    for (Player* p : mPlayers)
    {
        if (p->mRole == GUY && p->isDead == false) {
            livingGuy++;
        }
        else if (p->mRole == SPY && p->isDead == false) {
            livingSpy++;
        }
        else if (p->mRole == LUCKY && p->isDead == false) {
            livingLucky++;
        }
    }
    livingPlayer = livingGuy + livingSpy + livingLucky;
    if (livingPlayer == livingGuy) {
        ret = GUY;
    }
    else if (livingPlayer == livingSpy) {
        ret = SPY;
    }
    else if (livingPlayer == livingLucky) {
        ret = LUCKY;
    }
    if (livingPlayer == 2 && livingLucky > 0) {
        ret = LUCKY;
    }
    return ret;
}

void Banker::accounting(ROLE winRole)
{
    for (Player* p : mPlayers) {
        if (p->mRole == winRole) {
            p->mScore++;
        }
    }
}

//restart game
void Banker::resetPlayers()
{
    for (Player* p : mPlayers)
    {
        p->isDead = false;
    }
}

//reset game
void Banker::resetGame()
{
    mPlayers.clear();
    numGuy = 0;
    numSpy = 0;
    numLucky = 0;
}

void Banker::addPlayer(Player* p)
{
    if (p != NULL) {
        for (Player* player : mPlayers)
        {
            if (p->mName == player->mName) {
                return;
            }
        }
        mPlayers.push_back(p);
    }
}

//void Banker::removePlayer(std::string name)
//{
//    for (auto it = mPlayers.begin(); it != mPlayers.end(); it++) {
//        if ((*it)->mName == name) {
//            mPlayers.erase(it);
//        }
//    }
//}

std::string Banker::getWordbyName(std::string name)
{
    std::string ret = "白板";
    for (auto it = mPlayers.begin(); it != mPlayers.end(); it++) {
        if ((*it)->mName == name) {
            if ((*it)->mRole == GUY)
            {
                ret = mWords.gWord;
            }
            else if ((*it)->mRole == SPY)
            {
                ret = mWords.sWord;
            }
        }
    }
    return ret;
}

ROLE Banker::getRolebyName(std::string name)
{
    ROLE ret = UNDEFINED;
    for (auto it = mPlayers.begin(); it != mPlayers.end(); it++) {
        if ((*it)->mName == name) {
            ret = (*it)->mRole;
        }
    }
    return ret;
}

bool Banker::isPlayersFull()
{
    return mPlayers.size() == (numGuy + numLucky + numSpy);
}

int Banker::playerCount()
{
    return (int)mPlayers.size();
}

//rank players by score descent
void Banker::rankPlayers()
{
    std::sort(mPlayers.begin(), mPlayers.end(), [](Player* p1, Player* p2) -> bool{ return p1->mScore > p2->mScore; });
}

void Banker::setWords(Words w)
{
    mWords.gWord = w.gWord;
    mWords.sWord = w.sWord;
}

Words Banker::getWords()
{
    return Words(mWords.gWord, mWords.sWord);
}

int Banker::livingGuyCount()
{
    int ret = 0;
    for (Player* p : mPlayers) {
        if (p->mRole == GUY && p->isDead == false) {
            ret++;
        }
    }
    return ret;
}

int Banker::livingSpyCount()
{
    int ret = 0;
    for (Player* p : mPlayers) {
        if (p->mRole == SPY && p->isDead == false) {
            ret++;
        }
    }
    return ret;
}

int Banker::livingLuckyCount()
{
    int ret = 0;
    for (Player* p : mPlayers) {
        if (p->mRole == LUCKY && p->isDead == false) {
            ret++;
        }
    }
    return ret;
}