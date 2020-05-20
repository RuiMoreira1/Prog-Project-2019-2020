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
    Pool() = default;
    void FormPool(); //Formar as peças necessárias para completar o jogo
    void Form_init_coor(); //Obter as coordenadas iniciais de cada palavra
    void Form_word(); //Obter um vector com as palavras do ficheiro .txt
    string Get_word_copy(int num) const; //Obter a plavra atravês do indice, vector de words copiado e alterado
    void Form_direc(); //Foram o vector com as direções das palavras H ou V
    void Form_all_coor(); //Formar as coordenadas de todas as letras de todas as palavras
    int Get_all_coor1(int word, int num) const; //all_coor[1] = word, coor[1][2] = linha
    int Get_all_coor2(int word, int num) const; //all_coor[1] = word, coor[1][2] = coluna
    char Give_Tile(int num); //Da uma letra random e retira da tiles
    int Get_Size() const; //Da o tamanho do vetor com as peças
    int Get_Size_w() const; //Da o tamanho do vetor words
    int Get_w_Size(int num) const; //Da a length da palavra
    void Vector_Copy(); //Copia o vector
    void Set_to_Hash(int word_n, int letter, string player_coor); //Mete uma letra em # no vector w_copy
    void Add_to_Pool(char x); //Adiciona as tiles
    void Print_Board(); //Print do BOARD
private:
    vector<char> tiles; //Vetor com as peças
    vector<int> ini_coor1; //Coordenadas iniciais com linha
    vector<int> ini_coor2; //Coordenadas iniciais com coluna
    vector<string> w; //Vector de words
    vector<string> w_copy; //Vector de words copia
    vector<string> dire; //Vector com directions
    vector<vector<int>> all_coor1; //Todas as coordenadas atraves de words e linhas
    vector<vector<int>> all_coor2; //Todas as coordenadas atraves de words e colunas
    vector<vector<int>> All_Things;
    BOARD var = BOARD(var.Get_Warnings(0)); //var para iniciar BOARD
};
