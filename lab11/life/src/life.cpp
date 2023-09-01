#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include<fstream>
#include <string>
using namespace std;

Grid<string> makeBoard(const string filename){ //skapar en board utifrån ett filnamn
    string fileName;
    int rows;       //deklarerar variabler
    int columns;
    ifstream input;

    input.open(filename.c_str()); //öppnar filen som en c_string
    string line;
    getline(input, line); //hämtar rader
    rows = stoi(line); //sätter värdet genom att omvandla till int
    getline(input,line); //hämtar kolumner
    columns = stoi(line);
    Grid<string> board = Grid<string>(rows, columns); //skapar en tom grid
    for(int i = 0; i < rows; i++){ //går igenom varje "ruta"
        getline(input,line);
        for(int j = 0; j < columns; j++){
            char value = line[j];
            board[i][j] = value;
        }
    }
    return board;
}

void printBoard(Grid<string>& board){
    int rows = board.numRows(); //hämtar antalet rader
    int cols = board.numCols(); //hämtar antalet kolumner
    string boardToShow;
    for (int i=0; i<rows; i++){
        if (i != 0){ //om inte första raden
        boardToShow.append("\n"); //när ny rad gör först radbryt
        }
        for(int j=0; j<cols; j++){
            boardToShow.append(board.get(i,j));
        }
    }
    cout<<boardToShow<<endl;
}

int checkNeighbors(Grid<string>& board, int row, int col){
    int numberNeighbors = 0;
    //kolla runt om koordinat, om in bounds kolla om X, annars fortsätt
    for (int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
          bool condition = (i != 0 && j == 0 ) || ( j!= 0 && i == 0) || (j != 0 && i != 0); //i och j får ej vara 0 samtidigt (egna koordinaten)
          if(condition && board.inBounds(row+i,col+j)){ //sålänge vi är in bounds och inte är på den koordinat vars grannar vi ska kolla
               string neighbor = board.get(row+i,col+j); //giltig koordinat, hämta nu värdet där
               if (neighbor == "X"){ //om det är en cell där
                   numberNeighbors++; //öka antalet grannar
          }}
    }
    }
    return numberNeighbors;
}

void changeBoard(Grid<string>& board, int row, int col, int numberNeighbors, string originalValue){

    if(numberNeighbors < 2){ //alla celler med <2 grannar blir -
        board.set(row, col, "-");
    }
    else if(numberNeighbors == 3){ //de med tre grannar börjar leva
        board.set(row, col, "X");
    }
   else if(numberNeighbors >= 4){ //de med >=4 grannar dör
        board.set(row, col, "-");
    }
    else if (numberNeighbors == 2){ //vill ha samma värde som original-board
        board.set(row,col, originalValue);
    }
}


void nextGenBoard(Grid<string>& board){
    //copyBoard.deepCopy(board);
    int rows = board.numRows(); //hämtar antalet rader
    int cols = board.numCols(); //hämtar antalet kolumner
    Grid<string> nextGenBoard = Grid<string>(rows, cols);//vill bygga upp en ny board sen
    for (int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
          int numberNeighbors = checkNeighbors(board, i, j);
          changeBoard(nextGenBoard, i, j, numberNeighbors, board.get(i,j));
    }
    }
    board = nextGenBoard;
}

int main() {
    string filename;
    string welcomeMessage = "Welcome to the TDDD86 Game of Life, "
                            "a simulation of the lifecycle of a bacteria colony.""\n"
                            " Cells (X) live and die by the following rules: \n"
                            "- A cell with 1 or fewer neighbours dies.\n"
                            "- Locations with 2 neighbours remain stable.\n"
                            "- Locations with 3 neighbours will create life.\n"
                            "- A cell with 4 or more neighbours dies." ;
    cout << welcomeMessage << endl;
    cout << "Grid input file name? ";
    cin >> filename;

    Grid<string> board = makeBoard(filename); //skapar en grid utifrån vår fil
    printBoard(board); //visar board
    bool continueProgram = true; //vi fortsätter programmet när denna är true
    string answer;
    while(continueProgram){
        cout << "a)nimate, t)ick, q)uit?" << endl;
        cin >> answer;
        if (answer == "a"){
            while(answer == "a"){
                clearConsole();
                nextGenBoard(board);
                printBoard(board);
                pause(100);
               // cin >> answer;
            }
        }
        else if (answer == "t"){
            nextGenBoard(board); //skapar nästa generations board
            printBoard(board);
        }
        else if (answer == "q"){
            cout << "Have a nice Life!" << endl;
            continueProgram = false;
        }
    }

    return 0;
}
