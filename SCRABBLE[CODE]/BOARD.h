#include "BOARD.h"

using namespace std;



//Reading file line by line and inserting each line into a vector, if the file can´t be opened it throws an exception!!!
//TENS DE ALTERAR O PATH DO TEU FICHEIRO !!!!!!!!
void BOARD::open_file() {
    string line;
    try{
        fstream file(R"(C:\Users\ruipe\CLionProjects\PROG[BOARD_BUILDER]\cmake-build-debug\nice.txt)", ios::in);
        if(file.is_open()){
            while(getline(file,line)){
                file_input.push_back(line);
            }
        }
        else throw ios::failure( "Error opening file!\n");
        file.close();
    }
    catch(const exception &ex){
        cerr << ex.what() << endl;
        exit(1);
    }
}

//Initializing the vector according to the right dimensions
void BOARD::board_input_init(){
    board_input.assign(file_input.size(),vector<string>(4," "));
}


//Split the string being the whitespace the "delimiter" char and the insert it to a 2d vector of strings
void BOARD::split_string(){
    int i = 0;
    for(string &str: file_input){
        istringstream ss(str);
        int k = 0;
        while(ss){
            string word;
            ss >> word;
            board_input[i][k] = word;
            k++;
        }
        i++;
    }
}

//TEST FUNCTION [DELETED] WHEN DELIVERING THE PROJECT
void BOARD::test(){
    for(vector<string> &it : board_input){
        cout << it[0] << " " << it[1] << " " << it[2] << " " << endl;
    }
};


//BOARD ROWS AND COLUMNS
void BOARD::board_size(){
    stringstream s(board_input[0][0]);
    s >> rows;
    stringstream s2(board_input[0][2]);
    s2 >> columns;
    cout << board_input[1][2] << endl;

}

//INITIALIZE THE VECTOR FOR THE BOARD
void BOARD::storage_init(){
    storage.assign(rows+1,vector<char>(columns+1,' '));
}

//FILL THE ROW 0 AND COL 0 WITH THE COORDINATES USING ASCII
void BOARD::Fill_Cord(){
    storage[0][0] = '#';
    for(int i = 1; i < columns+1; i++){
        storage[0][i] = column_board;
        column_board += 1;
    }
    for(int k = 1; k < rows+1 ; k++){
        storage[k][0] = row_board;
        row_board += 1;
    }
}

//PRINT THE BOARD NEEDS SOME ALTERATIONS TO PRINT THE LETTER IN DIFFERENT COLOUR IF THE BOARD WAS CHANGED;
void BOARD::Print_Board() const{
    for(int i = 0; i < rows+1; i++){
        if( i != 0)
            cout << "|";
        else cout << " ";
        for(int j = 0; j < columns+1; j++){
            /*if(storage_copy[i][j] == '#'){
                cout << " " << storage[i][j] << " |"; // IF THE LETTER WAS CHANGED PRINT IT IN another colour!!!
            }*/
            cout << " " << storage[i][j] << " |";
        }
        cout << endl;
    }
}


//CREATING THE INITIAL BOARD WITH THE WORDS GIVEN IN THE FILE
void BOARD::Build_Board() {
    for(int i = 1; i < board_input.size();i++){                                 // Starting at one because 0 is the board size
        int init_x = board_input[i][0][0]-64 ,init_y = board_input[i][0][1]-96; // Initial values of the row and the col. string[k] == &char
        if(board_input[i][1] == "H"){                                           // so we decrement the row by the ascii code of A-1 and the col by the
            for(char it: board_input[i][2]){                                    //ascii code of a-1
                storage[init_x][init_y] = it; init_y++; //If the word is horizontal then the matrix should be incremented only in the column section
            }
        }
        else if(board_input[i][1] == "V"){
            for(char it2: board_input[i][2]){
                storage[init_x][init_y] = it2; init_x++; //If the word is vertical then the matrix should be incremented only in the row section
            }
        }
    }
}


//PARA FAZERES FRIEND CLASS E USARES O VETOR EM PRINCIPIO DEVES TER DO ALOCAR PARA ELE NÃO SE PERDER
void BOARD::matrix_copy(){
    storage_copy.assign(storage.begin(),storage.end()); //A copy of the matrix to be able to detected if the letter was changed by the user
                                                                  // and to check whether or not the word has been completed
}

//Check if the a word has been completed
bool BOARD::complete_word(){
    for(int i = 1; i < board_input.size(); i++){
        int count = 0;
        int init_x = board_input[i][0][0]-64 ,init_y = board_input[i][0][1]-96;
        if(board_input[i][1] == "H"){
            for(int j = 0; j < board_input[i][2].size(); j++){
                if(count == board_input[i][2].size()){
                    board_input[i][1] = "D";                    //Change the direction for D so that the word isn't analysed again
                    return true;                                //and doesn't give more points than it should
                }
                if(storage_copy[init_x][init_y] != '#') return false; //If it is different the word hasn't been completed
                count++; init_y++;                              //Increment count and col
            }
        }
        else if(board_input[i][1] == "V"){
            for(int j = 0; j < board_input[i][2].size(); j++){
                if(count == board_input[i][2].size()){
                    board_input[i][1] = "D";                    //Change the direction for D so that the word isn't analysed again
                    return true;                                //and doesn't give more points than it should
                }
                if(storage_copy[init_x][init_y] != '#') return false;  //If it is different the word hasn't been completed
                count++; init_x++;                              //Increment count and col
            }
        }
    }
}


void BOARD::vectors(){
    for(int i = 1; i < board_input.size();i++){
        words.push_back(board_input[i][2]);
        for(char &str: board_input[i][2]){
            soup.push_back(str);
        }
        coords.emplace_back(make_pair(board_input[i][0][0]-64,board_input[i][0][1]-96));
        direction.push_back(board_input[i][1]);
    }
}

