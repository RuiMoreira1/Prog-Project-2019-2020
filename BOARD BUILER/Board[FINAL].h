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



class Board {
private:
    int rows, columns, row_coord, column_coord;
    vector<vector<char>> storage;                      //2d vector == board
    map<int,string> dic;                               //map that contains the words in WORDS.txt file
    vector<tuple<int,int,string,string>> to_file;      //<row_coord,column_coord,word,direction>
    string direction, input_Word;                  
    char row_board, column_board;
public:
    void scan_input_board(); // Input board size
    Board() {
        rows = 0; columns = 0;
        row_coord = 0; column_coord = 0;
        row_board = 65; column_board = 97;           //Ascii code for 'A' and 'a'
        direction = "", input_Word = "";
    }
    void vector_init();                //Initialize the vector that holds the matrix
    void FillCord();                   //Fills the first column and row with "coordinates"
    void PrintBoard() const;           //Prints the Board
    void read_file();                  //Reads the words in WORDS.txt file
    void scan_input_cord();            //Ask the user for input [DIRECTION/ROW/COLUMN]
    void word_in_vec();                //Checks if the word given by the user is in the WORDS.txt file
    void insert_to_file();             //[COORD/DIRECTION/WORD] -> to file
    bool word_insert_vertical_2();     //Checks if the word fits the board [VERTICAL]
    bool word_insert_horizontal_2();   //Checks if the word fits the board [HORIZONTAL]
    void ending_file();                //Insert the vector to_file in the file
    bool Get_direction();              //Direction
    void Error();                      //The word given by the user doesn't fit the board clear the '!' added in word_insert_*direction*()
    static bool end();                 //Check if the user wants to end the program
};




