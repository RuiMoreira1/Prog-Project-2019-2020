#include "board.h"



int main(){
    auto *var = new Board(Board::Get_warnings(3));
    var->FillCord();
    var->PrintBoard();
    while(!var->read_file(Board::Get_warnings(4)));                 //If the file can´t be opened it will throw an exception, until the file can be opened
    while(true){
        var->word_in_vec();
        var->scan_input_cord(Board::Get_warnings(0),Board::Get_warnings(2));
        while((var->Get_direction()) ? !var->word_insert_horizontal_2(Board::Get_warnings(1)) : !var->word_insert_vertical_2(Board::Get_warnings(1))) {
            var->scan_input_cord(Board::Get_warnings(0),Board::Get_warnings(2));
            var->Error();                                                                       //If the word doesn't fit the board
        }                                                                                       //preserve the word, and ask for the
        var->PrintBoard();                                                                      //the user input(Direction/Row/Column) again
        if(Board::end()) break;                                                                 //until the insertion of the word is valid
        else continue;
    }
    var->ending_file(Board::Get_warnings(4));
    delete var;
    return 0;
}




//CREATED BY RUI_
