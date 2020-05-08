#include "board.h"


//Ask for user input regarding the size of the board
void Board::scan_input_board(){
    cout << "Size of the board? (R x C)" << endl;      //The board size
    cout << "Enter the Rows" << endl;
    cin >> rows;
    while(!cin || rows > 20 || rows < 1){             //If the user enters a row higher than 20 or lower than 1 or the user input is invalid ask for the user input again
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout << "Wrong input!!!" << endl; cin >> rows;
    }
    cout << "Enter the Columns" << endl;
    cin >> columns;
    while(!cin || columns > 20 || columns < 1){ //If the user enters a column higher than 20 or lower than 1 or the user input is invalid ask for the user input again
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout << "Wrong input!!!" << endl; cin >> columns;
    }
}


//Initialize storage vector
void Board::vector_init(){
    storage.assign(rows+1, vector<char>(columns+1, ' ')); //Initialize a 2d vector that stores the words with char ' ' inside
}                                                                                //rows+1 and col+1 so that the coordinate rows and columns can be inserted


//Fill the 1st column and row of board with the coordinates
void Board::FillCord(){                           //Fills the first column and row of storage vector
    storage[0][0] = '#';                          //so that the user can identify the initial coordinates
    for(int i = 1; i < columns+1; i++){           //where he wants the word to be inserted
        storage[0][i] = column_board;
        column_board += 1;                        //The coordinates are inserted in the board
    }                                             //using the ascii code starting at 97 for the column
    for(int k = 1; k < rows+1 ; k++){             //and 65 for the row
        storage[k][0] = row_board;
        row_board += 1;
    }
}


//Print the board with the desired area
void Board::PrintBoard() const{                        //Since the PrintBoard function doesn't update any of the private
    for(int i = 0; i < rows+1; i++){                   //variables in the board, is declared as a const function
        if( i != 0)
            cout << "|";                               //This functions helps to print the board, using storage
        else cout << " ";                              //to put the letters in the right places inside the board
        for(int j = 0; j < columns+1; j++){            //and using the desired amount of columns and rows entered by the user
            cout << " " << storage[i][j] << " |";
        }
        cout << endl;
    }
}

//Direction of the word input by user
void coord_input(string &dir){
    //cin.ignore(1000,'\n'); // Clean the buffer from cin, so that getline doesn't get an error
    while(true){
        getline(cin,dir,'\n');                       //user input with char delimiter '\n'
        transform(dir.begin(),dir.end(),dir.begin(),::toupper);  //uppercase the string so that the comparison, even if the user inserts
        if(dir == "HORIZONTAL" || dir == "VERTICAL") break;      //the word mixing lowercase and uppercase letters is valid, then break the loop
        else{
            cout << "Wrong input, enter horizontal or vertical" << endl; //if the user input is neither of those ask for the user input again
        }
    }
}


//Coordinates input by user, column and row 65 and 97 are the ascii values of of A and a;
void coord_input(int &x, const int rows_col, const char check = ' ', char tempo = ' '){
    string word;
    int ver;
    if(check == 'c') {                           //If check == 'c' then we are talking about the columns
        ver = 97;                                //since the columns are in lowercase letters a == 97
        word = "column";}                        //so the 'ver' is set up to the value 97
    else{
        ver = 65;                                //If check == 'a' -> rows, since rows are in uppercase a = 65
        word = "row";}                           //so the 'ver' is set up to the value 65
    cout << "Enter a valid " << word << endl;    //The word value helps the user identify if they should give the row or the column
    cin >> tempo;
    while(true){
        if(tempo > (rows_col-1)+ver || tempo < ver){                                        //A row == 1 a col == 1
            cout << "ERROR!!!\nEnter a valid " << word << endl;                                       //Helps to check whether the user is choosing a
            cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n'); cin >> tempo;   //and existing row or column in the board, if not
        }                                                                                            //it clears the user input and asks again
        else {
            x = (tempo-(ver-1));                 //If the column or row exists it will give the position the word should be inserted
            break;
        }
    }
}

//Ask me for the user input (direction,row_coord to insert the word,col_coord to insert the word)
void Board::scan_input_cord(){
    cout << "Enter the direction (Horizontal/Vertical)" << endl;
    coord_input(direction);                                                 //Ask the user the direction of the word
    cout << "Row in UPPERCASE LETTER, Column in LOWERCASE LETTER" << endl;
    coord_input(row_coord,rows,'r');                                   //Ask the user the row where we wants the word to be inserted
    coord_input(column_coord,columns,'c');                             //Ask the user the column where we wants the word to be inserted
}

//Read file line by line and getting the words into word_storage vector
//The file is opened only once and when checking if the word exists in dictionary only have to go throw the vector
//If the function can´t open the file it will throw an exception
void Board::read_file() {
    string line;
    try {
        fstream file(R"(C:\Users\ruipe\CLionProjects\PROG[BOARD_BUILDER]\WORDS.txt)", ios::in, ios::binary);  //The path of the file should be updated!!!
        if (file.is_open()) {
            while (getline(file, line)) {                 //So that we wouldn't have open the file every time we wanted
                dictionary.push_back(line);                     //this function is useful to load the words into a vector,
            }                                                   //so that later on, a verification can be done whether or not the word exists in the file
        }
        else throw ios::failure( "Error opening file!\n");
        file.close();
    }
    catch(const exception &ex) {                         //If the file can´t be opened the program will throw and exception and
        cerr << ex.what() << endl;                       //shut down the program
        exit(1);
    }
}


//Check if input word is in words.txt vector
bool in_vector(vector<string> &v, const string &word){              //Functions that helps to check whether or not the word exists in the
    vector<string>::iterator it = find(v.begin(),v.end(),word);     //dictionary/file created above
    return it != v.end();
}


void Board::word_insert_horizontal_2(){
    int length = input_Word.size(), k = 0;
    input_Word += "!"; // when k+1 is called if k == last char k+1 == ! so it doesn't get an error
    vector<tuple<int,int,char>> reserve; bool insert = true;
    if(column_coord+length > columns + 1){
        cout << "Word doesn't fit inside the board" << endl; insert = false;
    }
    else if(storage[row_coord][column_coord-1] != ' ' && column_coord-1 != 0){
        cout << "NEW FLAG" << endl; insert = false;
    }
    else{
        for(int i = column_coord; i < (column_coord+length); i++) {
            if (storage[row_coord][i] == input_Word[k]) { // Converting to string input_word[k] = &char
                cout << "WORKING SAME LETTER" << endl;
                reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
            }

            else if(row_coord == 1){
                if( (i == columns) && (storage[row_coord+1][i] == ' ') ){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k]));
                }
                else if( (i == 1) && (storage[row_coord+1][i] == ' ')){
                    if(storage[row_coord][i+1] == ' ' || storage[row_coord][i+1] == input_Word[k+1]){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else {
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if(storage[row_coord+1][i] == ' '){
                    if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1])){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                }
                else{
                    cout << "NOT WORKING" << endl; insert = false; break;
                }
            }

            else if(row_coord == rows){
                if( (i == 1) && (storage[row_coord-1][i] == ' ')){
                    if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1])){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if( (i == columns) && (storage[row_coord-1][i] == ' ') ){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k]));
                }
                else if( storage[row_coord-1][i] == ' '){
                    if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1]) ){
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
                if( (i == columns) && (storage[row_coord+1][i] == ' ') && (storage[row_coord-1][i] == ' ') ){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i, input_Word[k]));
                }
                else if ( (i == 1) && storage[row_coord-1][i] == ' '){
                    if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1])){
                        cout << "WORKING" << endl; reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if( (storage[row_coord+1][i] == ' ') && (storage[row_coord-1][i] == ' ')){
                    if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1]) ){
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
    vector<tuple<int,int,char>> reserve; bool insert = true; //Keeps the coords and the letter, if the word fits the board it will store the word in the board.
    if(row_coord+length > rows +1){
        cout << "Word doesn't fit inside the board" << endl; insert = false;
    }
    else if(storage[row_coord-1][column_coord] != ' ' && row_coord-1 != 0){
        cout << "NEW FLAG" << endl; insert = false;
    }
    else {
        for (int i = row_coord; i < (row_coord + length); i++) {
            if (storage[i][column_coord] == input_Word[k]) {
                cout << "WORKING" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
            }
            else if(column_coord == 1){
                if(i == rows && storage[i][column_coord+1] == ' '){
                    cout << "Working" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                }
                else if(i == 1 && storage[i][column_coord] == ' '){
                    if(storage[i+1][column_coord] == ' ' || storage[i+1][column_coord] == input_Word[k+1]){
                        cout << "Working" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                    }
                    else{
                        cout << "NOT WORKING" << endl; insert = false; break;
                    }
                }
                else if(storage[i][column_coord+1] == ' '){
                    if(storage[i+1][column_coord] == ' ' || storage[i+1][column_coord] == input_Word[k+1]){
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
                if( (i == rows) && storage[i][column_coord-1] == ' '){
                    cout << "WORKING" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++; insert = true;
                }
                else if(storage[i][column_coord-1] == ' '){
                    if(storage[i+1][column_coord] == ' ' || storage[i+1][column_coord] == input_Word[k+1]){
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
            else if(storage[i][column_coord-1] == ' ' && storage[i][column_coord+1] == ' ') {
                if( i == rows ){
                    if(storage[i][column_coord-1] == ' ' && storage[i][column_coord+1] == ' '){
                        cout << "Working" << endl; reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                    }
                    else{
                        cout << "Not working" << endl; insert = false; break;
                    }
                }
                else if (storage[i + 1][column_coord] == ' ' || storage[i + 1][column_coord] == input_Word[k + 1]) {
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


//Get the word input from the user and then check if it exists in words.txt
void Board::word_in_vec(){
    cin.ignore(numeric_limits<streamsize>::max(),'\n');          //Using the in_vector function checks if the word entered by the user
    while(true){                                                          //is in the file, if not asks for the user for another word, until he inserts one
        cout << "Enter a valid word to allocate in the board" << endl;    //that exists inside the file
        getline(cin,input_Word);
        transform(input_Word.begin(),input_Word.end(),input_Word.begin(),::tolower); //lowercase all the letters to be able to compared
        if(in_vector(dictionary, input_Word)){                                                    //the words inside the dictionary correctly
            cout << "Word is in words.txt" << endl; //if word in words.txt vector
            break;
        }

    }
}


//If the word insertion is valid add it to the vector to then output it to the file
void Board::insert_to_file(){
    to_file.emplace_back(make_tuple(row_coord,column_coord,input_Word,direction)); //Each element inside to_file vector is a tuple<int,int,string,string>
}

//Check if the user doesn't want to insert more data to the board
bool Board::end(){
    string over_check;
    cout << "If you want to end the word insertion write end, else write go" << endl;     //Checks whether the user wants to proceed
    cin.ignore(numeric_limits<streamsize>::max(),'\n');                          //with the word insertion in the board
    while(true){
        getline(cin, over_check);
        transform(over_check.begin(),over_check.end(),over_check.begin(),::tolower);       //lowercase all the input
        if(over_check == "end") return true;                                               //if input == end, finish program
        else if(over_check == "go") return false;                                          //else if the input == go, keep the program running
    }
}

bool Board::direct(){
    return (direction == "HORIZONTAL");            //To help the program decide which word_insert function to choose, to check if the insertion is indeed valid
}

bool my_sort(const tuple<int,int,string,string>&a, const tuple<int,int,string,string>&b){ //Custom function to sort the elements
    if(get<3>(a) == get<3>(b)){                                                           //that are going inside the file
        if(get<0>(a) == get<0>(b)){                                                       //first by direction
            if(get<1>(a) == get<1>(b)){                                                   //then by the first coordinate
                return (get<2>(a) < get<2>(b));                                           //then by the second coordinate
            }                                                                             //then by the word
            else return (get<1>(a) < get<1>(b));                                          //all in ascending order
        }
        else return (get<0>(a) < get<0>(b));
    }
    else return (get<3>(a) < get<3>(b));
}


//When the input in the board is over, insert the data to the file so that it can be used later on
void Board::ending_file() {
    sort(to_file.begin(),to_file.end(), my_sort);                              //applying the sort function to to_file vector
    try{
        fstream file;
        file.open("nice.txt", ios::out , ios::trunc);
        if(file.is_open()){
            file << rows << " x " << columns << endl;
            for(auto & it : to_file){
                file << char(get<0>(it)+64) <<  char(get<1>(it)+96) << " " << get<3>(it)[0] << " " << get<2>(it) << endl;  //File writing
            }                                                                            //row coordinate -> get<0>(it)+ ascii code of A-1
            file.close();                                                                //col coordinate -> get<1>(it)+ ascii code of a-1
        }                                                                                //direction -> get<3>(it)[0], just the first letter
        else throw ios::failure("Error while opening file\n");                   //word -> get<2>(it)
    }
    catch(const exception &ex) {                                           //If the file can't be opened the program will throw an
        cerr << ex.what() << endl;                                         //exception and shutdown
        exit(1);
    }

}


//Function not necessary just to check what the function above is printing to the Board.txt file
void Board::print_file(){
    for(auto &i : to_file){
        cout << get<0>(i) << " " << get<1>(i) << " " << get<3>(i)[0] << " " << get<2>(i) << endl;
    }
}

//CREATED BY RUIMOREIRA


