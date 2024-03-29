#include <iostream>
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Player.h"
#include "Pool.h"
using namespace std;

void Translate(vector<int>& v, string g) //Traduz as coordenadas do jogador e traduz em numeros
{
    v.push_back((int)g[0] - 64);
    v.push_back((int)g[1] - 96);
}
void Find_Word(vector<int>& v, vector<int> v2, Pool po) //Com o vector w descofre qual o  indice da palavra
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
bool Valid_Play(vector<int> word, vector<int> coor, Pool po) //Identifica se as coordenadas são validas na palavra
{
    int d = 0;
    vector<int> v;
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
                        d = 1;
                        v.push_back(1);
                        break;
                    }
                }
                if (d == 0)
                {
                    v.push_back(0);
                }
                d = 0;

            }
        }
    }
    for (int u = 0; u < v.size(); u++)
    {
        if (v[u] == 0)
        {
            return true;
        }
    }
    return false;

}
char Letter_Finder(vector<int> v, vector<int> coor, Pool po) //Da return a letra de uma palavra
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
bool Hand_Cheacker(vector<int> v, vector<int> coor, Pool p, Player pr) //Verifica se a Hand tem a letra escolhida
{
    for (int i = 0; i < pr.Get_H_Size(); i++)
    {
        if (pr.GetHand(i) == Letter_Finder(v, coor, p))
        {
            return true;
        }
    }
    return false;
}
bool Check_Coor(vector<int>& word, vector<int> vf, Player p, Pool po) //Check se as coordenadas acertam em letras
{

    if (word.size() == 0)
    {
        return false;
    }
    if (word.size() > 0)
    {
        return true;
    }
}
void Hash_Helper(vector<int> word, vector<int> coor, Pool& po, Player p, string player_coor) //Mete as Coordenadas em hash
{
    for (int i = 0; i < word.size(); i++)
    {
        for (int a = 0; a < po.Get_word_copy(word[i]).length(); a++)
        {
            if (po.Get_all_coor1(word[i], a) == coor[0] && po.Get_all_coor2(word[i], a) == coor[1])
            {
                po.Set_to_Hash(word[i], a, player_coor);
            }
        }
    }
}
void Check_Completion(vector<int> words, Player& p, Pool po) //Ve se a palavra esta completa
{
    for (int i = 0; i < words.size(); i++)
    {
        int flg = 0;
        for (int a = 0; a < po.Get_word_copy(words[i]).length(); a++)
        {
            string temp = po.Get_word_copy(words[i]);
            if (temp[a] != '#')
            {
                flg = 1;
            }
        }
        if (flg == 0)
        {
            p.SetToken(p.GetTokens() + 1);
            cout << "Player " << p.GetNum() << " - " << p.GetTokens() << endl;
        }
    }
}
bool Play_Possibility(Player p, Pool po) //Ve se é possivel jogar com as peças do jogador
{
    vector<char> v;
    for (int i = 0; i < po.Get_Size_w(); i++)
    {
        for (int a = 0; po.Get_word_copy(i).length(); a++)
        {
            string temp;
            temp = po.Get_word_copy(i);
            if (temp[a] != '#')
            {
                v.push_back(temp[a]);
                break;
            }
        }

    }
    cout << endl;
    for (int i = 0; i < p.Get_H_Size(); i++)
    {
        for (int a = 0; a < v.size(); a++)
        {
            if (p.GetHand(i) == v[a])
            {
                return true;
            }
        }

    }
    return false;

}
void Vez(Player& y, Pool& p) //Trata do turno do jogador
{
    if (Play_Possibility(y, p) == false && p.Get_Size() == 0)
    {
        cout << "Turned skipped" << endl;
        return;
    }
    while (Play_Possibility(y, p) == false)
    {
        p.Add_to_Pool(y.GetHand(0));
        y.Remove_from_Hand(0);
        y.SetHand(p.Give_Tile(3));
        cout << "A hand foi mudada" << endl;

    }
    cout << "As pecas do jogador sao:" << endl;
    for (int i = 0; i < y.Get_H_Size(); i++)
    {
        cout << y.GetHand(i) << " ";
    }
    cout << '\n';
    string player_coor; //variavel com as coordenadas do jogador em letras
    vector<int> tranlated; //vetor com as coordenadas traduzidas
    cout << "Onde quer jogar?(linha/coluna) " << endl;
    cin >> player_coor;
    cin.clear();
    cin.ignore(120891, '\n');
    Translate(tranlated, player_coor);
    vector<int> word;
    Find_Word(word, tranlated, p);
    while (!cin || player_coor.length() != 2 || Check_Coor(word, tranlated, y, p) == false || Letter_Finder(word, tranlated, p) == '#' || Valid_Play(word, tranlated, p) == false || Hand_Cheacker(word, tranlated, p, y) != true)
    {
        cout << "Cordenadas invalidas!" << endl;
        cout << "Onde quer jogar?(linha/coluna) " << endl;
        cin >> player_coor;
        tranlated = {};
        Translate(tranlated, player_coor);
        word = {};
        Find_Word(word, tranlated, p);
        cin.clear();
        cin.ignore(120891, '\n');
    }
    if (Valid_Play(word, tranlated, p) == true)
    {
        for (int i = 0; i < y.Get_H_Size(); i++)
        {
            if (Letter_Finder(word, tranlated, p) == y.GetHand(i))
            {
                y.Remove_from_Hand(i);
                break;
            }
        }
        Hash_Helper(word, tranlated, p, y, player_coor);
        Check_Completion(word, y, p);
    }
}
int main()
{
    cout << "Jogo de Scrable Junior:" << endl;
    cout << "Para 2 a 4 jogadores." << endl;
    cout << "Regras:" << endl;
    cout << "Para comecar o jogo tem de indicar a localizacao do ficheiro de construcao do BOARD" << endl;
    cout << "Atraves dos seus turnos, os jogadores tem uma seleção de letras que podem escolher e jogar no tabuleiro" << endl;
    cout << "A letra no tabuleiro pode ser selecionada atraves das suas coordenadas(linhas,colunas). As linhas sao representadas por letras maiusculas" << endl;
    cout << "e as colunas sao representados por letras minusculas." << endl;
    cout << "Palavras so podem ser completadas por ordem e pontos sao atribuidos a quem acabe uma palavra." << endl;
    cout << "O jogo acaba quando todas as letras forem selecionadas, ganha quem tiver mais pontos" << endl;
    Pool po;
    Player p1, p2, p3, p4;
    vector<Player> p = { p1, p2, p3, p4 };
    size_t size;
    po.FormPool();
    po.Form_init_coor();
    po.Form_word();
    po.Form_direc();
    po.Form_all_coor();
    po.Vector_Copy();
    cout << "Quantos jogadores? " << endl;
    cin >> size;
    while (!cin || ((size > 4) || (size < 2)))
    {
        cin.clear();
        cin.ignore(100000, '\n');
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
    for (int i = 0; i < size; i++)
    {
        p[i].SetNum(i + 1);
    }
    int end_con = 0;
    for (int i = 0; i < size; i++)
    {
        end_con = p[i].Get_H_Size() + end_con;
    }
    while (end_con > 0)
    {
        end_con = 0;
        for (int i = 0; i < size; i++)
        {
            int flg = 0;
            cout << "Jogador " << i + 1 << " --------------" << endl;
            po.Print_Board();
            Vez(p[i], po);
            po.Print_Board();
            Vez(p[i], po);
            if (po.Get_Size() >= 2)
            {
                p[i].SetHand(po.Give_Tile(i));
                p[i].SetHand(po.Give_Tile(i));
                flg = 1;
            }
            if (po.Get_Size() >= 1 && flg == 0)
            {
                p[i].SetHand(po.Give_Tile(i));
            }
            end_con = p[i].Get_H_Size() + end_con;
        }


    }
    cout << endl;
    cout << "Score:" << endl;
    cout << "Player:   -     Tokens" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Player " << p[i].GetNum() << "   -    " << p[i].GetTokens() << endl;
    }
    int win = 0;
    for (int i = 0; i < size; i++)
    {
        if (p[i].GetTokens() > p[win].GetTokens())
        {
            win = i;
        }
    }
    cout << "Player " << p[win].GetNum() << " ganhou com " << p[win].GetTokens() << "!" << endl;
    return 0;
}
