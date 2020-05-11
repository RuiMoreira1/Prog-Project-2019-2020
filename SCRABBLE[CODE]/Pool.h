#pragma once
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>  
#include <stdlib.h> 
#include "BOARD.h"
using namespace std;


class Pool {
public:
    Pool();
    void FormPool();
    char GetTiles(int num) const;
    void Form_init_coor();
    int Get_init_coor1(int num) const;
    int Get_init_coor2(int num) const;
    void Form_word();
    string Get_word(int num) const;
    string Get_word_copy(int num) const;
    void Form_direc();
    string Get_direc(int num) const;
    void Form_all_coor();
    int Get_all_coor1(int word, int num) const;
    int Get_all_coor2(int word, int num) const;
    char Give_Tile(int num);
    int Get_Size() const;
    int Get_Size_w() const;
    int Get_w_Size(int num) const;
    void Vector_Copy();
    void Set_to_Hash(int word_n, int letter);
    void Add_to_Pool(char x);
    void Set_All(vector<int> v);
private:
    vector<char> tiles;
    vector<int> ini_coor1;
    vector<int> ini_coor2;
    vector<int> fin_coor1;
    vector<int> fin_coor2;
    vector<string> w;
    vector<string> w_copy;
    vector<string> dire;
    vector<vector<int>> all_coor1;
    vector<vector<int>> all_coor2;
    vector<vector<int>> All_Things;
};
