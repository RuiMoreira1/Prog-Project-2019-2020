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
void Player::SetHand(char tile)
{
    hand.push_back(tile);
}
char Player::GetHand(int num) const
{
    return hand[num];
}
void Player::SetNum(int d)
{
    description = d;
}
int Player::GetNum() const
{
    return description;
}
void Player::SetToken(int points)
{
    token = points;
}
int Player::GetTokens() const
{
    return token;
}
int Player::Get_H_Size() const
{
    return hand.size();
}
void Player::Remove_from_Hand(int num)
{
    hand.erase(hand.begin() + num);
}
