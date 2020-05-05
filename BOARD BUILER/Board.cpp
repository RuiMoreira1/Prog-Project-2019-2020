#include "board.h"


//Ask for user input regarding the size of the board
void Board::scan_input_board(){
    cout << "Size of the board? (H x W)" << endl;
    cout << "Enter the Rows" << endl;
    cin >> rows;
    while(!cin || rows > 20 || rows < 0){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout << "Wrong input!!!" << endl; cin >> rows;
    }
    cout << "Enter the Columns" << endl;
    cin >> columns;
    while(!cin || columns > 20 || columns < 0){
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout << "Wrong input!!!" << endl; cin >> columns;
    }
}


//Initialize storage vector
void Board::vector_init(){
    storage.assign(rows+1, vector<char>(columns+1, '0'));
}


//Fill the 1st column and row of board with the coordinates
void Board::FillCord(){
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


//Print the board with the desired area
void Board::PrintBoard() const{
    for(int i = 0; i < rows+1; i++){
        if( i != 0)
            cout << "|";
        else cout << " ";
        for(int j = 0; j < columns+1; j++){
            cout << " " << storage[i][j] << " |";
        }
        cout << endl;
    }
}

void Board::test() {
    cout << rows << endl << column_coord;
}


//Direction of the word input by user
void coord_input(string &dir){
    //cin.ignore(1000,'\n'); // Clean the buffer from cin, so that getline doesn't get an error
    while(true){
        getline(cin,dir,'\n');
        transform(dir.begin(),dir.end(),dir.begin(),::toupper);
        if(dir == "HORIZONTAL" || dir == "VERTICAL") break;
        else{
            cout << "Wrong input, enter horizontal or vertical" << endl;
        }
    }
}


//Coordinates input by user, column and row 65 and 97 are the ascii values of of A and a;
void coord_input(int &x, const int rows_col, const char check = ' ', char tempo = ' '){
    string word;
    int ver;
    if(check == 'c') {
        ver = 97;
        word = "column";}
    else{
        ver = 65;
        word = "row";}
    cout << "Enter a valid " << word << endl;
    cin >> tempo;
    while(true){
        if(tempo > (rows_col-1)+ver || tempo < ver){
            cout << "ERROR!!!\nEnter a valid " << word << endl;
            cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n'); cin >> tempo;
        }
        else {
            x = (tempo-(ver-1));
            break;
        }
    }
}

//Ask me for the user input (direction,row_coord to insert the word,col_coord to insert the word)
void Board::scan_input_cord(){
    cout << "Enter the direction (Horizontal/Vertical)" << endl;
    coord_input(direction);
    cout << direction << endl;
    cout << "Row in UPPERCASE LETTER, Column in LOWERCASE LETTER" << endl;
    coord_input(row_coord,rows,'r');
    cout << row_coord << endl;
    coord_input(column_coord,columns,'c');
    cout << column_coord << endl;
}

//Read file line by line and getting the words into word_storage vector
//The file is opened only once and when checking if the word exists in dictionary only have to go throw the vector
//If the function can´t open the file it will throw an exception
void Board::read_file() {
    string line;
    try {
        fstream file(R"(C:\Users\ruipe\CLionProjects\PROG[BOARD_BUILDER]\WORDS.txt)", ios::in, ios::binary);
        if (file.is_open()) {
            while (getline(file, line)) {
                dictionary.push_back(line);
            }
        }
        else throw ios::failure( "Error opening file!\n");
        file.close();
    }
    catch(const exception &ex) {
        cerr << ex.what() << endl;
        exit(1);
    }
}


//Check if input word is in words.txt vector
bool in_vector(vector<string> &v, const string &word){
    vector<string>::iterator it = find(v.begin(),v.end(),word);
    return it != v.end();
}


//Get the word input from the user and then check if it exists in words.txt
void Board::word_in_vec(){
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    while(true){
        cout << "Enter a valid word to allocate in the board" << endl;
        getline(cin,input_Word);
        transform(input_Word.begin(),input_Word.end(),input_Word.begin(),::tolower);
        if(in_vector(dictionary, input_Word)){
            cout << "Word is in words.txt" << endl; //if word in words.txt vector
            break;
        }

    }
}


//If the word insertion is valid add it to the vector to then output it to the file
void Board::insert_to_file(){
    to_file.emplace_back(make_tuple(row_coord,column_coord,input_Word,direction));
}




//Check whether or not it is possible to insert the word in the desired coordinates (INDENTATION TO HIGH!)
bool invalid_cross_vertical(vector<tuple<int,int,string,string>> &v, int row_c, int col_c, int length, const string word){
    for(auto it = v.begin(); it != v.end(); it++){
        /*if(word == get<2>(*it)){                          //Avoiding duplicates in the board
            cout << "Duplicate" << endl;
            return false;
        }*/
        if(get<3>(*it) == "VERTICAL"){
            if(get<1>(*it) == col_c && get<0>(*it) == row_c){
                cout << "Your word can't be inserted there" << endl;
                return false;
            }
            else if(get<1>(*it) == col_c) { //IF THAT CASE IS POSSIBLE SEPARATE CONDITION COL_C+-
                if (row_c > get<0>(*it)) {
                    if ((get<2>(*it).size() + get<0>(*it)) >= row_c){
                        cout << "Your word can't be inserted there" << endl;
                        return false;
                    }
                }
                else {
                    if ((row_c + length) >= get<0>(*it)) {
                        cout << "Your word can't be inserted there" << endl;
                        return false;
                    }
                }                                                            // Words in the same vertically in the same row can only be entered
            }
            else if(get<1>(*it) == (col_c + 1) || get<1>(*it) == (col_c-1)){
                if(row_c > get<0>(*it)) {
                    if ((get<2>(*it).size() + get<0>(*it)) > row_c) {
                        cout << "Word can't be inserted there" << endl;
                        return false;
                    }
                }
                else {
                    if ((row_c + length) > get<0>(*it)) {
                        cout << "Your word can't be inserted there" << endl;
                        return false;
                    }
                }
            }
        }
        if(get<3>(*it) == "HORIZONTAL"){                                                      //Words in horizontal can't touch sides with
            if(get<0>(*it) == (row_c-1) || (row_c+length) == get<0>(*it)){                 //a vertical one
                if(col_c >= get<1>(*it) && col_c < get<1>(*it)+get<2>(*it).size()){
                    cout << "Your word can't be inserted there" << endl;
                    return false;
                }
            }
            else if((col_c +1 == get<1>(*it)) || col_c == (get<1>(*it) + get<2>(*it).size())){  //Make sure the word we are trying to insert
                if(get<0>(*it) < (row_c+length) && get<0>(*it) >= row_c){
                    cout << "Your word can't be inserted there" << endl;                                //is between the column limits of the other word
                    return false;
                }
            }
        }
    }
    return true; //Word can be inserted
}


//Word insertion if the direction is horizontal
void Board::word_insert_horizontal(){
    int length = input_Word.size(), k = 0;
    vector<char> reserve; bool insert = true;
    if(column_coord+length > columns + 1){
        cout << "Word doesn't fit inside the board" << endl;
    }
    else{
        for(int i = column_coord; i < (column_coord+length); i++) {
            if (storage[row_coord][i] == '0' || storage[row_coord][i] == input_Word[k]) { // Converting to string input_word[k] = &char
                cout << "WORKING" << endl;
                reserve.emplace_back(storage[i][column_coord]);
                storage[row_coord][i] = input_Word[k];
                k++;
            } else {
                insert = false;
                cout << "Bad word crossing" << endl;
                for (int j = 0; j < reserve.size(); j++) {
                    storage[row_coord][column_coord + j] = reserve[j];
                }
                break;
            }

        }
        if(insert) insert_to_file(); //Insert word to vec to then insert to a file
    }

}


//LATER ON ADD A TRY AND EXCEPTION //Word insertion if the direction is vertical
void Board::word_insert_vertical(){
    int length = input_Word.size(), k = 0;
    vector<char> reserve; bool insert = true; //reverse -> if the word can´t be written but meanwhile some spaces changed, restore the board
    cout << invalid_cross_vertical(to_file,row_coord,column_coord,input_Word.size(),input_Word) << endl;
    if(row_coord+length > rows +1){
        cout << "Word doesn't fit inside the board" << endl;
    }
    else {
        for (int i = row_coord; i < (row_coord + length); i++) {
            if (storage[i][column_coord] == '0' || storage[i][column_coord] == input_Word[k]) { // Converting to string input_word[k] = &char
                cout << "WORKING" << endl;
                reserve.emplace_back(storage[i][column_coord]);
                storage[i][column_coord] = input_Word[k];
                k++;
            } else {
                insert = false;
                cout << "Bad word crossing" << endl;
                for (int j = 0; j < reserve.size(); j++) {
                    storage[row_coord + j][column_coord] = reserve[j];
                }
                break;
            }
        }
        if(insert) insert_to_file();
    }
}



bool Board::end(){
    string over_check;
    cout << "If you want to end the word insertion write end, else write go" << endl;
    cin.ignore(1000,'\n');
    while(true){
        getline(cin, over_check,'\n');
        transform(over_check.begin(),over_check.end(),over_check.begin(),::tolower);
        if(over_check == "end") return true;
        if(over_check == "go") return false;
    }
}

bool Board::direc(){
    return (direction == "HORIZONTAL");
}


void Board::ending_file() {
    try{
        fstream file;
        file.open("nice.txt", ios::out , ios::trunc);
        if(file.is_open()){
            file << rows << " x " << columns << endl;
            for(auto & it : to_file){
                file << char(get<0>(it)+64) <<  char(get<1>(it)+96) << " " << get<3>(it)[0] << " " << get<2>(it) << endl;
            }
            file.close();
        }
        else throw ios::failure("Error while opening file\n");
    }
    catch(const exception &ex) {
        cerr << ex.what() << endl;
        exit(1);
    }

}

void Board::print_file(){
    for(auto &i : to_file){
        cout << get<0>(i) << " " << get<1>(i) << " " << get<3>(i)[0] << " " << get<2>(i) << endl;
    }
}

