#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <locale>
#include <windows.h>
#include <map>
using namespace std;
typedef string Warnings;


class Board {
private:
    int rows{}, columns{}, row_coord, column_coord;
    vector<vector<char>> storage;                      //2d vector == board
    map<int,string> dic;                               //map that contains the words in WORDS.txt file
    vector<tuple<int,int,string,string>> to_file;      //<row_coord,column_coord,word,direction>
    string direction, input_Word;
    char row_board, column_board;
public:
    void scan_input_board(const Warnings &warning);                            //Input board size
    explicit Board(const Warnings &warning);                                   //Constructor
    void vector_init();                                                        //Initialize the vector that holds the matrix
    void FillCord();                                                           //Fills the first column and row with "coordinates"
    void PrintBoard() const;                                                   //Prints the Board
    bool read_file(const Warnings &war);                                       //Reads the words in WORDS.txt file
    void scan_input_cord(const Warnings &war, const Warnings &war_d);          //Ask the user for input [DIRECTION/ROW/COLUMN]
    void word_in_vec();                                                        //Checks if the word given by the user is in the WORDS.txt file
    void insert_to_file();                                                     //[COORD/DIRECTION/WORD] -> to file
    bool word_insert_vertical_2(const Warnings &w );                           //Checks if the word fits the board [VERTICAL]
    bool word_insert_horizontal_2(const Warnings &v);                          //Checks if the word fits the board [HORIZONTAL]
    void ending_file(const Warnings &war);                                     //Insert the vector to_file in the file
    bool Get_direction();                                                      //Direction
    void Error();                                                              //The word given by the user doesn't fit the board clear the '!' added in word_insert_*direction*()
    static Warnings Get_warnings(int i);                                       //Vector with bad input warnings
    static bool end();                                                         //Check if the user wants to end the program
};


CREATED BY RUI_MOREIRA
