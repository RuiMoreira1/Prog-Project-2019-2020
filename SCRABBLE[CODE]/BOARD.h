#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;



class BOARD {
private:
    vector<string> file_input; //Each line of the file, [RAW LINE, CONTAINING WHITESPACES]
    vector<vector<string>> board_input; // {{STRING},{STRING},{STRING},....} STRING == "row_coord_col_cord", "direction", "word", "whitespace"
    vector<vector<char>> storage, storage_copy;
    vector<string> words, direction; //WORDS-> WORDS IN THE FILE ||||| DIRECTION -> DIRECTION OF THE WORDS IN THE FILE
    vector<pair<int,int>> coords; //TO ACCESS ELEMENT coords[i].first 1st element coords[i].second 2nd element
    vector<char> soup; //POOL WITH ALL THE CHARS OF THE WORDS IN THE FILE
    char row_board = 65, column_board = 97; //ASCII CODE OF A and a to put in the board
    int rows,columns;
public:
    BOARD(){
        rows = 0; columns = 0;
    }
    void open_file();                     //FILE OPENING
    void split_string();                  //SLICING THE FILE LINES BY WHITESPACES
    void board_input_init();              //INITIALIZING board_input VECTOR WITH THE DESIRED SPACE board_input[number of file lines][4]
    void test();                          //TEST FUNCTION
    void board_size();                    //LINE 1 OF THE FILE CONTAINS THE BOARD SIZE
    void Build_Board();                   //INITIALIZE THE BOARD MATRIX WITH THE FILE WORDS
    void storage_init();                  //INITIALIZING THE VECTOR WITH THE DESIRED SPACE storage[rows+1][col+1] each char initially == ' '
    void Fill_Cord();                     //FILL CORD 0 with coords using ascii AND ROWS USING ASCII
    void Print_Board() const;             //FUNCTION TO PRINT THE BOARD
    void matrix_copy();                   //COPY OF THE MATRIX TO CHECK WHETHER OR NOT ALTERATIONS HAVE BEEN DONE
    bool complete_word();                 //CHECK WHETHER OR NOT A WORD HAS BEEN COMPLETED
    void vectors();
    void vector_test();
};




