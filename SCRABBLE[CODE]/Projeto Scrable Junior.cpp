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
};
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
private:
    int token;
    int description;
    vector<char> hand;
};
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
int Pool::Get_all_coor1(int word,  int num) const
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
void Translate(vector<int>& v, string g)
{
    vector<char> ABC = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M','N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    vector<char> abc = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm','n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    for (int i = 0; i < abc.size(); i++)
    {
        if (g[0] == ABC[i])
        {
            v.push_back(i + 1);
        }
    }
    for (int a = 0; a < abc.size(); a++)
    {
        if (g[0] == abc[a])
        {
            v.push_back(a + 1);
        }
    }

}
void Find_Word(vector<int>& v, vector<int> v2, Pool po)
{
    for (int i = 0; i < po.Get_Size_w(); i++)
    {
        for (int a = 0; a < po.Get_w_Size(i); a++)
        {
            if (v2[0] == po.Get_all_coor1(i, a) && v2[1] == po.Get_all_coor2(i, a))
            {
                v.push_back(i);
            }
        }
    }
}
bool Valid_Play(vector<int> word, vector<int> coor, Pool po)
{
    for (int i = 0; i < word.size(); i++)
    {
        for (int a = 0; a < po.Get_word_copy(word[i]).length(); a++)
        {
            if (po.Get_all_coor1(word[i], a) == coor[0] && po.Get_all_coor2(word[i], a) == coor[1])
            {
                string temp = po.Get_word_copy(word[i]);
                if (a == 0)
                {
                    return true;
                }
                for (int x = 0; x < a; x++)
                {
                    if (temp[x] != '#')
                    {
                        return false;
                    }
                }
                return true;
            }
        }
    }
}
char Letter_Finder(vector<int> v,vector<int> coor, Pool po)
{
    char letter;
    int st = 0;
    for (int i = 0; i < v.size(); i++)
    {
        st = 0;
        for (int a = 0; a < po.Get_word_copy(v[i]).length(); a++)
        {
            if (po.Get_all_coor1(v[i], a) == coor[0] && po.Get_all_coor2(v[i], a) == coor[1])
            {
                string temp;
                temp = po.Get_word_copy(v[i]);
                return temp[a];
            }
        }
    }
}
bool Check_Coor(vector<int>& word, vector<int> vf, Player p, Pool po)
{
    Find_Word(word, vf, po);
    if (word.size() == 0)
    {
        return false;
    }
    if (word.size() > 0)
    {
        return true;
    }
}
void Hash_Helper(vector<int> word, vector<int> coor, Pool po)
{
    for (int i = 0; i < word.size(); i++)
    {
        for (int a = 0; a < po.Get_word_copy(word[i]).length(); a++)
        {
            if (po.Get_all_coor1(word[i], a) == coor[0] && po.Get_all_coor2(word[i], a) == coor[1])
            {
                po.Set_to_Hash(word[i], a);
            }
        }
    }
}
void Vez(Player y, Pool p)
{
    cout << "As pecas do jogador são:" << endl;
    for (int i = 0; i < y.Get_H_Size(); i++)
    {
        cout << y.GetHand(i) << " ";
    }
    cout << '\n';
    string player_coor;
    vector<int> tranlated;
    cout << "Onde quer jogar? ";
    cin >> player_coor;
    Translate(tranlated, player_coor);
    vector<int> word;
    while (Check_Coor(word, tranlated, y, p) != true && Letter_Finder(word, tranlated, p) == '#' && Valid_Play(word, tranlated, p) == false)
    {
        cout << "Nao tem essa letra!" << endl;
        cout << "Onde quer jogar? ";
        cin >> player_coor;
    }
    if (Valid_Play(word, tranlated, p) == true)
    {
        Hash_Helper(word, tranlated, p);
    }
    
}
int main()
{
    BOARD nice;
    nice.open_file();
    nice.board_input_init();
    nice.split_string();
    nice.board_size();
    nice.storage_init();
    nice.Fill_Cord();
    nice.Build_Board();
    nice.Print_Board();
    nice.vectors();
    vector<Player> p;
    Pool po;
    Player p1, p2, p3, p4;
    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);
    size_t size;
    po.FormPool();
    po.Form_init_coor();
    po.Form_word();
    po.Form_direc();
    po.Form_all_coor();
    po.Vector_Copy();
    cout << "Quantos jogadores? ";
    cin >> size;
    while (!cin || ((size > 4) || (size < 2)))
    {
        cin.clear();
        cin.ignore(numeric_limits <streamsize>::max(), '\n');
        cout << "Numero errado de jogadores. Tem de ser entre 2 e 4! " << endl;
        cout << "Quantos jogadores? ";
        cin >> size;
    }
    for (int i = 0; i < size; i++)
    {
        for (int a = 0; a < 7; a++)
        {
            if (po.Get_Size() == 0)
            {
                break;
            }
            p[i].SetHand(po.Give_Tile(a));

        }
        cout << endl;
        if (po.Get_Size() == 0)
        {
            break;
        }
    }
    while (po.Get_Size() > 0)
    {



    }
    return 0;
}
