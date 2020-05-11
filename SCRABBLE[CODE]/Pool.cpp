#include "Pool.h"
#include "Player.h"
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>  
#include <stdlib.h> 
#include "BOARD.h"
using namespace std;

Pool::Pool()
{

}
void Pool::FormPool()
{
    BOARD n;
    n.open_file();
    n.board_input_init();
    n.split_string();
    n.board_size();
    n.storage_init();
    n.Fill_Cord();
    n.Build_Board();
    n.vectors();
    for (int i = 0; i < n.soup.size(); i++)
    {
        tiles.push_back(n.soup[i]);
    }
}
char Pool::GetTiles(int num) const
{
    return tiles[num];
}
void Pool::Form_init_coor()
{
    BOARD n;
    n.open_file();
    n.board_input_init();
    n.split_string();
    n.board_size();
    n.storage_init();
    n.Fill_Cord();
    n.Build_Board();
    n.vectors();
    for (int i = 0; i < n.coords.size(); i++)
    {
        ini_coor1.push_back(n.coords[i].first);
        ini_coor2.push_back(n.coords[i].second);
    }
}
int Pool::Get_init_coor1(int num) const
{
    return ini_coor1[num];
}
int Pool::Get_init_coor2(int num) const
{
    return ini_coor2[num];
}
void Pool::Form_word()
{
    BOARD n;
    n.open_file();
    n.board_input_init();
    n.split_string();
    n.board_size();
    n.storage_init();
    n.Fill_Cord();
    n.Build_Board();
    n.vectors();
    for (int i = 0; i < n.words.size(); i++)
    {
        w.push_back(n.words[i]);
    }
}
string Pool::Get_word(int num) const
{
    return w[num];
}
string Pool::Get_word_copy(int num) const
{
    return w_copy[num];
}
void Pool::Form_direc()
{
    BOARD n;
    n.open_file();
    n.board_input_init();
    n.split_string();
    n.board_size();
    n.storage_init();
    n.Fill_Cord();
    n.Build_Board();
    n.vectors();
    for (int i = 0; i < n.direction.size(); i++)
    {
        dire.push_back(n.direction[i]);
    }
}
string Pool::Get_direc(int num) const
{
    return dire[num];
}
void Pool::Vector_Copy()
{
    for (int i = 0; i < w.size(); i++)
    {
        w_copy.push_back(w[i]);
    }
}
void Pool::Form_all_coor()
{
    for (int i = 0; i < w.size(); i++)
    {
        for (int i = 0; i < w.size(); i++)
        {
            if (dire[i] == "V")
            {
                all_coor1.push_back(vector<int>());
                all_coor2.push_back(vector<int>());
                for (int a = 0; a < w[i].length(); a++)
                {
                    all_coor2[i].push_back(ini_coor2[i]);
                    all_coor1[i].push_back(ini_coor1[i] + a);
                }
            }
            if (dire[i] == "H")
            {
                all_coor1.push_back(vector<int>());
                all_coor2.push_back(vector<int>());
                for (int a = 0; a < w[i].length(); a++)
                {
                    all_coor1[i].push_back(ini_coor1[i]);
                    all_coor2[i].push_back(ini_coor2[i] + a);
                }
            }


        }
    }

}
void Pool::Set_All(vector<int> v)
{
    All_Things.push_back(vector<int>());
    All_Things[All_Things.size() - 1].push_back(v[0]);
    All_Things[All_Things.size() - 1].push_back(v[0]);

}
int Pool::Get_all_coor1(int word, int num) const
{
    return all_coor1[word][num];
}
int Pool::Get_all_coor2(int word, int num) const
{
    return all_coor2[word][num];
}
char Pool::Give_Tile(int num)
{
    int rt;
    char temp;
    srand(time(NULL) + num);
    rt = rand() % tiles.size();
    temp = tiles[rt];
    tiles.erase(tiles.begin() + rt);
    return temp;
}
int Pool::Get_Size() const
{
    return tiles.size();
}
void Pool::Add_to_Pool(char x)
{
    tiles.push_back(x);
}
int Pool::Get_Size_w() const
{
    return w.size();
}
int Pool::Get_w_Size(int num) const
{
    return w[num].length();
}
void Pool::Set_to_Hash(int word_n, int letter)
{
    w_copy[word_n][letter] = '#';
}
