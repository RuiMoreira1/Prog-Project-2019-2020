#include "board.h"


//Colored text function for [windows only]
void text_color(const string &text,int color) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    cout << text;
}


//Constructor, asks for user input regarding the size of the board, and initializes the matrix holder vector with the desired space
Board::Board(const Warnings &warning){
    scan_input_board(warning);
    vector_init();
    row_coord = 0; column_coord = 0;
    row_board = 65; column_board = 97;           //Ascii code for 'A' and 'a'
    direction = "", input_Word = "";
}

//Ask for user input regarding the size of the board
void Board::scan_input_board(const Warnings &warning){
    cout << "Size of the board? (R x C)" << endl;      //The board size
    cout << "Enter the Rows" << endl;
    cin >> rows;
    while(!cin || rows > 20 || rows < 1){             //If the user enters a row higher than 20 or lower than 1 or the user input is invalid ask for the user input again
        cin.clear(); cin.ignore(100000000,'\n'); text_color(warning, 4); text_color("\n",7); cin >> rows;
    }
    cout << "Enter the Columns" << endl;
    cin >> columns;
    while(!cin || columns > 20 || columns < 1){ //If the user enters a column higher than 20 or lower than 1 or the user input is invalid ask for the user input again
        cin.clear(); cin.ignore(1000000000000,'\n'); text_color(warning, 4); text_color("\n",7); cin >> columns;
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
        storage[0][i] = column_board++;           //The coordinates are inserted in the board
    }                                             //using the ascii code starting at 97 for the column
    for(int k = 1; k < rows+1 ; k++){             //and 65 for the row
        storage[k][0] = row_board++;
    }
}


//Print the board with the desired area
void Board::PrintBoard() const{                        //Since the PrintBoard function doesn't update any of the private
    for(int i = 0; i < rows+1; i++){                   //variables in the board, is declared as a const function
        if( i != 0)
            text_color("|",4);                               //This functions helps to print the board, using storage
        else cout << " ";                                             //to put the letters in the right places inside the board
        for(int j = 0; j < columns+1; j++){                           //and using the desired amount of columns and rows entered by the user
            if(i == 0 || j == 0){
                text_color(" ",4); text_color(string(1,storage[i][j]),4); text_color(" |",4);
            }
            else if( storage[i][j] != ' ') {
                text_color(" ",15); text_color(string(1,storage[i][j]),15); text_color("  ",7);
            }
            else {
                text_color(" ",7); cout << storage[i][j] << "  ";
            }
        }
        cout << endl;
    }
}

//Direction of the word input by user
void coord_input(string &dir, const Warnings &war_d){
    //cin.ignore(1000,'\n'); // Clean the buffer from cin, so that getline doesn't get an error
    while(true){
        getline(cin,dir,'\n');                       //user input with char delimiter '\n'
        transform(dir.begin(),dir.end(),dir.begin(),::toupper);  //uppercase the string so that the comparison, even if the user inserts
        if(dir == "HORIZONTAL" || dir == "VERTICAL") break;      //the word mixing lowercase and uppercase letters is valid, then break the loop
        else{
            text_color(war_d,4); text_color("\n",7); //if the user input is neither of those ask for the user input again
        }
    }
}


//Coordinates input by user, column and row 65 and 97 are the ascii values of of A and a;
void coord_input(int &x, const int rows_col, const Warnings &war, const char check = ' ', char tempo = ' '){
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
        if(tempo > (rows_col-1)+ver || tempo < ver){                                                    //A row == 1 a col == 1
            text_color(war+word,4); text_color("\n",7);                                   //Helps to check whether the user is choosing a
            cin.clear();cin.ignore(1000000000,'\n'); cin >> tempo;                      //and existing row or column in the board, if not
        }                                                                                              //it clears the user input and asks again
        else {
            x = (tempo-(ver-1));                                      //If the column or row exists it will give the position the word should be inserted
            cin.clear();cin.ignore(10000000000,'\n'); //And the rest of the input is clear(case Aj only reads A but j stays in the buffer) with cin.clear and cin.ignore clears the j for the next input
            break;
        }
    }
}

//Ask me for the user input (direction,row_coord to insert the word,col_coord to insert the word)
void Board::scan_input_cord(const Warnings &war, const Warnings &war_d){
    text_color("Enter the direction (Horizontal/Vertical)\n",7);
    coord_input(direction,war_d);                                                 //Ask the user the direction of the word
    cout << "Row in UPPERCASE LETTER, Column in LOWERCASE LETTER" << endl;
    coord_input(row_coord,rows,war,'r');                                   //Ask the user the row where we wants the word to be inserted
    coord_input(column_coord,columns,war,'c');                             //Ask the user the column where we wants the word to be inserted
}

//Read file line by line and getting the words into word_storage vector
//The file is opened only once and when checking if the word exists in dictionary only have to go throw the vector
//If the function can´t open the file it will throw an exception
bool Board::read_file(const Warnings &war) {
    string line, path;
    cout << "Enter the FULL path to your dictionary file" << endl;
    cin >> path;
    try {
        ifstream file(path.c_str());
        if (file.is_open()) {
            int i = 0;
            while (getline(file, line)) {                 //So that we wouldn't have open the file every time we wanted
                dic[i] = line; i++;                             //this function is useful to load the words into a map(the find method in map is more efficient than,
            }                                                   //the vector one), so that later on,a verification can be done whether or not the word exists in the file
        }
        else throw ios::failure( war);
        file.close(); return true;
    }
    catch(const exception &ex) {                                                   //If the file can´t be opened the program will throw and exception and
        text_color(ex.what(),4); text_color("\n",7);                //tries to read again
        cin.clear(); cin.ignore(10000,'\n'); return false;
    }
}


//Check if input word is in words.txt vector
bool in_vector(map<int,string> &m, const string &word){
    auto it = find_if(m.begin(), m.end(), [word](const auto& mp){return mp.second == word;});                      //Functions that helps to check whether or not the word exists in the
    return it != m.end();                                                                                          //dictionary/file created above
}                                                                                                                  //auto = map<int,string>::iterator


//Get the word input from the user and then check if it exists in words.txt
void Board::word_in_vec(){
    cin.ignore(100000000,'\n');                           //Using the in_vector function checks if the word entered by the user
    while(true){                                                          //is in the file, if not asks for the user for another word, until he inserts one
        cout << "Enter a valid word to allocate in the board" << endl;    //that exists inside the file
        getline(cin,input_Word);
        transform(input_Word.begin(),input_Word.end(),input_Word.begin(),::tolower);  //lowercase all the letters to be able to compared
        if(in_vector(dic, input_Word)){                                                           //the words inside the dictionary correctly
            cout << "Word is in words.txt" << endl;                                                  //if word in words.txt vector
            break;
        }
    }
}

//If the word doesn't fit the board delete the '!' added
void Board::Error(){
    input_Word.pop_back();
}

//Function with all the warnings, regarding input errors
Warnings Board::Get_warnings(int i){
    Warnings invalid_coord = "ERROR!!!\nEnter a valid ";
    Warnings invalid_insertion = "Your word can't be inserted there!\n|||||||||||||Try again|||||||||||||\n";
    Warnings invalid_direction = "Wrong input, enter horizontal or vertical";
    Warnings invalid_board_size = "Wrong input!";
    Warnings file_open = "Error while opening file\n";
    vector<Warnings> warning = {invalid_coord,invalid_insertion,invalid_direction,invalid_board_size,file_open};
    return warning[i];
}

//Checks if the words fits horizontally
bool Board::word_insert_horizontal_2(const Warnings &warning){
    int length = input_Word.size(), k = 0;               //Length is calculate before updating the string so that the for loop doesn't extend the vec size
    input_Word += "!";                                   //When k+1 is called if k == last char k+1 == ! so it doesn't get an error
    vector<tuple<int,int,char>> reserve;                 //Keeps the coords and the letter, if the word fits the board it will store the word in the board.
    if( (column_coord+length > columns + 1) || (storage[row_coord][column_coord-1] != ' ' && column_coord-1 != 0) ){   //If the length of the word doesn't fit totally inside the board
        text_color(warning,4); return false;                                                                      //or if there is a word with the same orientation
    }                                                                                                                  //with no space between them
    for(int i = column_coord; i < (column_coord+length); i++) {
        if (storage[row_coord][i] == input_Word[k]) {                                //If the place in the vector where the insertion is being done
            reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;        //is already occupied by a char, if the char is == to the char being
        }                                                                            //placed the insertion is valid
        else if(row_coord == 1){
            if( (i == columns) && (storage[row_coord+1][i] == ' ') ){                           //Row == 1 && col == col && the place under the insertion
                reserve.emplace_back(make_tuple(row_coord,i,input_Word[k]));                    //is free(' ') then the insertion is valid
            }
            else if( (i == 1) && (storage[row_coord+1][i] == ' ')){                               //Row == 1 && col == 1 && the place under the insertion
                if(storage[row_coord][i+1] == ' ' || storage[row_coord][i+1] == input_Word[k+1]){ //is free(' ') and the place besides the insertion is also free(' ')
                    reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;             //or =='s to the next char of the string then the insertion is valid
                }
                else {
                    text_color(warning,4); return false;  //Where else the input is invalid
                }
            }
            else if(storage[row_coord+1][i] == ' '){                                                       //If Row == 1 and the place under is fre(' ') and
                if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1])){     //the place besides the insertion is also free(' ') or
                    reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;                      //equal to the next char of the string then the insertion is valid
                }
                else{
                    text_color(warning,4); return false;  //Where else the input is invalid
                }
            }
            else{
                text_color(warning,4); return false;  //Where else the input is invalid
            }
        }
        else if(row_coord == rows){
            if( ( i == 1 && storage[row_coord-1][i] == ' ' ) || ( storage[row_coord-1][i] == ' ') ){      //Row == rows if the place above the insertion and the
                if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1])){    //the place besides the word == to free(' ') or == to
                    reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;                     //the next char of the string then the insertion is valid
                }
                else{
                    text_color(warning,4); return false; //Where else the input is invalid
                }
            }
            else if( (i == columns) && (storage[row_coord-1][i] == ' ') ){       //Row == rows and col = col and the place above is free
                reserve.emplace_back(make_tuple(row_coord,i,input_Word[k]));     //then the insertion is valid
            }
            else{
                text_color(warning,4); return false;  //Where else the input is invalid
            }
        }
        else{
            if( (i == columns) && (storage[row_coord+1][i] == ' ') && (storage[row_coord-1][i] == ' ') ){    //if the col == col and the place above and under
                reserve.emplace_back(make_tuple(row_coord,i, input_Word[k]));                                //are free(' ') then the insertion is valid
            }
            else if ( ( i == 1 && storage[row_coord-1][i] == ' ') || ( (storage[row_coord+1][i] == ' ') && (storage[row_coord-1][i] == ' '))){
                if( (storage[row_coord][i+1] == ' ') || (storage[row_coord][i+1] == input_Word[k+1])){                    //if col == 1 and the place under is free(' ')
                    reserve.emplace_back(make_tuple(row_coord,i,input_Word[k])); k++;
                }
                else{
                    text_color(warning,4); return false;  //Where else the input is invalid
                }
            }
            else{
                text_color(warning,4); return false;  //Where else the input is invalid
            }
        }
    }

    for(auto &it : reserve){                                      //If the word fits the board, insert the word onto the board
        storage[get<0>(it)][get<1>(it)] = get<2>(it);    //auto = vector<tuple<int,int,char>>
    }
    input_Word.pop_back();   //Before entering the word to the file, if it fits the board, remove the '!' from the string
    insert_to_file();        //Insert the word onto the file
    return true;
}


//Checks if the word fits vertically
bool Board::word_insert_vertical_2(const Warnings &warning){
    int length = input_Word.size(), k = 0;              //Length is calculate before updating the string so that the for loop doesn't extend the vec size
    input_Word += "!";                                  //When k+1 is called if k == last char k+1 == ! so it doesn't get an error
    vector<tuple<int,int,char>> reserve;                //Keeps the coords and the letter, if the word fits the board it will store the word in the board.
    if((row_coord+length > rows +1) || (storage[row_coord-1][column_coord] != ' ' && row_coord-1 != 0)){
        text_color(warning,4); return false;
    }
    for(int i = row_coord; i < (row_coord + length); i++) {
        if (storage[i][column_coord] == input_Word[k]) {                             //If the place in the vector where the insertion is being done
            reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;     //is already occupied by a char, if the char is == to the char being
        }                                                                            //placed the insertion is valid
        else if(column_coord == 1){
            if(i == rows && storage[i][column_coord+1] == ' '){                                            //Column coord == 1
                reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;                       //if col == 1 and rows == rows check only for
            }                                                                                              //the place besides the insertion, if empty, the insertion is valid
            else if( (i == 1 && storage[i][column_coord] == ' ') || (storage[i][column_coord+1] == ' ') ){
                if(storage[i+1][column_coord] == ' ' || storage[i+1][column_coord] == input_Word[k+1]){    //col == 1 rows == 1 or col == 1 and the place besides
                    reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;                   //the insertion is free(' ') and the row under the insertion
                }                                                                                          //is == to ' ' or == to the next char in the string then the move is valid
                else{
                    text_color(warning,4); return false; //Where else the move is invalid
                }
            }
            else{
                text_color(warning,4); return false; //Where else the move is invalid
            }
        }
        else if(column_coord == columns){
            if( (i == rows) && storage[i][column_coord-1] == ' '){                            //Col = Col && rows == rows && the space besides the insertion is ' '
                reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;          //then the insertion is valid
            }
            else if(storage[i][column_coord-1] == ' '){                                                 //Col == col and the space besides the insertion is free(' ')
                if(storage[i+1][column_coord] == ' ' || storage[i+1][column_coord] == input_Word[k+1]){ //and the space under the insertion is free(' ') or == to
                    reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;                //the next char in the string, the insertion is valid
                }
                else{
                    text_color(warning,4); return false; //Where else the move is invalid
                }
            }
            else{
                text_color(warning,4); return false; //Where else the move is invalid
            }

        }
        else if(storage[i][column_coord-1] == ' ' && storage[i][column_coord+1] == ' ') {      //Both place besides the insertion are free(' ')
            if( i == rows ){                                                                   //the move is valid
                if(storage[i][column_coord-1] == ' ' && storage[i][column_coord+1] == ' '){
                    reserve.emplace_back(make_tuple(i,column_coord,input_Word[k])); k++;
                }
                else{
                    text_color(warning,4); return false; //Where else the move is invalid
                }
            }
            else if (storage[i + 1][column_coord] == ' ' || storage[i + 1][column_coord] == input_Word[k + 1]) { //If the place besides the insertion are free(' ')
                reserve.emplace_back(make_tuple(i, column_coord, input_Word[k])); k++;                           //and the place under the insertion is == to ' ' or
            }                                                                                                    //== to the next char in the string
            else{
                text_color(warning,4); return false; //Where else the move is invalid
            }
        }
        else{
            text_color(warning,4); return false; //Where else the move is invalid
        }
    }

    for(auto &it: reserve){                                        //If the word fits the board, insert the word onto the board
        storage[get<0>(it)][get<1>(it)] = get<2>(it);     //auto = vector<tuple<int,int,char>>
    }
    input_Word.pop_back(); //Before inserting the word, only if the word fits the board, eliminate the '!' inserted in the string
    insert_to_file();      //Insert the word to the file
    return true;
}

//If the word insertion is valid add it to the vector to then output it to the file
void Board::insert_to_file(){
    to_file.emplace_back(make_tuple(row_coord,column_coord,input_Word,direction)); //Each element inside to_file vector is a tuple<int,int,string,string>
}

//Check if the user doesn't want to insert more data to the board
bool Board::end(){
    string over_check;
    cout << "If you want to end the word insertion write end, else press write something else" << endl;     //Checks whether the user wants to proceed
    cin >> over_check;                                                                                      //with the word insertion in the board
    transform(over_check.begin(),over_check.end(),over_check.begin(),::tolower);                            //lowercase all the input
    return over_check == "end";                                                                             //if input == end, finish program

}

bool Board::Get_direction(){
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
void Board::ending_file(const Warnings &war) {
    sort(to_file.begin(),to_file.end(), my_sort);                              //applying the sort function to to_file vector
    try{
        fstream file;
        file.open("BOARD.txt", ios::out , ios::trunc);
        if(file.is_open()){
            file << rows << " x " << columns << endl;
            for(auto & it : to_file){
                file << char(get<0>(it)+64) <<  char(get<1>(it)+96) << " " << get<3>(it)[0] << " " << get<2>(it) << endl;  //File writing
            }                                                                            //row coordinate -> get<0>(it)+ ascii code of A-1
            file.close();                                                                //col coordinate -> get<1>(it)+ ascii code of a-1
        }                                                                                //direction -> get<3>(it)[0], just the first letter
        else throw ios::failure(war);                                                    //word -> get<2>(it)
    }
    catch(const exception &ex) {                                           //If the file can't be opened the program will throw an
        cerr << ex.what() << endl;                                         //exception and shutdown
        exit(1);
    }

}





//CREATED BY RUI_MOREIRA


