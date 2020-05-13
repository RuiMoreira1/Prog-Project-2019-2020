#include "Pool.h"


Pool::Pool()
{

}
void Pool::init_class() {
    var.open_file();
    var.board_input_init();
    var.split_string();
    var.board_size();
    var.storage_init();
    var.Fill_Cord();
    var.Build_Board();
    var.matrix_copy();
    var.vectors();
    var.Print_Board();
}
void Pool::Print_Board() {
    var.Print_Board();
};
void Pool::FormPool()
{
    for (int i = 0; i < var.soup.size(); i++)
    {
        tiles.push_back(var.soup[i]);
    }
}
char Pool::GetTiles(int num) const
{
    return tiles[num];
}
void Pool::Form_init_coor()
{
    for (int i = 0; i < var.coords.size(); i++)
    {
        ini_coor1.push_back(var.coords[i].first);
        ini_coor2.push_back(var.coords[i].second);
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
    for (int i = 0; i < var.words.size(); i++)
    {
        w.push_back(var.words[i]);
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
    for (int i = 0; i < var.direction.size(); i++)
    {
        dire.push_back(var.direction[i]);
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
void Pool::Set_to_Hash(int word_n, int letter, string player_coor)
{
    w_copy[word_n][letter] = '#';
    var.storage_copy[player_coor[0] - 64][player_coor[1] - 96] = '#';
}
void Pool::Remove_Targeted_Tiles(vector<char> target)
{
    for (int i = 0; i < target.size(); i++)
    {
        for (int a = 0; a < tiles.size(); a++)
        {
            if (tiles[a] == target[i])
            {
                tiles.erase(tiles.begin() + a);
                break;
            }
        }
    }
}
