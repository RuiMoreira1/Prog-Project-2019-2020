#include "Pool.h"


void Pool::Print_Board() {  //Print do Board
    var.Print_Board();
}

void Pool::FormPool() { //Forma a pool com as letras das palavras
    for (int i = 1; i < var.storage.size(); i++) {
        for (int j = 1; j < var.storage[i].size(); j++) {
            if (var.storage[i][j] != ' ') tiles.push_back(var.storage[i][j]);
        }
    }
}
void Pool::Form_init_coor() //Forma as coordenadas iniciais
{
    for (int i = 0; i < var.coords.size(); i++)
    {
        ini_coor1.push_back(var.coords[i].first);
        ini_coor2.push_back(var.coords[i].second);
    }
}
void Pool::Form_word() //Forma o vetor de words
{
    for (int i = 0; i < var.words.size(); i++)
    {
        w.push_back(var.words[i]);
    }
}
string Pool::Get_word_copy(int num) const
{
    return w_copy[num];
}
void Pool::Form_direc() //Form o vector com direçoes
{
    for (int i = 0; i < var.direction.size(); i++)
    {
        dire.push_back(var.direction[i]);
    }
}
void Pool::Vector_Copy() //Form o vector w_copy
{
    for (int i = 0; i < w.size(); i++)
    {
        w_copy.push_back(w[i]);
    }
}
void Pool::Form_all_coor() //Form o vector de todas as coordenadas all_coor1, all_coor2
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
int Pool::Get_all_coor1(int word, int num) const
{
    return all_coor1[word][num];
}
int Pool::Get_all_coor2(int word, int num) const
{
    return all_coor2[word][num];
}
char Pool::Give_Tile(int num) //Usa random para dar uma peça a hand e remove da tiles
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
void Pool::Set_to_Hash(int word_n, int letter, string player_coor)
{
    w_copy[word_n][letter] = '#';
    var.storage_copy[player_coor[0] - 64][player_coor[1] - 96] = '#';
} 
