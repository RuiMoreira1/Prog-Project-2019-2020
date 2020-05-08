#include <iostream>
#include <vector>
#include "board.h"
using namespace std;



void Board::word_insert_horizontal_2(){
    int length = input_Word.size(), k = 0;
    input_Word += "!"; // when k+1 is called if k == last char k+1 == ! so it doesn't get an error
    vector<tuple<int,int,char>> reserve; bool insert = true;
    if(column_coord+length > columns + 1){
        cout << "Word doesn't fit inside the board" << endl; insert = false;
    }
    else if(storage[row_coord][column_coord-1] != '0' && column_coord-1 != 0){
        cout << "NEW FLAG" << endl; insert = false;
    }
    else{
        for(int i = column_coord; i < (column_coord+length); i++) {
            if (storage[row_coord][i] == input_Word[k]) { // Converting to string input_word[k] = &char
                cout << "WORKING SAME LETTER" << endl;
                reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
            }

            else if(row_coord == 1){
                if( (i == columns) && (storage[row_coord+1][i] == '0') ){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k]));
                }
                else if( (i == 1) && (storage[row_coord+1][i] == '0')){
                    if(storage[row_coord][i+1] == '0' || storage[row_coord][i+1] == input_Word[k+1]){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else {
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if(storage[row_coord+1][i] == '0'){
                    if( (storage[row_coord][i+1] == '0') || (storage[row_coord][i+1] == input_Word[k+1])){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                }
                else{
                    cout << "NOT WORKING" << endl; insert = false; break;
                }
            }

            else if(row_coord == rows){
                if( (i == 1) && (storage[row_coord-1][i] == '0')){
                    if( (storage[row_coord][i+1] == '0') || (storage[row_coord][i+1] == input_Word[k+1])){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if( (i == columns) && (storage[row_coord-1][i] == '0') ){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k]));
                }
                else if( storage[row_coord-1][i] == '0'){
                    if( (storage[row_coord][i+1] == '0') || (storage[row_coord][i+1] == input_Word[k+1]) ){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else{
                    cout << "NOT WORKING" << endl; insert = false; break;
                }
            }

            else{
                if( (i == columns) && (storage[row_coord+1][i] == '0') && (storage[row_coord-1][i] == '0') ){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i, input_Word[k]));
                }
                else if ( (i == 1) && storage[row_coord-1][i] == '0'){
                    if( (storage[row_coord][i+1] == '0') || (storage[row_coord][i+1] == input_Word[k+1])){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if( (storage[row_coord+1][i] == '0') && (storage[row_coord-1][i] == '0')){
                    if( (storage[row_coord][i+1] == '0') || (storage[row_coord][i+1] == input_Word[k+1]) ){
                        cout << "Working" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else{
                    cout << "NOT WORKING" << endl; insert = false; break;
                }
            }


            }

        }
    if(insert){
        for(auto &it : reserve){
            storage[get<0>(it)][get<1>(it)] = get<2>(it);
        }
        input_Word.pop_back();
        insert_to_file();
    }

}






void Board::word_insert_vertical_2(){
    int length = input_Word.size(), k = 0;
    input_Word += "!";
    vector<tuple<int,int,char>> reserve; bool insert = true; //reverse -> if the word can´t be written but meanwhile some spaces changed, restore the board
    if(row_coord+length > rows +1){
        cout << "Word doesn't fit inside the board" << endl; insert = false;
    }
    else if(storage[row_coord-1][column_coord] != '0' && row_coord-1 != 0){
        cout << "NEW FLAG" << endl; insert = false;
    }
    else {
        for (int i = row_coord; i < (row_coord + length); i++) {
            if (storage[i][column_coord] == input_Word[k]) {
                cout << "WORKING" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
            }
            else if(column_coord == 1){
                if(i == rows && storage[i][column_coord+1] == '0'){
                    cout << "Working" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                }
                else if(i == 1 && storage[i][column_coord] == '0'){
                    if(storage[i+1][column_coord] == '0' || storage[i+1][column_coord] == input_Word[k+1]){
                        cout << "Working" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if(storage[i][column_coord+1] == '0'){
                    if(storage[i+1][column_coord] == '0' || storage[i+1][column_coord] == input_Word[k+1]){
                        cout << "Working" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else{
                    cout << "NOT WORKING" << endl; insert = false; break;
                }
            }
            else if(column_coord == columns){
                if( (i == rows) && storage[i][column_coord-1] == '0'){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++; insert = true;
                }
                else if(storage[i][column_coord-1] == '0'){
                    if(storage[i+1][column_coord] == '0' || storage[i+1][column_coord] == input_Word[k+1]){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++; insert = true;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else{
                    cout << "NOT WORKING" << endl; insert = false; break;
                }

            }
            else if(storage[i][column_coord-1] == '0' && storage[i][column_coord+1] == '0') {
                if( i == rows ){
                    if(storage[i][column_coord-1] == '0' && storage[i][column_coord+1] == '0'){
                        cout << "Working" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                    }
                    else{
                        cout << "Not working" << endl; insert = false; break;
                    }
                }
                else if (storage[i + 1][column_coord] == '0' || storage[i + 1][column_coord] == input_Word[k + 1]) {
                    cout << "WORKING" << endl;
                    reserve.emplace_back(make_tuple(i, column_coord, input_Word[k]));
                    k++;
                    insert = true;
                }
                else{
                    cout << "NOT WORKING" << endl; insert = false; break;
                }
            }
            else{
                cout << "NOT WORKING" << endl; insert = false; break;
            }
        }

    }
    if(insert){
       for(auto &it: reserve){
           storage[get<0>(it)][get<1>(it)] = get<2>(it);
       }
       input_Word.pop_back();
       insert_to_file();
    }
}


