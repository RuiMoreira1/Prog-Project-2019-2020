#include "board.h"
using namespace std;




int main(){
    Board var;
    var.scan_input_board();
    var.vector_init();
    var.FillCord();
    var.PrintBoard();
    var.read_file();
    while(true){
        var.word_in_vec();
        while(true) {
            var.scan_input_cord();
            if (var.Get_direction()) {
                if(!var.word_insert_horizontal_2())var.Error();
                else break;
            }
            else{
                if(!var.word_insert_vertical_2()) var.Error();
                else break;
            }
        }
        var.PrintBoard();
        if(Board::end()) break;
    }

    var.ending_file();

}
