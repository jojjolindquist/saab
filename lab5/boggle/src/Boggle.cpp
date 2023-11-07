// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

void Boggle::createRandomBoard(){
    visited.clear(); //nytt boggle -> ta bort visited
    shuffle(CUBES, 16); //shufflade tärningar på brädet
    for (int i = 0; i < NUM_CUBES; i++){
        string cube = CUBES[i];
        int index = randomInteger(0,5);
        int row = i / 4; //heltalsdivision
        int col = i % 4;
        board.set(row, col, string(1, cube[index]));
    }
}

void Boggle::createCustomizedBoard(string letters){
    visited.clear(); //nytt boggle -> ta bort visited
    for (int i = 0; i < NUM_CUBES; i++){
        int row = i / 4; //heltalsdivision
        int col = i % 4;
        board.set(row, col, string(1, letters[i]));
    }
}

bool Boggle::containsValidLetters(string letters){
    for (int i = 0; i < letters.size(); i++){
        if (ALPHABET.find(letters[i]) == string::npos){ //string::npos indikerar att input inte fanns i alfabetet (ingen bokstav)
            return false;
        }
    }
    return true;
}

void Boggle::showBoard(){
    for (int i = 0; i < board.nRows; i++){
        string output = "";
        for (int j = 0; j < board.nCols; j++){
            output.append(board[i][j]);
        }
        cout << output << endl;
    }
}

string Boggle::wordsToString(){
    auto wordsIt = humanWords.begin();
    string words = "{";
    while (wordsIt != humanWords.end()){
        words.append("\"" + *wordsIt + "\"" + ", ");
        wordsIt++;
    }
    if (words.size() > 1){ //lagt till mer än {
        words.pop_back(); //ta bort mellanrum och , på det sista ordet
        words.pop_back();
    }
    words.append("}");
    return words;
}

int Boggle::score(){
    int score = 0;
    auto wordsIt = humanWords.begin();
    while (wordsIt != humanWords.end()){
        int wordScore = wordsIt->size() - 3; //1 poäng om längd 4, 2 poäng om längd 5, 3 poäng om längd 6...
        score += wordScore;
        wordsIt++;
    }
    return score;
}

bool Boggle::insertWord(string word){
    if (word.size() >= 4 && lexicon.contains(word) && humanWords.find(word) == humanWords.end()){ //om == end() så finns inte ordet redan i vårt set
        humanWords.insert(toUpperCase(word));
        return true;
    }
    return false;
}

bool Boggle::checkWordOnBoard(string word){
    string firstLetter = string(1, word[0]);
    for (int i = 0; i < board.nRows; i ++){
        for (int j = 0; j < board.nCols; j ++){
            if (board.get(i,j) == firstLetter){
                if (recursiveSearch(word, i, j)){
                    return true;
                }
            }
        }
    }
 return false;
}

bool Boggle::recursiveSearch(string correctWord, int row, int col, string chosen){
    if (correctWord == ""){
        return true;
    }
    else{
        for (int i=-1; i<2; i++){
            for(int j=-1; j<2; j++){
              if(!(i==0 && j==0) && board.inBounds(row+i,col+j)){
                   string letter = board.get(row+i,col+j); //giltig koordinat, hämta nu värdet där
                   pair<int, int> neighbor = pair<int, int>(i,j);
                   if (visited.find(neighbor) == visited.end() && isPrefix(chosen+letter, correctWord)){
                       visited.insert(neighbor);
                  // if (isPrefix(chosen + letter, correctWord)){
                       //TODO: kolla om prefix till correctword, isåfall ta bort, skicka in ny version av
                       //TODO: markera visited neighbours
                       //TODO: hitta inte samma ord två gånger
                       int lengthPrefix = chosen.length();
                       string corrWordWithoutPrefix = correctWord.substr(0, lengthPrefix);
                       recursiveSearch(corrWordWithoutPrefix, row + i, col+j, chosen + letter);
                   }
                }
            }
        }
    }

}

bool Boggle::isPrefix(string substring, string word){
    if (word.find(substring) == 0){ //find() returnerar position som substrängen börjar, ett prefix börjar på pos 0
        return true;
    }
    return false;
}


