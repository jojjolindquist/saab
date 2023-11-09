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
    shuffle(CUBES, NUM_CUBES); //shufflade tärningar på brädet
    for (int i = 0; i < NUM_CUBES; i++){ //itererar genom alla kuber
        string cube = CUBES[i];
        int index = randomInteger(0,BOARD_SIZE+1); //hämtar ett random index
        int row = i / BOARD_SIZE; //heltalsdivision
        int col = i % BOARD_SIZE;
        board.set(row, col, string(1, cube[index]));
    }
}

void Boggle::createCustomizedBoard(const string& letters){
    visited.clear(); //nytt boggle -> ta bort visited
    for (int i = 0; i < NUM_CUBES; i++){
        int row = i / BOARD_SIZE; //heltalsdivision
        int col = i % BOARD_SIZE;
        board.set(row, col, toUpperCase(string(1, letters[i]))); //vill ha stora bokstäver på brädet oavsett
    }
}

bool Boggle::containsValidLetters(const string& letters){
    for (int i = 0; i < letters.size(); i++){
        if (ALPHABET.find(letters[i]) == string::npos){ //string::npos indikerar att input inte fanns i alfabetet (ingen bokstav)
            return false;
        }
    }
    return true;
}

string Boggle::showBoard(){
    string output = "";
    for (int i = 0; i < board.nRows; i++){      
        for (int j = 0; j < board.nCols; j++){
            output.append(board[i][j]);
        }
        output.append("\n");
    }
    return output;
}

string Boggle::wordsToString(const unordered_set<string>& wordsVec){
    auto wordsIt = wordsVec.begin();
    string words = "{";
    while (wordsIt != wordsVec.end()){
        words.append("\"" + toUpperCase(*wordsIt) + "\"" + ", ");
        wordsIt++;
    }
    if (words.size() > 1){ //lagt till mer än {
        words.pop_back(); //ta bort mellanrum och , på det sista ordet
        words.pop_back();
    }
    words.append("}");
    return words;
}

int Boggle::score(const unordered_set<string>& wordsVec){
    int score = 0;
    auto wordsIt = wordsVec.begin();
    while (wordsIt != wordsVec.end()){
        int wordScore = wordsIt->size() - 3; //1 poäng om längd 4, 2 poäng om längd 5, 3 poäng om längd 6...
        score += wordScore;
        wordsIt++;
    }
    return score;
}

bool Boggle::insertWord(string& word){
    if (word.size() >= MIN_WORD_LENGTH && lexicon.contains(word) && humanWords.find(word) == humanWords.end()
        && wordOnBoard(word)){ //om == end() så finns inte ordet redan i vårt set
        humanWords.insert(toUpperCase(word));
        return true;
    }
    return false;
}

bool Boggle::wordOnBoard(string& word){
    word = toUpperCase(word); //gör om till stor bokstav så att alla bokstäver som jämförs är stora
    string firstLetter = string(1, word[0]);
    for (int i = 0; i < board.nRows; i ++){ //går igenom alla rader och kolumner
        for (int j = 0; j < board.nCols; j ++){
            if (board.get(i,j) == firstLetter){ //hämta första bokstaven
                visited.clear(); //vill rensa inför varje sökning
                if (correctHumanGuess(word, i, j, board.get(i,j))){ //om ordet finns på brädet returnera sant
                    return true;
                }
            }
        }
    }
 return false;
}

bool Boggle::correctHumanGuess(const string& correctWord, const int& row, const int& col, const string& chosen){
    if (chosen == correctWord){ //är chosen nu det gissade ordet?
        return true;
    }
    else{
        for (int i=-1; i<2; i++){
            for(int j=-1; j<2; j++){
              if(!(i==0 && j==0) && board.inBounds(row+i,col+j)){
                   string letterNeighbor = board.get(row+i,col+j); //giltig koordinat, hämta nu värdet där
                   string neighbor = to_string(row+i) + to_string(col+j); //alla strängar med koordinater kommer vara unika
                   if (visited.find(neighbor) == visited.end() && isPrefix(chosen+letterNeighbor, correctWord)){
                       //om vi inte lagt till denna granne förut, samt att den nuvarande strängen+grannen
                       //är ett prefix till det gissade ordet, lägg till grannen och fortsätt sök.
                       visited.insert(neighbor);
                       bool found = correctHumanGuess(correctWord, row + i, col + j, chosen + letterNeighbor); //bygger upp chosen i varje anrop
                       if (found) { // Om det rekursiva anropet hittade ordet, returnera sant direkt
                         return true;
                       }
                       visited.erase(neighbor); //ta bort neighbor för backtracking
                   }
                }
            }
        }
    }
    return false;
}

bool Boggle::isPrefix(const string& substring, const string& word){
    if (word.find(substring) == 0){ //find() returnerar position som substrängen börjar, ett prefix börjar på pos 0
        return true;
    }
    return false;
}
void Boggle::findAllWords(){
    for (int i = 0; i < board.nRows; i ++){ //gå igenom alla rader och kolumner
            for (int j = 0; j < board.nCols; j ++){
                visited.clear(); //vill rensa inför varje sökning
                unordered_set<string> result = computerSearch(i , j , board.get(i, j)); //hämtar alla ogissade ord
                computerWords.insert(result.begin(), result.end()); //lägger in alla ord från resultatet
                //källa för insert: https://stackoverflow.com/questions/7089494/how-to-merge-multiple-sets-into-a-single-stdset-set-union
            }
    }

}
unordered_set<string> Boggle::computerSearch(const int& row, const int& col, const string& prefix){
    unordered_set<string> foundWords;
    visited.insert(to_string(row) + to_string(col)); // lägger till den bokstav vi utgår ifrån
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
          if(!(i==0 && j==0) && board.inBounds(row+i,col+j)){
               string letterNeighbour = board.get(row+i,col+j); //giltig koordinat, hämta nu värdet där
               string neighbor = to_string(row+i) + to_string(col+j); //alla strängar med koordinater kommer vara unika
               string newPrefix = prefix + letterNeighbour;
               if (visited.find(neighbor) == visited.end() && lexicon.containsPrefix(newPrefix)){
                   visited.insert(neighbor);

                   if (lexicon.contains(newPrefix) && humanWords.find(toUpperCase(newPrefix)) == humanWords.end()
                           && foundWords.find(newPrefix) == foundWords.end() && newPrefix.size() >= MIN_WORD_LENGTH) {
                     // om vi hittade ett ord i lexikonet, som inte människan gissat, samt inte hittats av datorn innan,
                     // av rätt längd, lägg till det nya hittade ordet
                       foundWords.insert(newPrefix);
                   }
                   unordered_set<string> subres = computerSearch(row + i, col + j, newPrefix); //efter vi lagt till, fortsätt sök om det finns längre ord med detta som prefix
                   foundWords.insert(subres.begin(), subres.end());
                   visited.erase(neighbor); //ta bort neighbor för backtracking
               }
            }
        }
    }
    return foundWords;
}
void Boggle::reset(){
    visited.clear();
    humanWords.clear();
    computerWords.clear();
}
