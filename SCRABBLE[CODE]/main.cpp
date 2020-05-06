#include "BOARD.h"


using namespace std;


// NOT REAL MAIN JUST TESTING IF THE CREATED FUNCTION WORK!!!
int main() {
    BOARD nice;
    nice.open_file();
    nice.board_input_init();
    nice.split_string();
    nice.test();
    nice.board_size();
    nice.storage_init();
    nice.Fill_Cord();
    nice.Print_Board();
    nice.Build_Board();
    nice.Print_Board();

}
