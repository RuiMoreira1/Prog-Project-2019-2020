#pragma once
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>  
#include <stdlib.h> 
#include "BOARD.h"
using namespace std;

class Player {
public:
    Player();
    void SetHand(char tile);
    char GetHand(int num) const;
    void SetNum(int description);
    int GetNum() const;
    void SetToken(int points);
    int GetTokens() const;
    int Get_H_Size() const;
    void Remove_from_Hand(int num);
private:
    int token;
    int description;
    vector<char> hand;
};
