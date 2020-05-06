#include "board.h"
using namespace std;





int main(){
    Board nice;
    nice.scan_input_board();
    nice.vector_init();
    nice.FillCord();
    nice.PrintBoard();
    nice.read_file();
    while(true){
        nice.word_in_vec();
        nice.scan_input_cord();
        if(nice.direct()){
            nice.word_insert_horizontal_2();
        }
        else{
            nice.word_insert_vertical_2();
        }
        nice.PrintBoard();
        if(Board::end()) break;
    }
    nice.print_file();
    nice.ending_file();



}
