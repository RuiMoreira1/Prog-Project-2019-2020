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
    void SetHand(char tile); //Da peças a Hand
    char GetHand(int num) const; //Dá return de uma peça da Hnad
    void SetNum(int description); //Dá um numero de numeros
    int GetNum() const; //Dá return un numero
    void SetToken(int points); //Dá tokens a um player
    int GetTokens() const; //Dá return aos tokens de um jogador
    int Get_H_Size() const; //Dá o size da Hand
    void Remove_from_Hand(int num); //Remove da Hand
private:
    int token; //pontos do jogador
    int description; //numero do jogador
    vector<char> hand; //a mão do jogador
};
