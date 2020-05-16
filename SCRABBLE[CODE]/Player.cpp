#include "Player.h"
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>  
#include <stdlib.h> 
#include "BOARD.h"
using namespace std;


Player::Player()
{

}
void Player::SetHand(char tile) // função para atribuir peças
{
    hand.push_back(tile);
}
char Player::GetHand(int num) const // função para obter a mão do jogador
{
    return hand[num];
}
void Player::SetNum(int d) // função para atribuir o numero do jogador
{
    description = d;
}
int Player::GetNum() const // função para obter o numero do jogador
{
    return description;
}
void Player::SetToken(int points) // função para atribuir os pontos do jogador
{
    token = points;
}
int Player::GetTokens() const // função para obter os pontos do jogador
{
    return token;
}
int Player::Get_H_Size() const // função para obter o tamanho da mão do jogador
{
    return hand.size();
}
void Player::Remove_from_Hand(int num)
{
    hand.erase(hand.begin() + num);
}
