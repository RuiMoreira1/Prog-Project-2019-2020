#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
using namespace std;
typedef string Warnings;



class BOARD {
private:
    vector<string> file_input;                  //Each line of the file, [RAW LINE, CONTAINING WHITESPACES]
    vector<vector<string>> board_input;         // {{STRING},{STRING},{STRING},....} STRING == "row_coord_col_cord", "direction", "word", "whitespace"
    vector<vector<char>> storage, storage_copy;
    vector<string> words, direction;            //WORDS-> WORDS IN THE FILE ||||| DIRECTION -> DIRECTION OF THE WORDS IN THE FILE
    vector<pair<int, int>> coords;              //TO ACCESS ELEMENT coords[i].first 1st element coords[i].second 2nd element
    vector<char> soup;                          //POOL WITH ALL THE CHARS OF THE WORDS IN THE FILE
    char row_board = 65, column_board = 97;     //ASCII CODE OF A and a to put in the board
    int rows{}, columns{};
    friend class Pool;
public:
    explicit BOARD(const Warnings &war);
    bool open_file(const Warnings &war);                     //FILE OPENING
    void split_string();                  //SLICING THE FILE LINES BY WHITESPACES
    void board_input_init();              //INITIALIZING board_input VECTOR WITH THE DESIRED SPACE board_input[number of file lines][4]
    void board_size();                    //LINE 1 OF THE FILE CONTAINS THE BOARD SIZE
    void Build_Board();                   //INITIALIZE THE BOARD MATRIX WITH THE FILE WORDS
    void storage_init();                  //INITIALIZING THE VECTOR WITH THE DESIRED SPACE storage[rows+1][col+1] each char initially == ' '
    void Fill_Cord();                     //FILL CORD 0 with coords using ascii AND ROWS USING ASCII
    void Print_Board() const;             //FUNCTION TO PRINT THE BOARD
    void vectors();
    static Warnings Get_Warnings(int i);
    void matrix_copy();                   //COPY OF STORAGE VECTOR
};
