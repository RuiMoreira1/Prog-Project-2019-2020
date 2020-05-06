#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <locale>
using namespace std;

class Board {
private:
    int rows, columns, row_coord, column_coord;
    vector<vector<char>> storage;
    vector<string> dictionary;
    vector<tuple<int,int,string,string>> to_file; // <row_coord,column_coord,word,direction>
    string direction, input_Word;
    char row_board, column_board;
public:
    void scan_input_board(); // Input board size
    Board() {
        rows = 0; columns = 0;
        row_coord = 0; column_coord = 0;
        row_board = 65; column_board = 97;
        direction = "", input_Word = "";
    }
    void vector_init(); //Initialize the vector that holds the matrix
    void FillCord();  //Fills the first column and row with "coordinates"
    void PrintBoard() const; //Prints the Board
    void read_file();
    void scan_input_cord();
    void word_in_vec();
    void insert_to_file();
    void word_insert_horizontal_2();
    void ending_file();
    void word_insert_vertical_2();
    void print_file();
    bool direct();
    static bool end();
};
