// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

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
          if(i != 0 && j != 0 && board.inBounds(row+i,col+j)){ //sålänge vi inte är på den koordinat vars grannar vi ska kolla
               string neighbor = board.get(row+i,col+j); //om giltig, hämta värdet där
               if (neighbor == "X"){
                   numberNeighbors++;
          }}
    }
    }
    return numberNeighbors;
}

void changeBoard(Grid<string>& board, int row, int col, int numberNeighbors){
    if(numberNeighbors < 2){ //alla celler med <2 grannar blir -
        board.set(row, col, "-");
    }
    else if(numberNeighbors == 3){
        board.set(row, col, "X");
    }
   else if(numberNeighbors >= 4){
        board.set(row, col, "-");
    }
}


void nextGenBoard(Grid<string>& board){
    int rows = board.numRows(); //hämtar antalet rader
    int cols = board.numCols(); //hämtar antalet kolumner
    for (int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
          int numberNeighbors = checkNeighbors(board, i, j);
          changeBoard(board, i, j, numberNeighbors);
    }
    }
}

int main() {

    // TODO: Finish the program!
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

    cout << board.toString()<<endl;
    printBoard(board);
    nextGenBoard(board);
    //while (getline(input, line)) { cout << line << endl; //skriver ut varje rad i .txt-filen
    //}
    //input.close();
    //string line;
    //getline(input, line);
    return 0;
}
